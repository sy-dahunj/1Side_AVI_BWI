// CapAttachUDP.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "CapAttachUDP.h"

#include "DataManager.h"
#include "LogFile.h"
#include "Common.h"
#include "SequenceMain.h"
#include "MESInterface.h"

#define UDP_CAPATTACH_LPORT	8050
#define UDP_CAPATTACH_HPORT	8050

IMPLEMENT_DYNAMIC(CCapAttachUDP, CWnd)

CCapAttachUDP g_objCapAttachUDP;

CCriticalSection g_csCapAttachUDP;	// Send_Command 문제 해결하기 위함

// CCapAttachUDP

CCapAttachUDP::CCapAttachUDP()
{
	m_strRecvCmd = "";
	m_bOpened = FALSE;
	m_bConnected = FALSE;
	m_nStatusCapAttach = 0;	// 상태 (0:Not Ready, 1:Ready)
	
	Reset();
}

CCapAttachUDP::~CCapAttachUDP()
{
}

BEGIN_MESSAGE_MAP(CCapAttachUDP, CWnd)
	ON_MESSAGE(UM_UDP_RECEIVE, OnUdpReceive)
END_MESSAGE_MAP()

// CCapAttachUDPer 메시지 처리기입니다.

BOOL CCapAttachUDP::Initialize()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	if (!pEquipData->bUseInlineMode) return FALSE;
	if (m_bOpened) return TRUE;

	m_bOpened = m_UdpCapAttach.Open_Socket(UDP_CAPATTACH_LPORT, UDP_CAPATTACH_HPORT, pEquipData->sCapAttachIp, this);
	if (!m_bOpened) return FALSE;
		
	Set_ConnectRequest();
	Reset();	// Clear

	CString strLog;
	strLog.Format("Initialize : IP(%s)", pEquipData->sCapAttachIp);
	pLogFile->Save_CapAttachLog(strLog);

	return TRUE;
}

void CCapAttachUDP::Terminate()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	Set_ConnectEnd();
	m_bOpened = FALSE;
	m_UdpCapAttach.Close_Socket();
	pLogFile->Save_CapAttachLog("Terminate");
}

void CCapAttachUDP::Reset()
{
	memset(m_bJudgeReq, 0x00, sizeof(BOOL) * 2 * 40 * 45);
	memset(m_dwReqStart, 0x00, sizeof(DWORD) * 2 * 40 * 45);
	memset(m_bJudgeDone, 0x00, sizeof(BOOL) * 2 * 40 * 45);
	memset(m_bBarcodeDone, 0x00, sizeof(BOOL) * 2 * 40 * 45);
}

void CCapAttachUDP::PortReset(int nPNo)
{
	memset(m_bJudgeReq[nPNo], 0x00, sizeof(BOOL) * 40 * 45);
	memset(m_dwReqStart[nPNo], 0x00, sizeof(DWORD) * 40 * 45);
	memset(m_bJudgeDone[nPNo], 0x00, sizeof(BOOL) * 40 * 45);
	memset(m_bBarcodeDone[nPNo], 0x00, sizeof(BOOL) * 2 * 40 * 45);
}

///////////////////////////////////////////////////////////////////////////////
// UDP Socket Message

