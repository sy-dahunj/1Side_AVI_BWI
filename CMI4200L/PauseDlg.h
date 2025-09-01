// PauseDlg.h : ��� ����
//
#pragma once

// CPauseDlg ��ȭ �����Դϴ�.

class CPauseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPauseDlg)

public:
	CPauseDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPauseDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PAUSE_DLG };
	CStaticCS	m_stcPauseTitle;
	CStaticCS	m_stcPauseMessage;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	CBrush	m_brushBack;
	void Initial_Controls();
};

extern CPauseDlg g_dlgPause;

///////////////////////////////////////////////////////////////////////////////
