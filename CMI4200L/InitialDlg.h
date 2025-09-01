// InitialDlg.h : 헤더 파일
//
#pragma once

// CInitialDlg 대화 상자입니다.

class CInitialDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInitialDlg)

private:
	static CInitialDlg *m_pInstance;

public:
	static CInitialDlg *Get_Instance(CWnd *pParent = NULL);
	void Delete_Instance();

public:
	CInitialDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInitialDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_INITIAL_DLG };
	CGroupCS	m_Group[5];
	CLabelCS	m_Label[12];
	CStaticCS	m_stcAxisName[27];  //KTY 25
	CLedStatic	m_ledAxisRun[27];
	CLedStatic	m_ledAxisHom[27];
	CLedStatic	m_ledInitOK;
	CStaticCS	m_stcInitCase[7];
	CPictureCS	m_Image[3];
	CPictureCS	m_picInitFlow[9];
	CStaticCS	m_stcInitFlow[9];
	CRadioCS	m_rdoInitStart;
	CRadioCS	m_rdoInitStop;
	CStaticCS	m_stcInitStripSize;
	CLedCS		m_ledMainAir[4];
	CLedCS		m_ledMainDoor[8];
	CLedCS		m_ledBuffDoor;
	CLedCS		m_ledLowerDoor[4];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRdoInitStart();
	afx_msg void OnBnClickedRdoInitStop();
	afx_msg void OnBnClickedChkMotionTest();
	afx_msg void OnBnClickedMesTest1();
	afx_msg void OnBnClickedMesTest2();

private:
	CBitmap		m_bmpImage[3];

	int		m_nBackColorLoop;
	BOOL	m_bInitialRunning;

	void Initial_Controls();
	void Display_Status();
	void Display_Initial();
	void Set_StatusColor(int nIdx, int nColor);	// nColor : 0:White,1:Red,2:Green,3:Blue

public:
	afx_msg void OnBnClickedMesTest3();
	afx_msg void OnBnClickedMesTest4();
	void LogAllDelete();
	void LogFileDelete(CString sPath);

};

///////////////////////////////////////////////////////////////////////////////
