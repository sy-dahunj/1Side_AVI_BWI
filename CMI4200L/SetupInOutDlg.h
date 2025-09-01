// SetupInOutDlg.h : ��� ����
//
#pragma once

#include "SetupInOutTabDlg.h"

// CSetupInOutDlg ��ȭ �����Դϴ�.

class CSetupInOutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupInOutDlg)

public:
	CSetupInOutDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetupInOutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETUP_IN_OUT_DLG };
	CTabCS		m_tabSetupInOut;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTcnSelchangingTabSetupInOut(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabSetupInOut(NMHDR *pNMHDR, LRESULT *pResult);

public:
	CSetupInOutTabDlg *m_pSetupInOutTabDlg;

private:
	void Initial_Controls();

public:
	void Display_Status();
};

///////////////////////////////////////////////////////////////////////////////
