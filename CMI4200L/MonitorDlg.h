// MonitorDlg.h : ��� ����
//
#pragma once

#include "MonitorMotionDlg.h"
#include "MonitorInOutDlg.h"
#include "MonitorLogDlg.h"

// CMonitorDlg ��ȭ �����Դϴ�.

class CMonitorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMonitorDlg)

private:
	static CMonitorDlg *m_pInstance;

public:
	static CMonitorDlg *Get_Instance(CWnd *pParent = NULL);
	void Delete_Instance();

public:
	CMonitorDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMonitorDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MONITOR_DLG };
	CPictureCS	m_picMonitorBack;
	CRadioCS	m_rdoMonitorMotion;
	CRadioCS	m_rdoMonitorInOut;
	CRadioCS	m_rdoMonitorLog;
	CButtonCS	m_btnMonitorClose;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRdoMonitorMotion();
	afx_msg void OnBnClickedRdoMonitorInOut();
	afx_msg void OnBnClickedRdoMonitorLog();
	afx_msg void OnBnClickedBtnMonitorClose();

public:
	CMonitorMotionDlg	*m_pMonitorMotionDlg;
	CMonitorInOutDlg	*m_pMonitorInOutDlg;
	CMonitorLogDlg		*m_pMonitorLogDlg;

private:
	void Initial_Controls();
	void Hide_Windows();
};

///////////////////////////////////////////////////////////////////////////////
