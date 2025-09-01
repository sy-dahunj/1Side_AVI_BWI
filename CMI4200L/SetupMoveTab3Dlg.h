// SetupMoveTab3Dlg.h : ��� ����
//
#pragma once
#include "cscontrols.h"

// CSetupMoveTab3Dlg ��ȭ �����Դϴ�.

class CSetupMoveTab3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab3Dlg)

public:
	CSetupMoveTab3Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetupMoveTab3Dlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETUP_MOVE_TAB3_DLG };
	CGroupCS	m_Group[4];
	CLabelCS	m_Label[35];

	CStaticCS	m_stcNGPickerX[8];
	CStaticCS	m_stcNGPickerZ[7];
	CStaticCS	m_stcGOODPickerY[7];
	CStaticCS	m_stcGOODPickerZ[13];

	CButtonCS	m_btnSave;
	CButtonCS	m_btnCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnCancel();


	afx_msg void OnStcNGPickerXClick(UINT nID);			// IDC_STC_NG_PICKER_X_0 Click
	afx_msg void OnStcNGPickerZClick(UINT nID);			// IDC_STC_NG_PICKER_Z_0 Click
	afx_msg void OnStcGOODPickerYClick(UINT nID);	    // IDC_STC_GOOD_PICKER_Y_0 Click
	afx_msg void OnStcGOODPickerZClick(UINT nID);	    // IDC_STC_GOOD_PICKER_Z_0 Click

private:
	void Initial_Controls();
	void Display_MoveData();
public:
	afx_msg void OnBnClickedGroup0();
};

///////////////////////////////////////////////////////////////////////////////
