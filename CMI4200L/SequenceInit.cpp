// SequenceInit.cpp : 구현 파일
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "CMI4200LDlg.h"
#include "SequenceInit.h"
#include <math.h>

#include "LogFile.h"
#include "SequenceMain.h"
#include "MESInterface.h"

CSequenceInit *CSequenceInit::m_pInstance = NULL;

CSequenceInit* CSequenceInit::Get_Instance()
{
	if (!m_pInstance)
		m_pInstance = new CSequenceInit();
	return m_pInstance;
}

void CSequenceInit::Delete_Instance()
{
	if (m_pInstance)
		delete m_pInstance;
	m_pInstance = NULL;
}

///////////////////////////////////////////////////////////////////////////////

CSequenceInit::CSequenceInit()
{
	m_pAJinAXL = CAJinAXL::Get_Instance();
	
	for (int i = 0; i < AXIS_COUNT; i++) {
		m_pStatus[i] = m_pAJinAXL->Get_pStatus(i);
		m_pParam[i] = m_pAJinAXL->Get_pParam(i);
	}
	
	m_pDX0 = m_pAJinAXL->Get_pDX0();
	m_pDX1 = m_pAJinAXL->Get_pDX1();
	m_pDX2 = m_pAJinAXL->Get_pDX2();
	m_pDX3 = m_pAJinAXL->Get_pDX3();
	m_pDX4 = m_pAJinAXL->Get_pDX4();
	m_pDX5 = m_pAJinAXL->Get_pDX5();
	m_pDX6 = m_pAJinAXL->Get_pDX6();
	
	m_pDY0 = m_pAJinAXL->Get_pDY0();
	m_pDY1 = m_pAJinAXL->Get_pDY1();
	m_pDY2 = m_pAJinAXL->Get_pDY2();
	m_pDY3 = m_pAJinAXL->Get_pDY3();
	m_pDY4 = m_pAJinAXL->Get_pDY4();
	m_pDY5 = m_pAJinAXL->Get_pDY5();
	m_pDY6 = m_pAJinAXL->Get_pDY6();

	m_pDataManager = CDataManager::Get_Instance();
	m_pEquipData = m_pDataManager->Get_pEquipData();
	m_pModelData = m_pDataManager->Get_pModelData();
	m_pMoveData = m_pDataManager->Get_pMoveData();
	
	m_pCommon = CCommon::Get_Instance();
	
	m_bThreadInitial = FALSE;
	m_pThreadInitial = NULL;
	
	Reset_InitialCase();
	m_bInitComplete = FALSE;
}

CSequenceInit::~CSequenceInit()
{
	if (m_pThreadInitial) {
		m_bThreadInitial = FALSE;
		WaitForSingleObject(m_pThreadInitial->m_hThread, INFINITE);
	}
}

void CSequenceInit::Get_InitCase(int &nMain, int &nCase1, int &nCase2, int &nCase3, int &nCase4, int &nCase5, int &nCase6, int &nCase7, int &nCase8, int &nCase9, int &nCase10, int &nCase11)
{
	nMain   = m_nInitMainCase;
	nCase1  = m_nInitLoad1Case;
	nCase2  = m_nInitLoad2Case;
	nCase3  = m_nInitUnload1Case;
	nCase4  = m_nInitUnload2Case;
	nCase5  = m_nInitNGTrayCase;
	nCase6  = m_nInitIndexTCase;
	nCase7  = m_nInitLDPickerCase;
	nCase8  = m_nInitNGPickerCase;
	nCase9  = m_nInitGDPickerCase;
	nCase10 = m_nInitULPickerCase;
	nCase11 = m_nInitInspectCase;
}

void CSequenceInit::Begin_InitialThread()
{
	m_bInitComplete = FALSE;
	Reset_InitialCase();
	if (m_nInitMainCase == 100) m_nInitMainCase = 110;
	
	if (m_pThreadInitial) End_InitialThread();
	m_bThreadInitial = TRUE;
	m_pThreadInitial = AfxBeginThread(Thread_Initial, this);
}

void CSequenceInit::End_InitialThread()
{
	if (m_pThreadInitial) {
		m_bThreadInitial = FALSE;
		WaitForSingleObject(m_pThreadInitial->m_hThread, INFINITE);
	}
}

void CSequenceInit::Reset_InitialCase()
{
	m_nInitMainCase = 100;
	m_nInitLoad1Case = 100;
	m_nInitLoad2Case = 100;
	m_nInitUnload1Case = 100;
	m_nInitUnload2Case = 100;
	m_nInitNGTrayCase = 100;
	m_nInitIndexTCase = 100;
	m_nInitLDPickerCase = 100;
	m_nInitNGPickerCase = 100;
	m_nInitGDPickerCase = 100;
	m_nInitULPickerCase = 100;
	m_nInitInspectCase = 100;
	m_nInitTestCase = 100;
}

/////////////////////////////////////////////////////////////////////////////
// Initial Thread Function 

UINT CSequenceInit::Thread_Initial(LPVOID lpVoid)
{
	CSequenceInit *pSequenceInit = (CSequenceInit*)lpVoid;
	CCommon *pCommon = CCommon::Get_Instance();

	while (pSequenceInit->m_bThreadInitial) {

//		if (!pSequenceInit->Initial_TestRun()) break;

		if (!pCommon->Check_MainEmgAir()) break;
		if (!pCommon->Check_MainDoor()) break;
		if (!pCommon->Check_ServoOn()) break;
		if (!pCommon->Check_DirveAlarm()) break;

		if (!pSequenceInit->Initial_MainRun()) break;		// 0.  (Error : 1100)
		if (!pSequenceInit->Initial_Load1Run()) break;		// 1.  (Error : 1210)
		if (!pSequenceInit->Initial_Load2Run()) break;		// 2.  (Error : 1260)
		if (!pSequenceInit->Initial_Unload1Run()) break;	// 3.  (Error : 1310)
		if (!pSequenceInit->Initial_Unload2Run()) break;	// 4.  (Error : 1360)

		if (!pSequenceInit->Initial_InspectRun()) break;	// 5.  (Error : 1410)
		if (!pSequenceInit->Initial_NGPickerRun()) break;	// 6.  (Error : 1510)
		if (!pSequenceInit->Initial_GDPickerRun()) break;	// 7.  (Error : 1610)
		if (!pSequenceInit->Initial_LDPickerRun()) break;	// 8.  (Error : 1710)
		if (!pSequenceInit->Initial_ULPickerRun()) break;	// 9.  (Error : 1810)

		if (!pSequenceInit->Initial_IndexTRun()) break;		// 10. (Error : 1910)
		if (!pSequenceInit->Initial_NGTrayRun()) break;		// 11. (Error : 1960)
		if (!pSequenceInit->Initial_Simulation()) break;		// 99. (Simulation)

		Sleep(10);
	} 
	pSequenceInit->m_bThreadInitial = FALSE;
	pSequenceInit->m_pThreadInitial = NULL;

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// 1. Main (Error : 1100, 1190)
BOOL CSequenceInit::Initial_MainRun()
{
	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitMainCase) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_MAIN, 5000);
		break;

	case 110:
		pLogFile->Save_HandlerLog("[Initial Sequence - Main] start");
		pMainDlg->Set_LotErrorLog("INITIAL", 906, "Start");

		gLot.sLotID = "";

		m_nInitMainCase = 120;
		m_pCommon->Set_LoopTime(INITIAL_MAIN, 5000);
		break;

	case 120:
		if (!m_pDX1->iLS_UnloadFullCheck) {
			m_nInitMainCase = 121;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 5000);
		}
		break;
	case 121:
#ifdef TRAY_CHECK2
		if (!m_pDX1->iLS_Z1Check1 && !m_pDX1->iLS_Z1Check2) {
#else
		if (!m_pDX1->iLS_Z1Check1) {
#endif
			m_nInitMainCase = 122;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 5000);
		}
		break;
	case 122:
#ifdef TRAY_CHECK2
		if (!m_pDX1->iLS_Z2Check1 && !m_pDX1->iLS_Z2Check2) {
#else
		if (!m_pDX1->iLS_Z2Check1) {
#endif
			m_nInitMainCase = 123;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 5000);
		}
		break;
	case 123:
		if (!m_pDX6->iUS_UnloadFullCheck) {
			m_nInitMainCase = 124;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 5000);
		}
		break;
	case 124:
#ifdef TRAY_CHECK2
		if (!m_pDX6->iUS_Z1Check1 && !m_pDX6->iUS_Z1Check2) {
#else
		if (!m_pDX6->iUS_Z1Check1) {
#endif
			m_nInitMainCase = 125;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 5000);
		}
		break;
	case 125:
