// SetupMoveTab4Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab4Dlg 대화 상자입니다.

class CSetupMoveTab4Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab4Dlg)

public:
	CSetupMoveTab4Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab4Dlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB4_DLG };
	CGroupCS	m_Group[6];
	CLabelCS	m_Label[29];

	CStaticCS	m_stcEmptyTrayCVRear[5];	//Load Tray X1
	CStaticCS	m_stcEmptyTrayElevZ[5];		//Load Tray X2
	CStaticCS	m_stcGoodTrayCVRear[4];		//Load Tray Z1
	CStaticCS	m_stcGoodTrayUnloadElevZ[4];//Load Tray Z2
	CStaticCS	m_stcEmptyTrayCVFront[7];	//Load Picker Y12
	CStaticCS	m_staticBarcodeX[4];		//Load Picker Z

	CButtonCS	m_btnSave;
	CButtonCS	m_btnCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnStcEmptyTrayCVRearClick(UINT nID);			// IDC_STC_EMPTY_TRAY_CV_REAR_0 Click
	afx_msg void OnStcEmptyTrayCVFrontClick(UINT nID);			// IDC_STC_EMPTY_TRAY_CV_FRONT_0 Click
	afx_msg void OnStcGoodTrayCVRearClick(UINT nID);			// IDC_STC_GOOD_TRAY_CV_REAR_0 Click
	afx_msg void OnStcEmptyTrayUnloadElevZClick(UINT nID);	    // IDC_STC_EMPTY_TRAY_ELEV_Z Click
	afx_msg void OnStcGoodTrayUnloadElevZClick(UINT nID);	    // IDC_STC_GOOD_TRAY_ELEV_Z Click
	afx_msg void OnStaticBarcodeXClick(UINT nID);				// IDC_STATIC_BARCODE_X Click

	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnCancel();

private:
	void Initial_Controls();
	void Display_MoveData();
};

///////////////////////////////////////////////////////////////////////////////
