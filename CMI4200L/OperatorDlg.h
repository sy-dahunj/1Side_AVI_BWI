// OperatorDlg.h : 헤더 파일
//
#pragma once

// COperatorDlg 대화 상자입니다.

class COperatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COperatorDlg)

private:
	static COperatorDlg *m_pInstance;

public:
	static COperatorDlg *Get_Instance(CWnd *pParent = NULL);
	void Delete_Instance();

public:
	COperatorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COperatorDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_OPERATOR_DLG };
	CPictureCS	m_Image;
	CStaticCS	m_stcEqpName;
	CStaticCS	m_stcDate;
	CStaticCS	m_stcTime;
	CStaticCS	m_stcVer;
	CPictureCS	m_picOperImg[11];
	CLabelCS	m_Label[40];
	CButtonCS	m_btnOperInitial;
	CButtonCS	m_btnOperWork;
	CButtonCS	m_btnOperManual;
	CButtonCS	m_btnOperSetup;
	CButtonCS	m_btnOperMonitor;
	CButtonCS	m_btnOperExit;
	CButtonCS	m_btnOperStart;
	CButtonCS	m_btnOperStop;
	CButtonCS	m_btnOperTray;
	CButtonCS	m_btnOperCleanOut;
	CButtonCS	m_btnOperEngineer;

	CStaticCS	m_stcOperLotID;
	CStaticCS	m_stcOperOperID;
	CStaticCS	m_stcOperCMCnt;

	CGridCS		m_grdData[2];
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnOperInitial();
	afx_msg void OnBnClickedBtnOperWork();
	afx_msg void OnBnClickedBtnOperManual();
	afx_msg void OnBnClickedBtnOperSetup();
	afx_msg void OnBnClickedBtnOperMonitor();
	afx_msg void OnBnClickedBtnOperExit();
	afx_msg void OnBnClickedBtnOperStart();
	afx_msg void OnBnClickedBtnOperStop();
	afx_msg void OnBnClickedBtnOperTray();
	afx_msg void OnBnClickedBtnOperCleanOut();
	afx_msg void OnBnClickedBtnOperEngineer();
	afx_msg void OnBnClickedBtnOperTest();

	afx_msg void OnBnClickedLotID();
	afx_msg void OnBnClickedCMCnt();
	afx_msg void OnBnClickedOperID();

private:
	CBitmap	m_bmpImage;

private:
	void Initial_Controls();
	void Display_Status();
	void Initial_Grid(CGridCS *pGrid, int nRows, int nCols);

public:
	void Hide_Windows();
	void Enable_ModeButton(BOOL bEnable, BOOL bOpMode);
};

///////////////////////////////////////////////////////////////////////////////
