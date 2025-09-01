// Common.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "Common.h"
#include <math.h>

#include "AJinAXL.h"
#include "DataManager.h"

#include "ErrorDlg.h"
#include "MsgBoxDlg.h"
#include "NumPadDlg.h"
#include "KeyPadDlg.h"
#include "PasswordDlg.h"

#include "LogFile.h"
#include "WorkDlg.h"

#include "SequenceMain.h"

#include <winnetwk.h>
#pragma comment(lib, "Mpr")

#include <wbemidl.h>
#include <comdef.h>

#pragma comment(lib, "wbemuuid.lib")

IMPLEMENT_DYNAMIC(CCommon, CWnd)

CCommon *CCommon::m_pInstance = NULL;

CCriticalSection g_csShowError;

CCommon *CCommon::Get_Instance()
{
	if (!m_pInstance) {
		m_pInstance = new CCommon();
		if (!m_pInstance->m_hWnd) {
			CRect r = m_pInstance->Get_Position();
			m_pInstance->CreateEx(0, AfxRegisterWndClass(0), "CCommon", 0, r, NULL, 0, NULL);
		}
	}
	return m_pInstance;
}

void CCommon::Delete_Instance()
{
	if (m_pInstance->m_hWnd) m_pInstance->DestroyWindow();
	if (m_pInstance) delete m_pInstance;
	m_pInstance = NULL;
}

// CCommon

CCommon::CCommon()
{
	Set_Position(0, 0, 0, 0);
	m_bPowerOffRelay = FALSE;

	m_nStatus = -1;
	m_bInsideLamp = FALSE;

	m_pFtp = NULL;
}

CCommon::~CCommon()
{
}

BEGIN_MESSAGE_MAP(CCommon, CWnd)
END_MESSAGE_MAP()

// CCommon 메시지 처리기입니다.

void CCommon::DoEvents(int nSleep)
{
	MSG msg;
	if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (nSleep > 0) Sleep(nSleep);
}

void CCommon::Delay_Time(DWORD msec)
{
	DWORD timeS = GetTickCount();
	DWORD dwTerm = 0;

	do {
		DoEvents();
		DWORD timeE = GetTickCount();
		dwTerm = (timeE - timeS);
	} while (dwTerm < msec);
}

void CCommon::Set_LoopTime(int nRun, DWORD msec)
{
	if (nRun == INITIAL_MAIN)		{ m_dwLoopInitMainStart = GetTickCount();		m_dwLoopInitMainDelay = msec; }
	if (nRun == INITIAL_LOAD1)		{ m_dwLoopInitLoadS1Start = GetTickCount();		m_dwLoopInitLoadS1Delay = msec; }
	if (nRun == INITIAL_LOAD2)		{ m_dwLoopInitLoad2Start = GetTickCount();		m_dwLoopInitLoad2Delay = msec; }
	if (nRun == INITIAL_UNLOAD1)	{ m_dwLoopInitUnload1Start = GetTickCount();	m_dwLoopInitUnload1Delay = msec; }
	if (nRun == INITIAL_UNLOAD2)	{ m_dwLoopInitUnload2Start = GetTickCount();	m_dwLoopInitUnload2Delay = msec; }
	if (nRun == INITIAL_INSPECT)	{ m_dwLoopInitInspectStart = GetTickCount();	m_dwLoopInitInspectDelay = msec; }
	if (nRun == INITIAL_NGPICKER)	{ m_dwLoopInitNGPickStart = GetTickCount();		m_dwLoopInitNGPickDelay = msec; }
	if (nRun == INITIAL_GDPICKER)	{ m_dwLoopInitGDPickStart = GetTickCount();		m_dwLoopInitGDPickDelay = msec; }
	if (nRun == INITIAL_LDPICKER)	{ m_dwLoopInitLDPickStart = GetTickCount();		m_dwLoopInitLDPickDelay = msec; }
	if (nRun == INITIAL_ULPICKER)	{ m_dwLoopInitULPickStart = GetTickCount();		m_dwLoopInitULPickDelay = msec; }
	if (nRun == INITIAL_INDEXT)		{ m_dwLoopInitIndexStart = GetTickCount();		m_dwLoopInitIndexDelay = msec; }
	if (nRun == INITIAL_NGTRAY)		{ m_dwLoopInitNGTrayStart = GetTickCount();		m_dwLoopInitNGTrayDelay = msec; }
				
	if (nRun == AUTO_LOAD1)			{ m_dwLoopLoadS1Start = GetTickCount();			m_dwLoopLoadS1Delay = msec; }
	if (nRun == AUTO_LOAD2)			{ m_dwLoopLoad2Start = GetTickCount();			m_dwLoopLoad2Delay = msec; }
	if (nRun == AUTO_UNLOAD1)		{ m_dwLoopUnload1Start = GetTickCount();		m_dwLoopUnload1Delay = msec; }
	if (nRun == AUTO_UNLOAD2)		{ m_dwLoopUnload2Start = GetTickCount();		m_dwLoopUnload2Delay = msec; }
	if (nRun == AUTO_INSPECT)		{ m_dwLoopInspectStart = GetTickCount();		m_dwLoopInspectDelay = msec; }
	if (nRun == AUTO_NGPICKER)		{ m_dwLoopNGPickStart = GetTickCount();			m_dwLoopNGPickDelay = msec; }
	if (nRun == AUTO_GDPICKER)		{ m_dwLoopGDPickStart = GetTickCount();			m_dwLoopGDPickDelay = msec; }
	if (nRun == AUTO_LDPICKER)		{ m_dwLoopLDPickStart = GetTickCount();			m_dwLoopLDPickDelay = msec; }
	if (nRun == AUTO_ULPICKER)		{ m_dwLoopULPickStart = GetTickCount();			m_dwLoopULPickDelay = msec; }
	if (nRun == AUTO_INDEXT)		{ m_dwLoopIndexStart = GetTickCount();			m_dwLoopIndexDelay = msec; }
	if (nRun == AUTO_NGTRAY)		{ m_dwLoopNGTrayStart = GetTickCount();			m_dwLoopNGTrayDelay = msec; }
	if (nRun == AUTO_BARCODE)		{ m_dwLoopBarcodeStart = GetTickCount();		m_dwLoopBarcodeDelay = msec; }
}

BOOL CCommon::Over_LoopTime(int nRun)
{
	DWORD dwLoopStart, dwLoopDelay;

	if (nRun == INITIAL_MAIN)		{ dwLoopStart = m_dwLoopInitMainStart;		dwLoopDelay = m_dwLoopInitMainDelay; }
	if (nRun == INITIAL_LOAD1)		{ dwLoopStart = m_dwLoopInitLoadS1Start;	dwLoopDelay = m_dwLoopInitLoadS1Delay; }
	if (nRun == INITIAL_LOAD2)		{ dwLoopStart = m_dwLoopInitLoad2Start;		dwLoopDelay = m_dwLoopInitLoad2Delay; }
	if (nRun == INITIAL_UNLOAD1)	{ dwLoopStart = m_dwLoopInitUnload1Start;	dwLoopDelay = m_dwLoopInitUnload1Delay; }
	if (nRun == INITIAL_UNLOAD2)	{ dwLoopStart = m_dwLoopInitUnload2Start;	dwLoopDelay = m_dwLoopInitUnload2Delay; }
	if (nRun == INITIAL_INSPECT)	{ dwLoopStart = m_dwLoopInitInspectStart;	dwLoopDelay = m_dwLoopInitInspectDelay; }
	if (nRun == INITIAL_NGPICKER)	{ dwLoopStart = m_dwLoopInitNGPickStart;	dwLoopDelay = m_dwLoopInitNGPickDelay; }
	if (nRun == INITIAL_GDPICKER)	{ dwLoopStart = m_dwLoopInitGDPickStart;	dwLoopDelay = m_dwLoopInitGDPickDelay; }
	if (nRun == INITIAL_LDPICKER)	{ dwLoopStart = m_dwLoopInitLDPickStart;	dwLoopDelay = m_dwLoopInitLDPickDelay; }
	if (nRun == INITIAL_ULPICKER)	{ dwLoopStart = m_dwLoopInitULPickStart;	dwLoopDelay = m_dwLoopInitULPickDelay; }
	if (nRun == INITIAL_INDEXT)		{ dwLoopStart = m_dwLoopInitIndexStart;		dwLoopDelay = m_dwLoopInitIndexDelay; }
	if (nRun == INITIAL_NGTRAY)		{ dwLoopStart = m_dwLoopInitNGTrayStart;	dwLoopDelay = m_dwLoopInitNGTrayDelay; }
				
	if (nRun == AUTO_LOAD1)			{ dwLoopStart = m_dwLoopLoadS1Start;		dwLoopDelay = m_dwLoopLoadS1Delay; }
	if (nRun == AUTO_LOAD2)			{ dwLoopStart = m_dwLoopLoad2Start;			dwLoopDelay = m_dwLoopLoad2Delay; }
	if (nRun == AUTO_UNLOAD1)		{ dwLoopStart = m_dwLoopUnload1Start;		dwLoopDelay = m_dwLoopUnload1Delay; }
	if (nRun == AUTO_UNLOAD2)		{ dwLoopStart = m_dwLoopUnload2Start;		dwLoopDelay = m_dwLoopUnload2Delay; }
	if (nRun == AUTO_INSPECT)		{ dwLoopStart = m_dwLoopInspectStart;		dwLoopDelay = m_dwLoopInspectDelay; }
	if (nRun == AUTO_NGPICKER)		{ dwLoopStart = m_dwLoopNGPickStart;		dwLoopDelay = m_dwLoopNGPickDelay; }
	if (nRun == AUTO_GDPICKER)		{ dwLoopStart = m_dwLoopGDPickStart;		dwLoopDelay = m_dwLoopGDPickDelay; }
	if (nRun == AUTO_LDPICKER)		{ dwLoopStart = m_dwLoopLDPickStart;		dwLoopDelay = m_dwLoopLDPickDelay; }
	if (nRun == AUTO_ULPICKER)		{ dwLoopStart = m_dwLoopULPickStart;		dwLoopDelay = m_dwLoopULPickDelay; }
	if (nRun == AUTO_INDEXT)		{ dwLoopStart = m_dwLoopIndexStart;			dwLoopDelay = m_dwLoopIndexDelay; }
	if (nRun == AUTO_NGTRAY)		{ dwLoopStart = m_dwLoopNGTrayStart;		dwLoopDelay = m_dwLoopNGTrayDelay; }
	if (nRun == AUTO_BARCODE)		{ dwLoopStart = m_dwLoopBarcodeStart;		dwLoopDelay = m_dwLoopBarcodeDelay; }

	DWORD dwTerm = GetTickCount() - dwLoopStart;
	if (dwTerm > dwLoopDelay) return TRUE;
	else return FALSE;
}

