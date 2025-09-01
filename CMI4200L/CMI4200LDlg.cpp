// CMI4200LDlg.cpp : ���� ����
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "CMI4200LDlg.h"
#include "afxdialogex.h"

#include "CapAttachUDP.h"
#include "SplashDlg.h"
#include "PasswordDlg.h"
#include "Common.h"
#include "MESInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCMI4200LDlg ��ȭ ����

CCMI4200LDlg::CCMI4200LDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCMI4200LDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCMI4200LDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_MAIN_BACK, m_picMainBack);
	DDX_Control(pDX, IDC_STC_MAIN_DATE, m_stcMainDate);
	DDX_Control(pDX, IDC_STC_MAIN_EQUIP, m_stcMainEquip);
	DDX_Control(pDX, IDC_STC_MAIN_LABEL, m_stcMainLabel);
	DDX_Control(pDX, IDC_STC_MAIN_VER, m_stcMainVer);
	DDX_Control(pDX, IDC_STC_MAIN_TIME, m_stcMainTime);
	DDX_Control(pDX, IDC_STC_MAIN_OPER, m_stcMainOper);
	DDX_Control(pDX, IDC_PIC_MODE_BACK, m_picModeBack);
	DDX_Control(pDX, IDC_RDO_MAIN_INITIAL, m_rdoMainInitial);
	DDX_Control(pDX, IDC_RDO_MAIN_WORK, m_rdoMainWork);
	DDX_Control(pDX, IDC_RDO_MAIN_MANUAL, m_rdoMainManual);
	DDX_Control(pDX, IDC_RDO_MAIN_SETUP, m_rdoMainSetup);
	DDX_Control(pDX, IDC_RDO_MAIN_PAUSE, m_rdoMainPause);
	DDX_Control(pDX, IDC_BTN_MAIN_MONITOR, m_btnMainMonitor);
	DDX_Control(pDX, IDC_BTN_MAIN_SYSTEM_EXIT, m_btnMainSystemExit);
	DDX_Control(pDX, IDC_BTN_MAIN_OPERATOR, m_btnMainOperator);
}

BEGIN_MESSAGE_MAP(CCMI4200LDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RDO_MAIN_INITIAL, &CCMI4200LDlg::OnBnClickedRdoMainInitial)
	ON_BN_CLICKED(IDC_RDO_MAIN_WORK, &CCMI4200LDlg::OnBnClickedRdoMainWork)
	ON_BN_CLICKED(IDC_RDO_MAIN_MANUAL, &CCMI4200LDlg::OnBnClickedRdoMainManual)
	ON_BN_CLICKED(IDC_RDO_MAIN_SETUP, &CCMI4200LDlg::OnBnClickedRdoMainSetup)
	ON_BN_CLICKED(IDC_RDO_MAIN_PAUSE, &CCMI4200LDlg::OnBnClickedRdoMainPause)
	ON_BN_CLICKED(IDC_BTN_MAIN_MONITOR, &CCMI4200LDlg::OnBnClickedBtnMainMonitor)
	ON_BN_CLICKED(IDC_BTN_MAIN_SYSTEM_EXIT, &CCMI4200LDlg::OnBnClickedBtnMainSystemExit)
	ON_BN_CLICKED(IDC_BTN_MAIN_OPERATOR, &CCMI4200LDlg::OnBnClickedBtnMainOperator)
	ON_STN_DBLCLK(IDC_STC_MAIN_TIME, &CCMI4200LDlg::OnStnDblclickStcMainTime)
	ON_STN_DBLCLK(IDC_STC_MAIN_LABEL, &CCMI4200LDlg::OnStnDblclickStcMainLabel)
END_MESSAGE_MAP()

// CCMI4200LDlg �޽��� ó����

