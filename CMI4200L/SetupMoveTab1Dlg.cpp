// SetupMoveTab1Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupMoveTab1Dlg.h"
#include "afxdialogex.h"

#include "DataManager.h"
#include "Common.h"
#include "LogFile.h"
#include "MESInterface.h"

// CSetupMoveTab1Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab1Dlg, CDialogEx)

CSetupMoveTab1Dlg::CSetupMoveTab1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab1Dlg::IDD, pParent)
{
}

CSetupMoveTab1Dlg::~CSetupMoveTab1Dlg()
{
}

void CSetupMoveTab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 38; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);

	DDX_Control(pDX, IDC_LABEL_38, m_Label[38]);
	DDX_Control(pDX, IDC_LABEL_39, m_Label[39]);
	DDX_Control(pDX, IDC_LABEL_40, m_Label[40]);
	DDX_Control(pDX, IDC_LABEL_41, m_Label[41]);
	DDX_Control(pDX, IDC_LABEL_42, m_Label[42]);
	DDX_Control(pDX, IDC_LABEL_43, m_Label[43]);

	//CMI3000
	DDX_Control(pDX, IDC_STC_SHUTTLE_X_0, m_stcShuttleX[0]);
	DDX_Control(pDX, IDC_STC_SHUTTLE_X_1, m_stcShuttleX[1]);
	DDX_Control(pDX, IDC_STC_SHUTTLE_X_2, m_stcShuttleX[2]);
	DDX_Control(pDX, IDC_STC_SHUTTLE_X_3, m_stcShuttleX[3]);
	DDX_Control(pDX, IDC_STC_SHUTTLE_X_4, m_stcShuttleX[4]);
	DDX_Control(pDX, IDC_STC_LD_TRAY_TR_1_Z_0, m_stcLoadTrayTR1Z[0]);
	DDX_Control(pDX, IDC_STC_LD_TRAY_TR_1_Z_1, m_stcLoadTrayTR1Z[1]);
	DDX_Control(pDX, IDC_STC_LD_TRAY_TR_1_Z_2, m_stcLoadTrayTR1Z[2]);
	DDX_Control(pDX, IDC_STC_LD_TRAY_TR_1_Z_3, m_stcLoadTrayTR1Z[3]);
	DDX_Control(pDX, IDC_STC_LD_TRAY_TR_1_Z_4, m_stcLoadTrayTR1Z[4]);

	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_2_Y_0, m_stcLoadTrayTR2Y[0]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_2_Y_1, m_stcLoadTrayTR2Y[1]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_2_Y_2, m_stcLoadTrayTR2Y[2]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_2_Y_3, m_stcLoadTrayTR2Y[3]);
	DDX_Control(pDX, IDC_STC_VISION_X_0, m_stcVisionX[0]);
	DDX_Control(pDX, IDC_STC_VISION_X_1, m_stcVisionX[1]);
	DDX_Control(pDX, IDC_STC_VISION_X_2, m_stcVisionX[2]);
	DDX_Control(pDX, IDC_STC_VISION_X_3, m_stcVisionX[3]);

	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_1_Y_0, m_stcLoadTrayTR1Y[0]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_1_Y_1, m_stcLoadTrayTR1Y[1]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_1_Y_2, m_stcLoadTrayTR1Y[2]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_1_Y_3, m_stcLoadTrayTR1Y[3]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_1_Y_4, m_stcLoadTrayTR1Y[4]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_1_Y_5, m_stcLoadTrayTR1Y[5]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_1_Y_6, m_stcLoadTrayTR1Y[6]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_2_Z_0, m_stcLoadTrayTR2Z[0]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_2_Z_1, m_stcLoadTrayTR2Z[1]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_2_Z_2, m_stcLoadTrayTR2Z[2]);
	DDX_Control(pDX, IDC_STC_LOAD_TRAY_TR_2_Z_3, m_stcLoadTrayTR2Z[3]);
	
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);

}

