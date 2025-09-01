// SetupEquipDlg.cpp : ±∏«ˆ ∆ƒ¿œ¿‘¥œ¥Ÿ.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "CMI4200LDlg.h"
#include "SetupEquipDlg.h"
#include "afxdialogex.h"

#include "CapAttachUDP.h"
#include "DataManager.h"
#include "Common.h"
#include "LogFile.h"
#include "MESInterface.h"

// CSetupEquipDlg ¥Î»≠ ªÛ¿⁄¿‘¥œ¥Ÿ.

IMPLEMENT_DYNAMIC(CSetupEquipDlg, CDialogEx)

CSetupEquipDlg::CSetupEquipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupEquipDlg::IDD, pParent)
{
}

CSetupEquipDlg::~CSetupEquipDlg()
{
}

void CSetupEquipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_0, m_Group[0]);
	DDX_Control(pDX, IDC_GROUP_1, m_Group[1]);
	DDX_Control(pDX, IDC_GROUP_2, m_Group[2]);
	DDX_Control(pDX, IDC_GROUP_3, m_Group[3]);
	DDX_Control(pDX, IDC_LABEL_0,  m_Label0);
	DDX_Control(pDX, IDC_LABEL_8,  m_Label8[0]);
	DDX_Control(pDX, IDC_LABEL_9,  m_Label8[1]);
	DDX_Control(pDX, IDC_LABEL_10,  m_Label8[2]);
	DDX_Control(pDX, IDC_LABEL_11,  m_Label8[3]);
	DDX_Control(pDX, IDC_LABEL_12,  m_Label8[4]);
	DDX_Control(pDX, IDC_LABEL_13,  m_Label8[5]);
	DDX_Control(pDX, IDC_LABEL_14,  m_Label8[6]);
	DDX_Control(pDX, IDC_LABEL_15,  m_Label8[7]);
	DDX_Control(pDX, IDC_LABEL_16,  m_Label8[8]);
	DDX_Control(pDX, IDC_LABEL_1,  m_Label8[9]);
	DDX_Control(pDX, IDC_LABEL_18,  m_Label8[10]);
	DDX_Control(pDX, IDC_LABEL_19,  m_Label8[11]);
	DDX_Control(pDX, IDC_LABEL_20,  m_Label8[12]);
	DDX_Control(pDX, IDC_LABEL_21,  m_Label8[13]);
	DDX_Control(pDX, IDC_LABEL_22,  m_Label8[14]);
	DDX_Control(pDX, IDC_LABEL_23,  m_Label8[15]);
	DDX_Control(pDX, IDC_LABEL_24,  m_Label8[16]);
	DDX_Control(pDX, IDC_LABEL_25,  m_Labe25);

	DDX_Control(pDX, IDC_STC_EQUIP_NAME, m_stcEquipName);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_USE_VISION_INSPECT_0 + i, m_rdoUseVisionInspect[i]);
	DDX_Control(pDX, IDC_RDO_USE_MANAGER_MODE_0, m_rdoUseManagerMode[0]);
	DDX_Control(pDX, IDC_RDO_USE_MANAGER_MODE_1, m_rdoUseManagerMode[1]);
	DDX_Control(pDX, IDC_RDO_USE_MES_0, m_rdoUseMES[0]);
	DDX_Control(pDX, IDC_RDO_USE_MES_1, m_rdoUseMES[1]);
	DDX_Control(pDX, IDC_RDO_USE_MES_APD_0, m_rdoUseMesApd[0]);
	DDX_Control(pDX, IDC_RDO_USE_MES_APD_1, m_rdoUseMesApd[1]);
	DDX_Control(pDX, IDC_RDO_USE_BARALARM_0, m_rdoUseBar2Alarm[0]);
	DDX_Control(pDX, IDC_RDO_USE_BARALARM_1, m_rdoUseBar2Alarm[1]);
	DDX_Control(pDX, IDC_RDO_USE_BARNG_0, m_rdoUseBar2NG[0]);
	DDX_Control(pDX, IDC_RDO_USE_BARNG_1, m_rdoUseBar2NG[1]);
	DDX_Control(pDX, IDC_RDO_USE_NGV_0, m_rdoNGVacuum[0]);
	DDX_Control(pDX, IDC_RDO_USE_NGV_1, m_rdoNGVacuum[1]);
	DDX_Control(pDX, IDC_RDO_USE_GDV_0, m_rdoGDVacuum[0]);
	DDX_Control(pDX, IDC_RDO_USE_GDV_1, m_rdoGDVacuum[1]);
	DDX_Control(pDX, IDC_RDO_USE_INLINE_0, m_rdoInlineMode[0]);
	DDX_Control(pDX, IDC_RDO_USE_INLINE_1, m_rdoInlineMode[1]);
	DDX_Control(pDX, IDC_RDO_NG_OUT_DIR_0, m_rdoNgSortMode[0]);
	DDX_Control(pDX, IDC_RDO_NG_OUT_DIR_1, m_rdoNgSortMode[1]);
	DDX_Control(pDX, IDC_RDO_USE_SEPARATION_0, m_rdoSeparationMode[0]);
	DDX_Control(pDX, IDC_RDO_USE_SEPARATION_1, m_rdoSeparationMode[1]);
	DDX_Control(pDX, IDC_CBO_NG_CODE, m_cboNgCode);
	DDX_Control(pDX, IDC_RDO_GD_SORT_DIR_0, m_rdoGDPickSortMode[0]);
	DDX_Control(pDX, IDC_RDO_GD_SORT_DIR_1, m_rdoGDPickSortMode[1]);
	DDX_Control(pDX, IDC_RDO_UNLOAD_SORT_DIR_0, m_rdoUnloadSortMode[0]);
	DDX_Control(pDX, IDC_RDO_UNLOAD_SORT_DIR_1, m_rdoUnloadSortMode[1]);

	DDX_Control(pDX, IDC_STC_DOOR_LOCK_NAME, m_stcDoorLockName);
	DDX_Control(pDX, IDC_STC_DOOR_LOCK_NAME2, m_stcDoorTimeName);
	DDX_Control(pDX, IDC_STC_DOORLOCK_TIME, m_stcDoorLockTime);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_DOOR_LOCK_0 + i, m_rdoDoorLock[i]);
	DDX_Control(pDX, IDC_GRP_TOWER, m_grpTower);
	for (int i = 0; i < 13; i++) DDX_Control(pDX, IDC_LBL_TOWER_0 + i,  m_lblTower[i]);
	for (int j = 0; j < 7; j++) DDX_Control(pDX, IDC_CHK_TOWER_0_0 + j,  m_chkTower[0][j]);
	for (int j = 0; j < 7; j++) DDX_Control(pDX, IDC_CHK_TOWER_1_0 + j,  m_chkTower[1][j]);
	for (int j = 0; j < 7; j++) DDX_Control(pDX, IDC_CHK_TOWER_2_0 + j,  m_chkTower[2][j]);
	for (int j = 0; j < 7; j++) DDX_Control(pDX, IDC_CHK_TOWER_3_0 + j,  m_chkTower[3][j]);
	for (int j = 0; j < 7; j++) DDX_Control(pDX, IDC_CHK_TOWER_4_0 + j,  m_chkTower[4][j]);
	for (int j = 0; j < 7; j++) DDX_Control(pDX, IDC_CHK_TOWER_5_0 + j,  m_chkTower[5][j]);

	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);

	DDX_Control(pDX, IDC_GROUP_PSW, m_GroupPsw);
	DDX_Control(pDX, IDC_STC_FM_ERROR_COUNT, m_stcFmErrorCount);
	DDX_Control(pDX, IDC_BTN_PSW_SAVE, m_btnPswSave);
	DDX_Control(pDX, IDC_BTN_PSW_READ, m_btnPswRead);

	DDX_Control(pDX, IDC_LBL_CAP_0, m_lblCap);
	DDX_Control(pDX, IDC_IPA_CAP_IP, m_ipaCapAttachIp);
	DDX_Control(pDX, IDC_BTN_CAP_CONNECT, m_btnCapConnect);
	DDX_Control(pDX, IDC_BTN_CAP_DISCONNECT, m_btnCapDisconnect);

	DDX_Control(pDX, IDC_STC_EQUIP_NGCOUNT, m_stcNGCount);
	DDX_Control(pDX, IDC_STC_INDEX_DATA_0, m_stcIndexPitch);
	DDX_Control(pDX, IDC_RDO_USE_DRY_0, m_rdoDryRun[0]);
	DDX_Control(pDX, IDC_RDO_USE_DRY_1, m_rdoDryRun[1]);
}

