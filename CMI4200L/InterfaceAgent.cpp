// InterfaceAgent.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "InterfaceAgent.h"
#include "DataManager.h"
#include "Common.h"
#include "LogFile.h"
#include "Inspector.h"

#define	TCP_MESAgent_IP	"127.0.0.1"

IMPLEMENT_DYNAMIC(CInterfaceAgent, CWnd)

CInterfaceAgent *CInterfaceAgent::m_pInstance = NULL;

CInterfaceAgent *CInterfaceAgent::Get_Instance()
{
	if (!m_pInstance) {
		m_pInstance = new CInterfaceAgent();
		if (!m_pInstance->m_hWnd) {
			CRect r = m_pInstance->Get_Position();
			m_pInstance->CreateEx(0, AfxRegisterWndClass(0), "CInterfaceAgent", 0, r, NULL, 0, NULL);
		}
	}
	return m_pInstance;
}

void CInterfaceAgent::Delete_Instance()
{
	if (m_pInstance->m_hWnd) m_pInstance->DestroyWindow();
	if (m_pInstance) delete m_pInstance;
	m_pInstance = NULL;
}

// CInterfaceAgent

CInterfaceAgent::CInterfaceAgent()
{
	Set_Position(0, 0, 0, 0);
}

CInterfaceAgent::~CInterfaceAgent()
{
}

BEGIN_MESSAGE_MAP(CInterfaceAgent, CWnd)
	ON_MESSAGE(UM_CLIENT_CONNECT, OnClientConnect)
	ON_MESSAGE(UM_CLIENT_RECEIVE, OnClientReceive)
	ON_MESSAGE(UM_CLIENT_CLOSE, OnClientClose)

END_MESSAGE_MAP()

// CInterfaceAgent 메시지 처리기입니다.

void CInterfaceAgent::Initialize_Client()
{
	m_sRecvData = "";
	if (gData.bMESAgent==TRUE) return;
	
	m_Client.Close_Socket();
	Sleep(500);
	m_Client.Open_Socket(TCP_MESAgent_IP, gData.nPortClient, this);
	m_sRecvData = "";
}

