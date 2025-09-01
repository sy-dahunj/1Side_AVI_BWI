// AJinAXL.cpp : 구현 파일
//
#include "stdafx.h"
#include "AJinAXL.h"
#include <math.h>
#include "MESInterface.h"

// AJin Board Library
#include "AXL.h"
#include "AXD.h"
#include "AXM.h"
#pragma comment (lib, "AXL.lib")

CAJinAXL *CAJinAXL::m_pInstance = NULL;

CAJinAXL* CAJinAXL::Get_Instance()
{
	if (!m_pInstance)
		m_pInstance = new CAJinAXL();
	return m_pInstance;
}

void CAJinAXL::Delete_Instance()
{
	if (m_pInstance)
		delete m_pInstance;
	m_pInstance = NULL;
}

// CAJinAXL

CAJinAXL::CAJinAXL(void)
{
	m_DX0.nValue = 0;
	m_DX1.nValue = 0;
	m_DX2.nValue = 0;
	m_DX3.nValue = 0;
	m_DX4.nValue = 0;
	m_DX5.nValue = 0;
	m_DX6.nValue = 0;

	m_DY0.nValue = 0;
	m_DY1.nValue = 0;
	m_DY2.nValue = 0;
	m_DY3.nValue = 0;
	m_DY4.nValue = 0;
	m_DY5.nValue = 0;
	m_DY6.nValue = 0;

	m_pThreadAJin = NULL;
	m_bThreadAJin = FALSE;
}

CAJinAXL::~CAJinAXL(void)
{
}

BOOL CAJinAXL::Initialize_AJin()
{
#ifdef AJIN_BOARD_USE
	DWORD dwReturn;
	long lDIOCount, lAxisCount;

	dwReturn = AxlOpenNoReset(7);
	if (dwReturn != AXT_RT_SUCCESS) return FALSE;

	// DIO
	dwReturn = AxdInfoGetModuleCount(&lDIOCount);
 	if (dwReturn != AXT_RT_SUCCESS) return FALSE;
	if (lDIOCount < DIO_MODULE_COUNT) return FALSE;
	
	Read_Output();

	m_DY0.oCameraTrigger = TRUE;
	m_DY0.oBarcodeTrigger = TRUE;
	m_DY0.oLightBarcode = TRUE;

	m_DY0.oLight11 = TRUE;
	m_DY0.oLight12 = TRUE;
	m_DY0.oLight13 = TRUE;
	m_DY0.oLight14 = TRUE;
	m_DY0.oLight21 = TRUE;
	m_DY0.oLight22 = TRUE;
	m_DY0.oLight23 = TRUE;
	m_DY0.oLight24 = TRUE;
	m_DY0.oLight32 = TRUE;
	m_DY0.oLight33 = TRUE;
	m_DY0.oLight34 = TRUE;
	m_DY0.oLight41 = TRUE;
	m_DY0.oLight42 = TRUE;
	m_DY0.oLight43 = TRUE; 
	m_DY0.oLight44 = TRUE;

	Write_Output(0);
	Sleep(100);

	// Motion
	dwReturn = AxmInfoGetAxisCount(&lAxisCount);
	if (dwReturn != AXT_RT_SUCCESS) return FALSE;
	if (lAxisCount < AXIS_COUNT) return FALSE;

	for (long i = 0; i < AXIS_COUNT; i++) Set_ServoOn(i, FALSE);
	Sleep(2000);

	AxmMotLoadParaAll("System/AJinSetting.mot");
#else
	Sim_SetOutToIn(99);
#endif

	for (long i = 0; i < AXIS_COUNT; i++) Set_ServoOn(i, TRUE);

	m_nGoodCnt = m_nEmptyCnt = 0;
	m_bThreadAJin = TRUE;
	m_pThreadAJin = AfxBeginThread(Thread_AJinRun, this);

	return TRUE;
}

void CAJinAXL::Terminate_AJin()
{
	if (m_pThreadAJin) {
		m_bThreadAJin = FALSE;
		WaitForSingleObject(m_pThreadAJin->m_hThread, INFINITE);
	}

	m_DY0.oStartLamp = FALSE;
	m_DY0.oStopLamp = FALSE;
	m_DY0.oResetLamp = FALSE;
	m_DY0.oAlarmBuzzer1 = FALSE;
	m_DY0.oAlarmBuzzer2 = FALSE;
	m_DY0.oTowerGreen = FALSE;
	m_DY0.oTowerYellow = FALSE;
	m_DY0.oTowerRed = FALSE;
	m_DY0.oInsideLamp = FALSE;
	Write_Output(0);

	for (long i = 0; i < AXIS_COUNT; i++) Set_ServoOn(i, FALSE);

#ifdef AJIN_BOARD_USE
	if (AxlIsOpened()) AxlClose();
#endif
}

