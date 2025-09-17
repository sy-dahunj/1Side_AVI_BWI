// Inspector.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "Inspector.h"

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

#include "CMI4200LDlg.h"
#include "WorkDlg.h"
#include "ManualDlg.h"
#include "SequenceMain.h"
#include "LogFile.h"
#include "MESInterface.h"

#define UDP_VISION_IP		"192.168.1.12"
//#define UDP_VISION_IP		"127.0.0.1"
#define UDP_VISION_PORT		20000

IMPLEMENT_DYNAMIC(CInspector, CWnd)

CInspector *CInspector::m_pInstance = NULL;

CCriticalSection g_csInspector;
CCriticalSection g_csLightTrigger;

CInspector *CInspector::Get_Instance()
{
	if (!m_pInstance) {
		m_pInstance = new CInspector();
		if (!m_pInstance->m_hWnd) {
			CRect r = m_pInstance->Get_Position();
			m_pInstance->CreateEx(0, AfxRegisterWndClass(0), "CInspector", 0, r, NULL, 0, NULL);
		}
	}
	return m_pInstance;
}

void CInspector::Delete_Instance()
{
	if (m_pInstance->m_hWnd) m_pInstance->DestroyWindow();
	if (m_pInstance) delete m_pInstance;
	m_pInstance = NULL;
}

// CInspector

CInspector::CInspector()
{
	Set_Position(0, 0, 0, 0);

	m_bConnectedVision = FALSE;
	m_nStatusRequestLoop = 0;
	m_nStatusVision = -1;		// Mold Inspector PC 상태 (0:Not Ready, 1:Ready)
}

CInspector::~CInspector()
{
}

BEGIN_MESSAGE_MAP(CInspector, CWnd)
	ON_MESSAGE(UM_UDP_RECEIVE, OnUdpReceive)
END_MESSAGE_MAP()

// CInspector 메시지 처리기입니다.

void CInspector::Initialize_Inspector()
{

	BOOL bVisionOpened;
#if AJIN_BOARD_USE
	bVisionOpened = m_UdpVision.Open_Socket(UDP_VISION_PORT, UDP_VISION_PORT, UDP_VISION_IP, this);
#else
	bVisionOpened = m_UdpVision.Open_Socket(9000, 9001, "127.0.0.1", this);
#endif

	
	//TEST=> BOOL bVisionOpened = m_UdpVision.Open_Socket(8000, 8001, UDP_VISION_IP, this);
	if (bVisionOpened) Set_ConnectRequest(INSPECTOR_VISION);
}

void CInspector::Terminate_Inspector()
{
	Set_ConnectEnd(INSPECTOR_VISION);
	m_UdpVision.Close_Socket();
}

///////////////////////////////////////////////////////////////////////////////
// UDP Socket Message

