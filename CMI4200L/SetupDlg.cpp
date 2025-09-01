// SetupDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupDlg.h"
#include "afxdialogex.h"

#include "CMI4200LDlg.h"

#include "Common.h"
#include "LogFile.h"

// CSetupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupDlg, CDialogEx)

CSetupDlg *CSetupDlg::m_pInstance = NULL;

CSetupDlg *CSetupDlg::Get_Instance(CWnd *pParent)
{
	if (!m_pInstance) {
		m_pInstance = new CSetupDlg(pParent);
		if (!m_pInstance->m_hWnd) {
			m_pInstance->Create(IDD_SETUP_DLG, pParent);
		}
	}
	return m_pInstance;
}

void CSetupDlg::Delete_Instance()
{
	if (m_pInstance->m_hWnd) m_pInstance->DestroyWindow();
	if (m_pInstance) delete m_pInstance;
	m_pInstance = NULL;
}

CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupDlg::IDD, pParent)
{
}

CSetupDlg::~CSetupDlg()
{
}

void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_SETUP_BACK, m_picSetupBack);
	DDX_Control(pDX, IDC_RDO_SETUP_EQUIP, m_rdoSetupEquip);
	DDX_Control(pDX, IDC_RDO_SETUP_MODEL, m_rdoSetupModel);
	DDX_Control(pDX, IDC_RDO_SETUP_MOVE, m_rdoSetupMove);
	DDX_Control(pDX, IDC_RDO_SETUP_MOTION, m_rdoSetupMotion);
	DDX_Control(pDX, IDC_RDO_SETUP_IN_OUT, m_rdoSetupInOut);
	DDX_Control(pDX, IDC_RDO_SETUP_DOOR_LOCK, m_rdoSetupDoorLock);
	DDX_Control(pDX, IDC_RDO_SETUP_DOOR_UNLOCK, m_rdoSetupDoorUnlock);
}

BEGIN_MESSAGE_MAP(CSetupDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RDO_SETUP_EQUIP, &CSetupDlg::OnBnClickedRdoSetupEquip)
	ON_BN_CLICKED(IDC_RDO_SETUP_MODEL, &CSetupDlg::OnBnClickedRdoSetupModel)
	ON_BN_CLICKED(IDC_RDO_SETUP_MOVE, &CSetupDlg::OnBnClickedRdoSetupMove)
	ON_BN_CLICKED(IDC_RDO_SETUP_MOTION, &CSetupDlg::OnBnClickedRdoSetupMotion)
	ON_BN_CLICKED(IDC_RDO_SETUP_IN_OUT, &CSetupDlg::OnBnClickedRdoSetupInOut)
	ON_BN_CLICKED(IDC_RDO_SETUP_DOOR_LOCK, &CSetupDlg::OnBnClickedRdoSetupDoorLock)
	ON_BN_CLICKED(IDC_RDO_SETUP_DOOR_UNLOCK, &CSetupDlg::OnBnClickedRdoSetupDoorUnlock)
END_MESSAGE_MAP()

// CSetupDlg 메시지 처리기입니다.

BOOL CSetupDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_pSetupEquipDlg = new CSetupEquipDlg(this);
	m_pSetupEquipDlg->Create(IDD_SETUP_EQUIP_DLG, this);

	m_pSetupModelDlg = new CSetupModelDlg(this);
	m_pSetupModelDlg->Create(IDD_SETUP_MODEL_DLG, this);

	m_pSetupMoveDlg = new CSetupMoveDlg(this);
	m_pSetupMoveDlg->Create(IDD_SETUP_MOVE_DLG, this);

	m_pSetupMotionDlg = new CSetupMotionDlg(this);
	m_pSetupMotionDlg->Create(IDD_SETUP_MOTION_DLG, this);

	m_pSetupInOutDlg = new CSetupInOutDlg(this);
	m_pSetupInOutDlg->Create(IDD_SETUP_IN_OUT_DLG, this);

	m_rdoSetupEquip.SetCheck(TRUE);
	m_rdoSetupEquip.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetupDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	m_pSetupInOutDlg->DestroyWindow();
	m_pSetupMotionDlg->DestroyWindow();
	m_pSetupMoveDlg->DestroyWindow();
	m_pSetupModelDlg->DestroyWindow();
	m_pSetupEquipDlg->DestroyWindow();

	if (m_pSetupInOutDlg) delete m_pSetupInOutDlg;
	if (m_pSetupMotionDlg) delete m_pSetupMotionDlg;
	if (m_pSetupMoveDlg) delete m_pSetupMoveDlg;
	if (m_pSetupModelDlg) delete m_pSetupModelDlg;
	if (m_pSetupEquipDlg) delete m_pSetupEquipDlg;

	m_pSetupInOutDlg = NULL;
	m_pSetupMotionDlg = NULL;
	m_pSetupMoveDlg = NULL;
	m_pSetupModelDlg = NULL;
	m_pSetupEquipDlg = NULL;
}

BOOL CSetupDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		if (m_rdoSetupEquip.GetCheck()) m_pSetupEquipDlg->ShowWindow(SW_SHOW);
		if (m_rdoSetupModel.GetCheck()) m_pSetupModelDlg->ShowWindow(SW_SHOW);
		if (m_rdoSetupMove.GetCheck()) m_pSetupMoveDlg->ShowWindow(SW_SHOW);
		if (m_rdoSetupMotion.GetCheck()) m_pSetupMotionDlg->ShowWindow(SW_SHOW);
		if (m_rdoSetupInOut.GetCheck()) m_pSetupInOutDlg->ShowWindow(SW_SHOW);