BOOL CCommon::Delay_LoopTime(int nRun, DWORD msec)
{
	DWORD dwLoopStart;

	if (nRun == INITIAL_MAIN)		dwLoopStart = m_dwLoopInitMainStart;		
	if (nRun == INITIAL_LOAD1)		dwLoopStart = m_dwLoopInitLoadS1Start;	
	if (nRun == INITIAL_LOAD2)		dwLoopStart = m_dwLoopInitLoad2Start;		
	if (nRun == INITIAL_UNLOAD1)	dwLoopStart = m_dwLoopInitUnload1Start;	
	if (nRun == INITIAL_UNLOAD2)	dwLoopStart = m_dwLoopInitUnload2Start;	
	if (nRun == INITIAL_INSPECT)	dwLoopStart = m_dwLoopInitInspectStart;	
	if (nRun == INITIAL_NGPICKER)	dwLoopStart = m_dwLoopInitNGPickStart;	
	if (nRun == INITIAL_GDPICKER)	dwLoopStart = m_dwLoopInitGDPickStart;	
	if (nRun == INITIAL_LDPICKER)	dwLoopStart = m_dwLoopInitLDPickStart;	
	if (nRun == INITIAL_ULPICKER)	dwLoopStart = m_dwLoopInitULPickStart;	
	if (nRun == INITIAL_INDEXT)		dwLoopStart = m_dwLoopInitIndexStart;		
	if (nRun == INITIAL_NGTRAY)		dwLoopStart = m_dwLoopInitNGTrayStart;	
				
	if (nRun == AUTO_LOAD1)			dwLoopStart = m_dwLoopLoadS1Start;	
	if (nRun == AUTO_LOAD2)			dwLoopStart = m_dwLoopLoad2Start;	
	if (nRun == AUTO_UNLOAD1)		dwLoopStart = m_dwLoopUnload1Start;	
	if (nRun == AUTO_UNLOAD2)		dwLoopStart = m_dwLoopUnload2Start;	
	if (nRun == AUTO_INSPECT)		dwLoopStart = m_dwLoopInspectStart;	
	if (nRun == AUTO_NGPICKER)		dwLoopStart = m_dwLoopNGPickStart;	
	if (nRun == AUTO_GDPICKER)		dwLoopStart = m_dwLoopGDPickStart;	
	if (nRun == AUTO_LDPICKER)		dwLoopStart = m_dwLoopLDPickStart;	
	if (nRun == AUTO_ULPICKER)		dwLoopStart = m_dwLoopULPickStart;	
	if (nRun == AUTO_INDEXT)		dwLoopStart = m_dwLoopIndexStart;	
	if (nRun == AUTO_NGTRAY)		dwLoopStart = m_dwLoopNGTrayStart;	
	if (nRun == AUTO_BARCODE)		dwLoopStart = m_dwLoopBarcodeStart;	

	DWORD dwTerm = GetTickCount() - dwLoopStart;
	if (dwTerm > msec) return TRUE;
	else return FALSE;
}

BOOL CCommon::Check_Position(int nAxis, int nMoveIdx)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(nAxis);

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	double dCheckPos = -1.0;

	if (pAJinAXL->Is_Done(nAxis)) {
		if (nAxis == AX_LOAD_TRAY_X1)			dCheckPos = pMoveData->dLoadTrayX1[nMoveIdx];
		if (nAxis == AX_LOAD_TRAY_X2)			dCheckPos = pMoveData->dLoadTrayX2[nMoveIdx]; 
		if (nAxis == AX_LOAD_TRAY_Z1)			dCheckPos = pMoveData->dLoadTrayZ1[nMoveIdx]; 
		if (nAxis == AX_LOAD_TRAY_Z2)			dCheckPos = pMoveData->dLoadTrayZ2[nMoveIdx]; 
		if (nAxis == AX_LOAD_PICKER_Y1)			dCheckPos = pMoveData->dLoadPickerY1[nMoveIdx];  
		if (nAxis == AX_LOAD_PICKER_Z)			dCheckPos = pMoveData->dLoadPickerZ[nMoveIdx];   
		if (nAxis == AX_LOAD_PICKER_Y2)			dCheckPos = pMoveData->dLoadPickerY2[nMoveIdx];  
		if (nAxis == AX_INDEX_R)				dCheckPos = pMoveData->dIndexR[nMoveIdx];
		if (nAxis == AX_BARCODE_A)				dCheckPos = pMoveData->dBarCodeA[nMoveIdx];
		if (nAxis == AX_INSPECTION_A)			dCheckPos = pMoveData->dInspectionA[nMoveIdx];   
		if (nAxis == AX_INSPECTION_Z)			dCheckPos = pMoveData->dInspectionZ[nMoveIdx];   
		if (nAxis == AX_NG_PICKER_X)			dCheckPos = pMoveData->dNGPickerX[nMoveIdx];     
		if (nAxis == AX_NG_PICKER_Z)			dCheckPos = pMoveData->dNGPickerZ[nMoveIdx];     
		if (nAxis == AX_NG_STAGE_Y)				dCheckPos = pMoveData->dNGStageY[nMoveIdx];
		if (nAxis == AX_GOOD_PICKER_Y)			dCheckPos = pMoveData->dGdPickerY[nMoveIdx];     
		if (nAxis == AX_GOOD_PICKER_Z)			dCheckPos = pMoveData->dGdPickerZ[nMoveIdx];    
		if (nAxis == AX_UNLOAD_PICKER_X1)		dCheckPos = pMoveData->dUnloadPickerX1[nMoveIdx];
		if (nAxis == AX_UNLOAD_PICKER_Z)		dCheckPos = pMoveData->dUnloadPickerZ[nMoveIdx]; 
		if (nAxis == AX_UNLOAD_PICKER_X2)		dCheckPos = pMoveData->dUnloadPickerX2[nMoveIdx];
		if (nAxis == AX_UNLOAD_TRAY_Y1)			dCheckPos = pMoveData->dUnloadTrayY1[nMoveIdx];  
		if (nAxis == AX_UNLOAD_TRAY_Y2)			dCheckPos = pMoveData->dUnloadTrayY2[nMoveIdx];  
		if (nAxis == AX_UNLOAD_TRAY_Z1)			dCheckPos = pMoveData->dUnloadTrayZ1[nMoveIdx];  
		if (nAxis == AX_UNLOAD_TRAY_Z2)			dCheckPos = pMoveData->dUnloadTrayZ2[nMoveIdx];  

		if (nAxis == AX_INDEX_R) {
			if (fabs(pStatus->dPos - dCheckPos) < 0.01) return TRUE;
		} else {
			if (fabs(pStatus->dPos - dCheckPos) < 0.1) return TRUE;
		}

	} else return FALSE;

	return FALSE;
}

