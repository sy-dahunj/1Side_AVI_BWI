// ManualDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "ManualDlg.h"
#include "afxdialogex.h"

#include "CMI4200LDlg.h"
#include "LogFile.h"

// CManualDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualDlg, CDialogEx)

CManualDlg *CManualDlg::m_pInstance = NULL;

CManualDlg *CManualDlg::Get_Instance(CWnd *pParent)
{
	if (!m_pInstance) {
		m_pInstance = new CManualDlg(pParent);
		if (!m_pInstance->m_hWnd) {
			m_pInstance->Create(IDD_MANUAL_DLG, pParent);
		}
	}
	return m_pInstance;
}

void CManualDlg::Delete_Instance()
{
	if (m_pInstance->m_hWnd) m_pInstance->DestroyWindow();
	if (m_pInstance) delete m_pInstance;
	m_pInstance = NULL;
}

CManualDlg::CManualDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualDlg::IDD, pParent)
{
}

CManualDlg::~CManualDlg()
{
}

void CManualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_MANUAL_BACK, m_picManualBack);
	DDX_Control(pDX, IDC_RDO_MANUAL_FLOW, m_rdoManualLoadTray);
	DDX_Control(pDX, IDC_RDO_MANUAL_ELEVATOR, m_rdoManualLoadPicker);
	DDX_Control(pDX, IDC_RDO_MANUAL_GRIPPER, m_rdoManualIndex);
	DDX_Control(pDX, IDC_RDO_MANUAL_PICKER, m_rdoManualNGoodPicker);
	DDX_Control(pDX, IDC_RDO_MANUAL_INSPECTOR, m_rdoManualUnloadTray);
	DDX_Control(pDX, IDC_RDO_MANUAL_DOOR_LOCK, m_rdoManualDoorLock);
	DDX_Control(pDX, IDC_RDO_MANUAL_DOOR_UNLOCK, m_rdoManualDoorUnlock);

	DDX_Control(pDX, IDC_RDO_MANUAL_GRIPPER2, m_rdoManualGripper2);
	DDX_Control(pDX, IDC_RDO_MANUAL_PICKER2, m_rdoManualPicker2);
	DDX_Control(pDX, IDC_RDO_MANUAL_ELEVATOR2, m_rdoManualUnloadPicker);
}

BEGIN_MESSAGE_MAP(CManualDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RDO_MANUAL_FLOW, &CManualDlg::OnBnClickedRdoManualLoadTray)
	ON_BN_CLICKED(IDC_RDO_MANUAL_ELEVATOR, &CManualDlg::OnBnClickedRdoManualLoadPicker)
	ON_BN_CLICKED(IDC_RDO_MANUAL_GRIPPER, &CManualDlg::OnBnClickedRdoManualIndex)
	ON_BN_CLICKED(IDC_RDO_MANUAL_PICKER, &CManualDlg::OnBnClickedRdoManualNGoodPicker)
	ON_BN_CLICKED(IDC_RDO_MANUAL_INSPECTOR, &CManualDlg::OnBnClickedRdoManualUnloadTray)
	ON_BN_CLICKED(IDC_RDO_MANUAL_DOOR_LOCK, &CManualDlg::OnBnClickedRdoManualDoorLock)
	ON_BN_CLICKED(IDC_RDO_MANUAL_DOOR_UNLOCK, &CManualDlg::OnBnClickedRdoManualDoorUnlock)
	ON_BN_CLICKED(IDC_RDO_MANUAL_GRIPPER2, &CManualDlg::OnBnClickedRdoManualGripper2)
	ON_BN_CLICKED(IDC_RDO_MANUAL_PICKER2, &CManualDlg::OnBnClickedRdoManualPicker2)
	ON_BN_CLICKED(IDC_RDO_MANUAL_ELEVATOR2, &CManualDlg::OnBnClickedRdoManualUnloadPicker)
END_MESSAGE_MAP()

// CManualDlg 메시지 처리기입니다.

