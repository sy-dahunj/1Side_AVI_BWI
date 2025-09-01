// MonitorInOutTabDlg.h : ��� ����
//
#pragma once

// CMonitorInOutTabDlg ��ȭ �����Դϴ�.

class CMonitorInOutTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMonitorInOutTabDlg)

public:
	CMonitorInOutTabDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMonitorInOutTabDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MONITOR_IN_OUT_TAB_DLG };
	CGroupCS	m_Group[2];
	CLedCS		m_ledIn[32];
	CLedCS		m_ledOut[32];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

private:
	int m_nInOutTab;

private:
	void Initial_Controls();

public:
	void Set_InOutTab(int nTab) { m_nInOutTab = nTab; }
	void Display_Status();
};

///////////////////////////////////////////////////////////////////////////////
