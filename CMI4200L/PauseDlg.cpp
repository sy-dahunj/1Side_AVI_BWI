// PauseDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "PauseDlg.h"
#include "afxdialogex.h"

#include "CMI4200LDlg.h"

// CPauseDlg ��ȭ �����Դϴ�.
CPauseDlg g_dlgPause;

IMPLEMENT_DYNAMIC(CPauseDlg, CDialogEx)

CPauseDlg::CPauseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPauseDlg::IDD, pParent)
{
}

CPauseDlg::~CPauseDlg()
{
}

void CPauseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STC_PAUSE_TITLE, m_stcPauseTitle);
	DDX_Control(pDX, IDC_STC_PAUSE_MESSAGE, m_stcPauseMessage);
}

BEGIN_MESSAGE_MAP(CPauseDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CPauseDlg �޽��� ó�����Դϴ�.

BOOL CPauseDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowPos(this, 0, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CPauseDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CPauseDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (gData.sCaption[1].GetLength() > 0) m_stcPauseTitle.SetWindowText(gData.sCaption[1]);
	if (gData.sCaption[2].GetLength() > 0) m_stcPauseMessage.SetWindowText(gData.sCaption[2]);

}

HBRUSH CPauseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (nCtlColor == CTLCOLOR_DLG)
		return (HBRUSH)m_brushBack;

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CPauseDlg::Initial_Controls() 
{
	m_brushBack.CreateSolidBrush(RGB(0x00, 0x00, 0x00));

	m_stcPauseTitle.Init_Ctrl("����", 30, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
	m_stcPauseMessage.Init_Ctrl("����", 20, FALSE, RGB(0xFF, 0x00, 0x00), RGB(0x00, 0x00, 0x00));
}

///////////////////////////////////////////////////////////////////////////////