BEGIN_MESSAGE_MAP(CSetupEquipDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_STN_CLICKED(IDC_STC_EQUIP_NAME, &CSetupEquipDlg::OnStnClickedStcEquipName)
	ON_STN_CLICKED(IDC_STC_FM_ERROR_COUNT, &CSetupEquipDlg::OnStnClickedStcFmErrorCount)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSetupEquipDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSetupEquipDlg::OnBnClickedBtnCancel)
	ON_STN_CLICKED(IDC_STC_OPTION_ENABLE, &CSetupEquipDlg::OnStnClickedStcOptionEnable)
	ON_STN_CLICKED(IDC_STC_EQUIP_NGCOUNT, &CSetupEquipDlg::OnStnClickedstcNGCount)
	ON_STN_CLICKED(IDC_STC_INDEX_DATA_0, &CSetupEquipDlg::OnStnClickedstcIndexPitch)
	ON_BN_CLICKED(IDC_BTN_CAP_CONNECT, &CSetupEquipDlg::OnBnClickedBtnCapConnect)
	ON_BN_CLICKED(IDC_BTN_CAP_DISCONNECT, &CSetupEquipDlg::OnBnClickedBtnCapDisconnect)
	ON_STN_CLICKED(IDC_STC_DOORLOCK_TIME, &CSetupEquipDlg::OnStnClickedstcRockTime)

	ON_BN_CLICKED(IDC_BTN_PSW_READ, &CSetupEquipDlg::OnBnClickedBtnPswRead)
	ON_BN_CLICKED(IDC_BTN_PSW_SAVE, &CSetupEquipDlg::OnBnClickedBtnPswSave)
