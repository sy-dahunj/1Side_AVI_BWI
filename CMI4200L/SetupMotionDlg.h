// SetupMotionDlg.h : ��� ����
//
#pragma once

#include "SetupMotionTabDlg.h"

// CSetupMotionDlg ��ȭ �����Դϴ�.

class CSetupMotionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMotionDlg)

public:
	CSetupMotionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetupMotionDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETUP_MOTION_DLG };
	CTabCS		m_tabSetupMotion;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTcnSelchangingTabSetupMotion(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabSetupMotion(NMHDR *pNMHDR, LRESULT *pResult);

public:
	CSetupMotionTabDlg *m_pSetupMotionTabDlg;

private:
	void Initial_Controls();

public:
	void Display_Status();
};

///////////////////////////////////////////////////////////////////////////////
