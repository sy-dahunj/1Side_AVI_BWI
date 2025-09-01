// SetupMoveTab4Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupMoveTab4Dlg.h"
#include "afxdialogex.h"

#include "DataManager.h"
#include "Common.h"
#include "LogFile.h"
#include "MESInterface.h"

// CSetupMoveTab4Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab4Dlg, CDialogEx)

CSetupMoveTab4Dlg::CSetupMoveTab4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab4Dlg::IDD, pParent)
{
}

CSetupMoveTab4Dlg::~CSetupMoveTab4Dlg()
{
}

void CSetupMoveTab4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 20; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	DDX_Control(pDX, IDC_LABEL_20, m_Label[20]);
	DDX_Control(pDX, IDC_LABEL_21, m_Label[21]);
	DDX_Control(pDX, IDC_LABEL_22, m_Label[22]);
	DDX_Control(pDX, IDC_LABEL_23, m_Label[23]);
	DDX_Control(pDX, IDC_LABEL_24, m_Label[24]);
	DDX_Control(pDX, IDC_LABEL_25, m_Label[25]);
	DDX_Control(pDX, IDC_LABEL_26, m_Label[26]);
	DDX_Control(pDX, IDC_LABEL_27, m_Label[27]);
	DDX_Control(pDX, IDC_LABEL_28, m_Label[28]);

	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_REAR_0, m_stcEmptyTrayCVRear[0]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_REAR_1, m_stcEmptyTrayCVRear[1]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_REAR_2, m_stcEmptyTrayCVRear[2]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_REAR_3, m_stcEmptyTrayCVRear[3]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_REAR_4, m_stcEmptyTrayCVRear[4]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_ELEV_Z_0, m_stcEmptyTrayElevZ[0]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_ELEV_Z_1, m_stcEmptyTrayElevZ[1]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_ELEV_Z_2, m_stcEmptyTrayElevZ[2]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_ELEV_Z_3, m_stcEmptyTrayElevZ[3]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_ELEV_Z_4, m_stcEmptyTrayElevZ[4]);

	DDX_Control(pDX, IDC_STC_GOOD_TRAY_CV_REAR_0, m_stcGoodTrayCVRear[0]);
	DDX_Control(pDX, IDC_STC_GOOD_TRAY_CV_REAR_1, m_stcGoodTrayCVRear[1]);
	DDX_Control(pDX, IDC_STC_GOOD_TRAY_CV_REAR_2, m_stcGoodTrayCVRear[2]);
	DDX_Control(pDX, IDC_STC_GOOD_TRAY_CV_REAR_3, m_stcGoodTrayCVRear[3]);
	DDX_Control(pDX, IDC_STC_GOOD_TRAY_ELEV_Z_0, m_stcGoodTrayUnloadElevZ[0]);
	DDX_Control(pDX, IDC_STC_GOOD_TRAY_ELEV_Z_1, m_stcGoodTrayUnloadElevZ[1]);
	DDX_Control(pDX, IDC_STC_GOOD_TRAY_ELEV_Z_2, m_stcGoodTrayUnloadElevZ[2]);
	DDX_Control(pDX, IDC_STC_GOOD_TRAY_ELEV_Z_3, m_stcGoodTrayUnloadElevZ[3]);

	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_FRONT_0, m_stcEmptyTrayCVFront[0]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_FRONT_1, m_stcEmptyTrayCVFront[1]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_FRONT_2, m_stcEmptyTrayCVFront[2]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_FRONT_3, m_stcEmptyTrayCVFront[3]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_FRONT_4, m_stcEmptyTrayCVFront[4]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_FRONT_5, m_stcEmptyTrayCVFront[5]);
	DDX_Control(pDX, IDC_STC_EMPTY_TRAY_CV_FRONT_6, m_stcEmptyTrayCVFront[6]);
	DDX_Control(pDX, IDC_STATIC_BARCODE_X_0, m_staticBarcodeX[0]);
	DDX_Control(pDX, IDC_STATIC_BARCODE_X_1, m_staticBarcodeX[1]);
	DDX_Control(pDX, IDC_STATIC_BARCODE_X_2, m_staticBarcodeX[2]);
	DDX_Control(pDX, IDC_STATIC_BARCODE_X_3, m_staticBarcodeX[3]);

	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);

}