LRESULT CCapAttachUDP::OnUdpReceive(WPARAM wLocalPort, LPARAM lParam)
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	CLogFile *pLogFile = CLogFile::Get_Instance();

	UINT nPort = (UINT)wLocalPort;
	BYTE byRecv[1024] = { 0 };
	CString strLog;

	int nLen = m_UdpCapAttach.Read_Socket(byRecv);

	if (nLen < 1) {
		strLog.Format("[H<-C] : Local Port (%d) Mismatch or Receive Data Zero (%d)", nPort, nLen);
		pLogFile->Save_CapAttachLog(strLog);
		return 0;
	}

	CString strRecvSocket;
	strRecvSocket.Format("%s", byRecv);
	m_strRecvCmd += strRecvSocket;

	while (!m_strRecvCmd.IsEmpty()) {
		int nStart = m_strRecvCmd.Find("@");
		int nEnd = m_strRecvCmd.Find("\n");

		if (nEnd < 0) break;	// 버퍼에 들어오는 중...

		if (nStart < 0 || nStart > nEnd) {
			strLog.Format("[H<-C] : <<Error>> %s : Start(%d), End(%d)", m_strRecvCmd, nStart, nEnd);
			pLogFile->Save_CapAttachLog(strLog);
			m_strRecvCmd.Delete(0, nEnd + 1);	// 쓰레기값이 채워져 있어서...
			continue;
		}

		CString strRecv = m_strRecvCmd.Mid(nStart + 1, nEnd - nStart - 1);
		m_strRecvCmd.Delete(0, nEnd + 1);

		if (!pEquipData->bUseInlineMode) return 0;

		char chSep = ',';
		CString strCmd, strOp;

		AfxExtractSubString(strCmd, strRecv, 0, chSep);
		AfxExtractSubString(strOp, strRecv, 1, chSep);

		// CapAttachUDP Log /////////////////////////////////////////////////////
		strLog.Format("[H<-C] : %s", strRecv);
		pLogFile->Save_CapAttachLog(strLog);
		///////////////////////////////////////////////////////////////////////

		CString strArg[8];
		for (int i = 0; i < 8; i++) AfxExtractSubString(strArg[i], strRecv, i + 2, chSep);

		if (strCmd == "CONNECT") {
			if (strOp == "REQUEST")	Get_ConnectRequest();
			else if (strOp == "REPLY") Get_ConnectReply();
			else if (strOp == "END") Get_ConnectEnd();

		} else if (strCmd == "STATUS") {
			if (strOp == "REQUEST")	Get_StatusRequest();
			else if (strOp == "REPLY") Get_StatusReply(strArg[0]);
			else if (strOp == "UPDATE") Get_StatusUpdate(strArg[0]);

		} else if (strCmd == "LOT") {
			if (strOp == "END") Get_LotEnd(strArg[0], strArg[1]);
			else if (strOp == "REPLY") Get_LotReply(strArg[0]);

		} else if (strCmd == "TRAY") {
			if (strOp == "UNLOAD") Get_TrayUnload();

		} else if (strCmd == "TEST") {
			if (strOp == "LOAD") Set_TestLoad();

		} else if (strCmd == "TIME") {
			if (strOp == "UPDATE") Get_TimeUpdate(strArg[0]);

		} else if (strCmd == "APD") {
			if (strOp == "REPLY") Get_APDReply(strArg[0]);
		} else if (strCmd == "BARCODE") {
			if (strOp == "REPLY") Get_BarcodeReply( strArg[0], strArg[1],strArg[2]);
		}
	}

	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// Get Command

void CCapAttachUDP::Get_ConnectRequest()
{
	m_bConnected = TRUE;
	Set_ConnectReply();
}

void CCapAttachUDP::Get_ConnectReply()
{
	m_bConnected = TRUE;
}

void CCapAttachUDP::Get_ConnectEnd()
{
	m_bConnected = FALSE;
}

void CCapAttachUDP::Get_StatusRequest()
{
	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
	BOOL bStatus = pSequenceMain->Get_ThreadMainRun();
	if (bStatus) Set_StatusReply(1);
	else Set_StatusReply(0);
}

void CCapAttachUDP::Get_StatusReply(CString sStatus)
{
	m_nStatusCapAttach = atoi(sStatus);
}

void CCapAttachUDP::Get_StatusUpdate(CString sStatus)
{
	m_nStatusCapAttach = atoi(sStatus);
}

void CCapAttachUDP::Get_LotReply(CString sPortNo)
{
// 	gData.nPortNo = atoi(sPortNo);
}

void CCapAttachUDP::Get_LotEnd(CString sLotID, CString sPortNo)
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	if (!pEquipData->bUseInlineMode) return;

	gData.bCapAttachWork = FALSE;
	//LotID, Port No
// 	int nLPNo = atoi(sPortNo) - 1;
// 	g_objMES.Set_LotEnd(gLot.sCALotID, gLot.nCACmCount, gData.sOperID, gLot.nCAGoodCount, gLot.nCANgCount);	

	//통합 Log 저장? Cap Lot ID도 전송 받아야 하나? 양식 보고 생각해보자.
