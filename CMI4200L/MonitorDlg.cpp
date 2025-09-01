// MonitorDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "MonitorDlg.h"
#include "afxdialogex.h"

// CMonitorDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMonitorDlg, CDialogEx)

CMonitorDlg *CMonitorDlg::m_pInstance = NULL;

CMonitorDlg *CMonitorDlg::Get_Instance(CWnd *pParent)
{
	if (!m_pInstance) {
		m_pInstance = new CMonitorDlg(pParent);
		if (!m_pInstance->m_hWnd) {
			m_pInstance->Create(IDD_MONITOR_DLG, pParent);
		}
	}
	return m_pInstance;
}

void CMonitorDlg::Delete_Instance()
{
	if (m_pInstance->m_hWnd) m_pInstance->DestroyWindow();
	if (m_pInstance) delete m_pInstance;
	m_pInstance = NULL;
}

CMonitorDlg::CMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonitorDlg::IDD, pParent)
{
}

CMonitorDlg::~CMonitorDlg()
{
}

void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_MONITOR_BACK, m_picMonitorBack);
	DDX_Control(pDX, IDC_RDO_MONITOR_MOTION, m_rdoMonitorMotion);
	DDX_Control(pDX, IDC_RDO_MONITOR_IN_OUT, m_rdoMonitorInOut);
	DDX_Control(pDX, IDC_RDO_MONITOR_LOG, m_rdoMonitorLog);
	DDX_Control(pDX, IDC_BTN_MONITOR_CLOSE, m_btnMonitorClose);
}

BEGIN_MESSAGE_MAP(CMonitorDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RDO_MONITOR_MOTION, &CMonitorDlg::OnBnClickedRdoMonitorMotion)
	ON_BN_CLICKED(IDC_RDO_MONITOR_IN_OUT, &CMonitorDlg::OnBnClickedRdoMonitorInOut)
	ON_BN_CLICKED(IDC_RDO_MONITOR_LOG, &CMonitorDlg::OnBnClickedRdoMonitorLog)
	ON_BN_CLICKED(IDC_BTN_MONITOR_CLOSE, &CMonitorDlg::OnBnClickedBtnMonitorClose)
END_MESSAGE_MAP()

// CMonitorDlg �޽��� ó�����Դϴ�.

BOOL CMonitorDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	Initial_Controls();

	m_pMonitorMotionDlg = new CMonitorMotionDlg(this);
	m_pMonitorMotionDlg->Create(IDD_MONITOR_MOTION_DLG, this);

	m_pMonitorInOutDlg = new CMonitorInOutDlg(this);
	m_pMonitorInOutDlg->Create(IDD_MONITOR_IN_OUT_DLG, this);

	m_pMonitorLogDlg = new CMonitorLogDlg(this);
	m_pMonitorLogDlg->Create(IDD_MONITOR_LOG_DLG, this);

	m_rdoMonitorMotion.SetCheck(TRUE);
	m_rdoMonitorMotion.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMonitorDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	m_pMonitorLogDlg->DestroyWindow();
	m_pMonitorInOutDlg->DestroyWindow();
	m_pMonitorMotionDlg->DestroyWindow();

	if (m_pMonitorLogDlg) delete m_pMonitorLogDlg;
	if (m_pMonitorInOutDlg) delete m_pMonitorInOutDlg;
	if (m_pMonitorMotionDlg) delete m_pMonitorMotionDlg;
	
	m_pMonitorLogDlg = NULL;
	m_pMonitorInOutDlg = NULL;
	m_pMonitorMotionDlg = NULL;
}

BOOL CMonitorDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMonitorDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
// 		SetWindowPos(NULL, 67, 136, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
// 		CenterWindow(GetDesktopWindow());
// 		CenterWindow(NULL);
		if (m_rdoMonitorMotion.GetCheck()) m_pMonitorMotionDlg->ShowWindow(SW_SHOW);
		if (m_rdoMonitorInOut.GetCheck()) m_pMonitorInOutDlg->ShowWindow(SW_SHOW);
		if (m_rdoMonitorLog.GetCheck()) m_pMonitorLogDlg->ShowWindow(SW_SHOW);
		SetTimer(0, 100, NULL);
	} else {
		KillTimer(0);
		if (m_rdoMonitorMotion.GetCheck()) m_pMonitorMotionDlg->ShowWindow(SW_HIDE);
		if (m_rdoMonitorInOut.GetCheck()) m_pMonitorInOutDlg->ShowWindow(SW_HIDE);
		if (m_rdoMonitorLog.GetCheck()) m_pMonitorLogDlg->ShowWindow(SW_HIDE);
	}
}

void CMonitorDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(0);

	if (m_pMonitorMotionDlg->IsWindowVisible()) m_pMonitorMotionDlg->Display_Status();
	if (m_pMonitorInOutDlg->IsWindowVisible()) m_pMonitorInOutDlg->Display_Status();

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CMonitorDlg::OnBnClickedRdoMonitorMotion()
{
	if (m_pMonitorMotionDlg->IsWindowVisible()) return;
	Hide_Windows();
	m_rdoMonitorMotion.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pMonitorMotionDlg->ShowWindow(SW_SHOW);
}

void CMonitorDlg::OnBnClickedRdoMonitorInOut()
{
	if (m_pMonitorInOutDlg->IsWindowVisible()) return;
	Hide_Windows();
	m_rdoMonitorInOut.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pMonitorInOutDlg->ShowWindow(SW_SHOW);
}

void CMonitorDlg::OnBnClickedRdoMonitorLog()
{
	if (m_pMonitorLogDlg->IsWindowVisible()) return;
	Hide_Windows();
	m_rdoMonitorLog.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pMonitorLogDlg->ShowWindow(SW_SHOW);
}

void CMonitorDlg::OnBnClickedBtnMonitorClose()
{
	ShowWindow(SW_HIDE);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CMonitorDlg::Initial_Controls() 
{
	m_picMonitorBack.Init_Ctrl(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xA0));
	m_rdoMonitorMotion.Init_Ctrl("����", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_MOTION, CRadioCS::emLeft);
	m_rdoMonitorInOut.Init_Ctrl("����", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_IN_OUT, CRadioCS::emLeft);
	m_rdoMonitorLog.Init_Ctrl("����", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_LOG, CRadioCS::emLeft);
	m_btnMonitorClose.Init_Ctrl("����", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, IDI_CLOSE, CRadioCS::emLeft);
}

void CMonitorDlg::Hide_Windows()
{
	m_pMonitorMotionDlg->ShowWindow(SW_HIDE);
	m_pMonitorInOutDlg->ShowWindow(SW_HIDE);
	m_pMonitorLogDlg->ShowWindow(SW_HIDE);

	m_rdoMonitorMotion.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoMonitorInOut.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoMonitorLog.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
}

///////////////////////////////////////////////////////////////////////////////