END_MESSAGE_MAP()

// CSetupEquipDlg ∏ﬁΩ√¡ˆ √≥∏Æ±‚¿‘¥œ¥Ÿ.

BOOL CSetupEquipDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ø©±‚ø° √ﬂ∞° √ ±‚»≠ ¿€æ˜¿ª √ﬂ∞°«’¥œ¥Ÿ.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// øπø‹: OCX º”º∫ ∆‰¿Ã¡ˆ¥¬ FALSE∏¶ π›»Ø«ÿæﬂ «’¥œ¥Ÿ.
}

void CSetupEquipDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CSetupEquipDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupEquipDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		m_stcFmErrorCount.SetWindowText("****");

		Display_EquipData();

// 		m_stcDoorLockName.ShowWindow(SW_HIDE);
// 		for (int i = 0; i < 2; i++) m_rdoDoorLock[i].ShowWindow(SW_HIDE);

//		m_GroupPsw.ShowWindow(SW_HIDE);
//		m_stcFmErrorCount.ShowWindow(SW_HIDE);
//		m_btnPswSave.ShowWindow(SW_HIDE);
//		m_btnPswRead.ShowWindow(SW_HIDE);

	}
}

void CSetupEquipDlg::OnStnClickedStcEquipName()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcEquipName.SetWindowText(strKey);
	}
}

void CSetupEquipDlg::OnStnClickedStcFmErrorCount()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	
	if (pCommon->Show_NumPad("", strNew) == IDOK) {
		int nCnt = strNew.GetLength();
		if (nCnt < 1) {
			AfxMessageBox("Password Input Error......");
			return;
		}
		for(int i=0; i<nCnt; i++ ) {
			strOld = strNew.Mid(i,1);
			if (strOld < "0" || strOld > "9") {
				AfxMessageBox("Password Input Error......");
				return;
			}
		}
		m_stcFmErrorCount.SetWindowText(strNew);
	}
}

void CSetupEquipDlg::OnStnClickedstcNGCount()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	
	if (pCommon->Show_NumPad("", strNew) == IDOK) {
		int nCnt = atoi(strNew);
		if (nCnt < 0 || nCnt > 100) {
			AfxMessageBox("NG Percent input Error(0~100)......");
			return;
		}
		m_stcNGCount.SetWindowText(strNew);
	}
}

void CSetupEquipDlg::OnStnClickedstcRockTime()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	
	if (pCommon->Show_NumPad("", strNew) == IDOK) {
		int nCnt = atoi(strNew);
		if (nCnt < 0) {
			AfxMessageBox("Door Lock Time input Error.....");
			return;
		}
		m_stcDoorLockTime.SetWindowText(strNew);
	}
}

void CSetupEquipDlg::OnStnClickedstcIndexPitch()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;

	if (pCommon->Show_NumPad("", strNew) == IDOK) {
		int nCnt = atoi(strNew);
		m_stcIndexPitch.SetWindowText(strNew);
	}
}