LRESULT CInspector::OnUdpReceive(WPARAM nPort, LPARAM lParam)
{
	int nInspectPC = 0;

	nInspectPC = INSPECTOR_VISION;
	BYTE byRecv[2048] = { 0 };
	int nLen = m_UdpVision.Read_Socket(byRecv);

	CString strRecvSocket;
	strRecvSocket.Format("%s", byRecv);

	int nLoopMax = 3;
	while (!strRecvSocket.IsEmpty() && nLoopMax > 0) {
		int nStart = strRecvSocket.Find("@");
		int nEnd = strRecvSocket.Find("\n");

		if (nStart > nEnd) return 0;

		CString strRecv = strRecvSocket.Mid(nStart + 1, nEnd - nStart - 1);
		strRecvSocket.Delete(0, nEnd + 1);

		// Inspector Log //////////////////////////////////////
		CString strLog;
		CLogFile *pLogFile = CLogFile::Get_Instance();
		strLog.Format("[H<-V%d],%s", nInspectPC, strRecv);
		pLogFile->Save_InspectorLog(strLog);
		///////////////////////////////////////////////////////

		CDataManager *pDataManager = CDataManager::Get_Instance();
		EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
		if (!pEquipData->bUseVisionInspect) return 0;

		char chSep = ',';
		CString strCmd, strOp;

		AfxExtractSubString(strCmd, strRecv, 0, chSep);
		AfxExtractSubString(strOp, strRecv, 1, chSep);

		if (strCmd == "CONNECT") {
			if (strOp == "REQUEST")	Get_ConnectRequest(nInspectPC);
			else if (strOp == "REPLY") Get_ConnectReply(nInspectPC);
			else if (strOp == "END") Get_ConnectEnd(nInspectPC);

		} else if (strCmd == "STATUS") {
			CString strStatus;
			AfxExtractSubString(strStatus, strRecv, 2, chSep);
			if (strOp == "REQUEST")	Get_StatusRequest(nInspectPC);
			else if (strOp == "REPLY") Get_StatusReply(nInspectPC, strStatus);
			else if (strOp == "UPDATE") Get_StatusUpdate(nInspectPC, strStatus);

		} else if (strCmd == "MODEL") {
			CString strFlag;
			AfxExtractSubString(strFlag, strRecv, 2, chSep);
			if (strOp == "REPLY") Get_ModelReply(nInspectPC, strFlag);

		} else if (strCmd == "LOT") {
			if (strOp == "REPLY") Get_LotReply(nInspectPC);
			if (strOp == "RESULT") Get_LotResult(nInspectPC, strRecv);

		} else if (strCmd == "LOAD") {
			if (strOp == "REPLY") Get_LoadReply(nInspectPC);

		} else if (strCmd == "SCAN") {
			CString strDir, strSpeed, strThickZ, strStartX;
			AfxExtractSubString(strDir, strRecv, 2, chSep);
			AfxExtractSubString(strSpeed, strRecv, 3, chSep);
			AfxExtractSubString(strThickZ, strRecv, 4, chSep);
			AfxExtractSubString(strStartX, strRecv, 5, chSep);
			
			if (strOp == "REQUEST") Get_ScanRequest(nInspectPC, strDir, strSpeed, strThickZ, strStartX);
			else if (strOp == "COMPLETE") Get_ScanComplete(nInspectPC, strDir, strSpeed, strThickZ, strStartX);
			else if (strOp == "REPLY") Get_ScanReply(nInspectPC);

		} else if (strCmd == "INSPECT") {
			CString strTemp;
			AfxExtractSubString(strTemp, strRecv, 2, chSep);
			if (strOp == "COMPLETE") Get_InspectComplete(nInspectPC, strRecv);
			if (strOp == "RESULT") Get_InspectResult(nInspectPC, strTemp);		// strTemp -> ResultFile (Merge PC)

		} else if (strCmd == "POSITION") {
			CString strGgn;
			AfxExtractSubString(strGgn, strRecv, 2, chSep);
			if (strOp == "REQUEST") Get_PositionRequest(nInspectPC, strGgn);

		} else if (strCmd == "AMOVE") {
			CString strX, strY, strZ, strGgn;
			AfxExtractSubString(strX, strRecv, 2, chSep);
			AfxExtractSubString(strY, strRecv, 3, chSep);
			AfxExtractSubString(strZ, strRecv, 4, chSep);
			AfxExtractSubString(strGgn, strRecv, 5, chSep);
			if (strOp == "REQUEST") Get_AMoveRequest(nInspectPC, strX, strY, strZ, strGgn);

		} else if (strCmd == "RMOVE") {
			CString strX, strY, strZ, strGgn;
			AfxExtractSubString(strX, strRecv, 2, chSep);
			AfxExtractSubString(strY, strRecv, 3, chSep);
			AfxExtractSubString(strZ, strRecv, 4, chSep);
			AfxExtractSubString(strGgn, strRecv, 5, chSep);
			if (strOp == "REQUEST") Get_RMoveRequest(nInspectPC, strX, strY, strZ, strGgn);

		} else if (strCmd == "ZMOVE") {
			CString strZ;
			AfxExtractSubString(strZ, strRecv, 2, chSep);
			if (strOp == "REQUEST") Get_ZMoveRequest(nInspectPC, strZ);

		} else if (strCmd == "TRIGGER") {
			CString strL1, strL2, strL3, strL4, strL5,  strL6, strL7, strL8, sType;
			AfxExtractSubString(sType, strRecv, 2, chSep);
			AfxExtractSubString(strL1, strRecv, 3, chSep);
			AfxExtractSubString(strL2, strRecv, 4, chSep);
			AfxExtractSubString(strL3, strRecv, 5, chSep);
			AfxExtractSubString(strL4, strRecv, 6, chSep);
			AfxExtractSubString(strL5, strRecv, 7, chSep);
			AfxExtractSubString(strL6, strRecv, 8, chSep);
			AfxExtractSubString(strL7, strRecv, 9, chSep);
			AfxExtractSubString(strL8, strRecv, 10, chSep);
			if (strOp == "REQUEST") Get_TriggerRequest(nInspectPC, strL1, strL2, strL3, strL4, strL5, strL6, strL7, strL8, sType);

		} else if (strCmd == "MOVE") {
			if (strOp == "REPLY") Get_MoveReply(nInspectPC);

		} else if (strCmd == "ERROR") {
			CString strMsg;
			AfxExtractSubString(strMsg, strRecv, 2, chSep);
			Get_ErrorPost(nInspectPC, strOp, strMsg);
			
		} else if (strCmd == "ALARM") {
			CString sGbn, sLotId, sErrNo, sInfo1, sInfo2, sInfo3;
			AfxExtractSubString(sGbn, strRecv, 2, chSep);
			AfxExtractSubString(sLotId, strRecv, 3, chSep);
			AfxExtractSubString(sErrNo, strRecv, 4, chSep);
			AfxExtractSubString(sInfo1, strRecv, 5, chSep);
			AfxExtractSubString(sInfo2, strRecv, 6, chSep);
			AfxExtractSubString(sInfo3, strRecv, 7, chSep);
			if (strOp == "REQUEST") { Get_AlarmRequest(nInspectPC, sGbn, sLotId, sErrNo, sInfo1, sInfo2, sInfo3); }	// 다발 불량, Barcode Shift 불량

		} else if (strCmd == "FOB") {
			CString sStatus;
			AfxExtractSubString(sStatus, strRecv, 2, chSep);
			if (strOp == "UPDATE")		{ Get_FOBUpdate(nInspectPC, sStatus); }	// Vision FOB 설정 변경시.
			else if (strOp == "REPLY")	{ Get_FOBReply(nInspectPC, sStatus); }	// Handler에서 FOB 상태 요청했을때.

		} else if (strCmd == "RECIPE") {
			CString strRecipe;
			AfxExtractSubString(strRecipe, strRecv, 2, chSep);
			if (strOp == "CHANGED") Get_RecipeChanged(nInspectPC, strRecipe);

		} else if (strCmd == "PMS") {
			CString strBarcode, strOrign, strMap;
			if (strOp == "UPLOAD") {			// Mold PC에서 받음 -> Pcb 에서도 받음
				AfxExtractSubString(strBarcode, strRecv, 2, chSep);
				AfxExtractSubString(strOrign, strRecv, 3, chSep);
				Get_PmsUpload(nInspectPC, strBarcode, strOrign);

			} else if (strOp == "RESULT") {		// 통합환경 PC에서 받음
				AfxExtractSubString(strBarcode, strRecv, 2, chSep);
				AfxExtractSubString(strMap, strRecv, 3, chSep);
				Get_PmsResult(nInspectPC, strBarcode, strMap);
			}

		} else if (strCmd == "STRIP") {
			if (strOp == "REPLY") Get_StripReply(nInspectPC);

		} else if (strCmd == "ADRDATA") {
			if (strOp == "COPY") Get_AdrDataCopy(nInspectPC);

		} else if (strCmd == "CAL") {
			CString strDir, strSpeed, strStartX;
			AfxExtractSubString(strDir, strRecv, 2, chSep);
			AfxExtractSubString(strSpeed, strRecv, 3, chSep);
			AfxExtractSubString(strStartX, strRecv, 4, chSep);
			if (strOp == "REQUEST") Get_CalRequest(nInspectPC, strDir, strSpeed, strStartX);
			else if (strOp == "REPLY") Get_CalReply(nInspectPC);	

		} else if (strCmd == "ELECT") {
			if (strOp == "REPLY") Get_ElectReply(nInspectPC);

		} else if (strCmd == "WARP") {
			if (strOp == "REPLY") Get_WarpReply(nInspectPC);

		} else if (strCmd == "MTHICK") {
			CString strLotId, strStripId, strValue[5];
			AfxExtractSubString(strLotId, strRecv, 2, chSep);
			AfxExtractSubString(strStripId, strRecv, 3, chSep);
			for (int i = 0; i < 5; i++) AfxExtractSubString(strValue[i], strRecv, 4+i, chSep);
			if (strOp == "COMPLETE") Get_MThickComplete(nInspectPC, strLotId, strStripId, strValue);

		} else if (strCmd == "CORRECT") {
			CString strX, strY, strZ;
			AfxExtractSubString(strX, strRecv, 2, chSep);
			AfxExtractSubString(strY, strRecv, 3, chSep);
			AfxExtractSubString(strZ, strRecv, 4, chSep);
			if (strOp == "COMPLETE") Get_CorrectComplete(nInspectPC, strX, strY, strZ);

		} else if (strCmd == "TIME") {
			if (strOp == "REPLY") Get_TimeReply(nInspectPC);

		} else if (strCmd == "APD") {
			if (strOp == "REPLY")	Get_APDReply(nInspectPC, strRecv);

		}
		nLoopMax--;
	}
	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// Get Command

void CInspector::Get_ConnectRequest(int nInspector)
{
	m_bConnectedVision = TRUE;
	Set_ConnectReply(nInspector);
}

void CInspector::Get_ConnectReply(int nInspector)
{
	m_bConnectedVision = TRUE;
}

void CInspector::Get_ConnectEnd(int nInspector)
{
	m_bConnectedVision = FALSE;
}

void CInspector::Get_StatusRequest(int nInspector)
{
	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
	BOOL bStatus = pSequenceMain->Get_ThreadMainRun();
	if (bStatus) Set_StatusReply(nInspector, 1);
	else Set_StatusReply(nInspector, 0);
}

void CInspector::Get_StatusReply(int nInspector, CString sStatus)
{
	m_nStatusVision = atoi(sStatus);
}

void CInspector::Get_StatusUpdate(int nInspector, CString sStatus)
{
	m_nStatusVision = atoi(sStatus);
}

void CInspector::Get_ModelReply(int nInspector, CString sFlag)
{
	if (sFlag == "0") {
		// OK
	} else {
		// NG
	}
}

void CInspector::Get_LotReply(int nInspector)
{
	//
}

void CInspector::Get_LotResult(int nInspector, CString strRecv)
{
	//char chSep = ',';
	//CString sData, sData1, sData2, strLog;

	//CLogFile *pLogFile = CLogFile::Get_Instance();

	//AfxExtractSubString(sData, strRecv, 2, chSep);	//NG수량
	//gData.nNGTotCnt = atoi(sData);

	//AfxExtractSubString(sData, strRecv, 3, chSep);	//NG item 수
	//gData.nRstCnt = atoi(sData);

	//if (gData.nRstCnt < 1 || gData.nRstCnt > 20) {
	//	strLog.Format("[H<-V%d] Error: TCnt[%d] NGCnt[%d]", nInspector, gData.nNGTotCnt, gData.nRstCnt);
	//	pLogFile->Save_InspectorLog(strLog);
	//	return;
	//}

	//for(int i=0; i<gData.nRstCnt; i++) {
	//	AfxExtractSubString(sData1, strRecv, 4+(i*2), chSep);	//NG Name
	//	AfxExtractSubString(sData2, strRecv, 5+(i*2), chSep);	//NG Count

	//	gData.sRstItem[i] = sData1;
	//	gData.nNGCnt[i] = atoi(sData2);
	//}

	//long lTNGCnt;
	//CIniFileCS Ini_LotData("System/LotData.ini");
	//lTNGCnt = Ini_LotData.Get_Long("TOTAL_DATA", "TOTAL_NG", 0);
	//lTNGCnt = lTNGCnt + gData.nNGTotCnt;
	//Ini_LotData.Set_Long("TOTAL_DATA", "TOTAL_NG", lTNGCnt);

	//pLogFile->Save_LotLog("LotResult");	//Lot log처리
}

void CInspector::Get_LoadReply(int nInspector)
{
	//
}

void CInspector::Get_ScanComplete(int nInspector, CString sLotID, CString sTrayNo, CString sTRNo, CString sGbn)
{
	int	nTrayNo = atoi(sTrayNo);
	int	nLineNo = atoi(sTRNo);

	if ((nTrayNo < 1 || nLineNo < 1) ||
		(sGbn != "I" && sGbn != "B") ) {
		Set_ScanReply(nInspector, 0);
		return;
	}

	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
	if (sGbn == "B") {
		int nBarcodeCase = pSequenceMain->Get_RunCase(AUTO_BARCODE);
		
		if (nBarcodeCase < 150 || nBarcodeCase > 200) {
			Set_ScanReply(nInspector, 0);
			return;
		}
		pSequenceMain->Set_RunCase(AUTO_BARCODE, 200);

	} else {
		int nVisionCase = pSequenceMain->Get_RunCase(AUTO_INSPECT);

		if (nVisionCase < 150 || nVisionCase > 200) {
			Set_ScanReply(nInspector, 0);
			return;
		}
		pSequenceMain->Set_RunCase(AUTO_INSPECT, 200);
	}

	Set_ScanReply(nInspector, 1);
}

void CInspector::Get_ScanRequest(int nInspector, CString sDir, CString sSpeed, CString sThickZ, CString sStartX)
{
	int nDir = atoi(sDir);
	double dSpeed = atof(sSpeed);
	double dThickZ = atof(sThickZ);
	double dStartX = atof(sStartX);
	int nNG = 0;

//	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
//	pSequenceMain->Set_SensStripID(0);

	if (dThickZ >= 0.0 && dThickZ < 9.0) {
		CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
		CManualDlg *pManualDlg = CManualDlg::Get_Instance();
		
		if (pWorkDlg->IsWindowVisible()) {									// AutoRun
			CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
			
//			int nMoldCase = pSequenceMain->Get_RunCase(AUTO_INSP_GQFN);
//			if (nMoldCase == 110 && dStartX > 0.0) pSequenceMain->Set_MoldScan(nDir, dSpeed, dThickZ, dStartX);
//			else nNG = 1;

		} else if (pManualDlg->m_pManualUnloadTrayDlg->IsWindowVisible()) {	// Manual

			//int n3dCase = pManualDlg->m_pManualInspectorDlg->Get_3dRunCase();
			//if (n3dCase == 0 && dStartX >= 0.0) 
			//	pManualDlg->m_pManualInspectorDlg->Set_3dScan(nDir, dSpeed, dThickZ, dStartX, SCAN_INSPECT);
			//else nNG = 1;

		} else nNG = 1;
	} else nNG = 1;

/*
		} else if (pManualDlg->m_pManualInspectorDlg->IsWindowVisible()) {	// Manual
			if (nInspector == INSPECTOR_MOLD) {
				int nMoldCase = pManualDlg->m_pManualInspectorDlg->Get_MoldRunCase();
				if (nMoldCase == 0) pManualDlg->m_pManualInspectorDlg->Set_MoldScan(nDir, dSpeed, dThickZ, 0.0, SCAN_INSPECT);
				else nNG = 1;
			} else if (nInspector == INSPECTOR_PCB) {
				int nPcbCase = pManualDlg->m_pManualInspectorDlg->Get_PcbRunCase();
				if (nPcbCase == 0) pManualDlg->m_pManualInspectorDlg->Set_PcbScan(nDir, dSpeed, dThickZ,  SCAN_INSPECT);
				else nNG = 1;
			} else if (nInspector == INSPECTOR_3D) {
				int n3dCase = pManualDlg->m_pManualInspectorDlg->Get_3dRunCase();
				if (n3dCase == 0 && dStartX >= 0.0) 
					pManualDlg->m_pManualInspectorDlg->Set_3dScan(nDir, dSpeed, dThickZ, dStartX, SCAN_INSPECT);
				else nNG = 1;
			} else nNG = 1;
		} else nNG = 1;
	} else nNG = 1;
*/

	Set_ScanReply(nInspector, nNG);
}

void CInspector::Get_ScanReply(int nInspector)
{
	//
}

void CInspector::Get_InspectComplete(int nInspector, CString strRecv)
{
	int		nTrayNo, nLineNo, nCount, nErr, x, cm;
	CString sTrayNo, sLineNo, sCount, sData[10], sBarcode[10], strLog, sCMData, sNGcode[10], sNGText[10];
	CString sDiameter[10], sCenterX[10], sCenterY[10], sO1O2Dist[10], sDiameterMin[10];
	char chSep = ',';

	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	CCommon *pCommon = CCommon::Get_Instance();

	//INSPECT,COMPLETE,GUY555AG6G01,1,1,5,G,G,G,G,G,NO_READ,NO_READ,NO_READ,NO_READ,NO_READ,NO_READ (B:Barcode shift NG)
	//INSPECT,COMPLETE,GUY555AG6G03,16,4,5,G,G,G,G,E,NO_READ,NO_READ,NO_READ,NO_READ,NO_READ,NO_READ
	AfxExtractSubString(sTrayNo, strRecv, 3, chSep);
	AfxExtractSubString(sLineNo, strRecv, 4, chSep);
	AfxExtractSubString(sCount, strRecv, 5, chSep);
	nTrayNo = atoi(sTrayNo);
	nLineNo = atoi(sLineNo);
	nCount = atoi(sCount);

#ifdef PICKER_3
	for(int i=0; i<3; i++) {
		AfxExtractSubString(sData[i],    strRecv, i+6,  chSep);
		AfxExtractSubString(sBarcode[i], strRecv, i+9, chSep);
		AfxExtractSubString(sNGcode[i], strRecv, i+12, chSep);
		AfxExtractSubString(sNGText[i], strRecv, i+15, chSep);

		//SBC 관련 측정값
		AfxExtractSubString(sDiameter[i],   strRecv, i+18, chSep);
		AfxExtractSubString(sCenterX[i],    strRecv, i+21, chSep);
		AfxExtractSubString(sCenterY[i],    strRecv, i+24, chSep);
		AfxExtractSubString(sO1O2Dist[i],   strRecv, i+27, chSep);
		AfxExtractSubString(sDiameterMin[i], strRecv, i+30, chSep);
	}
#endif
#ifdef PICKER_4
	for(int i=0; i<4; i++) {
		AfxExtractSubString(sData[i],    strRecv, i+6,  chSep);
		AfxExtractSubString(sBarcode[i], strRecv, i+10, chSep);
		AfxExtractSubString(sNGcode[i], strRecv, i+14, chSep);
		AfxExtractSubString(sNGText[i], strRecv, i+28, chSep);

		//SBC 관련 측정값
		AfxExtractSubString(sDiameter[i],   strRecv, i+26, chSep);
		AfxExtractSubString(sCenterX[i],    strRecv, i+31, chSep);
		AfxExtractSubString(sCenterY[i],    strRecv, i+36, chSep);
		AfxExtractSubString(sO1O2Dist[i],   strRecv, i+41, chSep);
		AfxExtractSubString(sDiameterMin[i], strRecv, i+46, chSep);
	}
#endif

#ifdef PICKER_5
	for(int i=0; i<5; i++) {
		AfxExtractSubString(sData[i],    strRecv, i+6,  chSep);
		AfxExtractSubString(sBarcode[i], strRecv, i+11, chSep);
		AfxExtractSubString(sNGcode[i], strRecv, i+16, chSep);
		AfxExtractSubString(sNGText[i], strRecv, i+21, chSep);

		//SBC 관련 측정값
		AfxExtractSubString(sDiameter[i],   strRecv, i+26, chSep);
		AfxExtractSubString(sCenterX[i],    strRecv, i+31, chSep);
		AfxExtractSubString(sCenterY[i],    strRecv, i+36, chSep);
		AfxExtractSubString(sO1O2Dist[i],   strRecv, i+41, chSep);
		AfxExtractSubString(sDiameterMin[i], strRecv, i+46, chSep);
	}
#endif
#ifdef PICKER_6
	for(int i=0; i<6; i++) {
		AfxExtractSubString(sData[i],    strRecv, i+6,  chSep);
		AfxExtractSubString(sBarcode[i], strRecv, i+12, chSep);
		AfxExtractSubString(sNGcode[i], strRecv, i+18, chSep);
		AfxExtractSubString(sNGText[i], strRecv, i+24, chSep);

		//SBC 관련 측정값
		AfxExtractSubString(sDiameter[i],   strRecv, i+30, chSep);
		AfxExtractSubString(sCenterX[i],    strRecv, i+36, chSep);
		AfxExtractSubString(sCenterY[i],    strRecv, i+42, chSep);
		AfxExtractSubString(sO1O2Dist[i],   strRecv, i+48, chSep);
		AfxExtractSubString(sDiameterMin[i], strRecv, i+54, chSep);
	}
#endif

	nErr = x = 0;	//검사결과 error check
	if      (nTrayNo == gData.IDXTrayNo[1][0] && nLineNo == gData.IDXLineNo[1]) x=1;
	else if (nTrayNo == gData.IDXTrayNo[2][0] && nLineNo == gData.IDXLineNo[2]) x=2;
	else																	nErr=9;

	cm = (nLineNo - 1) * gData.nPickCnt;
	if (nTrayNo<1 || nTrayNo >TRAY_MAX_CNT ||
		nLineNo<1 || nLineNo >gData.nArrayW) {
		pCommon->Show_Error(4300);

		CLogFile *pLogFile = CLogFile::Get_Instance();
		strLog.Format("[4300 Alarm] ==> ,Tray_No,%d,Line_No,%d,Cm_No,%d,Result,%d", nTrayNo,nLineNo,cm+1,nErr);
		pLogFile->Save_HandlerLog(strLog);
		return;
	}

	int nJugdeNo;
	for(int i=0; i<gData.nPickCnt; i++) 
	{
		if (pEquipData->bUseContinueLot) {
			if (gData.IndexInfo[x][i] > 0) { gData.IndexInfo[x][i] = 1; gLot.nGoodCnt++; }

		} else {
			if		(sData[i] == "G") { nJugdeNo = 1; gLot.nGoodCnt++;	}	//Good
			else if (sData[i] == "N") { nJugdeNo = 2; }					//NG
			else if (sData[i] == "M") { nJugdeNo = 4; }					//MES Check:NG
			else if (sData[i] == "B") { nJugdeNo = 5; }					//Barcode shift
			else if (sData[i] == "A") { nJugdeNo = 7; }					//Barrel Lens
			else if (sData[i] == "S") { nJugdeNo = 8; }					//Side Fill	(R12A)
			else if (sData[i] == "T") { nJugdeNo = 11;}					//Stiffener 측정 (R12C)
			else if (sData[i] == "R") { nJugdeNo = 12;}					//Lens 원자재 (R13B)
			else if (sData[i] == "F") { nJugdeNo = 13;}					//Lens Fiducial Notch Broken (F24)
			else if (sData[i] == "H") { nJugdeNo = 14;}					//Shiny Edge (F24)
			else if (sData[i] == "E") { nJugdeNo = 3;}					//Empty
			else					  { nJugdeNo = 2;}

			if		(nJugdeNo == 1) g_objMES.Set_Result(gLot.sLotID, sBarcode[i], "OK", sNGcode[i], sNGText[i], nTrayNo, (cm+i+1), 0,0,0,0);
			else if (nJugdeNo != 3) g_objMES.Set_Result(gLot.sLotID, sBarcode[i], "NG", sNGcode[i], sNGText[i], nTrayNo, (cm+i+1), 0,0,0,0);
		}
		gLot.nInsResult[nTrayNo-1][cm+i] = gLot.nBarResult[nTrayNo-1][cm+i] = nJugdeNo;
		gLot.sBarLoad[nTrayNo-1][cm+i] = sBarcode[i];
		if(sBarcode[i] =="NOREAD")
		{
			gLot.nNGCnt++;
		}


		gLot.sNGCode[nTrayNo-1][cm+i] = sNGcode[i];
		gLot.sNGText[nTrayNo-1][cm+i] = sNGText[i];
		gData.IDXPoNo[x][i] = cm+i+1;	//Pocket No Set
	}
	gData.nInsTrayNo = nTrayNo;
	gData.nInsLineNo = nLineNo;
	gData.IDXInspec[x] = 1;
	Set_InspectReply(nInspector, nErr);

	for (int i=0; i<gData.nPickCnt; i++) {	// SBC 불량 발생 Log 
		if (atoi(sNGcode[i]) == 16) {
			CLogFile *pLogFile = CLogFile::Get_Instance();
			strLog.Format("Tray_No,%d,Line_No,%d,Index,%d,Barcode,%s,Diameter,%s,CenterX,%s,CenterY,%s,O1O2Dist,%s,DiameterMin,%s", 
				nTrayNo, nLineNo, cm+i+1, sBarcode[i], sDiameter[i], sCenterX[i], sCenterY[i], sO1O2Dist[i], sDiameterMin[i]);
			pLogFile->Save_SBCNgLog(strLog);
		}
	}

	for(int i=0; i<gData.nPickCnt; i++) {
		if (gLot.nInsResult[nTrayNo-1][cm+i] == 2) {
			if (gLot.sBarLoad[nTrayNo-1][cm+i].GetLength() < 10) {
				if (gLot.sBarLoad[nTrayNo-1][cm+i] == "NO_GRAB")
					gLot.nBarResult[nTrayNo-1][cm+i] = 6;
				else
					gLot.nBarResult[nTrayNo-1][cm+i] = 5;
			} else {
				gLot.nBarResult[nTrayNo-1][cm+i] = 1;
			}
		}
	}

	if(gData.bUseBar2Alarm) {
		for(int i=0; i<gData.nPickCnt; i++) {
			if (gLot.nBarResult[nTrayNo-1][cm+i] == 5 || gLot.nBarResult[nTrayNo-1][cm+i] == 6) {
				if (gLot.nBarResult[nTrayNo-1][cm+i] == 5) pCommon->Show_Error(9901);
				if (gLot.nBarResult[nTrayNo-1][cm+i] == 6) pCommon->Show_Error(9902);

				CLogFile *pLogFile = CLogFile::Get_Instance();
				strLog.Format("[2D Barcode Alarm] ==> ,Tray_No,%d,Line_No,%d,Index,%d,Result,%d,Barcode,%s", nTrayNo,nLineNo,i+1,gLot.nInsResult[nTrayNo-1][cm+i],gLot.sBarLoad[nTrayNo-1][cm+i]);
				pLogFile->Save_HandlerLog(strLog);

				return;
			}
		}
	}
}
/*
BOOL CInspector::Check_HostResult(CString sBarcode)
{
	CString strLog;
	if (sBarcode.GetLength() < 10) return TRUE;

	//0:Barcode ID, 1:FUNC(기능검사), 2:MIX(조건검사), 3:VERSION(검사SW버전검사), 4:WEEK(바코드생성 주차검사), 5:FINAL(최종검사)
	for(int i=0; i<gCM.nLCount; i++ ) {
		if (gCM.sLData[i][0] == sBarcode) {
			if (gCM.sLData[i][4] == "OK" && gCM.sLData[i][5] == "OK") {
				return TRUE;
			} else {
				strLog.Format("LOT Result ==> MESNG.....Barcode[%s] FUNC[%s] MIX[%s] VERSION[%s] WEEK[%s] FINAL[%s]",
					gCM.sLData[i][0], gCM.sLData[i][1], gCM.sLData[i][2], gCM.sLData[i][3], gCM.sLData[i][4], gCM.sLData[i][5]);
				CLogFile *pLogFile = CLogFile::Get_Instance();
				pLogFile->Save_HandlerLog(strLog);
				return FALSE;
			}
		}
	}
	for(int i=0; i<gCM.nMCount; i++ ) {
		if (gCM.sMData[i][0] == sBarcode) {
			if (gCM.sMData[i][4] == "OK" && gCM.sMData[i][5] == "OK") {
				return TRUE;
			} else {
				strLog.Format("CM Result ==> MESNG.....Barcode[%s] FUNC[%s] MIX[%s] VERSION[%s] WEEK[%s] FINAL[%s]",
					gCM.sMData[i][0], gCM.sMData[i][1], gCM.sMData[i][2], gCM.sMData[i][3], gCM.sMData[i][4], gCM.sMData[i][5]);
				CLogFile *pLogFile = CLogFile::Get_Instance();
				pLogFile->Save_HandlerLog(strLog);
				return FALSE;
			}
		}
	}

	strLog.Format("LOT Result ==> MESNG.....Barcode[%s] LOT Data Not Found Error", sBarcode);
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog(strLog);

	return FALSE;
}

BOOL CInspector::Check_CMExist(CString sBarcode)
{
	if (sBarcode.GetLength() < 10) return TRUE;

	//0:Barcode ID, 1:FUNC(기능검사), 2:MIX(조건검사), 3:VERSION(검사SW버전검사), 4:WEEK(바코드생성 주차검사), 5:FINAL(최종검사)
	for(int i=0; i<gCM.nLCount; i++ ) {
		if (gCM.sLData[i][0] == sBarcode) return TRUE;
	}
	return FALSE;
}
*/
void CInspector::Get_InspectResult(int nInspector, CString sResultFile)
{
}

void CInspector::Get_PositionRequest(int nInspector, CString sGbn)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	double dX, dZ;
	if (sGbn=="B") {
		AXIS_STATUS *pStatusX = pAJinAXL->Get_pStatus(AX_BARCODE_A); dX = pStatusX->dPos;
		dZ = 0;
	} else {
		AXIS_STATUS *pStatusY = pAJinAXL->Get_pStatus(AX_INSPECTION_A); dX = pStatusY->dPos;
		AXIS_STATUS *pStatusZ = pAJinAXL->Get_pStatus(AX_INSPECTION_Z); dZ = pStatusZ->dPos;
	}
	Set_PositionReply(nInspector, dX, 0, dZ, sGbn);
}

