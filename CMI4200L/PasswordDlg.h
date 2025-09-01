// PasswordDlg.h : ��� ����
//
#pragma once

// CPasswordDlg ��ȭ �����Դϴ�.

class CPasswordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPasswordDlg)

public:
	CPasswordDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPasswordDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PASSWORD_DLG };
	CEditCS		m_edtPassword;
	CButtonCS	m_btnPassNum[10];
	CButtonCS	m_btnOK;
	CButtonCS	m_btnCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnPassNumClick(UINT nID);	// IDC_BTN_NUM_X Click
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();

private:
	CBrush	m_brushBack;

private:
	void Initial_Controls();
};

///////////////////////////////////////////////////////////////////////////////