void CCommon::Move_Position(int nAxis, int nMoveIdx)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(nAxis);

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	double dMovePos = -999;
	double dAccel = 1000;

	if (nAxis == AX_LOAD_TRAY_X1)		{	dMovePos = pMoveData->dLoadTrayX1[nMoveIdx];		dAccel = pMoveData->dDLoadTrayX1[nMoveIdx];       }
	if (nAxis == AX_LOAD_TRAY_X2)		{	dMovePos = pMoveData->dLoadTrayX2[nMoveIdx]; 		dAccel = pMoveData->dDLoadTrayX2[nMoveIdx]; 	   }
	if (nAxis == AX_LOAD_TRAY_Z1)		{	dMovePos = pMoveData->dLoadTrayZ1[nMoveIdx]; 		dAccel = pMoveData->dDLoadTrayZ1[nMoveIdx]; 	   }
	if (nAxis == AX_LOAD_TRAY_Z2)		{	dMovePos = pMoveData->dLoadTrayZ2[nMoveIdx]; 		dAccel = pMoveData->dDLoadTrayZ2[nMoveIdx]; 	   }
	if (nAxis == AX_LOAD_PICKER_Y1)		{	dMovePos = pMoveData->dLoadPickerY1[nMoveIdx];  	dAccel = pMoveData->dDLoadPickerY1[nMoveIdx];     }
	if (nAxis == AX_LOAD_PICKER_Z)		{	dMovePos = pMoveData->dLoadPickerZ[nMoveIdx];   	dAccel = pMoveData->dDLoadPickerZ[nMoveIdx];      }
	if (nAxis == AX_LOAD_PICKER_Y2)		{	dMovePos = pMoveData->dLoadPickerY2[nMoveIdx];  	dAccel = pMoveData->dDLoadPickerY2[nMoveIdx];     }
//	if (nAxis == AX_INDEX_R)			{	dMovePos = pMoveData->dIndexR[nMoveIdx];			dAccel = pMoveData->dDIndexR[nMoveIdx];		   }
	if (nAxis == AX_BARCODE_A)			{	dMovePos = pMoveData->dBarCodeA[nMoveIdx];			dAccel = pMoveData->dDBarCodeA[nMoveIdx];		   }
	if (nAxis == AX_INSPECTION_A)		{	dMovePos = pMoveData->dInspectionA[nMoveIdx];   	dAccel = pMoveData->dDInspectionA[nMoveIdx];      }
	if (nAxis == AX_INSPECTION_Z)		{	dMovePos = pMoveData->dInspectionZ[nMoveIdx];   	dAccel = pMoveData->dDInspectionZ[nMoveIdx];      }
	if (nAxis == AX_NG_PICKER_X)		{	dMovePos = pMoveData->dNGPickerX[nMoveIdx];     	dAccel = pMoveData->dDNGPickerX[nMoveIdx];        }
	if (nAxis == AX_NG_PICKER_Z)		{	dMovePos = pMoveData->dNGPickerZ[nMoveIdx];     	dAccel = pMoveData->dDNGPickerZ[nMoveIdx];        }
	if (nAxis == AX_NG_STAGE_Y)			{	dMovePos = pMoveData->dNGStageY[nMoveIdx];			dAccel = pMoveData->dDNGStageY[nMoveIdx];		   }
	if (nAxis == AX_GOOD_PICKER_Y)		{	dMovePos = pMoveData->dGdPickerY[nMoveIdx];     	dAccel = pMoveData->dDGdPickerY[nMoveIdx];        }
	if (nAxis == AX_GOOD_PICKER_Z)		{	dMovePos = pMoveData->dGdPickerZ[nMoveIdx];    		dAccel = pMoveData->dDGdPickerZ[nMoveIdx];    	   }
	if (nAxis == AX_UNLOAD_PICKER_X1)	{	dMovePos = pMoveData->dUnloadPickerX1[nMoveIdx];	dAccel = pMoveData->dDUnloadPickerX1[nMoveIdx];   }
	if (nAxis == AX_UNLOAD_PICKER_Z)	{	dMovePos = pMoveData->dUnloadPickerZ[nMoveIdx]; 	dAccel = pMoveData->dDUnloadPickerZ[nMoveIdx];    }
	if (nAxis == AX_UNLOAD_PICKER_X2)	{	dMovePos = pMoveData->dUnloadPickerX2[nMoveIdx];	dAccel = pMoveData->dDUnloadPickerX2[nMoveIdx];   }
	if (nAxis == AX_UNLOAD_TRAY_Y1)		{	dMovePos = pMoveData->dUnloadTrayY1[nMoveIdx];  	dAccel = pMoveData->dDUnloadTrayY1[nMoveIdx];     }
	if (nAxis == AX_UNLOAD_TRAY_Y2)		{	dMovePos = pMoveData->dUnloadTrayY2[nMoveIdx];  	dAccel = pMoveData->dDUnloadTrayY2[nMoveIdx];     }
	if (nAxis == AX_UNLOAD_TRAY_Z1)		{	dMovePos = pMoveData->dUnloadTrayZ1[nMoveIdx];  	dAccel = pMoveData->dDUnloadTrayZ1[nMoveIdx];     }
	if (nAxis == AX_UNLOAD_TRAY_Z2)		{	dMovePos = pMoveData->dUnloadTrayZ2[nMoveIdx];  	dAccel = pMoveData->dDUnloadTrayZ2[nMoveIdx];     }

	if (nAxis == AX_INDEX_R)	{
		pAJinAXL->Set_CVActPos(nAxis);
		dMovePos = pMoveData->dIndexR[nMoveIdx];	dAccel = pMoveData->dDIndexR[nMoveIdx];
	}

	if (dMovePos == -999) return;
	//pAJinAXL->Move_Absolute(nAxis, dMovePos);
	pAJinAXL->Move_Abs_Accel(nAxis, dMovePos, dAccel);
}

void CCommon::Show_Error(int nErrNo)
{
	if (gData.m_bErrorShow) return;

	CErrorDlg *pErrorDlg = CErrorDlg::Get_Instance();
	pErrorDlg->Set_ErrorNumber(nErrNo);
	if(nErrNo>=9901) pErrorDlg->Set_ErrorMessage(m_sMessage);
	pErrorDlg->ShowWindow(SW_SHOW);

	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	pWorkDlg->m_rdoWorkStop.SetCheck(TRUE);
}

int CCommon::Show_MsgBox(int nBtnCnt, CString sMsg)
{
	CMsgBoxDlg dlgMsgBox;
	dlgMsgBox.Set_Message(nBtnCnt, sMsg);
	return dlgMsgBox.DoModal();
}

int CCommon::Show_NumPad(CString sOld, CString &sNew)
{
	CNumPadDlg dlgNumPad;
	dlgNumPad.Set_OldValue(sOld);
	if (dlgNumPad.DoModal() == IDOK) {
		sNew = g_strReturnNumPad;
		return IDOK;
	} else return IDCANCEL;
}

int CCommon::Show_KeyPad(CString &sKey)
{
	CKeyPadDlg dlgKeyPad;
	if (dlgKeyPad.DoModal() == IDOK) {
		sKey = g_strReturnKeyPad;
		return IDOK;
	} else return IDCANCEL;
}

int CCommon::Show_Password()
{
	CPasswordDlg dlgPassword;
	return dlgPassword.DoModal();
}

BOOL CCommon::Check_MainEmgAir()
{
#ifdef AJIN_BOARD_USE
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	if (pDX0->iEMS1)	{ Show_Error(1); return FALSE; }
	if (pDX0->iEMS2)	{ Show_Error(2); return FALSE; }
	if (pDX0->iEMS3)	{ Show_Error(3); return FALSE; }
	if (pDX0->iEMS4)	{ Show_Error(4); return FALSE; }
	//if (pDX0->iEMS5)	{ Show_Error(5); return FALSE; }
	//if (pDX0->iEMS6)	{ Show_Error(6); return FALSE; }

	if (!pDX0->iMainAir1)	{ Show_Error(7); return FALSE; }
#ifdef ALIGN_NEW
	if (!pDX0->iMainAir2)	{ Show_Error(8); return FALSE; }
#endif

#endif
	return TRUE;
}

BOOL CCommon::Check_MainDoor()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	if (!pEquipData->bUseDoorLock) return TRUE;

#ifdef AJIN_BOARD_USE
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();

	if (!pDX0->iMainDoor1Close  && gData.nDoorInterlock18 != 1)		{ Show_Error(11); return FALSE; }
	if (!pDX0->iMainDoor2Close)										{ Show_Error(12); return FALSE; }
	if (!pDX0->iMainDoor3Close)										{ Show_Error(13); return FALSE; }
// 	if (!pDX0->iMainDoor4Close)										{ Show_Error(14); return FALSE; }
// 	if (!pDX0->iMainDoor5Close)										{ Show_Error(15); return FALSE; }
	if (!pDX0->iMainDoor6Close  && gData.nDoorInterlock67 != 1)		{ Show_Error(16); return FALSE; }
	if (!pDX0->iMainDoor7Close  && gData.nDoorInterlock67 != 1)		{ Show_Error(17); return FALSE; }
	if (!pDX0->iMainDoor8Close  && gData.nDoorInterlock18 != 1)		{ Show_Error(18); return FALSE; }

#endif
	return TRUE;
}