void CInspector::Get_AMoveRequest(int nInspector, CString sX, CString sY, CString sZ, CString sGbn)
{
	int nCanMove = 0;

	double dX = atof(sX);

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	CCommon *pCommon = CCommon::Get_Instance();
	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	
	if (sGbn!="I" && sGbn!="B") {
		Set_AMoveReply(nInspector, nCanMove, sGbn);
		return;
	}

	if (pWorkDlg->IsWindowVisible()) {		// AutoRun
		CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();

		if (sGbn=="B") {
			pSequenceMain->m_dBarcodePosA = dX;
	
			int nBarcodeCase = pSequenceMain->Get_RunCase(AUTO_BARCODE);
			if ((nBarcodeCase >= 150 && nBarcodeCase <= 170) ||
				(nBarcodeCase == 100 && gData.IndexJob[2] == 1 && gData.IndexJob[1] == 0)) {
				gData.IndexJob[2] = 0;
				pSequenceMain->Set_RunCase(AUTO_BARCODE, 160);
			} else {
				Set_AMoveReply(nInspector, nCanMove, sGbn);
				return;
			}

		} else {
			pSequenceMain->m_dVisionPosA = dX;
	
			int nVisionCase = pSequenceMain->Get_RunCase(AUTO_INSPECT);
			if ((nVisionCase >= 150 && nVisionCase <= 170) ||
				(nVisionCase == 100 && gData.IndexJob[1] == 1 && gData.IndexJob[2] == 0)) {
				gData.IndexJob[1] = 0;
				pSequenceMain->Set_RunCase(AUTO_INSPECT, 160);
			} else {
				Set_AMoveReply(nInspector, nCanMove, sGbn);
				return;
			}

		}
//		nCanMove = 1;
//		Set_AMoveReply(nInspector, nCanMove, sGbn);
		return;
	}
	
	if (sGbn!="B") {
		if (pAJinAXL->Is_Home(AX_INSPECTION_A)) {
			if (dX > 0.0) pAJinAXL->Move_Absolute(AX_INSPECTION_A, dX);
			nCanMove = 1;
		}
	} else {
		if (pAJinAXL->Is_Home(AX_BARCODE_A)) {
			if (dX > 0.0) pAJinAXL->Move_Absolute(AX_BARCODE_A, dX);
			nCanMove = 1;
		}
	}

	Set_AMoveReply(nInspector, nCanMove, sGbn);
	pAJinAXL->Read_MotionStatus();

	if (sGbn!="B") {
		while (!pAJinAXL->Is_Done(AX_INSPECTION_A)) { DoEvents(); }
	} else {
		while (!pAJinAXL->Is_Done(AX_BARCODE_A)) { DoEvents(); }
	}

	Set_MoveComplete(nInspector, sGbn);
}