BOOL CCMI4200LDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowText("CMI4200L_Handler");

	Initial_Controls();

	gData.bOpMode = TRUE;
	m_nCurrMode = MODE_NONE;
	m_nPrevMode = MODE_NONE;
	gData.m_bErrorShow = FALSE;
	gData.nPortNo = 1;

	m_pAJinAXL = CAJinAXL::Get_Instance();
	m_pDataManager = CDataManager::Get_Instance();
	m_pCommon = CCommon::Get_Instance();

	m_pInitialDlg = CInitialDlg::Get_Instance(this);
	m_pWorkDlg = CWorkDlg::Get_Instance(this);
	m_pManualDlg = CManualDlg::Get_Instance(this);
	m_pSetupDlg = CSetupDlg::Get_Instance(this);
	m_pMonitorDlg = CMonitorDlg::Get_Instance(this);
	g_dlgPause.Create(CPauseDlg::IDD, this);
	m_pErrorDlg = CErrorDlg::Get_Instance(NULL);
	m_pOperatorDlg = COperatorDlg::Get_Instance(this);

	m_pInspector = CInspector::Get_Instance();
	m_pLogFile = CLogFile::Get_Instance();

	m_pSequenceInit = CSequenceInit::Get_Instance();
	m_pSequenceMain = CSequenceMain::Get_Instance();

	g_objCapAttachUDP.Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), this, 0);

	//m_pExtBarcode_Honeywell = CExtBarcode_Honeywell::Get_Instance();
	m_pBarcode_DS1100 = CBarcode_DS1100::Get_Instance();
	m_CSocketTCP = CSocketTCP::Get_Instance();

	SetTimer(TIMER_DATE_TIME, 500, NULL);
	SetTimer(TIMER_DOOR_LOCK, 1000, NULL);

	CString sLog;
	sLog.Format("[Main Dialog] Program Start..   Version(%s)", MAIN_VERSION);
	m_pLogFile->Save_HandlerLog(sLog);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCMI4200LDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCMI4200LDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCMI4200LDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// HSMS Agent Close
// 	HWND hwnd = ::FindWindow("#32770", "HSMSAgent");
// 	if (hwnd)
// 		BOOL bOK = ::DestroyWindow(hwnd);
// 	::TerminateProcess()
// 	::ExitProcess(Process()

	m_pInspector->Set_StatusUpdate(INSPECTOR_VISION, 0);
	g_objCapAttachUDP.Set_StatusUpdate(0);

	m_pLogFile->Delete_Instance();
	m_pSequenceMain->Delete_Instance();
	m_pSequenceInit->Delete_Instance();

	m_pInspector->Delete_Instance();

	m_pErrorDlg->Delete_Instance();
	m_pMonitorDlg->Delete_Instance();
	m_pSetupDlg->Delete_Instance();
	m_pManualDlg->Delete_Instance();
	m_pWorkDlg->Delete_Instance();
	m_pInitialDlg->Delete_Instance();
	g_dlgPause.DestroyWindow();
	m_pOperatorDlg->Delete_Instance();

	m_pCommon->Delete_Instance();
	m_pDataManager->Delete_Instance();
	m_pAJinAXL->Delete_Instance();

	//m_pExtBarcode_Honeywell->Delete_Instance();
	m_pBarcode_DS1100->Delete_Instance();
	m_CSocketTCP->Delete_Instance();

	g_objCapAttachUDP.DestroyWindow();
}

BOOL CCMI4200LDlg::PreTranslateMessage(MSG* pMsg)
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CCMI4200LDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		Gloval_Initial();
		CSplashDlg dlgSplash;
		dlgSplash.Create(IDD_SPLASH_DLG, NULL);
		dlgSplash.ShowWindow(SW_SHOW);

		if (!m_pAJinAXL->Initialize_AJin()) { Exit_System(EXIT_SYSTEM_AJIN); return; }

		for (int i = 0; i < AXIS_COUNT; i++) {
			m_pAJinAXL->Read_MotionParam(i);
		}

		m_pDataManager->Read_EquipData();
		m_pDataManager->Read_ModelData();
		m_pDataManager->Read_MoveData();

		m_pInspector->Initialize_Inspector();
		Set_MainState(STATE_NONE);

		g_objCapAttachUDP.Initialize();

		m_nPrevMode = m_nCurrMode;
		m_nCurrMode = MODE_INITIAL;

		int nResult;
		//nResult = m_pExtBarcode_Honeywell->Connect();
		//if (nResult != 0 ) {
		//	m_pCommon->Show_MsgBox(1, "NG Barcde connection failed.");
		//}
		
		nResult = m_pBarcode_DS1100->Connect();
		if (nResult != 0 ) {
			m_pCommon->Show_MsgBox(1, "Lot Barcode connection failed.");
		}
		m_stcMainLabel.SetWindowText("Auto Vision Inspection - Initial Mode");

		EQUIP_DATA *pEquipData = m_pDataManager->Get_pEquipData();
		m_stcMainEquip.SetWindowText(pEquipData->sEquipName);

		g_objMES.Initialize(pEquipData->bUseMES);

