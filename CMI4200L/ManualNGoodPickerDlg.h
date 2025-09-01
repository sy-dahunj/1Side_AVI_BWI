// ManualNGoodPickerDlg.h : 헤더 파일
//
#pragma once

// CManualNGoodPickerDlg 대화 상자입니다.

class CManualNGoodPickerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualNGoodPickerDlg)

public:
	CManualNGoodPickerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualNGoodPickerDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_PICKER_DLG };
	CStaticCS	m_stcAxisPos[5];

	CButtonCS	m_btnGoodPickerX[2];
	CButtonCS	m_btnGoodPickerY[6];
	CButtonCS	m_btnGoodPickerZ[2];

	CButtonCS	m_btnGoodPicker1[4];
	CButtonCS	m_btnGoodPicker2[4];
	CButtonCS	m_btnGoodPicker3[4];
	CButtonCS	m_btnGoodPicker4[4];
	CButtonCS	m_btnGoodPicker5[4];
	CButtonCS	m_btnGoodPicker6[4];
	CButtonCS	m_btnGoodPickerAll[4];
	CLedCS		m_ledGoogPick1IO[5];
	CLedCS		m_ledGoogPick2IO[5];
	CLedCS		m_ledGoogPick3IO[5];
	CLedCS		m_ledGoogPick4IO[5];
	CLedCS		m_ledGoogPick5IO[5];
	CLedCS		m_ledGoogPick6IO[5];

	CButtonCS	m_btnNGPickX[6];
	CButtonCS	m_btnNGPickZ[3];
	CButtonCS	m_btnNGPickIO[24];
	CLedCS		m_ledNGPickIO[20];

	CStaticCS	m_stcPickerMove[4];
	CButtonCS	m_btnGoodPickMove;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);


	afx_msg void OnBtnPickerXClick(UINT nID);	// IDC_BTN_PICKER_X Click
	afx_msg void OnBtnPickerYClick(UINT nID);	// IDC_BTN_PICKER_Y Click
	afx_msg void OnBtnPickerZClick(UINT nID);	// IDC_BTN_PICKER_Z Click

	afx_msg void OnBtnPicker1Click(UINT nID);	// IDC_BTN_GOOD_PICKER1 Click
	afx_msg void OnBtnPicker2Click(UINT nID);	// IDC_BTN_GOOD_PICKER2 Click
	afx_msg void OnBtnPicker3Click(UINT nID);	// IDC_BTN_GOOD_PICKER3 Click
	afx_msg void OnBtnPicker4Click(UINT nID);	// IDC_BTN_GOOD_PICKER4 Click
	afx_msg void OnBtnPicker5Click(UINT nID);	// IDC_BTN_GOOD_PICKER5 Click
	afx_msg void OnBtnPicker6Click(UINT nID);	// IDC_BTN_GOOD_PICKER6 Click
	afx_msg void OnBtnPickerAClick(UINT nID);

	afx_msg void OnBtnNGPickXClick(UINT nID);
	afx_msg void OnBtnNGPickZClick(UINT nID);
	afx_msg void OnBtnNGPickIOClick(UINT nID);

	afx_msg void OnBtnGoodPickMoveClick();
	afx_msg void OnBtnGoodPickMovePosClick(UINT nID);
	afx_msg void OnBnClickedBtnGoodPicker4Move2();

private:
	double dCurrentX;
	double dCurrentY;

	void Initial_Controls();

public:
	void Display_Status();

};

///////////////////////////////////////////////////////////////////////////////
