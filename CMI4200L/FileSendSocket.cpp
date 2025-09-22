// FileSendSocket.cpp  (VS2010용)
#include "stdafx.h"
#include "FileSendSocket.h"

CFileSendSocket::CFileSendSocket()
	: m_state(SEND_IDLE),
	m_fileSize(0),
	m_hdrSent(0),
	m_nameSent(0),
	m_dataSent(0) {
		m_hdr.fileSizeN = 0;
		m_hdr.nameLenN  = 0;
}

CFileSendSocket::~CFileSendSocket() {
	if (m_in.m_hFile != CFile::hFileNull) m_in.Close();
}

BOOL CFileSendSocket::BeginSend(const CString& path, const CString& sendName) {
	if (m_state != SEND_IDLE && m_state != SEND_DONE) return FALSE;

	CFileException ex;
	if (!m_in.Open(path, CFile::modeRead | CFile::typeBinary | CFile::modeNoTruncate , &ex)) {
		m_state = SEND_ERR; return FALSE;
	}
	ULONGLONG sz = m_in.GetLength();
	m_fileSize = (uint64_t)sz;

	CString name = sendName;
	if (name.IsEmpty()) {
		int p = path.ReverseFind(_T('\\'));
		name = (p >= 0) ? path.Mid(p + 1) : path;
	}
	CT2A aName(name);
	m_name.assign((LPCSTR)aName, (LPCSTR)aName + strlen(aName));

	m_hdr.fileSizeN = htonll(m_fileSize);
	m_hdr.nameLenN  = htonl((uint32_t)m_name.size());
	m_hdrSent  = 0;
	m_nameSent = 0;
	m_dataSent = 0;

	m_state = SEND_HEADER;

	// 최초 송신 시도 + 이벤트 등록
	OnSend(0);
	AsyncSelect(FD_WRITE | FD_CLOSE);

	
	if (m_in.m_hFile != CFile::hFileNull) 
	{		
		m_in.Close();
		
	}
	m_state = SEND_IDLE;
	m_fileSize = 0;
	m_hdrSent = 0;
	m_nameSent = 0;
	m_dataSent =0; 
	m_hdr.fileSizeN = 0;
	m_hdr.nameLenN  = 0;
	
	return TRUE;
}

int CFileSendSocket::SafeSend(const void* buf, int len) {
	int ret = Send(buf, len);
	if (ret == SOCKET_ERROR) {
		int err = GetLastError();
		if (err == WSAEWOULDBLOCK) return 0;
		m_state = SEND_ERR;
		return SOCKET_ERROR;
	}
	return ret;
}

void CFileSendSocket::OnSend(int nErrorCode) {
	if (nErrorCode) { m_state = SEND_ERR; CAsyncSocket::OnSend(nErrorCode); return; }

	BYTE ioBuf[64 * 1024];

	for (;;) {
		if (m_state == SEND_HEADER) {
			int remain = (int)(sizeof(m_hdr) - m_hdrSent);
			if (remain > 0) {
				int sent = SafeSend(((BYTE*)&m_hdr) + m_hdrSent, remain);
				if (sent <= 0) break;
				m_hdrSent += sent;
				if (m_hdrSent < sizeof(m_hdr)) break;
			}
			m_state = SEND_NAME;
		}
		else if (m_state == SEND_NAME) {
			int remain = (int)(m_name.size() - m_nameSent);
			if (remain > 0) {
				int sent = SafeSend(m_name.data() + m_nameSent, remain);
				if (sent <= 0) break;
				m_nameSent += sent;
				if (m_nameSent < m_name.size()) break;
			}
			m_state = SEND_DATA;
		}
		else if (m_state == SEND_DATA) {
			if (m_dataSent >= m_fileSize) {
				m_state = SEND_DONE;
				break;
			}
			uint64_t remain64 = (m_fileSize > m_dataSent) ? (m_fileSize - m_dataSent) : 0ULL;
			UINT toRead = (UINT)((remain64 < (uint64_t)sizeof(ioBuf)) ? remain64 : (uint64_t)sizeof(ioBuf));
			UINT got = m_in.Read(ioBuf, toRead);
			if (got == 0) { m_state = SEND_DONE; break; }

			int sent = SafeSend(ioBuf, (int)got);
			if (sent < 0) break;            // error
			if (sent == 0) {                // would block → 롤백
				m_in.Seek(-(LONGLONG)got, CFile::current);
				break;
			}
			if ((UINT)sent < got) {         // 일부만 전송 → 남은 만큼 롤백
				LONGLONG delta = (LONGLONG)sent - (LONGLONG)got; // 음수
				m_in.Seek(delta, CFile::current);
				m_dataSent += (uint64_t)sent;
				break;
			}
			m_dataSent += got;
		}
		else break;
	}

	CAsyncSocket::OnSend(nErrorCode);
}

void CFileSendSocket::OnClose(int nErrorCode) {
	if (m_in.m_hFile != CFile::hFileNull) m_in.Close();
	CAsyncSocket::OnClose(nErrorCode);
}