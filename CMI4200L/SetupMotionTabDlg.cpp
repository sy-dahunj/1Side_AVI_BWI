// SetupMotionTabDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupMotionTabDlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"
#include "Common.h"

#include "SetupDlg.h"

// CSetupMotionTabDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMotionTabDlg, CDialogEx)

CSetupMotionTabDlg::CSetupMotionTabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMotionTabDlg::IDD, pParent)
{
}

CSetupMotionTabDlg::~CSetupMotionTabDlg()
{
}


void CSetupMotionTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 26; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_AXIS_NAME_0 + i, m_stcAxisName[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_AXIS_VEL_0 + i, m_stcAxisVel[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_AXIS_SON_0 + i, m_ledAxisSOn[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_AXIS_ELP_0 + i, m_ledAxisElp[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_AXIS_ELN_0 + i, m_ledAxisEln[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_AXIS_ALM_0 + i, m_ledAxisAlm[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_AXIS_INP_0 + i, m_ledAxisInP[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_AXIS_RUN_0 + i, m_ledAxisRun[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_AXIS_HOM_0 + i, m_ledAxisHom[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_CHK_S_ON_0 + i, m_chkSOn[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_HOME_0 + i, m_btnHome[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_ABS_DIST_0 + i, m_stcAbsDist[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_ABS_MOVE_0 + i, m_btnAbsMove[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_REL_DIST_0 + i, m_stcRelDist[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_REL_MOVE_P_0 + i, m_btnRelMoveP[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_REL_MOVE_N_0 + i, m_btnRelMoveN[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_STOP_0 + i, m_btnStop[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_RESET_0 + i, m_btnReset[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_JOG_P_0 + i, m_btnJogP[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_JOG_N_0 + i, m_btnJogN[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_MOV_SPEED_0 + i, m_stcMovSpeed[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_JOG_SPEED_0 + i, m_stcJogSpeed[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_SAVE_0 + i, m_btnSave[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_CANCEL_0 + i, m_btnCancel[i]);
}

BEGIN_MESSAGE_MAP(CSetupMotionTabDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_S_ON_0, IDC_CHK_S_ON_3, OnChkSOnClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_HOME_0, IDC_BTN_HOME_3, OnBtnHomeClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_ABS_DIST_0, IDC_STC_ABS_DIST_3, OnStcAbsDistClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ABS_MOVE_0, IDC_BTN_ABS_MOVE_3, OnBtnAbsMoveClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_REL_DIST_0, IDC_STC_REL_DIST_3, OnStcRelDistClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_REL_MOVE_P_0, IDC_BTN_REL_MOVE_P_3, OnBtnRelMovePClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_REL_MOVE_N_0, IDC_BTN_REL_MOVE_N_3, OnBtnRelMoveNClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_STOP_0, IDC_BTN_STOP_3, OnBtnStopClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_RESET_0, IDC_BTN_RESET_3, OnBtnResetClick)
	ON_MESSAGE(UM_CS_LBUTTON_DOWN, OnCsLButtonDown)
	ON_MESSAGE(UM_CS_LBUTTON_UP, OnCsLButtonUp)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_MOV_SPEED_0, IDC_STC_MOV_SPEED_3, OnStcMovSpeedClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_STC_JOG_SPEED_0, IDC_STC_JOG_SPEED_3, OnStcJogSpeedClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SAVE_0, IDC_BTN_SAVE_3, OnBtnSaveClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CANCEL_0, IDC_BTN_CANCEL_3, OnBtnCancelClick)
END_MESSAGE_MAP()

// CSetupMotionTabDlg 메시지 처리기입니다.

BOOL CSetupMotionTabDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 55, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_nMotionTab = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetupMotionTabDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CSetupMotionTabDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMotionTabDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		/*수정함 by kty
		//BOOL bShow = 4;//(m_nMotionTab == 4 || m_nMotionTab == 5 || m_nMotionTab == 6 ? FALSE : TRUE);
		BOOL bShow = (m_nMotionTab == 1 ? FALSE : TRUE);

		m_stcAxisName[3].ShowWindow(bShow);
		m_stcAxisPos[3].ShowWindow(bShow);
		m_stcAxisVel[3].ShowWindow(bShow);
		m_ledAxisSOn[3].ShowWindow(bShow);
		m_ledAxisElp[3].ShowWindow(bShow);
		m_ledAxisEln[3].ShowWindow(bShow);
		m_ledAxisAlm[3].ShowWindow(bShow);
		m_ledAxisInP[3].ShowWindow(bShow);
		m_ledAxisRun[3].ShowWindow(bShow);
		m_ledAxisHom[3].ShowWindow(bShow);

		m_Group[4].ShowWindow(bShow);
		for (int i = 22; i < 26; i++) m_Label[i].ShowWindow(bShow);

		m_chkSOn[3].ShowWindow(bShow);
		m_btnHome[3].ShowWindow(bShow);
		m_stcAbsDist[3].ShowWindow(bShow);
		m_btnAbsMove[3].ShowWindow(bShow);
		m_stcRelDist[3].ShowWindow(bShow);
		m_btnRelMoveP[3].ShowWindow(bShow);
		m_btnRelMoveN[3].ShowWindow(bShow);
		m_btnStop[3].ShowWindow(bShow);
		m_btnJogP[3].ShowWindow(bShow);
		m_btnJogN[3].ShowWindow(bShow);
		m_stcMovSpeed[3].ShowWindow(bShow);
		m_stcJogSpeed[3].ShowWindow(bShow);
		m_btnSave[3].ShowWindow(bShow);
		m_btnCancel[3].ShowWindow(bShow);
		*/
		CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

		CString strSection, strKeyName, strNm, strText;
		CString strSpeed;

		CIniFileCS INI("System/AxisList.ini");
		strSection = "AXIS";

		int nMaxAxis = 4;
		int nAxisNo;
		//int nMaxAxis = (m_nMotionTab == 5 ? 3 : 4);

		for (int i = 0; i < nMaxAxis; i++) {
			strKeyName.Format("%02d", m_nMotionIdx + i);
			strNm = INI.Get_String(strSection, strKeyName, "");
			strText.Format(" [%02d] %s", m_nMotionIdx + i + 8, strNm);
			m_stcAxisName[i].SetWindowText(strText);
			m_Group[i + 1].SetWindowText(strText);

			nAxisNo = m_nMotionIdx + i;
//			if((nAxisNo>=0 && nAxisNo<=1) || (nAxisNo>=19 && nAxisNo<=20))
//				m_btnHome[i].ShowWindow(FALSE);
//			else
				m_btnHome[i].ShowWindow(TRUE);
			if(nAxisNo==AX_INDEX_R) {
				m_btnRelMoveP[i].ShowWindow(FALSE);
				m_btnRelMoveN[i].ShowWindow(FALSE);
				m_btnJogP[i].ShowWindow(FALSE);
				m_btnJogN[i].ShowWindow(FALSE);
			} else {
				m_btnRelMoveP[i].ShowWindow(TRUE);
				m_btnRelMoveN[i].ShowWindow(TRUE);
				m_btnJogP[i].ShowWindow(TRUE);
				m_btnJogN[i].ShowWindow(TRUE);
			}

			m_ledAxisSOn[i].ShowWindow(SW_SHOW);
			//if (pAJinAXL->Is_ServoAxis(m_nMotionIdx + i)) m_ledAxisSOn[i].ShowWindow(SW_SHOW);
			//else m_ledAxisSOn[i].ShowWindow(SW_HIDE);

			m_ledAxisAlm[i].ShowWindow(SW_SHOW);
			//if (pAJinAXL->Is_ServoAxis(m_nMotionIdx + i)) m_ledAxisAlm[i].ShowWindow(SW_SHOW);
			//else m_ledAxisAlm[i].ShowWindow(SW_HIDE);

			m_ledAxisInP[i].ShowWindow(SW_SHOW);
			//if (pAJinAXL->Is_ServoAxis(m_nMotionIdx + i)) m_ledAxisInP[i].ShowWindow(SW_SHOW);
			//else m_ledAxisInP[i].ShowWindow(SW_HIDE);

			m_chkSOn[i].ShowWindow(SW_SHOW);
			//if (pAJinAXL->Is_ServoAxis(m_nMotionIdx + i)) m_chkSOn[i].ShowWindow(SW_SHOW);
			//else m_chkSOn[i].ShowWindow(SW_HIDE);

			if (pAJinAXL->Use_ElpAxis(m_nMotionIdx + i)) m_ledAxisElp[i].ShowWindow(SW_SHOW);
			else m_ledAxisElp[i].ShowWindow(SW_HIDE);

			if (pAJinAXL->Use_ElnAxis(m_nMotionIdx + i)) m_ledAxisEln[i].ShowWindow(SW_SHOW);
			else m_ledAxisEln[i].ShowWindow(SW_HIDE);

			AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(m_nMotionIdx + i);
			if (pStatus->bSOn) m_chkSOn[i].SetCheck(TRUE);
			else m_chkSOn[i].SetCheck(FALSE);

			m_stcAbsDist[i].SetWindowText("0.000");
			m_stcRelDist[i].SetWindowText("0.000");

			AXIS_PARAM *pParam = pAJinAXL->Get_pParam(m_nMotionIdx + i);
			strSpeed.Format("%0.3lf", pParam->dMovSpeed);
			m_stcMovSpeed[i].SetWindowText(strSpeed);

			strSpeed.Format("%0.3lf", pParam->dJogSpeed);
			m_stcJogSpeed[i].SetWindowText(strSpeed);			
		}
	}
}

void CSetupMotionTabDlg::OnChkSOnClick(UINT nID)
{
	int ID = nID - IDC_CHK_S_ON_0;

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	if (m_chkSOn[ID].GetCheck()) pAJinAXL->Set_ServoOn(m_nMotionIdx + ID, TRUE);
	else pAJinAXL->Set_ServoOn(m_nMotionIdx + ID, FALSE);
}

void CSetupMotionTabDlg::OnBtnHomeClick(UINT nID)
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	int ID = nID - IDC_BTN_HOME_0;
	if (Check_Interlock(m_nMotionIdx + ID)==FALSE) return;

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	pAJinAXL->Home_Search(m_nMotionIdx + ID);
}

void CSetupMotionTabDlg::OnStcAbsDistClick(UINT nID)
{
	int ID = nID - IDC_STC_ABS_DIST_0;
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcAbsDist[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcAbsDist[ID].SetWindowText(strNew);
	}
}

void CSetupMotionTabDlg::OnBtnAbsMoveClick(UINT nID)
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	int ID = nID - IDC_BTN_ABS_MOVE_0;

	CString strText;
	m_stcAbsDist[ID].GetWindowText(strText);
	double dDist = atof(strText);

	if (Check_Interlock(m_nMotionIdx + ID)==FALSE) return;

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	if(m_nMotionIdx + ID  == 7)
	{
		pAJinAXL->Set_CVActPos(m_nMotionIdx + ID);
	}

	pAJinAXL->Move_Absolute(m_nMotionIdx + ID, dDist);
}

void CSetupMotionTabDlg::OnStcRelDistClick(UINT nID)
{
	int ID = nID - IDC_STC_REL_DIST_0;
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcRelDist[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcRelDist[ID].SetWindowText(strNew);
	}
}

void CSetupMotionTabDlg::OnBtnRelMovePClick(UINT nID)
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	int ID = nID - IDC_BTN_REL_MOVE_P_0;

	CString strText;
	m_stcRelDist[ID].GetWindowText(strText);
	double dDist = atof(strText);

	if (dDist > 2.0) {
		//if (Check_Interlock(m_nMotionIdx + ID)==FALSE) return;
	}

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	pAJinAXL->Move_Relative(m_nMotionIdx + ID, dDist);
}

void CSetupMotionTabDlg::OnBtnRelMoveNClick(UINT nID)
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	int ID = nID - IDC_BTN_REL_MOVE_N_0;

	CString strText;
	m_stcRelDist[ID].GetWindowText(strText);
	double dDist = atof(strText) * -1.0;

	if (dDist < -2.0) {
		//if (Check_Interlock(m_nMotionIdx + ID)==FALSE) return;
	}

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	pAJinAXL->Move_Relative(m_nMotionIdx + ID, dDist);
}

void CSetupMotionTabDlg::OnBtnStopClick(UINT nID)
{
	int ID = nID - IDC_BTN_STOP_0;
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	pAJinAXL->Stop_Motion(m_nMotionIdx + ID);
}

void CSetupMotionTabDlg::OnBtnResetClick(UINT nID)
{
	int ID = nID - IDC_BTN_RESET_0;
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	pAJinAXL->Alarm_Reset(m_nMotionIdx + ID);
}

LRESULT CSetupMotionTabDlg::OnCsLButtonDown(WPARAM wParam, LPARAM lParam)
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return 0;

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	UINT nID = (int)wParam;
	if (nID >= IDC_BTN_JOG_P_0 && nID <= IDC_BTN_JOG_P_3) {			// Jog +
		int ID = nID - IDC_BTN_JOG_P_0;

		pAJinAXL->Jog_Positive(m_nMotionIdx + ID);
	} else if (nID >= IDC_BTN_JOG_N_0 && nID <= IDC_BTN_JOG_N_3) {	// Jog -
		int ID = nID - IDC_BTN_JOG_N_0;

		pAJinAXL->Jog_Negative(m_nMotionIdx + ID);
	}
	return 0;
}

LRESULT CSetupMotionTabDlg::OnCsLButtonUp(WPARAM wParam, LPARAM lParam)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	UINT nID = (int)wParam;
	if (nID >= IDC_BTN_JOG_P_0 && nID <= IDC_BTN_JOG_P_3) {			// Jog +
		int ID = nID - IDC_BTN_JOG_P_0;
		pAJinAXL->Stop_Motion(m_nMotionIdx + ID);
	} else if (nID >= IDC_BTN_JOG_N_0 && nID <= IDC_BTN_JOG_N_3) {	// Jog -
		int ID = nID - IDC_BTN_JOG_N_0;
		pAJinAXL->Stop_Motion(m_nMotionIdx + ID);
	}
	return 0;
}

void CSetupMotionTabDlg::OnStcMovSpeedClick(UINT nID)
{
	int ID = nID - IDC_STC_MOV_SPEED_0;
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcMovSpeed[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcMovSpeed[ID].SetWindowText(strNew);
	}
}

void CSetupMotionTabDlg::OnStcJogSpeedClick(UINT nID)
{
	int ID = nID - IDC_STC_JOG_SPEED_0;
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcJogSpeed[ID].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcJogSpeed[ID].SetWindowText(strNew);
	}
}

void CSetupMotionTabDlg::OnBtnSaveClick(UINT nID) 
{
	int ID = nID - IDC_BTN_SAVE_0;

	CString strSpeed;
	double dMovSpeed, dJogSpeed;

	m_stcMovSpeed[ID].GetWindowText(strSpeed);
	dMovSpeed = atof(strSpeed);

	m_stcJogSpeed[ID].GetWindowText(strSpeed);
	dJogSpeed = atof(strSpeed);

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	pAJinAXL->Save_MotionParam(m_nMotionIdx + ID, dMovSpeed, dJogSpeed);

	OnBtnCancelClick(ID + IDC_BTN_CANCEL_0);
}

void CSetupMotionTabDlg::OnBtnCancelClick(UINT nID) 
{
	int ID = nID - IDC_BTN_CANCEL_0;

	CString strSpeed;

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	pAJinAXL->Read_MotionParam(m_nMotionIdx + ID);

	AXIS_PARAM *pParam = pAJinAXL->Get_pParam(m_nMotionIdx + ID);
	strSpeed.Format("%0.3lf", pParam->dMovSpeed);
	m_stcMovSpeed[ID].SetWindowText(strSpeed);

	strSpeed.Format("%0.3lf", pParam->dJogSpeed);
	m_stcJogSpeed[ID].SetWindowText(strSpeed);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMotionTabDlg::Initial_Controls() 
{
	m_Group[0].Init_Ctrl("바탕", 12, TRUE, RGB(0x10, 0x50, 0x40), COLOR_DEFAULT);
	for (int i = 1; i < 5; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 0; i < 10; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 10; i < 26; i++) m_Label[i].Init_Ctrl("바탕", 8, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 4; i++) m_stcAxisName[i].Init_Ctrl("바탕", 8, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x00));
	for (int i = 0; i < 4; i++) m_stcAxisPos[i].Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0x00, 0x00), RGB(0xFF, 0xFF, 0xE0));
	for (int i = 0; i < 4; i++) m_stcAxisVel[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xFF, 0xE0));

	for (int i = 0; i < 4; i++) m_ledAxisSOn[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 4; i++) m_ledAxisElp[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 4; i++) m_ledAxisEln[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 4; i++) m_ledAxisAlm[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 4; i++) m_ledAxisInP[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 4; i++) m_ledAxisRun[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 4; i++) m_ledAxisHom[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));

	for (int i = 0; i < 4; i++) m_chkSOn[i].Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0x63, 0x47), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnHome[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x22, 0x8B, 0x22), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_stcAbsDist[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0x00));
	for (int i = 0; i < 4; i++) m_btnAbsMove[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_stcRelDist[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x00, 0xFF, 0x70));
	for (int i = 0; i < 4; i++) m_btnRelMoveP[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnRelMoveN[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnStop[i].Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnReset[i].Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnJogP[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x80, 0x00, 0x80), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnJogN[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x80, 0x00, 0x80), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_stcMovSpeed[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xD0));
	for (int i = 0; i < 4; i++) m_stcJogSpeed[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xEF, 0xD5));

	for (int i = 0; i < 4; i++) m_btnSave[i].Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnCancel[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
}

void CSetupMotionTabDlg::Display_Status()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	CString strPos, strVel;

	int nMaxAxis = 4;//(m_nMotionTab == 4 || m_nMotionTab == 5 || m_nMotionTab == 6 ? 3 : 4);

	//int nMaxAxis = (m_nMotionTab == 1 ? 3 : 4);

	for (int i = 0; i < nMaxAxis; i++) {
		AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(m_nMotionIdx + i);

		strPos.Format("%0.3lf", pStatus->dPos);
		m_stcAxisPos[i].SetWindowText(strPos);

		strVel.Format("%0.3lf", pStatus->dVel);
		m_stcAxisVel[i].SetWindowText(strVel);

		if (pStatus->bSOn) m_ledAxisSOn[i].On();
		else m_ledAxisSOn[i].Off();

		if (pStatus->bELP) m_ledAxisElp[i].On();
		else m_ledAxisElp[i].Off();

		if (pStatus->bELN) m_ledAxisEln[i].On();
		else m_ledAxisEln[i].Off();

		if (pStatus->bALM) m_ledAxisAlm[i].On();
		else m_ledAxisAlm[i].Off();

		if (pStatus->bInP) m_ledAxisInP[i].On();
		else m_ledAxisInP[i].Off();

		if (pStatus->bRun) m_ledAxisRun[i].On();
		else m_ledAxisRun[i].Off();

		if (pStatus->bHom) m_ledAxisHom[i].On();
		else m_ledAxisHom[i].Off();
	}
}

///////////////////////////////////////////////////////////////////////////////

BOOL CSetupMotionTabDlg::Check_Interlock(int nAxis)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();
	DX_DATA_2 *pDX2 = pAJinAXL->Get_pDX2();
	DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();
	DX_DATA_4 *pDX4 = pAJinAXL->Get_pDX4();
	DX_DATA_5 *pDX5 = pAJinAXL->Get_pDX5();

	if (nAxis == AX_LOAD_PICKER_Y1) {
		if (!pCommon->Check_Position(AX_LOAD_PICKER_Z, 0)) {
			AfxMessageBox(_T("Load Picker Z Ready Position 위치후에 진행하세요....."));
			return FALSE;
		}
	}
	if (nAxis == AX_NG_PICKER_X) {
#ifdef NG_PICKER_3
		if (!pDX3->iNGPicker1Up || !pDX3->iNGPicker2Up || !pDX3->iNGPicker3Up ||
			pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down ) {
				AfxMessageBox(_T("NG Picker Z Sylinder Up후에 진행하세요....."));
				return FALSE;
		}
#endif
#ifdef NG_PICKER_4
		if (!pDX3->iNGPicker1Up || !pDX3->iNGPicker2Up || !pDX3->iNGPicker3Up || !pDX3->iNGPicker4Up  ||
			pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down || pDX3->iNGPicker4Down ) {
			AfxMessageBox(_T("NG Picker Z Sylinder Up후에 진행하세요....."));
			return FALSE;
		}
#endif
#ifdef NG_PICKER_5
		if (!pDX3->iNGPicker1Up || !pDX3->iNGPicker2Up || !pDX3->iNGPicker3Up || !pDX3->iNGPicker4Up || !pDX3->iNGPicker5Up ||
			pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down || pDX3->iNGPicker4Down || pDX3->iNGPicker5Down ) {
			AfxMessageBox(_T("NG Picker Z Sylinder Up후에 진행하세요....."));
			return FALSE;
		}
#endif
		if (!pCommon->Check_Position(AX_NG_PICKER_Z, 1) ) {
			AfxMessageBox(_T("NG Picker Z축 NG Position 위치후에 진행하세요....."));
			return FALSE;
		}
	}


	if (nAxis == AX_NG_STAGE_Y)
	{

		if(!(pCommon->Check_Position(AX_NG_PICKER_Z, 1) )) {
			AfxMessageBox(_T("NG Picker Z Axis NG Position 이동후 진행하세요. ...."));
			return FALSE;
		}

#ifdef NG_PICKER_3
		if (!pDX3->iNGPicker1Up || !pDX3->iNGPicker2Up || !pDX3->iNGPicker3Up ||
			pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down ) {
				AfxMessageBox(_T("NG Picker Z Sylinder Up후에 진행하세요....."));
				return FALSE;
		}
#endif
#ifdef NG_PICKER_4
		if (!pDX3->iNGPicker1Up || !pDX3->iNGPicker2Up || !pDX3->iNGPicker3Up || !pDX3->iNGPicker4Up ||
			pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down || pDX3->iNGPicker4Down ) {
				AfxMessageBox(_T("NG Picker Z Sylinder Up후에 진행하세요....."));
				return FALSE;
		}
#endif
#ifdef NG_PICKER_5
		if (!pDX3->iNGPicker1Up || !pDX3->iNGPicker2Up || !pDX3->iNGPicker3Up || !pDX3->iNGPicker4Up || !pDX3->iNGPicker5Up ||
			pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down || pDX3->iNGPicker4Down || pDX3->iNGPicker5Down ) {
			AfxMessageBox(_T("NG Picker Z Sylinder Up후에 진행하세요....."));
			return FALSE;
		}
#endif
	}



	if (nAxis == AX_GOOD_PICKER_Y) 
	{
#ifdef PICKER_3
		if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
			pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down)
#endif
#ifdef PICKER_4
			if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
				!pDX4->iGoodPicker4Up ||
				pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down || 
				pDX4->iGoodPicker4Down )
#endif
#ifdef PICKER_5
		if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
			!pDX4->iGoodPicker4Up || !pDX4->iGoodPicker5Up ||
			pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down || 
			pDX4->iGoodPicker4Down || pDX4->iGoodPicker5Down )
#endif
#ifdef PICKER_6
		if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
			!pDX4->iGoodPicker4Up || !pDX4->iGoodPicker5Up || !pDX4->iGoodPicker6Up ||
			pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down || 
			pDX4->iGoodPicker4Down || pDX4->iGoodPicker5Down || pDX4->iGoodPicker6Down)
#endif
		{
			AfxMessageBox(_T("Good Picker Sylinder Up후 진행하세요............."));
			return FALSE;
		}

		if (!pCommon->Check_Position(AX_GOOD_PICKER_Z, 0) )
		{
			AfxMessageBox(_T("Good Picker Z축 Ready Up 위치후에 진행하세요....."));
			return FALSE;
		}

	}
	if (nAxis == AX_UNLOAD_PICKER_X1) {
		if (!pCommon->Check_Position(AX_UNLOAD_PICKER_Z, 0)) {
			AfxMessageBox(_T("Unload Picker Z Ready Position 위치후에 진행하세요....."));
			return FALSE;
		}
	}
	if (nAxis == AX_INDEX_R) {
		if (pDX2->iInspVacuumUp || !pDX2->iInspVacuumDown) {
			AfxMessageBox(_T("Index Vacuum Down후 진행하세요............."));
			return FALSE;
		}
		if (gData.bUseNGVacuum==TRUE && (pDX5->iNGVacuumUp || !pDX5->iNGVacuumDown)) {
			AfxMessageBox(_T("Index NG Vacuum Down후 진행하세요............."));
			return FALSE;
		}
		if (gData.bUseGDVacuum==TRUE && (pDX5->iGoodVacuumUp || !pDX5->iGoodVacuumDown)) {
			AfxMessageBox(_T("Index Good Vacuum Down후 진행하세요............."));
			return FALSE;
		}

#ifdef NG_PICKER_3
		if (!pDX3->iNGPicker1Up  || !pDX3->iNGPicker2Up  || !pDX3->iNGPicker3Up ||
			pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down ) {
				AfxMessageBox(_T("NG Picker Up후 진행하세요............."));
				return FALSE;
		}
#endif
#ifdef NG_PICKER_4
		if (!pDX3->iNGPicker1Up  || !pDX3->iNGPicker2Up  || !pDX3->iNGPicker3Up || !pDX3->iNGPicker4Up   ||
			pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down || pDX3->iNGPicker4Down  ) {
			AfxMessageBox(_T("NG Picker Up후 진행하세요............."));
			return FALSE;
		}
#endif
#ifdef NG_PICKER_5
		if (!pDX3->iNGPicker1Up  || !pDX3->iNGPicker2Up  || !pDX3->iNGPicker3Up || !pDX3->iNGPicker4Up  || !pDX3->iNGPicker5Up ||
			pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down || pDX3->iNGPicker4Down || pDX3->iNGPicker5Down ) {
			AfxMessageBox(_T("NG Picker Up후 진행하세요............."));
			return FALSE;
		}
#endif

#ifdef PICKER_3
		if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
			pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down )
#endif
#ifdef PICKER_4
			if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
				!pDX4->iGoodPicker4Up ||
				pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down || 
				pDX4->iGoodPicker4Down )