BEGIN_MESSAGE_MAP(CSetupMoveTab4Dlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_REAR_0, IDC_STC_EMPTY_TRAY_CV_REAR_0, OnStcEmptyTrayCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_REAR_1, IDC_STC_EMPTY_TRAY_CV_REAR_1, OnStcEmptyTrayCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_REAR_2, IDC_STC_EMPTY_TRAY_CV_REAR_2, OnStcEmptyTrayCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_REAR_3, IDC_STC_EMPTY_TRAY_CV_REAR_3, OnStcEmptyTrayCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_REAR_4, IDC_STC_EMPTY_TRAY_CV_REAR_4, OnStcEmptyTrayCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_ELEV_Z_0, IDC_STC_EMPTY_TRAY_ELEV_Z_0, OnStcEmptyTrayUnloadElevZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_ELEV_Z_1, IDC_STC_EMPTY_TRAY_ELEV_Z_1, OnStcEmptyTrayUnloadElevZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_ELEV_Z_2, IDC_STC_EMPTY_TRAY_ELEV_Z_2, OnStcEmptyTrayUnloadElevZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_ELEV_Z_3, IDC_STC_EMPTY_TRAY_ELEV_Z_3, OnStcEmptyTrayUnloadElevZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_ELEV_Z_4, IDC_STC_EMPTY_TRAY_ELEV_Z_4, OnStcEmptyTrayUnloadElevZClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_TRAY_CV_REAR_0, IDC_STC_GOOD_TRAY_CV_REAR_0, OnStcGoodTrayCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_TRAY_CV_REAR_1, IDC_STC_GOOD_TRAY_CV_REAR_1, OnStcGoodTrayCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_TRAY_CV_REAR_2, IDC_STC_GOOD_TRAY_CV_REAR_2, OnStcGoodTrayCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_TRAY_CV_REAR_3, IDC_STC_GOOD_TRAY_CV_REAR_3, OnStcGoodTrayCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_TRAY_ELEV_Z_0, IDC_STC_GOOD_TRAY_ELEV_Z_0, OnStcGoodTrayUnloadElevZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_TRAY_ELEV_Z_1, IDC_STC_GOOD_TRAY_ELEV_Z_1, OnStcGoodTrayUnloadElevZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_TRAY_ELEV_Z_2, IDC_STC_GOOD_TRAY_ELEV_Z_2, OnStcGoodTrayUnloadElevZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_TRAY_ELEV_Z_3, IDC_STC_GOOD_TRAY_ELEV_Z_3, OnStcGoodTrayUnloadElevZClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_FRONT_0, IDC_STC_EMPTY_TRAY_CV_FRONT_0, OnStcEmptyTrayCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_FRONT_1, IDC_STC_EMPTY_TRAY_CV_FRONT_1, OnStcEmptyTrayCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_FRONT_2, IDC_STC_EMPTY_TRAY_CV_FRONT_2, OnStcEmptyTrayCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_FRONT_3, IDC_STC_EMPTY_TRAY_CV_FRONT_3, OnStcEmptyTrayCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_FRONT_4, IDC_STC_EMPTY_TRAY_CV_FRONT_4, OnStcEmptyTrayCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_FRONT_5, IDC_STC_EMPTY_TRAY_CV_FRONT_5, OnStcEmptyTrayCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_EMPTY_TRAY_CV_FRONT_6, IDC_STC_EMPTY_TRAY_CV_FRONT_6, OnStcEmptyTrayCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STATIC_BARCODE_X_0, IDC_STATIC_BARCODE_X_0, OnStaticBarcodeXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STATIC_BARCODE_X_1, IDC_STATIC_BARCODE_X_1, OnStaticBarcodeXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STATIC_BARCODE_X_2, IDC_STATIC_BARCODE_X_2, OnStaticBarcodeXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STATIC_BARCODE_X_3, IDC_STATIC_BARCODE_X_3, OnStaticBarcodeXClick)

	ON_BN_CLICKED(IDC_BTN_SAVE, &CSetupMoveTab4Dlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSetupMoveTab4Dlg::OnBnClickedBtnCancel)	

END_MESSAGE_MAP()

// CSetupMoveTab4Dlg 메시지 처리기입니다.

BOOL CSetupMoveTab4Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 55, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetupMoveTab4Dlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CSetupMoveTab4Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab4Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		Display_MoveData();
	}
}


