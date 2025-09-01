// InitialDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "InitialDlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "Inspector.h"

#include "CMI4200LDlg.h"
#include "LogFile.h"
#include "OperatorDlg.h"
#include "MESInterface.h"

// CInitialDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInitialDlg, CDialogEx)

CInitialDlg *CInitialDlg::m_pInstance = NULL;

CInitialDlg *CInitialDlg::Get_Instance(CWnd *pParent)
{
	if (!m_pInstance) {
		m_pInstance = new CInitialDlg(pParent);
		if (!m_pInstance->m_hWnd) {
			m_pInstance->Create(IDD_INITIAL_DLG, pParent);
		}
	}
	return m_pInstance;
}

void CInitialDlg::Delete_Instance()
{
	if (m_pInstance->m_hWnd) m_pInstance->DestroyWindow();
	if (m_pInstance) delete m_pInstance;
	m_pInstance = NULL;
}

CInitialDlg::CInitialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInitialDlg::IDD, pParent)
{
}

CInitialDlg::~CInitialDlg()
{
}

void CInitialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 25; i++) DDX_Control(pDX, IDC_STC_AXIS_NAME_0 + i, m_stcAxisName[i]); 
	for (int i = 0; i < 25; i++) DDX_Control(pDX, IDC_LED_AXIS_RUN_0 + i, m_ledAxisRun[i]);
	for (int i = 0; i < 25; i++) DDX_Control(pDX, IDC_LED_AXIS_HOM_0 + i, m_ledAxisHom[i]);
	DDX_Control(pDX, IDC_LED_INIT_OK, m_ledInitOK);

	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_STC_INIT_CASE_0 + i, m_stcInitCase[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_IMAGE_0 + i, m_Image[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_PIC_INIT_FLOW_0 + i, m_picInitFlow[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_STC_INIT_FLOW_0 + i, m_stcInitFlow[i]);
	DDX_Control(pDX, IDC_RDO_INIT_START, m_rdoInitStart);
	DDX_Control(pDX, IDC_RDO_INIT_STOP, m_rdoInitStop);
	DDX_Control(pDX, IDC_STC_INIT_STRIP_SIZE, m_stcInitStripSize);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_MAIN_AIR_0 + i, m_ledMainAir[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LED_MAIN_DOOR_0 + i, m_ledMainDoor[i]);
	DDX_Control(pDX, IDC_LED_BUFF_DOOR_0, m_ledBuffDoor);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_LOWER_DOOR_0 + i, m_ledLowerDoor[i]);

	DDX_Control(pDX, IDC_STC_AXIS_NAME_25 , m_stcAxisName[25]); 
	DDX_Control(pDX, IDC_STC_AXIS_NAME_26 , m_stcAxisName[26]); 

	DDX_Control(pDX, IDC_LED_AXIS_RUN_25 , m_ledAxisRun[25]);
	DDX_Control(pDX, IDC_LED_AXIS_RUN_26 , m_ledAxisRun[26]);

	DDX_Control(pDX, IDC_LED_AXIS_HOM_25 , m_ledAxisHom[25]);
	DDX_Control(pDX, IDC_LED_AXIS_HOM_26 , m_ledAxisHom[26]);

	DDX_Control(pDX,  IDC_LED_MAIN_DOOR_6 , m_ledMainDoor[6]);
	DDX_Control(pDX, IDC_LED_MAIN_DOOR_7 , m_ledMainDoor[7]);
	
}

BEGIN_MESSAGE_MAP(CInitialDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RDO_INIT_START, &CInitialDlg::OnBnClickedRdoInitStart)
	ON_BN_CLICKED(IDC_RDO_INIT_STOP, &CInitialDlg::OnBnClickedRdoInitStop)
	ON_BN_CLICKED(IDC_MES_TEST1, &CInitialDlg::OnBnClickedMesTest1)
	ON_BN_CLICKED(IDC_MES_TEST2, &CInitialDlg::OnBnClickedMesTest2)
	ON_BN_CLICKED(IDC_MES_TEST3, &CInitialDlg::OnBnClickedMesTest3)
	ON_BN_CLICKED(IDC_MES_TEST4, &CInitialDlg::OnBnClickedMesTest4)
END_MESSAGE_MAP()

