// WorkDlg.h : 헤더 파일
//

#pragma once

#include "LogFile.h"
#include "FileSendSocket.h"

#define UM_UPDATE_MODEL			WM_USER+1
#define UM_UPDATE_RFID			WM_USER+2
#define	UM_UPDATE_JOB_LIST		WM_USER+3
#define UM_UPDATE_SHIFT_LIST	WM_USER+4
#define UM_UPDATE_LOTID			WM_USER+5
#define UM_LOT_START_END		WM_USER+6

#define OP_CLEAR				0
#define OP_INSERT				1
#define OP_DELETE				2

// CWorkDlg 대화 상자입니다.

class CWorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkDlg)

private:
	static CWorkDlg *m_pInstance;

public:
	static CWorkDlg *Get_Instance(CWnd *pParent = NULL);
	void Delete_Instance();

public:
	CWorkDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWorkDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_WORK_DLG };
	CGroupCS		m_Group[9];
	CLabelCS		m_Label[46];
	CLabelCS		m_LabelDoor;
	CStaticCS		m_stcModelName;
	CStaticCS		m_stcStripSize;
	CStaticCS		m_stcStripType;
	CStaticCS		m_stcCMCnt;	       //by kty	
	CLabelCS		m_LabelstcCMCnt;	       //by kty	
	
	CStaticCS		m_stcLotId1;
	CStaticCS		m_stcLotId2;
	CStaticCS		m_stcPartNo2;	
	
	CPictureCS		m_Image;
	CStaticCS		m_stcElecValue;
	CStaticCS		m_stcWarpValue;
	CStaticCS		m_stcWorkSlot[18];
	CButtonCS		m_btnConvClear;
	CStaticCS		m_stcConveyor;

	CStaticCS		m_stcLoadCount;
	CStaticCS		m_stcUnloadCount;

	CLedCS			m_ledAutoStartEnable;
	CRadioCS		m_rdoWorkStart;
	CRadioCS		m_rdoWorkStop;
	CCheckCS		m_chkStripStop;
	CCheckCS		m_chkLotStop;
	CCheckCS		m_chkSampleJob;
	CLedCS			m_ledPicker[4][6];

	CStaticCS		m_stcWorkCase[12];
	CStaticCS		m_stcWorkPicker[2];
	CStaticCS		m_stcTrayPos[4];
	CLedStatic		m_ledIndexJob[6];
	CLedStatic		m_ledIndexSlot[5][6];
	CLedCS			m_ledBarAlarm;
	CLedCS			m_ledBarNG;
	CCheckCS		m_chkMESUse;
	CCheckCS		m_chkContinueLot;
	CGridCS			m_grdShiftList;
	CButtonCS		m_btnBuzzerOff;
	CButtonCS		m_btnLotCancel;

	BOOL			m_bUseContinueLot;

	CStaticCS		m_stcLotsId[5];
	CStaticCS		m_stcTraysCount[5];
	CStaticCS		m_stcCmsCount[5];


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRdoWorkStart();
	afx_msg void OnBnClickedRdoWorkStop();
	afx_msg void OnBnClickedChkStripStop();
	afx_msg void OnBnClickedChkLotStop();
	afx_msg void OnBnClickedChkSampleJob();
	afx_msg void OnBnClickedBtnConvClear();
	afx_msg void OnBnClickedChkMESUse();
	afx_msg void OnBnClickedChkContinueLot();

	afx_msg void OnStcCmsCountClick(UINT nID);
	afx_msg void OnStcLotsIdClick(UINT nID);

	afx_msg void OnBnClickedLotID();
	afx_msg void OnBnClickedTrayCnt();
	afx_msg void OnBnClickedCMCnt();
	afx_msg void OnBnClickedBtnBuzzerOff();
	afx_msg void OnBnClickedBtnLotCancel();

	afx_msg LRESULT OnUpdateModel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateRfid(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateJobList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateShiftList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateLotID(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLotStartEnd(WPARAM wParam, LPARAM lParam);

private:
	CBitmap	m_bmpImage;
	BOOL	m_bInitialOk;
	int		m_nDisCnt;
	CString m_sCurLotID;
	CLogFile *pLogFile;

private:
	void Initial_Controls();
	void Display_Status();
	void Display_Tray();
	void Display_LotInfo();

protected:
	static DWORD CALLBACK StreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);

public:
	BOOL m_bAutoRunning;

	void Set_AutoRun(BOOL bAutoRun);
	void Set_AutoRunStatus(BOOL bAutoRun) { m_bAutoRunning = bAutoRun; }
	void Set_CleanOutMode();
	void Set_AlaramLog();

	void Clear_ConveyorList() { m_stcConveyor.SetWindowText("0"); }
	int GetCount_ConveyorList() { return GetDlgItemInt(IDC_STC_CONVEYOR); }
	BOOL Check_Start();
	void Initial_ShiftGrid();
	void Add_ShifeError();
	void AutoStop();
	void Clear_LotInfo();

	void FileSend();

	void Enable_LotInfo(BOOL on);

public: 
	CFileSendSocket m_sender;
	afx_msg void OnBnClickedBtnSend1();
	BOOL ConnectToServer(CString ip, UINT port);
    BOOL SendFile(CString filePath);
};

///////////////////////////////////////////////////////////////////////////////