#ifdef TRAY_CHECK2
		if (!m_pDX6->iUS_Z2Check1 && !m_pDX6->iUS_Z2Check2) {
#else
		if (!m_pDX6->iUS_Z2Check1) {
#endif
			m_nInitMainCase = 150;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 5000);
		}
		break;


	case 150:	// 각 파트 초기화 진행
		if (m_nInitLoad1Case == 100)		m_nInitLoad1Case = 110;
		if (m_nInitLoad2Case == 100)		m_nInitLoad2Case = 110;
		if (m_nInitUnload1Case == 100)		m_nInitUnload1Case = 110;
		if (m_nInitUnload2Case == 100)		m_nInitUnload2Case = 110;
		if (m_nInitNGTrayCase == 100)		m_nInitNGTrayCase = 110;
		if (m_nInitIndexTCase == 100)		m_nInitIndexTCase = 110;
		if (m_nInitLDPickerCase == 100)		m_nInitLDPickerCase = 110;
		if (m_nInitNGPickerCase == 100)		m_nInitNGPickerCase = 110;
		if (m_nInitGDPickerCase == 100)		m_nInitGDPickerCase = 110;
		if (m_nInitULPickerCase == 100)		m_nInitULPickerCase = 110;
		if (m_nInitInspectCase == 100)		m_nInitInspectCase = 110;

		m_nInitMainCase = 950;
		m_pCommon->Set_LoopTime(INITIAL_MAIN, 600000);
		break;


	case 950:	// Wait 
		if (m_nInitLoad1Case == 200 && m_nInitLoad2Case == 200 && m_nInitUnload1Case == 200 && m_nInitUnload2Case == 200 &&
			m_nInitNGTrayCase == 200 && m_nInitIndexTCase == 200 && m_nInitInspectCase == 200 &&
			m_nInitLDPickerCase == 200 && m_nInitNGPickerCase == 200 && m_nInitGDPickerCase == 200 && m_nInitULPickerCase == 200) {
			m_nInitMainCase = 960;
		}
		m_pCommon->Set_LoopTime(INITIAL_MAIN, 5000);
		break;

	case 960:	// Initial Complete
		m_bInitComplete = TRUE;

		m_nInitMainCase = 100;
		m_nInitLoad1Case = 100;
		m_nInitLoad2Case = 100;
		m_nInitUnload1Case = 100;
		m_nInitUnload2Case = 100;
		m_nInitNGTrayCase = 100;
		m_nInitIndexTCase = 100;
		m_nInitLDPickerCase = 100;
		m_nInitNGPickerCase = 100;
		m_nInitGDPickerCase = 100;
		m_nInitULPickerCase = 100;
		m_nInitInspectCase = 100;

		// 변수 초기화
		CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
		pSequenceMain->Set_RunCase(100, 440, 100, 440, 100, 100, 100, 100, 100, 100, 100, 100);
		pSequenceMain->Set_ClearRunData(0);
		gData.bCleanOutMode = FALSE;

		CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
		pMainDlg->Set_MainState(STATE_INITEND);
		g_objMES.Initialize(m_pEquipData->bUseMES);

		pLogFile->Save_HandlerLog("[Initial Sequence - Main] End");
		pMainDlg->Set_LotErrorLog("INITIAL", 907, "End");

		return FALSE;	// Thread_Initial 종료
	}

	// 1. Main (Error : 1100, 1900)
	if (m_pCommon->Over_LoopTime(INITIAL_MAIN)) {
		if (m_nInitMainCase >= 950) return TRUE;
		m_pCommon->Show_Error(1000 + m_nInitMainCase);
		return FALSE;
	} else {
		return TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// 1.  (Error : 1210)
BOOL CSequenceInit::Initial_Load1Run()
{
	double	dPosX1, dPosX2;
	AXIS_STATUS *pStatus;
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitLoad1Case) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_LOAD1, 5000);
		break;

	case 110:
		if(m_nInitLDPickerCase < 151) return TRUE;
		pLogFile->Save_HandlerLog("[Initial Sequence - Load1Run] start");
				
		m_nInitLoad1Case = 111;
		m_pCommon->Set_LoopTime(INITIAL_LOAD1, 5000);
		break;

	case 111:
			m_pDY1->oLS_LoadSupport12In = TRUE;
			m_pDY1->oLS_LoadSupport12Out = FALSE;

			m_pDY1->oLS_Z1AlignS12In = TRUE;
			m_pDY1->oLS_Z1AlignS12Out = FALSE;
			m_pDY1->oLS_Z1AlignM34In = TRUE;
			m_pDY1->oLS_Z1AlignM34Out = FALSE;

			m_pDY1->oLS_Z2AlignS12In = TRUE;
			m_pDY1->oLS_Z2AlignS12Out = FALSE;
			m_pDY1->oLS_Z2AlignM34In = TRUE;
			m_pDY1->oLS_Z2AlignM34Out = FALSE;

			m_pAJinAXL->Write_Output(1);
			m_nInitLoad1Case = 112;
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 5000);
		break;
	case 112:
		if (m_pDX1->iLS_LoadSupport1In && !m_pDX1->iLS_LoadSupport1Out 
			&& m_pDX1->iLS_LoadSupport2In && !m_pDX1->iLS_LoadSupport2Out &&
			m_pDX1->iLS_Z2AlignS12In && !m_pDX1->iLS_Z2AlignS12Out && 
			m_pDX1->iLS_Z2AlignM34In && !m_pDX1->iLS_Z2AlignM34Out) {
			m_nInitLoad1Case = 113;
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 5000);
		}
		break;
	case 113:
		if (m_pDX1->iLS_Z1AlignS12In && !m_pDX1->iLS_Z1AlignS12Out && m_pDX1->iLS_Z1AlignM34In && !m_pDX1->iLS_Z1AlignM34Out) {
			m_nInitLoad1Case = 150;
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 60000);
		}
		break;

	case 150:
		if (m_pCommon->Check_Position(AX_LOAD_PICKER_Z, 0) ) {
			m_nInitLoad1Case = 160;
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 60000);
		}
		break;

	case 160:
			pStatus = m_pAJinAXL->Get_pStatus(AX_LOAD_TRAY_X1);
			dPosX1 = pStatus->dPos;

			pStatus = m_pAJinAXL->Get_pStatus(AX_LOAD_TRAY_X2);
			dPosX2 = pStatus->dPos;

		if (dPosX1 <= dPosX2) {
			m_pCommon->Move_Position(AX_LOAD_TRAY_X1, 0);
			m_pCommon->Move_Position(AX_LOAD_TRAY_X2, 2);
		} else {
			m_pCommon->Move_Position(AX_LOAD_TRAY_X1, 2);
			m_pCommon->Move_Position(AX_LOAD_TRAY_X2, 0);
		}
			m_nInitLoad1Case = 161;
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 30000);
		break;
	case 161:
		if ((m_pCommon->Check_Position(AX_LOAD_TRAY_X1, 0) && m_pCommon->Check_Position(AX_LOAD_TRAY_X2, 2)) ||
			(m_pCommon->Check_Position(AX_LOAD_TRAY_X1, 2) && m_pCommon->Check_Position(AX_LOAD_TRAY_X2, 0))) {
			m_pCommon->Move_Position(AX_LOAD_TRAY_Z1, 0);
			m_pCommon->Move_Position(AX_LOAD_TRAY_Z2, 0);
			m_nInitLoad1Case = 162;
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 30000);
		}
		break;
	case 162:
		if (m_pCommon->Check_Position(AX_LOAD_TRAY_Z1, 0) && m_pCommon->Check_Position(AX_LOAD_TRAY_Z2, 0)) {
			m_pAJinAXL->Home_Search(AX_LOAD_TRAY_Z1);
			m_pAJinAXL->Home_Search(AX_LOAD_TRAY_Z2);
			m_nInitLoad1Case = 163;
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 60000);
		}
		break;
	case 163:
		if (m_pAJinAXL->Is_Home(AX_LOAD_TRAY_Z1) && m_pAJinAXL->Is_Home(AX_LOAD_TRAY_Z2)) {
			m_pCommon->Move_Position(AX_LOAD_TRAY_Z1, 0);
			m_pCommon->Move_Position(AX_LOAD_TRAY_Z2, 1);
			m_nInitLoad1Case = 164;
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 30000);
		}
		break;
	case 164:
		if (m_pCommon->Check_Position(AX_LOAD_TRAY_Z1, 0) && m_pCommon->Check_Position(AX_LOAD_TRAY_Z2, 1)) {
			m_pAJinAXL->Home_Search(AX_LOAD_TRAY_X1);
			m_pAJinAXL->Home_Search(AX_LOAD_TRAY_X2);
			m_nInitLoad1Case = 165;
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 60000);
		}
		break;
	case 165:
		if (m_pAJinAXL->Is_Home(AX_LOAD_TRAY_X1) && m_pAJinAXL->Is_Home(AX_LOAD_TRAY_X2)) {
			m_pCommon->Move_Position(AX_LOAD_TRAY_X1, 0);
			m_pCommon->Move_Position(AX_LOAD_TRAY_X2, 3);
			m_nInitLoad1Case = 166;
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 30000);
		}
		break;
	case 166:
		if (m_pCommon->Check_Position(AX_LOAD_TRAY_X1, 0) && m_pCommon->Check_Position(AX_LOAD_TRAY_X2, 3)) {
			m_nInitLoad1Case = 200;

			m_pDY1->oLS_Z1AlignS12In = FALSE;
			m_pDY1->oLS_Z1AlignS12Out = TRUE;
			m_pDY1->oLS_Z1AlignM34In = FALSE;
			m_pDY1->oLS_Z1AlignM34Out = TRUE;

			m_pDY1->oLS_Z2AlignS12In = FALSE;
			m_pDY1->oLS_Z2AlignS12Out = TRUE;
			m_pDY1->oLS_Z2AlignM34In = FALSE;
			m_pDY1->oLS_Z2AlignM34Out = TRUE;
			m_pAJinAXL->Write_Output(1);
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 30000);
		}
		break;

	case 200:	// Load Initialize Complete
		if (!m_pDX1->iLS_LoadSupport1In && m_pDX1->iLS_LoadSupport1Out && !m_pDX1->iLS_LoadSupport2In && m_pDX1->iLS_LoadSupport2Out
			 && !m_pDX1->iLS_Z2AlignS12In && m_pDX1->iLS_Z2AlignS12Out && !m_pDX1->iLS_Z2AlignM34In && m_pDX1->iLS_Z2AlignM34Out){
			m_pCommon->Set_LoopTime(INITIAL_LOAD1, 5000);
		} 		
		break;
	}

	// 1.  (Error : 1210)
	if (m_pCommon->Over_LoopTime(INITIAL_LOAD1)) {
		m_pCommon->Show_Error(1100 + m_nInitLoad1Case);
		return FALSE;
	} else {
		return TRUE;
	}
}