void CInterfaceAgent::Terminate_Client()
{
	m_Client.Close_Socket();
	gData.bMESAgent = FALSE;
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CInterfaceAgent::OnClientConnect(WPARAM wParam, LPARAM lParam)
{
	gData.bMESAgent = TRUE;
//	CMESAgentDlg *pMESAgentDlg = CMESAgentDlg::Get_Instance();
//	pMESAgentDlg->SendMessage(UM_HOST_ONLINE, (WPARAM)NULL, (LPARAM)NULL);

	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("MESAgent Connected...........");

	return 0;
}

LRESULT CInterfaceAgent::OnClientClose(WPARAM wParam, LPARAM lParam)
{
	gData.bMESAgent = FALSE;
//	CMESAgentDlg *pMESAgentDlg = CMESAgentDlg::Get_Instance();
//	pMESAgentDlg->SendMessage(UM_HOST_OFFLINE, (WPARAM)NULL, (LPARAM)NULL);

	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("MESAgent Not Connected...........");

	return 0;
}

LRESULT CInterfaceAgent::OnClientReceive(WPARAM wParam, LPARAM lParam)
{
	char chSTX = '@';
	char chETX = '\n';

	BYTE byRecv[2048] = { 0 };
	int nLen = m_Client.Read_Socket(byRecv);

	CString strRecv, strData;
	strRecv.Format("%s", byRecv);

	int nS = strRecv.Find(chSTX);
	int nE = strRecv.Find(chETX);

	if (nS==0 && nE > 0) {
		m_sRecvData = strRecv;
		Get_ReciveData();
		return 1;
	}
	if (nE > 0) {
		m_sRecvData = m_sRecvData + strRecv;
		Get_ReciveData();
		return 1;
	}

	if (nS==0)	m_sRecvData = strRecv;
	else		m_sRecvData = m_sRecvData + strRecv;

	// Agent Log ///////////////////////////////////////////
	CString strLog;
	strLog.Format("[<-] : %s", strRecv);
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_AgentLog(strLog);
	///////////////////////////////////////////////////////

	return 1;
}

void CInterfaceAgent::Get_ReciveData()
{
	// Host Log ///////////////////////////////////////////
	CString strLog;
	strLog.Format("[<-] : %s", m_sRecvData);
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_AgentLog(strLog);
	///////////////////////////////////////////////////////

	int nStart = m_sRecvData.Find("@");
	int nEnd = m_sRecvData.Find("\n");
	if (nStart >= nEnd) return;

	CString strRecv = m_sRecvData.Mid(nStart + 1, nEnd - nStart - 1);

	char chSep = ',';
	CString strCmd, strOp;

	AfxExtractSubString(strCmd, strRecv, 0, chSep);
	AfxExtractSubString(strOp, strRecv, 1, chSep);

	if (strCmd == "CONNECT") {
		if (strOp == "REQUEST")	Get_ConnectRequest();

	} else if (strCmd == "MESHOST") {
		Get_ConnectMESHost(strOp);

	} else if (strCmd == "RESULT") {
		Get_ResultData(strRecv);

	} else if (strCmd == "ERROR") {
		CString strID, strData;
		AfxExtractSubString(strID, strRecv, 2, chSep);
		AfxExtractSubString(strData, strRecv, 3, chSep);
		Get_Error(strOp, strID, strData);

	}
}

///////////////////////////////////////////////////////////////////////////////
// Get Command

void CInterfaceAgent::Get_ConnectRequest()
{
	Set_ConnectReply();
}

void CInterfaceAgent::Get_ConnectMESHost(CString sData)
{
	int nConnect = atoi(sData);
	if (nConnect==1) gData.bMESHost=TRUE;
	else			 gData.bMESHost=FALSE;
}

void CInterfaceAgent::Get_ResultData(CString sData)
{
	char chSep = ',';
	int	x, nCount;
	CString	sTemp, sCnt, strLog;

	AfxExtractSubString(sTemp, sData, 0, chSep);
	AfxExtractSubString(sCnt, sData, 1, chSep);
	nCount = atoi(sCnt);
	
	if(nCount <= 0) {
		strLog.Format("MESAgent ReciveData CM Count error => %d", nCount);
		CLogFile *pLogFile = CLogFile::Get_Instance();
		pLogFile->Save_HandlerLog(strLog);

		CCommon *pCommon = CCommon::Get_Instance();
		pCommon->Show_Error(904);
		return;
	}

	x = 2;
	if (gCM.nType==0) {
		gCM.nLCount = nCount;
		if(gCM.nLCount > 999) {
			strLog.Format("MESAgent ReciveData CM Count error => %d", nCount);
			CLogFile *pLogFile = CLogFile::Get_Instance();
			pLogFile->Save_HandlerLog(strLog);
			gCM.nLCount = 990;
		}

		for(int i=0; i<gCM.nLCount; i++) {
			for(int j=0; j<6; j++) {
				AfxExtractSubString(sTemp, sData, x, chSep);
				gCM.sLData[i][j] = sTemp;
				x++;
			}
		}
	}

	if (gCM.nType==1) {
		gCM.nType = 0;
		gCM.nMCount = nCount;
		if(gCM.nMCount > 9) {
			strLog.Format("MESAgent ReciveData CM Count error => %d", nCount);
			CLogFile *pLogFile = CLogFile::Get_Instance();
			pLogFile->Save_HandlerLog(strLog);
			gCM.nMCount = 9;
		}

		for(int i=0; i<gCM.nMCount; i++) {
			for(int j=0; j<6; j++) {
				AfxExtractSubString(sTemp, sData, x, chSep);
				gCM.sMData[i][j] = sTemp;
				x++;
			}
		}

		CInspector *pInspector = CInspector::Get_Instance();
//		pInspector->Get_InspectComplete(1, gCM.sInspecData, 2);
	}
}

void CInterfaceAgent::Get_Error(CString strOp, CString strID, CString strData)
{
}


///////////////////////////////////////////////////////////////////////////////
// Set Command


void CInterfaceAgent::Set_ConnectReply()
{
	m_strSend.Format("CONNECT,REPLY");
	Send_Command(m_strSend);
}

void CInterfaceAgent::Set_RequestLot(CString sLotID, int Count)
{
	gCM.nLCount = gCM.nMCount = 0;
	gCM.nType = 0;

	m_strSend.Format("LOT,%s,%d", sLotID, Count);
	Send_Command(m_strSend);
}

void CInterfaceAgent::Set_RequestCM(CString sLotID, int Count, CString sCMData)
{
	gCM.nMCount = 0;
	gCM.nType = 1;

	m_strSend.Format("CM,%s,%d,%s", sLotID, Count, sCMData);
	Send_Command(m_strSend);
}

void CInterfaceAgent::Set_CT()
{
	m_strSend.Format("CT");
	Send_Command(m_strSend);
}

///////////////////////////////////////////////////////////////////////////////
void CInterfaceAgent::Send_Command(CString sSend)
{
	CString strSend;
	strSend.Format("@%s\n", sSend);

	// Host Log ////////////////////////////////////////////
	CString strLog;
	strLog.Format("[->] : %s", strSend);
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_AgentLog(strLog);
	///////////////////////////////////////////////////////

	char chSend[102400] = { 0 };
	int nLength = strSend.GetLength();
	memcpy(chSend, (LPSTR)(LPCSTR)strSend, nLength);

	if (!m_Client.Write_Socket((BYTE*)chSend, nLength)) return;

//	CMESAgentDlg *pMESAgentDlg = CMESAgentDlg::Get_Instance();
//	pMESAgentDlg->SendMessage(UM_HOST_DATA, (WPARAM)&strLog, (LPARAM)NULL);
}

///////////////////////////////////////////////////////////////////////////////

void CInterfaceAgent::Test_Set()
{

}