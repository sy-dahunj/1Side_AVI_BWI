#pragma once


// CManualElevator2Dlg 대화 상자입니다.

class CManualElevator2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualElevator2Dlg)

public:
	CManualElevator2Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualElevator2Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_ELEVATOR2_DLG };
	CGroupCS	m_Group[4];
	CLabelCS	m_Label[1];
	CStaticCS	m_stcAxisPos[2];

	CLedCS	m_ledGoodCVRearIO[16];
	CLedCS	m_ledGoodCVMidIO[18];
	CLedCS	m_ledGoodCVFrontIO[17];

	CButtonCS	m_btnGoodCVRear[10];
	CButtonCS	m_btnGoodCVMid[10];
	CButtonCS	m_btnGoodCVFront[10];
	CButtonCS	m_btnGoodElevZ[4];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnBtnGoodCVRearClick(UINT nID);	// IDC_BTN_GOOD_TRAY_CV_REAR
	afx_msg void OnBtnGoodCVMidClick(UINT nID);		// IDC_BTN_GOOD_TRAY_CV_MID
	afx_msg void OnBtnGoodCVFrontClick(UINT nID);	// IDC_BTN_GOOD_TRAY_CV_FRONT
	afx_msg void OnBtnGoodElevZClick(UINT nID);		// IDC_BTN_GOOD_TRAY_ELEV_Z
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton17();

private:
	void Initial_Controls();

public:

	void Display_Status();


};