// Servo On Error : Error (100 - 127)
BOOL CCommon::Check_ServoOn()
{
#ifdef AJIN_BOARD_USE
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	for (int i = 0; i < AXIS_COUNT; i++) {
		AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(i);
		if (!pStatus->bSOn) { Show_Error(i + 100); return FALSE; }
	}
#endif
	return TRUE;
}

// Drive Alarm : Error(200 - 227)
BOOL CCommon::Check_DirveAlarm()
{
#ifdef AJIN_BOARD_USE
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	for (int i = 0; i < AXIS_COUNT; i++) {
		AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(i);

		if (pStatus->bALM) 
		{ 
			Show_Error(i + 200); 
			return FALSE; 
		}
	}
#endif
	return TRUE;
}

// Limit Check : Error ELN(300 - 327), ELP(400 - 427)
BOOL CCommon::Check_EndLimit()
{
#ifdef AJIN_BOARD_USE
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	for (int i = 0; i < AXIS_COUNT; i++) {
		AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(i);

		if (pStatus->bELN) { Show_Error(i + 300); return FALSE; }
		if (pStatus->bELP) { Show_Error(i + 400); return FALSE; }
	}
#endif
	return TRUE;
}

// Home Check : Error (500 - 527)
BOOL CCommon::Check_HomeDone()
{
#ifdef AJIN_BOARD_USE
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	for (int i = 0; i < AXIS_COUNT; i++) {
		if((i>=0 && i<=3) || (i>=19 && i<=22) || i==AX_INDEX_R) continue;

		AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(i);

		if (!pStatus->bHom) { Show_Error(i + 500); return FALSE; }
	}
#endif
	return TRUE;
}

BOOL CCommon::Check_Run(int nAxis)
{
#ifdef AJIN_BOARD_USE
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(nAxis);
	if (pStatus->bRun) return TRUE;
#endif
	return FALSE;
}

void CCommon::Locking_MainDoor(BOOL bLock, BOOL bAuto)
{
/*
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	if (bLock) {
		if (!pEquipData->bUseDoorLock && bAuto) {
			if (pDX0->iMainDoor1Close && pDX0->iMainDoor2Close && pDX0->iMainDoor3Close && pDX0->iMainDoor4Close && pDX0->iMainDoor5Close && 
				pDX0->iMainDoor6Close && pDX0->iMainDoor7Close && pDX0->iMainDoor8Close){
				pDY0->oMainDoor1Lock = TRUE;
				pDY0->oMainDoor2Lock = TRUE;
				pDY0->oMainDoor3Lock = TRUE;
				pDY0->oMainDoor4Lock = TRUE;
				pDY0->oMainDoor5Lock = TRUE;
				pDY0->oMainDoor6Lock = TRUE;
				pDY0->oMainDoor7Lock = TRUE;
				pAJinAXL->Write_Output(0);

				CIniFileCS INI("System/EquipData.ini");
				INI.Set_Bool("OPTION", "DOOR_LOCK", TRUE);
				pEquipData->bUseDoorLock = TRUE;				
			}
		} else {
			pDY0->oMainDoor1Lock = TRUE;
			pDY0->oMainDoor2Lock = TRUE;
			pDY0->oMainDoor3Lock = TRUE;
			pDY0->oMainDoor4Lock = TRUE;
			pDY0->oMainDoor5Lock = TRUE;
			pDY0->oMainDoor6Lock = TRUE;
			pDY0->oMainDoor7Lock = TRUE;
			pAJinAXL->Write_Output(0);
		}

	} else {
#ifdef AJIN_BOARD_USE
		while (TRUE) {
			int i = 0;
			for (i = 0; i < AXIS_COUNT; i++) {
				AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(i);
				if (pStatus->bRun) break;
			}
			if (i == AXIS_COUNT) break;
			DoEvents();
		}
#endif	
		pDY0->oMainDoor1Lock = FALSE;
		pDY0->oMainDoor2Lock = FALSE;
		pDY0->oMainDoor3Lock = FALSE;
		pDY0->oMainDoor4Lock = FALSE;
		pDY0->oMainDoor5Lock = FALSE;
		pDY0->oMainDoor6Lock = FALSE;
		pDY0->oMainDoor7Lock = FALSE;
		pAJinAXL->Write_Output(0);
	}
*/
}

void CCommon::Check_InsideLamp()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	if (pDX0->iMainDoor1Close && pDX0->iMainDoor2Close && pDX0->iMainDoor3Close && /*pDX0->iMainDoor4Close && pDX0->iMainDoor5Close &&*/ 
		pDX0->iMainDoor6Close && pDX0->iMainDoor7Close && pDX0->iMainDoor8Close){
			if (m_bInsideLamp) {
				m_bInsideLamp     = FALSE;
				pDY0->oInsideLamp = FALSE;
				pAJinAXL->Write_Output(0);
			}
	} else {
		if (!m_bInsideLamp) {
			m_bInsideLamp = TRUE;
			pDY0->oInsideLamp = TRUE;
			pAJinAXL->Write_Output(0);
		}
	}
}

void CCommon::Check_SystemReady()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	//if (pDX0->iEmoResetSw) {
	//	if (!m_bSystemReadyRelay) {
	//		m_bSystemReadyRelay = TRUE;
	//		pDY0->oSystemReady = TRUE;
	//		pAJinAXL->Write_Output(0);
	//	}
	//} else {
	//	if (m_bSystemReadyRelay) {
	//		m_bSystemReadyRelay = FALSE;
	//		pDY0->oSystemReady = FALSE;
	//		pAJinAXL->Write_Output(0);
	//	}
	//}
}

void CCommon::Check_PowerOffSw()
{
// 	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
// 	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
// 	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();
// 
// 	if (pDX0->iPowerOffSw) {
// 		if (!m_bPowerOffRelay) {
// 			m_bPowerOffRelay = TRUE;
// 			pDY0->oPowerOffRelay = TRUE;
// 			pAJinAXL->Write_Output(0);
// 			Sleep(500);
// 			CLogFile *pLogFile = CLogFile::Get_Instance();
// 			pLogFile->Save_HandlerLog("[Common Check] Power Off S/W 누름");
// 		}
// 	} else {
// 		if (m_bPowerOffRelay) {
// 			m_bPowerOffRelay = FALSE;
// 			pDY0->oPowerOffRelay = FALSE;
// 			pAJinAXL->Write_Output(0);
// 		}
// 	}
}

CString CCommon::Get_AdrIpAddress(CString sName)
{
	CString strIp;
/*
	if		(sName == "MAI401") strIp = "12.98.22.43";	// 1호기(4L6F)
	else if (sName == "MAI501") strIp = "12.98.22.43";	// 2호기(4L3F)
	else if (sName == "MAI201") strIp = "12.98.22.57";	// 3호기(2L1F)
	else if (sName == "MAI101") strIp = "12.98.22.77";	// 4호기(1L1F)
	else if (sName == "MAI301") strIp = "12.98.22.77";	// 5호기(3L1F)
	else if (sName == "MAI202") strIp = "12.98.22.57";	// 6호기(2L2F)
	else if (sName == "AQE01")  strIp = "12.98.59.28";	// 7호기(천안 3L3F)
	else						strIp = "127.0.0.1";	// Local_ip
*/
	strIp = "127.0.0.1";	// Local_ip
	return strIp;
}

CString CCommon::Get_MonitorName(CString sName)
{
	CString strFile;
	if		(sName == "MAI401") strFile = "\\MonitorEQP_22";	// 1호기(4L6F)
	else if (sName == "MAI501") strFile = "\\MonitorEQP_23";	// 2호기(4L3F)
	else if (sName == "MAI201") strFile = "\\MonitorEQP_19";	// 3호기(2L1F)
	else if (sName == "MAI101") strFile = "\\MonitorEQP_18";	// 4호기(1L1F)
	else if (sName == "MAI301") strFile = "\\MonitorEQP_21";	// 5호기(3L1F)
	else if (sName == "MAI202") strFile = "\\MonitorEQP_20";	// 6호기(2L2F)
	else if (sName == "AQE01")  strFile = "\\MonitorEQP_00";	// 7호기(천안 3L3F)
	else						strFile = "\\MonitorEQP_00";	// Default
	return strFile;
}

void CCommon::Check_MonitorEQP(int nStatus)
{
	if (m_nStatus == nStatus) return;

	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
	if (!Connect_NetworkDrive(NETWORK_EQP_DRIVE, NETWORK_EQP_FOLDER)) {
		Show_Error(611);
		return;
	}

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	CString strMonitor = Get_MonitorName(pEquipData->sEquipName);
	CIniFileCS INI(NETWORK_EQP_DRIVE + strMonitor + ".ini");

	INI.Set_Integer(strMonitor.Right(2), "status", nStatus);	// 0:Run, 1:Stop, 2:Error
	m_nStatus = nStatus;

	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	int nCount = pWorkDlg->GetCount_ConveyorList();
	INI.Set_Integer(strMonitor.Right(2), "standby", nCount);	// Conveyor List Lot Count

}

