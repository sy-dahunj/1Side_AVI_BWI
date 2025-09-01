// SetupMotionTabDlg.h : 헤더 파일
//
#pragma once

// CSetupMotionTabDlg 대화 상자입니다.

class CSetupMotionTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMotionTabDlg)

public:
	CSetupMotionTabDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMotionTabDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOTION_TAB_DLG };
	CGroupCS	m_Group[5];
	CLabelCS	m_Label[26];
	CStaticCS	m_stcAxisName[4];
	CStaticCS	m_stcAxisPos[4];
	CStaticCS	m_stcAxisVel[4];
	CLedStatic	m_ledAxisSOn[4];
	CLedStatic	m_ledAxisElp[4];
	CLedStatic	m_ledAxisEln[4];
	CLedStatic	m_ledAxisAlm[4];
	CLedStatic	m_ledAxisInP[4];
	CLedStatic	m_ledAxisRun[4];
	CLedStatic	m_ledAxisHom[4];
	CCheckCS	m_chkSOn[4];
	CButtonCS	m_btnHome[4];
	CStaticCS	m_stcAbsDist[4];
	CButtonCS	m_btnAbsMove[4];
	CStaticCS	m_stcRelDist[4];
	CButtonCS	m_btnRelMoveP[4];
	CButtonCS	m_btnRelMoveN[4];
	CButtonCS	m_btnStop[4];
	CButtonCS	m_btnReset[4];
	CButtonCS	m_btnJogP[4];
	CButtonCS	m_btnJogN[4];
	CStaticCS	m_stcMovSpeed[4];
	CStaticCS	m_stcJogSpeed[4];
	CButtonCS	m_btnSave[4];
	CButtonCS	m_btnCancel[4];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChkSOnClick(UINT nID);		// IDC_CHK_S_ON_X Click
	afx_msg void OnBtnHomeClick(UINT nID);		// IDC_BTN_HOME_X Click
	afx_msg void OnStcAbsDistClick(UINT nID);	// IDC_STC_ABS_DIST_X Click
	afx_msg void OnBtnAbsMoveClick(UINT nID);	// IDC_BTN_ABS_MOVE_X Click
	afx_msg void OnStcRelDistClick(UINT nID);	// IDC_STC_REL_DIST_X Click
	afx_msg void OnBtnRelMovePClick(UINT nID);	// IDC_BTN_REL_MOVE_P_X Click
	afx_msg void OnBtnRelMoveNClick(UINT nID);	// IDC_BTN_REL_MOVE_N_X Click
	afx_msg void OnBtnStopClick(UINT nID);		// IDC_BTN_STOP_X Click
	afx_msg void OnBtnResetClick(UINT nID);		// IDC_BTN_STOP_X Click
	afx_msg LRESULT OnCsLButtonDown(WPARAM wParam, LPARAM lParam);	// CS Button Down
	afx_msg LRESULT OnCsLButtonUp(WPARAM wParam, LPARAM lParam);	// CS Button Up
	afx_msg void OnStcMovSpeedClick(UINT nID);	// IDC_STC_MOV_SPEED_X Click
	afx_msg void OnStcJogSpeedClick(UINT nID);	// IDC_STC_JOG_SPEED_X Click
	afx_msg void OnBtnSaveClick(UINT nID);		// IDC_BTN_SAVE_X Click
	afx_msg void OnBtnCancelClick(UINT nID);	// IDC_BTN_CANCEL_X Click

private:
	int m_nMotionTab;
	int m_nMotionIdx;

private:
	void Initial_Controls();

public:
	void Set_MotionTab(int nTab) { m_nMotionTab = nTab; }
	void Set_MotionIdx(int nIdx) { m_nMotionIdx = nIdx; }
	void Display_Status();
	BOOL Check_Interlock(int nAxis);
};

///////////////////////////////////////////////////////////////////////////////
