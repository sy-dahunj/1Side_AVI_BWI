// MsgBoxDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "MsgBoxDlg.h"
#include "afxdialogex.h"

// CMsgBoxDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMsgBoxDlg, CDialogEx)

CMsgBoxDlg::CMsgBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMsgBoxDlg::IDD, pParent)
{
}

CMsgBoxDlg::~CMsgBoxDlg()
{
}

void CMsgBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STC_MSG, m_stcMsg);
	DDX_Control(pDX, IDC_BTN_ONE_OK, m_btnOneOK);
	DDX_Control(pDX, IDC_BTN_TWO_OK, m_btnTwoOK);
	DDX_Control(pDX, IDC_BTN_TWO_CANCEL, m_btnTwoCancel);
}

BEGIN_MESSAGE_MAP(CMsgBoxDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_ONE_OK, &CMsgBoxDlg::OnBnClickedBtnOneOk)
	ON_BN_CLICKED(IDC_BTN_TWO_OK, &CMsgBoxDlg::OnBnClickedBtnTwoOk)
	ON_BN_CLICKED(IDC_BTN_TWO_CANCEL, &CMsgBoxDlg::OnBnClickedBtnTwoCancel)
END_MESSAGE_MAP()

// CMsgBoxDlg 메시지 처리기입니다.

BOOL CMsgBoxDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	Initial_Controls();

	if (m_nBtnCnt == 1 || m_nBtnCnt == 9) {
		m_btnOneOK.ShowWindow(SW_SHOW);
		m_btnTwoOK.ShowWindow(SW_HIDE);
		m_btnTwoCancel.ShowWindow(SW_HIDE);
	} else {
		m_btnOneOK.ShowWindow(SW_HIDE);
		m_btnTwoOK.ShowWindow(SW_SHOW);
		m_btnTwoCancel.ShowWindow(SW_SHOW);
	}
	m_stcMsg.SetWindowText(m_strMsg);
	m_nCount = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMsgBoxDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CMsgBoxDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMsgBoxDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	SetTimer(0, 100, NULL);
}

void CMsgBoxDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(0);
	if (m_nBtnCnt != 9) return;

	m_nCount++;
	if (m_nCount >= 10) {
		OnBnClickedBtnOneOk();
		return;
	}

	SetTimer(0, 500, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

HBRUSH CMsgBoxDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG)
		return (HBRUSH)m_brushBack;

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CMsgBoxDlg::OnBnClickedBtnOneOk()
{
	EndDialog(IDOK);
}

void CMsgBoxDlg::OnBnClickedBtnTwoOk()
{
	EndDialog(IDOK);
}

void CMsgBoxDlg::OnBnClickedBtnTwoCancel()
{
	EndDialog(IDCANCEL);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CMsgBoxDlg::Initial_Controls() 
{
	m_brushBack.CreateSolidBrush(RGB(0x20, 0x00, 0x60));

	m_stcMsg.Init_Ctrl("바탕", 24, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0x80, 0x80, 0x80));

	m_btnOneOK.Init_Ctrl("바탕", 20, TRUE, RGB(0xFF, 0x00, 0xFF), COLOR_DEFAULT, IDI_OK, CButtonCS::emLeft);
	m_btnTwoOK.Init_Ctrl("바탕", 20, TRUE, RGB(0xFF, 0x00, 0xFF), COLOR_DEFAULT, IDI_OK, CButtonCS::emLeft);
	m_btnTwoCancel.Init_Ctrl("바탕", 20, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, IDI_CANCEL, CButtonCS::emLeft);
}

void CMsgBoxDlg::Set_Message(int nBtnCnt, CString strMsg) 
{
	m_nBtnCnt = nBtnCnt;
	m_strMsg = strMsg;
}

///////////////////////////////////////////////////////////////////////////////