BOOL CManualDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();
	
	m_pManualIndexDlg = new CManualIndexDlg(this);
	m_pManualIndexDlg->Create(IDD_MANUAL_ELEVATOR_DLG, this);

	m_pManualNGoodPickerDlg = new CManualNGoodPickerDlg(this);
	m_pManualNGoodPickerDlg->Create(IDD_MANUAL_PICKER_DLG, this);

	m_pManualUnloadTrayDlg = new CManualUnloadTrayDlg(this);
	m_pManualUnloadTrayDlg->Create(IDD_MANUAL_INSPECTOR_DLG, this);

	m_pManualLoadPickerDlg = new CManualLoadPickerDlg(this);
	m_pManualLoadPickerDlg->Create(IDD_MANUAL_PICKER2_DLG, this);

	m_pManualUnloadPickerDlg = new CManualUnloadPickerDlg(this);
	m_pManualUnloadPickerDlg->Create(IDD_MANUAL_PICKER3_DLG, this);

	m_pManualLotDataDlg = new CManualLotDataDlg(this);
	m_pManualLotDataDlg->Create(IDD_MANUAL_LOTDATA_DLG, this);

	m_pManualLoadTrayDlg = new CManualLoadTrayDlg(this);
	m_pManualLoadTrayDlg->Create(IDD_MANUAL_LOADING_DLG, this);

	// Inspector Dlg Visible
	m_rdoManualUnloadTray.SetCheck(TRUE);
	m_rdoManualUnloadTray.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CManualDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	m_pManualUnloadTrayDlg->DestroyWindow();
	m_pManualNGoodPickerDlg->DestroyWindow();
	m_pManualIndexDlg->DestroyWindow();
	m_pManualLoadTrayDlg->DestroyWindow();
	m_pManualLoadPickerDlg->DestroyWindow();
	m_pManualUnloadPickerDlg->DestroyWindow();

	if (m_pManualUnloadTrayDlg) delete m_pManualUnloadTrayDlg;
	if (m_pManualNGoodPickerDlg) delete m_pManualNGoodPickerDlg;
	if (m_pManualIndexDlg) delete m_pManualIndexDlg;
	

	if (m_pManualLoadPickerDlg) delete m_pManualLoadPickerDlg;
	if (m_pManualUnloadPickerDlg) delete m_pManualUnloadPickerDlg;
	if (m_pManualLotDataDlg) delete m_pManualLotDataDlg;

	m_pManualUnloadTrayDlg = NULL;
	m_pManualNGoodPickerDlg = NULL;
	m_pManualIndexDlg = NULL;	

	m_pManualLoadPickerDlg = NULL;
	m_pManualUnloadPickerDlg = NULL;
	m_pManualLotDataDlg = NULL;
	m_pManualLoadTrayDlg = NULL;
}

BOOL CManualDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		if (m_rdoManualLoadTray.GetCheck()) m_pManualLoadTrayDlg->ShowWindow(SW_SHOW);
		if (m_rdoManualLoadPicker.GetCheck()) m_pManualLoadPickerDlg->ShowWindow(SW_SHOW);
		if (m_rdoManualUnloadPicker.GetCheck()) m_pManualUnloadPickerDlg->ShowWindow(SW_SHOW);
		if (m_rdoManualIndex.GetCheck()) m_pManualIndexDlg->ShowWindow(SW_SHOW);
		if (m_rdoManualNGoodPicker.GetCheck()) m_pManualNGoodPickerDlg->ShowWindow(SW_SHOW);
		
		if (m_rdoManualUnloadTray.GetCheck()) m_pManualUnloadTrayDlg->ShowWindow(SW_SHOW);
		if (m_rdoManualPicker2.GetCheck()) m_pManualLotDataDlg->ShowWindow(SW_SHOW);

