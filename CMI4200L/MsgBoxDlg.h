// MsgBoxDlg.h : ��� ����
//
#pragma once

// CMsgBoxDlg ��ȭ �����Դϴ�.

class CMsgBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMsgBoxDlg)

public:
	CMsgBoxDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMsgBoxDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MSG_BOX_DLG };
	CStaticCS	m_stcMsg;
	CButtonCS	m_btnOneOK;
	CButtonCS	m_btnTwoOK;
	CButtonCS	m_btnTwoCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnOneOk();
	afx_msg void OnBnClickedBtnTwoOk();
	afx_msg void OnBnClickedBtnTwoCancel();

private:
	CBrush		m_brushBack;
	int			m_nBtnCnt;
	CString		m_strMsg;
	int			m_nCount;

	void Initial_Controls();

public:
	void Set_Message(int nBtnCnt, CString strMsg);
};

///////////////////////////////////////////////////////////////////////////////