BOOL CCommon::Connect_NetworkDrive(CString sDrive, CString sFolder)
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	CString strIp = Get_AdrIpAddress(pEquipData->sEquipName);
	CString strPath = "\\\\" + strIp + sFolder;

	char szRemote[128];
	DWORD dwLen = sizeof(szRemote); 

	DWORD dwReturn = WNetGetConnection((LPCSTR)sDrive, szRemote, &dwLen);
	if (dwReturn == NO_ERROR) {
		int nExist = GetFileAttributes(sDrive);
		if (nExist == -1) {		// Not Connected
			dwReturn = WNetCancelConnection(sDrive, TRUE);
			if (dwReturn != NO_ERROR) return FALSE;		// 삭제 실패
		} else return TRUE;

	} else if (dwReturn == ERROR_CONNECTION_UNAVAIL) {
		dwReturn = WNetCancelConnection(sDrive, TRUE);
		if (dwReturn != NO_ERROR) return FALSE;		// 삭제 실패
	}

	NETRESOURCE NetR;
	NetR.dwType = RESOURCETYPE_DISK;			// 공유 디스크
	NetR.lpLocalName = (LPSTR)(LPCSTR)sDrive;	// 로컬 드라이브
	NetR.lpRemoteName = (LPSTR)(LPCSTR)strPath;	// 경로
	NetR.lpProvider = NULL;

	DWORD dwFlag = CONNECT_UPDATE_PROFILE;		// CONNECT_REDIRECT;
	dwReturn = WNetAddConnection2(&NetR, "mirero", "Administrator", dwFlag);
	if (dwReturn == NO_ERROR) return TRUE;		// Success Connect
	else return FALSE;							// Fail Connect
}