BEGIN_MESSAGE_MAP(CSetupMoveTab1Dlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()

	//CMI3000
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_SHUTTLE_X_0, IDC_STC_SHUTTLE_X_0, OnStcSuttleXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_SHUTTLE_X_1, IDC_STC_SHUTTLE_X_1, OnStcSuttleXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_SHUTTLE_X_2, IDC_STC_SHUTTLE_X_2, OnStcSuttleXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_SHUTTLE_X_3, IDC_STC_SHUTTLE_X_3, OnStcSuttleXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_SHUTTLE_X_4, IDC_STC_SHUTTLE_X_4, OnStcSuttleXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LD_TRAY_TR_1_Z_0, IDC_STC_LD_TRAY_TR_1_Z_0, OnStcloadTrayTR1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LD_TRAY_TR_1_Z_1, IDC_STC_LD_TRAY_TR_1_Z_1, OnStcloadTrayTR1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LD_TRAY_TR_1_Z_2, IDC_STC_LD_TRAY_TR_1_Z_2, OnStcloadTrayTR1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LD_TRAY_TR_1_Z_3, IDC_STC_LD_TRAY_TR_1_Z_3, OnStcloadTrayTR1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LD_TRAY_TR_1_Z_4, IDC_STC_LD_TRAY_TR_1_Z_4, OnStcloadTrayTR1ZClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_2_Y_0, IDC_STC_LOAD_TRAY_TR_2_Y_0, OnStcloadTrayTR2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_2_Y_1, IDC_STC_LOAD_TRAY_TR_2_Y_1, OnStcloadTrayTR2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_2_Y_2, IDC_STC_LOAD_TRAY_TR_2_Y_2, OnStcloadTrayTR2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_2_Y_3, IDC_STC_LOAD_TRAY_TR_2_Y_3, OnStcloadTrayTR2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_VISION_X_0, IDC_STC_VISION_X_0, OnStcVisionXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_VISION_X_1, IDC_STC_VISION_X_1, OnStcVisionXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_VISION_X_2, IDC_STC_VISION_X_2, OnStcVisionXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_VISION_X_3, IDC_STC_VISION_X_3, OnStcVisionXClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_1_Y_0, IDC_STC_LOAD_TRAY_TR_1_Y_0, OnStcloadTrayTR1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_1_Y_1, IDC_STC_LOAD_TRAY_TR_1_Y_1, OnStcloadTrayTR1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_1_Y_2, IDC_STC_LOAD_TRAY_TR_1_Y_2, OnStcloadTrayTR1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_1_Y_3, IDC_STC_LOAD_TRAY_TR_1_Y_3, OnStcloadTrayTR1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_1_Y_4, IDC_STC_LOAD_TRAY_TR_1_Y_4, OnStcloadTrayTR1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_1_Y_5, IDC_STC_LOAD_TRAY_TR_1_Y_5, OnStcloadTrayTR1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_1_Y_6, IDC_STC_LOAD_TRAY_TR_1_Y_6, OnStcloadTrayTR1YClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_2_Z_0, IDC_STC_LOAD_TRAY_TR_2_Z_0, OnStcloadTrayTR2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_2_Z_1, IDC_STC_LOAD_TRAY_TR_2_Z_1, OnStcloadTrayTR2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_2_Z_2, IDC_STC_LOAD_TRAY_TR_2_Z_2, OnStcloadTrayTR2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_LOAD_TRAY_TR_2_Z_3, IDC_STC_LOAD_TRAY_TR_2_Z_3, OnStcloadTrayTR2ZClick)

	ON_BN_CLICKED(IDC_BTN_SAVE, &CSetupMoveTab1Dlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSetupMoveTab1Dlg::OnBnClickedBtnCancel)


END_MESSAGE_MAP()

// CSetupMoveTab1Dlg 메시지 처리기입니다.

BOOL CSetupMoveTab1Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 55, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetupMoveTab1Dlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CSetupMoveTab1Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab1Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		Display_MoveData();
	}
}

