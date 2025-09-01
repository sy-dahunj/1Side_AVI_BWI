// SetupMoveTab2Dlg.h : ��� ����
//
#pragma once

// CSetupMoveTab2Dlg ��ȭ �����Դϴ�.

class CSetupMoveTab2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab2Dlg)

public:
	CSetupMoveTab2Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetupMoveTab2Dlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETUP_MOVE_TAB2_DLG };
	CGroupCS	m_Group[5];
	CLabelCS	m_Label[16];

	CStaticCS	m_stcInspectTrayTRX[8];	//Index R
	CStaticCS	m_stcCover2Z[1];		//Barcode A
	CStaticCS	m_stcInspectTrayTRR[1];	//Inspection A
	CStaticCS	m_stcCover1Z[2];		//Inspection Z
	CStaticCS	m_stcNGStageY[4];		//NG Stage Y

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

	afx_msg void OnStcCover1ZYClick(UINT nID);				// IDC_STC_COVER_1_Z_0 Click
	afx_msg void OnStcCover2ZClick(UINT nID);				// IDC_STC_COVER_2_Z_0 Click
	afx_msg void OnStcInspectTrayTRXClick(UINT nID);		// IDC_STC_INSPECT_TRAY_TR_X_0 Click
	afx_msg void OnStcInspectTrayTRRClick(UINT nID);		// IDC_STC_INSPECT_TRAY_TR_R_0 Click
	afx_msg void OnstcNGStageYClick(UINT nID);

private:
	void Initial_Controls();
	void Display_MoveData();
};

///////////////////////////////////////////////////////////////////////////////
