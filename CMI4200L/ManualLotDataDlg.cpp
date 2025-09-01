// ManualLotDataDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CMI4200L.h"
#include "ManualLotDataDlg.h"
#include "afxdialogex.h"
#include "ListBoxDlg.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "LogFile.h"
#include "ManualDlg.h"
#include "ExtBarcode_Honeywell.h"

// CManualLotDataDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualLotDataDlg, CDialogEx)

CManualLotDataDlg::CManualLotDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualLotDataDlg::IDD, pParent)
{

}

CManualLotDataDlg::~CManualLotDataDlg()
{
}

void CManualLotDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_0, m_Group[0]);
	DDX_Control(pDX, IDC_GROUP_1, m_Group[1]);
	DDX_Control(pDX, IDC_GROUP_2, m_Group[2]);
	DDX_Control(pDX, IDC_GROUP_3, m_Group[3]);
	DDX_Control(pDX, IDC_GROUP_4, m_Group[4]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	DDX_Control(pDX, IDC_LABEL_4, m_Label[4]);
	DDX_Control(pDX, IDC_LABEL_5, m_Label[5]);
	for (int i = 0; i < 60; i++) DDX_Control(pDX, IDC_LABEL_S_1 + i, m_Labels[i]);

	DDX_Control(pDX, IDC_STC_LOT_ID, m_stcLotID);
	DDX_Control(pDX, IDC_STC_PACKAGE_NAME, m_stcPackageName);
	DDX_Control(pDX, IDC_STC_TOTAL_SLOT, m_stcSlotCount);
	DDX_Control(pDX, IDC_STC_MODEL_NAME, m_stcModelName);
	DDX_Control(pDX, IDC_STC_SHIFT_NAME, m_stcShiftID);
	DDX_Control(pDX, IDC_STC_OPER_NAME, m_stcOperID);
	for (int i = 0; i < 60; i++) DDX_Control(pDX, IDC_STC_SID_1 + i, m_stcSID[i]);
	DDX_Control(pDX, IDC_STC_SID_EDIT, m_stcSIDEdit);

	DDX_Control(pDX, IDC_BTN_LOTID_APPLY, m_btnLotApply);
	DDX_Control(pDX, IDC_BTN_OPERID_APPLY, m_btnOperApply);
	DDX_Control(pDX, IDC_BTN_SID_APPLY, m_btnSIDApply);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CManualLotDataDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_STN_CLICKED(IDC_STC_LOT_ID, &CManualLotDataDlg::OnStnClickedStcLotID)
	ON_STN_CLICKED(IDC_STC_PACKAGE_NAME, &CManualLotDataDlg::OnStnClickedStcPackageName)
	ON_STN_CLICKED(IDC_STC_TOTAL_SLOT, &CManualLotDataDlg::OnStnClickedStcSlotCount)
	ON_STN_CLICKED(IDC_STC_MODEL_NAME, &CManualLotDataDlg::OnStnClickedStcModelName)
	ON_STN_CLICKED(IDC_STC_SHIFT_NAME, &CManualLotDataDlg::OnStnClickedStcShiftID)
	ON_STN_CLICKED(IDC_STC_OPER_NAME, &CManualLotDataDlg::OnStnClickedStcOperID)
	ON_STN_CLICKED(IDC_STC_SID_EDIT, &CManualLotDataDlg::OnStnClickedStcSIDEdit)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_SID_1, IDC_STC_SID_60, OnStnClickedStcSID)
	
	ON_BN_CLICKED(IDC_BTN_LOTID_APPLY, &CManualLotDataDlg::OnBnClickedBtnLotApply)
	ON_BN_CLICKED(IDC_BTN_OPERID_APPLY, &CManualLotDataDlg::OnBnClickedBtnOperApply)
	ON_BN_CLICKED(IDC_BTN_SID_APPLY, &CManualLotDataDlg::OnBnClickedBtnSIDApply)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CManualLotDataDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CManualLotDataDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_SID_APPLY3, &CManualLotDataDlg::OnBnClickedBtnSidApply3)
	ON_BN_CLICKED(IDC_BTN_SID_APPLY4, &CManualLotDataDlg::OnBnClickedBtnSidApply4)
	ON_BN_CLICKED(IDC_BTN_SID_APPLY5, &CManualLotDataDlg::OnBnClickedBtnSidApply5)
