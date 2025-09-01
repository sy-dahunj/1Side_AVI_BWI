// KeyPadDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "KeyPadDlg.h"
#include "afxdialogex.h"

// CKeyPadDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CKeyPadDlg, CDialogEx)

CString g_strReturnKeyPad;

CKeyPadDlg::CKeyPadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyPadDlg::IDD, pParent)
{
}

CKeyPadDlg::~CKeyPadDlg()
{
}

void CKeyPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_0, m_Label);
	DDX_Control(pDX, IDC_STC_KEY_NAME, m_stcKeyName);
	DDX_Control(pDX, IDC_BTN_CLEAR, m_btnClear);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDel);
	for (int i = 0; i < 38; i++) DDX_Control(pDX, IDC_BTN_KEY_0 + i, m_btnKey[i]);
	DDX_Control(pDX, IDC_BTN_OK, m_btnOK);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CKeyPadDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CKeyPadDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_DEL, &CKeyPadDlg::OnBnClickedBtnDel)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_KEY_0, IDC_BTN_KEY_37, OnBtnKeyClick)
	ON_BN_CLICKED(IDC_BTN_OK, &CKeyPadDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CKeyPadDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()

// CKeyPadDlg �޽��� ó�����Դϴ�.

BOOL CKeyPadDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	Initial_Controls();

	g_strReturnKeyPad = "";

	m_stcKeyName.SetWindowText("");

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CKeyPadDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CKeyPadDlg::PreTranslateMessage(MSG* pMsg) 
{
//	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
//		return TRUE;
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE) return TRUE;
		if (pMsg->wParam == VK_RETURN) { OnBnClickedBtnOk(); return TRUE; }
		if (pMsg->wParam == VK_BACK) { OnBnClickedBtnDel(); return TRUE; }
		if (pMsg->wParam == VK_DELETE) { OnBnClickedBtnDel(); return TRUE; }
	}

	if (pMsg->message == WM_CHAR) {
		TCHAR tChar[256];
		tChar[0] = pMsg->wParam;
		tChar[1] = NULL;
		
		CString strKeyName, sData;
		sData = tChar;	sData.MakeUpper();
		m_stcKeyName.GetWindowText(strKeyName);
		m_stcKeyName.SetWindowText(strKeyName + sData);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CKeyPadDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);
}

HBRUSH CKeyPadDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (nCtlColor == CTLCOLOR_DLG)
		return (HBRUSH)m_brushBack;

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

void CKeyPadDlg::OnBnClickedBtnClear()
{
	m_stcKeyName.SetWindowText("");
}

void CKeyPadDlg::OnBnClickedBtnDel()
{
	CString strKeyName, strKey;
	m_stcKeyName.GetWindowText(strKeyName);
	if(strKeyName.GetLength() > 0) {
		strKey = strKeyName.Left(strKeyName.GetLength()-1);
		m_stcKeyName.SetWindowText(strKey);
	}
}

void CKeyPadDlg::OnBtnKeyClick(UINT nID)
{
	int ID = nID - IDC_BTN_KEY_0;

	CString strKeyName, strKey;
	m_stcKeyName.GetWindowText(strKeyName);
	m_btnKey[ID].GetWindowText(strKey);
	m_stcKeyName.SetWindowText(strKeyName + strKey);
}

void CKeyPadDlg::OnBnClickedBtnOk()
{
	CString strKeyName;
	m_stcKeyName.GetWindowText(strKeyName);
	if (strKeyName == "") return;
	g_strReturnKeyPad = strKeyName;
	EndDialog(IDOK);
}

void CKeyPadDlg::OnBnClickedBtnCancel()
{
	EndDialog(IDCANCEL);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CKeyPadDlg::Initial_Controls() 
{
	m_brushBack.CreateSolidBrush(RGB(0x90, 0x80, 0xC0));

	m_Label.Init_Ctrl("����", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_stcKeyName.Init_Ctrl("����", 20, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xFF, 0xB0));

	m_btnClear.Init_Ctrl("����", 15, TRUE, RGB(0x00, 0xD0, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnDel.Init_Ctrl("����", 15, TRUE, RGB(0x00, 0xD0, 0x00), COLOR_DEFAULT, 0, 0);

	for (int i = 0; i < 38; i++) m_btnKey[i].Init_Ctrl("����", 20, TRUE, RGB(0xB0, 0x50, 0x00), COLOR_DEFAULT, 0, 0);

	m_btnOK.Init_Ctrl("����", 20, TRUE, RGB(0xFF, 0x00, 0xFF), COLOR_DEFAULT, IDI_OK, CButtonCS::emLeft);
	m_btnCancel.Init_Ctrl("����", 20, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, IDI_CANCEL, CButtonCS::emLeft);
}

///////////////////////////////////////////////////////////////////////////////
