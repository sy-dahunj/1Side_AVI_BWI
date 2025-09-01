// MonitorInOutDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "MonitorInOutDlg.h"
#include "afxdialogex.h"

// CMonitorInOutDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMonitorInOutDlg, CDialogEx)

CMonitorInOutDlg::CMonitorInOutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonitorInOutDlg::IDD, pParent)
{
}

CMonitorInOutDlg::~CMonitorInOutDlg()
{
}

void CMonitorInOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MONITOR_IN_OUT, m_tabMonitorInOut);
}

BEGIN_MESSAGE_MAP(CMonitorInOutDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_MONITOR_IN_OUT, &CMonitorInOutDlg::OnTcnSelchangingTabMonitorInOut)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MONITOR_IN_OUT, &CMonitorInOutDlg::OnTcnSelchangeTabMonitorInOut)
END_MESSAGE_MAP()

// CMonitorInOutDlg �޽��� ó�����Դϴ�.

BOOL CMonitorInOutDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// 	SetWindowPos(this, 120, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	SetWindowPos(this, 0, 70, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_pMonitorInOutTabDlg = new CMonitorInOutTabDlg(&m_tabMonitorInOut);
	m_pMonitorInOutTabDlg->Create(IDD_MONITOR_IN_OUT_TAB_DLG, &m_tabMonitorInOut);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMonitorInOutDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	m_pMonitorInOutTabDlg->DestroyWindow();
	if (m_pMonitorInOutTabDlg) delete m_pMonitorInOutTabDlg;
	m_pMonitorInOutTabDlg = NULL;
}

BOOL CMonitorInOutDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMonitorInOutDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		int nTab = m_tabMonitorInOut.GetCurSel();
		m_pMonitorInOutTabDlg->Set_InOutTab(nTab);
		m_pMonitorInOutTabDlg->ShowWindow(SW_SHOW);
	} else {
		m_pMonitorInOutTabDlg->ShowWindow(SW_HIDE);
	}
}

void CMonitorInOutDlg::OnTcnSelchangingTabMonitorInOut(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_pMonitorInOutTabDlg->ShowWindow(SW_HIDE);
	*pResult = 0;
}

void CMonitorInOutDlg::OnTcnSelchangeTabMonitorInOut(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_tabMonitorInOut.GetCurSel();
	m_pMonitorInOutTabDlg->Set_InOutTab(nTab);
	m_pMonitorInOutTabDlg->ShowWindow(SW_SHOW);
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CMonitorInOutDlg::Initial_Controls() 
{
	m_tabMonitorInOut.InsertItem(0, "In/Out (000 - 031)");
	m_tabMonitorInOut.InsertItem(1, "In/Out (100 - 131)");
	m_tabMonitorInOut.InsertItem(2, "In/Out (200 - 231)");
	m_tabMonitorInOut.InsertItem(3, "In/Out (300 - 331)");
	m_tabMonitorInOut.InsertItem(4, "In/Out (400 - 431)");
	m_tabMonitorInOut.InsertItem(5, "In/Out (500 - 531)");
	m_tabMonitorInOut.InsertItem(6, "In/Out (600 - 631)");

	m_tabMonitorInOut.Init_Ctrl("����", 14, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);

//	m_tabMonitorInOut.SetMinTabWidth(280);
	m_tabMonitorInOut.SetItemSize(CSize(280, 50));
}

void CMonitorInOutDlg::Display_Status()
{
	m_pMonitorInOutTabDlg->Display_Status();
}

///////////////////////////////////////////////////////////////////////////////
