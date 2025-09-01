// SetupMoveTab2Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupMoveTab2Dlg.h"
#include "afxdialogex.h"

#include "DataManager.h"
#include "Common.h"
#include "LogFile.h"

// CSetupMoveTab2Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab2Dlg, CDialogEx)

CSetupMoveTab2Dlg::CSetupMoveTab2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab2Dlg::IDD, pParent)
{
}

CSetupMoveTab2Dlg::~CSetupMoveTab2Dlg()
{
}

void CSetupMoveTab2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	DDX_Control(pDX, IDC_GROUP_4, m_Group[4]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	DDX_Control(pDX, IDC_LABEL_12, m_Label[12]);
	DDX_Control(pDX, IDC_LABEL_13, m_Label[13]);
	DDX_Control(pDX, IDC_LABEL_14, m_Label[14]);
	DDX_Control(pDX, IDC_LABEL_15, m_Label[15]);

	DDX_Control(pDX, IDC_STC_INSPECT_TRAY_TR_X_0, m_stcInspectTrayTRX[0]);
	DDX_Control(pDX, IDC_STC_INSPECT_TRAY_TR_X_1, m_stcInspectTrayTRX[1]);
	DDX_Control(pDX, IDC_STC_INSPECT_TRAY_TR_X_2, m_stcInspectTrayTRX[2]);
	DDX_Control(pDX, IDC_STC_INSPECT_TRAY_TR_X_3, m_stcInspectTrayTRX[3]);
	DDX_Control(pDX, IDC_STC_INSPECT_TRAY_TR_X_4, m_stcInspectTrayTRX[4]);
	DDX_Control(pDX, IDC_STC_INSPECT_TRAY_TR_X_5, m_stcInspectTrayTRX[5]);
	DDX_Control(pDX, IDC_STC_INSPECT_TRAY_TR_X_6, m_stcInspectTrayTRX[6]);
	DDX_Control(pDX, IDC_STC_INSPECT_TRAY_TR_X_7, m_stcInspectTrayTRX[7]);
	DDX_Control(pDX, IDC_STC_COVER_2_Z_0, m_stcCover2Z[0]);
	DDX_Control(pDX, IDC_STC_INSPECT_TRAY_TR_R_0, m_stcInspectTrayTRR[0]);
	DDX_Control(pDX, IDC_STC_COVER_1_Z_0, m_stcCover1Z[0]);
	DDX_Control(pDX, IDC_STC_COVER_1_Z_2, m_stcCover1Z[1]);
	DDX_Control(pDX, IDC_STC_NGSTAGE_Y_0, m_stcNGStageY[0]);
	DDX_Control(pDX, IDC_STC_NGSTAGE_Y_1, m_stcNGStageY[1]);
	DDX_Control(pDX, IDC_STC_NGSTAGE_Y_2, m_stcNGStageY[2]);
	DDX_Control(pDX, IDC_STC_NGSTAGE_Y_3, m_stcNGStageY[3]);

	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CSetupMoveTab2Dlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_INSPECT_TRAY_TR_X_0, IDC_STC_INSPECT_TRAY_TR_X_0, OnStcInspectTrayTRXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_INSPECT_TRAY_TR_X_1, IDC_STC_INSPECT_TRAY_TR_X_1, OnStcInspectTrayTRXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_INSPECT_TRAY_TR_X_2, IDC_STC_INSPECT_TRAY_TR_X_2, OnStcInspectTrayTRXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_INSPECT_TRAY_TR_X_3, IDC_STC_INSPECT_TRAY_TR_X_3, OnStcInspectTrayTRXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_INSPECT_TRAY_TR_X_4, IDC_STC_INSPECT_TRAY_TR_X_4, OnStcInspectTrayTRXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_INSPECT_TRAY_TR_X_5, IDC_STC_INSPECT_TRAY_TR_X_5, OnStcInspectTrayTRXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_INSPECT_TRAY_TR_X_6, IDC_STC_INSPECT_TRAY_TR_X_6, OnStcInspectTrayTRXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_INSPECT_TRAY_TR_X_7, IDC_STC_INSPECT_TRAY_TR_X_7, OnStcInspectTrayTRXClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_COVER_1_Z_0, IDC_STC_COVER_1_Z_0, OnStcCover1ZYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_COVER_1_Z_2, IDC_STC_COVER_1_Z_2, OnStcCover1ZYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_COVER_2_Z_0, IDC_STC_COVER_2_Z_0, OnStcCover2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_INSPECT_TRAY_TR_R_0, IDC_STC_INSPECT_TRAY_TR_R_0, OnStcInspectTrayTRRClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NGSTAGE_Y_0, IDC_STC_NGSTAGE_Y_0, OnstcNGStageYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NGSTAGE_Y_1, IDC_STC_NGSTAGE_Y_1, OnstcNGStageYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NGSTAGE_Y_2, IDC_STC_NGSTAGE_Y_2, OnstcNGStageYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_NGSTAGE_Y_3, IDC_STC_NGSTAGE_Y_3, OnstcNGStageYClick)

	ON_BN_CLICKED(IDC_BTN_SAVE, &CSetupMoveTab2Dlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSetupMoveTab2Dlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()

// CSetupMoveTab2Dlg 메시지 처리기입니다.

BOOL CSetupMoveTab2Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 55, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetupMoveTab2Dlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CSetupMoveTab2Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab2Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		m_Label[15].ShowWindow(gData.bUseCMPress);
		m_stcCover1Z[1].ShowWindow(gData.bUseCMPress);
		Display_MoveData();
	}
}


