// SplashDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SplashDlg.h"
#include "afxdialogex.h"

// CSplashDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSplashDlg, CDialogEx)

CSplashDlg::CSplashDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSplashDlg::IDD, pParent)
{
}

CSplashDlg::~CSplashDlg()
{
}

void CSplashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_IMAGE_0 + i, m_Image[i]);
}

BEGIN_MESSAGE_MAP(CSplashDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CSplashDlg �޽��� ó�����Դϴ�.

BOOL CSplashDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CSplashDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

HBRUSH CSplashDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (nCtlColor == CTLCOLOR_DLG)
		return (HBRUSH)GetStockObject(WHITE_BRUSH);

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSplashDlg::Initial_Controls() 
{
	m_Label[0].Init_Ctrl("Arial Black", 20, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xFF, 0xFF));
	m_Label[1].Init_Ctrl("Arial Black", 24, TRUE, RGB(0xFF, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	m_Label[2].Init_Ctrl("����", 12, TRUE, RGB(0x80, 0x20, 0x20), RGB(0xFF, 0xFF, 0xFF));
	m_Label[3].Init_Ctrl("����", 12, TRUE, RGB(0x80, 0x20, 0x20), RGB(0xFF, 0xFF, 0xFF));

	m_bmpImage[0].LoadBitmap(IDB_SYNAPSE_IMAGE);
	m_Image[0].SetBitmap(m_bmpImage[0]);
	m_Image[0].SetWindowPos(this, 0, 0, 680, 300, SWP_NOMOVE | SWP_NOZORDER);

	m_bmpImage[1].LoadBitmap(IDB_SYNAPSE_LOGO);
	m_Image[1].SetBitmap(m_bmpImage[1]);
	m_Image[0].SetWindowPos(this, 0, 0, 260, 75, SWP_NOMOVE);
}

///////////////////////////////////////////////////////////////////////////////
