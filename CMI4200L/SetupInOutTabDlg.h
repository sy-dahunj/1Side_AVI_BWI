// SetupInOutTabDlg.h : ��� ����
//
#pragma once

// CSetupInOutTabDlg ��ȭ �����Դϴ�.

class CSetupInOutTabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupInOutTabDlg)

public:
	CSetupInOutTabDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetupInOutTabDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETUP_IN_OUT_TAB_DLG };
	CGroupCS	m_Group[2];
	CStaticCS	m_stcIn[32];
	CCheckCS	m_chkOut[32];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChkOutClick(UINT nID);	// IDC_CHK_OUT_XX Click

private:
	int m_nInOutTab;

private:
	void Initial_Controls();
	void Set_CheckBox(int nIdx, BOOL bChk);
	void Set_Output(int nIdx, BOOL bOut);

public:
	void Set_InOutTab(int nTab) { m_nInOutTab = nTab; }
	void Display_Status();
};

///////////////////////////////////////////////////////////////////////////////