// 	CString strLog;
// 	SYSTEMTIME time;
// 	GetLocalTime(&time);
// 	gLot.dwCALotEnd = GetTickCount();
// 	gLot.sCAEndTime.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
// 	DWORD dwTime = gLot.dwCALotEnd - gLot.dwCALotStart;
// 	double dTackTime = dwTime / 1000.0 / gLot.nCACmCount;	// Floating-point inexact result
// 
// 	CLogFile *pLogFile = CLogFile::Get_Instance();
// 	strLog.Format("%s,%s,%s,%d,%02d,%04d,%0.7lf,%d,%d",
// 		gLot.sCALotID, gLot.sCAStartTime, gLot.sCAEndTime, dwTime, gLot.nCATrayCount, gLot.nCACmCount, dTackTime, gLot.nCAGoodCount, gLot.nCANgCount);
// 	pLogFile->Save_JobListLog(strLog);

}

void CCapAttachUDP::Get_TimeUpdate(CString sTime)
{
	// sTime Format : "2000-01-01 12:30:30 000"
	CString strTemp;
	SYSTEMTIME time;

	strTemp = sTime.Mid(0, 4);  time.wYear = atoi(strTemp);			// Year
	strTemp = sTime.Mid(5, 2);  time.wMonth = atoi(strTemp);		// Month
	strTemp = sTime.Mid(8, 2);  time.wDay = atoi(strTemp);			// Day
	strTemp = sTime.Mid(11, 2); time.wHour = atoi(strTemp);			// Hour
	strTemp = sTime.Mid(14, 2); time.wMinute = atoi(strTemp);		// Minute
	strTemp = sTime.Mid(17, 2); time.wSecond = atoi(strTemp);		// Second
	strTemp = sTime.Mid(20, 3); time.wMilliseconds = atoi(strTemp);	// MilliSecond

	SetLocalTime(&time);
}

void CCapAttachUDP::Get_TrayUnload()
{
	gData.bCapTrayLoad = FALSE;
}

void CCapAttachUDP::Get_APDReply(CString sCapForceAvg)
{
	gData.dAssyLoadCellAvg = atof(sCapForceAvg);
}

void CCapAttachUDP::Get_BarcodeReply(CString sPortNo, CString sTrayNo, CString sCmNo)
{
	Set_BarcodeDone(atoi(sPortNo), atoi(sTrayNo), atoi(sCmNo), TRUE);
}

// Set Command