END_MESSAGE_MAP()


// CManualLotDataDlg 메시지 처리기입니다.
BOOL CManualLotDataDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CManualLotDataDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CManualLotDataDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualLotDataDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		for (int i = 0; i < 60; i++) {
			CString sTemp;
			sTemp.Format("  %02d", i+1);
			m_Labels[i].SetWindowText(sTemp);
		}

		LotData_Read();
		Display_LotData();
	}
}

void CManualLotDataDlg::OnStnClickedStcLotID()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcLotID.SetWindowText(strKey);
	}
}

void CManualLotDataDlg::OnStnClickedStcPackageName()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcPackageName.SetWindowText(strKey);
	}
}

void CManualLotDataDlg::OnStnClickedStcSlotCount()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcSlotCount.GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		int nMax = atoi(strNew);
		if(nMax<1 || nMax > 60) {
			AfxMessageBox(_T("Input Error of Slot Total Count (1~60) !!!"));
			return;
		}
		m_stcSlotCount.SetWindowText(strNew);
	}
}

void CManualLotDataDlg::OnStnClickedStcModelName()
{
	gData.nType = 1;
	CListBoxDlg dlgListBox;
	int nRst = dlgListBox.DoModal();

	if(gData.sListName != "") {
		m_stcModelName.SetWindowText(gData.sListName);
	}
}

void CManualLotDataDlg::OnStnClickedStcShiftID()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcShiftID.SetWindowText(strKey);
	}
}

void CManualLotDataDlg::OnStnClickedStcOperID()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcOperID.SetWindowText(strKey);
	}
}

void CManualLotDataDlg::OnStnClickedStcSIDEdit()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcSIDEdit.SetWindowText(strKey);
	}
}

void CManualLotDataDlg::OnStnClickedStcSID(UINT nID) 
{
	int ID = nID - IDC_STC_SID_1;
	
	CCommon *pCommon = CCommon::Get_Instance();
	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcSID[ID].SetWindowText(strKey);
	}
}

void CManualLotDataDlg::OnBnClickedBtnSIDApply()
{
	int		nMax;
	CString sInput, sData;

	m_stcSlotCount.GetWindowText(sInput);
	nMax = atoi(sInput);
	if(nMax<1 || nMax > 60) {
		AfxMessageBox(_T("Input Error of Slot Total Count (1~60) !!!"));
		return;
	}

	m_stcSIDEdit.GetWindowText(sInput);
	if (sInput.GetLength() < 1) {
		AfxMessageBox(_T("Input Error of Slot ID Data !!!"));
		return;
	}

	for (int i=0; i<nMax; i++) {
		sData.Format("%s_%02d", sInput, i+1);
		m_stcSID[i].SetWindowText(sData);
	}
	for (int i=nMax; i<60; i++) {
		sData = "";
		m_stcSID[i].SetWindowText(sData);
	}
}

void CManualLotDataDlg::OnBnClickedBtnSave()
{
	//CString sData;

	//m_stcLotID.GetWindowText(gData.sLotID);
	//m_stcPackageName.GetWindowText(gData.sPackageName);
	//m_stcModelName.GetWindowText(gData.sModelName);
	//m_stcShiftID.GetWindowText(gData.sShiftID);
	//m_stcOperID.GetWindowText(gData.sOperID);
	//m_stcSlotCount.GetWindowText(sData);
	//gData.nMaxCnt = atoi(sData);
	//for (int i=0; i<60; i++) {
	//	m_stcSID[i].GetWindowText(gData.sSID[i+1]);
	//}

	//LotData_Write();
}

void CManualLotDataDlg::OnBnClickedBtnCancel()
{
	LotData_Read();
	Display_LotData();
}