//kty
void CSetupMoveTab1Dlg::OnStcSuttleXClick(UINT nID)
{
 	int ID=0;
	if		(nID == IDC_STC_SHUTTLE_X_0) ID = 0;
	else if (nID == IDC_STC_SHUTTLE_X_1) ID = 1;
	else if (nID == IDC_STC_SHUTTLE_X_2) ID = 2;
	else if (nID == IDC_STC_SHUTTLE_X_3) ID = 3;
	else if (nID == IDC_STC_SHUTTLE_X_4) ID = 4;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcShuttleX[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcShuttleX[ID].SetWindowText(strNew);
	}
}
void CSetupMoveTab1Dlg::OnStcloadTrayTR1YClick(UINT nID)	
{
 	int ID=0;
	if		(nID == IDC_STC_LOAD_TRAY_TR_1_Y_0) ID = 0;
	else if (nID == IDC_STC_LOAD_TRAY_TR_1_Y_1) ID = 1;
	else if (nID == IDC_STC_LOAD_TRAY_TR_1_Y_2) ID = 2;
	else if (nID == IDC_STC_LOAD_TRAY_TR_1_Y_3) ID = 3;
	else if (nID == IDC_STC_LOAD_TRAY_TR_1_Y_4) ID = 4;
	else if (nID == IDC_STC_LOAD_TRAY_TR_1_Y_5) ID = 5;
	else if (nID == IDC_STC_LOAD_TRAY_TR_1_Y_6) ID = 6;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	
	m_stcLoadTrayTR1Y[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcLoadTrayTR1Y[ID].SetWindowText(strNew);
	}
}
void CSetupMoveTab1Dlg::OnStcloadTrayTR1ZClick(UINT nID)
{
 	int ID=0;
	if		(nID == IDC_STC_LD_TRAY_TR_1_Z_0) ID = 0;
	else if (nID == IDC_STC_LD_TRAY_TR_1_Z_1) ID = 1;
	else if (nID == IDC_STC_LD_TRAY_TR_1_Z_2) ID = 2;
	else if (nID == IDC_STC_LD_TRAY_TR_1_Z_3) ID = 3;
	else if (nID == IDC_STC_LD_TRAY_TR_1_Z_4) ID = 4;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;

	m_stcLoadTrayTR1Z[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcLoadTrayTR1Z[ID].SetWindowText(strNew);
	}
}
void CSetupMoveTab1Dlg::OnStcloadTrayTR2YClick(UINT nID)
{
 	int ID=0;
	if		(nID == IDC_STC_LOAD_TRAY_TR_2_Y_0) ID = 0;
	else if (nID == IDC_STC_LOAD_TRAY_TR_2_Y_1) ID = 1;
	else if (nID == IDC_STC_LOAD_TRAY_TR_2_Y_2) ID = 2;
	else if (nID == IDC_STC_LOAD_TRAY_TR_2_Y_3) ID = 3;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;

	m_stcLoadTrayTR2Y[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcLoadTrayTR2Y[ID].SetWindowText(strNew);
	}
}
void CSetupMoveTab1Dlg::OnStcloadTrayTR2ZClick(UINT nID)
{
 	int ID=0;
	if		(nID == IDC_STC_LOAD_TRAY_TR_2_Z_0) ID = 0;
	else if (nID == IDC_STC_LOAD_TRAY_TR_2_Z_1) ID = 1;
	else if (nID == IDC_STC_LOAD_TRAY_TR_2_Z_2) ID = 2;
	else if (nID == IDC_STC_LOAD_TRAY_TR_2_Z_3) ID = 3;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;

	m_stcLoadTrayTR2Z[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcLoadTrayTR2Z[ID].SetWindowText(strNew);
	}
}
void CSetupMoveTab1Dlg::OnStcVisionXClick(UINT nID)
{
 	int ID=0;
	if		(nID == IDC_STC_VISION_X_0) ID = 0;
	else if (nID == IDC_STC_VISION_X_1) ID = 1;
	else if (nID == IDC_STC_VISION_X_2) ID = 2;
	else if (nID == IDC_STC_VISION_X_3) ID = 3;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcVisionX[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcVisionX[ID].SetWindowText(strNew);
	}
}

