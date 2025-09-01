// SetupMoveDlg.h : ��� ����
//
#pragma once

#include "SetupMoveTab1Dlg.h"
#include "SetupMoveTab2Dlg.h"
#include "SetupMoveTab3Dlg.h"
#include "SetupMoveTab4Dlg.h"

// CSetupMoveDlg ��ȭ �����Դϴ�.

class CSetupMoveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveDlg)

public:
	CSetupMoveDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetupMoveDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETUP_MOVE_DLG };
	CTabCS		m_tabSetupMove;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTcnSelchangingTabSetupMove(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabSetupMove(NMHDR *pNMHDR, LRESULT *pResult);

public:
	CSetupMoveTab1Dlg *m_pSetupMoveTab1Dlg;
	CSetupMoveTab2Dlg *m_pSetupMoveTab2Dlg;
	CSetupMoveTab3Dlg *m_pSetupMoveTab3Dlg;
	CSetupMoveTab4Dlg *m_pSetupMoveTab4Dlg;

private:
	void Initial_Controls();
};

///////////////////////////////////////////////////////////////////////////////
