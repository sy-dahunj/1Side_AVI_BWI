// MonitorInOutTabDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "MonitorInOutTabDlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"

// CMonitorInOutTabDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMonitorInOutTabDlg, CDialogEx)

CMonitorInOutTabDlg::CMonitorInOutTabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonitorInOutTabDlg::IDD, pParent)
{
}

CMonitorInOutTabDlg::~CMonitorInOutTabDlg()
{
}

void CMonitorInOutTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 32; i++) DDX_Control(pDX, IDC_LED_IN_0 + i, m_ledIn[i]);
	for (int i = 0; i < 32; i++) DDX_Control(pDX, IDC_LED_OUT_0 + i, m_ledOut[i]);
}

BEGIN_MESSAGE_MAP(CMonitorInOutTabDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// CMonitorInOutTabDlg 메시지 처리기입니다.

BOOL CMonitorInOutTabDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 55, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_nInOutTab = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMonitorInOutTabDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CMonitorInOutTabDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMonitorInOutTabDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		CString strSection, strKeyName, strText;

		CIniFileCS INI_In("System/InputList.ini");

		strSection = "INPUT";
		for (int i = 0; i < 32; i++) {
			strKeyName.Format("%03d", m_nInOutTab * 100 + i);
			strText.Format("[%s] %s", strKeyName, INI_In.Get_String(strSection, strKeyName, ""));
			m_ledIn[i].SetWindowText(strText);
		}

		CIniFileCS INI_Out("System/OutputList.ini");

		strSection = "OUTPUT";
		for (int i = 0; i < 32; i++) {
			strKeyName.Format("%03d", m_nInOutTab * 100 + i);
			strText.Format("[%s] %s", strKeyName, INI_Out.Get_String(strSection, strKeyName, ""));
			m_ledOut[i].SetWindowText(strText);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CMonitorInOutTabDlg::Initial_Controls() 
{
	m_Group[0].Init_Ctrl("바탕", 12, TRUE, RGB(0x20, 0x80, 0x20), COLOR_DEFAULT);
	m_Group[1].Init_Ctrl("바탕", 12, TRUE, RGB(0x80, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 0; i < 32; i++) m_ledIn[i].Init_Ctrl("굴림", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 32; i++) m_ledOut[i].Init_Ctrl("굴림", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
}

void CMonitorInOutTabDlg::Display_Status()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	if (m_nInOutTab == 0) {
		DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
		DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

		for (int i = 0; i < 32; i++) {
			if ((pDX0->nValue >> i) & 0x01) m_ledIn[i].Set_On(TRUE);
			else m_ledIn[i].Set_On(FALSE);

			if ((pDY0->nValue >> i) & 0x01) m_ledOut[i].Set_On(TRUE);
			else m_ledOut[i].Set_On(FALSE);
		}

	} else if (m_nInOutTab == 1) {
		DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();
		DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

		for (int i = 0; i < 32; i++) {
			if ((pDX1->nValue >> i) & 0x01) m_ledIn[i].Set_On(TRUE);
			else m_ledIn[i].Set_On(FALSE);

			if ((pDY1->nValue >> i) & 0x01) m_ledOut[i].Set_On(TRUE);
			else m_ledOut[i].Set_On(FALSE);
		}

	} else if (m_nInOutTab == 2) {
		DX_DATA_2 *pDX2 = pAJinAXL->Get_pDX2();
		DY_DATA_2 *pDY2 = pAJinAXL->Get_pDY2();

		for (int i = 0; i < 32; i++) {
			if ((pDX2->nValue >> i) & 0x01) m_ledIn[i].Set_On(TRUE);
			else m_ledIn[i].Set_On(FALSE);

			if ((pDY2->nValue >> i) & 0x01) m_ledOut[i].Set_On(TRUE);
			else m_ledOut[i].Set_On(FALSE);
		}

	} else if (m_nInOutTab == 3) {
		DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();
		DY_DATA_3 *pDY3 = pAJinAXL->Get_pDY3();

		for (int i = 0; i < 32; i++) {
			if ((pDX3->nValue >> i) & 0x01) m_ledIn[i].Set_On(TRUE);
			else m_ledIn[i].Set_On(FALSE);

			if ((pDY3->nValue >> i) & 0x01) m_ledOut[i].Set_On(TRUE);
			else m_ledOut[i].Set_On(FALSE);
		}
	
	} else if (m_nInOutTab == 4) {
		DX_DATA_4 *pDX4 = pAJinAXL->Get_pDX4();
		DY_DATA_4 *pDY4 = pAJinAXL->Get_pDY4();

		for (int i = 0; i < 32; i++) {
			if ((pDX4->nValue >> i) & 0x01) m_ledIn[i].Set_On(TRUE);
			else m_ledIn[i].Set_On(FALSE);

			if ((pDY4->nValue >> i) & 0x01) m_ledOut[i].Set_On(TRUE);
			else m_ledOut[i].Set_On(FALSE);
		}
	
	} else if (m_nInOutTab == 5) {
		DX_DATA_5 *pDX5 = pAJinAXL->Get_pDX5();
		DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();

		for (int i = 0; i < 32; i++) {
			if ((pDX5->nValue >> i) & 0x01) m_ledIn[i].Set_On(TRUE);
			else m_ledIn[i].Set_On(FALSE);

			if ((pDY5->nValue >> i) & 0x01) m_ledOut[i].Set_On(TRUE);
			else m_ledOut[i].Set_On(FALSE);
		}
	
	} else if (m_nInOutTab == 6) {
		DX_DATA_6 *pDX6 = pAJinAXL->Get_pDX6();
		DY_DATA_6 *pDY6 = pAJinAXL->Get_pDY6();

		for (int i = 0; i < 32; i++) {
			if ((pDX6->nValue >> i) & 0x01) m_ledIn[i].Set_On(TRUE);
			else m_ledIn[i].Set_On(FALSE);

			if ((pDY6->nValue >> i) & 0x01) m_ledOut[i].Set_On(TRUE);
			else m_ledOut[i].Set_On(FALSE);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
