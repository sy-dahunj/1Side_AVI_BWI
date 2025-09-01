// ManualDlg.h : 헤더 파일
//
#pragma once

#include "ManualFlowDlg.h"
#include "ManualIndexDlg.h"
#include "ManualNGoodPickerDlg.h"
#include "ManualUnloadTrayDlg.h"
#include "ManualLoadPickerDlg.h"
#include "ManualUnloadPickerDlg.h"
#include "ManualLotDataDlg.h"
#include "ManualLoadTrayDlg.h"

// CManualDlg 대화 상자입니다.

class CManualDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualDlg)

private:
	static CManualDlg *m_pInstance;

public:
	static CManualDlg *Get_Instance(CWnd *pParent = NULL);
	void Delete_Instance();

public:
	CManualDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_DLG };
	CPictureCS	m_picManualBack;
	CRadioCS	m_rdoManualLoadTray;
	CRadioCS	m_rdoManualLoadPicker;
	CRadioCS	m_rdoManualIndex;
	CRadioCS	m_rdoManualNGoodPicker;
	CRadioCS	m_rdoManualUnloadTray;
	CRadioCS	m_rdoManualUnloadPicker;

	CRadioCS	m_rdoManualDoorLock;
	CRadioCS	m_rdoManualDoorUnlock;

	CRadioCS	m_rdoManualGripper2;
	CRadioCS	m_rdoManualPicker2;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRdoManualLoadTray();
	afx_msg void OnBnClickedRdoManualLoadPicker();
	afx_msg void OnBnClickedRdoManualIndex();
	afx_msg void OnBnClickedRdoManualNGoodPicker();
	afx_msg void OnBnClickedRdoManualUnloadTray();
	afx_msg void OnBnClickedRdoManualUnloadPicker();

	afx_msg void OnBnClickedRdoManualDoorLock();
	afx_msg void OnBnClickedRdoManualDoorUnlock();

	afx_msg void OnBnClickedRdoManualGripper2();
	afx_msg void OnBnClickedRdoManualPicker2();
	

public:
	
	CManualIndexDlg	*m_pManualIndexDlg;
	CManualNGoodPickerDlg	*m_pManualNGoodPickerDlg;
	CManualUnloadTrayDlg	*m_pManualUnloadTrayDlg;

	CManualLoadPickerDlg	*m_pManualLoadPickerDlg;
	CManualUnloadPickerDlg	*m_pManualUnloadPickerDlg;
	CManualLotDataDlg	*m_pManualLotDataDlg;
	CManualLoadTrayDlg	*m_pManualLoadTrayDlg;

private:
	void Initial_Controls();
	void Hide_Windows();

public:
	void MainDoor_Lock();
	void MainDoor_Unlock();
};

///////////////////////////////////////////////////////////////////////////////