#ifdef FTP_USE
		if (!m_pCommon->Connect_NetworkDrive(NETWORK_ADR_DRIVE, NETWORK_ADR_FOLDER)) {
			m_pCommon->Show_MsgBox(1, "ADR server network driver(R:) The connection failed.");
			//m_pCommon->Show_MsgBox(1, "ADR ���� ��Ʈ��ũ ����̺� (R:) ���� �����Դϴ�. Ȯ�� �� �����Ͽ� �ֽʽÿ�.");
		}
#endif
		CString sCreFile;
		m_pCommon->MakeFolder(ECM_LOG);
		sCreFile.Format("D:\\CMI4200L\\Run\\LOG\\Alarm\\Log\\");
		m_pCommon->MakeFolder(sCreFile);
		sCreFile.Format("D:\\CMI4200L\\Run\\LOG\\Handler\\History\\");
		m_pCommon->MakeFolder(sCreFile);
		sCreFile.Format("D:\\CMI4200L\\Run\\LOG\\MESAgent\\");
		m_pCommon->MakeFolder(sCreFile);

		char myCom[256];
		gethostname(myCom, sizeof(myCom));
		gData.sComName.Format("%s", myCom);

		CString strVersion;
		strVersion.Format("%s", MAIN_VERSION);
		m_stcMainVer.SetWindowText(strVersion);

		m_rdoMainInitial.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

		m_pInspector->Set_StatusUpdate(INSPECTOR_VISION, 0);
		m_pInspector->Set_StatusRequest(INSPECTOR_VISION);
		g_objCapAttachUDP.Set_StatusUpdate(0);

		//gData.sVersion = MAIN_VERSION;
		//gData.sSerialNo = SERIAL_NUMBER;
		//m_pManualLotDataDlg->LotData_Read();

#ifdef CM_PRESS
		gData.bUseCMPress = TRUE;
#else
		gData.bUseCMPress = FALSE;
#endif

		CIniFileCS INI("System/Inspection.ini");
		gTD.dCount[0] = INI.Get_Integer("COUNT", "COUNT_00", 0);
		gTD.dCount[1] = INI.Get_Integer("COUNT", "COUNT_01", 0);

		gData.sCaption[0] = INI.Get_String("MESSAGE", "001", "");
		gData.sCaption[1] = INI.Get_String("MESSAGE", "002", "");
		gData.sCaption[2] = INI.Get_String("MESSAGE", "003", "");

		CIniFileCS INI_E("System/EquipData.ini");
		INI_E.Set_Bool("OPTION", "DOOR_LOCK", TRUE);
		m_pDataManager->Read_EquipData();

		if (gData.sCaption[0].GetLength() > 0) m_rdoMainPause.SetWindowText(gData.sCaption[0]);

		m_pCommon->Delay_Time(1000);
		dlgSplash.DestroyWindow();

		m_pInitialDlg->ShowWindow(SW_SHOW);
		m_rdoMainInitial.SetCheck(TRUE);

		m_dwEquipProcTime = (DWORD)INI_E.Get_Integer("EQUIPMENT", "PROC_TIME", 0);

#ifdef PICKER_6
		gData.nPickCnt = 6;
#endif
#ifdef PICKER_4
		gData.nPickCnt = 4;
#endif
#ifdef PICKER_5
		gData.nPickCnt = 5;
#endif
#ifdef PICKER_3
		gData.nPickCnt = 3;
#endif
		Set_LotErrorLog("PROGRAM BEGIN", 900, "Program Begin");
	}
}

