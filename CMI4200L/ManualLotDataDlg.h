#pragma once


// CManualLotDataDlg 대화 상자입니다.

class CManualLotDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualLotDataDlg)

public:
	CManualLotDataDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualLotDataDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_LOTDATA_DLG };
	CGroupCS	m_Group[5];
	CLabelCS	m_Label[6];
	CLabelCS	m_Labels[60];
	CStaticCS	m_stcLotID;
	CStaticCS	m_stcPackageName;
	CStaticCS	m_stcSlotCount;
	CStaticCS	m_stcModelName;
	CStaticCS	m_stcShiftID;
	CStaticCS	m_stcOperID;
	CStaticCS	m_stcSIDEdit;
	CStaticCS	m_stcSID[60];

	CButtonCS	m_btnLotApply;
	CButtonCS	m_btnOperApply;
	CButtonCS	m_btnSIDApply;
	CButtonCS	m_btnSave;
	CButtonCS	m_btnCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStnClickedStcLotID();
	afx_msg void OnStnClickedStcPackageName();
	afx_msg void OnStnClickedStcSlotCount();
	afx_msg void OnStnClickedStcModelName();
	afx_msg void OnStnClickedStcShiftID();
	afx_msg void OnStnClickedStcOperID();
	afx_msg void OnStnClickedStcSIDEdit();
	afx_msg void OnStnClickedStcSID(UINT nID);

	afx_msg void OnBnClickedBtnLotApply();
	afx_msg void OnBnClickedBtnOperApply();
	afx_msg void OnBnClickedBtnSIDApply();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnCancel();

private:
	void Initial_Controls();
	void Display_LotData();

public:
	void LotData_Read();
	void LotData_Write();
	void Display_Status();
	afx_msg void OnBnClickedBtnSidApply3();
	afx_msg void OnBnClickedBtnSidApply4();
	afx_msg void OnBnClickedBtnSidApply5();
};