// CInitialDlg 메시지 처리기입니다.

BOOL CInitialDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	CString strSection, strKeyName, strNo, strNm, strText;

	CIniFileCS INI("System/AxisList.ini");
	strSection = "AXIS";
	for (int i = 0; i < AXIS_COUNT; i++) {
		strKeyName.Format("%02d", i);
		strNm = INI.Get_String(strSection, strKeyName, "");
		strText.Format(" [%02d] %s", i+8, strNm);
		m_stcAxisName[i].SetWindowText(strText);
	}
	for (int i = AXIS_COUNT; i < 27; i++) {
		m_stcAxisName[i].SetWindowText("");
	}

	for (int i = 0; i < 7; i++) m_stcInitCase[i].SetWindowText("000");

	m_bInitialRunning = FALSE;
	m_rdoInitStop.SetCheck(TRUE);
	m_rdoInitStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CInitialDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CInitialDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CInitialDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		CDataManager *pDataManager = CDataManager::Get_Instance();
		MODEL_DATA *pModelData = pDataManager->Get_pModelData();
		CString sTemp;
		sTemp.Format("%d (%0.1lf)   X   %d (%0.1lf)", pModelData->nArrayL, pModelData->dPitchL, pModelData->nArrayW, pModelData->dPitchW);
		m_stcInitStripSize.SetWindowText(sTemp);

		SetTimer(0, 100, NULL);

	} else {
		KillTimer(0);
	}
}

void CInitialDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(0);

	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	CCommon *pCommon = CCommon::Get_Instance();

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();

	CSequenceInit *pSequenceInit = CSequenceInit::Get_Instance();
	CLogFile *pLogFile = CLogFile::Get_Instance();
	
	if (pDX0->iStartSw && !m_rdoInitStart.GetCheck()) {
		pLogFile->Save_HandlerLog("[Initial Mode] START S/W Push");
		m_rdoInitStart.SetCheck(TRUE);
		Display_Status();
		SetTimer(0, 100, NULL);
		return;
	} else if (pDX0->iStopSw && !m_rdoInitStop.GetCheck()) {
		pLogFile->Save_HandlerLog("[Initial Mode] STOP S/W Push");
		m_rdoInitStop.SetCheck(TRUE);
	}

	Display_Status();

	if (m_rdoInitStart.GetCheck()) {
		if (!m_bInitialRunning) {	// First Start
			if (pCommon->Show_MsgBox(2, "초기화를 진행 하시겠습니까?") == IDOK) {
			//if (pCommon->Show_MsgBox(2, "Do you want to initialize?") == IDOK) {
				m_bInitialRunning = TRUE;

				pMainDlg->Enable_ModeButton(FALSE);
				pMainDlg->m_btnMainOperator.EnableWindow(FALSE);

				CInspector *pInspector = CInspector::Get_Instance();
				
				//비전에 초기화 커맨드 날려줌...?? 필요한지..
				pInspector->Set_StatusUpdate(INSPECTOR_VISION, 0);

				m_rdoInitStart.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
				m_rdoInitStart.Invalidate(FALSE);
				m_rdoInitStop.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
				m_rdoInitStop.Invalidate(FALSE);

				m_nBackColorLoop = 0;
				Set_StatusColor(0, 2);	// Green
				for (int i = 1; i < 9; i++) Set_StatusColor(i, 0);	// White

				pSequenceInit->Begin_InitialThread();

			} else {
				m_rdoInitStop.SetCheck(TRUE);
			}

		} else {					// Running
			Display_Initial();

			if (pSequenceInit->Get_InitComplete()) {
				m_bInitialRunning = FALSE;

				m_rdoInitStop.SetCheck(TRUE);
				m_rdoInitStart.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
				m_rdoInitStart.Invalidate(FALSE);
				m_rdoInitStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
				m_rdoInitStop.Invalidate(FALSE);

				for (int i = 1; i < 9; i++) Set_StatusColor(i, 2);	// Green

				pLogFile->Save_HandlerLog("[Initial Mode] Initialization is complete");

				pCommon->Show_MsgBox(1, "초기화가 완료 되었습니다.");
				//pCommon->Show_MsgBox(1, "Initialization is complete.");

				CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
				pWorkDlg->Clear_ConveyorList();
				//pWorkDlg->Clear_BufferList();
				pWorkDlg->Set_CleanOutMode();

				CManualDlg *pManualDlg = CManualDlg::Get_Instance();
				//pManualDlg->m_pManualInspectorDlg->Set_MoldRunCase(0);
				//pManualDlg->m_pManualInspectorDlg->Set_PcbRunCase(0);
				//pManualDlg->m_pManualInspectorDlg->Set_3dRunCase(0);

				CInspector *pInspector = CInspector::Get_Instance();
				
				pInspector->Set_StatusUpdate(INSPECTOR_VISION, 1);

				pMainDlg->Enable_ModeButton(TRUE);
				pMainDlg->m_btnMainOperator.EnableWindow(TRUE);
				pMainDlg->Set_CurrentMode(MODE_WORK);

				COperatorDlg *pOperatorDlg = COperatorDlg::Get_Instance();
				pOperatorDlg->ShowWindow(SW_SHOW);
				return;

			} else if (!pSequenceInit->Get_ThreadInitial()) {
				pLogFile->Save_HandlerLog("[Initial Mode] Auto STOP");
				m_rdoInitStop.SetCheck(TRUE);
			}
		}

	} else if (m_rdoInitStop.GetCheck()) {
		if (m_bInitialRunning) {	// First Stop
			m_bInitialRunning = FALSE;

			m_rdoInitStart.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
			m_rdoInitStart.Invalidate(FALSE);
			m_rdoInitStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
			m_rdoInitStop.Invalidate(FALSE);
			pSequenceInit->End_InitialThread();

			pMainDlg->Enable_ModeButton(TRUE);
			pMainDlg->m_btnMainOperator.EnableWindow(TRUE);

		} else {
			if (!gData.m_bErrorShow) {
				pCommon->Check_MainEmgAir();	// Emg & Main Air
			}
		}
	}

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CInitialDlg::OnBnClickedRdoInitStart()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Initial Mode] START Button push");
}

