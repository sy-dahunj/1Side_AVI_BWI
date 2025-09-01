// SetupModelDlg.h : 헤더 파일
//
#pragma once

// CSetupModelDlg 대화 상자입니다.

class CSetupModelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupModelDlg)

public:
	CSetupModelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupModelDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MODEL_DLG };
	CGroupCS	m_Group[2];
	CLabelCS	m_Label[11];
	CStaticCS	m_stcCurrentModel;
	CListCS		m_lstModelList;
	CButtonCS	m_btnModelInsert;
	CButtonCS	m_btnModelDelete;
	CButtonCS	m_btnModelChange;
	CStaticCS	m_stcSelectModel;
	CRadioCS	m_rdoStripSize[2];
	CRadioCS	m_rdoStripType[3];

	CStaticCS	m_stcPkgXCount;
	CStaticCS	m_stcPkgYCount;
	CStaticCS	m_stcPitchL;
	CStaticCS	m_stcPitchW;

	CStaticCS	m_stcTrayFirstL;
	CStaticCS	m_stcTrayFirstW;
	CStaticCS	m_stcCMWsize;
	CStaticCS	m_stcCMCount;

	CRadioCS	m_rdoModelSample[2];
	CButtonCS	m_btnSave;
	CButtonCS	m_btnCancel;
	//}}AFX_DATA

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLbnSelchangeLstModelList();
	afx_msg void OnBnClickedBtnModelInsert();
	afx_msg void OnBnClickedBtnModelDelete();
	afx_msg void OnBnClickedBtnModelChange();
	afx_msg void OnStnClickedStcPkgXCount();
	afx_msg void OnStnClickedStcPkgYCount();
	afx_msg void OnStnClickedStcPitchL();
	afx_msg void OnStnClickedStcPitchW();

	afx_msg void OnStnClickedstcTrayFirstL();
	afx_msg void OnStnClickedStcTrayFirstW();
	afx_msg void OnStnClickedStcCMWsize();
	afx_msg void OnStnClickedStcCMCount();

	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnCancel();

private:
	void Initial_Controls();

public:
	void Display_ModelList();
	void Display_ModelData(CString sModel);
	void Set_ModelChange(CString sModel);
};

///////////////////////////////////////////////////////////////////////////////
