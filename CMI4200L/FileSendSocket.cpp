// FileSendSocket.cpp  (VS2010¿ë)
#include "stdafx.h"
#include "FileSendSocket.h"

CFileSendSocket::CFileSendSocket()
	: m_state(SEND_IDLE),
	m_fileSize(0),
	m_hdrSent(0),
	m_nameSent(0),
	m_dataSent(0),
	m_bConnected(FALSE)
{
	m_hdr.fileSizeN = 0;
	m_hdr.nameLenN  = 0;
}

CFileSendSocket::~CFileSendSocket()
{
	if (m_in.m_hFile != CFile::hFileNull)
		m_in.Close();
}

BOOL CFileSendSocket::BeginSend(const CString& path, const CString& sendName)
{
	try
	{
		if (m_state != SEND_IDLE && m_state != SEND_DONE)
			return FALSE;

		CFileException ex;
		if (!m_in.Open(path, CFile::modeRead | CFile::typeBinary | CFile::modeNoTruncate, &ex))
		{
			m_state = SEND_ERR;
			return FALSE;
		}

		ULONGLONG sz = m_in.GetLength();
		m_fileSize = (uint64_t)sz;

		CString name = sendName;
		if (name.IsEmpty())
		{
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

		OnSend(0);

		return TRUE;
	}
	catch (CFileException* pEx)
	{
		return FALSE;
	}
}

int CFileSendSocket::SafeSend(const void* buf, int len)
{
	int ret = Send(buf, len);
	if (ret == SOCKET_ERROR)
	{
		int err = GetLastError();
		if (err == WSAEWOULDBLOCK)
			return 0;
		m_state = SEND_ERR;
		return SOCKET_ERROR;
	}
	return ret;
}

void CFileSendSocket::OnSend(int nErrorCode)
{
	try
	{
		if (nErrorCode)
		{
			m_state = SEND_ERR;
			CAsyncSocket::OnSend(nErrorCode);
			return;
		}

		if (m_in.m_hFile == CFile::hFileNull)
			return;

		BYTE ioBuf[64 * 1024];

		for (;;)
		{
			if (m_state == SEND_HEADER)
			{
				int remain = (int)(sizeof(m_hdr) - m_hdrSent);
				if (remain > 0)
				{
					int sent = SafeSend(((BYTE*)&m_hdr) + m_hdrSent, remain);
					if (sent <= 0) break;
					m_hdrSent += sent;
					if (m_hdrSent < sizeof(m_hdr)) break;
				}
				m_state = SEND_NAME;
			}
			else if (m_state == SEND_NAME)
			{
				int remain = (int)(m_name.size() - m_nameSent);
				if (remain > 0)
				{
					int sent = SafeSend(m_name.data() + m_nameSent, remain);
					if (sent <= 0) break;
					m_nameSent += sent;
					if (m_nameSent < (int)m_name.size()) break;
				}
				m_state = SEND_DATA;
			}
			else if (m_state == SEND_DATA)
			{
				if (m_dataSent >= m_fileSize)
				{
					m_state = SEND_DONE;
					break;
				}

				uint64_t remain64 = m_fileSize - m_dataSent;
				UINT toRead = (UINT)((remain64 < sizeof(ioBuf)) ? remain64 : sizeof(ioBuf));
				UINT got = m_in.Read(ioBuf, toRead);
				if (got == 0)
				{
					m_state = SEND_DONE;
					break;
				}

				int sent = SafeSend(ioBuf, (int)got);
				if (sent < 0) break;
				if (sent == 0)
				{
					m_in.Seek(-(LONGLONG)got, CFile::current);
					break;
				}
				if ((UINT)sent < got)
				{
					LONGLONG delta = (LONGLONG)sent - (LONGLONG)got;
					m_in.Seek(delta, CFile::current);
					m_dataSent += sent;
					break;
				}
				m_dataSent += got;
			}
			else break;
		}

		if (m_state == SEND_DONE)
		{
			m_in.Close();
			m_state = SEND_IDLE;
			m_fileSize = 0;
			m_hdrSent = 0;
			m_nameSent = 0;
			m_dataSent = 0;
			m_hdr.fileSizeN = 0;
			m_hdr.nameLenN = 0;
		}
	}
	catch (CFileException* pEx)
	{
		return;
	}

	CAsyncSocket::OnSend(nErrorCode);
}

void CFileSendSocket::OnClose(int nErrorCode)
{
	try
	{
		m_bConnected = FALSE;
		if (m_in.m_hFile != CFile::hFileNull)
			m_in.Close();
	}
	catch (CFileException* pEx)
	{
		m_bConnected = FALSE;
	}

	CAsyncSocket::OnClose(nErrorCode);
}

BOOL CFileSendSocket::ConnectToServer(LPCTSTR ip, UINT port)
{
	try
	{
		if (m_hSocket != INVALID_SOCKET)
		{
			ShutDown();
			Close();
		}

		if (!Create())
		{
			return FALSE;
		}

		AsyncSelect(FD_WRITE | FD_CLOSE);

		if (!Connect(ip, port))
		{
			int err = GetLastError();
			if (err != WSAEWOULDBLOCK)
			{
				return FALSE;
			}
		}
	}
	catch (CFileException* pEx)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CFileSendSocket::SendFile(const CString& path)
{
#ifdef AJIN_BOARD_USE
	CString ip = _T("192.168.1.12");
	UINT port = 21000;
#else
	//CString ip = _T("192.168.219.73");
	CString ip = _T("127.0.0.1");
	UINT port = 21000;
#endif

	try
	{
		if (!m_bConnected)
		{
			m_lastFilePath = path;
			if (!ConnectToServer(ip, port))
				return FALSE;
			return FALSE;
		}

		BOOL ret = BeginSend(path);
		if (!ret)
		{
			return FALSE;
		}
	}
	catch (CFileException* pEx)
	{
		return FALSE;
	}

	return TRUE;
}

void CFileSendSocket::OnConnect(int nErrorCode)
{
	try
	{
		if (nErrorCode == 0)
		{
			m_bConnected = TRUE;

			if (!m_lastFilePath.IsEmpty())
			{
				BeginSend(m_lastFilePath);
				m_lastFilePath.Empty();
			}
		}
		else
		{
			m_bConnected = FALSE;
		}
	}
	catch (CFileException* pEx)
	{
		m_bConnected = FALSE;
	}

	CAsyncSocket::OnConnect(nErrorCode);
}