void CSetupEquipDlg::OnBnClickedBtnCapConnect()
{
	if (!g_objCapAttachUDP.Initialize()) return;
	CLogFile *pLogFile = CLogFile::Get_Instance();

	m_ipaCapAttachIp.EnableWindow(FALSE);
	pLogFile->Save_CapAttachLog("[Cap Connect] Click");
}

void CSetupEquipDlg::OnBnClickedBtnCapDisconnect()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();

	g_objCapAttachUDP.Terminate();
	m_ipaCapAttachIp.EnableWindow(TRUE);
	pLogFile->Save_CapAttachLog("[Cap Disconnect] Click");
}

void CSetupEquipDlg::OnStnClickedStcOptionEnable()
{
	return;

	if (m_stcDoorLockName.IsWindowVisible()) {
		m_stcDoorLockName.ShowWindow(SW_HIDE);
		for (int i = 0; i < 2; i++) m_rdoDoorLock[i].ShowWindow(SW_HIDE);

		m_GroupPsw.ShowWindow(SW_HIDE);
		m_stcFmErrorCount.ShowWindow(SW_HIDE);
		m_btnPswSave.ShowWindow(SW_HIDE);
		m_btnPswRead.ShowWindow(SW_HIDE);

	} else {

		CCommon *pCommon = CCommon::Get_Instance();
		if (pCommon->Show_Password() == IDOK) {
			m_stcDoorLockName.ShowWindow(SW_SHOW);
			for (int i = 0; i < 2; i++) m_rdoDoorLock[i].ShowWindow(SW_SHOW);

			m_GroupPsw.ShowWindow(SW_SHOW);
			m_stcFmErrorCount.ShowWindow(SW_SHOW);
			m_btnPswSave.ShowWindow(SW_SHOW);
			m_btnPswRead.ShowWindow(SW_SHOW);
		}
	}
}