BOOL CCommon::Open_Ftp()
{
	if (m_pFtp) return FALSE;
	try {
		CDataManager *pDataManager = CDataManager::Get_Instance();
		EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

		CString strIp = Get_AdrIpAddress(pEquipData->sEquipName);
		m_pFtp = m_Session.GetFtpConnection(strIp, "Administrator", "mirero");
		if (!m_pFtp) return FALSE;

	} catch (CInternetException *pEx) {
		delete m_pFtp;
		m_pFtp = NULL;
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

void CCommon::Close_Ftp()
{
	if (!m_pFtp) return;

	m_pFtp->Close();
	delete m_pFtp;
	m_pFtp = NULL;
}

void CCommon::Copy_AdrData()
{
	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();

#ifdef FTP_USE
	if (!Open_Ftp()) {
		Show_Error(612);
#else
	if (!Connect_NetworkDrive(NETWORK_ADR_DRIVE, NETWORK_ADR_FOLDER)) {
		Show_Error(610);
#endif
		return;
	}

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	CString strSourceImage = "D:\\Inspection\\ADR_DATA\\SEND\\IMAGE\\*.*";
	CString strSourceData = "D:\\Inspection\\ADR_DATA\\SEND\\DATA\\*.*";
	CString strTarget;
#ifdef FTP_USE
	strTarget.Format("%s\\%s\\input\\", NETWORK_FTP_FOLDER, pEquipData->sEquipName);
#else
	strTarget.Format("%s\\%s\\input\\", NETWORK_ADR_DRIVE, pEquipData->sEquipName);
#endif

	int nImgOk = 0, nImgFail = 0, nDatOk = 0, nDatFail = 0;

	CFileFind Finder;
	BOOL bExist = Finder.FindFile(strSourceImage);
	while (bExist) {
		bExist = Finder.FindNextFile();
		if (Finder.IsDirectory()) continue;
		CString strFile = strTarget + Finder.GetFileName();
#ifdef FTP_USE
		if (m_pFtp->PutFile(Finder.GetFilePath(), strFile)) {
#else
		if (CopyFile(Finder.GetFilePath(), strFile, FALSE)) {
#endif
			nImgOk++;
			DeleteFile(Finder.GetFilePath());
		} else nImgFail++;
	}

	bExist = Finder.FindFile(strSourceData);
	while (bExist) {
		bExist = Finder.FindNextFile();
		if (Finder.IsDirectory()) continue;
		CString strFile = strTarget + Finder.GetFileName();
#ifdef FTP_USE
		if (m_pFtp->PutFile(Finder.GetFilePath(), strFile)) {
#else
		if (CopyFile(Finder.GetFilePath(), strFile, FALSE)) {
#endif
			nDatOk++;
			DeleteFile(Finder.GetFilePath());
		} else nDatFail++;
	}

#ifdef FTP_USE
	Close_Ftp();
#endif

	// Inspector Log //////////////////////////////////////
	CString strLog;
	CLogFile *pLogFile = CLogFile::Get_Instance();
	strLog.Format("[H->ADR] : Image(OK:%d, Fail:%d) and Data(OK:%d, Fail:%d) File Moved", nImgOk, nImgFail, nDatOk, nDatFail);
	pLogFile->Save_InspectorLog(strLog);
	///////////////////////////////////////////////////////
}

void CCommon::Copy_AdrDData()
{
#ifdef ADR_D_USE
	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	CString strSourceImage = "D:\\Inspection\\ADR_DATA\\SEND\\IMAGE\\*.*";
	CString strSourceData = "D:\\Inspection\\ADR_DATA\\SEND\\DATA\\*.*";
	CString strTarget;
	strTarget.Format("D:\\datamanager\\inspection\\%s\\input\\", pEquipData->sEquipName);

	int nImgOk = 0, nImgFail = 0, nDatOk = 0, nDatFail = 0;

	CFileFind Finder;
	BOOL bExist = Finder.FindFile(strSourceImage);
	while (bExist) {
		bExist = Finder.FindNextFile();
		if (Finder.IsDirectory()) continue;
		CString strFile = strTarget + Finder.GetFileName();
		if (CopyFile(Finder.GetFilePath(), strFile, FALSE)) {
			nImgOk++;
			DeleteFile(Finder.GetFilePath());
		} else nImgFail++;
	}

	bExist = Finder.FindFile(strSourceData);
	while (bExist) {
		bExist = Finder.FindNextFile();
		if (Finder.IsDirectory()) continue;
		CString strFile = strTarget + Finder.GetFileName();
		if (CopyFile(Finder.GetFilePath(), strFile, FALSE)) {
			nDatOk++;
			DeleteFile(Finder.GetFilePath());
		} else nDatFail++;
	}

	// Inspector Log //////////////////////////////////////
	CString strLog;
	CLogFile *pLogFile = CLogFile::Get_Instance();
	strLog.Format("[H->HDD] : Image(OK:%d, Fail:%d) and Data(OK:%d, Fail:%d) File Moved", nImgOk, nImgFail, nDatOk, nDatFail);
	pLogFile->Save_InspectorLog(strLog);
	///////////////////////////////////////////////////////
#endif
}

void CCommon::Backup_File(CString strPath, CString strName)
{
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Create_Folder(strPath + "\\Backup");

	CString strOriginFile, strTargetFile, strDateTime;

	SYSTEMTIME time;
	GetLocalTime(&time);
	strDateTime.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	strOriginFile.Format("%s\\%s.ini", strPath, strName);
	strTargetFile.Format("%s\\Backup\\%s_%s.ini", strPath, strName, strDateTime);

	if (!CopyFile(strOriginFile, strTargetFile, FALSE)) return;
}

int CCommon::Get_Random(int nStart, int nEnd)
{
	static BOOL bSeed = FALSE;
	if (nStart >= nEnd) return 0;
	if (!bSeed) { srand((unsigned)time(NULL)); bSeed = TRUE; }
	return (rand() % (nEnd - nStart + 1) + nStart);
}
/////////////////////////////////////////////////////////////////////////////

void CCommon::Wait_Time(DWORD msec)
{
	DWORD timeS = GetTickCount();
	DWORD dwTerm = 0;

	do {
		DoEvents();
		DWORD timeE = GetTickCount();
		dwTerm = (timeE - timeS);
	} while (dwTerm < msec);
}

CString CCommon::Make_HexToChar(CString sRecv)
{
	int nLen = sRecv.GetLength();
	if (nLen % 2) return "";

	CString strChar = "", strTemp;
	for (int i = 0; i < nLen / 2; i++) {
		CString strHex = sRecv.Mid(i * 2, 2);
		UINT nChar = strtol(strHex, NULL, 16);
		strTemp.Format("%c", nChar);
		if(i==0)	strChar = strTemp;
		else		strChar = strTemp + strChar;
	}
	return strChar;
}

int CCommon::Make_HexToInt1st(long lValue)
{
	UINT nChar;
	CString sRecv;

	sRecv.Format("%04X", lValue);
	CString strHex = sRecv.Mid(2, 2);
	nChar = strtol(strHex, NULL, 16);
	return nChar;
}

int CCommon::Make_HexToInt2nd(long lValue)
{
	UINT nChar;
	CString sRecv;

	sRecv.Format("%04X", lValue);
	CString strHex = sRecv.Mid(0, 2);
	nChar = strtol(strHex, NULL, 16);
	return nChar;
}

void CCommon::Make_LongToSplit(long lValue)
{
	DWORD dwStatus, dw1st, dw2nd, m_l1st, m_l2nd;

	dw1st = dw2nd = m_l1st = m_l2nd = 0;
	dwStatus = lValue;

	if((dwStatus >>  0) & 0x1) dw1st = dw1st|0X0001;	//0000000000000001
	if((dwStatus >>  1) & 0x1) dw1st = dw1st|0X0002;	//0000000000000010
	if((dwStatus >>  2) & 0x1) dw1st = dw1st|0X0004;	//0000000000000100
	if((dwStatus >>  3) & 0x1) dw1st = dw1st|0X0008;	//0000000000001000
	if((dwStatus >>  4) & 0x1) dw1st = dw1st|0X0010;	//0000000000010000
	if((dwStatus >>  5) & 0x1) dw1st = dw1st|0X0020;	//0000000000100000
	if((dwStatus >>  6) & 0x1) dw1st = dw1st|0X0040;	//0000000001000000
	if((dwStatus >>  7) & 0x1) dw1st = dw1st|0X0080;	//0000000010000000
	if((dwStatus >>  8) & 0x1) dw1st = dw1st|0X0100;	//0000000100000000
	if((dwStatus >>  9) & 0x1) dw1st = dw1st|0X0200;	//0000001000000000
	if((dwStatus >> 10) & 0x1) dw1st = dw1st|0X0400;	//0000010000000000
	if((dwStatus >> 11) & 0x1) dw1st = dw1st|0X0800;	//0000100000000000
	if((dwStatus >> 12) & 0x1) dw1st = dw1st|0X1000;	//0001000000000000
	if((dwStatus >> 13) & 0x1) dw1st = dw1st|0X2000;	//0010000000000000
	if((dwStatus >> 14) & 0x1) dw1st = dw1st|0X4000;	//0100000000000000
	if((dwStatus >> 15) & 0x1) dw1st = dw1st|0X8000;	//1000000000000000
	
	if((dwStatus >> 16) & 0x1) dw2nd = dw2nd|0X0001;	//0000000000000001
	if((dwStatus >> 17) & 0x1) dw2nd = dw2nd|0X0002;	//0000000000000010
	if((dwStatus >> 18) & 0x1) dw2nd = dw2nd|0X0004;	//0000000000000100
	if((dwStatus >> 19) & 0x1) dw2nd = dw2nd|0X0008;	//0000000000001000
	if((dwStatus >> 20) & 0x1) dw2nd = dw2nd|0X0010;	//0000000000010000
	if((dwStatus >> 21) & 0x1) dw2nd = dw2nd|0X0020;	//0000000000100000
	if((dwStatus >> 22) & 0x1) dw2nd = dw2nd|0X0040;	//0000000001000000
	if((dwStatus >> 23) & 0x1) dw2nd = dw2nd|0X0080;	//0000000010000000
	if((dwStatus >> 24) & 0x1) dw2nd = dw2nd|0X0100;	//0000000100000000
	if((dwStatus >> 25) & 0x1) dw2nd = dw2nd|0X0200;	//0000001000000000
	if((dwStatus >> 26) & 0x1) dw2nd = dw2nd|0X0400;	//0000010000000000
	if((dwStatus >> 27) & 0x1) dw2nd = dw2nd|0X0800;	//0000100000000000
	if((dwStatus >> 28) & 0x1) dw2nd = dw2nd|0X1000;	//0001000000000000
	if((dwStatus >> 29) & 0x1) dw2nd = dw2nd|0X2000;	//0010000000000000
	if((dwStatus >> 30) & 0x1) dw2nd = dw2nd|0X4000;	//0100000000000000
	if((dwStatus >> 31) & 0x1) dw2nd = dw2nd|0X8000;	//1000000000000000

	m_l1st = dw1st;
	m_l2nd = dw2nd;
}

long CCommon::Make_LongToMix(long l1st, long l2nd)
{
	long lValue;
	DWORD dwStatus, dw1st, dw2nd;
	dwStatus = 0;

	dw1st = l1st;
	if((dw1st >>  0) & 0x1) dwStatus = dwStatus|0X00000001;	//0000000000000001
	if((dw1st >>  1) & 0x1) dwStatus = dwStatus|0X00000002;	//0000000000000010
	if((dw1st >>  2) & 0x1) dwStatus = dwStatus|0X00000004;	//0000000000000100
	if((dw1st >>  3) & 0x1) dwStatus = dwStatus|0X00000008;	//0000000000001000
	if((dw1st >>  4) & 0x1) dwStatus = dwStatus|0X00000010;	//0000000000010000
	if((dw1st >>  5) & 0x1) dwStatus = dwStatus|0X00000020;	//0000000000100000
	if((dw1st >>  6) & 0x1) dwStatus = dwStatus|0X00000040;	//0000000001000000
	if((dw1st >>  7) & 0x1) dwStatus = dwStatus|0X00000080;	//0000000010000000
	if((dw1st >>  8) & 0x1) dwStatus = dwStatus|0X00000100;	//0000000100000000
	if((dw1st >>  9) & 0x1) dwStatus = dwStatus|0X00000200;	//0000001000000000
	if((dw1st >> 10) & 0x1) dwStatus = dwStatus|0X00000400;	//0000010000000000
	if((dw1st >> 11) & 0x1) dwStatus = dwStatus|0X00000800;	//0000100000000000
	if((dw1st >> 12) & 0x1) dwStatus = dwStatus|0X00001000;	//0001000000000000
	if((dw1st >> 13) & 0x1) dwStatus = dwStatus|0X00002000;	//0010000000000000
	if((dw1st >> 14) & 0x1) dwStatus = dwStatus|0X00004000;	//0100000000000000
	if((dw1st >> 15) & 0x1) dwStatus = dwStatus|0X00008000;	//1000000000000000
	
	dw2nd = l2nd;
	if((dw2nd >>  0) & 0x1) dwStatus = dwStatus|0X00010000;	//0000000000000001
	if((dw2nd >>  1) & 0x1) dwStatus = dwStatus|0X00020000;	//0000000000000010
	if((dw2nd >>  2) & 0x1) dwStatus = dwStatus|0X00040000;	//0000000000000100
	if((dw2nd >>  3) & 0x1) dwStatus = dwStatus|0X00080000;	//0000000000001000
	if((dw2nd >>  4) & 0x1) dwStatus = dwStatus|0X00100000;	//0000000000010000
	if((dw2nd >>  5) & 0x1) dwStatus = dwStatus|0X00200000;	//0000000000100000
	if((dw2nd >>  6) & 0x1) dwStatus = dwStatus|0X00400000;	//0000000001000000
	if((dw2nd >>  7) & 0x1) dwStatus = dwStatus|0X00800000;	//0000000010000000
	if((dw2nd >>  8) & 0x1) dwStatus = dwStatus|0X01000000;	//0000000100000000
	if((dw2nd >>  9) & 0x1) dwStatus = dwStatus|0X02000000;	//0000001000000000
	if((dw2nd >> 10) & 0x1) dwStatus = dwStatus|0X04000000;	//0000010000000000
	if((dw2nd >> 11) & 0x1) dwStatus = dwStatus|0X08000000;	//0000100000000000
	if((dw2nd >> 12) & 0x1) dwStatus = dwStatus|0X10000000;	//0001000000000000
	if((dw2nd >> 13) & 0x1) dwStatus = dwStatus|0X20000000;	//0010000000000000
	if((dw2nd >> 14) & 0x1) dwStatus = dwStatus|0X40000000;	//0100000000000000
	if((dw2nd >> 15) & 0x1) dwStatus = dwStatus|0X80000000;	//1000000000000000-0000000000000000

	lValue = dwStatus;
	return lValue;
}

long CCommon::Make_CharToLong(CString sRecv)
{
	char cc1, cc2;
	CString sc3;

	cc1 = sRecv.GetAt(0);
	cc2 = sRecv.GetAt(1);
	sc3.Format("%02X%02X", cc2, cc1);
	return strtol(sc3, NULL, 16);
}

CString CCommon::Make_HashKey(CString sGlassID, int Seq)
{
	CString sData;
	double	dOut, dSeed = 7919;
	int		nHashValue, nTmp, nCnt, nLayerSize;
	long	ltmp;

	nLayerSize = int(dSeed / int(pow(dSeed, 0.5)));	//=89

	nCnt = sGlassID.GetLength();
	nTmp = 0;
	for(int i=0; i<nCnt; i++) {
		ltmp = (long)nTmp;
		ltmp = ltmp * 255;
		ltmp = ltmp + (255 & (sGlassID.GetAt(i)));
		nTmp = ltmp % (int)dSeed;
	}
	nHashValue = nTmp;

	if(Seq == 0) {
		dOut = nHashValue / nLayerSize;
		dOut = ceil(dOut - 0.49999);
	} else {
		dOut = nHashValue % nLayerSize;
	}

	nTmp = (int)dOut;
	sData.Format("%08d", nTmp);
	return sData;
}

void CCommon::MakeFolder(CString sPath)	//"D:\\Run\\Log\\LotData\\YYYY\\MM\\DD\\";
{
	CString sTemp;
	int nIdx = 0;

	while(true) {
		nIdx = sPath.Find("\\");
		sTemp += sPath.Mid(0, nIdx) + "\\";
		CreateDirectory(sTemp,FALSE);
		sPath = sPath.Mid(nIdx+1, sPath.GetLength());
		if(nIdx<0) break;
	}
}

void CCommon::MakeFTPFolder(CString sPath)	//"/C4_CE_T01/CELL/Defect/01/02/03/04/";
{
	int nCC=0;
	CString sDataAA[100], sTempAA, aAA;

	for(int i=0; i<100; i++) {
		AfxExtractSubString(aAA,	sPath, i, '/');
		if(aAA.GetLength() > 0) {
			sDataAA[nCC] = aAA;
			nCC++;
		}
		if(nCC>1 && aAA.GetLength() < 1) break;
	}
	sTempAA = "/";
	for(int i=0; i<nCC; i++) {
		sTempAA = sTempAA + sDataAA[i] + "/";
		if((sDataAA[3] == "HOST" && i>3) ||
		   (sDataAA[3] == "INSPECTOR" && i>5) ||
		   (sDataAA[3] == "INDEX" && i>3) ||
		   (sDataAA[2] == "IMAGE" && i>5) ) {
			m_pFtp->CreateDirectory(sDataAA[i]);
		}
		m_pFtp->SetCurrentDirectory(sTempAA);
	}
}

// x의 n(0~31)번째 비트를, b(0,1)로 설정하는 함수
DWORD CCommon::setAbit(DWORD x, int n, int b)
{
	if (b == 1) return (DWORD) (x | (1 << n) );
	else		return (DWORD) (x & (~(1 << n)));
}

void CCommon::PickerLoad_Move(int nType, int nYY, int nTrayNo)
{
	m_dP1Y1 = m_dP1Y2 = m_dP1Z = 0.0;;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	if(nType < 1   || nType > 2) return;
	if(nYY < 1     || nYY > gData.nArrayW) return;
	if(nTrayNo < 1 || nTrayNo > 2) return;

	if (nType == 1) {		// Up
		if (nTrayNo == 1) {	// x1
			m_dP1X[0] = pMoveData->dLoadTrayX1[2] + ((nYY-1) * (gData.dTrayPitchW + pMoveData->dLoadTrayX1[4]));
			m_dP1Y1 = pMoveData->dLoadPickerY1[0];
			m_dP1Z = pMoveData->dLoadPickerZ[1];
		}
		if (nTrayNo == 2) {	// x2
			m_dP1X[1] = pMoveData->dLoadTrayX2[2] + ((nYY-1) * (gData.dTrayPitchW + pMoveData->dLoadTrayX2[4]));
			m_dP1Y1 = pMoveData->dLoadPickerY1[1];
			m_dP1Z = pMoveData->dLoadPickerZ[2];
		}
		
		m_dP1Y2 = pMoveData->dLoadPickerY2[0];	// + pMoveData->dLoadPickerY2[2];
	}

	if (nType == 2) {	// Down
		m_dP1Y1 = pMoveData->dLoadPickerY1[2];
		m_dP1Y2 = pMoveData->dLoadPickerY2[1];	// + pMoveData->dLoadPickerY2[3];
		m_dP1Z = pMoveData->dLoadPickerZ[3];
	}
}

void CCommon::PickerUnload_Move(int nType, int nYY, int nTrayNo)	//Unload Picker
{
	m_dP2X1 = m_dP2X2 = m_dP2Z = 0.0;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	if(nType < 1   || nType > 3) return;
	if(nYY < 1     || nYY > gData.nArrayW) return;
	if(nTrayNo < 1 || nTrayNo > 2) return;

	if (nType == 1) {	// Up
		m_dP2X1 = pMoveData->dUnloadPickerX1[0];
		m_dP2X2 = pMoveData->dUnloadPickerX2[0];	// + pMoveData->dUnloadPickerX2[2];
		m_dP2Z = pMoveData->dUnloadPickerZ[1];
	}

	if (nType == 2) {		// Down
		// gData.bUnloadSortFront TRUE : 장비기준 Front부터 적재하고 Front쪽(+방향)으로 Stage를 움직인다.
		// gData.bUnloadSortFront FALSE : 장비기준 Rear부터 적재하고 Rear쪽(-방향)으로 Stage를 움직인다.
		if(nTrayNo == 1 ) {	// y1
			if (gData.bUnloadSortFront) { m_dP2Y[0] = pMoveData->dUnloadTrayY1[2] + ((nYY-1) * (gData.dTrayPitchW + pMoveData->dUnloadTrayY1[4])); }
			else						{ m_dP2Y[0] = pMoveData->dUnloadTrayY1[2] - ((nYY-1) * (gData.dTrayPitchW + pMoveData->dUnloadTrayY1[4])); }
			m_dP2X1 = pMoveData->dUnloadPickerX1[1];
			m_dP2Z = pMoveData->dUnloadPickerZ[2];
		}
		if(nTrayNo == 2 ) {	// y2
			if (gData.bUnloadSortFront) { m_dP2Y[1] = pMoveData->dUnloadTrayY2[2] + ((nYY-1) * (gData.dTrayPitchW + pMoveData->dUnloadTrayY2[4])); }
			else						{ m_dP2Y[1] = pMoveData->dUnloadTrayY2[2] - ((nYY-1) * (gData.dTrayPitchW + pMoveData->dUnloadTrayY2[4])); }
			m_dP2X1 = pMoveData->dUnloadPickerX1[2];
			m_dP2Z = pMoveData->dUnloadPickerZ[2];
		}
		
		m_dP2X2 = pMoveData->dUnloadPickerX2[1];	// + pMoveData->dUnloadPickerX2[3];
	}

	if (nType == 3) {		// Sorting
		if(nTrayNo == 1 ) {	// y1
			m_dP2Y[0] = pMoveData->dUnloadTrayY1[2] + ((nYY-1) * (gData.dTrayPitchW + pMoveData->dUnloadTrayY1[4]));
		}
		if(nTrayNo == 2 ) {	// y2
			m_dP2Y[1] = pMoveData->dUnloadTrayY2[2] + ((nYY-1) * (gData.dTrayPitchW + pMoveData->dUnloadTrayY2[4]));
		}
	}
}

void CCommon::PickerNG_DnMove(int nPNo, int nXX, int nYY, int nTrayNo)	//NG Picker
{
	m_dP3X = m_dP3Z = 0.0;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	if(nPNo < 1    || nPNo > gData.nArrayL) return;
	if(nXX < 1     || nXX > gData.nArrayL) return;
//	if(nTrayNo < 1 || nTrayNo > 2) return;
/*
	if (nXX == 1) m_dP3X = pMoveData->dNGPickerX[nPNo] - (4 * (gData.dTrayPitchL + pMoveData->dNGPickerX[7]));
	if (nXX == 2) m_dP3X = pMoveData->dNGPickerX[nPNo] - (3 * (gData.dTrayPitchL + pMoveData->dNGPickerX[7]));
	if (nXX == 3) m_dP3X = pMoveData->dNGPickerX[nPNo] - (2 * (gData.dTrayPitchL + pMoveData->dNGPickerX[7]));
	if (nXX == 4) m_dP3X = pMoveData->dNGPickerX[nPNo] - (1 * (gData.dTrayPitchL + pMoveData->dNGPickerX[7]));
	if (nXX == 5) m_dP3X = pMoveData->dNGPickerX[nPNo] - (0 * (gData.dTrayPitchL + pMoveData->dNGPickerX[7]));
*/
	m_dP3X = pMoveData->dNGPickerX[nPNo] - ((nXX-1) * (gData.dTrayPitchL + pMoveData->dNGPickerX[7]));
	m_dP3Z = pMoveData->dNGPickerZ[1];
}

void CCommon::PickerNG_UpMove(int nPNo, int nXX)
{
	m_dP3X = m_dP3Z = 0.0;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	if(nPNo < 1 || nPNo > 3) return;
	if(nXX < 1  || nXX > gData.nArrayL) return;

	if(nPNo == 1) m_dP3X = pMoveData->dNGPickerX[1] - ((nXX-1) * gData.dIndexPitch);
	if(nPNo == 2) m_dP3X = pMoveData->dNGPickerX[3] - ((nXX-1) * gData.dIndexPitch);
	if(nPNo == 3) m_dP3X = pMoveData->dNGPickerX[5] - ((nXX-1) * gData.dIndexPitch);

	if(nPNo == 1) m_dP3Z = pMoveData->dNGPickerZ[1];
	if(nPNo == 2) m_dP3Z = pMoveData->dNGPickerZ[3];
	if(nPNo == 3) m_dP3Z = pMoveData->dNGPickerZ[5];

}

void CCommon::PickerNGStageMove(int nLine, int nTrayNo)
{
	m_dP3Y = 0.0;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	if(nLine < 1   || nLine > gData.nArrayW) return;
	if(nTrayNo < 1 || nTrayNo > 2) return;

	if (gData.bNgSortFront) {
		// 기존에 사용하던 방향. 장비정면에 가까운 NG Tray 부터 채운다.
		if(nTrayNo == 1) m_dP3Y = pMoveData->dNGStageY[1] + ((nLine-1) * (gData.dTrayPitchW + pMoveData->dNGStageY[3]));
		if(nTrayNo == 2) m_dP3Y = pMoveData->dNGStageY[2] + ((nLine-1) * (gData.dTrayPitchW + pMoveData->dNGStageY[3]));
	} else {
		// 뒤에서 부터 채워준다. 장비후면에 가까운 NG Tray 부터 채운다.
		if(nTrayNo == 1) m_dP3Y = pMoveData->dNGStageY[1] - ((nLine-1) * (gData.dTrayPitchW + pMoveData->dNGStageY[3]));
		if(nTrayNo == 2) m_dP3Y = pMoveData->dNGStageY[2] - ((nLine-1) * (gData.dTrayPitchW + pMoveData->dNGStageY[3]));
	}

}

void CCommon::PickerGood_Move(int nType, int nPNo, int nYY)		//Good Picker
{
	m_dP4Y = m_dP4Z = 0.0;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	if(nType < 1   || nType > 2) return;
	if(nPNo < 1    || nPNo > 6) return;
	if(nYY < 1     || nYY > 6) return;

	if (nType == 1) {	// Up
		m_dP4Y = pMoveData->dGdPickerY[nPNo] - ((nYY-1) * gData.dIndexPitch);
		if(nPNo == 1) m_dP4Z = pMoveData->dGdPickerZ[1];
		if(nPNo == 2) m_dP4Z = pMoveData->dGdPickerZ[3];
		if(nPNo == 3) m_dP4Z = pMoveData->dGdPickerZ[5];
		if(nPNo == 4) m_dP4Z = pMoveData->dGdPickerZ[7];
		if(nPNo == 5) m_dP4Z = pMoveData->dGdPickerZ[9];
		if(nPNo == 6) m_dP4Z = pMoveData->dGdPickerZ[11];
	}

	if (nType == 2) {	// Down
		m_dP4Y = pMoveData->dGdPickerY[nPNo] - ((nYY-1) * gData.dIndexPitch);
		if(nPNo == 1) m_dP4Z = pMoveData->dGdPickerZ[2];
		if(nPNo == 2) m_dP4Z = pMoveData->dGdPickerZ[4];
		if(nPNo == 3) m_dP4Z = pMoveData->dGdPickerZ[6];
		if(nPNo == 4) m_dP4Z = pMoveData->dGdPickerZ[8];
		if(nPNo == 5) m_dP4Z = pMoveData->dGdPickerZ[10];
		if(nPNo == 6) m_dP4Z = pMoveData->dGdPickerZ[12];
	}
}

void CCommon::Set_NGPickerUp(int nNo)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_3 *pDY3 = pAJinAXL->Get_pDY3();

	if (nNo == 0 || nNo == 1) { pDY3->oNGPicker1Up = TRUE; pDY3->oNGPicker1Down = FALSE; }
	if (nNo == 0 || nNo == 2) { pDY3->oNGPicker2Up = TRUE; pDY3->oNGPicker2Down = FALSE; }
	if (nNo == 0 || nNo == 3) { pDY3->oNGPicker3Up = TRUE; pDY3->oNGPicker3Down = FALSE; }
	if (nNo == 0 || nNo == 4) { pDY3->oNGPicker4Up = TRUE; pDY3->oNGPicker4Down = FALSE; }

	pAJinAXL->Write_Output(3);
}

void CCommon::Set_NGPickerDown(int nNo)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_3 *pDY3 = pAJinAXL->Get_pDY3();

	if (nNo == 1) { pDY3->oNGPicker1Up = FALSE; pDY3->oNGPicker1Down = TRUE; gData.NGJobPic[0]=1; }
	if (nNo == 2) { pDY3->oNGPicker2Up = FALSE; pDY3->oNGPicker2Down = TRUE; gData.NGJobPic[1]=1; }
	if (nNo == 3) { pDY3->oNGPicker3Up = FALSE; pDY3->oNGPicker3Down = TRUE; gData.NGJobPic[2]=1; }
	if (nNo == 4) { pDY3->oNGPicker4Up = FALSE; pDY3->oNGPicker4Down = TRUE; gData.NGJobPic[3]=1; }

	pAJinAXL->Write_Output(3);
}

BOOL CCommon::Get_NGPickerDown(int nNo)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();

	if (nNo == 1 && !pDX3->iNGPicker1Up && pDX3->iNGPicker1Down) return TRUE;
	if (nNo == 2 && !pDX3->iNGPicker2Up && pDX3->iNGPicker2Down) return TRUE;
	if (nNo == 3 && !pDX3->iNGPicker3Up && pDX3->iNGPicker3Down) return TRUE;
	if (nNo == 4 && !pDX3->iNGPicker4Up && pDX3->iNGPicker4Down) return TRUE;

	return FALSE;
}

void CCommon::Set_NGPickerClose(int nNo)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_3 *pDY3 = pAJinAXL->Get_pDY3();

	if (nNo == 1) { pDY3->oNGPicker1Open = FALSE; pDY3->oNGPicker1Close = TRUE; }
	if (nNo == 2) { pDY3->oNGPicker2Open = FALSE; pDY3->oNGPicker2Close = TRUE; }
	if (nNo == 3) { pDY3->oNGPicker3Open = FALSE; pDY3->oNGPicker3Close = TRUE; }
	if (nNo == 4) { pDY3->oNGPicker4Open = FALSE; pDY3->oNGPicker4Close = TRUE; }

	pAJinAXL->Write_Output(3);
}

BOOL CCommon::Get_NGPickerClose(int nNo)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();

	if (nNo == 1 && !pDX3->iNGPicker1Open) return TRUE;
	if (nNo == 2 && !pDX3->iNGPicker2Open) return TRUE;
	if (nNo == 3 && !pDX3->iNGPicker3Open) return TRUE;
	if (nNo == 4 && !pDX3->iNGPicker4Open) return TRUE;

	return FALSE;
}

