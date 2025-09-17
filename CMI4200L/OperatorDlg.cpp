// OperatorDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "OperatorDlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"
#include "Common.h"
#include "DataManager.h"
#include "CMI4200LDlg.h"
#include "MonitorDlg.h"
#include "LogFile.h"

// COperatorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COperatorDlg, CDialogEx)

COperatorDlg *COperatorDlg::m_pInstance = NULL;

COperatorDlg *COperatorDlg::Get_Instance(CWnd *pParent)
{
	if (!m_pInstance) {
		m_pInstance = new COperatorDlg(pParent);
		if (!m_pInstance->m_hWnd) {
			m_pInstance->Create(IDD_OPERATOR_DLG, pParent);
		}
	}
	return m_pInstance;
}

void COperatorDlg::Delete_Instance()
{
	if (m_pInstance->m_hWnd) m_pInstance->DestroyWindow();
	if (m_pInstance) delete m_pInstance;
	m_pInstance = NULL;
}

COperatorDlg::COperatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COperatorDlg::IDD, pParent)
{
}

COperatorDlg::~COperatorDlg()
{
}

void COperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE_LOGO, m_Image);
	DDX_Control(pDX, IDC_STC_OPER_EQP, m_stcEqpName); 
	DDX_Control(pDX, IDC_STC_OPER_DATE, m_stcDate); 
	DDX_Control(pDX, IDC_STC_OPER_TIME, m_stcTime); 
	DDX_Control(pDX, IDC_STC_OPER_VER, m_stcVer); 
	for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_PIC_OPER_IMG_0 + i, m_picOperImg[i]);
	for (int i = 0; i < 30; i++) DDX_Control(pDX, IDC_OPERR_LABEL_0 + i, m_Label[i]);

	DDX_Control(pDX, IDC_BTN_OPER_INITIAL, m_btnOperInitial);
	DDX_Control(pDX, IDC_BTN_OPER_WORK, m_btnOperWork);
	DDX_Control(pDX, IDC_BTN_OPER_MANUAL, m_btnOperManual);
	DDX_Control(pDX, IDC_BTN_OPER_SETUP, m_btnOperSetup);
	DDX_Control(pDX, IDC_BTN_OPER_MONITOR, m_btnOperMonitor);
	DDX_Control(pDX, IDC_BTN_OPER_EXIT, m_btnOperExit);
	DDX_Control(pDX, IDC_BTN_OPER_START, m_btnOperStart);
	DDX_Control(pDX, IDC_BTN_OPER_STOP, m_btnOperStop);
	DDX_Control(pDX, IDC_BTN_OPER_EXCHANGE, m_btnOperTray);
	DDX_Control(pDX, IDC_BTN_OPER_CLEANOUT, m_btnOperCleanOut);
	DDX_Control(pDX, IDC_BTN_OPER_ENGINEER, m_btnOperEngineer);

	DDX_Control(pDX, IDC_STC_OPER_LOTID, m_stcOperLotID);
	DDX_Control(pDX, IDC_STC_OPER_OPERID, m_stcOperOperID);
	DDX_Control(pDX, IDC_STC_OPER_CMCNT, m_stcOperCMCnt);

	DDX_Control(pDX, IDC_GRD_DATA_0, m_grdData[0]);
	DDX_Control(pDX, IDC_GRD_DATA_1, m_grdData[1]);
}

BEGIN_MESSAGE_MAP(COperatorDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_OPER_INITIAL, &COperatorDlg::OnBnClickedBtnOperInitial)
	ON_BN_CLICKED(IDC_BTN_OPER_WORK, &COperatorDlg::OnBnClickedBtnOperWork)
	ON_BN_CLICKED(IDC_BTN_OPER_MANUAL, &COperatorDlg::OnBnClickedBtnOperManual)
	ON_BN_CLICKED(IDC_BTN_OPER_SETUP, &COperatorDlg::OnBnClickedBtnOperSetup)
	ON_BN_CLICKED(IDC_BTN_OPER_MONITOR, &COperatorDlg::OnBnClickedBtnOperMonitor)
	ON_BN_CLICKED(IDC_BTN_OPER_EXIT, &COperatorDlg::OnBnClickedBtnOperExit)
	ON_BN_CLICKED(IDC_BTN_OPER_START, &COperatorDlg::OnBnClickedBtnOperStart)
	ON_BN_CLICKED(IDC_BTN_OPER_STOP, &COperatorDlg::OnBnClickedBtnOperStop)
	ON_BN_CLICKED(IDC_BTN_OPER_EXCHANGE, &COperatorDlg::OnBnClickedBtnOperTray)
	ON_BN_CLICKED(IDC_BTN_OPER_CLEANOUT, &COperatorDlg::OnBnClickedBtnOperCleanOut)
	ON_BN_CLICKED(IDC_BTN_OPER_ENGINEER, &COperatorDlg::OnBnClickedBtnOperEngineer)
	ON_BN_CLICKED(IDC_BTN_OPER_TEST, &COperatorDlg::OnBnClickedBtnOperTest)

	ON_BN_CLICKED(IDC_STC_OPER_LOTID, &COperatorDlg::OnBnClickedLotID)
	ON_BN_CLICKED(IDC_STC_OPER_OPERID, &COperatorDlg::OnBnClickedOperID)
	ON_BN_CLICKED(IDC_STC_OPER_CMCNT, &COperatorDlg::OnBnClickedCMCnt)