// 2.  (Error : 1260)
BOOL CSequenceInit::Initial_Load2Run()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitLoad2Case) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_LOAD2, 5000);
		break;

	case 110:
		pLogFile->Save_HandlerLog("[Initial Sequence - Load2Run] start");
				
		m_nInitLoad2Case = 111;
		m_pCommon->Set_LoopTime(INITIAL_LOAD2, 5000);
		break;

	case 111:
			m_pDY1->oLS_UnloadSupport12In = TRUE;
			m_pDY1->oLS_UnloadSupport12Out = FALSE;
			m_pAJinAXL->Write_Output(1);
			m_nInitLoad2Case = 112;
			m_pCommon->Set_LoopTime(INITIAL_LOAD2, 5000);
		break;
	case 112:
		if (m_pDX1->iLS_UnloadSupport1In && !m_pDX1->iLS_UnloadSupport1Out && m_pDX1->iLS_UnloadSupport2In && !m_pDX1->iLS_UnloadSupport2Out) {
			m_nInitLoad2Case = 113;
			m_pCommon->Set_LoopTime(INITIAL_LOAD2, 5000);
		}
		break;
	case 113:
		if (1) {
			m_nInitLoad2Case = 200;
			m_pCommon->Set_LoopTime(INITIAL_LOAD2, 60000);
		}
		break;

	case 200:	// Load Initialize Complete
		if (1)
		{	
			m_pCommon->Set_LoopTime(INITIAL_LOAD2, 5000);
		}
		break;
	}

	// 2.  (Error : 1260)
	if (m_pCommon->Over_LoopTime(INITIAL_LOAD2)) {
		m_pCommon->Show_Error(1150 + m_nInitLoad2Case);
		return FALSE;
	} else {
		return TRUE;
	}
}

// 3.  (Error : 1310)
BOOL CSequenceInit::Initial_Unload1Run()
{
	double	dPosY1, dPosY2;
	AXIS_STATUS *pStatus;
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitUnload1Case) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 5000);
		break;

	case 110:
		if(m_nInitULPickerCase < 151) return TRUE;
		pLogFile->Save_HandlerLog("[Initial Sequence - Unload1Run] start");
				
		m_nInitUnload1Case = 111;
		m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 5000);
		break;

	case 111:
			m_pDY6->oUS_LoadSupport12In = TRUE;
			m_pDY6->oUS_LoadSupport12Out = FALSE;
					 
			m_pDY6->oUS_Z1AlignS12In = TRUE;
			m_pDY6->oUS_Z1AlignS12Out = FALSE;
			m_pDY6->oUS_Z1AlignM34In = TRUE;
			m_pDY6->oUS_Z1AlignM34Out = FALSE;
			
			m_pDY6->oUS_Z2AlignS12In = TRUE;
			m_pDY6->oUS_Z2AlignS12Out = FALSE;
			m_pDY6->oUS_Z2AlignM34In = TRUE;
			m_pDY6->oUS_Z2AlignM34Out = FALSE;
			
			m_pAJinAXL->Write_Output(6);
			m_nInitUnload1Case = 112;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 5000);
		break;
	case 112:
		if (m_pDX6->iUS_LoadSupport1In && !m_pDX6->iUS_LoadSupport1Out && m_pDX6->iUS_LoadSupport2In && !m_pDX6->iUS_LoadSupport2Out) {
			m_nInitUnload1Case = 113;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 5000);
		}
		break;
	case 113:
		if (m_pDX6->iUS_Z1AlignS12In && !m_pDX6->iUS_Z1AlignS12Out && m_pDX6->iUS_Z1AlignM34In && !m_pDX6->iUS_Z1AlignM34Out
			&& m_pDX6->iUS_Z2AlignS12In && !m_pDX6->iUS_Z2AlignS12Out && m_pDX6->iUS_Z2AlignM34In && !m_pDX6->iUS_Z2AlignM34Out) {
			m_nInitUnload1Case = 150;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 60000);
		}
		break;

	case 150:
		if (m_pCommon->Check_Position(AX_UNLOAD_PICKER_Z, 0) ) {
			m_nInitUnload1Case = 160;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 60000);
		}
		break;

	case 160:
			pStatus = m_pAJinAXL->Get_pStatus(AX_UNLOAD_TRAY_Y1);
			dPosY1 = pStatus->dPos;

			pStatus = m_pAJinAXL->Get_pStatus(AX_UNLOAD_TRAY_Y2);
			dPosY2 = pStatus->dPos;

		if (dPosY1 >= dPosY2) {
			m_pCommon->Move_Position(AX_UNLOAD_TRAY_Y1, 0);
			m_pCommon->Move_Position(AX_UNLOAD_TRAY_Y2, 3);
		} else {
			m_pCommon->Move_Position(AX_UNLOAD_TRAY_Y1, 3);
			m_pCommon->Move_Position(AX_UNLOAD_TRAY_Y2, 0);
		}
			m_nInitUnload1Case = 161;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 30000);
		break;
	case 161:
		if ((m_pCommon->Check_Position(AX_UNLOAD_TRAY_Y1, 0) && m_pCommon->Check_Position(AX_UNLOAD_TRAY_Y2, 3)) ||
			(m_pCommon->Check_Position(AX_UNLOAD_TRAY_Y1, 3) && m_pCommon->Check_Position(AX_UNLOAD_TRAY_Y2, 0))) {
			m_pCommon->Move_Position(AX_UNLOAD_TRAY_Z1, 0);
			m_pCommon->Move_Position(AX_UNLOAD_TRAY_Z2, 0);
			m_nInitUnload1Case = 162;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 30000);
		}
		break;
	case 162:
		if (m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z1, 0) && m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z2, 0)) {
			m_pAJinAXL->Home_Search(AX_UNLOAD_TRAY_Z1);
			m_pAJinAXL->Home_Search(AX_UNLOAD_TRAY_Z2);
			m_nInitUnload1Case = 163;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 60000);
		}
		break;
	case 163:
		if (m_pAJinAXL->Is_Home(AX_UNLOAD_TRAY_Z1) && m_pAJinAXL->Is_Home(AX_UNLOAD_TRAY_Z2)) {
			m_pCommon->Move_Position(AX_UNLOAD_TRAY_Z1, 0);
			m_pCommon->Move_Position(AX_UNLOAD_TRAY_Z2, 1);
			m_nInitUnload1Case = 164;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 30000);
		}
		break;
	case 164:
		if (m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z1, 0) && m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z2, 1)) {
			m_pAJinAXL->Home_Search(AX_UNLOAD_TRAY_Y1);
			m_pAJinAXL->Home_Search(AX_UNLOAD_TRAY_Y2);
			m_nInitUnload1Case = 165;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 60000);
		}
		break;
	case 165:
		if (m_pAJinAXL->Is_Home(AX_UNLOAD_TRAY_Y1) && m_pAJinAXL->Is_Home(AX_UNLOAD_TRAY_Y2)) {
			m_pCommon->Move_Position(AX_UNLOAD_TRAY_Y1, 0);
			m_pCommon->Move_Position(AX_UNLOAD_TRAY_Y2, 3);
			m_nInitUnload1Case = 166;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 30000);
		}
		break;
	case 166:
		if (m_pCommon->Check_Position(AX_UNLOAD_TRAY_Y1, 0) && m_pCommon->Check_Position(AX_UNLOAD_TRAY_Y2, 3)) {
			m_pDY6->oUS_Z1AlignS12In = FALSE;
			m_pDY6->oUS_Z1AlignS12Out = TRUE;
			m_pDY6->oUS_Z1AlignM34In = FALSE;
			m_pDY6->oUS_Z1AlignM34Out = TRUE;

			m_pDY6->oUS_Z2AlignS12In = FALSE;
			m_pDY6->oUS_Z2AlignS12Out = TRUE;
			m_pDY6->oUS_Z2AlignM34In = FALSE;
			m_pDY6->oUS_Z2AlignM34Out = TRUE;
			m_pAJinAXL->Write_Output(6);
			m_nInitUnload1Case = 200;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 30000);
		}
		break;


	case 200:	// Load Initialize Complete
		if (!m_pDX6->iUS_Z1AlignS12In && m_pDX6->iUS_Z1AlignS12Out && !m_pDX6->iUS_Z1AlignM34In && m_pDX6->iUS_Z1AlignM34Out
			&& !m_pDX6->iUS_Z2AlignS12In && m_pDX6->iUS_Z2AlignS12Out && !m_pDX6->iUS_Z2AlignM34In && m_pDX6->iUS_Z2AlignM34Out) {
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD1, 5000);
		}
		break;
	}

	// 3.  (Error : 1310)
	if (m_pCommon->Over_LoopTime(INITIAL_UNLOAD1)) {
		m_pCommon->Show_Error(1200 + m_nInitUnload1Case);
		return FALSE;
	} else {
		return TRUE;
	}
}

// 4.  (Error : 1360)
BOOL CSequenceInit::Initial_Unload2Run()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitUnload2Case) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_UNLOAD2, 5000);
		break;

	case 110:
		pLogFile->Save_HandlerLog("[Initial Sequence - Unload2Run] start");
				
		m_nInitUnload2Case = 111;
		m_pCommon->Set_LoopTime(INITIAL_UNLOAD2, 5000);
		break;

	case 111:
			m_pDY6->oUS_UnloadSupport12In = TRUE;
			m_pDY6->oUS_UnloadSupport12Out = FALSE;
		
			m_pAJinAXL->Write_Output(6);
			m_nInitUnload2Case = 112;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD2, 5000);
		break;
	case 112:
		if (m_pDX6->iUS_UnloadSupport1In && !m_pDX6->iUS_UnloadSupport1Out && m_pDX6->iUS_UnloadSupport2In && !m_pDX6->iUS_UnloadSupport2Out) {
			m_nInitUnload2Case = 113;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD2, 5000);
		}
		break;
	case 113:
		if (1) {
			
			m_nInitUnload2Case = 200;
			m_pCommon->Set_LoopTime(INITIAL_UNLOAD2, 60000);
		}
		break;

	case 200:	// Load Initialize Complete
		if (1) {
		m_pCommon->Set_LoopTime(INITIAL_UNLOAD2, 5000);
		}
		break;
	}

	// 4.  (Error : 1360)
	if (m_pCommon->Over_LoopTime(INITIAL_UNLOAD2)) {
		m_pCommon->Show_Error(1250 + m_nInitUnload2Case);
		return FALSE;
	} else {
		return TRUE;
	}
}