//		m_rdoSetupDoorLock.SetCheck(TRUE);
//		m_rdoSetupDoorUnlock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
//		m_rdoSetupDoorLock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);

		SetTimer(0, 100, NULL);

	} else {
		KillTimer(0);

//		m_rdoSetupDoorUnlock.SetCheck(TRUE);
//		m_rdoSetupDoorLock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
//		m_rdoSetupDoorUnlock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);

		if (m_rdoSetupEquip.GetCheck()) m_pSetupEquipDlg->ShowWindow(SW_HIDE);
		if (m_rdoSetupModel.GetCheck()) m_pSetupModelDlg->ShowWindow(SW_HIDE);
		if (m_rdoSetupMove.GetCheck()) m_pSetupMoveDlg->ShowWindow(SW_HIDE);
		if (m_rdoSetupMotion.GetCheck()) m_pSetupMotionDlg->ShowWindow(SW_HIDE);
		if (m_rdoSetupInOut.GetCheck()) m_pSetupInOutDlg->ShowWindow(SW_HIDE);
	}
}

void CSetupDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(0);

	CCommon *pCommon = CCommon::Get_Instance();
	if (!gData.m_bErrorShow) {
		pCommon->Check_MainEmgAir();	// Emg & Main Air
	}

	if (m_pSetupMotionDlg->IsWindowVisible()) m_pSetupMotionDlg->Display_Status();
	if (m_pSetupInOutDlg->IsWindowVisible()) m_pSetupInOutDlg->Display_Status();

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CSetupDlg::OnBnClickedRdoSetupEquip()
{
	if (m_pSetupEquipDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Setup - Equip] Start");
	m_rdoSetupEquip.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pSetupEquipDlg->ShowWindow(SW_SHOW);
}

void CSetupDlg::OnBnClickedRdoSetupModel()
{
	if (m_pSetupModelDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Setup - Model] Start");
	m_rdoSetupModel.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pSetupModelDlg->ShowWindow(SW_SHOW);
}

void CSetupDlg::OnBnClickedRdoSetupMove()
{
	if (m_pSetupMoveDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Setup - Move] Start");
	m_rdoSetupMove.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pSetupMoveDlg->ShowWindow(SW_SHOW);
}

void CSetupDlg::OnBnClickedRdoSetupMotion()
{
	if (m_pSetupMotionDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Setup - Motion] Start");
	m_rdoSetupMotion.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pSetupMotionDlg->ShowWindow(SW_SHOW);
}

void CSetupDlg::OnBnClickedRdoSetupInOut()
{
	if (m_pSetupInOutDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Setup - InOut] Start");
	m_rdoSetupInOut.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pSetupInOutDlg->ShowWindow(SW_SHOW);
}

void CSetupDlg::OnBnClickedRdoSetupDoorLock()
{
/*
	if (m_rdoSetupDoorLock.GetCheck()) {
		CLogFile *pLogFile = CLogFile::Get_Instance();
		pLogFile->Save_HandlerLog("[Setup] Door Lock button push");
		m_rdoSetupDoorUnlock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
		m_rdoSetupDoorLock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	}
	*/
}

void CSetupDlg::OnBnClickedRdoSetupDoorUnlock()
{
/*
	if (m_rdoSetupDoorUnlock.GetCheck()) {
		CLogFile *pLogFile = CLogFile::Get_Instance();
		pLogFile->Save_HandlerLog("[Setup] Door Unlock button push");
		m_rdoSetupDoorLock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
		m_rdoSetupDoorUnlock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	}
*/
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupDlg::Initial_Controls() 
{
	m_picSetupBack.Init_Ctrl(RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xE0, 0xF0));
	m_rdoSetupEquip.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoSetupModel.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoSetupMove.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoSetupMotion.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_MOTION, CRadioCS::emLeft);
	m_rdoSetupInOut.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_IN_OUT, CRadioCS::emLeft);
//	m_rdoSetupDoorLock.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
//	m_rdoSetupDoorUnlock.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
}

void CSetupDlg::Hide_Windows()
{
	m_pSetupEquipDlg->ShowWindow(SW_HIDE);
	m_pSetupModelDlg->ShowWindow(SW_HIDE);
	m_pSetupMoveDlg->ShowWindow(SW_HIDE);
	m_pSetupMotionDlg->ShowWindow(SW_HIDE);
	m_pSetupInOutDlg->ShowWindow(SW_HIDE);

	m_rdoSetupEquip.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoSetupModel.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoSetupMove.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoSetupMotion.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoSetupInOut.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
}

void CSetupDlg::MainDoor_Lock()
{
//	CLogFile *pLogFile = CLogFile::Get_Instance();
//	pLogFile->Save_HandlerLog("[Setup] Door Lock cmd exec");
//	m_rdoSetupDoorLock.SetCheck(TRUE);
//	m_rdoSetupDoorUnlock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
//	m_rdoSetupDoorLock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
}

void CSetupDlg::MainDoor_Unlock()
{
//	CLogFile *pLogFile = CLogFile::Get_Instance();
//	pLogFile->Save_HandlerLog("[Manual] Door Unlock cmd exec");
//	m_rdoSetupDoorUnlock.SetCheck(TRUE);
//	m_rdoSetupDoorLock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
//	m_rdoSetupDoorUnlock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
}

///////////////////////////////////////////////////////////////////////////////
