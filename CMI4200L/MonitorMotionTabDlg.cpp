// MonitorMotionTab1Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "MonitorMotionTabDlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"

// CMonitorMotionTabDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMonitorMotionTabDlg, CDialogEx)

CMonitorMotionTabDlg::CMonitorMotionTabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonitorMotionTabDlg::IDD, pParent)
{
}

CMonitorMotionTabDlg::~CMonitorMotionTabDlg()
{
}

void CMonitorMotionTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_0, m_Group);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_STC_AXIS_NAME_0 + i, m_stcAxisName[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_STC_AXIS_VEL_0 + i, m_stcAxisVel[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_LED_AXIS_SON_0 + i, m_ledAxisSOn[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_LED_AXIS_ELP_0 + i, m_ledAxisElp[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_LED_AXIS_ELN_0 + i, m_ledAxisEln[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_LED_AXIS_ALM_0 + i, m_ledAxisAlm[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_LED_AXIS_INP_0 + i, m_ledAxisInP[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_LED_AXIS_RUN_0 + i, m_ledAxisRun[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_LED_AXIS_HOM_0 + i, m_ledAxisHom[i]);
}

BEGIN_MESSAGE_MAP(CMonitorMotionTabDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// CMonitorMotionTabDlg 메시지 처리기입니다.

BOOL CMonitorMotionTabDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 55, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_nMotionTab = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMonitorMotionTabDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CMonitorMotionTabDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMonitorMotionTabDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		/* 
		BOOL bShow = (m_nMotionTab == 0 ? FALSE : TRUE);

		m_stcAxisName[7].ShowWindow(bShow);
		m_stcAxisPos[7].ShowWindow(bShow);
		m_stcAxisVel[7].ShowWindow(bShow);

		m_ledAxisSOn[7].ShowWindow(bShow);
		m_ledAxisElp[7].ShowWindow(bShow);
		m_ledAxisEln[7].ShowWindow(bShow);
		m_ledAxisAlm[7].ShowWindow(bShow);
		m_ledAxisInP[7].ShowWindow(bShow);
		m_ledAxisRun[7].ShowWindow(bShow);
		m_ledAxisHom[7].ShowWindow(bShow);
		*/
		bShow = FALSE;
		m_stcAxisName[8].ShowWindow(bShow);
		m_stcAxisPos[8].ShowWindow(bShow);
		m_stcAxisVel[8].ShowWindow(bShow);

		m_ledAxisSOn[8].ShowWindow(bShow);
		m_ledAxisElp[8].ShowWindow(bShow);
		m_ledAxisEln[8].ShowWindow(bShow);
		m_ledAxisAlm[8].ShowWindow(bShow);
		m_ledAxisInP[8].ShowWindow(bShow);
		m_ledAxisRun[8].ShowWindow(bShow);
		m_ledAxisHom[8].ShowWindow(bShow);

		CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

		CString strSection, strKeyName, strNm, strText;
		CString strMovSpeed, strJogSpeed;

		CIniFileCS INI("System/AxisList.ini");
		strSection = "AXIS";

		//int nMaxAxis = (m_nMotionTab == 2 ? 9 : 8);
		//int nMaxAxis = (m_nMotionTab == 0 ? 7 : 8);
		int nMaxAxis = (m_nMotionTab == 3 ? 8 : 8);  
	
		for (int i = 0; i < nMaxAxis; i++) {
			strKeyName.Format("%02d", m_nMotionTab * 8 + i);
			strNm = INI.Get_String(strSection, strKeyName, "");
			strText.Format(" [%02d] %s", m_nMotionTab * 8 + i + 8, strNm);
			m_stcAxisName[i].SetWindowText(strText);

			//if (pAJinAXL->Is_ServoAxis(m_nMotionTab * 8 + i)) m_ledAxisSOn[i].ShowWindow(SW_SHOW);
			//else m_ledAxisSOn[i].ShowWindow(SW_HIDE);

			//if (pAJinAXL->Is_ServoAxis(m_nMotionTab * 8 + i)) m_ledAxisAlm[i].ShowWindow(SW_SHOW);
			//else m_ledAxisAlm[i].ShowWindow(SW_HIDE);

			//if (pAJinAXL->Is_ServoAxis(m_nMotionTab * 8 + i)) m_ledAxisInP[i].ShowWindow(SW_SHOW);
			//else m_ledAxisInP[i].ShowWindow(SW_HIDE);

			//if (pAJinAXL->Use_ElpAxis(m_nMotionTab * 8 + i)) m_ledAxisElp[i].ShowWindow(SW_SHOW);
			//else m_ledAxisElp[i].ShowWindow(SW_HIDE);

			//if (pAJinAXL->Use_ElnAxis(m_nMotionTab * 8 + i)) m_ledAxisEln[i].ShowWindow(SW_SHOW);
			//else m_ledAxisEln[i].ShowWindow(SW_HIDE);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CMonitorMotionTabDlg::Initial_Controls() 
{
	m_Group.Init_Ctrl("바탕", 12, TRUE, RGB(0x10, 0x50, 0x40), COLOR_DEFAULT);
	for (int i = 0; i < 10; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 9; i++) m_stcAxisName[i].Init_Ctrl("바탕", 8, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x00));
	for (int i = 0; i < 9; i++) m_stcAxisPos[i].Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0x00, 0x00), RGB(0xFF, 0xFF, 0xE0));
	for (int i = 0; i < 9; i++) m_stcAxisVel[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xFF, 0xE0));

	for (int i = 0; i < 9; i++) m_ledAxisSOn[i].Init_Ctrl("", 0, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 9; i++) m_ledAxisElp[i].Init_Ctrl("", 0, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 9; i++) m_ledAxisEln[i].Init_Ctrl("", 0, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 9; i++) m_ledAxisAlm[i].Init_Ctrl("", 0, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 9; i++) m_ledAxisInP[i].Init_Ctrl("", 0, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 9; i++) m_ledAxisRun[i].Init_Ctrl("", 0, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 9; i++) m_ledAxisHom[i].Init_Ctrl("", 0, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
}

void CMonitorMotionTabDlg::Display_Status()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	CString strPos, strVel;

	//int nMaxAxis = (m_nMotionTab == 2 ? 9 : 8);
	//int nMaxAxis = (m_nMotionTab == 0 ? 7 : 8);
	int nMaxAxis = (m_nMotionTab == 3 ? 3 : 8);   

	for (int i = 0; i < nMaxAxis; i++) {
		AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(m_nMotionTab * 8 + i);

		strPos.Format("%0.3lf", pStatus->dPos);
		m_stcAxisPos[i].SetWindowText(strPos);

		strVel.Format("%0.3lf", pStatus->dVel);
		m_stcAxisVel[i].SetWindowText(strVel);

		if (pStatus->bSOn) m_ledAxisSOn[i].Set_On(TRUE);
		else m_ledAxisSOn[i].Set_On(FALSE);

		if (pStatus->bELP) m_ledAxisElp[i].Set_On(TRUE);
		else m_ledAxisElp[i].Set_On(FALSE);

		if (pStatus->bELN) m_ledAxisEln[i].Set_On(TRUE);
		else m_ledAxisEln[i].Set_On(FALSE);

		if (pStatus->bALM) m_ledAxisAlm[i].Set_On(TRUE);
		else m_ledAxisAlm[i].Set_On(FALSE);

		if (pStatus->bInP) m_ledAxisInP[i].Set_On(TRUE);
		else m_ledAxisInP[i].Set_On(FALSE);

		if (pStatus->bRun) m_ledAxisRun[i].Set_On(TRUE);
		else m_ledAxisRun[i].Set_On(FALSE);

		if (pStatus->bHom) m_ledAxisHom[i].Set_On(TRUE);
		else m_ledAxisHom[i].Set_On(FALSE);
	}
}

///////////////////////////////////////////////////////////////////////////////