void CCMI4200LDlg::OnTimer(UINT_PTR nIDEvent)
{
	CCommon *pCommon = CCommon::Get_Instance();

	switch (nIDEvent) {
	case TIMER_DATE_TIME:
		Display_DateTime();
		pCommon->Check_InsideLamp();
		break;
	case TIMER_TOWER_FLKR:
		Set_TowerFlicker();
		break;
	case TIMER_DOOR_LOCK:
		Set_DoorLock();
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CCMI4200LDlg::OnBnClickedRdoMainInitial()
{
	Set_CurrentMode(MODE_INITIAL);
}

void CCMI4200LDlg::OnBnClickedRdoMainWork()
{
	/*if (gData.bOpMode) {
		if (m_pCommon->Show_Password() != IDOK) {
			if (m_nCurrMode == MODE_INITIAL) m_rdoMainInitial.SetCheck(TRUE);
			if (m_nCurrMode == MODE_WORK) m_rdoMainWork.SetCheck(TRUE);
			if (m_nCurrMode == MODE_MANUAL) m_rdoMainManual.SetCheck(TRUE);
			if (m_nCurrMode == MODE_SETUP) m_rdoMainSetup.SetCheck(TRUE);
			if (m_nCurrMode == MODE_PROHIBIT) m_rdoMainPause.SetCheck(TRUE);
			return;
		}
	}*/
	Set_CurrentMode(MODE_WORK);
	Invalidate(FALSE);
}

void CCMI4200LDlg::OnBnClickedRdoMainManual()
{
	/*if (gData.bOpMode) {
		if (m_pCommon->Show_Password() != IDOK) {
			if (m_nCurrMode == MODE_INITIAL) m_rdoMainInitial.SetCheck(TRUE);
			if (m_nCurrMode == MODE_WORK) m_rdoMainWork.SetCheck(TRUE);
			if (m_nCurrMode == MODE_MANUAL) m_rdoMainManual.SetCheck(TRUE);
			if (m_nCurrMode == MODE_SETUP) m_rdoMainSetup.SetCheck(TRUE);
			if (m_nCurrMode == MODE_PROHIBIT) m_rdoMainPause.SetCheck(TRUE);
			return;
		}
	}*/
	Set_CurrentMode(MODE_MANUAL);
	Invalidate(FALSE);
}

void CCMI4200LDlg::OnBnClickedRdoMainSetup()
{
	if (m_pCommon->Show_Password() == IDOK) {
		Set_CurrentMode(MODE_SETUP);
		Invalidate(FALSE);
	} else {
		if (m_nCurrMode == MODE_INITIAL) m_rdoMainInitial.SetCheck(TRUE);
		if (m_nCurrMode == MODE_WORK) m_rdoMainWork.SetCheck(TRUE);
		if (m_nCurrMode == MODE_MANUAL) m_rdoMainManual.SetCheck(TRUE);
		if (m_nCurrMode == MODE_SETUP) m_rdoMainSetup.SetCheck(TRUE);
		if (m_nCurrMode == MODE_PROHIBIT) m_rdoMainPause.SetCheck(TRUE);
	}
}

void CCMI4200LDlg::OnBnClickedBtnMainMonitor()
{
	if (m_pMonitorDlg->IsWindowVisible()) m_pMonitorDlg->ShowWindow(SW_HIDE);
	else m_pMonitorDlg->ShowWindow(SW_SHOW);	
}

void CCMI4200LDlg::OnBnClickedRdoMainPause()
{
	Set_CurrentMode(MODE_PROHIBIT);
}

void CCMI4200LDlg::OnBnClickedBtnMainSystemExit()
{
	if (m_pCommon->Show_MsgBox(2, "Are you sure you want to exit the program?") == IDOK) {
		Exit_System(EXIT_SYSTEM_NONE);
	}
}

void CCMI4200LDlg::OnBnClickedBtnMainOperator()
{
	Set_CurrentMode(MODE_WORK);
	m_pOperatorDlg->ShowWindow(SW_SHOW);
}

void CCMI4200LDlg::OnStnDblclickStcMainTime()
{
	CInspector *pInspector = CInspector::Get_Instance();
	pInspector->Set_TimeUpdate(INSPECTOR_VISION);
}

void CCMI4200LDlg::OnStnDblclickStcMainLabel()
{
	CWnd *pDeskTopWnd = GetDesktopWindow();
	if (!pDeskTopWnd) return;
	CWindowDC DeskTopDC(pDeskTopWnd);

	CImage imgScreen;
	int nX = GetSystemMetrics(SM_CXSCREEN);
	int nY = GetSystemMetrics(SM_CYSCREEN);
	if (!imgScreen.Create(nX, nY, 32)) return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strLog, strMsg, strFile, strPath = "D:\\Screen";
	m_pLogFile->Create_Folder(strPath);
	strFile.Format("%s\\%04d%02d%02d_%02d%02d%02d.png", strPath, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	HDC hDC = imgScreen.GetDC();
	BitBlt(hDC, 0, 0, nX, nY, DeskTopDC, 0, 0, SRCCOPY);

	imgScreen.Save(strFile, Gdiplus::ImageFormatPNG);
	imgScreen.ReleaseDC();

	strLog.Format("%s Screen Capture Completed.", strFile);
	m_pLogFile->Save_HandlerLog(strLog);

	strMsg.Format("%s\n\nScreen Capture Completed.", strFile);
	m_pCommon->Show_MsgBox(1, strMsg);
}

/////////////////////////////////////////////////////////////////////////////
// User Functions

void CCMI4200LDlg::Initial_Controls() 
{
	m_picMainBack.Init_Ctrl(RGB(0x00, 0x00, 0x00), RGB(0x80, 0xE0, 0xA0));
	m_stcMainDate.Init_Ctrl("����", 15, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x00, 0x00, 0x80));
	m_stcMainEquip.Init_Ctrl("����", 15, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x40));
	m_stcMainLabel.Init_Ctrl("����", 15, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
	m_stcMainVer.Init_Ctrl("����", 15, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x40));
	m_stcMainTime.Init_Ctrl("����", 15, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x00, 0x00, 0x80));
	m_stcMainOper.Init_Ctrl("����", 14, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x00, 0x00, 0x80));

	m_picModeBack.Init_Ctrl(RGB(0x00, 0x00, 0x00), RGB(0x80, 0xE0, 0xA0));
	m_rdoMainInitial.Init_Ctrl("����", 14, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_INITIAL, CRadioCS::emTop);
	m_rdoMainWork.Init_Ctrl("����", 14, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_WORK, CRadioCS::emTop);
	m_rdoMainManual.Init_Ctrl("����", 14, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_MANUAL, CRadioCS::emTop);
	m_rdoMainSetup.Init_Ctrl("����", 14, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_SETUP, CRadioCS::emTop);
	m_rdoMainPause.Init_Ctrl("����", 14, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_PAUSE, CRadioCS::emTop);
	m_btnMainMonitor.Init_Ctrl("����", 14, TRUE, RGB(0x00, 0xA0, 0x00), COLOR_DEFAULT, IDI_MONITOR, CButtonCS::emTop);
	m_btnMainSystemExit.Init_Ctrl("����", 14, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, IDI_SYSTEM_EXIT, CButtonCS::emTop);
	m_btnMainOperator.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, NULL, CButtonCS::emTop);
}

