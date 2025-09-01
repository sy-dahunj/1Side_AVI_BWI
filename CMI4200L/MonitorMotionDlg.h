// MonitorMotionDlg.h : ��� ����
//
#pragma once

#include "MonitorMotionTabDlg.h"

// CMonitorMotionDlg ��ȭ �����Դϴ�.

class CMonitorMotionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMonitorMotionDlg)

public:
	CMonitorMotionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMonitorMotionDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MONITOR_MOTION_DLG };
	CTabCS		m_tabMonitorMotion;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTcnSelchangingTabMonitorMotion(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabMonitorMotion(NMHDR *pNMHDR, LRESULT *pResult);

public:
	CMonitorMotionTabDlg *m_pMonitorMotionTabDlg;

private:
	void Initial_Controls();

public:
	void Display_Status();
};

///////////////////////////////////////////////////////////////////////////////
