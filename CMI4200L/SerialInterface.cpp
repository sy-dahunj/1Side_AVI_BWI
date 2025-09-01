// SerialInterface.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SerialInterface.h"


CString CSerialInterface::m_sStrConvError = _T("");

/////////////////////////////////////////////////////////////////////////////
// CQueue 구현부

// Queue의 생성자
CQueue::CQueue()
{
	Clear();
}

// Queue를 초기화
void CQueue::Clear()
{
	m_iHead = m_iTail = 0;
	memset(buff, 0, MAX_COM_BUFFER);
}

// Queue에 들어 있는 자료 개수.
int CQueue::GetSize()
{
	return (m_iHead - m_iTail + MAX_COM_BUFFER) % MAX_COM_BUFFER;
}

// Queue에 1 byte 넣음.
bool CQueue::PutByte(BYTE b)
{
	if (GetSize() == (MAX_COM_BUFFER-1)) 
		return false;
	buff[m_iHead++] = b;
	m_iHead %= MAX_COM_BUFFER;
	return true;
}

// Queue에서 1 byte 꺼냄.
bool CQueue::GetByte(BYTE* pb)
{
	if (GetSize() == 0) 
		return false;
	*pb = buff[m_iTail++];
	m_iTail %= MAX_COM_BUFFER;
	return true;
}

// CSerialInterface

IMPLEMENT_DYNAMIC(CSerialInterface, CWnd)

CSerialInterface::CSerialInterface()
: m_hComm(NULL)
, m_bConnected(false)
, m_dwMaxBuffer(MAX_COM_BUFFER)
{

}

CSerialInterface::~CSerialInterface()
{
	bDisConnect();
}


BEGIN_MESSAGE_MAP(CSerialInterface, CWnd)
END_MESSAGE_MAP()



// CSerialInterface 메시지 처리기입니다.
bool CSerialInterface::bDisConnect()
{
	if(m_hComm!=NULL)
	{
		//	Modify by jaehuns because remain handle. 2009.04.13
		if(m_osRead.hEvent  != NULL) 
		{ 
			CloseHandle(m_osRead.hEvent); 
			m_osRead.hEvent = NULL; 
		}
		if(m_osWrite.hEvent != NULL) 
		{ 
			CloseHandle(m_osWrite.hEvent); 
			m_osWrite.hEvent = NULL; 
		}


		SetCommMask(m_hComm, 0);
		PurgeComm(m_hComm, 
			PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR );
		CloseHandle(m_hComm);
		m_hComm=NULL;
		m_bConnected=false;

	}

	return true;
}

bool CSerialInterface::bCheckCOM(HANDLE hComm)
{
	WORD wSize;

	// first allocation memory
	LPCOMMPROP lpCommProp=(LPCOMMPROP)malloc(sizeof(COMMPROP));
	lpCommProp->wPacketLength=sizeof(COMMPROP);
	GetCommProperties(hComm, lpCommProp);
	wSize=lpCommProp->wPacketLength;
	free(lpCommProp);

	// second allocation memory
	lpCommProp=(LPCOMMPROP)malloc(wSize);
	lpCommProp->wPacketLength=wSize;
	GetCommProperties(hComm, lpCommProp);

	// Checking Comm
	CString str;

	if(lpCommProp->dwProvSubType!=PST_RS232 )
	{
		m_sStrConvError = _T("PST_RS232 false");
		if(lpCommProp->dwProvSubType!=PST_MODEM)
		{
			m_sStrConvError = _T("PST_MODEM false");
			return false;
		}
	}

	if(lpCommProp->dwMaxTxQueue!=0)
		m_dwMaxBuffer=lpCommProp->dwMaxTxQueue;
	if( (lpCommProp->dwMaxRxQueue!=0) && (lpCommProp->dwMaxRxQueue < lpCommProp->dwMaxTxQueue) )
		m_dwMaxBuffer=lpCommProp->dwMaxRxQueue;

	if( (lpCommProp->dwSettableParams & SP_BAUD) != SP_BAUD )
	{
		m_sStrConvError = _T("Can not Init Baud rate");
		return false;
	}
	if( (lpCommProp->dwSettableParams & SP_DATABITS) != SP_DATABITS )
	{
		m_sStrConvError = _T("Can not Init SP_DATABITS");
		return false;
	}
	if( (lpCommProp->dwSettableParams & SP_HANDSHAKING) != SP_HANDSHAKING )
	{
		m_sStrConvError = _T("Can not Init SP_HANDSHAKING");
		return false;		
	}
	if( (lpCommProp->dwSettableParams & SP_PARITY) != SP_PARITY )
	{
		m_sStrConvError = _T("Can not Init SP_PARITY");
		return false;
	}
	if( (lpCommProp->dwSettableParams & SP_PARITY_CHECK) != SP_PARITY_CHECK )
	{
		m_sStrConvError = _T("Can not Init SP_PARITY_CHECK");
		return false;
	}
	if( (lpCommProp->dwSettableParams & SP_RLSD) != SP_RLSD )
	{
		m_sStrConvError = _T("Can Init SP_RLSD");
		return false;
	}
	if( (lpCommProp->dwSettableParams & SP_STOPBITS) != SP_STOPBITS )
	{
		m_sStrConvError = _T("Can not Init SP_STOPBITS");
		return false;
	}

	// Free memory
	free(lpCommProp);
	return true;
}