// 5.  (Error : 1410)
BOOL CSequenceInit::Initial_InspectRun()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitInspectCase) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_INSPECT, 5000);
		break;

	case 110:
		pLogFile->Save_HandlerLog("[Initial Sequence - InspectRun] start");
				
		m_nInitInspectCase = 111;
		m_pCommon->Set_LoopTime(INITIAL_INSPECT, 5000);
		break;

	case 111:
			m_pAJinAXL->Home_Search(AX_INSPECTION_Z);
			m_nInitInspectCase = 112;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		break;
	case 112:
		if (m_pAJinAXL->Is_Home(AX_INSPECTION_Z) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_INSPECT, 1000)) break;
			m_pDY2->oCMPressUp = TRUE;
			m_pDY2->oCMPressDn = FALSE;
			m_pAJinAXL->Write_Output(2);

			if (gData.bUseCMPress)	m_nInitInspectCase = 115;
			else					m_nInitInspectCase = 113;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		}
		break;
	case 113:
		if (m_pAJinAXL->Is_Home(AX_INSPECTION_Z) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_INSPECT, 1000)) break;
			m_pCommon->Move_Position(AX_INSPECTION_Z, 0);
			m_nInitInspectCase = 114;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		}
		break;
	case 114:
		if (m_pCommon->Check_Position(AX_INSPECTION_Z, 0) ) {
			m_nInitInspectCase = 120;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		}
		break;
	case 115:
		if (m_pAJinAXL->Is_Home(AX_INSPECTION_Z) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_INSPECT, 1000)) break;
			m_pCommon->Move_Position(AX_INSPECTION_Z, 1);
			m_nInitInspectCase = 116;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		}
		break;
	case 116:
		if (m_pCommon->Check_Position(AX_INSPECTION_Z, 1) ) {
			m_nInitInspectCase = 117;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		}
		break;
	case 117:
		if (m_pDX2->iCMPressUp && !m_pDX2->iCMPressDn) {
			m_nInitInspectCase = 120;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		}
		break;

	case 120:
			m_pAJinAXL->Home_Search(AX_INSPECTION_A);
			m_nInitInspectCase = 121;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		break;
	case 121:
		if (m_pAJinAXL->Is_Home(AX_INSPECTION_A)) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_INSPECT, 1000)) break;
			m_pCommon->Move_Position(AX_INSPECTION_A, 0);
			m_nInitInspectCase = 122;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		}
		break;
	case 122:
		if (m_pCommon->Check_Position(AX_INSPECTION_A, 0)) {
			m_nInitInspectCase = 123;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		}
		break;
	case 123:
			m_pAJinAXL->Home_Search(AX_BARCODE_A);
			m_nInitInspectCase = 124;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		break;
	case 124:
		if (m_pAJinAXL->Is_Home(AX_BARCODE_A)) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_INSPECT, 1000)) break;
			m_pCommon->Move_Position(AX_BARCODE_A, 0);
			m_nInitInspectCase = 125;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 30000);
		}
		break;
	case 125:
		if (m_pCommon->Check_Position(AX_BARCODE_A, 0)) {
			m_nInitInspectCase = 200;
			m_pCommon->Set_LoopTime(INITIAL_INSPECT, 60000);
		}
		break;

	case 200:	// Load Initialize Complete
		m_pCommon->Set_LoopTime(INITIAL_INSPECT, 5000);
		break;
	}

	// 5.  (Error : 1410)
	if (m_pCommon->Over_LoopTime(INITIAL_INSPECT)) {
		m_pCommon->Show_Error(1300 + m_nInitInspectCase);
		return FALSE;
	} else {
		return TRUE;
	}
}

// 6.  (Error : 1510)
BOOL CSequenceInit::Initial_NGPickerRun()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitNGPickerCase) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 5000);
		break;

	case 110:
		pLogFile->Save_HandlerLog("[Initial Sequence - NGPickerRun] start");
				
		m_nInitNGPickerCase = 111;
		m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 5000);
		break;

	case 111:
			m_pDY3->oNGPicker1Open = TRUE;
			m_pDY3->oNGPicker1Close = FALSE;
			m_pDY3->oNGPicker2Open = TRUE;
			m_pDY3->oNGPicker2Close = FALSE;
			m_pDY3->oNGPicker3Open = TRUE;
			m_pDY3->oNGPicker3Close = FALSE;
#ifndef NG_PICKER_3
			m_pDY3->oNGPicker4Open = TRUE;
			m_pDY3->oNGPicker4Close = FALSE;
		#ifndef NG_PICKER_4
			m_pDY3->oNGPicker5Open = TRUE;
			m_pDY3->oNGPicker5Close = FALSE;
		#endif
#endif

			m_pDY3->oNGPicker1Up = TRUE;
			m_pDY3->oNGPicker1Down = FALSE;
			m_pDY3->oNGPicker2Up = TRUE;
			m_pDY3->oNGPicker2Down = FALSE;
			m_pDY3->oNGPicker3Up = TRUE;
			m_pDY3->oNGPicker3Down = FALSE;
#ifndef NG_PICKER_3
			m_pDY3->oNGPicker4Up = TRUE;
			m_pDY3->oNGPicker4Down = FALSE;
		#ifndef NG_PICKER_4
			m_pDY3->oNGPicker5Up = TRUE;
			m_pDY3->oNGPicker5Down = FALSE;
		#endif
#endif

			m_pAJinAXL->Write_Output(3);
			m_nInitNGPickerCase = 112;
			m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 60000);
		break;
	case 112:
#ifdef NG_PICKER_3
		if (m_pDX3->iNGPicker1Open && m_pDX3->iNGPicker2Open && m_pDX3->iNGPicker3Open)
#endif
#ifdef NG_PICKER_4
	if (m_pDX3->iNGPicker1Open && m_pDX3->iNGPicker2Open && m_pDX3->iNGPicker3Open && m_pDX3->iNGPicker4Open)
#endif
#ifdef NG_PICKER_5
		if (m_pDX3->iNGPicker1Open && m_pDX3->iNGPicker2Open && m_pDX3->iNGPicker3Open && m_pDX3->iNGPicker4Open && m_pDX3->iNGPicker5Open )
#endif
		{
			m_pAJinAXL->Home_Search(AX_NG_PICKER_Z);
			m_nInitNGPickerCase = 113;
			m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 60000);
		}
		break;
	case 113:
#ifdef NG_PICKER_3
		if (m_pDX3->iNGPicker1Up && m_pDX3->iNGPicker2Up && m_pDX3->iNGPicker3Up &&
			!m_pDX3->iNGPicker1Down && !m_pDX3->iNGPicker2Down && !m_pDX3->iNGPicker3Down )
#endif
#ifdef NG_PICKER_4
		if (m_pDX3->iNGPicker1Up && m_pDX3->iNGPicker2Up && m_pDX3->iNGPicker3Up && m_pDX3->iNGPicker4Up &&  
			!m_pDX3->iNGPicker1Down && !m_pDX3->iNGPicker2Down && !m_pDX3->iNGPicker3Down && !m_pDX3->iNGPicker4Down )
#endif
#ifdef NG_PICKER_5
		if (m_pDX3->iNGPicker1Up && m_pDX3->iNGPicker2Up && m_pDX3->iNGPicker3Up && m_pDX3->iNGPicker4Up && m_pDX3->iNGPicker5Up && 
			!m_pDX3->iNGPicker1Down && !m_pDX3->iNGPicker2Down && !m_pDX3->iNGPicker3Down && !m_pDX3->iNGPicker4Down && !m_pDX3->iNGPicker5Down )
#endif
		{
			m_nInitNGPickerCase = 114;
			m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 60000);
		}
		break;
	case 114:
#ifdef NG_PICKER_3
		if((!m_pEquipData->bUseVisionInspect) ||
			(!m_pDX3->iNGPicker1CMCheck && !m_pDX3->iNGPicker2CMCheck && !m_pDX3->iNGPicker3CMCheck))
#endif
#ifdef NG_PICKER_4
		if((!m_pEquipData->bUseVisionInspect) ||
		   (!m_pDX3->iNGPicker1CMCheck && !m_pDX3->iNGPicker2CMCheck && !m_pDX3->iNGPicker3CMCheck && !m_pDX3->iNGPicker4CMCheck ))
#endif
#ifdef NG_PICKER_5
		if((!m_pEquipData->bUseVisionInspect) ||
		   (!m_pDX3->iNGPicker1CMCheck && !m_pDX3->iNGPicker2CMCheck && !m_pDX3->iNGPicker3CMCheck && !m_pDX3->iNGPicker4CMCheck && !m_pDX3->iNGPicker5CMCheck))
#endif
		{
			m_nInitNGPickerCase = 150;
			m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 60000);
		}
		break;

	case 150:
		if (m_pAJinAXL->Is_Home(AX_NG_PICKER_Z) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_NGPICKER, 1000)) break;
			m_pCommon->Move_Position(AX_NG_PICKER_Z, 0);
			m_nInitNGPickerCase = 151;
			m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 30000);
		}
		break;
	case 151:
		if (m_pCommon->Check_Position(AX_NG_PICKER_Z, 0) ) {
			m_pAJinAXL->Home_Search(AX_NG_PICKER_X);
			m_nInitNGPickerCase = 152;
			m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 60000);
		}
		break;
	case 152:
		if (m_pAJinAXL->Is_Home(AX_NG_PICKER_X) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_NGPICKER, 1000)) break;
			m_pCommon->Move_Position(AX_NG_PICKER_X, 0);
			m_nInitNGPickerCase = 153;
			m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 60000);
		}
		break;
	case 153:
		if (m_pCommon->Check_Position(AX_NG_PICKER_X, 0)) {
			m_nInitNGPickerCase = 200;
			m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 60000);
		}
		break;

	case 200:	// Load Initialize Complete
		m_pCommon->Set_LoopTime(INITIAL_NGPICKER, 5000);
		break;
	}

	// 6.  (Error : 1510)
	if (m_pCommon->Over_LoopTime(INITIAL_NGPICKER)) {
		m_pCommon->Show_Error(1400 + m_nInitNGPickerCase);
		return FALSE;
	} else {
		return TRUE;
	}
}

