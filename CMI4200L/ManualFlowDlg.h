// ManualFlowDlg.h : 헤더 파일
//
#pragma once
#include "afxwin.h"

// CManualFlowDlg 대화 상자입니다.

class CManualFlowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualFlowDlg)

public:
	CManualFlowDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualFlowDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_FLOW_DLG };
	CGroupCS	m_Group[12];
	CLabelCS	m_Label[4];
	CStaticCS	m_stcAxisPos[2];
	CButtonCS	m_btnLoConvW;
	CButtonCS	m_btnUpConvW[2];
	CCheckCS	m_chkPIOOut[4];
	CLedCS		m_ledPIOOut[4];
	CLedCS		m_ledPIOIn[8];
	CButtonCS	m_btnLoadIo[2];
	CCheckCS	m_chkLoadIo[3];
	CLedCS		m_ledLoadIo[8];
	CLedCS		m_ledBufferIo;
	CButtonCS	m_btnUnloadIo[2];
	CCheckCS	m_chkUnloadIo[4];
	CLedCS		m_ledUnloadIo[11];
	CStaticCS	m_stcLotId2;
	CStaticCS	m_stcPartNo2;
	CCheckCS	m_chkReadRfid2;
	CLedCS		m_ledCount[8];
	CStaticCS	m_stcTimeOut[8];
	CButtonCS	m_btnUnloadStage[2];
	CLedCS		m_ledUnloadStage[2];
	CCheckCS	m_ckLoadRightConvRun;
	CCheckCS	m_chkUnloadRightConvRun;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnLoConvWClick(UINT nID);	// IDC_BTN_LO_CONV_W Click
	afx_msg void OnBtnUpConvWClick(UINT nID);	// IDC_BTN_UP_CONV_W Click
	afx_msg void OnChkFlowIfIoClick(UINT nID);	// IDC_CHK_FLOW_IF_IO Click
	afx_msg void OnBtnLoadIoClick(UINT nID);	// IDC_BTN_LOAD_IO Click
	afx_msg void OnChkLoadIoClick(UINT nID);	// IDC_CHK_LOAD_IO Click
	afx_msg void OnBtnUnloadIoClick(UINT nID);	// IDC_BTN_UNLOAD_IO Click
	afx_msg void OnChkUnloadIoClick(UINT nID);	// IDC_CHK_UNLOAD_IO Click
	afx_msg void OnBnClickedChkReadRfid2();
	afx_msg void OnBnClickedBtnPioReset();
	afx_msg void OnStcTimeOutT1();
	afx_msg void OnStcTimeOutT3();
	afx_msg void OnStcTimeOutT4();
	afx_msg void OnStcTimeOutT6();
	afx_msg void OnBnClickedBtnTimeoutSave();
	afx_msg void OnBnClickedBtnTimeoutCancel();
	afx_msg void OnBnClickedBtnUnloadUp();
	afx_msg void OnBnClickedBtnUnloadDn();
	afx_msg void OnBnClickedChkLoadIo3();
	afx_msg void OnBnClickedChkUnloadIo4();

private:
	CString		m_strRfid;

private:
	void Initial_Controls();

public:
	void Display_Status();
	void OHTTimeOut_Display();
	void Set_Rfid(CString sRfid) { m_strRfid = sRfid; }
};

///////////////////////////////////////////////////////////////////////////////