void CInspector::Get_RMoveRequest(int nInspector, CString sX, CString sY, CString sZ, CString sGbn)
{
	int nCanMove = 0;
	
	double dX = atof(sX);
	double dY = atof(sY);
	double dZ = atof(sZ);
	
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();
	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	
	if (sGbn!="I" && sGbn!="B") {
		Set_RMoveReply(nInspector, nCanMove, sGbn);
		return;
	}

	if (pWorkDlg->IsWindowVisible()) 
	{									// AutoRun
		CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
		
	}
	else if (pManualDlg->m_pManualUnloadTrayDlg->IsWindowVisible()) 
	{	// Manual
			
	}
	
	Set_RMoveReply(nInspector, nCanMove, sGbn);

	pAJinAXL->Read_MotionStatus();
	
	//while (!pAJinAXL->Is_Done(AX_SCAN_X) || !pAJinAXL->Is_Done(AX_SCAN_Y) || !pAJinAXL->Is_Done(AX_SCAN_Z)) { DoEvents(); }

	Set_MoveComplete(nInspector, sGbn);
}

void CInspector::Get_ZMoveRequest(int nInspector, CString sZ)
{
	double dZ = atof(sZ);
	if (dZ <= 0.0) return;

	int nCanMove = 0;

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_2 *pDX2 = pAJinAXL->Get_pDX2();

	CCommon *pCommon = CCommon::Get_Instance();
	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	
	if (!pAJinAXL->Is_Home(AX_INSPECTION_Z)) return;
	if (pWorkDlg->IsWindowVisible()) {
		CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
		pSequenceMain->m_dVisionPosZ = dZ;

		int nVisionCase = pSequenceMain->Get_RunCase(AUTO_INSPECT);
		if (nVisionCase == 150) {
			pSequenceMain->Set_RunCase(AUTO_INSPECT, 180);
		} else {
			Set_AMoveReply(nInspector, nCanMove, "I");
			return;
		}

	} else {
		if (gData.bUseCMPress) {
			if (pDX2->iCMPressUp || !pDX2->iCMPressDn) {
				//			AfxMessageBox(_T("CM Press Block Down일 경우만 가능합니다.............."));
				return;
			}
		}

		pAJinAXL->Move_Absolute(AX_INSPECTION_Z, dZ);
		pAJinAXL->Read_MotionStatus();

		while (!pAJinAXL->Is_Done(AX_INSPECTION_Z)) { DoEvents(); }

		Set_MoveComplete(nInspector, "I");
	}	
}

