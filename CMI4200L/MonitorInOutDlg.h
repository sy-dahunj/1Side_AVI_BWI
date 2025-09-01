// MonitorInOutDlg.h : ��� ����
//
#pragma once

#include "MonitorInOutTabDlg.h"

// CMonitorInOutDlg ��ȭ �����Դϴ�.

class CMonitorInOutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMonitorInOutDlg)

public:
	CMonitorInOutDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMonitorInOutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MONITOR_IN_OUT_DLG };
	CTabCS		m_tabMonitorInOut;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTcnSelchangingTabMonitorInOut(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabMonitorInOut(NMHDR *pNMHDR, LRESULT *pResult);

public:
	CMonitorInOutTabDlg *m_pMonitorInOutTabDlg;

private:
	void Initial_Controls();

public:
	void Display_Status();
};

///////////////////////////////////////////////////////////////////////////////