// 7.  (Error : 1610)
BOOL CSequenceInit::Initial_GDPickerRun()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitGDPickerCase) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 5000);
		break;

	case 110:
		pLogFile->Save_HandlerLog("[Initial Sequence - GDPickerRun] start");
				
		m_nInitGDPickerCase = 111;
		m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 5000);
		break;

	case 111:
			m_pDY4->oGoodPicker1Open = TRUE;
			m_pDY4->oGoodPicker1Close = FALSE;
			m_pDY4->oGoodPicker2Open = TRUE;
			m_pDY4->oGoodPicker2Close = FALSE;
			m_pDY4->oGoodPicker3Open = TRUE;
			m_pDY4->oGoodPicker3Close = FALSE;
			m_pDY4->oGoodPicker4Open = TRUE;
			m_pDY4->oGoodPicker4Close = FALSE;
			m_pDY4->oGoodPicker5Open = TRUE;
			m_pDY4->oGoodPicker5Close = FALSE;

			m_pDY4->oGoodPicker1Up = TRUE;
			m_pDY4->oGoodPicker1Down = FALSE;
			m_pDY4->oGoodPicker2Up = TRUE;
			m_pDY4->oGoodPicker2Down = FALSE;
			m_pDY4->oGoodPicker3Up = TRUE;
			m_pDY4->oGoodPicker3Down = FALSE;
#ifdef PICKER_4
			m_pDY4->oGoodPicker4Up = TRUE;
			m_pDY4->oGoodPicker4Down = FALSE;
#endif
#ifdef PICKER_5
			m_pDY4->oGoodPicker4Up = TRUE;
			m_pDY4->oGoodPicker4Down = FALSE;
			m_pDY4->oGoodPicker5Up = TRUE;
			m_pDY4->oGoodPicker5Down = FALSE;
#endif
#ifdef PICKER_6
			m_pDY4->oGoodPicker4Up = TRUE;
			m_pDY4->oGoodPicker4Down = FALSE;
			m_pDY4->oGoodPicker5Up = TRUE;
			m_pDY4->oGoodPicker5Down = FALSE;

			m_pDY4->oGoodPicker6Open = TRUE;
			m_pDY4->oGoodPicker6Close = FALSE;
			m_pDY4->oGoodPicker6Up = TRUE;
			m_pDY4->oGoodPicker6Down = FALSE;
#endif

			m_pAJinAXL->Write_Output(4);
			m_nInitGDPickerCase = 112;
			m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 60000);
		break;
	case 112:
#ifdef PICKER_3
		if (m_pDX4->iGoodPicker1Open && m_pDX4->iGoodPicker2Open && m_pDX4->iGoodPicker3Open)
#endif
#ifdef PICKER_4
			if (m_pDX4->iGoodPicker1Open && m_pDX4->iGoodPicker2Open && m_pDX4->iGoodPicker3Open && 
				m_pDX4->iGoodPicker4Open )
#endif
#ifdef PICKER_5
		if (m_pDX4->iGoodPicker1Open && m_pDX4->iGoodPicker2Open && m_pDX4->iGoodPicker3Open && 
			m_pDX4->iGoodPicker4Open && m_pDX4->iGoodPicker5Open )
#endif
#ifdef PICKER_6
		if (m_pDX4->iGoodPicker1Open && m_pDX4->iGoodPicker2Open && m_pDX4->iGoodPicker3Open && 
			m_pDX4->iGoodPicker4Open && m_pDX4->iGoodPicker5Open && m_pDX4->iGoodPicker6Open)
#endif
		{
			m_pAJinAXL->Home_Search(AX_GOOD_PICKER_Z);
			m_nInitGDPickerCase = 113;
			m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 60000);
		}
		break;
	case 113:
#ifdef PICKER_3
		if (m_pDX4->iGoodPicker1Up && m_pDX4->iGoodPicker2Up && m_pDX4->iGoodPicker3Up && 
			!m_pDX4->iGoodPicker1Down && !m_pDX4->iGoodPicker2Down && !m_pDX4->iGoodPicker3Down )
#endif
#ifdef PICKER_4
			if (m_pDX4->iGoodPicker1Up && m_pDX4->iGoodPicker2Up && m_pDX4->iGoodPicker3Up && 
				m_pDX4->iGoodPicker4Up && 
				!m_pDX4->iGoodPicker1Down && !m_pDX4->iGoodPicker2Down && !m_pDX4->iGoodPicker3Down && 
				!m_pDX4->iGoodPicker4Down)
#endif
#ifdef PICKER_5
		if (m_pDX4->iGoodPicker1Up && m_pDX4->iGoodPicker2Up && m_pDX4->iGoodPicker3Up && 
			m_pDX4->iGoodPicker4Up && m_pDX4->iGoodPicker5Up &&
			!m_pDX4->iGoodPicker1Down && !m_pDX4->iGoodPicker2Down && !m_pDX4->iGoodPicker3Down && 
			!m_pDX4->iGoodPicker4Down && !m_pDX4->iGoodPicker5Down )
#endif
#ifdef PICKER_6
		if (m_pDX4->iGoodPicker1Up && m_pDX4->iGoodPicker2Up && m_pDX4->iGoodPicker3Up && 
			m_pDX4->iGoodPicker4Up && m_pDX4->iGoodPicker5Up && m_pDX4->iGoodPicker6Up &&
			!m_pDX4->iGoodPicker1Down && !m_pDX4->iGoodPicker2Down && !m_pDX4->iGoodPicker3Down && 
			!m_pDX4->iGoodPicker4Down && !m_pDX4->iGoodPicker5Down && !m_pDX4->iGoodPicker6Down)
#endif
		{
			m_nInitGDPickerCase = 114;
			m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 60000);
		}
		break;
	case 114:
#ifdef PICKER_3
		if((!m_pEquipData->bUseVisionInspect) ||
		   (!m_pDX4->iGoodPicker1CMCheck && !m_pDX4->iGoodPicker2CMCheck && !m_pDX4->iGoodPicker3CMCheck ))
#endif
#ifdef PICKER_4
		   if((!m_pEquipData->bUseVisionInspect) ||
			   (!m_pDX4->iGoodPicker1CMCheck && !m_pDX4->iGoodPicker2CMCheck && !m_pDX4->iGoodPicker3CMCheck && 
			   !m_pDX4->iGoodPicker4CMCheck))
#endif
#ifdef PICKER_5
		if((!m_pEquipData->bUseVisionInspect) ||
		   (!m_pDX4->iGoodPicker1CMCheck && !m_pDX4->iGoodPicker2CMCheck && !m_pDX4->iGoodPicker3CMCheck && 
			!m_pDX4->iGoodPicker4CMCheck && !m_pDX4->iGoodPicker5CMCheck ))
#endif
#ifdef PICKER_6
		if((!m_pEquipData->bUseVisionInspect) ||
		   (!m_pDX4->iGoodPicker1CMCheck && !m_pDX4->iGoodPicker2CMCheck && !m_pDX4->iGoodPicker3CMCheck && 
			!m_pDX4->iGoodPicker4CMCheck && !m_pDX4->iGoodPicker5CMCheck && !m_pDX4->iGoodPicker6CMCheck))
#endif
		{
			m_nInitGDPickerCase = 150;
			m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 60000);
		}
		break;

	case 150:
		if (m_pAJinAXL->Is_Home(AX_GOOD_PICKER_Z) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_GDPICKER, 1000)) break;
			m_pCommon->Move_Position(AX_GOOD_PICKER_Z, 0);
			m_nInitGDPickerCase = 151;
			m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 30000);
		}
		break;
	case 151:
		if (m_pCommon->Check_Position(AX_GOOD_PICKER_Z, 0) ) {
			m_pAJinAXL->Home_Search(AX_GOOD_PICKER_Y);
			m_nInitGDPickerCase = 152;
			m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 60000);
		}
		break;
	case 152:
		if (m_pAJinAXL->Is_Home(AX_GOOD_PICKER_Y) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_GDPICKER, 1000)) break;
			m_pCommon->Move_Position(AX_GOOD_PICKER_Y, 0);
			m_nInitGDPickerCase = 153;
			m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 60000);
		}
		break;
	case 153:
		if (m_pCommon->Check_Position(AX_GOOD_PICKER_Y, 0)) {
			m_nInitGDPickerCase = 200;
			m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 60000);
		}
		break;

	case 200:	// Load Initialize Complete
		m_pCommon->Set_LoopTime(INITIAL_GDPICKER, 5000);
		break;
	}

	// 7.  (Error : 1610)
	if (m_pCommon->Over_LoopTime(INITIAL_GDPICKER)) {
		m_pCommon->Show_Error(1500 + m_nInitGDPickerCase);
		return FALSE;
	} else {
		return TRUE;
	}
}
			 
// 8.  (Error : 1710)
BOOL CSequenceInit::Initial_LDPickerRun()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitLDPickerCase) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 5000);
		break;

	case 110:
		pLogFile->Save_HandlerLog("[Initial Sequence - LDPickerRun] start");
				
		m_nInitLDPickerCase = 111;
		m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 5000);
		break;

	case 111:
			m_pDY2->oMLPicker1Open = TRUE;
			m_pDY2->oMLPicker1Close = FALSE;
			m_pDY2->oMLPicker2Open = TRUE;
			m_pDY2->oMLPicker2Close = FALSE;
			m_pDY2->oMLPicker3Open = TRUE;
			m_pDY2->oMLPicker3Close = FALSE;
#ifdef PICKER_4
			m_pDY2->oMLPicker4Open = TRUE;
			m_pDY2->oMLPicker4Close = FALSE;

#endif
#ifdef PICKER_5
			m_pDY2->oMLPicker4Open = TRUE;
			m_pDY2->oMLPicker4Close = FALSE;
			m_pDY2->oMLPicker5Open = TRUE;
			m_pDY2->oMLPicker5Close = FALSE;
#endif
#ifdef PICKER_6
			m_pDY2->oMLPicker4Open = TRUE;
			m_pDY2->oMLPicker4Close = FALSE;
			m_pDY2->oMLPicker5Open = TRUE;
			m_pDY2->oMLPicker5Close = FALSE;
			m_pDY2->oMLPicker6Open = TRUE;
			m_pDY2->oMLPicker6Close = FALSE;
#endif
			m_pAJinAXL->Write_Output(2);
			m_nInitLDPickerCase = 112;
			m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 5000);
		break;
	case 112:
#ifdef PICKER_3
		if (m_pDX2->iMLPicker1Open && m_pDX2->iMLPicker2Open && m_pDX2->iMLPicker3Open )
#endif
#ifdef PICKER_4
			if (m_pDX2->iMLPicker1Open && m_pDX2->iMLPicker2Open && m_pDX2->iMLPicker3Open && 
				m_pDX2->iMLPicker4Open)
