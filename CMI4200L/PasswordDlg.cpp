// PasswordDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "PasswordDlg.h"
#include "afxdialogex.h"

// CPasswordDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPasswordDlg, CDialogEx)

CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPasswordDlg::IDD, pParent)
{
}

CPasswordDlg::~CPasswordDlg()
{
}

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_PASSWORD, m_edtPassword);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_BTN_PASS_NUM_0 + i, m_btnPassNum[i]);
	DDX_Control(pDX, IDC_BTN_OK, m_btnOK);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CPasswordDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_PASS_NUM_0, IDC_BTN_PASS_NUM_9, OnBtnPassNumClick)
	ON_BN_CLICKED(IDC_BTN_OK, &CPasswordDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CPasswordDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()

// CPasswordDlg �޽��� ó�����Դϴ�.

BOOL CPasswordDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	Initial_Controls();

	m_edtPassword.SetWindowText("");

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CPasswordDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CPasswordDlg::PreTranslateMessage(MSG* pMsg) 
{
//	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
//		return TRUE;

	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE) return TRUE;
		if (pMsg->wParam == VK_RETURN) { OnBnClickedBtnOk(); return TRUE; }
	}

	if (pMsg->message == WM_CHAR) {
		TCHAR tChar[256];
		tChar[0] = pMsg->wParam;
		tChar[1] = NULL;
		int nChar = atoi(tChar);
		if (tChar[0] >= '0' && tChar[0] <= '9') { OnBtnPassNumClick(IDC_BTN_PASS_NUM_0 + nChar); return TRUE; }
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CPasswordDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);
}

HBRUSH CPasswordDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (nCtlColor == CTLCOLOR_DLG)
		return (HBRUSH)m_brushBack;

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

void CPasswordDlg::OnBtnPassNumClick(UINT nID)
{
	int ID = nID - IDC_BTN_PASS_NUM_0;

	CString strPassword, strNum;
	m_edtPassword.GetWindowText(strPassword);
	m_btnPassNum[ID].GetWindowText(strNum);
	m_edtPassword.SetWindowText(strPassword + strNum);
}

void CPasswordDlg::OnBnClickedBtnOk()
{
	CString strPassword, siniPsw, strPsw;

	SYSTEMTIME time;
	GetLocalTime(&time);
	strPsw.Format("%02d%02d%02d", time.wMinute, time.wHour, time.wDay);

	CIniFileCS INI("System/USER_PSW.ini");
	if (!INI.Check_File()) {
		m_edtPassword.SetWindowText("");
		siniPsw = strPassword = strPsw;
	} else {
		siniPsw = INI.Get_String("PASSWORD", "PSW", "");
//		siniPsw = strPsw;
		m_edtPassword.GetWindowText(strPassword);
	}

	if (strPassword == siniPsw) EndDialog(IDOK);
	else m_edtPassword.SetWindowText("");
}

void CPasswordDlg::OnBnClickedBtnCancel()
{
	EndDialog(IDCANCEL);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CPasswordDlg::Initial_Controls() 
{
	m_brushBack.CreateSolidBrush(RGB(0x70, 0xD0, 0xF0));

	m_edtPassword.Init_Ctrl("����", 20, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xFF, 0xB0));

	for (int i = 0; i < 10; i++) m_btnPassNum[i].Init_Ctrl("����", 20, TRUE, RGB(0xB0, 0x50, 0x00), COLOR_DEFAULT, 0, 0);

	m_btnOK.Init_Ctrl("����", 20, TRUE, RGB(0xFF, 0x00, 0xFF), COLOR_DEFAULT, IDI_OK, CButtonCS::emLeft);
	m_btnCancel.Init_Ctrl("����", 20, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, IDI_CANCEL, CButtonCS::emLeft);
}

///////////////////////////////////////////////////////////////////////////////
