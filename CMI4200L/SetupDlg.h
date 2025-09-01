// SetupDlg.h : ��� ����
//
#pragma once

#include "SetupEquipDlg.h"
#include "SetupModelDlg.h"
#include "SetupMoveDlg.h"
#include "SetupMotionDlg.h"
#include "SetupInOutDlg.h"

// CSetupDlg ��ȭ �����Դϴ�.

class CSetupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupDlg)

private:
	static CSetupDlg *m_pInstance;

public:
	static CSetupDlg *Get_Instance(CWnd *pParent = NULL);
	void Delete_Instance();

public:
	CSetupDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetupDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETUP_DLG };
	CPictureCS	m_picSetupBack;
	CRadioCS	m_rdoSetupEquip;
	CRadioCS	m_rdoSetupModel;
	CRadioCS	m_rdoSetupMove;
	CRadioCS	m_rdoSetupMotion;
	CRadioCS	m_rdoSetupInOut;
	CRadioCS	m_rdoSetupDoorLock;
	CRadioCS	m_rdoSetupDoorUnlock;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRdoSetupEquip();
	afx_msg void OnBnClickedRdoSetupModel();
	afx_msg void OnBnClickedRdoSetupMove();
	afx_msg void OnBnClickedRdoSetupMotion();
	afx_msg void OnBnClickedRdoSetupInOut();
	afx_msg void OnBnClickedRdoSetupDoorLock();
	afx_msg void OnBnClickedRdoSetupDoorUnlock();

public:
	CSetupEquipDlg	*m_pSetupEquipDlg;
	CSetupModelDlg	*m_pSetupModelDlg;
	CSetupMoveDlg	*m_pSetupMoveDlg;
	CSetupMotionDlg	*m_pSetupMotionDlg;
	CSetupInOutDlg	*m_pSetupInOutDlg;

private:
	void Initial_Controls();
	void Hide_Windows();

public:
	void MainDoor_Lock();
	void MainDoor_Unlock();
};

///////////////////////////////////////////////////////////////////////////////
