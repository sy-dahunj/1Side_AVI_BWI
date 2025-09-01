// SetupInOutDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupInOutDlg.h"
#include "afxdialogex.h"

// CSetupInOutDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSetupInOutDlg, CDialogEx)

CSetupInOutDlg::CSetupInOutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupInOutDlg::IDD, pParent)
{
}

CSetupInOutDlg::~CSetupInOutDlg()
{
}

void CSetupInOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETUP_IN_OUT, m_tabSetupInOut);
}

BEGIN_MESSAGE_MAP(CSetupInOutDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_SETUP_IN_OUT, &CSetupInOutDlg::OnTcnSelchangingTabSetupInOut)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SETUP_IN_OUT, &CSetupInOutDlg::OnTcnSelchangeTabSetupInOut)
END_MESSAGE_MAP()

// CSetupInOutDlg �޽��� ó�����Դϴ�.

BOOL CSetupInOutDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_pSetupInOutTabDlg = new CSetupInOutTabDlg(&m_tabSetupInOut);
	m_pSetupInOutTabDlg->Create(IDD_SETUP_IN_OUT_TAB_DLG, &m_tabSetupInOut);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSetupInOutDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	m_pSetupInOutTabDlg->DestroyWindow();
	if (m_pSetupInOutTabDlg) delete m_pSetupInOutTabDlg;
	m_pSetupInOutTabDlg = NULL;
}

BOOL CSetupInOutDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupInOutDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		int nTab = m_tabSetupInOut.GetCurSel();
		m_pSetupInOutTabDlg->Set_InOutTab(nTab);
		m_pSetupInOutTabDlg->ShowWindow(SW_SHOW);
	} else {
		m_pSetupInOutTabDlg->ShowWindow(SW_HIDE);
	}
}

void CSetupInOutDlg::OnTcnSelchangingTabSetupInOut(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_pSetupInOutTabDlg->ShowWindow(SW_HIDE);
	*pResult = 0;
}

void CSetupInOutDlg::OnTcnSelchangeTabSetupInOut(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_tabSetupInOut.GetCurSel();
	m_pSetupInOutTabDlg->Set_InOutTab(nTab);
	m_pSetupInOutTabDlg->ShowWindow(SW_SHOW);
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupInOutDlg::Initial_Controls() 
{
	m_tabSetupInOut.InsertItem(0, "In/Out (000 - 031)");
	m_tabSetupInOut.InsertItem(1, "In/Out (100 - 131)");
	m_tabSetupInOut.InsertItem(2, "In/Out (200 - 231)");
	m_tabSetupInOut.InsertItem(3, "In/Out (300 - 331)");
	m_tabSetupInOut.InsertItem(4, "In/Out (400 - 431)");
	m_tabSetupInOut.InsertItem(5, "In/Out (500 - 531)");
	m_tabSetupInOut.InsertItem(6, "In/Out (600 - 631)");

	m_tabSetupInOut.Init_Ctrl("����", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);

//	m_tabSetupInOut.SetMinTabWidth(270);
	m_tabSetupInOut.SetItemSize(CSize(270, 50));
}

void CSetupInOutDlg::Display_Status()
{
	m_pSetupInOutTabDlg->Display_Status();
}

///////////////////////////////////////////////////////////////////////////////
