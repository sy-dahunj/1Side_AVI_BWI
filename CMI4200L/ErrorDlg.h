// ErrorDlg.h : 헤더 파일
//
#pragma once

// CErrorDlg 대화 상자입니다.

class CErrorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CErrorDlg)

private:
	static CErrorDlg *m_pInstance;

public:
	static CErrorDlg *Get_Instance(CWnd *pParent = NULL);
	void Delete_Instance();

public:
	CErrorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CErrorDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ERROR_DLG };
	CLabelCS	m_Label[2];
	CStaticCS	m_stcErrBack[4];
	CStaticCS	m_stcErrTitle;
	CPictureCS	m_Image;
	CStaticCS	m_stcErrPos[9];
	CStaticCS	m_stcErrNo;
	CStaticCS	m_stcErrMsg;
	CButtonCS	m_btnBuzzerOff;
	CButtonCS	m_btnErrSkip;
	CButtonCS	m_btnErrRetry;
	CButtonCS	m_btnErrOK;
	CButtonCS	m_btnSystemExit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnBuzzerOff();
	afx_msg void OnBnClickedBtnErrSkip();
	afx_msg void OnBnClickedBtnErrRetry();
	afx_msg void OnBnClickedBtnErrOk();
	afx_msg void OnBnClickedBtnSystemExit();

private:
	CBitmap		m_bmpImage;
	int			m_nErrNo;
	CString		m_strErrMsg;
	CString		m_strErrSubMsg;
	int			m_nBackColorLoop;

private:
	void Initial_Controls();
	void ErrorTimeEdit();
	void Load_ErrorImage(int nErrNo);

public:
	void Set_ErrorNumber(int nErrNo) { m_nErrNo = nErrNo; }
	void Set_ErrorMessage(CString sErrMsg) { m_strErrMsg = sErrMsg; }
	void Set_ErrorSubMessage(CString sErrMsg) { m_strErrSubMsg = sErrMsg; }
	void Set_ErrorLog(CString sErrNo, CString sErrMsg);
};

///////////////////////////////////////////////////////////////////////////////