//kty
void CSetupMoveTab2Dlg::OnStcCover1ZYClick(UINT nID)
{
 	int ID=0;
	if (nID == IDC_STC_COVER_1_Z_0) ID=0;
	else							ID=1;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcCover1Z[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcCover1Z[ID].SetWindowText(strNew);
	}

}
void CSetupMoveTab2Dlg::OnStcCover2ZClick(UINT nID)
{
 	int ID=0;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcCover2Z[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcCover2Z[ID].SetWindowText(strNew);
	}

}
void CSetupMoveTab2Dlg::OnStcInspectTrayTRXClick(UINT nID)
{
 	int ID=0;
	if		(nID == IDC_STC_INSPECT_TRAY_TR_X_0) ID = 0;
	else if (nID == IDC_STC_INSPECT_TRAY_TR_X_1) ID = 1;
	else if (nID == IDC_STC_INSPECT_TRAY_TR_X_2) ID = 2;
	else if (nID == IDC_STC_INSPECT_TRAY_TR_X_3) ID = 3;
	else if (nID == IDC_STC_INSPECT_TRAY_TR_X_4) ID = 4;
	else if (nID == IDC_STC_INSPECT_TRAY_TR_X_5) ID = 5;
	else if (nID == IDC_STC_INSPECT_TRAY_TR_X_6) ID = 6;
	else if (nID == IDC_STC_INSPECT_TRAY_TR_X_7) ID = 7;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	
	m_stcInspectTrayTRX[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcInspectTrayTRX[ID].SetWindowText(strNew);
	}
}

void CSetupMoveTab2Dlg::OnStcInspectTrayTRRClick(UINT nID)
{
 	int ID=0;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcInspectTrayTRR[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcInspectTrayTRR[ID].SetWindowText(strNew);
	}
}

void CSetupMoveTab2Dlg::OnstcNGStageYClick(UINT nID)
{
 	int ID=0;
	if		(nID == IDC_STC_NGSTAGE_Y_0) ID = 0;
	else if (nID == IDC_STC_NGSTAGE_Y_1) ID = 1;
	else if (nID == IDC_STC_NGSTAGE_Y_2) ID = 2;
	else if (nID == IDC_STC_NGSTAGE_Y_3) ID = 3;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	
	m_stcNGStageY[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcNGStageY[ID].SetWindowText(strNew);
	}
}