DWORD CSerialInterface::WriteComm(BYTE *pBuff, DWORD nToWrite)
{
	DWORD	dwWritten, dwError, dwErrorFlags;
	COMSTAT	comstat;

	if (! WriteFile( m_hComm, pBuff, nToWrite, &dwWritten, &m_osWrite) )
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			// 읽을 문자가 남아 있거나 전송할 문자가 남아 있을 경우 Overapped IO의
			// 특성에 따라 ERROR_IO_PENDING 에러 메시지가 전달된다.
			//timeouts에 정해준 시간만큼 기다려준다.
			while (! GetOverlappedResult( m_hComm, &m_osWrite, &dwWritten, true))
			{
				dwError = GetLastError();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError( m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError( m_hComm, &dwErrorFlags, &comstat);
		}
	}

	return dwWritten;
}

DWORD CSerialInterface::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD	dwRead, dwError, dwErrorFlags;
	COMSTAT	comstat;

	//----------------- system queue에 도착한 byte수만 미리 읽는다.
	ClearCommError( m_hComm, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;

	if (dwRead > 0)
	{
		if (! ReadFile( m_hComm, pBuff, nToRead, &dwRead, &m_osRead))
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				//--------- timeouts에 정해준 시간만큼 기다려준다.
				while (! GetOverlappedResult( m_hComm, &m_osRead, &dwRead, true))
				{
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError( m_hComm, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError( m_hComm, &dwErrorFlags, &comstat);
			}
		}
	}

	return dwRead;
}

bool CSerialInterface::bConnect(LPCTSTR lpFileName, DWORD dwBaudRate, BYTE ByteSize, BYTE byParity, BYTE byStopBits, DWORD dwXonoff)
{
	CString strLog;

	strLog.Format(_T("SubCtrl::Connect(COM=%s, BaudRate=%d, Byte=%d, Parity=%d, Stop=%d, Xonoff=%d"),
		lpFileName, dwBaudRate, ByteSize, byParity, byStopBits, dwXonoff);

	CString strTest;
	DCB dcb;
	COMMTIMEOUTS timeouts;

	// Init overlapped structure.
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;

	//	Modify by jaehuns because remain handle. 2009.04.13
	m_osRead.hEvent = CreateEvent(NULL, true, false, NULL);
	if(!m_osRead.hEvent) 
	{
		return(false);
	}

	m_osWrite.hEvent = CreateEvent(NULL, true, false, NULL);
	if(!m_osWrite.hEvent)
	{
		CloseHandle(m_osRead.hEvent);
		m_osRead.hEvent = NULL;
		return (false);
	}

	// Create COM Port
	m_hComm=CreateFile(lpFileName, GENERIC_READ|GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, NULL);

	if(m_hComm==INVALID_HANDLE_VALUE)  // modify by jaehuns 2009.04.13
	{
		m_hComm = NULL;  
		//	Modify by jaehuns because remain handle. 2009.04.13
		if(m_osRead.hEvent  != NULL) { CloseHandle(m_osRead.hEvent); m_osRead.hEvent = NULL; }
		if(m_osWrite.hEvent != NULL) { CloseHandle(m_osWrite.hEvent); m_osWrite.hEvent = NULL; }

		return false;
	}

	if(!bCheckCOM(m_hComm))
	{
		return false;
	}

	// Set Event 
	SetCommMask(m_hComm, EV_RXCHAR);
	// Set Buffer size
	SetupComm(m_hComm, m_dwMaxBuffer, m_dwMaxBuffer);
	// Port Init
	PurgeComm(m_hComm, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR );

	// Set TimeOut
	timeouts.ReadIntervalTimeout=0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier=0;
	timeouts.ReadTotalTimeoutConstant=0;
	timeouts.WriteTotalTimeoutMultiplier=2*CBR_9600/dwBaudRate;
	timeouts.WriteTotalTimeoutConstant=0;
	SetCommTimeouts(m_hComm, &timeouts);

	dcb.DCBlength=sizeof(DCB);
	GetCommState(m_hComm, &dcb);

	dcb.BaudRate=dwBaudRate;
	dcb.ByteSize=ByteSize;
	dcb.Parity=byParity;
	dcb.StopBits=byStopBits;
	dcb.fInX=dcb.fOutX=dwXonoff;

	if(dwXonoff)
	{
		dcb.XonChar=ASCII_XON;
		dcb.XoffChar=ASCII_XOFF;
		dcb.XonLim=100;
		dcb.XoffLim=100;
	}

	if(!SetCommState(m_hComm, &dcb))
	{
		return false;
	}

	m_bConnected=true;

	return m_bConnected;
}

bool CSerialInterface::SetEventDefault()
{
	bool bOk=true;
	memset(&m_Os, 0, sizeof(OVERLAPPED));

	if (! (m_Os.hEvent = CreateEvent( NULL, true, false, NULL)) )
		bOk = false;
	if (! SetCommMask(m_hComm, EV_RXCHAR) )
		bOk = false;
	if (! bOk)
	{
		//		pConInf->m_sStrConvError="Error while creating ThreadWatchComm";
		return false;
	}
	return bOk;
}

void CSerialInterface::CloseOS()
{
	if(m_Os.hEvent)
	{
		CloseHandle(m_Os.hEvent);
		m_Os.hEvent = NULL;
	}	
}

BOOL CSerialInterface::WaitCOMEvent(LPDWORD lpEvtMask, LPOVERLAPPED lpOverlapped)
{
	return static_cast<BOOL>( WaitCommEvent(m_hComm, lpEvtMask, lpOverlapped) );
}


 