void CCMI4200LDlg::Hide_ModeWindows()
{
	m_rdoMainInitial.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoMainWork.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoMainManual.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoMainSetup.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoMainPause.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);

	if (m_nCurrMode == MODE_INITIAL) m_pInitialDlg->ShowWindow(SW_HIDE);
	if (m_nCurrMode == MODE_WORK) m_pWorkDlg->ShowWindow(SW_HIDE);
	if (m_nCurrMode == MODE_MANUAL) m_pManualDlg->ShowWindow(SW_HIDE);
	if (m_nCurrMode == MODE_SETUP) m_pSetupDlg->ShowWindow(SW_HIDE);
	if (m_nCurrMode == MODE_PROHIBIT) g_dlgPause.ShowWindow(SW_HIDE);

	m_nPrevMode = m_nCurrMode;
}

void CCMI4200LDlg::Enable_ModeButton(BOOL bEnable)
{
	m_rdoMainInitial.EnableWindow(bEnable);
	m_rdoMainWork.EnableWindow(bEnable);
	m_rdoMainManual.EnableWindow(bEnable);
	m_rdoMainSetup.EnableWindow(bEnable);
	m_rdoMainPause.EnableWindow(bEnable);
}

void CCMI4200LDlg::Exit_System(int nExitNo) 
{
	if (nExitNo == EXIT_SYSTEM_AJIN) m_pCommon->Show_MsgBox(1, "Ajin board initialization fails.");
	if (nExitNo == EXIT_SYSTEM_RFID) m_pCommon->Show_MsgBox(1, "RFID Control Port Open failure.");
	if (nExitNo == EXIT_SYSTEM_LASER) m_pCommon->Show_MsgBox(1, "Laser sensor Port Open failure.");
	if (nExitNo == EXIT_SYSTEM_ELECT) m_pCommon->Show_MsgBox(1, "Electrostatic sensor Port Open failure.");

	m_pLogFile->Save_HandlerLog("[Main Dialog] Program Exit");

	Set_LotErrorLog("PROGRAM EXIT", 909, "Program Exit");

	CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
	int nProcTime = (int)m_dwEquipProcTime;
	INI.Set_Integer("EQUIPMENT", "PROC_TIME", nProcTime);

	m_pInspector->Terminate_Inspector();
	m_pAJinAXL->Terminate_AJin();
	g_objCapAttachUDP.Terminate();

	//m_pExtBarcode_Honeywell->Disconnect();
	m_pBarcode_DS1100->Disconnect();
	m_CSocketTCP->Disconnect();

	KillTimer(TIMER_DOOR_LOCK);

	DestroyWindow();
}

