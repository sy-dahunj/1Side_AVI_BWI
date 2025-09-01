// SocketTCP.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SocketTCP.h"

// CSocketTCP

IMPLEMENT_DYNAMIC(CSocketTCP, CWnd)

CSocketTCP *CSocketTCP::m_pInstance = NULL;

CSocketTCP* CSocketTCP::Get_Instance()
{
	if (!m_pInstance)
		m_pInstance = new CSocketTCP();
	return m_pInstance;
}

void CSocketTCP::Delete_Instance()
{
	if (m_pInstance)
		delete m_pInstance;
	m_pInstance = NULL;
}

CSocketTCP::CSocketTCP()
{
	m_pWndParent = NULL;
	
	m_nMsgAccept = 0;
	m_nMsgReceive_Client = 9001;

	m_bConnected_Client = FALSE;

	m_nPort_Client = 9001;

//	m_strIPAddress = _T("127.0.0.1");  // s:192.168.0.125, N-L 192.168.0.101  
	m_strIPAddress = _T("192.168.0.101");  // s:192.168.0.125, N-L 192.168.0.101  

	m_nTimeOut = 1000;
}

CSocketTCP::~CSocketTCP()
{
}


BEGIN_MESSAGE_MAP(CSocketTCP, CWnd)
END_MESSAGE_MAP()


// CSocketTCP 메시지 처리기입니다.
int CSocketTCP::SetParams_MSG( CWnd* pWnd, const UINT& nMsgAccept, const UINT& nMsgReceive, const UINT& nMsgClient )
{
	m_pWndParent = pWnd;
	m_nMsgAccept = nMsgAccept;
	m_nMsgReceive_Client = nMsgClient;

	return 0;
}

int CSocketTCP::SetParams_Client( const CString& strIP, const UINT& nPort, const int& nTimeOut )
{
	m_strIPAddress = strIP;
	m_nPort_Client = nPort;
	m_nTimeOut = nTimeOut;

	return 0;
}

int CSocketTCP::Connect()
{
	m_bConnected_Client = FALSE;

	m_DataSocket_Client.Close();
	m_DataSocket_Client.Reset();

	if( !m_DataSocket_Client.Create() )
	{
		return -1;
	}

	// 접속 요청
	m_DataSocket_Client.SetTimeOut(m_nTimeOut);
	if( !m_DataSocket_Client.Connect(m_strIPAddress, m_nPort_Client) )
	{		
		return -1;
	}
	m_DataSocket_Client.KillTimeOut();

	// 클라이언트 소켓 초기화
	m_DataSocket_Client.Init(m_pWndParent, m_nMsgReceive_Client);

	m_bConnected_Client = TRUE;
	
	//2D Barcode SetRead 
	SendData("LON\r");

	return 0;
}

int CSocketTCP::Reconnect()
{
	m_bConnected_Client = FALSE;

	m_DataSocket_Client.Close();
	m_DataSocket_Client.Reset();

	if( !m_DataSocket_Client.Create() )
	{
		return -1;
	}

	// 접속 요청
	if( !m_DataSocket_Client.Connect(m_strIPAddress, m_nPort_Client) )
	{		
		return -1;
	}

	// 클라이언트 소켓 초기화
	m_DataSocket_Client.Init(m_pWndParent, m_nMsgReceive_Client);

	m_bConnected_Client = TRUE;

	return 0;
}

int CSocketTCP::Disconnect()
{
	//2D Barcode ResetRead 
	SendData("LOFF\r");

	m_bConnected_Client = FALSE;

	m_DataSocket_Client.Close();
	m_DataSocket_Client.Reset();

	return 0;
}

int CSocketTCP::GetReceive( CString& strReceive )
{
	TCHAR chTemp[512];

#ifdef _UNICODE
	char ch[512];

	m_DataSocket.Receive( ch, 512 );
			
	MultiByteToWideChar(0, 0, ch, 512, chTemp, 512);
#else		
	m_DataSocket.Receive( (LPSTR)chTemp, 512 );
#endif
	strReceive = chTemp;

	return 0;
}

int CSocketTCP::GetReceive_Client( CString& strReceive )
{
	TCHAR chTemp[512];

#ifdef _UNICODE
	char ch[512];

	m_DataSocket_Client.Receive( ch, 512 );
			
	MultiByteToWideChar(0, 0, ch, 255, chTemp, 512);
#else		
	m_DataSocket_Client.Receive( (LPSTR)chTemp, 512 );
#endif
	strReceive = chTemp;

	return 0;
}

int CSocketTCP::SendData( const CString& strData )
{
	// 데이터 전송
	if( FALSE == IsConnected_Client() )
	{
		return -1;
	}

	TCHAR chTemp[512];
#ifdef _UNICODE
	char ch[512];

	swprintf_s(chTemp, 512, (LPCTSTR)strData);
	WideCharToMultiByte(0, 0, chTemp, 512, ch, 512, 0, 0);
		
	m_DataSocket_Client.Send( ch, 512 );
#else
	lstrcpyn( (LPSTR)chTemp, (LPSTR)strData.operator const TCHAR*(), 512 );
	m_DataSocket_Client.Send( chTemp, 512 );
#endif

	return 0;
}


int CSocketTCP::SendByte( BYTE data[], int nLength )
{
	// 데이터 전송
	if( FALSE == IsConnected_Client() )
	{
		return -1;
	}

	if( 255 < nLength )
		return -1;

	m_DataSocket_Client.Send( data, nLength );

	return 0;
}


int CSocketTCP::GetSocketName_Client( CString& strIPAddress, UINT& nPort )
{
	m_DataSocket.GetSockName(strIPAddress, nPort);
	return 0;
}

BOOL CSocketTCP::IsConnected_Client()
{
	return m_bConnected_Client;
}

