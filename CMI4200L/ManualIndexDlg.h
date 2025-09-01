// ManualIndexDlg.h : 헤더 파일
//
#pragma once

// CManualIndexDlg 대화 상자입니다.

class CManualIndexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualIndexDlg)

public:
	CManualIndexDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualIndexDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_ELEVATOR_DLG };
	CStaticCS	m_stcAxisPos[6];
	CButtonCS	m_btnVisionY[8];
	CButtonCS	m_btnVisionA[1];
	CButtonCS	m_btnVisionZ[2];
	CButtonCS	m_btnBarcodeA[1];
	CButtonCS	m_btnNGStageY[3];
	CButtonCS	m_btnTRIO[16];
	CButtonCS	m_btnVacIO[14];
	CButtonCS	m_btnNGVacIO[14];
	CButtonCS	m_btnGDVacIO[14];
	CButtonCS	m_btnBlock[2];

	CLedCS		m_ledTRIO[19];
	CLedCS		m_ledVacIO[6];
	CLedCS		m_ledNGVacIO[6];
	CLedCS		m_ledGDVacIO[6];
	CLedCS		m_ledBlock[2];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	afx_msg void OnBtnVisionYClick(UINT nID);
	afx_msg void OnBtnVisionAClick(UINT nID);
	afx_msg void OnBtnVisionZClick(UINT nID);
	afx_msg void OnBtnBarcoeAClick(UINT nID);
	afx_msg void OnBtnNGStageYClick(UINT nID);
	afx_msg void OnBtnTRIOClick(UINT nID);
	afx_msg void OnBtnVacIOClick(UINT nID);
	afx_msg void OnBtnNGVacIOClick(UINT nID);
	afx_msg void OnBtnGDVacIOClick(UINT nID);
	afx_msg void OnBnClickedBtnPressUp();
	afx_msg void OnBnClickedBtnPressDown();

private:
	CString		m_strRfid;
	int			m_nMRunCase;

private:
	void Initial_Controls();
	BOOL Manual_Run();

protected:
	BOOL		m_bThreadElevator1;
	CWinThread	*m_pThreadElevator1;
	static UINT	Thread_Elevator1(LPVOID lpVoid);

public:
	void Begin_Elevator1ThreadMold();
	void End_Elevator1ThreadMold();

	void Display_Status();
	void Set_Rfid(CString sRfid) { m_strRfid = sRfid; }
};

///////////////////////////////////////////////////////////////////////////////