#endif
#ifdef PICKER_5
		if (m_pDX2->iMLPicker1Open && m_pDX2->iMLPicker2Open && m_pDX2->iMLPicker3Open && 
			m_pDX2->iMLPicker4Open && m_pDX2->iMLPicker5Open )
#endif
#ifdef PICKER_6
		if (m_pDX2->iMLPicker1Open && m_pDX2->iMLPicker2Open && m_pDX2->iMLPicker3Open && 
			m_pDX2->iMLPicker4Open && m_pDX2->iMLPicker5Open && m_pDX2->iMLPicker6Open)
#endif
		{
			m_pAJinAXL->Home_Search(AX_LOAD_PICKER_Z);
			m_nInitLDPickerCase = 150;
			m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 60000);
		}
		break;
	case 113:
#ifdef PICKER_3
		if((!m_pEquipData->bUseVisionInspect) ||
		   (!m_pDX2->iMLPicker1CMCheck && !m_pDX2->iMLPicker2CMCheck && !m_pDX2->iMLPicker3CMCheck ))
#endif
#ifdef PICKER_4
		   if((!m_pEquipData->bUseVisionInspect) ||
			   (!m_pDX2->iMLPicker1CMCheck && !m_pDX2->iMLPicker2CMCheck && !m_pDX2->iMLPicker3CMCheck && 
			   !m_pDX2->iMLPicker4CMCheck ))
#endif
#ifdef PICKER_5
		if((!m_pEquipData->bUseVisionInspect) ||
		   (!m_pDX2->iMLPicker1CMCheck && !m_pDX2->iMLPicker2CMCheck && !m_pDX2->iMLPicker3CMCheck && 
			!m_pDX2->iMLPicker4CMCheck && !m_pDX2->iMLPicker5CMCheck))
#endif
#ifdef PICKER_6
		if((!m_pEquipData->bUseVisionInspect) ||
			(!m_pDX2->iMLPicker1CMCheck && !m_pDX2->iMLPicker2CMCheck && !m_pDX2->iMLPicker3CMCheck && 
			!m_pDX2->iMLPicker4CMCheck && !m_pDX2->iMLPicker5CMCheck && !m_pDX2->iMLPicker6CMCheck))
#endif
		{
			m_nInitLDPickerCase = 150;
			m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 5000);
		}
		break;

	case 150:
		if (m_pAJinAXL->Is_Home(AX_LOAD_PICKER_Z) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_LDPICKER, 1000)) break;
			m_pCommon->Move_Position(AX_LOAD_PICKER_Z, 0);
			m_nInitLDPickerCase = 151;
			m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 30000);
		}
		break;
	case 151:
		if (m_pCommon->Check_Position(AX_LOAD_PICKER_Z, 0) ) {
			m_nInitLDPickerCase = 152;
			m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 90000);
		}
		break;
	case 152:
		if ((m_pCommon->Check_Position(AX_LOAD_TRAY_Z1, 0) || m_pCommon->Check_Position(AX_LOAD_TRAY_Z1, 1)) &&
			(m_pCommon->Check_Position(AX_LOAD_TRAY_Z2, 0) || m_pCommon->Check_Position(AX_LOAD_TRAY_Z2, 1)) ) {
			m_pAJinAXL->Home_Search(AX_LOAD_PICKER_Y2);
			m_nInitLDPickerCase = 153;
			m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 30000);
		}
		break;
	case 153:
		if (m_pAJinAXL->Is_Home(AX_LOAD_PICKER_Y2) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_LDPICKER, 1000)) break;
			m_pCommon->Move_Position(AX_LOAD_PICKER_Y2, 0);
			m_nInitLDPickerCase = 154;
			m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 90000);
		}
		break;
	case 154:
		if ((m_pCommon->Check_Position(AX_LOAD_TRAY_Z1, 0) || m_pCommon->Check_Position(AX_LOAD_TRAY_Z1, 1)) &&
			(m_pCommon->Check_Position(AX_LOAD_TRAY_Z2, 0) || m_pCommon->Check_Position(AX_LOAD_TRAY_Z2, 1)) ) {
			m_pAJinAXL->Home_Search(AX_LOAD_PICKER_Y1);
			m_nInitLDPickerCase = 155;
			m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 30000);
		}
		break;
	case 155:
		if (m_pAJinAXL->Is_Home(AX_LOAD_PICKER_Y1) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_LDPICKER, 1000)) break;
			m_pCommon->Move_Position(AX_LOAD_PICKER_Y1, 0);
			m_nInitLDPickerCase = 156;
			m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 30000);
		}
		break;
	case 156:
		if (m_pCommon->Check_Position(AX_LOAD_PICKER_Y1, 0) && m_pCommon->Check_Position(AX_LOAD_PICKER_Y2, 0) ) {
			m_nInitLDPickerCase = 200;
			m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 30000);
		}
		break;

	case 200:	// Load Initialize Complete
		m_pCommon->Set_LoopTime(INITIAL_LDPICKER, 5000);
		break;
	}

	// 8.  (Error : 1710)
	if (m_pCommon->Over_LoopTime(INITIAL_LDPICKER)) {
		m_pCommon->Show_Error(1600 + m_nInitLDPickerCase);
		return FALSE;
	} else {
		return TRUE;
	}
}

// 9.  (Error : 1810)
BOOL CSequenceInit::Initial_ULPickerRun()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitULPickerCase) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 5000);
		break;

	case 110:
		pLogFile->Save_HandlerLog("[Initial Sequence - ULPickerRun] start");
				
		m_nInitULPickerCase = 111;
		m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 5000);
		break;

	case 111:
			m_pDY5->oMUPicker1Open = TRUE;
			m_pDY5->oMUPicker1Close = FALSE;
			m_pDY5->oMUPicker2Open = TRUE;
			m_pDY5->oMUPicker2Close = FALSE;
			m_pDY5->oMUPicker3Open = TRUE;
			m_pDY5->oMUPicker3Close = FALSE;
#ifdef PICKER_4
			m_pDY5->oMUPicker4Open = TRUE;
			m_pDY5->oMUPicker4Close = FALSE;
			
#endif
#ifdef PICKER_5
			m_pDY5->oMUPicker4Open = TRUE;
			m_pDY5->oMUPicker4Close = FALSE;
			m_pDY5->oMUPicker5Open = TRUE;
			m_pDY5->oMUPicker5Close = FALSE;
#endif
#ifdef PICKER_6
			m_pDY5->oMUPicker4Open = TRUE;
			m_pDY5->oMUPicker4Close = FALSE;
			m_pDY5->oMUPicker5Open = TRUE;
			m_pDY5->oMUPicker5Close = FALSE;
			m_pDY5->oMUPicker6Open = TRUE;
			m_pDY5->oMUPicker6Close = FALSE;
#endif
			m_pAJinAXL->Write_Output(5);
			m_nInitULPickerCase = 112;
			m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 60000);
		break;
	case 112:
#ifdef PICKER_3
		if (m_pDX5->iMUPicker1Open && m_pDX5->iMUPicker2Open && m_pDX5->iMUPicker3Open)
#endif
#ifdef PICKER_4
			if (m_pDX5->iMUPicker1Open && m_pDX5->iMUPicker2Open && m_pDX5->iMUPicker3Open && 
				m_pDX5->iMUPicker4Open )
#endif
#ifdef PICKER_5
		if (m_pDX5->iMUPicker1Open && m_pDX5->iMUPicker2Open && m_pDX5->iMUPicker3Open && 
			m_pDX5->iMUPicker4Open && m_pDX5->iMUPicker5Open )
#endif
#ifdef PICKER_6
		if (m_pDX5->iMUPicker1Open && m_pDX5->iMUPicker2Open && m_pDX5->iMUPicker3Open && 
			m_pDX5->iMUPicker4Open && m_pDX5->iMUPicker5Open && m_pDX5->iMUPicker6Open)
#endif
		{
			m_pAJinAXL->Home_Search(AX_UNLOAD_PICKER_Z);
			m_nInitULPickerCase = 113;
			m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 60000);
		}
		break;
	case 113:
#ifdef PICKER_3
		if((!m_pEquipData->bUseVisionInspect) ||
		   (!m_pDX5->iMUPicker1CMCheck && !m_pDX5->iMUPicker2CMCheck && !m_pDX5->iMUPicker3CMCheck ))
#endif
#ifdef PICKER_4
		   if((!m_pEquipData->bUseVisionInspect) ||
			   (!m_pDX5->iMUPicker1CMCheck && !m_pDX5->iMUPicker2CMCheck && !m_pDX5->iMUPicker3CMCheck && 
			   !m_pDX5->iMUPicker4CMCheck))
#endif
#ifdef PICKER_5
		if((!m_pEquipData->bUseVisionInspect) ||
		   (!m_pDX5->iMUPicker1CMCheck && !m_pDX5->iMUPicker2CMCheck && !m_pDX5->iMUPicker3CMCheck && 
			!m_pDX5->iMUPicker4CMCheck && !m_pDX5->iMUPicker5CMCheck ))
#endif
#ifdef PICKER_6
		if((!m_pEquipData->bUseVisionInspect) ||
		   (!m_pDX5->iMUPicker1CMCheck && !m_pDX5->iMUPicker2CMCheck && !m_pDX5->iMUPicker3CMCheck && 
			!m_pDX5->iMUPicker4CMCheck && !m_pDX5->iMUPicker5CMCheck && !m_pDX5->iMUPicker6CMCheck))
