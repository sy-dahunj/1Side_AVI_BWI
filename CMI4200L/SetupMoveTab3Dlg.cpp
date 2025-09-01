// SetupMoveTab3Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupMoveTab3Dlg.h"
#include "afxdialogex.h"

#include "DataManager.h"
#include "Common.h"
#include "LogFile.h"
#include "MESInterface.h"

// CSetupMoveTab3Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab3Dlg, CDialogEx)

CSetupMoveTab3Dlg::CSetupMoveTab3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab3Dlg::IDD, pParent)
{
}

CSetupMoveTab3Dlg::~CSetupMoveTab3Dlg()
{
}

void CSetupMoveTab3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 22; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	DDX_Control(pDX, IDC_LABEL_22, m_Label[22]);
	DDX_Control(pDX, IDC_LABEL_23, m_Label[23]);
	DDX_Control(pDX, IDC_LABEL_24, m_Label[24]);
	DDX_Control(pDX, IDC_LABEL_25, m_Label[25]);
	DDX_Control(pDX, IDC_LABEL_26, m_Label[26]);
	DDX_Control(pDX, IDC_LABEL_27, m_Label[27]);
	DDX_Control(pDX, IDC_LABEL_28, m_Label[28]);
	DDX_Control(pDX, IDC_LABEL_29, m_Label[29]);
	DDX_Control(pDX, IDC_LABEL_30, m_Label[30]);
	DDX_Control(pDX, IDC_LABEL_31, m_Label[31]);
	DDX_Control(pDX, IDC_LABEL_32, m_Label[32]);
	DDX_Control(pDX, IDC_LABEL_33, m_Label[33]);
	DDX_Control(pDX, IDC_LABEL_34, m_Label[34]);

	DDX_Control(pDX, IDC_STC_NG_PICKER_X_0, m_stcNGPickerX[0]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_X_1, m_stcNGPickerX[1]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_X_2, m_stcNGPickerX[2]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_X_3, m_stcNGPickerX[3]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_X_4, m_stcNGPickerX[4]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_X_5, m_stcNGPickerX[5]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_X_6, m_stcNGPickerX[6]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_X_7, m_stcNGPickerX[7]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_Z_0, m_stcNGPickerZ[0]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_Z_1, m_stcNGPickerZ[1]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_Z_2, m_stcNGPickerZ[2]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_Z_3, m_stcNGPickerZ[3]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_Z_4, m_stcNGPickerZ[4]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_Z_5, m_stcNGPickerZ[5]);
	DDX_Control(pDX, IDC_STC_NG_PICKER_Z_6, m_stcNGPickerZ[6]);

	DDX_Control(pDX, IDC_STC_GOOD_PICKER_X_0, m_stcGOODPickerY[0]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_X_1, m_stcGOODPickerY[1]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_X_2, m_stcGOODPickerY[2]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_X_3, m_stcGOODPickerY[3]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_X_4, m_stcGOODPickerY[4]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_X_5, m_stcGOODPickerY[5]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_X_6, m_stcGOODPickerY[6]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_0, m_stcGOODPickerZ[0]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_1, m_stcGOODPickerZ[1]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_2, m_stcGOODPickerZ[2]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_3, m_stcGOODPickerZ[3]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_4, m_stcGOODPickerZ[4]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_5, m_stcGOODPickerZ[5]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_6, m_stcGOODPickerZ[6]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_7, m_stcGOODPickerZ[7]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_8, m_stcGOODPickerZ[8]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_9, m_stcGOODPickerZ[9]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_10, m_stcGOODPickerZ[10]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_11, m_stcGOODPickerZ[11]);
	DDX_Control(pDX, IDC_STC_GOOD_PICKER_Z_12, m_stcGOODPickerZ[12]);

	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CSetupMoveTab3Dlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_X_0, IDC_STC_NG_PICKER_X_0, OnStcNGPickerXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_X_1, IDC_STC_NG_PICKER_X_1, OnStcNGPickerXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_X_2, IDC_STC_NG_PICKER_X_2, OnStcNGPickerXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_X_3, IDC_STC_NG_PICKER_X_3, OnStcNGPickerXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_X_4, IDC_STC_NG_PICKER_X_4, OnStcNGPickerXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_X_5, IDC_STC_NG_PICKER_X_5, OnStcNGPickerXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_X_6, IDC_STC_NG_PICKER_X_6, OnStcNGPickerXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_X_7, IDC_STC_NG_PICKER_X_7, OnStcNGPickerXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_Z_0, IDC_STC_NG_PICKER_Z_0, OnStcNGPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_Z_1, IDC_STC_NG_PICKER_Z_1, OnStcNGPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_Z_2, IDC_STC_NG_PICKER_Z_2, OnStcNGPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_Z_3, IDC_STC_NG_PICKER_Z_3, OnStcNGPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_Z_4, IDC_STC_NG_PICKER_Z_4, OnStcNGPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_Z_5, IDC_STC_NG_PICKER_Z_5, OnStcNGPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NG_PICKER_Z_6, IDC_STC_NG_PICKER_Z_6, OnStcNGPickerZClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_X_0, IDC_STC_GOOD_PICKER_X_0, OnStcGOODPickerYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_X_1, IDC_STC_GOOD_PICKER_X_1, OnStcGOODPickerYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_X_2, IDC_STC_GOOD_PICKER_X_2, OnStcGOODPickerYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_X_3, IDC_STC_GOOD_PICKER_X_3, OnStcGOODPickerYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_X_4, IDC_STC_GOOD_PICKER_X_4, OnStcGOODPickerYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_X_5, IDC_STC_GOOD_PICKER_X_5, OnStcGOODPickerYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_X_6, IDC_STC_GOOD_PICKER_X_6, OnStcGOODPickerYClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_0, IDC_STC_GOOD_PICKER_Z_0, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_1, IDC_STC_GOOD_PICKER_Z_1, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_2, IDC_STC_GOOD_PICKER_Z_2, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_3, IDC_STC_GOOD_PICKER_Z_3, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_4, IDC_STC_GOOD_PICKER_Z_4, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_5, IDC_STC_GOOD_PICKER_Z_5, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_6, IDC_STC_GOOD_PICKER_Z_6, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_7, IDC_STC_GOOD_PICKER_Z_7, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_8, IDC_STC_GOOD_PICKER_Z_8, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_9, IDC_STC_GOOD_PICKER_Z_9, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_10, IDC_STC_GOOD_PICKER_Z_10, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_11, IDC_STC_GOOD_PICKER_Z_11, OnStcGOODPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_GOOD_PICKER_Z_12, IDC_STC_GOOD_PICKER_Z_12, OnStcGOODPickerZClick)

	ON_BN_CLICKED(IDC_BTN_SAVE, &CSetupMoveTab3Dlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSetupMoveTab3Dlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()

// CSetupMoveTab3Dlg 메시지 처리기입니다.

BOOL CSetupMoveTab3Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 55, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetupMoveTab3Dlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CSetupMoveTab3Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab3Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		Display_MoveData();
	}
}


