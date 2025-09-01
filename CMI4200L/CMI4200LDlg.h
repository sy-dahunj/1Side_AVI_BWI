// CMI4200LDlg.h : 헤더 파일
//
#pragma once

#include "InitialDlg.h"
#include "WorkDlg.h"
#include "ManualDlg.h"
#include "SetupDlg.h"
#include "MonitorDlg.h"
#include "ErrorDlg.h"
#include "PauseDlg.h"

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "Inspector.h"
#include "LogFile.h"
#include "ManualLotDataDlg.h"
#include "SequenceInit.h"
#include "SequenceMain.h"
#include "OperatorDlg.h"

//#include "ExtBarcode_Honeywell.h"
#include "SocketTCP.h"
#include "Barcode_DS1100.h"

#define	MODE_NONE			0
#define MODE_INITIAL		1
#define MODE_WORK			2
#define MODE_MANUAL			3
#define MODE_SETUP			4
#define MODE_PROHIBIT		5

#define EXIT_SYSTEM_NONE	0
#define EXIT_SYSTEM_AJIN	1
#define EXIT_SYSTEM_RFID	2
#define EXIT_SYSTEM_LASER	3
#define EXIT_SYSTEM_ELECT	4

#define TIMER_DATE_TIME		0
#define TIMER_TOWER_FLKR	1
#define TIMER_DOOR_LOCK		3

#define STATE_NONE			0
#define STATE_INITEND		1
#define STATE_RUN			2
#define STATE_LOTEND		3
#define STATE_ALARM			4
#define STATE_EMER			5

// CCMI4200LDlg 대화 상자
class CCMI4200LDlg : public CDialogEx
{
	// 생성입니다.
public:
	CCMI4200LDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CMI4200L_DIALOG };
	CPictureCS	m_picMainBack;
	CStaticCS	m_stcMainDate;
	CStaticCS	m_stcMainEquip;
	CStaticCS	m_stcMainLabel;
	CStaticCS	m_stcMainVer;
	CStaticCS	m_stcMainTime;
	CStaticCS	m_stcMainOper;
	CPictureCS	m_picModeBack;
	CRadioCS	m_rdoMainInitial;
	CRadioCS	m_rdoMainWork;
	CRadioCS	m_rdoMainManual;
	CRadioCS	m_rdoMainSetup;
	CRadioCS	m_rdoMainPause;
	CButtonCS	m_btnMainMonitor;
	CButtonCS	m_btnMainSystemExit;
	CButtonCS	m_btnMainOperator;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRdoMainInitial();
	afx_msg void OnBnClickedRdoMainWork();
	afx_msg void OnBnClickedRdoMainManual();
	afx_msg void OnBnClickedRdoMainSetup();
	afx_msg void OnBnClickedBtnMainMonitor();
	afx_msg void OnBnClickedRdoMainPause();
	afx_msg void OnBnClickedBtnMainSystemExit();
	afx_msg void OnBnClickedBtnMainOperator();
	afx_msg void OnStnDblclickStcMainTime();
	afx_msg void OnStnDblclickStcMainLabel();

private:
	CAJinAXL		*m_pAJinAXL;
	CDataManager	*m_pDataManager;
	CCommon			*m_pCommon;

	// Dialogs
	CInitialDlg		*m_pInitialDlg;
	CWorkDlg		*m_pWorkDlg;
	CManualDlg		*m_pManualDlg;
	CSetupDlg		*m_pSetupDlg;
	CMonitorDlg		*m_pMonitorDlg;
	CErrorDlg		*m_pErrorDlg;
	COperatorDlg	*m_pOperatorDlg;

	CInspector		*m_pInspector;
	CLogFile		*m_pLogFile;

	CSequenceInit	*m_pSequenceInit;
	CSequenceMain	*m_pSequenceMain;
	CManualLotDataDlg	*m_pManualLotDataDlg;

	//CExtBarcode_Honeywell *m_pExtBarcode_Honeywell;
	CBarcode_DS1100 *m_pBarcode_DS1100;
	CSocketTCP		*m_CSocketTCP; 

	int m_nCurrMode;
	int m_nPrevMode;

	int m_dwEquipProcTime;

private:
	void Initial_Controls();
	void Hide_ModeWindows();
	void Do_Events();

public:
	void Set_CurrentMode(int nMode);

	int Get_CurrentMode() { return m_nCurrMode; }
	int Get_PreviousMode() { return m_nPrevMode; }

	void Set_MainState(int nState);
	void Set_TowerFlicker();

	void Enable_ModeButton(BOOL bEnable);

	void Display_DateTime();
	void Exit_System(int nExitNo);

	void Gloval_Initial();
	void LogAllDelete();
	void LogFileDelete(CString sPath);

	void Set_DoorLock();
	void Set_LotErrorLog(CString sEvent, int nErrCode, CString sMessage);
};

///////////////////////////////////////////////////////////////////////////////