//		m_rdoManualDoorLock.SetCheck(TRUE);
//		m_rdoManualDoorUnlock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
//		m_rdoManualDoorLock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);

		SetTimer(0, 100, NULL);

	} else {
		KillTimer(0);

//		m_rdoManualDoorUnlock.SetCheck(TRUE);
//		m_rdoManualDoorLock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
//		m_rdoManualDoorUnlock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);

		if (m_rdoManualLoadTray.GetCheck()) m_pManualLoadTrayDlg->ShowWindow(SW_HIDE);
		//if (m_rdoManualElevator.GetCheck()) m_pManualElevatorDlg->ShowWindow(SW_HIDE);
		//if (m_rdoManualGripper.GetCheck()) m_pManualGripperDlg->ShowWindow(SW_HIDE);
		if (m_rdoManualLoadPicker.GetCheck()) m_pManualLoadPickerDlg->ShowWindow(SW_HIDE);
		if (m_rdoManualUnloadPicker.GetCheck()) m_pManualUnloadPickerDlg->ShowWindow(SW_HIDE);
		if (m_rdoManualIndex.GetCheck()) m_pManualIndexDlg->ShowWindow(SW_HIDE);

		if (m_rdoManualNGoodPicker.GetCheck()) m_pManualNGoodPickerDlg->ShowWindow(SW_HIDE);
		if (m_rdoManualUnloadTray.GetCheck()) m_pManualUnloadTrayDlg->ShowWindow(SW_HIDE);
		if (m_rdoManualPicker2.GetCheck()) m_pManualLotDataDlg->ShowWindow(SW_HIDE);
	}
}

void CManualDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(0);

	CCommon *pCommon = CCommon::Get_Instance();
	if (!gData.m_bErrorShow) {
		pCommon->Check_MainEmgAir();	// Emg & Main Air
	}

	if (m_pManualIndexDlg->IsWindowVisible()) {
		m_pManualIndexDlg->Display_Status();
	} else if (m_pManualNGoodPickerDlg->IsWindowVisible()) {
		m_pManualNGoodPickerDlg->Display_Status();
	} else if (m_pManualLoadPickerDlg->IsWindowVisible()) {
		m_pManualLoadPickerDlg->Display_Status();
	} else if (m_pManualUnloadPickerDlg->IsWindowVisible()) {
		m_pManualUnloadPickerDlg->Display_Status();
	} else if (m_pManualUnloadTrayDlg->IsWindowVisible()) {
		m_pManualUnloadTrayDlg->Display_Status();
	} else if (m_pManualLotDataDlg->IsWindowVisible()) {
		m_pManualLotDataDlg->Display_Status();
	} else if (m_pManualLoadTrayDlg->IsWindowVisible()) {
		m_pManualLoadTrayDlg->Display_Status();
	}

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CManualDlg::OnBnClickedRdoManualLoadTray()
{
	if (m_pManualLoadTrayDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Manual - Load Tray] Start");
	m_rdoManualLoadTray.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pManualLoadTrayDlg->ShowWindow(SW_SHOW);
}

void CManualDlg::OnBnClickedRdoManualLoadPicker()
{
	if (m_pManualLoadPickerDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Manual - Load Picker] Start");
	m_rdoManualLoadPicker.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pManualLoadPickerDlg->ShowWindow(SW_SHOW);
}

void CManualDlg::OnBnClickedRdoManualIndex()
{
	if (m_pManualIndexDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Manual - Index/Inspect] Start");
	m_rdoManualIndex.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pManualIndexDlg->ShowWindow(SW_SHOW);

}

void CManualDlg::OnBnClickedRdoManualNGoodPicker()
{
	if (m_pManualNGoodPickerDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Manual -NG/Good Picker] Start");
	m_rdoManualNGoodPicker.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pManualNGoodPickerDlg->ShowWindow(SW_SHOW);
}

void CManualDlg::OnBnClickedRdoManualUnloadTray()
{
	if (m_pManualUnloadTrayDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Manual - Unload Tray] Start");
	m_rdoManualUnloadTray.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pManualUnloadTrayDlg->ShowWindow(SW_SHOW);
}

void CManualDlg::OnBnClickedRdoManualGripper2()
{

}