void CSetupMoveTab3Dlg::OnStcNGPickerXClick(UINT nID)			
{
 	int ID=0;
	if		(nID == IDC_STC_NG_PICKER_X_0) ID = 0;
	else if (nID == IDC_STC_NG_PICKER_X_1) ID = 1;
	else if (nID == IDC_STC_NG_PICKER_X_2) ID = 2;
	else if (nID == IDC_STC_NG_PICKER_X_3) ID = 3;
	else if (nID == IDC_STC_NG_PICKER_X_4) ID = 4;
	else if (nID == IDC_STC_NG_PICKER_X_5) ID = 5;
	else if (nID == IDC_STC_NG_PICKER_X_6) ID = 6;
	else if (nID == IDC_STC_NG_PICKER_X_7) ID = 7;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcNGPickerX[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcNGPickerX[ID].SetWindowText(strNew);
	}
}

void CSetupMoveTab3Dlg::OnStcNGPickerZClick(UINT nID)			
{
 	int ID=0;
	if		(nID == IDC_STC_NG_PICKER_Z_0) ID = 0;
	else if (nID == IDC_STC_NG_PICKER_Z_1) ID = 1;
	else if (nID == IDC_STC_NG_PICKER_Z_2) ID = 2;
	else if (nID == IDC_STC_NG_PICKER_Z_3) ID = 3;
	else if (nID == IDC_STC_NG_PICKER_Z_4) ID = 4;
	else if (nID == IDC_STC_NG_PICKER_Z_5) ID = 5;
	else if (nID == IDC_STC_NG_PICKER_Z_6) ID = 6;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;

	m_stcNGPickerZ[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcNGPickerZ[ID].SetWindowText(strNew);
	}
}

