// DataSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data.h"
#include "DataSocket.h"

// CDataSocket

CDataSocket::CDataSocket()
	: m_pWndParent(NULL)
	, m_pFile(NULL)
	, m_pArchiveIn(NULL)
	, m_pArchiveOut(NULL)
	, m_nMSG(WM_USER + 2)
	, m_nTimerID(0)
	, m_dwStart(0)
	, m_dwTimeOut(0)
	, m_bCheck(FALSE)
{
}

CDataSocket::~CDataSocket()
{
	Reset();
}


// CDataSocket 멤버 함수
void CDataSocket::Init(CWnd *pWnd, UINT nMSG)
{
	Reset();

	m_nMSG = nMSG;

	m_pWndParent = pWnd;
	m_pFile = new CSocketFile(this);
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
}

void CDataSocket::Receive(CData * pData)
{
	if(m_pArchiveIn != NULL)
		pData->Serialize(*m_pArchiveIn);
}

int CDataSocket::Receive(void* lpBuf, int nBufLen, int nFlags)
{
	return CSocket::Receive(lpBuf, nBufLen, nFlags);
}

void CDataSocket::operator >>(CData & data)
{
	Receive (&data);
}

void CDataSocket::Send(CData * pData)
{
	if(m_pArchiveOut != NULL)
		pData->Serialize(*m_pArchiveOut);
}

int CDataSocket::Send(const void* lpBuf, int nBufLen, int nFlags)
{
	return CSocket::Send(lpBuf, nBufLen, nFlags);
}

void CDataSocket::Flush()
{
	if(m_pArchiveOut != NULL)
		m_pArchiveOut->Flush();
}

void CDataSocket::operator <<(CData & data)
{
	Send (&data);
	Flush();
}

void CDataSocket::OnReceive(int nErrorCode) 
{
	if( m_pWndParent )
		m_pWndParent->SendMessage(m_nMSG);

	CSocket::OnReceive(nErrorCode);
}

void CDataSocket::OnClose(int nErrorCode) 
{
	if( m_pWndParent )
	{
		m_pWndParent->SendMessage(m_nMSG, -1, -1);
	}
	Reset();
	
	CSocket::OnClose(nErrorCode);
}

void CDataSocket::Reset()
{
	if(m_pWndParent)
		m_pWndParent = NULL;

	if(m_pFile != NULL) {
		delete m_pFile;
		m_pFile = NULL;
	}
	if(m_pArchiveIn != NULL) {
		m_pArchiveIn->Abort();
		delete m_pArchiveIn;
		m_pArchiveIn = NULL;
	}
	if(m_pArchiveOut != NULL) {
		m_pArchiveOut->Abort();
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
	}	
}
BOOL CDataSocket::SetTimeOut(int nTimeOut)
{

	TRACE( _T("Start Timer %ld\n"), GetTickCount() );

	m_dwTimeOut = static_cast<DWORD>(nTimeOut);
	m_dwStart = GetTickCount();
	m_bCheck = TRUE;

	return TRUE;
}

BOOL CDataSocket::KillTimeOut()
{
	TRACE( _T("Kill Timer %ld\n"), GetTickCount() );

	m_bCheck = FALSE;

	return TRUE;
}


BOOL CDataSocket::OnMessagePending()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	TRACE( _T("OnMessagePending() %ld\n"), GetTickCount() );

	if( m_bCheck )
	{
		if( m_dwTimeOut < GetTickCount() - m_dwStart )
		{
			TRACE( _T("OnMessagePending()--TimeOut %ld\n"), GetTickCount() );
			m_bCheck = FALSE;

			CSocket::Close();
			Reset();
		}

	}
	return CSocket::OnMessagePending();
}