END_MESSAGE_MAP()

// COperatorDlg 메시지 처리기입니다.

BOOL COperatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COperatorDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL COperatorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void COperatorDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		CDataManager *pDataManager = CDataManager::Get_Instance();
		EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
		m_stcEqpName.SetWindowText(pEquipData->sEquipName);

		CString strVersion;
		strVersion.Format("%s", MAIN_VERSION);
		m_stcVer.SetWindowText(strVersion);

		MODEL_DATA *pModelData = pDataManager->Get_pModelData();
		m_Label[15].SetWindowText(pModelData->sModelName);

		if (pEquipData->bUseDoorLock) {
			m_Label[24].Init_Ctrl("Segoe UI", 18, TRUE, RGB(0x00, 0x00, 0x00),RGB(0x00, 0xFF, 0x00));
			m_Label[25].Init_Ctrl("Segoe UI", 18, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xF0, 0xF0, 0xF0));
		} else {
			m_Label[24].Init_Ctrl("Segoe UI", 18, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xF0, 0xF0, 0xF0));
			m_Label[25].Init_Ctrl("Segoe UI", 18, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xFF, 0x00, 0x00));
		}
		
		CString strText;
		m_stcOperLotID.SetWindowText(gData.sLotID);
		m_stcOperOperID.SetWindowText(gData.sOperID);
		strText.Format("%d", gData.nCMJobCount);
		m_stcOperCMCnt.SetWindowText(strText);

		/*gData.bOpMode = TRUE;
		Enable_ModeButton(FALSE, FALSE);*/
		Display_Status();
		SetTimer(0, 200, NULL);
	} else {
		KillTimer(0);
	}
}

void COperatorDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(0);

	Display_Status();

	SetTimer(0, 300, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

HBRUSH COperatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG)
		return (HBRUSH)GetStockObject(WHITE_BRUSH);

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void COperatorDlg::Initial_Controls() 
{
	m_bmpImage.LoadBitmap(IDB_LGINNOTEK_LOGO);
	m_Image.SetBitmap(m_bmpImage);
	m_Image.SetWindowPos(this, 0, 0, 200, 38, SWP_NOMOVE | SWP_NOZORDER);

	m_stcEqpName.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	m_stcDate.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	m_stcTime.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	m_stcVer.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));

	for (int i = 0; i < 1; i++) m_picOperImg[i].Init_Ctrl(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xFF));
	for (int i = 1; i < 8; i++) m_picOperImg[i].Init_Ctrl(COLOR_DEFAULT, RGB(0xE6, 0xE6, 0xE6));
	for (int i = 7; i <10; i++) m_picOperImg[i].Init_Ctrl(COLOR_DEFAULT, RGB(0xF0, 0xF0, 0xF0));
	m_picOperImg[10].Init_Ctrl(COLOR_DEFAULT, RGB(0xE6, 0xE6, 0xE6));

	for (int i = 0; i < 2; i++) m_Label[i].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xE6, 0xE6, 0xE6));

	m_Label[2].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xEB, 0xEB, 0xEB));
	m_Label[9].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xEB, 0xEB, 0xEB));
	m_Label[16].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xEB, 0xEB, 0xEB));

	for (int i = 3; i < 6; i++) m_Label[i].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xFF, 0xFF, 0xFF));
	for (int i = 6; i < 9; i++) m_Label[i].Init_Ctrl("Segoe UI", 10, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xFF, 0xFF, 0xFF));
	for (int i =10; i <16; i++) m_Label[i].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xFF, 0xFF, 0xFF));
	for (int i =17; i <23; i++) m_Label[i].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xFF, 0xFF, 0xFF));

	m_Label[23].Init_Ctrl("Segoe UI", 18, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xEB, 0xEB, 0xEB));
	m_Label[24].Init_Ctrl("Segoe UI", 18, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xF0, 0xF0, 0xF0));
	m_Label[25].Init_Ctrl("Segoe UI", 18, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xF0, 0xF0, 0xF0));
	m_Label[26].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xEB, 0xEB, 0xEB));
	m_Label[27].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xFF, 0xFF, 0xFF));
	m_Label[28].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xFF, 0xFF, 0xFF));
	m_Label[29].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00),RGB(0xFF, 0xFF, 0xFF));

	m_stcOperLotID.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	m_stcOperOperID.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	m_stcOperCMCnt.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));

	m_btnOperInitial.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperWork.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperManual.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperSetup.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperMonitor.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperExit.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperStart.Init_Ctrl("Segoe UI", 40, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperStop.Init_Ctrl("Segoe UI", 40, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperTray.Init_Ctrl("Segoe UI", 30, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperCleanOut.Init_Ctrl("Segoe UI", 30, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);

	m_btnOperEngineer.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	Initial_Grid(&m_grdData[0], 8, 5);
	Initial_Grid(&m_grdData[1], 8, 5);
}

void COperatorDlg::Initial_Grid(CGridCS *pGrid, int nRows, int nCols)
{
	pGrid->Set_RowCount(nRows);
	pGrid->Set_ColCount(nCols);
	pGrid->Set_FixRowCount(0);
	pGrid->Set_FixColCount(0);

	long lTotalW = pGrid->Get_GridWidth();
	long lTotalH = pGrid->Get_GridHeight();
	long lCellW = lTotalW / nCols;
	long lCellH = lTotalH / nRows;

	CString str;
	for (int i = 0; i < nRows; i++) {
		pGrid->Set_RowHeight(i, lCellH);

		for (int j = 0; j < nCols; j++) {
			if (i == 0) pGrid->Set_ColWidth(j, lCellW);

			pGrid->Set_CellAlign(i, j, CELL_ALIGN_CENTER);
			str.Format(_T("%d"), i * nCols + j + 1);
			pGrid->Set_CellText(i, j, str);
		}
	}
}

void COperatorDlg::OnBnClickedBtnOperStart()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CDataManager *pDataManager = CDataManager::Get_Instance();
	
	if (gData.bUseAllPass) {
		pCommon->Show_MsgBox(1, "Not allowed [All Pass] in operator mode.......");
		return;
	}

	if (gData.bCleanOutMode) {
		if (pCommon->Show_MsgBox(2, "Are you sure you want to Start by Clean Out Mode.....") != IDOK) return;
	}

	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	if (pWorkDlg->Check_Start()==FALSE) return;

	pWorkDlg->m_rdoWorkStart.SetCheck(TRUE);
	Enable_ModeButton(FALSE, FALSE);

	CString sLog;
	CLogFile *pLogFile = CLogFile::Get_Instance();
	sLog.Format("[Operator] START button push....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
	pLogFile->Save_HandlerLog(sLog);
}

void COperatorDlg::OnBnClickedBtnOperStop()
{
	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	pWorkDlg->m_rdoWorkStop.SetCheck(TRUE);
	Enable_ModeButton(TRUE, gData.bOpMode);

	CString sLog;
	CLogFile *pLogFile = CLogFile::Get_Instance();
	sLog.Format("[Operator] STOP button push....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
	pLogFile->Save_HandlerLog(sLog);

	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	pMainDlg->Set_MainState(STATE_INITEND);
}

void COperatorDlg::OnBnClickedBtnOperTray()
{
	if(gData.nNGTrayPos != 0){
		CCommon *pCommon = CCommon::Get_Instance();
		pCommon->Show_MsgBox(1, "Equipment Run Status Error,     NG Tray Position Error");
		return;
	}
	
	//Tray Data Clear..
	for(int i = 0; i<20; i++){
		for(int j=0; j<20; j++){
			gData.NG1TrayInfo[i][j] = 0;
			gData.NG2TrayInfo[i][j] = 0;
		}
	}
	
	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
	pSequenceMain->Set_RunCase(AUTO_NGTRAY, 100);

	m_btnOperTray.Init_Ctrl("Segoe UI", 30, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0x00), NULL, CButtonCS::emTop);
	m_btnOperTray.Invalidate(FALSE);

	CString sLog;
	CLogFile *pLogFile = CLogFile::Get_Instance();
	sLog.Format("[Operator] Tray Exchange button push....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
	pLogFile->Save_HandlerLog(sLog);

}
void COperatorDlg::OnBnClickedBtnOperCleanOut()
{
	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();

	if (pWorkDlg->m_rdoWorkStart.GetCheck()) {
		pCommon->Show_MsgBox(1, "Run중에는 Clean Out Mode를 설정 할수 없습니다........");
		return;
	}

	if (pCommon->Show_MsgBox(2, "Are you sure you want to Clean Out?") != IDOK) return;

	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
	pSequenceMain->Set_RunCase(AUTO_INSPECT, 100);
	pSequenceMain->Set_RunCase(AUTO_BARCODE, 100);
	gData.bCleanOutMode = TRUE;

	m_btnOperCleanOut.Init_Ctrl("Segoe UI", 30, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xB7, 0xDE, 0xE8), NULL, CButtonCS::emTop);
	m_btnOperCleanOut.Invalidate(FALSE);

	CString sLog;
	CLogFile *pLogFile = CLogFile::Get_Instance();
	sLog.Format("[Operator] Clean Out button push....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
	pLogFile->Save_HandlerLog(sLog);

}

void COperatorDlg::Hide_Windows()
{
	ShowWindow(SW_HIDE);
}

void COperatorDlg::OnBnClickedBtnOperInitial()
{
	ShowWindow(SW_HIDE);
	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	pMainDlg->Set_CurrentMode(MODE_INITIAL);
}
void COperatorDlg::OnBnClickedBtnOperWork()
{
	ShowWindow(SW_HIDE);
	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	pMainDlg->Set_CurrentMode(MODE_WORK);
}
void COperatorDlg::OnBnClickedBtnOperManual()
{
	ShowWindow(SW_HIDE);
	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	pMainDlg->Set_CurrentMode(MODE_MANUAL);
}
void COperatorDlg::OnBnClickedBtnOperSetup()
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (pCommon->Show_Password() != IDOK) return;

	ShowWindow(SW_HIDE);
	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	pMainDlg->Set_CurrentMode(MODE_SETUP);
}
void COperatorDlg::OnBnClickedBtnOperMonitor()
{
	CMonitorDlg *pMonitorDlg = CMonitorDlg::Get_Instance();
	if (pMonitorDlg->IsWindowVisible()) pMonitorDlg->ShowWindow(SW_HIDE);
	else pMonitorDlg->ShowWindow(SW_SHOW);	
}
void COperatorDlg::OnBnClickedBtnOperExit()
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (pCommon->Show_MsgBox(2, "Are you sure you want to exit the program?") == IDOK) {

		CString sLog;
		CLogFile *pLogFile = CLogFile::Get_Instance();
		sLog.Format("[Operator] Program Exit button push....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
		pLogFile->Save_HandlerLog(sLog);

		CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
		pMainDlg->Exit_System(EXIT_SYSTEM_NONE);
	}
}

void COperatorDlg::OnBnClickedBtnOperEngineer()
{
	CCommon *pCommon = CCommon::Get_Instance();
	//if (pCommon->Show_Password() != IDOK) return;
	ShowWindow(SW_HIDE);
	gData.bOpMode = FALSE;
	Enable_ModeButton(TRUE, gData.bOpMode);
}

void COperatorDlg::OnBnClickedLotID()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	if (pWorkDlg->m_rdoWorkStart.GetCheck() && gData.nDoorInterlock18 != 1) {
		pCommon->Show_MsgBox(1, "Run중에는 Lot ID를 수정 할수 없습니다........");
		return;
	}

	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcOperLotID.SetWindowText(strKey);
		pWorkDlg->m_stcLotId1.SetWindowText(strKey);
		gData.sLotID = strKey;

		CString sLog;
		CLogFile *pLogFile = CLogFile::Get_Instance();
		sLog.Format("[Operator] Lot ID Input....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
		pLogFile->Save_HandlerLog(sLog);
	}
}

void COperatorDlg::OnBnClickedOperID()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();

	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcOperOperID.SetWindowText(strKey);
		gData.sOperID = strKey;

		CString sLog;
		CLogFile *pLogFile = CLogFile::Get_Instance();
		sLog.Format("[Operator] Operator ID Input....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
		pLogFile->Save_HandlerLog(sLog);
	}
}