void CManualLotDataDlg::OnBnClickedBtnLotApply()
{
	//barcode reading...
	CExtBarcode_Honeywell *m_pExtBarcode = CExtBarcode_Honeywell::Get_Instance();

	CString sData;
	m_pExtBarcode->GetBarcode(sData);
	if (sData.GetLength() < 1) {
		AfxMessageBox(_T("Barcode read data not found !!!"));
		return;
	}
	m_stcLotID.SetWindowText(sData);
}

void CManualLotDataDlg::OnBnClickedBtnOperApply()
{
	//barcode reading...
	CExtBarcode_Honeywell *m_pExtBarcode = CExtBarcode_Honeywell::Get_Instance();

	CString sData;
	m_pExtBarcode->GetBarcode(sData);
	if (sData.GetLength() < 1) {
		AfxMessageBox(_T("Barcode read data not found !!!"));
		return;
	}
	m_stcOperID.SetWindowText(sData);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CManualLotDataDlg::Initial_Controls() 
{
	for (int i = 0; i < 5; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	for (int i = 0; i < 6; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x80, 0xC0));
	for (int i = 0; i < 60; i++) m_Labels[i].Init_Ctrl("바탕", 9, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	m_stcLotID.Init_Ctrl("바탕", 10, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xC0, 0x80));
	m_stcPackageName.Init_Ctrl("바탕", 10, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xC0, 0x80));
	m_stcSlotCount.Init_Ctrl("바탕", 10, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xC0, 0x80));
	m_stcModelName.Init_Ctrl("바탕", 10, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xC0, 0x80));
	m_stcShiftID.Init_Ctrl("바탕", 10, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xC0, 0x80));
	m_stcOperID.Init_Ctrl("바탕", 10, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xC0, 0x80));
	m_stcSIDEdit.Init_Ctrl("바탕", 10, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x80, 0xF0, 0xF0));

	for (int i = 0; i < 60; i++) m_stcSID[i].Init_Ctrl("바탕", 10, TRUE, RGB(0xFF, 0x00, 0x00), RGB(0xFF, 0xFF, 0xE0));

	m_btnLotApply.Init_Ctrl("바탕", 8, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnOperApply.Init_Ctrl("바탕", 8, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
//	m_btnSIDApply.Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnSave.Init_Ctrl("바탕", 15, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnCancel.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
}

void CManualLotDataDlg::Display_LotData()
{
	//CString sData;

	//m_stcLotID.SetWindowText(gData.sLotID);
	//m_stcPackageName.SetWindowText(gData.sPackageName);
	//m_stcModelName.SetWindowText(gData.sModelName);
	//m_stcShiftID.SetWindowText(gData.sShiftID);
	//m_stcOperID.SetWindowText(gData.sOperID);
	//sData.Format("%d", gData.nMaxCnt);
	//m_stcSlotCount.SetWindowText(sData);
	//for (int i=0; i<60; i++) {
	//	sData = gData.sSID[i+1];
	//	m_stcSID[i].SetWindowText(sData);
	//}
}

void CManualLotDataDlg::Display_Status()
{
}

void CManualLotDataDlg::LotData_Read()
{
	//CString strSection, strKey;

	//CIniFileCS INI("System/LotData.ini");
	//if (!INI.Check_File()) return;

	//strSection = "LOT_DATA";
	//gData.sLotID = INI.Get_String(strSection, "LOT_ID", "");
	//gData.sPackageName = INI.Get_String(strSection, "PACKAGE_NAME", "");
	//gData.sModelName = INI.Get_String(strSection, "MODEL_NAME", "");
	//gData.sShiftID = INI.Get_String(strSection, "SHIFT_ID", "");
	//gData.sOperID = INI.Get_String(strSection, "OPER_ID", "");
	//gData.nMaxCnt = INI.Get_Integer(strSection, "LOT_COUNT", 0);
	//for(int i=1; i<61; i++) {
	//	strKey.Format("SID_%02d", i);
	//	gData.sSID[i] = INI.Get_String(strSection, strKey, "");
	//}
}

void CManualLotDataDlg::LotData_Write()
{
	//CString strSection, strKey;

	//CIniFileCS INI("System/LotData.ini");
	//if (!INI.Check_File()) return;

	//strSection = "LOT_DATA";
	//INI.Set_String(strSection, "LOT_ID", gData.sLotID);
	//INI.Set_String(strSection, "PACKAGE_NAME", gData.sPackageName);
	//INI.Set_String(strSection, "MODEL_NAME", gData.sModelName);
	//INI.Set_String(strSection, "SHIFT_ID", gData.sShiftID);
	//INI.Set_String(strSection, "OPER_ID", gData.sOperID);
	//INI.Set_Integer(strSection, "LOT_COUNT", gData.nMaxCnt);
	//for(int i=1; i<61; i++) {
	//	strKey.Format("SID_%02d", i);
	//	INI.Set_String(strSection, strKey, gData.sSID[i]);
	//}

	//CIniFileCS INI_Equ("System/EquipData.ini");
	//INI_Equ.Set_String("MODEL", "CURRENT", gData.sModelName);

	//CDataManager *pDataManager = CDataManager::Get_Instance();
	//pDataManager->Read_EquipData();
	//pDataManager->Read_ModelData();
	//pDataManager->Read_MoveData();

	//MODEL_DATA *pModelData = pDataManager->Get_pModelData();
}

void CManualLotDataDlg::OnBnClickedBtnSidApply3()
{
	int		nMax;
	CString sInput, sData;

	m_stcSlotCount.GetWindowText(sInput);
	nMax = atoi(sInput);
	if(nMax<1 || nMax > 60) {
		AfxMessageBox(_T("Input Error of Slot Total Count (1~60) !!!"));
		return;
	}

	m_stcSIDEdit.GetWindowText(sInput);
	if (sInput.GetLength() < 1) {
		AfxMessageBox(_T("Input Error of Slot ID Data !!!"));
		return;
	}

	for (int i=0; i<nMax; i++) {
		sData.Format("%s%02d", sInput, i+1);
		m_stcSID[i].SetWindowText(sData);
	}
	for (int i=nMax; i<60; i++) {
		sData = "";
		m_stcSID[i].SetWindowText(sData);
	}
}


void CManualLotDataDlg::OnBnClickedBtnSidApply4()
{
	int		nMax;
	CString sInput, sData;

	m_stcSlotCount.GetWindowText(sInput);
	nMax = atoi(sInput);
	if(nMax<1 || nMax > 60) {
		AfxMessageBox(_T("Input Error of Slot Total Count (1~60) !!!"));
		return;
	}

	m_stcSIDEdit.GetWindowText(sInput);
	if (sInput.GetLength() < 1) {
		AfxMessageBox(_T("Input Error of Slot ID Data !!!"));
		return;
	}

	for (int i=0; i<nMax; i++) {
		sData.Format("%s_%03d", sInput, i+1);
		m_stcSID[i].SetWindowText(sData);
	}
	for (int i=nMax; i<60; i++) {
		sData = "";
		m_stcSID[i].SetWindowText(sData);
	}
}


void CManualLotDataDlg::OnBnClickedBtnSidApply5()
{
	int		nMax;
	CString sInput, sData;

	m_stcSlotCount.GetWindowText(sInput);
	nMax = atoi(sInput);
	if(nMax<1 || nMax > 60) {
		AfxMessageBox(_T("Input Error of Slot Total Count (1~60) !!!"));
		return;
	}

	m_stcSIDEdit.GetWindowText(sInput);
	if (sInput.GetLength() < 1) {
		AfxMessageBox(_T("Input Error of Slot ID Data !!!"));
		return;
	}

	for (int i=0; i<nMax; i++) {
		sData.Format("%s%03d", sInput, i+1);
		m_stcSID[i].SetWindowText(sData);
	}
	for (int i=nMax; i<60; i++) {
		sData = "";
		m_stcSID[i].SetWindowText(sData);
	}
}