#endif
#ifdef PICKER_5
		if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
			!pDX4->iGoodPicker4Up || !pDX4->iGoodPicker5Up ||
			pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down || 
			pDX4->iGoodPicker4Down || pDX4->iGoodPicker5Down )
#endif
#ifdef PICKER_6
		if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
			!pDX4->iGoodPicker4Up || !pDX4->iGoodPicker5Up || !pDX4->iGoodPicker6Up ||
			pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down || 
			pDX4->iGoodPicker4Down || pDX4->iGoodPicker5Down || pDX4->iGoodPicker6Down)
#endif
		{
			AfxMessageBox(_T("Good Picker Up후 진행하세요............."));
			return FALSE;
		}
		if (!pCommon->Check_Position(AX_LOAD_PICKER_Z, 0)) {
			AfxMessageBox(_T("Load Picker Z Ready Position 위치후에 진행하세요....."));
			return FALSE;
		}
		if (!pCommon->Check_Position(AX_UNLOAD_PICKER_Z, 0)) {
			AfxMessageBox(_T("Unload Picker Z Ready Position 위치후에 진행하세요....."));
			return FALSE;
		}
		if (!pDX2->iInspCMAlign1In || pDX2->iInspCMAlign1Out || !pDX2->iInspCMAlign2In || pDX2->iInspCMAlign2Out || 
			!pDX2->iInspCMAlign3In || pDX2->iInspCMAlign3Out || !pDX2->iInspCMAlign4In || pDX2->iInspCMAlign4Out ) {
			AfxMessageBox(_T("Index Align 1~4 In후 진행하세요............."));
			return FALSE;
		}
		if (gData.bUseCMPress) {
			if (!pDX2->iCMPressUp || pDX2->iCMPressDn) {
				AfxMessageBox(_T("CM Press Block Up후에 진행하세요....."));
				return FALSE;
			}
		}
	}

	if (nAxis == AX_LOAD_TRAY_X1)
	{
		if(!pCommon->Check_Position(AX_LOAD_PICKER_Z, 0))
		{
			AfxMessageBox(_T("Load Picker Z Ready Up으로 이동후 진행하세요......."));
			return FALSE;
		}	


		if((pCommon->Check_Position(AX_LOAD_TRAY_Z1, 0) && pCommon->Check_Position(AX_LOAD_TRAY_Z2, 1))
			|| (pCommon->Check_Position(AX_LOAD_TRAY_Z1, 1) && pCommon->Check_Position(AX_LOAD_TRAY_Z2, 0)))
		{
			//pass
		}
		else
		{
			AfxMessageBox(_T("Load Tray Z축 위치 확인하세요 (Up & Down)"));
			return FALSE;
		}

		double dPosZ1 = pAJinAXL->Get_pStatus(AX_LOAD_TRAY_Z1)->dPos;
		double dPosZ2 = pAJinAXL->Get_pStatus(AX_LOAD_TRAY_Z2)->dPos;

		if( abs(dPosZ1 -dPosZ2) < 60 )
		{
			AfxMessageBox(_T("Load Tray Z축 단차 확인하세요."));
			return FALSE;
		}				
	}

	if (nAxis == AX_LOAD_TRAY_X2) 
	{
		if(!pCommon->Check_Position(AX_LOAD_PICKER_Z, 0))
		{
			AfxMessageBox(_T("Load Picker Z Ready Up으로 이동후 진행하세요......."));
			return FALSE;
		}	

		if((pCommon->Check_Position(AX_LOAD_TRAY_Z1, 0) && pCommon->Check_Position(AX_LOAD_TRAY_Z2, 1))
			|| (pCommon->Check_Position(AX_LOAD_TRAY_Z1, 1) && pCommon->Check_Position(AX_LOAD_TRAY_Z2, 0)))
		{
			//pass
		}
		else
		{
			AfxMessageBox(_T("Load Tray Z축 위치 확인하세요 (Up & Down)"));
			return FALSE;
		}

		double dPosZ1 = pAJinAXL->Get_pStatus(AX_LOAD_TRAY_Z1)->dPos;
		double dPosZ2 = pAJinAXL->Get_pStatus(AX_LOAD_TRAY_Z2)->dPos;

		if( abs(dPosZ1 -dPosZ2) < 60 )
		{
			AfxMessageBox(_T("Load Tray Z축 단차 확인하세요."));
			return FALSE;
		}		


		
	}

	if (nAxis == AX_UNLOAD_TRAY_Y1) 
	{
		if(!pCommon->Check_Position(AX_UNLOAD_PICKER_Z, 0))
		{
			AfxMessageBox(_T("Unload Picker Z Ready Up으로 이동후 진행하세요......."));
			return FALSE;
		}

		if((pCommon->Check_Position(AX_UNLOAD_TRAY_Z1, 0) && pCommon->Check_Position(AX_UNLOAD_TRAY_Z2, 1))
			|| (pCommon->Check_Position(AX_UNLOAD_TRAY_Z1, 1) && pCommon->Check_Position(AX_UNLOAD_TRAY_Z2, 0)))
		{
			//pass
		}
		else
		{
			AfxMessageBox(_T("Unload Tray Z축 위치 확인하세요 (Up & Down)"));
			return FALSE;
		}

		double dPosZ1 = pAJinAXL->Get_pStatus(AX_UNLOAD_TRAY_Z1)->dPos;
		double dPosZ2 = pAJinAXL->Get_pStatus(AX_UNLOAD_TRAY_Z2)->dPos;

		if( abs(dPosZ1 -dPosZ2) < 60 )
		{
			AfxMessageBox(_T("Unload Tray Z축 단차 확인하세요."));
			return FALSE;
		}			
	}

	if (nAxis == AX_UNLOAD_TRAY_Y2)
	{
		if(!pCommon->Check_Position(AX_UNLOAD_PICKER_Z, 0))
		{
			AfxMessageBox(_T("Unload Picker Z Ready Up으로 이동후 진행하세요......."));
			return FALSE;
		}	

		if((pCommon->Check_Position(AX_UNLOAD_TRAY_Z1, 0) && pCommon->Check_Position(AX_UNLOAD_TRAY_Z2, 1))
			|| (pCommon->Check_Position(AX_UNLOAD_TRAY_Z1, 1) && pCommon->Check_Position(AX_UNLOAD_TRAY_Z2, 0)))
		{
			//pass
		}
		else
		{
			AfxMessageBox(_T("Unload Tray Z축 위치 확인하세요 (Up & Down)"));
			return FALSE;
		}

		double dPosZ1 = pAJinAXL->Get_pStatus(AX_UNLOAD_TRAY_Z1)->dPos;
		double dPosZ2 = pAJinAXL->Get_pStatus(AX_UNLOAD_TRAY_Z2)->dPos;

		if( abs(dPosZ1 -dPosZ2) < 60 )
		{
			AfxMessageBox(_T("Unload Tray Z축 단차 확인하세요."));
			return FALSE;
		}		
	}
	return TRUE;

	
}