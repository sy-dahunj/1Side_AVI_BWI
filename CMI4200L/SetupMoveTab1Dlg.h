// SetupMoveTab1Dlg.h : ��� ����
//
#pragma once
#include "cscontrols.h"

// CSetupMoveTab1Dlg ��ȭ �����Դϴ�.

class CSetupMoveTab1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab1Dlg)

public:
	CSetupMoveTab1Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetupMoveTab1Dlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETUP_MOVE_TAB1_DLG };
	CGroupCS	m_Group[6];
	CLabelCS	m_Label[44];
	CButtonCS	m_btnSave;
	CButtonCS	m_btnCancel;

	CStaticCS	m_stcShuttleX[5];		//Load Tray X1
	CStaticCS	m_stcLoadTrayTR1Z[5];	//Load Tray X2
	CStaticCS	m_stcLoadTrayTR2Y[4];	//Load Tray Z1
	CStaticCS	m_stcVisionX[4];		//Load Tray Z2
	CStaticCS	m_stcLoadTrayTR1Y[7];	//Load Picker Y12
	CStaticCS	m_stcLoadTrayTR2Z[4];	//Load Picker Z


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnCancel();

	//CMI3000
	afx_msg void OnStcSuttleXClick(UINT nID);					//IDC_STC_SHUTTLE_X_0
	afx_msg void OnStcloadTrayTR1YClick(UINT nID);				//IDC_STC_LOAD_TRAY_TR_1_Y_0
	afx_msg void OnStcloadTrayTR1ZClick(UINT nID);				//IDC_STC_LOAD_TRAY_TR_1_Z_0
	afx_msg void OnStcloadTrayTR2YClick(UINT nID);				//IDC_STC_LOAD_TRAY_TR_2_Y_0
	afx_msg void OnStcloadTrayTR2ZClick(UINT nID);				//IDC_STC_LOAD_TRAY_TR_2_Z_0
	afx_msg void OnStcVisionXClick(UINT nID);					//IDC_STC_VISION_X_0

private:
	void Initial_Controls();
	void Display_MoveData();
};

///////////////////////////////////////////////////////////////////////////////