void CCommon::Set_TimeUpdate(CString sTime)	// sTime Format : "2000-01-01 12:30:30 000"
{
	CString strTemp;
	SYSTEMTIME time;

	strTemp = sTime.Mid(0, 4);  time.wYear = atoi(strTemp);			// Year
	strTemp = sTime.Mid(5, 2);  time.wMonth = atoi(strTemp);		// Month
	strTemp = sTime.Mid(8, 2);  time.wDay = atoi(strTemp);			// Day
	strTemp = sTime.Mid(11, 2); time.wHour = atoi(strTemp);			// Hour
	strTemp = sTime.Mid(14, 2); time.wMinute = atoi(strTemp);		// Minite
	strTemp = sTime.Mid(17, 2); time.wSecond = atoi(strTemp);		// Second
	strTemp = sTime.Mid(20, 3); time.wMilliseconds = atoi(strTemp);	// MilliSecond

	SetLocalTime(&time);
}

/*
// 정수 x 의 n번째 비트를, b로 설정하는 함수
unsigned short setAbit(unsigned short x, int n, int b) { // setbit()

  if (b == 1)
    return (unsigned short) (x | (1 << n) );
  else
   return (unsigned short) ( x & (~(1 << n)));

}

char *ushortToBinary(unsigned short i) {
  static char s[16 + 1] = { '0', };
  int count = 16;

  do { s[--count] = '0' + (char) (i & 1);
       i = i >> 1;
  } while (count);

  return s;
}
*/