void CAJinAXL::Read_Input()
{
#ifdef AJIN_BOARD_USE
	AxdiReadInportDword(0, 0, &m_DX0.nValue);
	AxdiReadInportDword(1, 0, &m_DX1.nValue);
	AxdiReadInportDword(2, 0, &m_DX2.nValue);
	AxdiReadInportDword(3, 0, &m_DX3.nValue);
	AxdiReadInportDword(4, 0, &m_DX4.nValue);
	AxdiReadInportDword(5, 0, &m_DX5.nValue);
	AxdiReadInportDword(6, 0, &m_DX6.nValue);
#endif
}

void CAJinAXL::Read_Output()
{
#ifdef AJIN_BOARD_USE
	AxdoReadOutportDword(7, 0, &m_DY0.nValue);
	AxdoReadOutportDword(8, 0, &m_DY1.nValue);
	AxdoReadOutportDword(9, 0, &m_DY2.nValue);
	AxdoReadOutportDword(10, 0, &m_DY3.nValue);
	AxdoReadOutportDword(11, 0, &m_DY4.nValue);
	AxdoReadOutportDword(12, 0, &m_DY5.nValue);
	AxdoReadOutportDword(13, 0, &m_DY6.nValue);
#endif
}

void CAJinAXL::Write_Output(int nModule)
{
#ifdef AJIN_BOARD_USE
	if (nModule == 0) AxdoWriteOutportDword(7, 0, m_DY0.nValue);
	if (nModule == 1) AxdoWriteOutportDword(8, 0, m_DY1.nValue);
	if (nModule == 2) AxdoWriteOutportDword(9, 0, m_DY2.nValue);
	if (nModule == 3) AxdoWriteOutportDword(10, 0, m_DY3.nValue);
	if (nModule == 4) AxdoWriteOutportDword(11, 0, m_DY4.nValue);
	if (nModule == 5) AxdoWriteOutportDword(12, 0, m_DY5.nValue);
	if (nModule == 6) AxdoWriteOutportDword(13, 0, m_DY6.nValue);
#else
	Sim_SetOutToIn(nModule);
#endif
}

void CAJinAXL::Read_MotionStatus()
{
#ifdef AJIN_BOARD_USE
	DWORD dwStatus;

	for (int i = 0; i < AXIS_COUNT; i++) {
		
		// Position Reading
		AxmStatusGetActPos(i, &m_Status[i].dPos);

		// Velocity Reading
		AxmStatusReadVel(i, &m_Status[i].dVel);

		// Servo-On Reading
		AxmSignalIsServoOn(i, &dwStatus);
		m_Status[i].bSOn = (BOOL)dwStatus;

// 		// Origin Limit
// 		AxmSignalReadInputBit(i, UIO_INP0, &dwStatus);		// In0 : Home
// 		m_Status[i].bOrg = (BOOL)dwStatus;

		// Mechanical Input
		AxmStatusReadMechanical(i, &dwStatus);
		
		// Positive Limit
		m_Status[i].bELP = (BOOL)((dwStatus >> 0) & 0x1);	// bit0
		if (i==AX_INDEX_R || i==AX_LOAD_PICKER_Y2 || i==AX_UNLOAD_PICKER_X2) m_Status[i].bELP = FALSE;

		// Negative Limit
		m_Status[i].bELN = (BOOL)((dwStatus >> 1) & 0x1);	// bit1
		if (i==AX_INDEX_R) m_Status[i].bELN = FALSE;

		// Alarm
		m_Status[i].bALM = (BOOL)((dwStatus >> 4) & 0x1);	// bit4

		// In-Position
		m_Status[i].bInP = (BOOL)((dwStatus >> 5) & 0x1);	// bit5

		// Motion Running
		AxmStatusReadInMotion(i, &dwStatus);
		m_Status[i].bRun = (BOOL)dwStatus;

		// Home Done
		AxmHomeGetResult(i, &dwStatus);
		if (dwStatus == HOME_SUCCESS) m_Status[i].bHom = TRUE;
		else m_Status[i].bHom = FALSE;
	}
#endif
}

void CAJinAXL::Set_ServoOn(int nAxis, BOOL bOnOff)
{
#ifdef AJIN_BOARD_USE
	AxmSignalServoOn(nAxis, bOnOff);
#else
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(nAxis);
	pStatus->bSOn = TRUE;
#endif
}

