// NumPadDlg.h : ��� ����
//
#pragma once

// CNumPadDlg ��ȭ �����Դϴ�.

extern CString g_strReturnNumPad;

class CNumPadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNumPadDlg)

public:
	CNumPadDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNumPadDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NUM_PAD_DLG };
	CLabelCS	m_Label[2];
	CStaticCS	m_stcOldValue;
	CStaticCS	m_stcNewValue;
	CButtonCS	m_btnClear;
	CButtonCS	m_btnNum[10];
	CButtonCS	m_btnDot;
	CButtonCS	m_btnMinus;
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
	afx_msg void OnBtnNumClick(UINT nID);	// IDC_BTN_NUM_X Click
	afx_msg void OnBnClickedBtnDot();
	afx_msg void OnBnClickedBtnMinus();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();

private:
	CString		m_strOldValue;
	CString		m_strNewValue; 
	CBrush		m_brushBack;

private:
	void Initial_Controls();

public:
	void Set_OldValue(CString sOld);
};

///////////////////////////////////////////////////////////////////////////////