void CCMI4200LDlg::Display_DateTime()
{
	CTime datetime = CTime::GetCurrentTime();

	CString strDate = datetime.Format("%Y-%m-%d");
	m_stcMainDate.SetWindowText(strDate);

	CString strTime = datetime.Format("%p %I:%M:%S");
	m_stcMainTime.SetWindowText(strTime);
	m_stcMainOper.SetWindowText(gData.sOperID);

	if (datetime.GetHour()==7) {
		if (gTD.nType==1) {
			gTD.nType = 0;
			for(int i=0; i<24; i++) {
				gTD.dTack[i][49] = 0.0;
			}
			for(int i=0; i<2; i++) {
				gTD.dCount[i] = 0;
			}
			LogAllDelete();
		}
	} else {
		gTD.nType = 1;
	}

	 if (gIt.nWriteHH != datetime.GetHour() && gData.sComName.GetLength() > 0) {
		CLogFile *pLogFile = CLogFile::Get_Instance();
		pLogFile->Save_Interlock(1);
	 }
}

void CCMI4200LDlg::Set_CurrentMode(int nMode)
{
	if (m_nCurrMode == nMode) return;
	Hide_ModeWindows();

	m_nCurrMode = nMode;

	m_stcMainLabel.Init_Ctrl("����", 15, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
	if (m_nCurrMode == MODE_INITIAL) {
		m_pInitialDlg->ShowWindow(SW_SHOW);
		m_stcMainLabel.SetWindowText("Auto Vision Inspection - Initial Mode");
		m_rdoMainInitial.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		if (!m_rdoMainInitial.GetCheck()) m_rdoMainInitial.SetCheck(TRUE);
		m_pLogFile->Save_HandlerLog("[Main Dialog] Initial Mode start");

	} else if (m_nCurrMode == MODE_WORK) {
		m_pWorkDlg->ShowWindow(SW_SHOW);
		m_stcMainLabel.SetWindowText("Auto Vision Inspection - Work Mode");
		m_rdoMainWork.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		if (!m_rdoMainWork.GetCheck()) m_rdoMainWork.SetCheck(TRUE);
		m_pLogFile->Save_HandlerLog("[Main Dialog] Work Mode start");

	} else if (m_nCurrMode == MODE_MANUAL) {
		m_pManualDlg->ShowWindow(SW_SHOW);
		m_stcMainLabel.SetWindowText("Auto Vision Inspection - Manual Mode");
		m_rdoMainManual.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		if (!m_rdoMainManual.GetCheck()) m_rdoMainManual.SetCheck(TRUE);
		m_pLogFile->Save_HandlerLog("[Main Dialog] Manual Mode start");

	} else if (m_nCurrMode == MODE_SETUP) {
		m_pSetupDlg->ShowWindow(SW_SHOW);
		m_stcMainLabel.SetWindowText("Auto Vision Inspection - Setup Mode");
		m_rdoMainSetup.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		if (!m_rdoMainSetup.GetCheck()) m_rdoMainSetup.SetCheck(TRUE);
		m_pLogFile->Save_HandlerLog("[Main Dialog] Setup Mode start");

	} else if (m_nCurrMode == MODE_PROHIBIT) {
		g_dlgPause.ShowWindow(SW_SHOW);
		m_stcMainLabel.SetWindowText("Auto Vision Inspection - Pause");
		m_rdoMainPause.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		if (!m_rdoMainPause.GetCheck()) m_rdoMainPause.SetCheck(TRUE);
		m_pLogFile->Save_HandlerLog("[Main Dialog] Pause Start");

	}

	if (gData.bUseDryRun) {
		m_stcMainLabel.Init_Ctrl("����", 20, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0xFF, 0x00, 0x00));
		m_stcMainLabel.SetWindowText("Dry Run Mode");
	}

	if (m_nCurrMode != MODE_PROHIBIT) m_rdoMainPause.SetCheck(FALSE);
	if (m_nPrevMode == MODE_INITIAL) m_rdoMainInitial.SetCheck(FALSE);
	if (m_nPrevMode == MODE_WORK) m_rdoMainWork.SetCheck(FALSE);
	if (m_nPrevMode == MODE_MANUAL) m_rdoMainManual.SetCheck(FALSE);
	if (m_nPrevMode == MODE_SETUP) m_rdoMainSetup.SetCheck(FALSE);

}