#endif
		{
			m_nInitULPickerCase = 150;
			m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 10000);
		}
		break;

	case 150:
		if (m_pAJinAXL->Is_Home(AX_UNLOAD_PICKER_Z) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_ULPICKER, 1000)) break;
			m_pCommon->Move_Position(AX_UNLOAD_PICKER_Z, 0);
			m_nInitULPickerCase = 151;
			m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 30000);
		}
		break;
	case 151:
		if (m_pCommon->Check_Position(AX_UNLOAD_PICKER_Z, 0) ) {
			m_nInitULPickerCase = 152;
			m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 90000);
		}
		break;
	case 152:
		if ((m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z1, 0) || m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z1, 1)) &&
			(m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z2, 0) || m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z2, 1)) ) {
			m_pAJinAXL->Home_Search(AX_UNLOAD_PICKER_X2);
			m_nInitULPickerCase = 153;
			m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 30000);
		}
		break;
	case 153:
		if (m_pAJinAXL->Is_Home(AX_UNLOAD_PICKER_X2) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_ULPICKER, 1000)) break;
			m_pCommon->Move_Position(AX_UNLOAD_PICKER_X2, 0);
			m_nInitULPickerCase = 154;
			m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 90000);
		}
		break;
	case 154:
		if ((m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z1, 0) || m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z1, 1)) &&
			(m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z2, 0) || m_pCommon->Check_Position(AX_UNLOAD_TRAY_Z2, 1)) ) {
			m_pAJinAXL->Home_Search(AX_UNLOAD_PICKER_X1);
			m_nInitULPickerCase = 155;
			m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 30000);
		}
		break;
	case 155:
		if (m_pAJinAXL->Is_Home(AX_UNLOAD_PICKER_X1) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_ULPICKER, 1000)) break;
			m_pCommon->Move_Position(AX_UNLOAD_PICKER_X1, 0);
			m_nInitULPickerCase = 156;
			m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 30000);
		}
		break;
	case 156:
		if (m_pCommon->Check_Position(AX_UNLOAD_PICKER_X1, 0) && m_pCommon->Check_Position(AX_UNLOAD_PICKER_X2, 0) ) {
			m_nInitULPickerCase = 200;
			m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 30000);
		}
		break;

	case 200:	// Load Initialize Complete
		m_pCommon->Set_LoopTime(INITIAL_ULPICKER, 5000);
		break;
	}

	// 9.  (Error : 1810)
	if (m_pCommon->Over_LoopTime(INITIAL_ULPICKER)) {
		m_pCommon->Show_Error(1700 + m_nInitULPickerCase);
		return FALSE;
	} else {
		return TRUE;
	}
}


// 10. (Error : 1910)
BOOL CSequenceInit::Initial_IndexTRun()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitIndexTCase) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_INDEXT, 5000);
		break;

	case 110:
		if(m_nInitLDPickerCase < 151) return TRUE;
		if(m_nInitULPickerCase < 151) return TRUE;
		if(m_nInitNGPickerCase < 151) return TRUE;
		if(m_nInitGDPickerCase < 151) return TRUE;
		if(m_nInitInspectCase < 113) return TRUE;

		pLogFile->Save_HandlerLog("[Initial Sequence - IndexTRun] start");
				
		m_nInitIndexTCase = 111;
		m_pCommon->Set_LoopTime(INITIAL_INDEXT, 5000);
		break;

	case 111:
			m_pDY2->oInspCMAlign1In = TRUE;
			m_pDY2->oInspCMAlign1Out = FALSE;
			m_pDY2->oInspCMAlign2In = TRUE;
			m_pDY2->oInspCMAlign2Out = FALSE;
			m_pDY2->oInspCMAlign3In = TRUE;
			m_pDY2->oInspCMAlign3Out = FALSE;
			m_pDY2->oInspCMAlign4In = TRUE;
			m_pDY2->oInspCMAlign4Out = FALSE;
			m_pAJinAXL->Write_Output(2);

			Sleep(500);

			m_pDY3->oInspVacuumPad1On = FALSE;
			m_pDY3->oInspVacuumPad2On = FALSE;
			m_pDY3->oInspVacuumPad3On = FALSE;
			m_pDY3->oInspVacuumPad4On = FALSE;
			m_pDY3->oInspVacuumPad5On = FALSE;
			m_pDY3->oInspVacuumPad6On = FALSE;
			m_pAJinAXL->Write_Output(3);

			Sleep(500);

			m_pDY5->oNGVacuumPad1On = FALSE;
			m_pDY5->oNGVacuumPad2On = FALSE;
			m_pDY5->oNGVacuumPad3On = FALSE;
			m_pDY5->oNGVacuumPad4On = FALSE;
			m_pDY5->oNGVacuumPad5On = FALSE;
			m_pDY5->oNGVacuumPad6On = FALSE;

			m_pDY5->oGoodVacuumPad1On = FALSE;
			m_pDY5->oGoodVacuumPad2On = FALSE;
			m_pDY5->oGoodVacuumPad3On = FALSE;
			m_pDY5->oGoodVacuumPad4On = FALSE;
			m_pDY5->oGoodVacuumPad5On = FALSE;
			m_pDY5->oGoodVacuumPad6On = FALSE;
			m_pAJinAXL->Write_Output(5);

			m_nInitIndexTCase = 112;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 60000);
		break;
	case 112:
		if (m_pDX2->iInspCMAlign1In && !m_pDX2->iInspCMAlign1Out && m_pDX2->iInspCMAlign2In && !m_pDX2->iInspCMAlign2Out && 
			m_pDX2->iInspCMAlign3In && !m_pDX2->iInspCMAlign3Out && m_pDX2->iInspCMAlign4In && !m_pDX2->iInspCMAlign4Out ) {
			if (!m_pDX3->iInspVacuumPad1Check && !m_pDX3->iInspVacuumPad2Check && !m_pDX3->iInspVacuumPad3Check && 
				!m_pDX3->iInspVacuumPad4Check && !m_pDX3->iInspVacuumPad5Check  ) {
				m_pDY2->oInspVacuumUp = FALSE;
				m_pDY2->oInspVacuumDown = TRUE;
				m_pAJinAXL->Write_Output(2);
				m_nInitIndexTCase = 113;
				m_pCommon->Set_LoopTime(INITIAL_INDEXT, 5000);
			}
		}
		break;
	case 113:
		if (!m_pDX2->iInspVacuumUp && m_pDX2->iInspVacuumDown ) {
			m_nInitIndexTCase = 114;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 5000);
		}
		break;

	case 114:
		if (!m_pDX5->iNGVacuumPad1Check && !m_pDX5->iNGVacuumPad2Check && !m_pDX5->iNGVacuumPad3Check && 
			!m_pDX5->iNGVacuumPad4Check && !m_pDX5->iNGVacuumPad5Check ) {
			m_pDY5->oNGVacuumUp = FALSE;
			m_pDY5->oNGVacuumDown = TRUE;
			m_pAJinAXL->Write_Output(5);

			m_nInitIndexTCase = 115;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 5000);
		}
		break;
	case 115:
		if (gData.bUseNGVacuum==FALSE || (!m_pDX5->iNGVacuumUp && m_pDX5->iNGVacuumDown)) {
			m_nInitIndexTCase = 116;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 5000);
		}
		break;

	case 116:
		if (!m_pDX5->iGoodVacuumPad1Check && !m_pDX5->iGoodVacuumPad2Check && !m_pDX5->iGoodVacuumPad3Check && 
			!m_pDX5->iGoodVacuumPad4Check && !m_pDX5->iGoodVacuumPad5Check  ) {
			m_pDY5->oGoodVacuumUp = FALSE;
			m_pDY5->oGoodVacuumDown = TRUE;
			m_pAJinAXL->Write_Output(5);

			m_nInitIndexTCase = 117;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 5000);
		}
		break;
	case 117:
		if (gData.bUseGDVacuum==FALSE || (!m_pDX5->iGoodVacuumUp && m_pDX5->iGoodVacuumDown)) {
			m_nInitIndexTCase = 130;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 60000);
		}
		break;

	case 130:
		if (m_pCommon->Check_Position(AX_LOAD_PICKER_Z, 0) && (m_pCommon->Check_Position(AX_NG_PICKER_Z, 0) || m_pCommon->Check_Position(AX_NG_PICKER_Z, 1)) &&
			m_pCommon->Check_Position(AX_GOOD_PICKER_Z, 0) && m_pCommon->Check_Position(AX_UNLOAD_PICKER_Z, 0) &&
			(m_pCommon->Check_Position(AX_INSPECTION_Z, 0) || m_pCommon->Check_Position(AX_INSPECTION_Z, 1)) ) {
			if ((gData.bUseCMPress && m_pDX2->iCMPressUp && !m_pDX2->iCMPressDn) || !gData.bUseCMPress) {
				m_pAJinAXL->Home_Search(AX_INDEX_R);
				m_nInitIndexTCase = 131;
				m_pCommon->Set_LoopTime(INITIAL_INDEXT, 60000);
			}
		}
		break;
	case 131:
		if (m_pAJinAXL->Is_Home(AX_INDEX_R) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_INDEXT, 1000)) break;
			m_nInitIndexTCase = 132;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 60000);
		}
		break;

	case 132:
		if (gData.nIndexPos == 1) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_INDEXT, 2000)) break;
			m_nInitIndexTCase = 140;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 60000);
		} else {
			if ((gData.bUseCMPress && m_pDX2->iCMPressUp && !m_pDX2->iCMPressDn) || !gData.bUseCMPress) {
				m_pCommon->Move_Position(AX_INDEX_R, 0);
				m_nInitIndexTCase = 133;
				m_pCommon->Set_LoopTime(INITIAL_INDEXT, 60000);
			}
		}
		break;
	case 133:
		if (m_pCommon->Check_Position(AX_INDEX_R, 0) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_INDEXT, 300)) break;
			m_nInitIndexTCase = 132;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 60000);
		}
		break;

	case 140:
			m_pDY2->oInspCMAlign1In = FALSE;
			m_pDY2->oInspCMAlign1Out = TRUE;
			m_pAJinAXL->Write_Output(2);
			m_nInitIndexTCase = 141;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 60000);
		break;
	case 141:
		if (!m_pDX2->iInspCMAlign1In && m_pDX2->iInspCMAlign1Out ) {
			m_nInitIndexTCase = 200;
			m_pCommon->Set_LoopTime(INITIAL_INDEXT, 60000);
		}
		break;

	case 200:	// Load Initialize Complete
		m_pCommon->Set_LoopTime(INITIAL_INDEXT, 5000);
		break;
	}

	// 10. (Error : 1910)
	if (m_pCommon->Over_LoopTime(INITIAL_INDEXT)) {
		m_pCommon->Show_Error(1800 + m_nInitIndexTCase);
		return FALSE;
	} else {
		return TRUE;
	}
}
		
