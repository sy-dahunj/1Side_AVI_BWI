// KeyPadDlg.h : ��� ����
//
#pragma once

// CKeyPadDlg ��ȭ �����Դϴ�.

extern CString g_strReturnKeyPad;

class CKeyPadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKeyPadDlg)

public:
	CKeyPadDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CKeyPadDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_KEY_PAD_DLG };
	CLabelCS	m_Label;
	CStaticCS	m_stcKeyName;
	CButtonCS	m_btnClear;
	CButtonCS	m_btnDel;
	CButtonCS	m_btnKey[38];
	CButtonCS	m_btnOK;
	CButtonCS	m_btnCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBtnKeyClick(UINT nID);	// IDC_BTN_KEY_XX Click
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();

private:
	CBrush	m_brushBack;
	void Initial_Controls();
};

///////////////////////////////////////////////////////////////////////////////