//KTY
void CSetupMoveTab4Dlg::OnStcEmptyTrayUnloadElevZClick(UINT nID)
{
 	int ID=0;
	if		(nID == IDC_STC_EMPTY_TRAY_ELEV_Z_0) ID = 0;
	else if (nID == IDC_STC_EMPTY_TRAY_ELEV_Z_1) ID = 1;
	else if (nID == IDC_STC_EMPTY_TRAY_ELEV_Z_2) ID = 2;
	else if (nID == IDC_STC_EMPTY_TRAY_ELEV_Z_3) ID = 3;
	else if (nID == IDC_STC_EMPTY_TRAY_ELEV_Z_4) ID = 4;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcEmptyTrayElevZ[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcEmptyTrayElevZ[ID].SetWindowText(strNew);
	}
}
void CSetupMoveTab4Dlg::OnStcGoodTrayUnloadElevZClick(UINT nID)	
{
 	int ID=0;
	if		(nID == IDC_STC_GOOD_TRAY_ELEV_Z_0) ID = 0;
	else if (nID == IDC_STC_GOOD_TRAY_ELEV_Z_1) ID = 1;
	else if (nID == IDC_STC_GOOD_TRAY_ELEV_Z_2) ID = 2;
	else if (nID == IDC_STC_GOOD_TRAY_ELEV_Z_3) ID = 3;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcGoodTrayUnloadElevZ[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcGoodTrayUnloadElevZ[ID].SetWindowText(strNew);
	}

}
void CSetupMoveTab4Dlg::OnStaticBarcodeXClick(UINT nID)	
{
 	int ID=0;
	if		(nID == IDC_STATIC_BARCODE_X_0) ID = 0;
	else if (nID == IDC_STATIC_BARCODE_X_1) ID = 1;
	else if (nID == IDC_STATIC_BARCODE_X_2) ID = 2;
	else if (nID == IDC_STATIC_BARCODE_X_3) ID = 3;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_staticBarcodeX[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_staticBarcodeX[ID].SetWindowText(strNew);
	}
}

void CSetupMoveTab4Dlg::OnStcEmptyTrayCVRearClick(UINT nID)
{
 	int ID=0;
	if		(nID == IDC_STC_EMPTY_TRAY_CV_REAR_0) ID = 0;
	else if (nID == IDC_STC_EMPTY_TRAY_CV_REAR_1) ID = 1;
	else if (nID == IDC_STC_EMPTY_TRAY_CV_REAR_2) ID = 2;
	else if (nID == IDC_STC_EMPTY_TRAY_CV_REAR_3) ID = 3;
	else if (nID == IDC_STC_EMPTY_TRAY_CV_REAR_4) ID = 4;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;

	m_stcEmptyTrayCVRear[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcEmptyTrayCVRear[ID].SetWindowText(strNew);
	}
}
void CSetupMoveTab4Dlg::OnStcEmptyTrayCVFrontClick(UINT nID)	
{
 	int ID=0;
	if		(nID == IDC_STC_EMPTY_TRAY_CV_FRONT_0) ID = 0;
	else if (nID == IDC_STC_EMPTY_TRAY_CV_FRONT_1) ID = 1;
	else if (nID == IDC_STC_EMPTY_TRAY_CV_FRONT_2) ID = 2;
	else if (nID == IDC_STC_EMPTY_TRAY_CV_FRONT_3) ID = 3;
	else if (nID == IDC_STC_EMPTY_TRAY_CV_FRONT_4) ID = 4;
	else if (nID == IDC_STC_EMPTY_TRAY_CV_FRONT_5) ID = 5;
	else if (nID == IDC_STC_EMPTY_TRAY_CV_FRONT_6) ID = 6;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcEmptyTrayCVFront[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcEmptyTrayCVFront[ID].SetWindowText(strNew);
	}
}
void CSetupMoveTab4Dlg::OnStcGoodTrayCVRearClick(UINT nID)	
{
 	int ID=0;
	if		(nID == IDC_STC_GOOD_TRAY_CV_REAR_0) ID = 0;
	else if (nID == IDC_STC_GOOD_TRAY_CV_REAR_1) ID = 1;
	else if (nID == IDC_STC_GOOD_TRAY_CV_REAR_2) ID = 2;
	else if (nID == IDC_STC_GOOD_TRAY_CV_REAR_3) ID = 3;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcGoodTrayCVRear[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcGoodTrayCVRear[ID].SetWindowText(strNew);
	}
}

