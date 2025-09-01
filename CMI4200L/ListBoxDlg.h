// ListBoxDlg.h : ��� ����
//
#pragma once

// CListBoxDlg ��ȭ �����Դϴ�.

class CListBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListBoxDlg)

public:
	CListBoxDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CListBoxDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LIST_BOX_DLG };
	CButtonCS	m_btnOK;
	CButtonCS	m_btnCancel;
	CListCS		m_lstLotList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLbnSelchangeLstList();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	int	m_nDCnt;
	void Initial_Controls();

public:
	void Display_List();
};

///////////////////////////////////////////////////////////////////////////////
