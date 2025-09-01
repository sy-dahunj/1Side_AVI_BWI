// MonitorMotionTabDlg.cpp : 구현 파일입니다.
//
#pragma once

// CMonitorMotionTabDlg 대화 상자입니다.

class CMonitorMotionTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMonitorMotionTabDlg)

public:
	CMonitorMotionTabDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMonitorMotionTabDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_MONITOR_MOTION_TAB_DLG };
	CGroupCS	m_Group;
	CLabelCS	m_Label[10];
	CStaticCS	m_stcAxisName[9];
	CStaticCS	m_stcAxisPos[9];
	CStaticCS	m_stcAxisVel[9];
	CLedCS		m_ledAxisSOn[9];
	CLedCS		m_ledAxisElp[9];
	CLedCS		m_ledAxisEln[9];
	CLedCS		m_ledAxisAlm[9];
	CLedCS		m_ledAxisInP[9];
	CLedCS		m_ledAxisRun[9];
	CLedCS		m_ledAxisHom[9];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

private:
	int m_nMotionTab;

private:
	void Initial_Controls();

public:
	void Set_MotionTab(int nTab) { m_nMotionTab = nTab; }
	void Display_Status();
};

///////////////////////////////////////////////////////////////////////////////
