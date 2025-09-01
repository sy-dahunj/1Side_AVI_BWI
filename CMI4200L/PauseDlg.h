// PauseDlg.h : 헤더 파일
//
#pragma once

// CPauseDlg 대화 상자입니다.

class CPauseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPauseDlg)

public:
	CPauseDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPauseDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PAUSE_DLG };
	CStaticCS	m_stcPauseTitle;
	CStaticCS	m_stcPauseMessage;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