void CAJinAXL::Home_Search(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmHomeSetStart(nAxis);
	m_Status[nAxis].bHom = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(nAxis);
	pStatus->bHom = TRUE;
#endif
}

void CAJinAXL::Set_Home(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmStatusSetActPos(nAxis, 0.0);
	AxmStatusSetCmdPos(nAxis, 0.0);
	AxmHomeSetResult(nAxis, HOME_SUCCESS);
#endif
}

void CAJinAXL::Set_CVActPos(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmStatusSetActPos(nAxis, 0.0);
	AxmStatusSetCmdPos(nAxis, 0.0);
	Sleep(10);
#else
	Sim_SetMotion(1, nAxis, 0.0);
#endif
}

void CAJinAXL::Move_Absolute(int nAxis, double dPos)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_ABS_MODE);
	double	dVel = m_Param[nAxis].dMovSpeed;
	double	dAcc = m_Param[nAxis].dMovSpeed * 4.0;
	AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dAcc);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	Sim_SetMotion(1, nAxis, dPos);
#endif
}

void CAJinAXL::Move_Abs_Accel(int nAxis, double dPos, double dAcc)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_ABS_MODE);
	double	dVel = m_Param[nAxis].dMovSpeed;
	AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dAcc);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	Sim_SetMotion(1, nAxis, dPos);
#endif
}

void CAJinAXL::Move_Relative(int nAxis, double dPos)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_REL_MODE);
	double	dVel = m_Param[nAxis].dMovSpeed;
	double	dAcc = m_Param[nAxis].dMovSpeed * 4.0;
	AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dAcc);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	Sim_SetMotion(2, nAxis, dPos);
#endif
}

void CAJinAXL::Jog_Positive(int nAxis)
{
#ifdef AJIN_BOARD_USE
	double	dVel = m_Param[nAxis].dJogSpeed;
	double	dAcc = m_Param[nAxis].dJogSpeed * 4.0;
	AxmMoveVel(nAxis, dVel, dAcc, dAcc);
#endif
}

void CAJinAXL::Jog_Negative(int nAxis)
{
#ifdef AJIN_BOARD_USE
	double	dVel = m_Param[nAxis].dJogSpeed * -1.0;
	double	dAcc = m_Param[nAxis].dJogSpeed * 4.0;
	AxmMoveVel(nAxis, dVel, dAcc, dAcc);
#endif
}

void CAJinAXL::Stop_Motion(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveSStop(nAxis);
#endif
}

void CAJinAXL::EStop_Motion(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveEStop(nAxis);
#endif
}

void CAJinAXL::Alarm_Reset(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveEStop(nAxis);
	Sleep(200);
	AxmSignalServoAlarmReset(nAxis, TRUE);
	Sleep(200);
	AxmSignalServoAlarmReset(nAxis, FALSE);
#endif
}

BOOL CAJinAXL::Is_Done(int nAxis)
{
#ifdef AJIN_BOARD_USE
	if (m_Status[nAxis].bRun) return FALSE;
	if (!m_Status[nAxis].bInP) return FALSE;
#endif
	return TRUE;
}

BOOL CAJinAXL::Is_Home(int nAxis)
{
//	if((nAxis>=0 && nAxis<=3) || (nAxis>=19 && nAxis<=22)) return TRUE;
#ifdef AJIN_BOARD_USE
	if (!m_Status[nAxis].bHom) return FALSE;
	if (m_Status[nAxis].bRun) return FALSE;
#endif
	return TRUE;
}