void CCMI4200LDlg::Do_Events()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void CCMI4200LDlg::Gloval_Initial()
{
	gData.nTotalCount = 0;
	gTD.nType = 1;
	gTD.dTackTime = 0.0;
	for(int i=0; i<24; i++) {
		for(int j=0; j<50; j++) {
			gTD.dTack[i][j] = 0.0;
		}
	}
	for(int i=0; i<2; i++) {
		gTD.dCount[i] = 0;
	}
}

void CCMI4200LDlg::Set_MainState(int nState)
{
	KillTimer(TIMER_TOWER_FLKR);

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	gData.m_nMS = nState;
	gData.m_bTowerOn = gData.m_bBuzzerOff = FALSE;

	// Tower
	pDY0->oTowerGreen = pEquipData->bTower[gData.m_nMS][0];
	pDY0->oTowerYellow = pEquipData->bTower[gData.m_nMS][1];
	pDY0->oTowerRed = pEquipData->bTower[gData.m_nMS][2];

	// Buzzer
	pDY0->oAlarmBuzzer1 = pEquipData->bTower[gData.m_nMS][4];
	pDY0->oAlarmBuzzer2 = pEquipData->bTower[gData.m_nMS][5];

	// Start, Stop, Reset SW
	switch (gData.m_nMS) {
	case STATE_NONE:
		pDY0->oStartLamp = FALSE;
		pDY0->oStopLamp = FALSE;
		pDY0->oResetLamp = FALSE;
		break;
	case STATE_INITEND:
	case STATE_LOTEND:
		pDY0->oStartLamp = FALSE;
		pDY0->oStopLamp = TRUE;
		pDY0->oResetLamp = FALSE;
		break;
	case STATE_RUN:
		pDY0->oStartLamp = TRUE;
		pDY0->oStopLamp = FALSE;
		pDY0->oResetLamp = FALSE;
		break;
	case STATE_ALARM:
	case STATE_EMER:
		pDY0->oStartLamp = FALSE;
		pDY0->oStopLamp = FALSE;
		pDY0->oResetLamp = TRUE;
		break;
	}
	pAJinAXL->Write_Output(0);

	// Flicker
	if (pEquipData->bTower[nState][3] || pEquipData->bTower[nState][6]) SetTimer(TIMER_TOWER_FLKR, 500, NULL);
}