void CSetupMoveTab2Dlg::OnBnClickedBtnSave()
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

	strSection = "INDEX_R";
	for (int i = 0; i < 8; i++) {
		m_stcInspectTrayTRX[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("R%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dIndexR[i] != dData) {
			sData.Format("[Setup - Index/Inspection] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dIndexR[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "BARCODE_A";
	for (int i = 0; i < 1; i++) {
		m_stcCover2Z[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("A%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dBarCodeA[i] != dData) {
			sData.Format("[Setup - Index/Inspection] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dBarCodeA[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "INSPECTION_A";
	for (int i = 0; i < 1; i++) {
		m_stcInspectTrayTRR[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("A%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dInspectionA[i] != dData) {
			sData.Format("[Setup - Index/Inspection] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dInspectionA[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "INSPECTION_Z";
	for (int i = 0; i < 2; i++) {
		m_stcCover1Z[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Z%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dInspectionZ[i] != dData) {
			sData.Format("[Setup - Index/Inspection] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dInspectionZ[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	strSection = "NG_STAGE_Y";
	for (int i = 0; i < 4; i++) {
		m_stcNGStageY[i].GetWindowText(strData);
		dData = atof(strData);
		strKey.Format("Y%02d", i);
		INI.Set_Double(strSection, strKey, dData, "%0.3lf");

		if (pMoveData->dNGStageY[i] != dData) {
			sData.Format("[Setup - Index/Inspection] ==> Group[%s] : Item[%s] Value[%0.3lf=>%0.3lf]", strSection, strKey, pMoveData->dNGStageY[i], dData);
			pLogFile->Save_HistoryLog(sData);
		}
	}

	pLogFile->Save_HandlerLog("[Setup - Index/Inspection] save");

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

void CSetupMoveTab2Dlg::OnBnClickedBtnCancel()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	pDataManager->Read_MoveData();

	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab2Dlg::Initial_Controls() 
{
	for (int i = 0; i < 5; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	for (int i = 0; i < 16; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 2; i++) m_stcCover1Z[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xB0, 0xF0, 0xB0));
	for (int i = 0; i < 1; i++) m_stcCover2Z[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xB0, 0xF0, 0xB0));
	for (int i = 0; i < 8; i++) m_stcInspectTrayTRX[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xB0, 0xF0, 0xB0));
	for (int i = 0; i < 1; i++) m_stcInspectTrayTRR[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xB0, 0xF0, 0xB0));
	for (int i = 0; i < 4; i++) m_stcNGStageY[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xB0, 0xF0, 0xB0));

	m_btnSave.Init_Ctrl("바탕", 15, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnCancel.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
}

void CSetupMoveTab2Dlg::Display_MoveData()
{
	CString strData;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MOVE_DATA *pMoveData = pDataManager->Get_pMoveData();

	for (int i = 0; i < 8; i++) {
		strData.Format("%0.3lf", pMoveData->dIndexR[i]);
		m_stcInspectTrayTRX[i].SetWindowText(strData);
	}

	for (int i = 0; i < 1; i++) {
		strData.Format("%0.3lf", pMoveData->dBarCodeA[i]);
		m_stcCover2Z[i].SetWindowText(strData);
	}

	for (int i = 0; i < 1; i++) {
		strData.Format("%0.3lf", pMoveData->dInspectionA[i]);
		m_stcInspectTrayTRR[i].SetWindowText(strData);
	}

	for (int i = 0; i < 2; i++) {
		strData.Format("%0.3lf", pMoveData->dInspectionZ[i]);
		m_stcCover1Z[i].SetWindowText(strData);
	}

	for (int i = 0; i < 4; i++) {
		strData.Format("%0.3lf", pMoveData->dNGStageY[i]);
		m_stcNGStageY[i].SetWindowText(strData);
	}

}

