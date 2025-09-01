// SetupInOutTabDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupInOutTabDlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"
#include "Common.h"

// CSetupInOutTabDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupInOutTabDlg, CDialogEx)

CSetupInOutTabDlg::CSetupInOutTabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupInOutTabDlg::IDD, pParent)
{
}

CSetupInOutTabDlg::~CSetupInOutTabDlg()
{
}

void CSetupInOutTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 32; i++) DDX_Control(pDX, IDC_STC_IN_0 + i, m_stcIn[i]);
	for (int i = 0; i < 32; i++) DDX_Control(pDX, IDC_CHK_OUT_0 + i, m_chkOut[i]);
}

BEGIN_MESSAGE_MAP(CSetupInOutTabDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_OUT_0, IDC_CHK_OUT_31, OnChkOutClick)
END_MESSAGE_MAP()

// CSetupInOutTabDlg 메시지 처리기입니다.

BOOL CSetupInOutTabDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 55, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_nInOutTab = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetupInOutTabDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CSetupInOutTabDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupInOutTabDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		CString strSection, strKeyName, strText;

		CIniFileCS INI_In("System/InputList.ini");

		strSection = "INPUT";
		for (int i = 0; i < 32; i++) {
			strKeyName.Format("%03d", m_nInOutTab * 100 + i);
			strText.Format("[%s] %s", strKeyName, INI_In.Get_String(strSection, strKeyName, ""));
			m_stcIn[i].SetWindowText(strText);
		}

		CIniFileCS INI_Out("System/OutputList.ini");

		strSection = "OUTPUT";
		for (int i = 0; i < 32; i++) {
			strKeyName.Format("%03d", m_nInOutTab * 100 + i);
			strText.Format("[%s] %s", strKeyName, INI_Out.Get_String(strSection, strKeyName, ""));
			m_chkOut[i].SetWindowText(strText);
		}

		CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

		if (m_nInOutTab == 0) {
			DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

			for (int i = 0; i < 32; i++) {
				if ((pDY0->nValue >> i) & 0x01) Set_CheckBox(i, TRUE);
				else Set_CheckBox(i, FALSE);
			}

		} else if (m_nInOutTab == 1) {
			DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

			for (int i = 0; i < 32; i++) {
				if ((pDY1->nValue >> i) & 0x01) Set_CheckBox(i, TRUE);
				else Set_CheckBox(i, FALSE);
			}

		} else if (m_nInOutTab == 2) {
			DY_DATA_2 *pDY2 = pAJinAXL->Get_pDY2();

			for (int i = 0; i < 32; i++) {
				if ((pDY2->nValue >> i) & 0x01) Set_CheckBox(i, TRUE);
				else Set_CheckBox(i, FALSE);
			}

		} else if (m_nInOutTab == 3) {
			DY_DATA_3 *pDY3 = pAJinAXL->Get_pDY3();

			for (int i = 0; i < 32; i++) {
				if ((pDY3->nValue >> i) & 0x01) Set_CheckBox(i, TRUE);
				else Set_CheckBox(i, FALSE);
			}

		} else if (m_nInOutTab == 4) {
			DY_DATA_4 *pDY4 = pAJinAXL->Get_pDY4();

			for (int i = 0; i < 32; i++) {
				if ((pDY4->nValue >> i) & 0x01) Set_CheckBox(i, TRUE);
				else Set_CheckBox(i, FALSE);
			}

		} else if (m_nInOutTab == 5) {
			DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();

			for (int i = 0; i < 32; i++) {
				if ((pDY5->nValue >> i) & 0x01) Set_CheckBox(i, TRUE);
				else Set_CheckBox(i, FALSE);
			}

		} else if (m_nInOutTab == 6) {
			DY_DATA_6 *pDY6 = pAJinAXL->Get_pDY6();

			for (int i = 0; i < 32; i++) {
				if ((pDY6->nValue >> i) & 0x01) Set_CheckBox(i, TRUE);
				else Set_CheckBox(i, FALSE);
			}
		}
	}
}

void CSetupInOutTabDlg::OnChkOutClick(UINT nID)
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	int ID = nID - IDC_CHK_OUT_0;

	if (m_chkOut[ID].GetCheck()) {
		m_chkOut[ID].Set_Color(RGB(0x01, 0x00, 0x00), RGB(0xFF, 0xC0, 0x00));	// On
		Set_Output(ID, TRUE);
	} else {
		m_chkOut[ID].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x20, 0x20));	// Off
		Set_Output(ID, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupInOutTabDlg::Initial_Controls() 
{
	m_Group[0].Init_Ctrl("바탕", 12, TRUE, RGB(0x20, 0x80, 0x20), COLOR_DEFAULT);
	m_Group[1].Init_Ctrl("바탕", 12, TRUE, RGB(0x80, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 0; i < 32; i++) m_stcIn[i].Init_Ctrl("바탕", 9, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x50, 0x00));			// Off
	for (int i = 0; i < 32; i++) m_chkOut[i].Init_Ctrl("바탕", 9, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x20, 0x20), 0, 0);	// Off
}

