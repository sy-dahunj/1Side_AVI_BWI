#pragma once


// CManualLoadPickerDlg 대화 상자입니다.

class CManualUnloadPickerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualUnloadPickerDlg)

public:
	CManualUnloadPickerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualUnloadPickerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_PICKER3_DLG };
	CStaticCS	m_stcAxisPos[6];
	CButtonCS	m_btnMLPickY1[6];
	CButtonCS	m_btnMLPickY2[4];
	CButtonCS	m_btnMLPickZ[7];
	CButtonCS	m_btnMLPickIO[28];
	CLedCS		m_ledMLPickIO[24];

	CStaticCS	m_stcPickerMove[4];
	CButtonCS	m_btnNGPickMove;
	CButtonCS	m_btnNGPickMoveZ;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnBtnMLNGPickY1Click(UINT nID);
	afx_msg void OnBtnMLNGPickY2Click(UINT nID);
	afx_msg void OnBtnMLNGPickZClick(UINT nID);
	afx_msg void OnBtnMLPickIOClick(UINT nID);

	afx_msg void OnBtnNGPickMoveClick();
	afx_msg void OnBnClickedBtnNgPickerMove2();
	afx_msg void OnBtnNGPickMovePosClick(UINT nID);


private:
	void Initial_Controls();

public:
	double dCurrentX;
	double dCurrentY;

	void Display_Status();

};
