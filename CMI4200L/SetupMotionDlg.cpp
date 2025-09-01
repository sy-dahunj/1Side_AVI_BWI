// SetupMotionDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupMotionDlg.h"
#include "afxdialogex.h"

// CSetupMotionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMotionDlg, CDialogEx)

CSetupMotionDlg::CSetupMotionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMotionDlg::IDD, pParent)
{
}

CSetupMotionDlg::~CSetupMotionDlg()
{
}

void CSetupMotionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETUP_MOTION, m_tabSetupMotion);
}

BEGIN_MESSAGE_MAP(CSetupMotionDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_SETUP_MOTION, &CSetupMotionDlg::OnTcnSelchangingTabSetupMotion)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SETUP_MOTION, &CSetupMotionDlg::OnTcnSelchangeTabSetupMotion)
END_MESSAGE_MAP()

// CSetupMotionDlg 메시지 처리기입니다.

BOOL CSetupMotionDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_pSetupMotionTabDlg = new CSetupMotionTabDlg(&m_tabSetupMotion);
	m_pSetupMotionTabDlg->Create(IDD_SETUP_MOTION_TAB_DLG, &m_tabSetupMotion);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetupMotionDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	m_pSetupMotionTabDlg->DestroyWindow();
	if (m_pSetupMotionTabDlg) delete m_pSetupMotionTabDlg;
	m_pSetupMotionTabDlg = NULL;
}

BOOL CSetupMotionDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMotionDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		int nTab = m_tabSetupMotion.GetCurSel();
		m_pSetupMotionTabDlg->Set_MotionTab(nTab);

		int nIdx = nTab * 4;	// Start Axis Index
		//int nIdx = (nTab == 7 ? 25 : (nTab == 8 ? 29 : nTab * 4));	    // Start Axis Index.. kty
		m_pSetupMotionTabDlg->Set_MotionIdx(nIdx);

		m_pSetupMotionTabDlg->ShowWindow(SW_SHOW);
	} else {
		m_pSetupMotionTabDlg->ShowWindow(SW_HIDE);
	}
}

void CSetupMotionDlg::OnTcnSelchangingTabSetupMotion(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_pSetupMotionTabDlg->ShowWindow(SW_HIDE);
	*pResult = 0;
}

void CSetupMotionDlg::OnTcnSelchangeTabSetupMotion(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_tabSetupMotion.GetCurSel();
	m_pSetupMotionTabDlg->Set_MotionTab(nTab);

	int nIdx = nTab * 4;	// Start Axis Index
	//int nIdx = (nTab == 7 ? 25 : (nTab == 8 ? 29 : nTab * 4));	    // Start Axis Index ... kty
	m_pSetupMotionTabDlg->Set_MotionIdx(nIdx);

	m_pSetupMotionTabDlg->ShowWindow(SW_SHOW);
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMotionDlg::Initial_Controls() 
{
	m_tabSetupMotion.InsertItem(0, "Axis (08-11)");
	m_tabSetupMotion.InsertItem(1, "Axis (12-15)");
	m_tabSetupMotion.InsertItem(2, "Axis (16-19)");
	m_tabSetupMotion.InsertItem(3, "Axis (20-23)");
	m_tabSetupMotion.InsertItem(4, "Axis (24-27)");
	m_tabSetupMotion.InsertItem(5, "Axis (28-30)");

	m_tabSetupMotion.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);

//	m_tabSetupMotion.SetMinTabWidth(155);
	m_tabSetupMotion.SetItemSize(CSize(155, 50));
}

void CSetupMotionDlg::Display_Status()
{
	m_pSetupMotionTabDlg->Display_Status();
}

///////////////////////////////////////////////////////////////////////////////