void CCMI4200LDlg::Set_TowerFlicker()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	if (gData.m_bTowerOn) {
		gData.m_bTowerOn = FALSE;
		if (pEquipData->bTower[gData.m_nMS][3]) {
			pDY0->oTowerGreen = FALSE;
			pDY0->oTowerYellow = FALSE;
			pDY0->oTowerRed = FALSE;
		}		
		if (pEquipData->bTower[gData.m_nMS][6]) {
			pDY0->oAlarmBuzzer1 = FALSE;
			pDY0->oAlarmBuzzer2 = FALSE;
		}
	} else {
		gData.m_bTowerOn = TRUE;
		if (pEquipData->bTower[gData.m_nMS][3]) {
			pDY0->oTowerGreen = pEquipData->bTower[gData.m_nMS][0];
			pDY0->oTowerYellow = pEquipData->bTower[gData.m_nMS][1];
			pDY0->oTowerRed = pEquipData->bTower[gData.m_nMS][2];
		}
		if (pEquipData->bTower[gData.m_nMS][6]) {
			pDY0->oAlarmBuzzer1 = pEquipData->bTower[gData.m_nMS][4];
			pDY0->oAlarmBuzzer2 = pEquipData->bTower[gData.m_nMS][5];
		}
	}
	if (gData.m_bBuzzerOff == TRUE) {
		pDY0->oAlarmBuzzer1 = FALSE;
		pDY0->oAlarmBuzzer2 = FALSE;
	}
	pAJinAXL->Write_Output(0);
}

void CCMI4200LDlg::Set_DoorLock()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	if (pEquipData->bUseDoorLock) return;
	if (gData.dwDoorStartTime <= 0) gData.dwDoorStartTime = GetTickCount();

	DWORD dwCurrentTime = GetTickCount();
	DWORD dwDoorEndTime = DWORD(gData.dDoorLockTime) * 60 * 1000;	//��
	if (dwCurrentTime - gData.dwDoorStartTime >= dwDoorEndTime) {
		CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
		if (!INI.Check_File()) return;
		INI.Set_Bool("OPTION", "DOOR_LOCK", TRUE);

		m_pLogFile->Save_HandlerLog("Door Lock�� Auto�� ���� �Ͽ����ϴ�...");

		gData.dwDoorStartTime = 0;
		pDataManager->Read_EquipData();

//		CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
//		pWorkDlg->PostMessage(UM_UPDATE_MODEL, NULL, NULL);
	}
}

void CCMI4200LDlg::LogAllDelete()
{
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\Alarm");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\Alarm\\Log");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\Handler");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\Handler\\History");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\MESAgent");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\Inspector");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\JobList");
}

void CCMI4200LDlg::LogFileDelete(CString sPath)
{
    CTime CurTime = CTime::GetCurrentTime();
    CTime DayXTime;
    DayXTime = CurTime - CTimeSpan(LOG_DELETE_DAY, 0, 0, 0);
    CString path, file_path, file_name;
    path.Format("%s\\*.*", sPath);
    CFileFind finder;
    BOOL bRes;
    bRes = finder.FindFile(path);

    while(bRes)
    {
        bRes = finder.FindNextFile();
        if(!finder.IsDirectory())
        {
            bool bDelete = true;

            file_name = finder.GetFileName();
            file_path.Format("%s\\%s", sPath, file_name);

            if(file_name.GetLength() >= 8) {
                int nLogYear = _ttoi(file_name.Left(4));
                int nLogMonth = _ttoi(file_name.Mid(4, 2));
                int nLogDay = _ttoi(file_name.Mid(6, 2));
				
				if (nLogYear>2000 && nLogMonth > 0 && nLogMonth < 13 && nLogDay > 0 && nLogDay < 32) {
					CTime LogTime(nLogYear, nLogMonth, nLogDay, 0, 0, 0, 0);
					if(LogTime >= DayXTime) bDelete = false;
				}
            }   

            if(bDelete) DeleteFile(file_path);
        }
    }
}


void CCMI4200LDlg::Set_LotErrorLog(CString sEvent, int nErrCode, CString sMessage)
{
	CString strModel, strAction, strLog;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	strModel = pEquipData->sCurrModel;

	if (gData.sLotID == "") gData.sLotID = "LOT_ID";

	strAction.Format("%0.3lf", (GetTickCount() - m_dwEquipProcTime) / 1000.0);
	m_dwEquipProcTime = GetTickCount();

	strLog.Format("%s,%s,%s,%s,%04d,%s,%s,", strModel, MAIN_VERSION, gData.sLotID, sEvent, nErrCode, sMessage, strAction);
	m_pLogFile->Save_AVIError(strLog);
}
///////////////////////////////////////////////////////////////////////////////