void CManualDlg::OnBnClickedRdoManualPicker2()
{
	if (m_pManualLotDataDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Manual - LotData] Start");
	m_rdoManualPicker2.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pManualLotDataDlg->ShowWindow(SW_SHOW);
/*
	if (m_pManualPicker2Dlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Manual - Picker2] Start");
	m_rdoManualPicker2.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pManualPicker2Dlg->ShowWindow(SW_SHOW);
*/
}

void CManualDlg::OnBnClickedRdoManualUnloadPicker()
{
	if (m_pManualUnloadPickerDlg->IsWindowVisible()) return;
	Hide_Windows();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Manual - Unload Picker] Start");
	m_rdoManualUnloadPicker.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	m_pManualUnloadPickerDlg->ShowWindow(SW_SHOW);


}

void CManualDlg::OnBnClickedRdoManualDoorLock()
{
/*
	if (m_rdoManualDoorLock.GetCheck()) {
		CLogFile *pLogFile = CLogFile::Get_Instance();
		pLogFile->Save_HandlerLog("[Manual] Door Lock button push");
//		CCommon *pCommon = CCommon::Get_Instance();
//		pCommon->Locking_MainDoor(TRUE);
		m_rdoManualDoorUnlock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
		m_rdoManualDoorLock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	}
*/
}

void CManualDlg::OnBnClickedRdoManualDoorUnlock()
{
/*
	if (m_rdoManualDoorUnlock.GetCheck()) {
		CLogFile *pLogFile = CLogFile::Get_Instance();
		pLogFile->Save_HandlerLog("[Manual] Door Unlock button push");
		m_rdoManualDoorLock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
		m_rdoManualDoorUnlock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
//		CCommon *pCommon = CCommon::Get_Instance();
//		pCommon->Locking_MainDoor(FALSE);
	}
*/
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CManualDlg::Initial_Controls() 
{
	m_picManualBack.Init_Ctrl(RGB(0x00, 0x00, 0x00), RGB(0xE0, 0xFF, 0xE0));
	m_rdoManualLoadTray.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoManualLoadPicker.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoManualIndex.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoManualNGoodPicker.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoManualUnloadTray.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
//	m_rdoManualDoorLock.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
//	m_rdoManualDoorUnlock.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);

	m_rdoManualUnloadPicker.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoManualGripper2.Init_Ctrl("바탕", 10, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoManualPicker2.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
}

void CManualDlg::Hide_Windows()
{
	m_pManualLoadTrayDlg->ShowWindow(SW_HIDE);
	m_pManualIndexDlg->ShowWindow(SW_HIDE);
	m_pManualNGoodPickerDlg->ShowWindow(SW_HIDE);
	m_pManualLoadPickerDlg->ShowWindow(SW_HIDE);
	m_pManualUnloadPickerDlg->ShowWindow(SW_HIDE);
	m_pManualUnloadTrayDlg->ShowWindow(SW_HIDE);

	m_pManualLotDataDlg->ShowWindow(SW_HIDE);
	

	m_rdoManualLoadTray.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualLoadPicker.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualIndex.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualNGoodPicker.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualUnloadPicker.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);

	m_rdoManualGripper2.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualPicker2.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoManualUnloadTray.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);

}

void CManualDlg::MainDoor_Lock()
{
//	CLogFile *pLogFile = CLogFile::Get_Instance();
//	pLogFile->Save_HandlerLog("[Manual] Door Lock cmd exec");
//	m_rdoManualDoorLock.SetCheck(TRUE);
//	m_rdoManualDoorUnlock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
//	m_rdoManualDoorLock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
}

void CManualDlg::MainDoor_Unlock()
{
//	CLogFile *pLogFile = CLogFile::Get_Instance();
//	pLogFile->Save_HandlerLog("[Manual] Door Unlock cmd exec");
//	m_rdoManualDoorUnlock.SetCheck(TRUE);
//	m_rdoManualDoorLock.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
//	m_rdoManualDoorUnlock.Set_Color(RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
}

///////////////////////////////////////////////////////////////////////////////
