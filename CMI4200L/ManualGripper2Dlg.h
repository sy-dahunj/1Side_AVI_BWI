#pragma once


// CManualGripper2Dlg 대화 상자입니다.

class CManualGripper2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualGripper2Dlg)

public:
	CManualGripper2Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualGripper2Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_GRIPPER2_DLG };
	CGroupCS	m_Group[9];
	CLabelCS	m_Label[6];
	CStaticCS	m_stcAxisPos[4];
	CButtonCS	m_btnGrip1Y[11];
	CButtonCS	m_btnGrip2Y[4];
	CButtonCS	m_btnGripRailW;
	CButtonCS	m_btnLaserX;
	CButtonCS	m_btnGrip1Io[4];
	CLedCS		m_ledGrip1Io[8];
	CButtonCS	m_btnGrip2Io[8];
	CLedCS		m_ledGrip2Io[9];
	CCheckCS	m_chkGripIo[3];
	CButtonCS	m_btnGripRailIo[2];
	CLedCS		m_ledGripRailIo[2];
	CStaticCS	m_stcLaserValue;
	CButtonCS	m_btnLaserRead;
	CStaticCS	m_stcElectValue;
	CButtonCS	m_btnElectRead;

	//CMI3000 by kty
	CStaticCS   m_stcBarcodeRead;
	CButtonCS   m_btnBarcodeRead;
	CButtonCS	m_btnNGTrayUnloadY[4];
	CButtonCS	m_btnUnloadNGBarcodeX[3];
	CButtonCS	m_btnUnloadNGBarcodeY[4];


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	//CMI3000 by kty
	afx_msg void OnBtnNGTrayYClick(UINT nID);		// IDC_CHK_GRIP_IO Click
	afx_msg void OnBtnNGBarcodeXClick(UINT nID);		// IDC_CHK_GRIP_IO Click
	afx_msg void OnBtnNGBarcodeYClick(UINT nID);		// IDC_CHK_GRIP_IO Click
	afx_msg void OnBtnBarcodeReadClick(UINT nID);		



private:
	void Initial_Controls();

public:
	void Display_Status();

};