void CInitialDlg::OnBnClickedRdoInitStop()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Initial Mode] STOP Button push");
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CInitialDlg::Initial_Controls() 
{
	for (int i = 0; i < 5; i++) m_Group[i].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);

	for (int i = 0; i < 12; i++) m_Label[i].Init_Ctrl("Segoe UI", 11, TRUE, RGB(0xFF, 0xFF, 0xFF),RGB(0xA0, 0xA0, 0xA0));
	m_Label[3].Set_Font("Segoe UI", 12, TRUE);

	for (int i = 0; i < 27; i++) m_stcAxisName[i].Init_Ctrl("Segoe UI", 9, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x00));
	for (int i = 0; i < 27; i++) m_ledAxisRun[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 27; i++) m_ledAxisHom[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));

	m_ledInitOK.SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));

	for (int i = 0; i < 7; i++) m_stcInitCase[i].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xFF, 0xE0));
	m_stcInitCase[0].Set_Color(RGB(0xFF, 0x00, 0x00), RGB(0xFF, 0xFF, 0xE0));

	for (int i = 0; i < 3; i++) m_bmpImage[i].LoadBitmap(IDB_ARW4_DN);
	for (int i = 0; i < 3; i++) m_Image[i].SetBitmap(m_bmpImage[i]);
	for (int i = 0; i < 3; i++) m_Image[i].SetWindowPos(NULL, 0, 0, 36, 36, SWP_NOZORDER | SWP_NOMOVE);

	for (int i = 0; i < 9; i++) m_picInitFlow[i].Init_Ctrl(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xFF));
	for (int i = 0; i < 9; i++) m_stcInitFlow[i].Init_Ctrl("Segoe UI", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));

	m_rdoInitStart.Init_Ctrl("Segoe UI", 15, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoInitStop.Init_Ctrl("Segoe UI", 15, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_stcInitStripSize.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x80, 0x00), RGB(0xFF, 0xFF, 0xE0));

	for (int i = 0; i < 4; i++) m_ledMainAir[i].Init_Ctrl("Segoe UI", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 8; i++) m_ledMainDoor[i].Init_Ctrl("Segoe UI", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	m_ledBuffDoor.Init_Ctrl("Segoe UI", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 4; i++) m_ledLowerDoor[i].Init_Ctrl("Segoe UI", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

}

void CInitialDlg::Display_Status()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
	DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();

	for (int i = 0; i < AXIS_COUNT; i++) {
		AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(i);

		if (pStatus->bRun) m_ledAxisRun[i].On();
		else m_ledAxisRun[i].Off();

		if((i>=0 && i<=3) || (i>=19 && i<=22)) {
			if (pStatus->bSOn) m_ledAxisHom[i].On();
			else m_ledAxisHom[i].Off();
		} else {
			if (pStatus->bHom) m_ledAxisHom[i].On();
			else m_ledAxisHom[i].Off();
		}
	}

	// Main Air
	if (!pDX0->iMainAir1) m_ledMainAir[0].Set_On(FALSE);
	else m_ledMainAir[0].Set_On(TRUE);

	if (!pDX0->iMainAir2) m_ledMainAir[1].Set_On(FALSE);
	else m_ledMainAir[1].Set_On(TRUE);

	// Main Door
	if (0 == pDX0->iMainDoor1Close) m_ledMainDoor[0].Set_On(FALSE);
	else m_ledMainDoor[0].Set_On(TRUE);

	if (0 == pDX0->iMainDoor2Close) m_ledMainDoor[1].Set_On(FALSE);
	else m_ledMainDoor[1].Set_On(TRUE);

	if (0 == pDX0->iMainDoor3Close) m_ledMainDoor[2].Set_On(FALSE);
	else m_ledMainDoor[2].Set_On(TRUE);

	if (0 == pDX0->iMainDoor4Close) m_ledMainDoor[3].Set_On(FALSE);
	else m_ledMainDoor[3].Set_On(TRUE);

	if (0 == pDX0->iMainDoor5Close) m_ledMainDoor[4].Set_On(FALSE);
	else m_ledMainDoor[4].Set_On(TRUE);

	if (0 == pDX0->iMainDoor6Close) m_ledMainDoor[5].Set_On(FALSE);
	else m_ledMainDoor[5].Set_On(TRUE);

	if (0 == pDX0->iMainDoor7Close) m_ledMainDoor[6].Set_On(FALSE);
	else m_ledMainDoor[6].Set_On(TRUE);

	if (0 == pDX0->iMainDoor8Close) m_ledMainDoor[7].Set_On(FALSE);
	else m_ledMainDoor[7].Set_On(TRUE);

	CSequenceInit *pSequenceInit = CSequenceInit::Get_Instance();
	if (pSequenceInit->Get_InitComplete()) m_ledInitOK.On();
	else m_ledInitOK.Off();

}

