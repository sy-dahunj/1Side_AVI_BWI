// MonitorLogDlg.h : ��� ����
//
#pragma once

// CMonitorLogDlg ��ȭ �����Դϴ�.

class CMonitorLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMonitorLogDlg)

public:
	CMonitorLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMonitorLogDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MONITOR_LOG_DLG };
	CGroupCS		m_Group[2];
	CLabelCS		m_Label;
	CRichEditCtrl	m_redtLogDisplay;
	CStaticCS		m_stcLogDate;
	CButtonCS		m_btnGoToday;
	CMonthCalCtrl	m_calMonth;
	CRadioCS		m_rdoLogAlarm;
	CRadioCS		m_rdoLogJobList;
	CRadioCS		m_rdoLogHandler;
	CRadioCS		m_rdoLogInspector;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnGoToday();
	afx_msg void OnMcnSelchangeCalMonth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRdoLogAlarm();
	afx_msg void OnBnClickedRdoLogJobList();
	afx_msg void OnBnClickedRdoLogHandler();
	afx_msg void OnBnClickedRdoLogInspector();

private:
	CFont	m_fontCalendar;
	CFont	m_fontREdit;

private:
	void Initial_Controls();		

protected:
	static DWORD CALLBACK StreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	void Read_LogFile();
};

///////////////////////////////////////////////////////////////////////////////