void CInspector::Get_TriggerRequest(int nInspector, CString sL1, CString sL2, CString sL3, CString sL4, CString sL5, CString sL6, CString sL7, CString sL8, CString sType)
{
	gData.nLight[0] = atoi(sL1);
	gData.nLight[1] = atoi(sL2);
	gData.nLight[2] = atoi(sL3);
	gData.nLight[3] = atoi(sL4);
	gData.nLight[4] = atoi(sL5);
	gData.nLight[5] = atoi(sL6);
	gData.nLight[6] = atoi(sL7);
	gData.nLight[7] = atoi(sL8);

	// Inspector Log //////////////////////////////////////
//	CString strLog;
//	CLogFile *pLogFile = CLogFile::Get_Instance();
	///////////////////////////////////////////////////////

	//CCommon *pCommon = CCommon::Get_Instance();
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	if (sType == "B") {
		AfxBeginThread(Thread_TriggerBarcode, (LPVOID)NULL);
// 		if (gData.nTrigDelayBar > 0) Sleep(gData.nTrigDelayBar);
// 		pDY0->oBarcodeTrigger = FALSE;
// 		pDY0->oLightBarcode = FALSE;
// 		pAJinAXL->Write_Output(0);
// 
// 		Sleep(gData.nTrigSetBar);
// 
// 		pDY0->oBarcodeTrigger = TRUE;
// 		pDY0->oLightBarcode = TRUE;
// 		pAJinAXL->Write_Output(0);

	} else {
		AfxBeginThread(Thread_TriggerInspect, (LPVOID)NULL);
// 		if (gData.nTrigDelayIns > 0) Sleep(gData.nTrigDelayIns);
// 		pDY0->oCameraTrigger = FALSE;
// 		if (gData.nLight[0] == 1)	pDY0->oLight11 = FALSE;
// 		else						pDY0->oLight11 = TRUE;
// 		if (gData.nLight[1] == 1)	pDY0->oLight12 = FALSE;
// 		else						pDY0->oLight12 = TRUE;
// 		if (gData.nLight[2] == 1)	pDY0->oLight13 = FALSE;
// 		else						pDY0->oLight13 = TRUE;
// 		if (gData.nLight[3] == 1)	pDY0->oLight14 = FALSE;
// 		else						pDY0->oLight14 = TRUE;
// 		if (gData.nLight[4] == 1)	pDY0->oLight21 = FALSE;
// 		else						pDY0->oLight21 = TRUE;
// 		if (gData.nLight[5] == 1)	pDY0->oLight22 = FALSE;
// 		else						pDY0->oLight22 = TRUE;
// 		if (gData.nLight[6] == 1)	pDY0->oLight23 = FALSE;
// 		else						pDY0->oLight23 = TRUE;
// 		if (gData.nLight[7] == 1)	pDY0->oLight24 = FALSE;
// 		else						pDY0->oLight24 = TRUE;
// 		pAJinAXL->Write_Output(0);
// 
// 		Sleep(gData.nTrigSetIns);
// 
// 		pDY0->oCameraTrigger = TRUE;
// 		pDY0->oLight11 = TRUE;
// 		pDY0->oLight12 = TRUE;
// 		pDY0->oLight13 = TRUE;
// 		pDY0->oLight14 = TRUE;
// 		pDY0->oLight21 = TRUE;
// 		pDY0->oLight22 = TRUE;
// 		pDY0->oLight23 = TRUE;
// 		pDY0->oLight24 = TRUE;
// 		pDY0->oLight32 = TRUE;
// 		pDY0->oLight33 = TRUE;
// 		pDY0->oLight34 = TRUE;
// 		pDY0->oLight41 = TRUE;
// 		pDY0->oLight42 = TRUE;
// 		pDY0->oLight43 = TRUE; 
// 		pDY0->oLight44 = TRUE;
// 		pAJinAXL->Write_Output(0);

	}
	
	//Set_TriggerReply(nInspector, 1);
}