void CSetupMoveTab1Dlg::OnBnClickedBtnSave()
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

	strSection = "LOAD_TRAY_X1";
	for (int i = 0; i < 5; i++) {
		m_stcShuttleX[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("X%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dLoadTrayX1[i] != dData) {
			sData.Format("[Setup - Load/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dLoadTrayX1[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "LOAD_TRAY_X2";
	for (int i = 0; i < 5; i++) {
		m_stcLoadTrayTR1Z[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("X%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dLoadTrayX2[i] != dData) {
			sData.Format("[Setup - Load/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dLoadTrayX2[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "LOAD_TRAY_Z1";
	for (int i = 0; i < 4; i++) {
		m_stcLoadTrayTR2Y[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Z%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dLoadTrayZ1[i] != dData) {
			sData.Format("[Setup - Load/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dLoadTrayZ1[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "LOAD_TRAY_Z2";
	for (int i = 0; i < 4; i++) {
		m_stcVisionX[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Z%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dLoadTrayZ2[i] != dData) {
			sData.Format("[Setup - Load/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dLoadTrayZ2[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "LOAD_PICKER_Y1";
	for (int i = 0; i < 3; i++) {
		m_stcLoadTrayTR1Y[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Y%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dLoadPickerY1[i] != dData) {
			sData.Format("[Setup - Load/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dLoadPickerY1[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "LOAD_PICKER_Y2";
	for (int i = 0; i < 4; i++) {
		m_stcLoadTrayTR1Y[i+3].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Y%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dLoadPickerY2[i] != dData) {
			sData.Format("[Setup - Load/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dLoadPickerY2[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "LOAD_PICKER_Z";
	for (int i = 0; i < 4; i++) {
		m_stcLoadTrayTR2Z[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Z%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		// RMS 항목 저장
		if (i == 1) g_objMES.Save_AviRmsData("Load Picker Z Load1 Down Position", strData);
		if (i == 2) g_objMES.Save_AviRmsData("Load Picker Z Load2 Down Position", strData);
		if (i == 3) g_objMES.Save_AviRmsData("Load Picker Z Index Down Position", strData);

		if (pMoveData->dLoadPickerZ[i] != dData) {
			sData.Format("[Setup - Load/Tray Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dLoadPickerZ[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	pLogFile->Save_HandlerLog("[Setup - Load/Tray Picker] save");

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

void CSetupMoveTab1Dlg::OnBnClickedBtnCancel()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	pDataManager->Read_MoveData();

	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab1Dlg::Initial_Controls() 
{
	for (int i = 0; i < 6; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	for (int i = 0; i < 44; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 5; i++) m_stcShuttleX[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 7; i++) m_stcLoadTrayTR1Y[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 5; i++) m_stcLoadTrayTR1Z[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 4; i++) m_stcLoadTrayTR2Y[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 4; i++) m_stcLoadTrayTR2Z[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 4; i++) m_stcVisionX[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xFF, 0xF0));

	m_btnSave.Init_Ctrl("바탕", 15, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);	
	m_btnCancel.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
}

void CSetupMoveTab1Dlg::Display_MoveData()
{
	CString strData;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	for (int i = 0; i < 5; i++) {
		strData.Format("%0.3lf", pMoveData->dLoadTrayX1[i]);
		m_stcShuttleX[i].SetWindowText(strData);
	}	
	for (int i = 0; i < 5; i++) {
		strData.Format("%0.3lf", pMoveData->dLoadTrayX2[i]);
		m_stcLoadTrayTR1Z[i].SetWindowText(strData);
	}	

	for (int i = 0; i < 4; i++) {
		strData.Format("%0.3lf", pMoveData->dLoadTrayZ1[i]);
		m_stcLoadTrayTR2Y[i].SetWindowText(strData);
	}	
	for (int i = 0; i < 4; i++) {
		strData.Format("%0.3lf", pMoveData->dLoadTrayZ2[i]);
		m_stcVisionX[i].SetWindowText(strData);
	}

	for (int i = 0; i < 3; i++) {
		strData.Format("%0.3lf", pMoveData->dLoadPickerY1[i]);
		m_stcLoadTrayTR1Y[i].SetWindowText(strData);
	}	
	for (int i = 0; i < 4; i++) {
		strData.Format("%0.3lf", pMoveData->dLoadPickerY2[i]);
		m_stcLoadTrayTR1Y[i+3].SetWindowText(strData);
	}	
	for (int i = 0; i < 4; i++) {
		strData.Format("%0.3lf", pMoveData->dLoadPickerZ[i]);
		m_stcLoadTrayTR2Z[i].SetWindowText(strData);
	}	

}

///////////////////////////////////////////////////////////////////////////////