void CCommon::Get_HardInfo(CString &strHardDisk)
{
	ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;

	// GetDiskFreeSpaceEx 호출
	if (GetDiskFreeSpaceEx("C:\\", &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
		// GB로 변환하여 출력
		double totalGB = static_cast<double>(totalBytes.QuadPart) / (1024 * 1024 * 1024);
		double freeGB = static_cast<double>(totalFreeBytes.QuadPart) / (1024 * 1024 * 1024);
		double usedGB = totalGB - freeGB;

		strHardDisk.Format("%lf", freeGB);
	}
}

void CCommon::Get_RAMSize(CString &strRAM)
{
	ULONGLONG Size;
	GetPhysicallyInstalledSystemMemory(&Size);
	strRAM.Format(_T("%llu"), ((Size/1024)/1024));
}

void CCommon::Get_CPUInfo(CString& strCPU)
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	HKEY hKey;	
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		char buffer[256];
		DWORD bufferSize = sizeof(buffer);
		if (RegQueryValueEx(hKey, _T("ProcessorNameString"), NULL, NULL, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS)
		{
			strCPU = (CString)buffer;
		}
		RegCloseKey(hKey);
	}

	switch (sysInfo.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_AMD64: strCPU += " x64";  break;
	case PROCESSOR_ARCHITECTURE_INTEL: strCPU += " x86"; break;
	default:  strCPU += " Unknown"; break;
	}   
	
}