void CSetupInOutTabDlg::Display_Status()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	if (m_nInOutTab == 0) {
		DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();

		for (int i = 0; i < 32; i++) {
			if ((pDX0->nValue >> i) & 0x01) m_stcIn[i].Set_Color(RGB(0x01, 0x00, 0x00), RGB(0x20, 0xFF, 0x20));	// On
			else							m_stcIn[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x50, 0x00));	// Off
			m_stcIn[i].Invalidate(FALSE);
		}

	} else if (m_nInOutTab == 1) {
		DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();

		for (int i = 0; i < 32; i++) {
			if ((pDX1->nValue >> i) & 0x01) m_stcIn[i].Set_Color(RGB(0x01, 0x00, 0x00), RGB(0x20, 0xFF, 0x20));	// On
			else							m_stcIn[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x50, 0x00));	// Off
			m_stcIn[i].Invalidate(FALSE);
		}

	} else if (m_nInOutTab == 2) {
		DX_DATA_2 *pDX2 = pAJinAXL->Get_pDX2();

		for (int i = 0; i < 32; i++) {
			if ((pDX2->nValue >> i) & 0x01) m_stcIn[i].Set_Color(RGB(0x01, 0x00, 0x00), RGB(0x20, 0xFF, 0x20));	// On
			else							m_stcIn[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x50, 0x00));	// Off
			m_stcIn[i].Invalidate(FALSE);
		}

	} else if (m_nInOutTab == 3) {
		DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();

		for (int i = 0; i < 32; i++) {
			if ((pDX3->nValue >> i) & 0x01) m_stcIn[i].Set_Color(RGB(0x01, 0x00, 0x00), RGB(0x20, 0xFF, 0x20));	// On
			else							m_stcIn[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x50, 0x00));	// Off
			m_stcIn[i].Invalidate(FALSE);
		}

	} else if (m_nInOutTab == 4) {
		DX_DATA_4 *pDX4 = pAJinAXL->Get_pDX4();

		for (int i = 0; i < 32; i++) {
			if ((pDX4->nValue >> i) & 0x01) m_stcIn[i].Set_Color(RGB(0x01, 0x00, 0x00), RGB(0x20, 0xFF, 0x20));	// On
			else							m_stcIn[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x50, 0x00));	// Off
			m_stcIn[i].Invalidate(FALSE);
		}

	} else if (m_nInOutTab == 5) {
		DX_DATA_5 *pDX5 = pAJinAXL->Get_pDX5();

		for (int i = 0; i < 32; i++) {
			if ((pDX5->nValue >> i) & 0x01) m_stcIn[i].Set_Color(RGB(0x01, 0x00, 0x00), RGB(0x20, 0xFF, 0x20));	// On
			else							m_stcIn[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x50, 0x00));	// Off
			m_stcIn[i].Invalidate(FALSE);
		}
	} else if (m_nInOutTab == 6) {
		DX_DATA_6 *pDX6 = pAJinAXL->Get_pDX6();

		for (int i = 0; i < 32; i++) {
			if ((pDX6->nValue >> i) & 0x01) m_stcIn[i].Set_Color(RGB(0x01, 0x00, 0x00), RGB(0x20, 0xFF, 0x20));	// On
			else							m_stcIn[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x50, 0x00));	// Off
			m_stcIn[i].Invalidate(FALSE);
		}
	}

}

void CSetupInOutTabDlg::Set_CheckBox(int nIdx, BOOL bChk)
{
	if (bChk) {
		m_chkOut[nIdx].SetCheck(TRUE);
		m_chkOut[nIdx].Set_Color(RGB(0x01, 0x00, 0x00), RGB(0xFF, 0xC0, 0x00));	// On
	} else {
		m_chkOut[nIdx].SetCheck(FALSE);
		m_chkOut[nIdx].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x20, 0x20));	// Off
	}
}

void CSetupInOutTabDlg::Set_Output(int nIdx, BOOL bOut)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	if (m_nInOutTab == 0) {
		DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();
		if (bOut) pDY0->nValue |= (1 << nIdx);
		else pDY0->nValue &= ~(1 << nIdx);
		pAJinAXL->Write_Output(0);

	} else if (m_nInOutTab == 1) {
		DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();
		if (bOut) pDY1->nValue |= (1 << nIdx);
		else pDY1->nValue &= ~(1 << nIdx);
		pAJinAXL->Write_Output(1);

	} else if (m_nInOutTab == 2) {
		DY_DATA_2 *pDY2 = pAJinAXL->Get_pDY2();
		if (bOut) pDY2->nValue |= (1 << nIdx);
		else pDY2->nValue &= ~(1 << nIdx);
		pAJinAXL->Write_Output(2);

	} else if (m_nInOutTab == 3) {
		DY_DATA_3 *pDY3 = pAJinAXL->Get_pDY3();
		if (bOut) pDY3->nValue |= (1 << nIdx);
		else pDY3->nValue &= ~(1 << nIdx);
		pAJinAXL->Write_Output(3);
	
	} else if (m_nInOutTab == 4) {
		DY_DATA_4 *pDY4 = pAJinAXL->Get_pDY4();
		if (bOut) pDY4->nValue |= (1 << nIdx);
		else pDY4->nValue &= ~(1 << nIdx);
		pAJinAXL->Write_Output(4);
	
	} else if (m_nInOutTab == 5) {
		DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();
		if (bOut) pDY5->nValue |= (1 << nIdx);
		else pDY5->nValue &= ~(1 << nIdx);
		pAJinAXL->Write_Output(5);
	
	} else if (m_nInOutTab == 6) {
		DY_DATA_6 *pDY6 = pAJinAXL->Get_pDY6();
		if (bOut) pDY6->nValue |= (1 << nIdx);
		else pDY6->nValue &= ~(1 << nIdx);
		pAJinAXL->Write_Output(6);
	
	}

}

/////////////////////////////////////////////////////////////////////////////