UINT CInspector::Thread_TriggerInspect(LPVOID lpVoid)
{
	g_csLightTrigger.Lock();

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	if (gData.nTrigDelayIns > 0) Sleep(gData.nTrigDelayIns);
	pDY0->oCameraTrigger = FALSE;
	if (gData.nLight[0] == 1)	pDY0->oLight11 = FALSE;
	else						pDY0->oLight11 = TRUE;
	if (gData.nLight[1] == 1)	pDY0->oLight12 = FALSE;
	else						pDY0->oLight12 = TRUE;
	if (gData.nLight[2] == 1)	pDY0->oLight13 = FALSE;
	else						pDY0->oLight13 = TRUE;
	if (gData.nLight[3] == 1)	pDY0->oLight14 = FALSE;
	else						pDY0->oLight14 = TRUE;
	if (gData.nLight[4] == 1)	pDY0->oLight21 = FALSE;
	else						pDY0->oLight21 = TRUE;
	if (gData.nLight[5] == 1)	pDY0->oLight22 = FALSE;
	else						pDY0->oLight22 = TRUE;
	if (gData.nLight[6] == 1)	pDY0->oLight23 = FALSE;
	else						pDY0->oLight23 = TRUE;
	if (gData.nLight[7] == 1)	pDY0->oLight24 = FALSE;
	else						pDY0->oLight24 = TRUE;
	pAJinAXL->Write_Output(0);

	Sleep(gData.nTrigSetIns);

	pDY0->oCameraTrigger = TRUE;
	pDY0->oLight11 = TRUE;
	pDY0->oLight12 = TRUE;
	pDY0->oLight13 = TRUE;
	pDY0->oLight14 = TRUE;
	pDY0->oLight21 = TRUE;
	pDY0->oLight22 = TRUE;
	pDY0->oLight23 = TRUE;
	pDY0->oLight24 = TRUE;
	pDY0->oLight32 = TRUE;
	pDY0->oLight33 = TRUE;
	pDY0->oLight34 = TRUE;
	pDY0->oLight41 = TRUE;
	pDY0->oLight42 = TRUE;
	pDY0->oLight43 = TRUE; 
	pDY0->oLight44 = TRUE;
	pAJinAXL->Write_Output(0);


	g_csLightTrigger.Unlock();

	return 0;
}

UINT CInspector::Thread_TriggerBarcode(LPVOID lpVoid)
{
	g_csLightTrigger.Lock();

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	if (gData.nTrigDelayBar > 0) Sleep(gData.nTrigDelayBar);
	pDY0->oBarcodeTrigger = FALSE;
	pDY0->oLightBarcode = FALSE;
	pAJinAXL->Write_Output(0);

	Sleep(gData.nTrigSetBar);

	pDY0->oBarcodeTrigger = TRUE;
	pDY0->oLightBarcode = TRUE;
	pAJinAXL->Write_Output(0);

	g_csLightTrigger.Unlock();

	return 0;
}

void CInspector::Get_MoveReply(int nInspector)
{
	//
}

void CInspector::Get_ErrorOccur(int nInspector, CString sType)
{
	int nType = atoi(sType);
	
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	CCommon *pCommon = CCommon::Get_Instance();
	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();

	if (nType == 1) {			// FM Error
		pCommon->Show_Error(9300);
	} else if (nType == 2) {	// 2D Barcode Reading Error
		pCommon->Show_Error(7400);
	}
	Set_ErrorReply(nInspector);
}

void CInspector::Get_ErrorPost(int nInspector, CString sAlmNo, CString sMsg)
{
	int nAlmNo = atoi(sAlmNo);
	
	CCommon *pCommon = CCommon::Get_Instance();

	if(nAlmNo>=9901) pCommon->Set_ErrorSubMessage(sMsg);
	pCommon->Show_Error(nAlmNo);

	Set_ErrorReply(nInspector);
}