// 11. (Error : 1960)
BOOL CSequenceInit::Initial_NGTrayRun()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	switch (m_nInitNGTrayCase) {
	case 100:
		m_pCommon->Set_LoopTime(INITIAL_NGTRAY, 5000);
		break;

	case 110:
		if(m_nInitNGPickerCase < 151) return TRUE;
		pLogFile->Save_HandlerLog("[Initial Sequence - NGTrayRun] start");
				
		m_nInitNGTrayCase = 111;
		m_pCommon->Set_LoopTime(INITIAL_NGTRAY, 60000);
		break;

	case 111:
		if (m_pCommon->Check_Position(AX_NG_PICKER_Z, 0) ) {
			m_pAJinAXL->Home_Search(AX_NG_STAGE_Y);
			m_nInitNGTrayCase = 112;
			m_pCommon->Set_LoopTime(INITIAL_NGTRAY, 60000);
		}
		break;
	case 112:
		if (m_pAJinAXL->Is_Home(AX_NG_STAGE_Y) ) {
			if (!m_pCommon->Delay_LoopTime(INITIAL_NGTRAY, 1000)) break;
			m_pCommon->Move_Position(AX_NG_STAGE_Y, 0);
			m_nInitNGTrayCase = 113;
			m_pCommon->Set_LoopTime(INITIAL_NGTRAY, 60000);
		}
		break;
	case 113:
		if (m_pCommon->Check_Position(AX_NG_STAGE_Y, 0) ) {
			gData.nNGTrayPos = 0;
			m_nInitNGTrayCase = 200;
			m_pCommon->Set_LoopTime(INITIAL_NGTRAY, 60000);
		}
		break;

	case 200:	// Load Initialize Complete
		m_pCommon->Set_LoopTime(INITIAL_NGTRAY, 5000);
		break;
	}

	// 11. (Error : 1960)
	if (m_pCommon->Over_LoopTime(INITIAL_NGTRAY)) {
		m_pCommon->Show_Error(1850 + m_nInitNGTrayCase);
		return FALSE;
	} else {
		return TRUE;
	}
}
		 
BOOL CSequenceInit::Initial_TestRun()
{
/*
	switch (m_nInitTestCase) {
	case 100:
			m_nInitTestCase = 101;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 1000000);
		break;
	case 101:
			m_pAJinAXL->Home_Search(AX_INDEX_R);
			m_nInitTestCase = 102;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 60000);
		break;
	case 102:
		if (m_pAJinAXL->Is_Home(AX_INDEX_R) ) {
			m_nInitTestCase = 110;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 60000);
		}
		break;

	case 110:
		gData.nTotalCount++;
		m_nInitMainCase = gData.nTotalCount;
		if (gData.nTotalCount > 50) {
			m_nInitTestCase = 115;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 1000);
		} else {
			m_pCommon->Move_Position(AX_INDEX_R, 0);
			m_nInitTestCase = 112;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 60000);
		}
		break;
	case 112:
		if (m_pCommon->Check_Position(AX_INDEX_R, 0) ) {
			m_nInitTestCase = 110;
			m_pCommon->Set_LoopTime(INITIAL_MAIN, 60000);
		}
		break;

	case 115:
		gData.nTotalCount = 0;
		m_nInitTestCase = 100;
		return FALSE;
	}
*/
	if (m_pCommon->Over_LoopTime(INITIAL_MAIN)) {
		return FALSE;
	} else {
		return TRUE;
	}

}

BOOL CSequenceInit::Get_NGPickerTest()
{
/*
	int nFromCnt, nToT;
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(AX_NG_PICKER_X);

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	//사용변수 초기화
	gData.nNGPickerFromCnt = gData.nNGPickerFromWorkCnt = gData.nNGPickerToWorkCnt = 0;
	for(int i=0; i<6; i++) {
		gData.nNGPickerFromW[i] = 0;
		gData.nNGPickerToW[i] = 0;			// W Array [6]: Picker 수량  
		gData.nNGPickerFromL[i] = 0;		// [6]: Picker 수량  
		gData.nNGPickerToL[i] = 0;			// L Array [6]: Picker 수량  
		gData.dNGPickerFromPosX[i] = 0;		// [6]: Picker 수량  
		gData.dNGPickerFromPosY[i] = 0;   
		gData.dNGPickerFromPosZ[i] = 0;   
		gData.dNGPickerToPosX[i] = 0;
		gData.dNGPickerToPosY[i] = 0;
		gData.dNGPickerToPosZ[i] = 0;
	}
	
	nToT = nFromCnt = 0;
	for(int w=0; w<gData.nArrayW; w++) {
		for(int l=0; l<gData.nArrayL; l++) {
			if(nFromCnt == 6) break;

			if (nToT >= gData.nTotalCount) {
				gData.nNGPickerFromW[nFromCnt] = w;
				gData.nNGPickerFromL[nFromCnt] = l;

				gData.nNGPickerToW[nFromCnt] = w;
				gData.nNGPickerToL[nFromCnt] = l;

				nFromCnt++;
			}
			nToT++;
		}
	}
	gData.nTotalCount = gData.nTotalCount +6;


	gData.nNGPickerFromCnt = nFromCnt;

	// From, To 좌표계산
	for(int i=0; i<gData.nNGPickerFromCnt; i++ )
	{ 
		gData.dNGPickerFromPosX[i] = (pMoveData->dNGPickerX[1] + gData.dTrayFirstL) + (gData.dTrayPitchL * gData.nNGPickerFromL[i]) - gData.dNGPickerOffSetX[i];
		gData.dNGPickerFromPosY[i] = (pMoveData->dNGPickerY[1] + gData.dTrayFirstW) + (gData.dTrayPitchW * gData.nNGPickerFromW[i]) - gData.dNGPickerOffSetY[i];
		gData.dNGPickerFromPosZ[i] =  pMoveData->dNGPickerY[1] - gData.dNGPickerOffSetZ[i];
	}

	for(int i=0; i<gData.nNGPickerFromCnt; i++ )
	{ 
		gData.dNGPickerToPosX[i] = (pMoveData->dNGPickerX[2] + gData.dTrayFirstL) + (gData.dTrayPitchL * gData.nNGPickerToL[i]) - gData.dNGPickerOffSetX[i];
		gData.dNGPickerToPosY[i] = (pMoveData->dNGPickerY[2] + gData.dTrayFirstW) + (gData.dTrayPitchW * gData.nNGPickerToW[i]) - gData.dNGPickerOffSetY[i];
		gData.dNGPickerToPosZ[i] =  pMoveData->dNGPickerY[2] - gData.dNGPickerOffSetZ[i];
	}
*/
	return TRUE;
}	

BOOL CSequenceInit::Initial_Simulation()
{
#ifdef AJIN_BOARD_USE
	return TRUE;
#endif
	Sleep(SIM_WAITTIMES);

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
	DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();
	DX_DATA_2 *pDX2 = pAJinAXL->Get_pDX2();
	DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();
	DX_DATA_4 *pDX4 = pAJinAXL->Get_pDX4();
	DX_DATA_5 *pDX5 = pAJinAXL->Get_pDX5();
	DX_DATA_6 *pDX6 = pAJinAXL->Get_pDX6();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();
	DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();
	DY_DATA_2 *pDY2 = pAJinAXL->Get_pDY2();
	DY_DATA_3 *pDY3 = pAJinAXL->Get_pDY3();
	DY_DATA_4 *pDY4 = pAJinAXL->Get_pDY4();
	DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();
	DY_DATA_6 *pDY6 = pAJinAXL->Get_pDY6();

	if (m_nInitMainCase == 124) { pDX6->iUS_Z1Check1 = FALSE; pDX6->iUS_Z1Check2 = FALSE; }
	if (m_nInitMainCase == 125) { pDX6->iUS_Z2Check1 = FALSE; pDX6->iUS_Z2Check2 = FALSE; }

	if (m_nInitLoad1Case == 114) { pAJinAXL->Move_Absolute(AX_LOAD_TRAY_X1, 0.0); pAJinAXL->Move_Absolute(AX_LOAD_TRAY_X2, 0.0); }
	if (m_nInitLoad1Case == 115) { pAJinAXL->Move_Absolute(AX_LOAD_TRAY_Z1, 0.0); pAJinAXL->Move_Absolute(AX_LOAD_TRAY_Z2, 0.0); }
	if (m_nInitLoad2Case == 0) { }

	if (m_nInitUnload1Case == 114) { pAJinAXL->Move_Absolute(AX_UNLOAD_TRAY_Y1, 0.0); pAJinAXL->Move_Absolute(AX_UNLOAD_TRAY_Y2, 0.0); }
	if (m_nInitUnload1Case == 115) { pAJinAXL->Move_Absolute(AX_UNLOAD_TRAY_Z1, 0.0); pAJinAXL->Move_Absolute(AX_UNLOAD_TRAY_Z2, 0.0); }
	if (m_nInitUnload2Case == 0) { }
	if (m_nInitIndexTCase == 133) { pDX2->iInspCMAlignCheck1 = FALSE; pDX2->iInspCMAlignCheck2 = FALSE; pDX2->iInspCMAlignCheck3 = FALSE; }
	if (m_nInitLDPickerCase == 0) { }
	if (m_nInitNGPickerCase == 0) { }
	if (m_nInitGDPickerCase == 0) { }
	if (m_nInitULPickerCase == 152) { m_pCommon->Move_Position(AX_UNLOAD_TRAY_Z1, 0); m_pCommon->Move_Position(AX_UNLOAD_TRAY_Z2, 0); }
	if (m_nInitInspectCase == 0) { }
	
	if (m_nInitNGTrayCase == 111) { pDX3->iNGTray1Check = TRUE; pDX3->iNGTray2Check = TRUE;
									pDX1->iLS_Load1FCheck = TRUE; pDX6->iUS_Load1FCheck = TRUE;
									pDX0->iMainDoor1Close = TRUE; pDX0->iMainDoor2Close = TRUE; pDX0->iMainDoor3Close = TRUE; pDX0->iMainDoor4Close = TRUE; 
									pDX0->iMainDoor5Close = TRUE; pDX0->iMainDoor6Close = TRUE; pDX0->iMainDoor7Close = TRUE; pDX0->iMainDoor8Close = TRUE; }

	return TRUE;
}