void COperatorDlg::OnBnClickedCMCnt()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	if (pWorkDlg->m_rdoWorkStart.GetCheck() && gData.nDoorInterlock18 != 1) {
		pCommon->Show_MsgBox(1, "Run중에는 CM수량 입력을 할수 없습니다........");
		return;
	}

	CString strOld, strNew;
	int nCM, nCM1, nCM2; 
	m_stcOperCMCnt.GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcOperCMCnt.SetWindowText(strNew);
		pWorkDlg->m_stcCMCnt.SetWindowText(strNew);
		nCM = atoi(strNew);
		gData.nCMJobCount = nCM;

		nCM1 = nCM / gData.nCMMaxCount;
		nCM2 = nCM % gData.nCMMaxCount;
		if(nCM2 > 0) nCM1++;
		gData.nTrayJobCount = nCM1;
		strNew.Format("%d", gData.nTrayJobCount);
		pWorkDlg->m_stcLotId2.SetWindowText(strNew);  

		CString sLog;
		CLogFile *pLogFile = CLogFile::Get_Instance();
		sLog.Format("[Operator] CM Count Input....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
		pLogFile->Save_HandlerLog(sLog);

	}
}

void COperatorDlg::Display_Status()
{
	CTime datetime = CTime::GetCurrentTime();

	CString strDate = datetime.Format("%Y-%m-%d");
	m_stcDate.SetWindowText(strDate);

	CString strTime = datetime.Format("%p %I:%M:%S");
	m_stcTime.SetWindowText(strTime);

	// Start/Stop botton
	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	if (pWorkDlg->m_rdoWorkStart.GetCheck()) {
		m_btnOperStart.Init_Ctrl("Segoe UI", 40, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x00, 0xFF, 0x00), NULL, CButtonCS::emTop);
		m_btnOperStop.Init_Ctrl("Segoe UI", 40, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
		m_btnOperTray.Init_Ctrl("Segoe UI", 30, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
		m_btnOperStart.Invalidate(FALSE);
		m_btnOperStop.Invalidate(FALSE);
		m_btnOperTray.Invalidate(FALSE);
		Enable_ModeButton(FALSE, FALSE);
	}
	if (pWorkDlg->m_rdoWorkStop.GetCheck()) {
		m_btnOperStop.Init_Ctrl("Segoe UI", 40, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0x00, 0x00), NULL, CButtonCS::emTop);
		m_btnOperStart.Init_Ctrl("Segoe UI", 40, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
		m_btnOperStart.Invalidate(FALSE);
		m_btnOperStop.Invalidate(FALSE);
		Enable_ModeButton(TRUE, gData.bOpMode);
	}

	// Tower
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	if (pDY0->oTowerRed)	m_picOperImg[7].Init_Ctrl(COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));
	else					m_picOperImg[7].Init_Ctrl(COLOR_DEFAULT, RGB(0xF0, 0xF0, 0xF0));
	if (pDY0->oTowerYellow)	m_picOperImg[8].Init_Ctrl(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));
	else					m_picOperImg[8].Init_Ctrl(COLOR_DEFAULT, RGB(0xF0, 0xF0, 0xF0));
	if (pDY0->oTowerGreen)	m_picOperImg[9].Init_Ctrl(COLOR_DEFAULT, RGB(0x00, 0xFF, 0x00));
	else					m_picOperImg[9].Init_Ctrl(COLOR_DEFAULT, RGB(0xF0, 0xF0, 0xF0));
	for(int i=7; i<10; i++) m_picOperImg[i].Invalidate(FALSE);

	if (gData.bCleanOutMode) m_btnOperCleanOut.Init_Ctrl("Segoe UI", 30, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xB7, 0xDE, 0xE8), NULL, CButtonCS::emTop);
	else					 m_btnOperCleanOut.Init_Ctrl("Segoe UI", 30, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);

	m_Label[3].SetWindowText(gData.sAlarmTime[0]);
	m_Label[4].SetWindowText(gData.sAlarmTime[1]);
	m_Label[5].SetWindowText(gData.sAlarmTime[2]);
	m_Label[6].SetWindowText(gData.sAlarmList[0]);
	m_Label[7].SetWindowText(gData.sAlarmList[1]);
	m_Label[8].SetWindowText(gData.sAlarmList[2]);
	for(int i=3; i<9; i++) m_Label[i].Invalidate(FALSE);

	CString strText;
	strText.Format("%d", gLot.nGoodCnt);
	m_Label[20].SetWindowText(strText);

	strText.Format("%d", gLot.nNGCnt);
	m_Label[21].SetWindowText(strText);

	if ((gLot.nGoodCnt + gLot.nNGCnt) < 1) strText = "0.0";
	else strText.Format("%0.1lf", gLot.nGoodCnt * 100.0 / (gLot.nGoodCnt + gLot.nNGCnt));
	strText = strText + "%";
	m_Label[22].SetWindowText(strText);
	for(int i=20; i<23; i++) m_Label[i].Invalidate(FALSE);

	for(int y=0; y<gData.nArrayW; y++) {		//8
		for(int x=0; x<gData.nArrayL; x++) {	//5
			if		(gData.NG1TrayInfo[y][x] == 0)	m_grdData[0].Set_CellBackClr(y, x, RGB(0xFF, 0xFF, 0xFF));
			else if	(gData.NG1TrayInfo[y][x] == 1)	m_grdData[0].Set_CellBackClr(y, x, RGB(0x00, 0xFF, 0x00));
			else if (gData.NG1TrayInfo[y][x] == 2)	m_grdData[0].Set_CellBackClr(y, x, RGB(0xFF, 0x00, 0x00));
			else if (gData.NG1TrayInfo[y][x] == 3)	m_grdData[0].Set_CellBackClr(y, x, RGB(0x00, 0x00, 0xFF));
			else									m_grdData[0].Set_CellBackClr(y, x, RGB(0x00, 0x00, 0x00));

			if		(gData.NG2TrayInfo[y][x] == 0)	m_grdData[1].Set_CellBackClr(y, x, RGB(0xFF, 0xFF, 0xFF));
			else if	(gData.NG2TrayInfo[y][x] == 1)	m_grdData[1].Set_CellBackClr(y, x, RGB(0x00, 0xFF, 0x00));
			else if (gData.NG2TrayInfo[y][x] == 2)	m_grdData[1].Set_CellBackClr(y, x, RGB(0xFF, 0x00, 0x00));
			else if (gData.NG2TrayInfo[y][x] == 3)	m_grdData[1].Set_CellBackClr(y, x, RGB(0x00, 0x00, 0xFF));
			else									m_grdData[1].Set_CellBackClr(y, x, RGB(0x00, 0x00, 0x00));
		}
	}
}