void CInspector::Get_AlarmRequest(int nInspector, CString sGbn, CString sLotId, CString sErrNo, CString sInfo1, CString sInfo2, CString sInfo3)
{
	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	CCommon *pCommon = CCommon::Get_Instance();
	CString strErrMsg;

	int nErrNo = atoi(sErrNo);	

	if (nErrNo == 9950) {
		// 9950 : 다발불량
		// sInfo1: NG Code, sInfo2: NG Count
		int nNGCnt = atoi(sInfo2);		
		strErrMsg.Format(" ==> LotID:%s. NG Code:%s. NG Coutn:%d", sLotId, sInfo1, nNGCnt);

	} else if (nErrNo == 9960){
		// Barcode Shift 불량
		// sInfo1: X, sInfo2: Y, sInfo3: R
		double dShiftX = atof(sInfo1);
		double dShiftY = atof(sInfo2);
		double dShiftR = atof(sInfo3);
		strErrMsg.Format(" ==> LotID:%s. X: %0.3lf Y: %0.3lf R: %0.3lf", sLotId, dShiftX, dShiftY, dShiftR);
	}
	pCommon->Set_ErrorSubMessage(strErrMsg);

	int nMode = pMainDlg->Get_CurrentMode();
	if (nMode == MODE_WORK) { pCommon->m_sMessage = strErrMsg; pCommon->Show_Error(nErrNo); }
}

void CInspector::Get_FOBUpdate(int nInspector, CString sStatus)
{
	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	CCommon *pCommon = CCommon::Get_Instance();

	gData.nVisionFOBMode = atoi(sStatus);	// 1:FOB Mode On

	if (gData.nVisionFOBMode) {
		CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();

		int nMode = pMainDlg->Get_CurrentMode();
		if (nMode == MODE_WORK && pSequenceMain->Get_IsAutoRun()) pCommon->Show_Error(9970);
	}
}

void CInspector::Get_FOBReply(int nInspector, CString sStatus)
{
	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	CCommon *pCommon = CCommon::Get_Instance();

	gData.nVisionFOBMode = atoi(sStatus);	// 1:FOB Mode On
}

void CInspector::Get_APDReply(int nInspector, CString strRecv)
{
	char chSep = ',';
	CString strGbn, strLotId, strPortNo, strCount;
	CString strGV[10];

	//@APD,REPLY,I,TESTLOT,0,4,111.10,222.20,33.30,44.40
	AfxExtractSubString(strGbn, strRecv, 2, chSep);
	AfxExtractSubString(strLotId, strRecv, 3, chSep);
	AfxExtractSubString(strPortNo, strRecv, 4, chSep);
	AfxExtractSubString(strCount, strRecv, 5, chSep);	

	int nCount = atoi(strCount);	// strCount는 이미지 GV값 개수
	gData.nAviApdCnt = nCount;

	for (int i = 0; i < nCount; i++) {
		AfxExtractSubString(strGV[i], strRecv, 6 + i, chSep);
		gData.sVisionGV[i] = strGV[i];
	}

	g_objMES.Save_AviApdData(gData.sLotID, 0, gData.sOperID);

	gData.bAviApdReceive = TRUE;	// APD 데이터 MES 보고 완료.
}

void CInspector::Get_RecipeChanged(int nInspector, CString sRecipe)
{
	// 핸들러에서 처리
	Set_RecipeReply(nInspector);
}

void CInspector::Get_PmsUpload(int nInspector, CString sBarcode, CString sOrign)
{
}

void CInspector::Get_PmsResult(int nInspector, CString sBarcode, CString sMap)
{
}

// 통합환경 PC에서만 온다.
void CInspector::Get_StripReply(int nInspector)
{
	gData.nNGTrayPos++;
	if (gData.nNGTrayPos > 2) gData.nNGTrayPos =1;
	gData.nNGPos++;
	if (gData.nNGPos > 5) gData.nNGPos =1;

	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	pWorkDlg->SendMessage(UM_UPDATE_SHIFT_LIST, (WPARAM)OP_INSERT, (LPARAM)NULL);
}

void CInspector::Get_AdrDataCopy(int nInspector)
{
	AfxBeginThread(Thread_AdrDataCopy, this);
	Set_AdrDataReply(nInspector);
}

void CInspector::Get_CalRequest(int nInspector, CString sDir, CString sSpeed, CString sStartX)
{
	int nDir = atoi(sDir);
	double dSpeed = atof(sSpeed);
	double dStartX = atof(sStartX);

	CManualDlg *pManualDlg = CManualDlg::Get_Instance();

//	if (pManualDlg->m_pManualInspectorDlg->IsWindowVisible()) {	// Manual
////		if (nInspector == INSPECTOR_MOLD) {
////			int nMoldCase = pManualDlg->m_pManualInspectorDlg->Get_MoldRunCase();
////			if (nMoldCase == 0) pManualDlg->m_pManualInspectorDlg->Set_MoldScan(nDir, dSpeed, 0.0, 0.0, SCAN_CALIBRATE);	
////		} else if (nInspector == INSPECTOR_PCB) {
////			int nPcbCase = pManualDlg->m_pManualInspectorDlg->Get_PcbRunCase();
////			if (nPcbCase == 0) pManualDlg->m_pManualInspectorDlg->Set_PcbScan(nDir, dSpeed, 0.0, SCAN_CALIBRATE);
////		} else if (nInspector == INSPECTOR_3D) {
//			int n3dCase = pManualDlg->m_pManualInspectorDlg->Get_3dRunCase();
//			if (n3dCase == 0) pManualDlg->m_pManualInspectorDlg->Set_3dScan(nDir, dSpeed, 0.0, dStartX, SCAN_CALIBRATE);
////		}
//	}
	Set_CalReply(nInspector);
}

void CInspector::Get_CalReply(int nInspector)
{
	//
}


void CInspector::Get_ElectReply(int nInspector)
{
	//
}

void CInspector::Get_WarpReply(int nInspector)
{
	//
}

void CInspector::Get_NGBarcodeReply(int nInspector)
{
	//
}

void CInspector::Get_MThickComplete(int nInspector, CString sLotId, CString sStripId, CString sValue[])
{
}

void CInspector::Get_CorrectComplete(int nInspector, CString sX, CString sY, CString sZ)
{
	CString strX = "0.0";
	CString strY = "0.0";
	CString strZ = "0.0";

	if (sX != "") strX.Format("%0.3lf", atof(sX));
	if (sY != "") strY.Format("%0.3lf", atof(sY));
	if (sZ != "") strZ.Format("%0.3lf", atof(sZ));
}

void CInspector::Get_TimeReply(int nInspector)
{
	//
}

/////////////////////////////////////////////////////////////////////////////
// Set Command