void CSetupMoveTab4Dlg::OnBnClickedBtnSave()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	MODEL_DATA *pModelData = pDataManager->Get_pModelData();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();
	CCommon *pCommon = CCommon::Get_Instance();

	CString strModelFile;
	strModelFile.Format("MoveData_%d", pModelData->nStripSize);
	pCommon->Backup_File(gsCurrentDir + "\\System", strModelFile);

	strModelFile.Format("System/MoveData_%d.ini", pModelData->nStripSize);
	CIniFileCS INI(strModelFile);

	CString strSection, strKey, strData, sData;
	double dData;

	CLogFile *pLogFile = CLogFile::Get_Instance();

	strSection = "UNLOAD_TRAY_Y1";
	for (int i = 0; i < 5; i++) {
		m_stcEmptyTrayCVRear[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Y%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dUnloadTrayY1[i] != dData) {
			sData.Format("[Setup - Unload/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dUnloadTrayY1[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "UNLOAD_TRAY_Y2";
	for (int i = 0; i < 5; i++) {
		m_stcEmptyTrayElevZ[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Y%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dUnloadTrayY2[i] != dData) {
			sData.Format("[Setup - Unload/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dUnloadTrayY2[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "UNLOAD_TRAY_Z1";
	for (int i = 0; i < 4; i++) {
		m_stcGoodTrayCVRear[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Z%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dUnloadTrayZ1[i] != dData) {
			sData.Format("[Setup - Unload/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dUnloadTrayZ1[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "UNLOAD_TRAY_Z2";
	for (int i = 0; i < 4; i++) {
		m_stcGoodTrayUnloadElevZ[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Z%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dUnloadTrayZ2[i] != dData) {
			sData.Format("[Setup - Unload/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dUnloadTrayZ2[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "UNLOAD_PICKER_X1";
	for (int i = 0; i < 3; i++) {
		m_stcEmptyTrayCVFront[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("X%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dUnloadPickerX1[i] != dData) {
			sData.Format("[Setup - Unload/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dUnloadPickerX1[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "UNLOAD_PICKER_X2";
	for (int i = 0; i < 4; i++) {
		m_stcEmptyTrayCVFront[i+3].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("X%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dUnloadPickerX2[i] != dData) {
			sData.Format("[Setup - Unload/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dUnloadPickerX2[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "UNLOAD_PICKER_Z";
	for (int i = 0; i < 4; i++) {
		m_staticBarcodeX[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Z%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		// RMS 항목 저장
		if (i == 1) g_objMES.Save_AviRmsData("Unload Picker Z Load Down Position", strData);
		if (i == 2) g_objMES.Save_AviRmsData("Unload Picker Z Unload Down Position", strData);

		if (pMoveData->dUnloadPickerZ[i] != dData) {
			sData.Format("[Setup - Unload/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dUnloadPickerZ[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	pLogFile->Save_HandlerLog("[Setup - Unload/Tray Picker] save");

	OnBnClickedBtnCancel();

	/////////////////////////////////////////////////////////////////////////////////
#ifdef MOVE_DATA_COPY
	CString strTarget, strTemp;

	strTemp = pModelData->sModelName;
	strTarget.Format("Model/%s/MoveData_%d.ini", strTemp, pModelData->nStripSize);

	if (!CopyFile(strModelFile, strTarget, FALSE)) {
		pCommon->Show_MsgBox(1, "Copy fail.");
		return;
	}
#endif
	//////////////////////////////////////////////////////////////////////////////////
}

void CSetupMoveTab4Dlg::OnBnClickedBtnCancel()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	pDataManager->Read_MoveData();

	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab4Dlg::Initial_Controls() 
{
	for (int i = 0; i < 6; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	for (int i = 0; i < 29; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 5; i++) m_stcEmptyTrayCVRear[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++) m_stcEmptyTrayElevZ[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 4; i++) m_stcGoodTrayCVRear[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 4; i++) m_stcGoodTrayUnloadElevZ[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 7; i++) m_stcEmptyTrayCVFront[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 4; i++) m_staticBarcodeX[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xA0, 0xF0, 0xC0));

	m_btnSave.Init_Ctrl("바탕", 15, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnCancel.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
}

void CSetupMoveTab4Dlg::Display_MoveData()
{
	CString strData;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	for (int i = 0; i < 5; i++) {
		strData.Format("%0.3lf", pMoveData->dUnloadTrayY1[i]);
		m_stcEmptyTrayCVRear[i].SetWindowText(strData);
	}	
	for (int i = 0; i < 5; i++) {
		strData.Format("%0.3lf", pMoveData->dUnloadTrayY2[i]);
		m_stcEmptyTrayElevZ[i].SetWindowText(strData);
	}	

	for (int i = 0; i < 4; i++) {
		strData.Format("%0.3lf", pMoveData->dUnloadTrayZ1[i]);
		m_stcGoodTrayCVRear[i].SetWindowText(strData);
	}	
	for (int i = 0; i < 4; i++) {
		strData.Format("%0.3lf", pMoveData->dUnloadTrayZ2[i]);
		m_stcGoodTrayUnloadElevZ[i].SetWindowText(strData);
	}

	for (int i = 0; i < 3; i++) {
		strData.Format("%0.3lf", pMoveData->dUnloadPickerX1[i]);
		m_stcEmptyTrayCVFront[i].SetWindowText(strData);
	}	
	for (int i = 0; i < 4; i++) {
		strData.Format("%0.3lf", pMoveData->dUnloadPickerX2[i]);
		m_stcEmptyTrayCVFront[i+3].SetWindowText(strData);
	}	
	for (int i = 0; i < 4; i++) {
		strData.Format("%0.3lf", pMoveData->dUnloadPickerZ[i]);
		m_staticBarcodeX[i].SetWindowText(strData);
	}	
}

///////////////////////////////////////////////////////////////////////////////