void CInitialDlg::Display_Initial() 
{
	int nMain, nCase[13];
	CString strCase;

	CSequenceInit *pSequenceInit = CSequenceInit::Get_Instance();
	pSequenceInit->Get_InitCase(nMain, nCase[0], nCase[1], nCase[2], nCase[3], nCase[4], nCase[5], nCase[6], nCase[7], nCase[8], nCase[9], nCase[10]);
	
	strCase.Format("%03d", nMain);
	m_stcInitCase[0].SetWindowText(strCase);
/*
	strCase.Format("%03d", nLoad);
	m_stcInitCase[1].SetWindowText(strCase);

	strCase.Format("%03d", nUnload);
	m_stcInitCase[2].SetWindowText(strCase);

	strCase.Format("%03d", nElev);
	m_stcInitCase[3].SetWindowText(strCase);

	strCase.Format("%03d", nGrip);
	m_stcInitCase[4].SetWindowText(strCase);

	strCase.Format("%03d", nPick);
	m_stcInitCase[5].SetWindowText(strCase);

	strCase.Format("%03d", nInsp);
	m_stcInitCase[6].SetWindowText(strCase);
*/
	if (m_nBackColorLoop == 10) m_nBackColorLoop = 0;

	if (nMain == 100) return;
	
	if (nMain < 160) {
		if (m_nBackColorLoop == 1) Set_StatusColor(1, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(1, 3);	// Blue
	} else if (nMain == 160) {
		if (m_nBackColorLoop == 0) Set_StatusColor(1, 2);	// Green
	}

	if (nCase[0] < 200 || nCase[1] < 200 || nCase[2] < 200 || nCase[3] < 200) {
		if (m_nBackColorLoop == 1) Set_StatusColor(2, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(2, 3);	// Blue
	} else if (nCase[0] == 200 && nCase[1] == 200 && nCase[2] == 200 && nCase[3] == 200) {
		if (m_nBackColorLoop == 0) Set_StatusColor(2, 2);	// Green
	}

	if (nCase[10] < 200) {
		if (m_nBackColorLoop == 1) Set_StatusColor(3, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(3, 3);	// Blue
	} else if (nCase[10] == 200) {
		if (m_nBackColorLoop == 0) Set_StatusColor(3, 2);	// Green
	}

	if (nCase[5] < 200) {
		if (m_nBackColorLoop == 1) Set_StatusColor(4, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(4, 3);	// Blue
	} else if (nCase[5] == 200) {
		if (m_nBackColorLoop == 0) Set_StatusColor(4, 2);	// Green
	}

	if (nCase[4] < 200) {
		if (m_nBackColorLoop == 1) Set_StatusColor(5, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(5, 3);	// Blue
	} else if (nCase[4] == 200) {
		if (m_nBackColorLoop == 0) Set_StatusColor(5, 2);	// Green
	}

	if (nCase[6] < 200 || nCase[9] < 200) {
		if (m_nBackColorLoop == 1) Set_StatusColor(6, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(6, 3);	// Blue
	} else if (nCase[6] == 200 && nCase[9] == 200) {
		if (m_nBackColorLoop == 0) Set_StatusColor(6, 2);	// Green
	}

	if (nCase[7] < 200 || nCase[8] < 200) {
		if (m_nBackColorLoop == 1) Set_StatusColor(7, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(7, 3);	// Blue
	} else if (nCase[7] == 200 && nCase[8] == 200) {
		if (m_nBackColorLoop == 0) Set_StatusColor(7, 2);	// Green
	}

	m_nBackColorLoop++;
}

void CInitialDlg::Set_StatusColor(int nIdx, int nColor)
{
	if (nColor == 0) m_picInitFlow[nIdx].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xFF));	// White
	if (nColor == 1) m_picInitFlow[nIdx].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));	// Red
	if (nColor == 2) m_picInitFlow[nIdx].Set_Color(COLOR_DEFAULT, RGB(0x00, 0xFF, 0x00));	// Green
	if (nColor == 3) m_picInitFlow[nIdx].Set_Color(COLOR_DEFAULT, RGB(0x00, 0x00, 0xFF));	// Blue

	m_picInitFlow[nIdx].Invalidate(FALSE);
	m_stcInitFlow[nIdx].Invalidate(FALSE);
}
///////////////////////////////////////////////////////////////////////////////


void CInitialDlg::OnBnClickedMesTest1()
{
	g_objMES.Set_LotStart("GFY624CH6L05", 555, "11111");
	return;
}


void CInitialDlg::OnBnClickedMesTest2()
{
	CString sLotid, sBid, sJ;

	sLotid = "GFY624CH6L05";

	for(int i=0; i<555; i++) {
		sBid.Format("BarcodeID%005d", (i+1));
		if (sJ == "OK") sJ = "NG";
		else			sJ = "OK";

		g_objMES.Set_Result(sLotid, sBid, sJ, "GG", "GGGGGGGGGG", 1,2,3,4,5,6);
		Sleep(10);
	}
	return;
}


void CInitialDlg::OnBnClickedMesTest3()
{
	g_objMES.Set_LotEnd("GFY624CH6L05", 555, "11111", 444, 111);
	g_objMES.Set_TackTime(0.699, "GFY624CH6L05", 555, "2017/12/04 14:00:10", "2017/12/04 14:10:22");

	return;
}


void CInitialDlg::OnBnClickedMesTest4()
{
//	g_objMES.Set_Alarm(1, 1101, "가아자");

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

	return;
}

void CInitialDlg::LogAllDelete()
{
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\Alarm");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\Alarm\\Log");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\Handler");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\Handler\\History");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\MESAgent");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\Inspector");
	LogFileDelete("D:\\CMI4200L\\Run\\LOG\\JobList");
}

void CInitialDlg::LogFileDelete(CString sPath)
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