void CInspector::Set_ConnectRequest(int nInspector)
{
	CString sSendData;
	sSendData = "CONNECT,REQUEST";
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_ConnectReply(int nInspector)
{
	CString sSendData;
	sSendData = "CONNECT,REPLY";
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_ConnectEnd(int nInspector)
{
	CString sSendData;
	sSendData = "CONNECT,END";
	Send_Command(nInspector, sSendData);

	m_bConnectedVision = FALSE;
}

void CInspector::Set_StatusRequest(int nInspector)
{
	m_nStatusVision = -1;	// 응답 감시하기 위해

//	m_strSend = "STATUS,REQUEST";
//	Send_Command(nInspector, m_strSend);
}

void CInspector::Set_StatusReply(int nInspector, int nStatus)
{
//	m_strSend.Format("STATUS,REPLY,%d", nStatus);
//	Send_Command(nInspector, m_strSend);
}

void CInspector::Set_StatusUpdate(int nInspector, int nStatus)
{
	CString sSendData;
	sSendData.Format("STATUS,UPDATE,%d", nStatus);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_ModelUpdate(int nInspector, CString sModel, double dSizeX, double dSizeY, double dThick, int nBlockCnt, int nPkgXCnt, int nPkgYCnt, double dBallSize)
{
	CString sSendData;
	sSendData.Format("MODEL,UPDATE,%s,%0.3lf,%0.3lf,%0.3lf,%d,%d,%d,%0.3lf", sModel, dSizeX, dSizeY, dThick, nBlockCnt, nPkgXCnt, nPkgYCnt, dBallSize);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_LotStart(int nInspector)
{
	CString sSendData;
	sSendData.Format("LOT,START,%s,%d,%d", gLot.sLotID, gLot.nTrayCount, gLot.nCMCount);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_LotCount(int nInspector)
{
	CString sSendData;
	sSendData.Format("LOT,COUNT,%s,%d,%d", gLot.sLotID, gLot.nTrayCount, gLot.nCMCount);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_LotComplete(int nInspector)
{
	CString sSendData;
	sSendData.Format("LOT,COMPLETE");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_LoadComplete(int nInspector, int nTrayNo, int nTRNo)
{
	CString sSendData;
	sSendData.Format("LOAD,COMPLETE,%s,%02d,%d,%s", gLot.sLotID, nTrayNo, nTRNo, gData.sRecipeName);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_ScanReply(int nInspector, int nNG)
{
	CString sSendData;
	sSendData.Format("SCAN,REPLY,%d", nNG);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_ScanComplete(int nInspector)
{
	CString sSendData;
	sSendData.Format("SCAN,COMPLETE");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_InspectReply(int nInspector, int nErr)
{
	CString sSendData;
	sSendData.Format("INSPECT,REPLY,%d", nErr);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_ReviewReply(int nInspector)
{
	CString sSendData;
	sSendData.Format("REVIEW,REPLY");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_PositionReply(int nInspector, double dX, double dY, double dZ, CString sGbn)
{
	CString sSendData;
	sSendData.Format("POSITION,REPLY,%0.3lf,%0.3lf,%0.3lf,%s", dX, dY, dZ, sGbn);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_AMoveReply(int nInspector, int nCanMove, CString sGbn)
{
	CString sSendData;
	sSendData.Format("AMOVE,REPLY,%d,%s", nCanMove, sGbn);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_RMoveReply(int nInspector, int nCanMove, CString sGbn)
{
	CString sSendData;
	sSendData.Format("RMOVE,REPLY,%d,%s", nCanMove, sGbn);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_TriggerReply(int nInspector, int nCanMove)
{
	CString sSendData;
	sSendData.Format("TRIGGER,REPLY,%d", nCanMove);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_MoveComplete(int nInspector, CString sGbn)
{
	CString sSendData;
	sSendData.Format("MOVE,COMPLETE,%s", sGbn);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_ErrorReply(int nInspector)
{
	CString sSendData;
	sSendData.Format("ERROR,REPLY");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_RecipeReply(int nInspector)
{
	CString sSendData;
	sSendData.Format("RECIPE,REPLY");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_PmsDownload(int nInspector, CString sBarcode, CString sMap)
{
	CString sSendData;
	sSendData.Format("PMS,DOWNLOAD,%s,%s", sBarcode, sMap);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_StripComplete(int nInspector, int nInspectId, CString sModel, CString sLotId, CString sPartNo, int nStripId, CString sStatus)
{
	CString sSendData;
	sSendData.Format("STRIP,COMPLETE,%d,%s,%s,%s,%02d,%s", nInspectId, sModel, sLotId, sPartNo, nStripId, sStatus);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_AdrDataReply(int nInspector)
{
	CString sSendData;
	sSendData.Format("ADRDAA,REPLY");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_CalReply(int nInspector)
{
	CString sSendData;
	sSendData.Format("CAL,REPLY");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_CalComplete(int nInspector)
{
	CString sSendData;
	sSendData.Format("CAL,COMPLETE");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_LaserReply(int nInspector, int nNG)
{
	CString sSendData;
	sSendData.Format("LASER,REPLY,%d", nNG);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_LaserComplete(int nInspector)
{
	CString sSendData;
	sSendData.Format("LASER,COMPLETE");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_ElectComplete(int nInspector, CString sLotId, CString sStripId, double dValue, int nInOut)
{
	CString sSendData;
	sSendData.Format("ELECT,COMPLETE,%s,%s,%0.3lf,%d", sLotId, sStripId, dValue, nInOut);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_WarpComplete(int nInspector, CString sLotId, CString sStripId, double dValue)
{
	CString sSendData;
	sSendData.Format("WARP,COMPLETE,%s,%s,%0.3lf", sLotId, sStripId, dValue);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_MThickReply(int nInspector)
{
	CString sSendData;
	sSendData.Format("MTHICK,REPLY");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_TimeUpdate(int nInspector)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strTime;
//	strTime.Format("%04d,%02d,%02d,%02d,%02d,%02d,%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d %03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	CString sSendData;
	sSendData.Format("TIME,UPDATE,%s", strTime);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_NGBarcode(int nInspector, CString sLodID, CString sBarcodeData, int TrayNo, int nBarcodeX, int nBarcodeY)
{
	CString sSendData;
	if (sBarcodeData.GetLength() == 0) sBarcodeData = "NO_READ";
	sSendData.Format("BARCODE,DATA,%s,%s,%d,%d,%d", sBarcodeData, sLodID, TrayNo, nBarcodeX, nBarcodeY);
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_FOBRequest(int nInspector)
{
	gData.nVisionFOBMode = -1;
	CString sSendData;
	sSendData.Format("FOB,REQUEST");
	Send_Command(nInspector, sSendData);
}

void CInspector::Set_APDRequest(int nInspector)
{
	int nPortNo = 0;
	CString strSendCmd;
	for (int i = 0; i < 10; i++) gData.sVisionGV[i] = "";
	strSendCmd.Format("APD,REQUEST,I,%s,%d", gData.sLotID, nPortNo);
	Send_Command(nInspector, strSendCmd);
	gData.bAviApdRequest = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// UDP Socket Send Message

void CInspector::Send_Command(int nInspector, CString strSend)
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	if (!pEquipData->bUseVisionInspect) return;

	// Inspector Log //////////////////////////////////////
	CString strLog;
	CLogFile *pLogFile = CLogFile::Get_Instance();
	strLog.Format("[H->V%d],%s", nInspector, strSend);
	pLogFile->Save_InspectorLog(strLog);
	///////////////////////////////////////////////////////

	g_csInspector.Lock();	// Critical Section

	CString strSendSocket;
	strSendSocket.Format("@%s\n", strSend);

	char chSend[2048] = { 0 };
	int nLength = strSendSocket.GetLength();
	memcpy(chSend, (LPSTR)(LPCSTR)strSendSocket, nLength);

	m_UdpVision.Write_Socket((BYTE*)chSend, nLength);

	g_csInspector.Unlock();	// Critical Section
}
/////////////////////////////////////////////////////////////////////////////

void CInspector::DoEvents(int nSleep)
{
	MSG msg;
	if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (nSleep > 0) Sleep(nSleep);
}

/////////////////////////////////////////////////////////////////////////////
// AdrData Copy Thread Function

UINT CInspector::Thread_AdrDataCopy(LPVOID lpVoid)
{
	CCommon *pCommon = CCommon::Get_Instance();
	pCommon->Copy_AdrDData();

	return 0;
}

/////////////////////////////////////////////////////////////////////////////

void CInspector::Test_Command()
{
//	Get_ModelUpdate("TEST-111006", "80", "280", "0.3", "3", "3", "3", "0.01");
//	Get_LoadComplete("Strip-A");
//	m_strSend.Format("RMOVE,REQUEST,10.0,20.0,0");
//	Send_Command(m_strSend);
//	Set_AMoveRequest(0, 10, 0);
// 	Get_ScanComplete();

// 	Get_ScanRequest(INSPECTOR_MOLD, "1", "50.0", "");
// 	Get_ScanRequest(INSPECTOR_PCB, "0", "100.0", "");
// 	Get_ScanRequest(INSPECTOR_3D, "1", "50.0", "15.0");
// 	Get_ReviewComplete(INSPECTOR_MOLD, "00");
// 	Get_PmsUpload(INSPECTOR_MOLD, "ABCDEFG", "2");
	Get_AdrDataCopy(0);
}