void CSetupMoveTab3Dlg::OnStcGOODPickerYClick(UINT nID)	    
{
 	int ID=0;
	if		(nID == IDC_STC_GOOD_PICKER_X_0) ID = 0;
	else if (nID == IDC_STC_GOOD_PICKER_X_1) ID = 1;
	else if (nID == IDC_STC_GOOD_PICKER_X_2) ID = 2;
	else if (nID == IDC_STC_GOOD_PICKER_X_3) ID = 3;
	else if (nID == IDC_STC_GOOD_PICKER_X_4) ID = 4;
	else if (nID == IDC_STC_GOOD_PICKER_X_5) ID = 5;
	else if (nID == IDC_STC_GOOD_PICKER_X_6) ID = 6;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcGOODPickerY[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcGOODPickerY[ID].SetWindowText(strNew);
	}
}
void CSetupMoveTab3Dlg::OnStcGOODPickerZClick(UINT nID)
{
 	int ID=0;
	if		(nID == IDC_STC_GOOD_PICKER_Z_0) ID = 0;
	else if (nID == IDC_STC_GOOD_PICKER_Z_1) ID = 1;
	else if (nID == IDC_STC_GOOD_PICKER_Z_2) ID = 2;
	else if (nID == IDC_STC_GOOD_PICKER_Z_3) ID = 3;
	else if (nID == IDC_STC_GOOD_PICKER_Z_4) ID = 4;
	else if (nID == IDC_STC_GOOD_PICKER_Z_5) ID = 5;
	else if (nID == IDC_STC_GOOD_PICKER_Z_6) ID = 6;
	else if (nID == IDC_STC_GOOD_PICKER_Z_7) ID = 7;
	else if (nID == IDC_STC_GOOD_PICKER_Z_8) ID = 8;
	else if (nID == IDC_STC_GOOD_PICKER_Z_9) ID = 9;
	else if (nID == IDC_STC_GOOD_PICKER_Z_10) ID = 10;
	else if (nID == IDC_STC_GOOD_PICKER_Z_11) ID = 11;
	else if (nID == IDC_STC_GOOD_PICKER_Z_12) ID = 12;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	
	m_stcGOODPickerZ[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcGOODPickerZ[ID].SetWindowText(strNew);
	}
}