void CSetupEquipDlg::OnBnClickedBtnSave()
{
	CString strSection, strKey, strData, sData[9];
	CCommon *pCommon = CCommon::Get_Instance();
	pCommon->Backup_File(gsCurrentDir + "\\System", "EquipData");

	CIniFileCS INI("System/EquipData.ini");
	strSection = "OPTION";

	m_stcEquipName.GetWindowText(strData);
	INI.Set_String(strSection, "EQUIP_NAME", strData);

	if (m_rdoUseVisionInspect[0].GetCheck()) { INI.Set_Bool(strSection, "VISION_INSPECT", FALSE); sData[0] = "No"; }
	if (m_rdoUseVisionInspect[1].GetCheck()) { INI.Set_Bool(strSection, "VISION_INSPECT", TRUE); sData[0] = "Use"; }

	if (m_rdoUseManagerMode[0].GetCheck()) { INI.Set_Bool(strSection, "MANAGER_MODE", FALSE); sData[1] = "No"; }
	if (m_rdoUseManagerMode[1].GetCheck()) { INI.Set_Bool(strSection, "MANAGER_MODE", TRUE); sData[1] = "Use"; }

	if (m_rdoUseBar2Alarm[0].GetCheck()) { INI.Set_Bool(strSection, "BARCODE_ALARM", FALSE); sData[2] = "No"; }
	if (m_rdoUseBar2Alarm[1].GetCheck()) { INI.Set_Bool(strSection, "BARCODE_ALARM", TRUE); sData[2] = "Use"; }

	if (m_rdoUseBar2NG[0].GetCheck()) { INI.Set_Bool(strSection, "BARCODE_NG", FALSE); sData[3] = "No"; }
	if (m_rdoUseBar2NG[1].GetCheck()) { INI.Set_Bool(strSection, "BARCODE_NG", TRUE); sData[3] = "Use"; }

	if (m_rdoUseMES[0].GetCheck()) { INI.Set_Bool(strSection, "MES_USE", FALSE); sData[4] = "No"; }
	if (m_rdoUseMES[1].GetCheck()) { INI.Set_Bool(strSection, "MES_USE", TRUE); sData[4] = "Use"; }

	if (m_rdoUseMesApd[0].GetCheck()) { INI.Set_Bool(strSection, "MES_APD", FALSE); sData[8] = "No"; }
	if (m_rdoUseMesApd[1].GetCheck()) { INI.Set_Bool(strSection, "MES_APD", TRUE); sData[8] = "Use"; }

	if (m_rdoNGVacuum[0].GetCheck()) { INI.Set_Bool(strSection, "VACUUM_NG_USE", FALSE); sData[5] = "No"; }
	if (m_rdoNGVacuum[1].GetCheck()) { INI.Set_Bool(strSection, "VACUUM_NG_USE", TRUE); sData[5] = "Use"; }

	if (m_rdoGDVacuum[0].GetCheck()) { INI.Set_Bool(strSection, "VACUUM_GOOD_USE", FALSE); sData[6] = "No"; }
	if (m_rdoGDVacuum[1].GetCheck()) { INI.Set_Bool(strSection, "VACUUM_GOOD_USE", TRUE); sData[6] = "Use"; }

	if (m_rdoInlineMode[0].GetCheck()) { INI.Set_Bool(strSection, "INLINE_MODE_USE", FALSE); }
	if (m_rdoInlineMode[1].GetCheck()) { INI.Set_Bool(strSection, "INLINE_MODE_USE", TRUE); }

	if (m_rdoNgSortMode[0].GetCheck()) { INI.Set_Bool(strSection, "NG_SORT_DIR", TRUE); }
	if (m_rdoNgSortMode[1].GetCheck()) { INI.Set_Bool(strSection, "NG_SORT_DIR", FALSE); }

	if (m_rdoSeparationMode[0].GetCheck()) { INI.Set_Bool(strSection, "SEPARATION_MODE_USE", FALSE); }
	if (m_rdoSeparationMode[1].GetCheck()) { INI.Set_Bool(strSection, "SEPARATION_MODE_USE", TRUE); }

	if (m_rdoGDPickSortMode[0].GetCheck()) { INI.Set_Bool(strSection, "GOOD_PICKER_SORT_DIR", TRUE); }
	if (m_rdoGDPickSortMode[1].GetCheck()) { INI.Set_Bool(strSection, "GOOD_PICKER_SORT_DIR", FALSE); }

	if (m_rdoUnloadSortMode[0].GetCheck()) { INI.Set_Bool(strSection, "UNLOAD_SORT_DIR", TRUE); }
	if (m_rdoUnloadSortMode[1].GetCheck()) { INI.Set_Bool(strSection, "UNLOAD_SORT_DIR", FALSE); }

	if (m_rdoDryRun[0].GetCheck()) { INI.Set_Bool(strSection, "DRY_RUN_USE", FALSE); sData[7] = "No"; }
	if (m_rdoDryRun[1].GetCheck()) { INI.Set_Bool(strSection, "DRY_RUN_USE", TRUE); sData[7] = "Use"; }

	m_stcNGCount.GetWindowText(strData);
	int nNGCount = atoi(strData);
	INI.Set_Integer(strSection, "DRY_NG_COUNT", nNGCount);

	m_stcIndexPitch.GetWindowText(strData);
	double dIndexPitch = atof(strData);
	INI.Set_Double(strSection, "INDEX_PITCH", dIndexPitch);

	m_ipaCapAttachIp.GetWindowText(strData); INI.Set_String("CAPATTACH", "CAP_IP", strData);

	int nData = m_cboNgCode.GetCurSel(); 
	if (nData == 0) INI.Set_Integer(strSection, "SEPARATION_NG_CODE", 7);
	if (nData == 1) INI.Set_Integer(strSection, "SEPARATION_NG_CODE", 8);
	if (nData == 2) INI.Set_Integer(strSection, "SEPARATION_NG_CODE", 11);
	if (nData == 3) INI.Set_Integer(strSection, "SEPARATION_NG_CODE", 12);
	if (nData == 4) INI.Set_Integer(strSection, "SEPARATION_NG_CODE", 13);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			strKey.Format("%d%d", i, j);
			INI.Set_Bool("TOWER", strKey, m_chkTower[i][j].GetCheck());
		}
	}

	if (m_rdoDoorLock[0].GetCheck()) { INI.Set_Bool(strSection, "DOOR_LOCK", FALSE); sData[5] = "No"; }
	if (m_rdoDoorLock[1].GetCheck()) { INI.Set_Bool(strSection, "DOOR_LOCK", TRUE); sData[5] = "Use"; }
	m_stcDoorLockTime.GetWindowText(strData);
	gData.dDoorLockTime = atoi(strData);
	INI.Set_Integer(strSection, "DOOR_LOCK_TIME", gData.dDoorLockTime);

	//strData.Format("[Setup - Equip Dialog] => Vision[%s] Manager[%s] BarAlarm[%s] BarNG[%s] MES[%s] DOOR[%s]", sData[0], sData[1], sData[2], sData[3], sData[4], sData[5]);
	strData.Format("[Setup - Equip Dialog] => Vision[%s] Manager[%s] BarAlarm[%s] BarNG[%s] MES[%s] NGV[%s] GDV[%s] Dry[%s] APD[%s]",
		sData[0], sData[1], sData[2], sData[3], sData[4], sData[5], sData[6], sData[7], sData[8]);
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HistoryLog(strData);

	OnBnClickedBtnCancel();

	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	pMainDlg->Set_MainState(gData.m_nMS);

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	g_objMES.Set_MESUse(pEquipData->bUseMES);
}