void CCapAttachUDP::Set_ConnectRequest()
{
	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	strSendCmd.Format("CONNECT,REQUEST,%s,%d", pEquipData->sCapAttachIp, UDP_CAPATTACH_LPORT);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_ConnectReply()
{
	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	strSendCmd.Format("CONNECT,REPLY,%s,%d", pEquipData->sCapAttachIp, UDP_CAPATTACH_LPORT);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_ConnectEnd()
{
	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	strSendCmd.Format("CONNECT,END,%s,%d", pEquipData->sCapAttachIp, UDP_CAPATTACH_LPORT);
	Send_Command(strSendCmd);
	m_bConnected = FALSE;
}

void CCapAttachUDP::Set_StatusRequest()
{
	m_nStatusCapAttach = 0;
	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	strSendCmd.Format("STATUS,REQUEST,%s,%d", pEquipData->sCapAttachIp, UDP_CAPATTACH_LPORT);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_StatusReply(int nStatus)
{
	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	strSendCmd.Format("STATUS,REPLY,%d,%s,%d", nStatus, pEquipData->sCapAttachIp, UDP_CAPATTACH_LPORT);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_StatusUpdate(int nStatus)
{
	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	strSendCmd.Format("STATUS,UPDATE,%d,%s,%d", nStatus, pEquipData->sCapAttachIp, UDP_CAPATTACH_LPORT);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_LotStart(int nPortNo)
{
	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	CString strLotId = gData.sLotID;
	int nTrayUseCnt = gData.nTrayJobCount;
	int nCmUseCnt = gData.nCMJobCount;
/*	gData.nPortNo = 0;*/

	strSendCmd.Format("LOT,START,%s,%d,%d,%d,%s,%d", strLotId, nPortNo, nTrayUseCnt, nCmUseCnt, gData.sRecipeName, 0);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_LotEnd(int nPortNo)
{
	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	CString strLotId = gData.sLotID;

	strSendCmd.Format("LOT,END,%s,%d", strLotId, nPortNo);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_ContinueLotInfo()
{
	CString	strSendCmd;

	strSendCmd.Format("LOT,INFO,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d", gData.sLotsID[0], gData.sLotsID[1], gData.sLotsID[2], gData.sLotsID[3], gData.sLotsID[4],
																gData.nCmsUseCnt[0], gData.nCmsUseCnt[1], gData.nCmsUseCnt[2], gData.nCmsUseCnt[3], gData.nCmsUseCnt[4]);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_TrayLoad(int nPortNo)
{
	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	CString strLotId = gData.sLotID;
	int nTrayCnt = gData.nGoodTrayCount;
	int nCmUseCnt = gData.nCTrayCmCnt;
	int nLotIndex = gData.nCUnloadLotIndex;

	strSendCmd.Format("TRAY,LOAD,%s,%d,%d,%d", strLotId, nTrayCnt, nCmUseCnt, nPortNo, nLotIndex);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_TrayEnd(int nPortNo)
{
	CString	strSendCmd;
	int nTrayCnt = gData.nGoodTrayCount;

	strSendCmd.Format("TRAY,END,%d,%d", nTrayCnt, nPortNo);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_BarcodeUpdate(int nPortNo, int nTrayNo, int nCmNo, CString sBarcode)
{
	CString	strSendCmd;
	strSendCmd.Format("BARCODE,UPDATE,%d,%d,%d,%s", nPortNo, nTrayNo, nCmNo, sBarcode);
	Send_Command(strSendCmd);

	Set_BarcodeDone(nPortNo, nTrayNo, nCmNo, FALSE);

// 	CLogFile *pLogFile = CLogFile::Get_Instance();
// 	CString strLog;
// 	strLog.Format("[H->C] : %s", strSendCmd);
// 	pLogFile->Save_CapAttachLog(strLog);
}

void CCapAttachUDP::Set_APDRequest()
{
	CString	strSendCmd;
	gData.dAssyLoadCellAvg = -1.0;
	strSendCmd.Format("APD,REQUEST");
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_TestLoad()
{
	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	CString strLotId = "TEST_AVI";
	int nTrayCnt = 1;
	int nCmUseCnt = 15;

	strSendCmd.Format("LOT,START,%s,%d,%d,%d,%s", strLotId, 1, 1, nCmUseCnt, gData.sRecipeName);
	Send_Command(strSendCmd);

	Sleep(100);

	strSendCmd.Format("LOT,END,%s,%d", strLotId, 1);
	Send_Command(strSendCmd);
	
	Sleep(100);

	strSendCmd.Format("TRAY,LOAD,%s,%d,%d,%d", strLotId, nTrayCnt, nCmUseCnt, 1);
	Send_Command(strSendCmd);
}

void CCapAttachUDP::Set_TimeUpdate()
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strTime;
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d %03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	CString	strSendCmd;
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	strSendCmd.Format("TIME,UPDATE,%s,%s,%d", strTime, pEquipData->sCapAttachIp, UDP_CAPATTACH_LPORT);
	Send_Command(strSendCmd);
}

/////////////////////////////////////////////////////////////////////////////
// UDP Socket Send Message

void CCapAttachUDP::Send_Command(CString strSend)
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	if (!pEquipData->bUseInlineMode) return;

	CString strLog;
	strLog.Format("[H->C] : %s", strSend);
	pLogFile->Save_CapAttachLog(strLog);

	CString strSendSocket;
	strSendSocket.Format("@%s\n", strSend);

	char chSend[1024] = { 0 };
	int nLength = strSendSocket.GetLength();
	memcpy(chSend, (LPSTR)(LPCSTR)strSendSocket, nLength);

	g_csCapAttachUDP.Lock();	// Critical Section

	m_UdpCapAttach.Write_Socket((BYTE*)chSend, nLength);

	g_csCapAttachUDP.Unlock();	// Critical Section
}

/////////////////////////////////////////////////////////////////////////////

void CCapAttachUDP::Test_Command(int nNo)
{
}
