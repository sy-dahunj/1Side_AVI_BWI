#pragma once


// CManualLoadTrayDlg 대화 상자입니다.

class CManualLoadTrayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualLoadTrayDlg)

public:
	CManualLoadTrayDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualLoadTrayDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_LOADING_DLG };
	CStaticCS	m_stcAxisPos[4];
	CButtonCS	m_btnTR1Y[3];
	CButtonCS	m_btnTR1Z[4];
	CButtonCS	m_btnTR2Y[3];
	CButtonCS	m_btnTR2Z[4];

	CButtonCS	m_btnTR1IO[6];
	CButtonCS	m_btnShuttleIO[2];
	CButtonCS	m_btnTR2IO[6];
	CButtonCS	m_btnShuttleIO2[2];

	CLedCS		m_ledTR1[6];
	CLedCS		m_ledTR2[6];
	CLedCS		m_ledShuttle[6];
	CLedCS		m_ledShuttle2[6];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnBtnShuttleIOClick(UINT nID);
	afx_msg void OnBtnShuttleIO2Click(UINT nID);
	afx_msg void OnBtnTR1YClick(UINT nID);
	afx_msg void OnBtnTR1ZClick(UINT nID);
	afx_msg void OnBtnTR1IOClick(UINT nID);
	afx_msg void OnBtnTR2YClick(UINT nID);
	afx_msg void OnBtnTR2ZClick(UINT nID);
	afx_msg void OnBtnTR2IOClick(UINT nID);

private:
	void Initial_Controls();

public:
	void Display_Status();

};