void CSetupEquipDlg::OnBnClickedBtnCancel()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	pDataManager->Read_EquipData();
	
	Display_EquipData();
}


///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupEquipDlg::Initial_Controls() 
{
	m_Group[0].Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_Group[1].Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_Group[2].Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_Group[3].Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);

	m_Label0.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x40, 0x80));
	for (int i = 0; i < 17; i++) m_Label8[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x00));
	m_Label8[9].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x80, 0xC0));

	m_stcEquipName.Init_Ctrl("πŸ≈¡", 20, TRUE, RGB(0xFF, 0xFF, 0x80), RGB(0x00, 0x10, 0xC0));
	m_stcFmErrorCount.Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xC0, 0x80));

	for (int i = 0; i < 2; i++) m_rdoUseVisionInspect[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoUseManagerMode[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoUseMES[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoUseMesApd[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoUseBar2Alarm[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoUseBar2NG[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoNGVacuum[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoGDVacuum[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoInlineMode[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoNgSortMode[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoSeparationMode[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoGDPickSortMode[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoUnloadSortMode[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoDryRun[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);

	m_stcDoorLockName.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x00));
	for (int i = 0; i < 2; i++) m_rdoDoorLock[i].Init_Ctrl("πŸ≈¡", 12, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xE0, 0x40), CRadioCS::emRed, 0);
	m_stcDoorTimeName.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x40, 0x80));
	m_stcDoorLockTime.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	m_Labe25.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x40, 0x80));

	m_grpTower.Init_Ctrl("πŸ≈¡", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 13; i++) m_lblTower[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) m_chkTower[i][j].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0x00, 0xF0, 0x00), CRadioCS::emRed, 0);

	m_btnSave.Init_Ctrl("πŸ≈¡", 15, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnCancel.Init_Ctrl("πŸ≈¡", 15, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	m_stcNGCount.Init_Ctrl("πŸ≈¡", 15, TRUE, RGB(0xFF, 0xFF, 0x80), RGB(0x00, 0x10, 0xC0));
	m_stcIndexPitch.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));

	m_lblCap.Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60)); // ROS Data
	m_btnCapConnect.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_btnCapDisconnect.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);

	CString strText;
	strText.Format("07 : Barrel/Lens"); m_cboNgCode.AddString(strText);
	strText.Format("08 : Side Fill"); m_cboNgCode.AddString(strText);
	strText.Format("11 : Stiffener √¯¡§"); m_cboNgCode.AddString(strText);
	strText.Format("12 : Lens ø¯¿⁄¿Á"); m_cboNgCode.AddString(strText);
	strText.Format("13 : Lens Fiducial"); m_cboNgCode.AddString(strText);
	m_cboNgCode.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xE0, 0x00));

}