BOOL CAJinAXL::Is_MoveDone(int nAxis, double dPos)
{
#ifdef AJIN_BOARD_USE
	if (!Is_Done(nAxis)) return FALSE;
	if (fabs(m_Status[nAxis].dPos - dPos) > 0.1) return FALSE;
#endif
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Motion Param Read / Write Function

void CAJinAXL::Read_MotionParam(int nAxis)
{
	CIniFileCS INI("System/AxisParam.ini");
	if (!INI.Check_File()) return;
	
	CString strAxis;
	strAxis.Format("AXIS_%02d", nAxis);
	m_Param[nAxis].dMovSpeed = INI.Get_Double(strAxis, "MOVE", 0.0);
	m_Param[nAxis].dJogSpeed = INI.Get_Double(strAxis, "JOG", 0.0);
}

void CAJinAXL::Save_MotionParam(int nAxis, double dMovSp, double dJogSp)
{
	CIniFileCS INI("System/AxisParam.ini");
	if (!INI.Check_File()) return;
	
	CString strAxis;
	strAxis.Format("AXIS_%02d", nAxis);
	INI.Set_Double(strAxis, "MOVE", dMovSp, "%0.3lf");
	INI.Set_Double(strAxis, "JOG", dJogSp, "%0.3lf");

	// RMS 항목
	Save_RmsMotionSpeed(nAxis, dMovSp);
}

void CAJinAXL::Save_RmsMotionSpeed(int nAxis, double dSpeed)
{
	CString strAxis = "", strName, strSpeed, strAccel;

	if		(nAxis == AX_LOAD_TRAY_X1)		strAxis = "Load Tray1 X";
	else if (nAxis == AX_LOAD_TRAY_X2)		strAxis = "Load Tray2 X";
	else if (nAxis == AX_LOAD_TRAY_Z1)		strAxis = "Load Tray1 Z";
	else if (nAxis == AX_LOAD_TRAY_Z2)		strAxis = "Load Tray2 Z";
	else if (nAxis == AX_LOAD_PICKER_Y1)	strAxis = "Load Picker Y1";
	else if (nAxis == AX_LOAD_PICKER_Z)		strAxis = "Load Picker Z";
	else if (nAxis == AX_LOAD_PICKER_Y2)	strAxis = "Load Picker Y2";
	else if (nAxis == AX_INDEX_R)			strAxis = "Index R";
	else if (nAxis == AX_BARCODE_A)			strAxis = "Barcode A";
	else if (nAxis == AX_INSPECTION_A)		strAxis = "Inspection A";
	else if (nAxis == AX_INSPECTION_Z)		strAxis = "Inspection Z";
	else if (nAxis == AX_NG_PICKER_X)		strAxis = "NG Picker X";
	else if (nAxis == AX_NG_PICKER_Z)		strAxis = "NG Picker Z";
	else if (nAxis == AX_NG_STAGE_Y)		strAxis = "NG Stage Y";
	else if (nAxis == AX_GOOD_PICKER_Y)		strAxis = "Good Picker Y";
	else if (nAxis == AX_GOOD_PICKER_Z)		strAxis = "Good Picker Z";
	else if (nAxis == AX_UNLOAD_PICKER_X1)	strAxis = "Unload Picker X1";
	else if (nAxis == AX_UNLOAD_PICKER_Z)	strAxis = "Unload Picker Z";
	else if (nAxis == AX_UNLOAD_PICKER_X2)	strAxis = "Unload Picker X2";
	else if (nAxis == AX_UNLOAD_TRAY_Y1)	strAxis = "Unload Tray1 Y";
	else if (nAxis == AX_UNLOAD_TRAY_Y2)	strAxis = "Unload Tray2 Y";
	else if (nAxis == AX_UNLOAD_TRAY_Z1)	strAxis = "Unload Tray1 Z";
	else if (nAxis == AX_UNLOAD_TRAY_Z2)	strAxis = "Unload Tray2 Z";

	if (strAxis == "") return;

	strSpeed.Format("%0.3lf", dSpeed);
	strAccel.Format("%0.3lf", 0.0);

	strName.Format("%s Speed", strAxis); g_objMES.Save_AviRmsData(strName, strSpeed);
	strName.Format("%s Accel", strAxis); g_objMES.Save_AviRmsData(strName, strAccel);
}

void CAJinAXL::Status_Monitoring()
{
	int	nIndexPos=0;
	if      (!m_DX2.iInspCMAlignCheck1 && !m_DX2.iInspCMAlignCheck2 && !m_DX2.iInspCMAlignCheck3) nIndexPos = 1;
	else if ( m_DX2.iInspCMAlignCheck1 && !m_DX2.iInspCMAlignCheck2 && !m_DX2.iInspCMAlignCheck3) nIndexPos = 2;
	else if (!m_DX2.iInspCMAlignCheck1 &&  m_DX2.iInspCMAlignCheck2 && !m_DX2.iInspCMAlignCheck3) nIndexPos = 3;
	else if ( m_DX2.iInspCMAlignCheck1 &&  m_DX2.iInspCMAlignCheck2 && !m_DX2.iInspCMAlignCheck3) nIndexPos = 4;
	else if (!m_DX2.iInspCMAlignCheck1 && !m_DX2.iInspCMAlignCheck2 &&  m_DX2.iInspCMAlignCheck3) nIndexPos = 5;
	else if ( m_DX2.iInspCMAlignCheck1 && !m_DX2.iInspCMAlignCheck2 &&  m_DX2.iInspCMAlignCheck3) nIndexPos = 6;
	else if (!m_DX2.iInspCMAlignCheck1 &&  m_DX2.iInspCMAlignCheck2 &&  m_DX2.iInspCMAlignCheck3) nIndexPos = 7;
	else if ( m_DX2.iInspCMAlignCheck1 &&  m_DX2.iInspCMAlignCheck2 &&  m_DX2.iInspCMAlignCheck3) nIndexPos = 8;

	if (gData.nIndexPos == 8 && nIndexPos != 8) gData.nIndexPos = 0;
	if (gData.nIndexPos < nIndexPos) gData.nIndexPos = nIndexPos;

// 	if (!m_DX6.iUS_Unload1FCheck)	m_nGoodCnt++;
// 	else							m_nGoodCnt = 0;
// 	if(m_nGoodCnt>200) {
// 		gData.nGoodTrayCount = 0;
// 		m_nGoodCnt = 0;
// 	}

	if (!m_DX1.iLS_Unload1FCheck)	m_nEmptyCnt++;
	else							m_nEmptyCnt = 0;
	if(m_nEmptyCnt>200) {
		gData.nEmptyTrayCount = 0;
		m_nEmptyCnt = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// Thread Function 
UINT CAJinAXL::Thread_AJinRun(LPVOID lpVoid)
{
	CAJinAXL *pAJinAXL = (CAJinAXL*)lpVoid;
	
	while (pAJinAXL->m_bThreadAJin) {
		pAJinAXL->Read_Input();
		pAJinAXL->Read_MotionStatus();
		pAJinAXL->Status_Monitoring();
		Sleep(1);
	}
	pAJinAXL->m_bThreadAJin = FALSE;
	pAJinAXL->m_pThreadAJin = NULL;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////

BOOL CAJinAXL::Is_ServoAxis(int nAxis)
{
	if (nAxis == AX_LOAD_TRAY_X1		||
		nAxis == AX_LOAD_TRAY_X2		|| 
		nAxis == AX_LOAD_TRAY_Z1		||
		nAxis == AX_LOAD_TRAY_Z2		|| 
		nAxis == AX_LOAD_PICKER_Y1		||
		nAxis == AX_LOAD_PICKER_Z		||
		nAxis == AX_LOAD_PICKER_Y2		||
		nAxis == AX_INDEX_R				||
		nAxis == AX_BARCODE_A			||
		nAxis == AX_INSPECTION_A		||
		nAxis == AX_INSPECTION_Z		||
		nAxis == AX_NG_PICKER_X			||
		nAxis == AX_NG_PICKER_Z			||
		nAxis == AX_NG_STAGE_Y			||
		nAxis == AX_GOOD_PICKER_Y		||
		nAxis == AX_GOOD_PICKER_Z		||
		nAxis == AX_UNLOAD_PICKER_X1	|| 
		nAxis == AX_UNLOAD_PICKER_Z		||
		nAxis == AX_UNLOAD_PICKER_X2	|| 
		nAxis == AX_UNLOAD_TRAY_Y1		||
		nAxis == AX_UNLOAD_TRAY_Y2		||
		nAxis == AX_UNLOAD_TRAY_Z1		||
		nAxis == AX_UNLOAD_TRAY_Z2) return TRUE;	

	else return FALSE;

}

BOOL CAJinAXL::Use_OrgAxis(int nAxis)
{
	return FALSE;
}

BOOL CAJinAXL::Use_ElpAxis(int nAxis)
{
	return TRUE;
}

BOOL CAJinAXL::Use_ElnAxis(int nAxis)
{
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void CAJinAXL::Sim_SetMotion(int nNo, int nAxis, double dPos)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(nAxis);

	Sleep(SIM_WAITTIMEM);
	if		(nNo == 1)	pStatus->dPos = dPos;
	else if (nNo == 2)	pStatus->dPos = pStatus->dPos + dPos;
	else if (nNo == 3)	pStatus->dPos = dPos;
}

void CAJinAXL::Sim_SetOutToIn(int nNo)
{
	Sleep(SIM_WAITTIMES);
	BOOL bT = TRUE;
	BOOL bF = FALSE;

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

	if (nNo==0) {
		pDX0->iStartSw		 		 = bF;
		pDX0->iStopSw		 		 = bF;
		pDX0->iResetSw		 		 = bF;
		pDX0->iMainAir1		 		 = bT;
		pDX0->iMainAir2		 		 = bT;

		pDX0->iMainDoor1Close		 = bT;
		pDX0->iMainDoor2Close		 = bT;
		pDX0->iMainDoor3Close		 = bT;
		pDX0->iMainDoor4Close		 = bT;
		pDX0->iMainDoor5Close		 = bT;
		pDX0->iMainDoor6Close		 = bT;
		pDX0->iMainDoor7Close		 = bT;
		pDX0->iMainDoor8Close		 = bT;

		pDX0->iEMS1		 = bF;
		pDX0->iEMS2		 = bF;
		pDX0->iEMS3		 = bF;
		pDX0->iEMS4		 = bF;
		pDX0->iEMS5		 = bF;
		pDX0->iEMS6		 = bF;
	}
	if (nNo==1) {
		pDX1->iLS_LoadSupport1In	= pDY1->oLS_LoadSupport12In;
		pDX1->iLS_LoadSupport1Out	= pDY1->oLS_LoadSupport12Out;
		pDX1->iLS_LoadSupport2In	= pDY1->oLS_LoadSupport12In;
		pDX1->iLS_LoadSupport2Out	= pDY1->oLS_LoadSupport12Out;
		
		pDX1->iLS_UnloadSupport1In	= pDY1->oLS_UnloadSupport12In;
		pDX1->iLS_UnloadSupport1Out	= pDY1->oLS_UnloadSupport12Out;
		pDX1->iLS_UnloadSupport2In	= pDY1->oLS_UnloadSupport12In;
		pDX1->iLS_UnloadSupport2Out	= pDY1->oLS_UnloadSupport12Out;
        
		pDX1->iLS_Z1AlignM34In	= pDY1->oLS_Z1AlignM34In;
		pDX1->iLS_Z1AlignM34Out	= pDY1->oLS_Z1AlignM34Out;
		pDX1->iLS_Z1AlignS12In	= pDY1->oLS_Z1AlignS12In;
		pDX1->iLS_Z1AlignS12Out	= pDY1->oLS_Z1AlignS12Out;
		
		pDX1->iLS_Z2AlignM34In	= pDY1->oLS_Z2AlignM34In;
		pDX1->iLS_Z2AlignM34Out	= pDY1->oLS_Z2AlignM34Out;
		pDX1->iLS_Z2AlignS12In	= pDY1->oLS_Z2AlignS12In;
		pDX1->iLS_Z2AlignS12Out	= pDY1->oLS_Z2AlignS12Out;
	}
	if (nNo==2) {
		pDX2->iMLPicker1Open    = pDY2->oMLPicker1Open;
		pDX2->iMLPicker2Open    = pDY2->oMLPicker2Open;
		pDX2->iMLPicker3Open    = pDY2->oMLPicker3Open;
		pDX2->iMLPicker4Open    = pDY2->oMLPicker4Open;
		pDX2->iMLPicker5Open    = pDY2->oMLPicker5Open;
		pDX2->iMLPicker6Open    = pDY2->oMLPicker6Open;

		pDX2->iMLPicker1CMCheck    = pDY2->oMLPicker1Close;
		pDX2->iMLPicker2CMCheck    = pDY2->oMLPicker2Close;
		pDX2->iMLPicker3CMCheck    = pDY2->oMLPicker3Close;
		pDX2->iMLPicker4CMCheck    = pDY2->oMLPicker4Close;
		pDX2->iMLPicker5CMCheck    = pDY2->oMLPicker5Close;
		pDX2->iMLPicker6CMCheck    = pDY2->oMLPicker6Close;

		pDX2->iCMPressUp		= pDY2->oCMPressUp;
		pDX2->iCMPressDn		= pDY2->oCMPressDn;

		pDX2->iInspCMAlign1In	= pDY2->oInspCMAlign1In;
		pDX2->iInspCMAlign1Out	= pDY2->oInspCMAlign1Out;
		pDX2->iInspCMAlign2In	= pDY2->oInspCMAlign2In;
		pDX2->iInspCMAlign2Out	= pDY2->oInspCMAlign2Out;
		pDX2->iInspCMAlign3In	= pDY2->oInspCMAlign3In;
		 
		pDX2->iInspCMAlign3Out	= pDY2->oInspCMAlign3Out;
		pDX2->iInspCMAlign4In	= pDY2->oInspCMAlign4In;
		pDX2->iInspCMAlign4Out	= pDY2->oInspCMAlign4Out;
		pDX2->iInspVacuumUp		= pDY2->oInspVacuumUp;
		pDX2->iInspVacuumDown	= pDY2->oInspVacuumDown;
	}
	if (nNo==3) {
		pDX3->iInspVacuumPad1Check	= pDY3->oInspVacuumPad1On;
		pDX3->iInspVacuumPad2Check	= pDY3->oInspVacuumPad2On;
		pDX3->iInspVacuumPad3Check	= pDY3->oInspVacuumPad3On;
		pDX3->iInspVacuumPad4Check	= pDY3->oInspVacuumPad4On;
		pDX3->iInspVacuumPad5Check	= pDY3->oInspVacuumPad5On;
		pDX3->iInspVacuumPad6Check	= pDY3->oInspVacuumPad6On;
        			      
		pDX3->iNGPicker1Open		= pDY3->oNGPicker1Open;
		pDX3->iNGPicker2Open		= pDY3->oNGPicker2Open;
		pDX3->iNGPicker3Open		= pDY3->oNGPicker3Open;
		pDX3->iNGPicker4Open		= pDY3->oNGPicker4Open;
		pDX3->iNGPicker5Open		= pDY3->oNGPicker5Open;
		pDX3->iNGPicker1Up			= pDY3->oNGPicker1Up;
		pDX3->iNGPicker1Down		= pDY3->oNGPicker1Down;
		pDX3->iNGPicker2Up			= pDY3->oNGPicker2Up;
        								
		pDX3->iNGPicker2Down		= pDY3->oNGPicker2Down;
		pDX3->iNGPicker3Up			= pDY3->oNGPicker3Up;
		pDX3->iNGPicker3Down		= pDY3->oNGPicker3Down;
		pDX3->iNGPicker4Up			= pDY3->oNGPicker4Up;
		pDX3->iNGPicker4Down		= pDY3->oNGPicker4Down;
		pDX3->iNGPicker5Up			= pDY3->oNGPicker5Up;
		pDX3->iNGPicker5Down		= pDY3->oNGPicker5Down;

		pDX3->iNGPicker1CMCheck		= !pDY3->oNGPicker1Open;
		pDX3->iNGPicker2CMCheck		= !pDY3->oNGPicker2Open;
		pDX3->iNGPicker3CMCheck		= !pDY3->oNGPicker3Open;
		pDX3->iNGPicker4CMCheck		= !pDY3->oNGPicker4Open;
		pDX3->iNGPicker5CMCheck		= !pDY3->oNGPicker5Open;
	}
	if (nNo==4) {
		pDX4->iGoodPicker1Open	= pDY4->oGoodPicker1Open;
		pDX4->iGoodPicker2Open	= pDY4->oGoodPicker2Open;
		pDX4->iGoodPicker3Open	= pDY4->oGoodPicker3Open;
		pDX4->iGoodPicker4Open	= pDY4->oGoodPicker4Open;
		pDX4->iGoodPicker5Open	= pDY4->oGoodPicker5Open;
		pDX4->iGoodPicker6Open	= pDY4->oGoodPicker6Open;
		pDX4->iGoodPicker1Up	= pDY4->oGoodPicker1Up;
		pDX4->iGoodPicker1Down	= pDY4->oGoodPicker1Down;
        
		pDX4->iGoodPicker2Up	= pDY4->oGoodPicker2Up;
		pDX4->iGoodPicker2Down	= pDY4->oGoodPicker2Down;
		pDX4->iGoodPicker3Up	= pDY4->oGoodPicker3Up;
		pDX4->iGoodPicker3Down	= pDY4->oGoodPicker3Down;
		pDX4->iGoodPicker4Up	= pDY4->oGoodPicker4Up;
		pDX4->iGoodPicker4Down	= pDY4->oGoodPicker4Down;
		pDX4->iGoodPicker5Up	= pDY4->oGoodPicker5Up;
		pDX4->iGoodPicker5Down	= pDY4->oGoodPicker5Down;
        
		pDX4->iGoodPicker6Up	= pDY4->oGoodPicker6Up;
		pDX4->iGoodPicker6Down	= pDY4->oGoodPicker6Down;
	
		pDX4->iGoodPicker1CMCheck	= !pDY4->oGoodPicker1Open;
		pDX4->iGoodPicker2CMCheck	= !pDY4->oGoodPicker2Open;
		pDX4->iGoodPicker3CMCheck	= !pDY4->oGoodPicker3Open;
		pDX4->iGoodPicker4CMCheck	= !pDY4->oGoodPicker4Open;
		pDX4->iGoodPicker5CMCheck	= !pDY4->oGoodPicker5Open;
		pDX4->iGoodPicker6CMCheck	= !pDY4->oGoodPicker6Open;

		pDX4->iNGPicker6Open	= pDY4->oNGPicker6Open;
		pDX4->iNGPicker6Up		= pDY4->oNGPicker6Up;
		pDX4->iNGPicker6Down	= pDY4->oNGPicker6Down;
	}
	if (nNo==5) {
		pDX5->iMUPicker1Open	= pDY5->oMUPicker1Open;
		pDX5->iMUPicker2Open	= pDY5->oMUPicker2Open;
		pDX5->iMUPicker3Open	= pDY5->oMUPicker3Open;
		pDX5->iMUPicker4Open	= pDY5->oMUPicker4Open;
		pDX5->iMUPicker5Open	= pDY5->oMUPicker5Open;
		pDX5->iMUPicker6Open	= pDY5->oMUPicker6Open;

		pDX5->iMUPicker1CMCheck	= !pDY5->oMUPicker1Open;
		pDX5->iMUPicker2CMCheck	= !pDY5->oMUPicker2Open;
		pDX5->iMUPicker3CMCheck	= !pDY5->oMUPicker3Open;
		pDX5->iMUPicker4CMCheck	= !pDY5->oMUPicker4Open;
		pDX5->iMUPicker5CMCheck	= !pDY5->oMUPicker5Open;
		pDX5->iMUPicker6CMCheck	= !pDY5->oMUPicker6Open;
								 
		pDX5->iNGVacuumUp		= pDY5->oNGVacuumUp;
		pDX5->iNGVacuumDown		= pDY5->oNGVacuumDown;
		pDX5->iNGVacuumPad1Check	= pDY5->oNGVacuumPad1On;
		pDX5->iNGVacuumPad2Check	= pDY5->oNGVacuumPad2On;
		pDX5->iNGVacuumPad3Check	= pDY5->oNGVacuumPad3On;
		pDX5->iNGVacuumPad4Check	= pDY5->oNGVacuumPad4On;
		pDX5->iNGVacuumPad5Check	= pDY5->oNGVacuumPad5On;
		pDX5->iNGVacuumPad6Check	= pDY5->oNGVacuumPad6On;
		
		pDX5->iGoodVacuumUp			= pDY5->oGoodVacuumUp;
		pDX5->iGoodVacuumDown		= pDY5->oGoodVacuumDown;
		pDX5->iGoodVacuumPad1Check	= pDY5->oGoodVacuumPad1On;
		pDX5->iGoodVacuumPad2Check	= pDY5->oGoodVacuumPad2On;
		pDX5->iGoodVacuumPad3Check	= pDY5->oGoodVacuumPad3On;
		pDX5->iGoodVacuumPad4Check	= pDY5->oGoodVacuumPad4On;
		pDX5->iGoodVacuumPad5Check	= pDY5->oGoodVacuumPad5On;
		pDX5->iGoodVacuumPad6Check	= pDY5->oGoodVacuumPad6On;
	}
	if (nNo==6) {
		pDX6->iUS_UnloadSupport1In	= pDY6->oUS_UnloadSupport12In;
		pDX6->iUS_UnloadSupport1Out	= pDY6->oUS_UnloadSupport12Out;
		pDX6->iUS_UnloadSupport2In	= pDY6->oUS_UnloadSupport12In;
		pDX6->iUS_UnloadSupport2Out	= pDY6->oUS_UnloadSupport12Out;

		pDX6->iUS_LoadSupport1In	= pDY6->oUS_LoadSupport12In;
		pDX6->iUS_LoadSupport1Out	= pDY6->oUS_LoadSupport12Out;
		pDX6->iUS_LoadSupport2In	= pDY6->oUS_LoadSupport12In;
		pDX6->iUS_LoadSupport2Out	= pDY6->oUS_LoadSupport12Out;

		pDX6->iUS_Z1AlignM34In		= pDY6->oUS_Z1AlignM34In;
		pDX6->iUS_Z1AlignM34Out		= pDY6->oUS_Z1AlignM34Out;
		pDX6->iUS_Z1AlignS12In		= pDY6->oUS_Z1AlignS12In;
		pDX6->iUS_Z1AlignS12Out		= pDY6->oUS_Z1AlignS12Out;

		pDX6->iUS_Z2AlignM34In		= pDY6->oUS_Z2AlignM34In;
		pDX6->iUS_Z2AlignM34Out		= pDY6->oUS_Z2AlignM34Out;
		pDX6->iUS_Z2AlignS12In		= pDY6->oUS_Z2AlignS12In;
		pDX6->iUS_Z2AlignS12Out		= pDY6->oUS_Z2AlignS12Out;
	}
}
