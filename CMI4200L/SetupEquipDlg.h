// SetupEquipDlg.h : 헤더 파일
//
#pragma once

// CSetupEquipDlg 대화 상자입니다.

class CSetupEquipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupEquipDlg)

public:
	CSetupEquipDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupEquipDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_EQUIP_DLG };
	CGroupCS	m_Group[4];
	CLabelCS	m_Label0;
	CStaticCS	m_stcEquipName;

	CLabelCS	m_Label8[17];
	CLabelCS	m_Labe25;
	CRadioCS	m_rdoUseVisionInspect[2];
	CRadioCS	m_rdoUseManagerMode[2];
	CRadioCS	m_rdoUseBar2Alarm[2];
	CRadioCS	m_rdoUseBar2NG[2];
	CRadioCS	m_rdoUseMES[2];
	CRadioCS	m_rdoUseMesApd[2];
	CGroupCS	m_grpTower;
	CLabelCS	m_lblTower[13];
	CCheckCS	m_chkTower[6][7];	// [0:None,1:Init,2:Ready,3:Run,4:Alarm,5:Emer][0:Green,1:Yellow,2:Red,3:Flicker,4:Buzz1,5:Buzz2,6:Flicker]

	CStaticCS	m_stcDoorLockName;
	CRadioCS	m_rdoDoorLock[2];
	CStaticCS	m_stcDoorTimeName;
	CStaticCS	m_stcDoorLockTime;

	CRadioCS	m_rdoNGVacuum[2];
	CRadioCS	m_rdoGDVacuum[2];
	CRadioCS	m_rdoInlineMode[2];
	CRadioCS	m_rdoNgSortMode[2];		// NG 배출 방향 설정. TRUE : Front, FALSE : Rear
	CRadioCS	m_rdoSeparationMode[2];
	CComboCS	m_cboNgCode;
	CRadioCS	m_rdoGDPickSortMode[2];	// TURE : 1번 부터, FALSE : 5번 부터
	CRadioCS	m_rdoUnloadSortMode[2];	// TRUE : Front 부터, FALSE : Rear 부터
	CButtonCS	m_btnSave;
	CButtonCS	m_btnCancel;

	CGroupCS	m_GroupPsw;
	CStaticCS	m_stcFmErrorCount;
	CButtonCS	m_btnPswSave;
	CButtonCS	m_btnPswRead;

	CRadioCS	m_rdoDryRun[2];
	CStaticCS	m_stcNGCount;
	CStaticCS	m_stcIndexPitch;

	CLabelCS	m_lblCap;
	CIPAddressCtrl	m_ipaCapAttachIp;
	CButtonCS	m_btnCapConnect;
	CButtonCS	m_btnCapDisconnect;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStnClickedStcEquipName();
	afx_msg void OnStnClickedStcFmErrorCount();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnCancel();

	afx_msg void OnStnClickedStcOptionEnable();

	afx_msg void OnBnClickedBtnPswRead();
	afx_msg void OnBnClickedBtnPswSave();
	afx_msg void OnStnClickedstcNGCount();
	afx_msg void OnStnClickedstcIndexPitch();
	afx_msg void OnBnClickedBtnCapConnect();
	afx_msg void OnBnClickedBtnCapDisconnect();
	afx_msg void OnStnClickedstcRockTime();

private:
	void Initial_Controls();
	void Display_EquipData();

};

///////////////////////////////////////////////////////////////////////////////
