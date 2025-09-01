// KeyPadDlg.h : 헤더 파일
//
#pragma once

// CKeyPadDlg 대화 상자입니다.

extern CString g_strReturnKeyPad;

class CKeyPadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKeyPadDlg)

public:
	CKeyPadDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CKeyPadDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_KEY_PAD_DLG };
	CLabelCS	m_Label;
	CStaticCS	m_stcKeyName;
	CButtonCS	m_btnClear;
	CButtonCS	m_btnDel;
	CButtonCS	m_btnKey[38];
	CButtonCS	m_btnOK;
	CButtonCS	m_btnCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
