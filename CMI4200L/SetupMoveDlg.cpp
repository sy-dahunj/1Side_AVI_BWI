// SetupMoveDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupMoveDlg.h"
#include "afxdialogex.h"

// CSetupMoveDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSetupMoveDlg, CDialogEx)

CSetupMoveDlg::CSetupMoveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveDlg::IDD, pParent)
{
}

CSetupMoveDlg::~CSetupMoveDlg()
{
}

void CSetupMoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETUP_MOVE, m_tabSetupMove);
}

BEGIN_MESSAGE_MAP(CSetupMoveDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_SETUP_MOVE, &CSetupMoveDlg::OnTcnSelchangingTabSetupMove)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SETUP_MOVE, &CSetupMoveDlg::OnTcnSelchangeTabSetupMove)
END_MESSAGE_MAP()

// CSetupMoveDlg �޽��� ó�����Դϴ�.

BOOL CSetupMoveDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_pSetupMoveTab1Dlg = new CSetupMoveTab1Dlg(&m_tabSetupMove);
	m_pSetupMoveTab1Dlg->Create(IDD_SETUP_MOVE_TAB1_DLG, &m_tabSetupMove);

	m_pSetupMoveTab2Dlg = new CSetupMoveTab2Dlg(&m_tabSetupMove);
	m_pSetupMoveTab2Dlg->Create(IDD_SETUP_MOVE_TAB2_DLG, &m_tabSetupMove);

	m_pSetupMoveTab3Dlg = new CSetupMoveTab3Dlg(&m_tabSetupMove);
	m_pSetupMoveTab3Dlg->Create(IDD_SETUP_MOVE_TAB3_DLG, &m_tabSetupMove);

	m_pSetupMoveTab4Dlg = new CSetupMoveTab4Dlg(&m_tabSetupMove);
	m_pSetupMoveTab4Dlg->Create(IDD_SETUP_MOVE_TAB4_DLG, &m_tabSetupMove);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSetupMoveDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	m_pSetupMoveTab4Dlg->DestroyWindow();
	m_pSetupMoveTab3Dlg->DestroyWindow();
	m_pSetupMoveTab2Dlg->DestroyWindow();
	m_pSetupMoveTab1Dlg->DestroyWindow();

	if (m_pSetupMoveTab4Dlg) delete m_pSetupMoveTab4Dlg;
	if (m_pSetupMoveTab3Dlg) delete m_pSetupMoveTab3Dlg;
	if (m_pSetupMoveTab2Dlg) delete m_pSetupMoveTab2Dlg;
	if (m_pSetupMoveTab1Dlg) delete m_pSetupMoveTab1Dlg;

	m_pSetupMoveTab4Dlg = NULL;
	m_pSetupMoveTab3Dlg = NULL;
	m_pSetupMoveTab2Dlg = NULL;
	m_pSetupMoveTab1Dlg = NULL;
}

BOOL CSetupMoveDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	int nTab = m_tabSetupMove.GetCurSel();
	if (bShow) {
		if (nTab == 0) m_pSetupMoveTab1Dlg->ShowWindow(SW_SHOW);
		if (nTab == 1) m_pSetupMoveTab2Dlg->ShowWindow(SW_SHOW);
		if (nTab == 2) m_pSetupMoveTab3Dlg->ShowWindow(SW_SHOW);
		if (nTab == 3) m_pSetupMoveTab4Dlg->ShowWindow(SW_SHOW);
	} else {
		if (nTab == 0) m_pSetupMoveTab1Dlg->ShowWindow(SW_HIDE);
		if (nTab == 1) m_pSetupMoveTab2Dlg->ShowWindow(SW_HIDE);
		if (nTab == 2) m_pSetupMoveTab3Dlg->ShowWindow(SW_HIDE);
		if (nTab == 3) m_pSetupMoveTab4Dlg->ShowWindow(SW_HIDE);
	}
}

void CSetupMoveDlg::OnTcnSelchangingTabSetupMove(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_tabSetupMove.GetCurSel();
	if (nTab == 0) m_pSetupMoveTab1Dlg->ShowWindow(SW_HIDE);
	if (nTab == 1) m_pSetupMoveTab2Dlg->ShowWindow(SW_HIDE);
	if (nTab == 2) m_pSetupMoveTab3Dlg->ShowWindow(SW_HIDE);
	if (nTab == 3) m_pSetupMoveTab4Dlg->ShowWindow(SW_HIDE);
	*pResult = 0;
}

void CSetupMoveDlg::OnTcnSelchangeTabSetupMove(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_tabSetupMove.GetCurSel();
	if (nTab == 0) m_pSetupMoveTab1Dlg->ShowWindow(SW_SHOW);
	if (nTab == 1) m_pSetupMoveTab2Dlg->ShowWindow(SW_SHOW);
	if (nTab == 2) m_pSetupMoveTab3Dlg->ShowWindow(SW_SHOW);
	if (nTab == 3) m_pSetupMoveTab4Dlg->ShowWindow(SW_SHOW);
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveDlg::Initial_Controls() 
{
	m_tabSetupMove.InsertItem(0, "Load / Tray-Picker");
	m_tabSetupMove.InsertItem(1, "Index / Inspection");
	m_tabSetupMove.InsertItem(2, "NG / Good Picker");
	m_tabSetupMove.InsertItem(3, "Unload / Tray-Picker");

	m_tabSetupMove.Init_Ctrl("����", 14, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);

//	m_tabSetupMove.SetMinTabWidth(270);
	m_tabSetupMove.SetItemSize(CSize(270, 50));
}

///////////////////////////////////////////////////////////////////////////////