void CSetupEquipDlg::Display_EquipData()
{
	CString strData;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	m_stcEquipName.SetWindowText(pEquipData->sEquipName);

	if (pEquipData->bUseVisionInspect) m_rdoUseVisionInspect[1].SetCheck(TRUE);
	else m_rdoUseVisionInspect[0].SetCheck(TRUE);

	if (pEquipData->bUseManagerMode) m_rdoUseManagerMode[1].SetCheck(TRUE);
	else m_rdoUseManagerMode[0].SetCheck(TRUE);

	if (pEquipData->bUseBar2Alarm) m_rdoUseBar2Alarm[1].SetCheck(TRUE);
	else m_rdoUseBar2Alarm[0].SetCheck(TRUE);

	if (pEquipData->bUseBar2NG) m_rdoUseBar2NG[1].SetCheck(TRUE);
	else m_rdoUseBar2NG[0].SetCheck(TRUE);

	if (pEquipData->bUseMES) m_rdoUseMES[1].SetCheck(TRUE);
	else m_rdoUseMES[0].SetCheck(TRUE);

	if (pEquipData->bUseMesApd) m_rdoUseMesApd[1].SetCheck(TRUE);
	else m_rdoUseMesApd[0].SetCheck(TRUE);

	if (gData.bUseNGVacuum) m_rdoNGVacuum[1].SetCheck(TRUE);
	else m_rdoNGVacuum[0].SetCheck(TRUE);

	if (gData.bUseGDVacuum) m_rdoGDVacuum[1].SetCheck(TRUE);
	else m_rdoGDVacuum[0].SetCheck(TRUE);

	if (pEquipData->bUseInlineMode) m_rdoInlineMode[1].SetCheck(TRUE);
	else m_rdoInlineMode[0].SetCheck(TRUE);

	if (gData.bNgSortFront) m_rdoNgSortMode[0].SetCheck(TRUE);
	else m_rdoNgSortMode[1].SetCheck(TRUE);

	if (gData.bUseSeparationMode) m_rdoSeparationMode[1].SetCheck(TRUE);
	else m_rdoSeparationMode[0].SetCheck(TRUE);

	if (gData.bGDPickerSort1) m_rdoGDPickSortMode[0].SetCheck(TRUE);
	else m_rdoGDPickSortMode[1].SetCheck(TRUE);

	if (gData.bUnloadSortFront) m_rdoUnloadSortMode[0].SetCheck(TRUE);
	else m_rdoUnloadSortMode[1].SetCheck(TRUE);

	if (gData.bUseDryRun) m_rdoDryRun[1].SetCheck(TRUE);
	else m_rdoDryRun[0].SetCheck(TRUE);

	strData.Format("%d", gData.nNGPercent);
	m_stcNGCount.SetWindowText(strData);

	strData.Format("%.3f", gData.dIndexPitch);
	m_stcIndexPitch.SetWindowText(strData);

	m_ipaCapAttachIp.EnableWindow(!g_objCapAttachUDP.Is_Opened());
	m_ipaCapAttachIp.SetWindowText(pEquipData->sCapAttachIp);

	if (gData.nSeparationNgCode ==  7) m_cboNgCode.SetCurSel(0);
	if (gData.nSeparationNgCode ==  8) m_cboNgCode.SetCurSel(1);
	if (gData.nSeparationNgCode == 11) m_cboNgCode.SetCurSel(2);
	if (gData.nSeparationNgCode == 12) m_cboNgCode.SetCurSel(3);
	if (gData.nSeparationNgCode == 13) m_cboNgCode.SetCurSel(4);

	for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) m_chkTower[i][j].SetCheck(pEquipData->bTower[i][j]);

	if (pEquipData->bUseDoorLock) m_rdoDoorLock[1].Check_Radio(IDC_RDO_DOOR_LOCK_0, IDC_RDO_DOOR_LOCK_1);
	else m_rdoDoorLock[0].Check_Radio(IDC_RDO_DOOR_LOCK_0, IDC_RDO_DOOR_LOCK_1);
	strData.Format("%d", gData.dDoorLockTime);
	m_stcDoorLockTime.SetWindowText(strData);
}

///////////////////////////////////////////////////////////////////////////////


void CSetupEquipDlg::OnBnClickedBtnPswRead()
{
	CString strPassword;

	CIniFileCS INI("System/USER_PSW.ini");
	if (!INI.Check_File()) {
		m_stcFmErrorCount.SetWindowText("****");
		return;
	}
	strPassword = INI.Get_String("PASSWORD", "PSW", "");
	m_stcFmErrorCount.SetWindowText(strPassword);
}


void CSetupEquipDlg::OnBnClickedBtnPswSave()
{
	CString strPassword, strOld;

	m_stcFmErrorCount.GetWindowText(strPassword);
	int nCnt = strPassword.GetLength();
	if (nCnt < 1) {
		AfxMessageBox("Password Input Error......");
		return;
	}
	for(int i=0; i<nCnt; i++ ) {
		strOld = strPassword.Mid(i,1);
		if (strOld < "0" || strOld > "9") {
			AfxMessageBox("Password Input Error......");
			return;
		}
	}

	CIniFileCS INI("System/USER_PSW.ini");
	INI.Set_String("PASSWORD", "PSW", strPassword);

}