void COperatorDlg::Enable_ModeButton(BOOL bEnable, BOOL bOpMode)
{
	m_btnOperInitial.EnableWindow(bEnable);
	if (!bOpMode) m_btnOperWork.EnableWindow(bEnable);
	if (!bOpMode) m_btnOperManual.EnableWindow(bEnable);
	if (!bOpMode) m_btnOperSetup.EnableWindow(bEnable);
}

///////////////////////////////////////////////////////////////////////////////


void COperatorDlg::OnBnClickedBtnOperTest()
{
	CSequenceInit *pSequenceInit = CSequenceInit::Get_Instance();
	pSequenceInit->Set_InitComplete(TRUE);

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
	DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();
	DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();
	DX_DATA_6 *pDX6 = pAJinAXL->Get_pDX6();
	CCommon *pCommon = CCommon::Get_Instance();

	pDX3->iNGTray1Check = TRUE;
	pDX3->iNGTray2Check = TRUE;

	pDX1->iLS_Load1FCheck = TRUE;
	pDX6->iUS_Load1FCheck = TRUE;
	pDX0->iMainDoor1Close = TRUE;
	pDY0->oTowerRed = TRUE;
	pDY0->oTowerGreen = TRUE;

	gLot.nGoodCnt = 10;
	gLot.nNGCnt   = 90;

	gData.NG1TrayInfo[0][0] = 4;
	gData.NG1TrayInfo[1][2] = 1;
	gData.NG1TrayInfo[6][3] = 2;
	gData.NG1TrayInfo[7][4] = 3;

	gData.NG2TrayInfo[0][0] = 4;
	gData.NG2TrayInfo[1][2] = 1;
	gData.NG2TrayInfo[6][3] = 2;
	gData.NG2TrayInfo[7][4] = 3;
}

