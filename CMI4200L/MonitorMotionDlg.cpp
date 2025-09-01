// MonitorMotionDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "MonitorMotionDlg.h"
#include "afxdialogex.h"

// CMonitorMotionDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMonitorMotionDlg, CDialogEx)

CMonitorMotionDlg::CMonitorMotionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonitorMotionDlg::IDD, pParent)
{
}

CMonitorMotionDlg::~CMonitorMotionDlg()
{
}

void CMonitorMotionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MONITOR_MOTION, m_tabMonitorMotion);
}

BEGIN_MESSAGE_MAP(CMonitorMotionDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_MONITOR_MOTION, &CMonitorMotionDlg::OnTcnSelchangingTabMonitorMotion)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MONITOR_MOTION, &CMonitorMotionDlg::OnTcnSelchangeTabMonitorMotion)
END_MESSAGE_MAP()

// CMonitorMotionDlg �޽��� ó�����Դϴ�.

BOOL CMonitorMotionDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// 	SetWindowPos(this, 120, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	SetWindowPos(this, 0, 70, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_pMonitorMotionTabDlg = new CMonitorMotionTabDlg(&m_tabMonitorMotion);
	m_pMonitorMotionTabDlg->Create(IDD_MONITOR_MOTION_TAB_DLG, &m_tabMonitorMotion);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMonitorMotionDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	m_pMonitorMotionTabDlg->DestroyWindow();
	if (m_pMonitorMotionTabDlg) delete m_pMonitorMotionTabDlg;
	m_pMonitorMotionTabDlg = NULL;
}

BOOL CMonitorMotionDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMonitorMotionDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		int nTab = m_tabMonitorMotion.GetCurSel();
		m_pMonitorMotionTabDlg->Set_MotionTab(nTab);
		m_pMonitorMotionTabDlg->ShowWindow(SW_SHOW);
	} else {
		m_pMonitorMotionTabDlg->ShowWindow(SW_HIDE);
	}
}

void CMonitorMotionDlg::OnTcnSelchangingTabMonitorMotion(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_pMonitorMotionTabDlg->ShowWindow(SW_HIDE);
	*pResult = 0;
}

void CMonitorMotionDlg::OnTcnSelchangeTabMonitorMotion(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_tabMonitorMotion.GetCurSel();
	m_pMonitorMotionTabDlg->Set_MotionTab(nTab);
	m_pMonitorMotionTabDlg->ShowWindow(SW_SHOW);
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CMonitorMotionDlg::Initial_Controls() 
{
	m_tabMonitorMotion.InsertItem(0, "Motion Axis (08-15)");
	m_tabMonitorMotion.InsertItem(1, "Motion Axis (16-23)");
	m_tabMonitorMotion.InsertItem(2, "Motion Axis (24-30)");

//	m_tabMonitorMotion.SetMinTabWidth(373);
	m_tabMonitorMotion.SetItemSize(CSize(373, 50));

	m_tabMonitorMotion.Init_Ctrl("����", 14, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);	
}

void CMonitorMotionDlg::Display_Status()
{
	m_pMonitorMotionTabDlg->Display_Status();
}

///////////////////////////////////////////////////////////////////////////////
