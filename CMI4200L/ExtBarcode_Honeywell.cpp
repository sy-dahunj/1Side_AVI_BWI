// ExtBarcode_Honeywell.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ExtBarcode_Honeywell.h"
#include "DataManager.h"


#define SCAN_PORT	"COM7"
// CExtBarcode_Honeywell

IMPLEMENT_DYNAMIC(CExtBarcode_Honeywell, CWnd)

CExtBarcode_Honeywell *CExtBarcode_Honeywell::m_pInstance = NULL;

CExtBarcode_Honeywell* CExtBarcode_Honeywell::Get_Instance()
{
	if (!m_pInstance)
		m_pInstance = new CExtBarcode_Honeywell();
	return m_pInstance;
}

void CExtBarcode_Honeywell::Delete_Instance()
{
	if (m_pInstance)
		delete m_pInstance;
	m_pInstance = NULL;
}

CExtBarcode_Honeywell::CExtBarcode_Honeywell()
: m_bConnected(FALSE)
, m_bChanged(FALSE)
, m_strRead(_T(""))
, m_strBarcode(_T(""))
, m_hWndParent(NULL)
, m_nMSG(0)
, m_pThread(NULL)
{

}

CExtBarcode_Honeywell::~CExtBarcode_Honeywell()
{
}


BEGIN_MESSAGE_MAP(CExtBarcode_Honeywell, CWnd)
END_MESSAGE_MAP()

// CExtBarcode_Honeywell 메시지 처리기입니다.

int CExtBarcode_Honeywell::Initialize()
{
	Connect();
	
	return 0;
}

int CExtBarcode_Honeywell::UnInitialize()
{
	Disconnect();

	return 0;
}

int CExtBarcode_Honeywell::Save()
{
	return 0;
}

int CExtBarcode_Honeywell::Load()
{
	return 0;
}


int CExtBarcode_Honeywell::Connect()
{

	m_strRead = _T("");

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	CString strCOMPort = pEquipData->sNGBarcodePort;//SCAN_PORT;  //  dataG.GetStringValue(CDefCMI2k::strBarcodeReaderCOM);

	if(!m_Rs232c.bConnect(strCOMPort, 115200, 8, 0, 0, 0) )
	{
		Disconnect();
		//strCOMPort =  _T("//./") + strCOMPort;
		if(!m_Rs232c.bConnect( strCOMPort, 115200, 8, 0, 0, 0) )
		{
			Disconnect();
	
			return -1;
		}
	}

	m_strRead = _T("");

	
	if( !( m_pThread = (CWinThread*)AfxBeginThread(ThreadFunc, this) ) )
	{
		Disconnect();
		return -1;
	}

	return 0;
}

int CExtBarcode_Honeywell::Connect(LPCTSTR lpFileName, DWORD dwBaudRate, BYTE ByteSize, BYTE byParity, BYTE byStopBits, DWORD dwXonoff) 
{
	if(!m_Rs232c.bConnect(lpFileName, dwBaudRate, ByteSize, byParity, byStopBits, dwXonoff) )
	{
		Disconnect();
		CString strCOMPort;
		strCOMPort.Format( _T("//./%s"), lpFileName);

		if(!m_Rs232c.bConnect( strCOMPort, dwBaudRate, ByteSize, byParity, byStopBits, dwXonoff) )
		{
			Disconnect();
	
			return -1;
		}
	}

	m_strRead = _T("");
	
	if( !( m_pThread = (CWinThread*)AfxBeginThread(ThreadFunc, this) ) )
	{
		Disconnect();
		return -1;
	}

	return 0;
}

int CExtBarcode_Honeywell::Disconnect()
{
	m_Rs232c.bDisConnect();

	if( m_pThread )
	{
		WaitForSingleObject(m_pThread->m_hThread, 3000);

		m_pThread = NULL;
	}
	return 0;
}

BOOL CExtBarcode_Honeywell::IsConnected() const
{
	return m_Rs232c.m_bConnected;
}


int CExtBarcode_Honeywell::GetBarcode(CString& strBarcode)
{
	strBarcode = m_strBarcode;
	m_strBarcode = _T("");
	return 0;
}

BOOL CExtBarcode_Honeywell::IsChanged() const
{
	return m_bChanged;
}

int CExtBarcode_Honeywell::ResetChanged()
{
	m_bChanged = FALSE;
	m_strBarcode = _T("");

	return 0;
}

int CExtBarcode_Honeywell::SetMessage(HWND hWnd, UINT Msg)
{
	m_hWndParent = hWnd;
	m_nMSG = Msg;

	return 0;
}

UINT CExtBarcode_Honeywell::ThreadFunc(LPVOID lpThreadParam)
{
	CExtBarcode_Honeywell *pSubCtrl = (CExtBarcode_Honeywell *)lpThreadParam;
	CSerialInterface *pRs232c = &pSubCtrl->m_Rs232c;

	DWORD		dwEvent;
	BYTE		buff[8192];	 // 읽기 버퍼
	DWORD		dwRead;	 // 읽은 바이트수.
	long		temp=0;

	// Event, OS 설정.
	if(!pRs232c->SetEventDefault())
		return -1;

	// 포트를 감시하는 루프.
	while (pRs232c->m_bConnected)
	{
		dwEvent = 0;
		char ch;

		// 포트에 읽을 거리가 올때까지 기다린다.
		pRs232c->WaitCOMEvent(&dwEvent);		

		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{		
			// 포트에서 읽을 수 있는 만큼 읽는다.
			do	
			{
				dwRead = pRs232c->ReadComm(buff, MAX_COM_BUFFER);

				for( DWORD i=0; i< dwRead; i++ )
				{
					switch(buff[i])
					{
					case ASCII_STX:				//0x02
						ch = buff[i];
						break;
					case ASCII_LF:				//0x0A
					case ASCII_CR:				//0x0D
						pSubCtrl->ReadProcess();
						break;
					default: 
						pSubCtrl->AddChar(buff[i]);
						break;
					}//switch(buff[i])
				}//for( DWORD i=0; i< dwRead; i++ )
			} while (dwRead);
		}
	}	
	pRs232c->CloseOS();
	return 0;
}


int CExtBarcode_Honeywell::AddChar(char ch)
{
	m_strRead+=ch;

	return 0;
}

int CExtBarcode_Honeywell::ReadProcess()
{
	if( _T("") != m_strRead )
	{
		if( m_strBarcode != m_strRead )
		{
			m_strBarcode = m_strRead;
			m_bChanged = TRUE;
		}
	}

	if(NULL!=m_hWndParent)
	{
		::SendMessage(m_hWndParent, m_nMSG, 0, (LPARAM)(LPCTSTR)m_strBarcode);
		//어떻게 활용해야 하는지는 구현해야 함..
	}

	m_strRead = _T("");
	return 0;
}