void CSetupMoveTab3Dlg::OnBnClickedBtnSave()
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

	strSection = "NG_PICKER_X";
	for (int i = 0; i < 8; i++) {
		m_stcNGPickerX[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("X%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dNGPickerX[i] != dData) {
			sData.Format("[Setup - NG/Good Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dNGPickerX[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "NG_PICKER_Z";
	for (int i = 0; i < 7; i++) {
		m_stcNGPickerZ[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Z%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		// RMS 항목 저장
		if (i == 0) g_objMES.Save_AviRmsData("NG Picker Z Index Down Position", strData);
		if (i == 1) g_objMES.Save_AviRmsData("NG Picker Z Tray Down Position", strData);

		if (pMoveData->dNGPickerZ[i] != dData) {
			sData.Format("[Setup - NG/Good Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dNGPickerZ[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "GOOD_PICKER_Y";
	for (int i = 0; i < 7; i++) {
		m_stcGOODPickerY[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Y%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dGdPickerY[i] != dData) {
			sData.Format("[Setup - NG/Good Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dGdPickerY[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "GOOD_PICKER_Z";
	for (int i = 0; i < 13; i++) {
		m_stcGOODPickerZ[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Z%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		// RMS 항목 저장
		if (i ==  2) g_objMES.Save_AviRmsData("Good Picker Z Picker1 Down Position", strData);
		if (i ==  4) g_objMES.Save_AviRmsData("Good Picker Z Picker2 Down Position", strData);
		if (i ==  6) g_objMES.Save_AviRmsData("Good Picker Z Picker3 Down Position", strData);
		if (i ==  8) g_objMES.Save_AviRmsData("Good Picker Z Picker4 Down Position", strData);
		if (i == 10) g_objMES.Save_AviRmsData("Good Picker Z Picker5 Down Position", strData);
		if (i == 12) g_objMES.Save_AviRmsData("Good Picker Z Picker6 Down Position", strData);

		if (pMoveData->dGdPickerZ[i] != dData) {
			sData.Format("[Setup - NG/Good Picker] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dGdPickerZ[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	pLogFile->Save_HandlerLog("[Setup - NG/Good Picker] save");

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

void CSetupMoveTab3Dlg::OnBnClickedBtnCancel()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	pDataManager->Read_MoveData();

	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab3Dlg::Initial_Controls() 
{
	for (int i = 0; i < 4; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	for (int i = 0; i < 35; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 8; i++) m_stcNGPickerX[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 7; i++) m_stcNGPickerZ[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 7; i++) m_stcGOODPickerY[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 13; i++) m_stcGOODPickerZ[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xEF, 0xD5));

	m_btnSave.Init_Ctrl("바탕", 15, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnCancel.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);

#ifdef NG_PICKER_3
	m_Label[30].ShowWindow(FALSE);
	m_stcNGPickerX[4].ShowWindow(FALSE);
	m_stcNGPickerX[5].ShowWindow(FALSE);
#endif

#ifdef NG_PICKER_4
	//m_Label[30].ShowWindow(FALSE);
	//m_stcNGPickerX[4].ShowWindow(FALSE);
	m_stcNGPickerX[5].ShowWindow(FALSE);
#endif

#ifdef PICKER_4
	m_Label[17].ShowWindow(FALSE);
	m_Label[26].ShowWindow(FALSE);
	m_Label[27].ShowWindow(FALSE);
	m_stcGOODPickerY[5].ShowWindow(FALSE);
	m_stcGOODPickerZ[9].ShowWindow(FALSE);
	m_stcGOODPickerZ[10].ShowWindow(FALSE);

	m_Label[21].ShowWindow(FALSE);
	m_Label[28].ShowWindow(FALSE);
	m_Label[29].ShowWindow(FALSE);
	m_stcGOODPickerY[6].ShowWindow(FALSE);
	m_stcGOODPickerZ[11].ShowWindow(FALSE);
	m_stcGOODPickerZ[12].ShowWindow(FALSE);
#endif

#ifdef PICKER_5
	m_Label[21].ShowWindow(FALSE);
	m_Label[28].ShowWindow(FALSE);
	m_Label[29].ShowWindow(FALSE);
	m_stcGOODPickerY[6].ShowWindow(FALSE);
	m_stcGOODPickerZ[11].ShowWindow(FALSE);
	m_stcGOODPickerZ[12].ShowWindow(FALSE);
#endif
#ifdef PICKER_6
	m_Label[21].ShowWindow(TRUE);
	m_Label[28].ShowWindow(TRUE);
	m_Label[29].ShowWindow(TRUE);
	m_stcGOODPickerY[6].ShowWindow(TRUE);
	m_stcGOODPickerZ[11].ShowWindow(TRUE);
	m_stcGOODPickerZ[12].ShowWindow(TRUE);
#endif
}

void CSetupMoveTab3Dlg::Display_MoveData()
{
	CString strData;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	for (int i = 0; i < 8; i++) {
		strData.Format("%0.3lf", pMoveData->dNGPickerX[i]);
		m_stcNGPickerX[i].SetWindowText(strData);
	}

	for (int i = 0; i < 7; i++) {
		strData.Format("%0.3lf", pMoveData->dNGPickerZ[i]);
		m_stcNGPickerZ[i].SetWindowText(strData);
	}

	for (int i = 0; i < 7; i++) {
		strData.Format("%0.3lf", pMoveData->dGdPickerY[i]);
		m_stcGOODPickerY[i].SetWindowText(strData);
	}

	for (int i = 0; i < 13; i++) {
		strData.Format("%0.3lf", pMoveData->dGdPickerZ[i]);
		m_stcGOODPickerZ[i].SetWindowText(strData);
	}

}

///////////////////////////////////////////////////////////////////////////////
