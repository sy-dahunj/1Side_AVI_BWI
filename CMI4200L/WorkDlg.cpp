// WorkDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "WorkDlg.h"
#include "afxdialogex.h"

#include "CMI4200LDlg.h"

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "LogFile.h"
#include "ExtBarcode_Honeywell.h"
#include "Barcode_DS1100.h"
#include "MESInterface.h"
#include "Inspector.h"
#include "CapAttachUDP.h"

// CWorkDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWorkDlg, CDialogEx)

CWorkDlg *CWorkDlg::m_pInstance = NULL;

CWorkDlg *CWorkDlg::Get_Instance(CWnd *pParent)
{
	if (!m_pInstance) {
		m_pInstance = new CWorkDlg(pParent);
		if (!m_pInstance->m_hWnd) {
			m_pInstance->Create(IDD_WORK_DLG, pParent);
		}
	}
	return m_pInstance;
}

void CWorkDlg::Delete_Instance()
{
	if (m_pInstance->m_hWnd) m_pInstance->DestroyWindow();
	if (m_pInstance) delete m_pInstance;
	m_pInstance = NULL;
}

CWorkDlg::CWorkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkDlg::IDD, pParent)
{
	pLogFile = CLogFile::Get_Instance();
	gData.nLotInfoBlockDelay = 0;
}

CWorkDlg::~CWorkDlg()
{
}

void CWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i <= 2; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 4; i <= 6; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i <= 2; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 6; i <= 9; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 19; i < 39; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	DDX_Control(pDX, IDC_LABEL_3, m_Label[3]);
	DDX_Control(pDX, IDC_LABEL_4, m_Label[4]);
	DDX_Control(pDX, IDC_LABEL_DOOR, m_LabelDoor);

	DDX_Control(pDX, IDC_STC_MODEL_NAME, m_stcModelName);
	DDX_Control(pDX, IDC_STC_STRIP_SIZE, m_stcStripSize);
	DDX_Control(pDX, IDC_STC_STRIP_TYPE, m_stcStripType);
	DDX_Control(pDX, IDC_CHK_ALL_PASS, m_chkAllPass);

	DDX_Control(pDX, IDC_STC_LOT_ID_1, m_stcLotId1);
	DDX_Control(pDX, IDC_STC_LOT_ID_2, m_stcLotId2);
	DDX_Control(pDX, IDC_STC_PART_NO_2, m_stcPartNo2);
	
	DDX_Control(pDX, IDC_IMAGE_0, m_Image);
	//DDX_Control(pDX, IDC_STC_ELEC_VALUE, m_stcElecValue);
	//DDX_Control(pDX, IDC_STC_WARP_VALUE, m_stcWarpValue);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_STC_WORK_SLOT_0 + i, m_stcWorkSlot[i]);
	DDX_Control(pDX, IDC_STC_WORK_SLOT_10, m_stcWorkSlot[10]);
	DDX_Control(pDX, IDC_STC_WORK_SLOT_11, m_stcWorkSlot[11]);
	DDX_Control(pDX, IDC_STC_WORK_SLOT_12, m_stcWorkSlot[12]);
	DDX_Control(pDX, IDC_STC_WORK_SLOT_13, m_stcWorkSlot[13]);
	DDX_Control(pDX, IDC_STC_WORK_SLOT_14, m_stcWorkSlot[14]);
	DDX_Control(pDX, IDC_STC_WORK_SLOT_15, m_stcWorkSlot[15]);
	DDX_Control(pDX, IDC_STC_WORK_SLOT_16, m_stcWorkSlot[16]);
	DDX_Control(pDX, IDC_STC_WORK_SLOT_17, m_stcWorkSlot[17]);

	DDX_Control(pDX, IDC_STC_WORK_PICKER1, m_stcWorkPicker[0]);
	DDX_Control(pDX, IDC_STC_WORK_PICKER2, m_stcWorkPicker[1]);
	DDX_Control(pDX, IDC_BTN_CONV_CLEAR, m_btnConvClear);
	DDX_Control(pDX, IDC_STC_CONVEYOR, m_stcConveyor);

	DDX_Control(pDX, IDC_STC_LOAD_COUNT, m_stcLoadCount);
	DDX_Control(pDX, IDC_STC_UNLOAD_COUNT, m_stcUnloadCount);

	DDX_Control(pDX, IDC_LED_AUTO_START_ENABLE, m_ledAutoStartEnable);
	DDX_Control(pDX, IDC_RDO_WORK_START, m_rdoWorkStart);
	DDX_Control(pDX, IDC_RDO_WORK_STOP, m_rdoWorkStop);
	DDX_Control(pDX, IDC_CHK_STRIP_STOP, m_chkStripStop);
	DDX_Control(pDX, IDC_CHK_LOT_STOP, m_chkLotStop);
	DDX_Control(pDX, IDC_CHK_SAMPLE_JOB, m_chkSampleJob);

	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_STC_WORK_CASE_0 + i, m_stcWorkCase[i]);
	DDX_Control(pDX, IDC_STC_WORK_CASE_9,  m_stcWorkCase[9]);
	DDX_Control(pDX, IDC_STC_WORK_CASE_10, m_stcWorkCase[10]);
	DDX_Control(pDX, IDC_STC_WORK_CASE_11, m_stcWorkCase[11]);

	DDX_Control(pDX, IDC_STC_CM_CNT, m_stcCMCnt);
	DDX_Control(pDX, IDC_STC_CM_LABEL, m_LabelstcCMCnt);

	DDX_Control(pDX, IDC_STC_TRAY_POS_0, m_stcTrayPos[0]);
	DDX_Control(pDX, IDC_STC_TRAY_POS_1, m_stcTrayPos[1]);
	DDX_Control(pDX, IDC_STC_TRAY_POS_2, m_stcTrayPos[2]);
	DDX_Control(pDX, IDC_STC_TRAY_POS_3, m_stcTrayPos[3]);

	DDX_Control(pDX, IDC_LED_INDEX_JOB_0, m_ledIndexJob[0]);
	DDX_Control(pDX, IDC_LED_INDEX_JOB_1, m_ledIndexJob[1]);
	DDX_Control(pDX, IDC_LED_INDEX_JOB_2, m_ledIndexJob[2]);
	DDX_Control(pDX, IDC_LED_INDEX_JOB_3, m_ledIndexJob[3]);
	DDX_Control(pDX, IDC_LED_INDEX_JOB_4, m_ledIndexJob[4]);
	DDX_Control(pDX, IDC_LED_INDEX_JOB_5, m_ledIndexJob[5]);

	DDX_Control(pDX, IDC_LED_INDEX_POS_1_0, m_ledIndexSlot[0][0]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_1_1, m_ledIndexSlot[0][1]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_1_2, m_ledIndexSlot[0][2]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_1_3, m_ledIndexSlot[0][3]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_1_4, m_ledIndexSlot[0][4]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_1_5, m_ledIndexSlot[0][5]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_2_0, m_ledIndexSlot[1][0]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_2_1, m_ledIndexSlot[1][1]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_2_2, m_ledIndexSlot[1][2]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_2_3, m_ledIndexSlot[1][3]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_2_4, m_ledIndexSlot[1][4]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_2_5, m_ledIndexSlot[1][5]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_3_0, m_ledIndexSlot[2][0]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_3_1, m_ledIndexSlot[2][1]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_3_2, m_ledIndexSlot[2][2]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_3_3, m_ledIndexSlot[2][3]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_3_4, m_ledIndexSlot[2][4]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_3_5, m_ledIndexSlot[2][5]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_4_0, m_ledIndexSlot[3][0]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_4_1, m_ledIndexSlot[3][1]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_4_2, m_ledIndexSlot[3][2]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_4_3, m_ledIndexSlot[3][3]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_4_4, m_ledIndexSlot[3][4]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_4_5, m_ledIndexSlot[3][5]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_5_0, m_ledIndexSlot[4][0]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_5_1, m_ledIndexSlot[4][1]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_5_2, m_ledIndexSlot[4][2]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_5_3, m_ledIndexSlot[4][3]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_5_4, m_ledIndexSlot[4][4]);
	DDX_Control(pDX, IDC_LED_INDEX_POS_5_5, m_ledIndexSlot[4][5]);

	DDX_Control(pDX, IDC_LED_PICKER_0_0, m_ledPicker[0][0]);
	DDX_Control(pDX, IDC_LED_PICKER_0_1, m_ledPicker[0][1]);
	DDX_Control(pDX, IDC_LED_PICKER_0_2, m_ledPicker[0][2]);
	DDX_Control(pDX, IDC_LED_PICKER_0_3, m_ledPicker[0][3]);
	DDX_Control(pDX, IDC_LED_PICKER_0_4, m_ledPicker[0][4]);
	DDX_Control(pDX, IDC_LED_PICKER_0_5, m_ledPicker[0][5]);
	DDX_Control(pDX, IDC_LED_PICKER_1_0, m_ledPicker[1][0]);
	DDX_Control(pDX, IDC_LED_PICKER_1_1, m_ledPicker[1][1]);
	DDX_Control(pDX, IDC_LED_PICKER_1_2, m_ledPicker[1][2]);
	DDX_Control(pDX, IDC_LED_PICKER_1_3, m_ledPicker[1][3]);
	DDX_Control(pDX, IDC_LED_PICKER_1_4, m_ledPicker[1][4]);
	DDX_Control(pDX, IDC_LED_PICKER_1_5, m_ledPicker[1][5]);
	DDX_Control(pDX, IDC_LED_PICKER_2_0, m_ledPicker[2][0]);
	DDX_Control(pDX, IDC_LED_PICKER_2_1, m_ledPicker[2][1]);
	DDX_Control(pDX, IDC_LED_PICKER_2_2, m_ledPicker[2][2]);
	DDX_Control(pDX, IDC_LED_PICKER_2_3, m_ledPicker[2][3]);
	DDX_Control(pDX, IDC_LED_PICKER_2_4, m_ledPicker[2][4]);
	DDX_Control(pDX, IDC_LED_PICKER_2_5, m_ledPicker[2][5]);
	DDX_Control(pDX, IDC_LED_PICKER_3_0, m_ledPicker[3][0]);
	DDX_Control(pDX, IDC_LED_PICKER_3_1, m_ledPicker[3][1]);
	DDX_Control(pDX, IDC_LED_PICKER_3_2, m_ledPicker[3][2]);
	DDX_Control(pDX, IDC_LED_PICKER_3_3, m_ledPicker[3][3]);
	DDX_Control(pDX, IDC_LED_PICKER_3_4, m_ledPicker[3][4]);
	DDX_Control(pDX, IDC_LED_PICKER_3_5, m_ledPicker[3][5]);

	DDX_Control(pDX, IDC_LED_BAR_ALARM, m_ledBarAlarm);
	DDX_Control(pDX, IDC_LED_BAR_ALARM2, m_ledBarNG);
	DDX_Control(pDX, IDC_GRD_SHIFT_LIST, m_grdShiftList);
	DDX_Control(pDX, IDC_BTN_BUZZER_OFF, m_btnBuzzerOff);
	DDX_Control(pDX, IDC_BTN_LOT_CANCEL, m_btnLotCancel);
	DDX_Control(pDX, IDC_CHK_MES_USE, m_chkMESUse);

	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_LOADPICK_NO_0 + i, m_stcLoadPickNo[i]);
	
}

BEGIN_MESSAGE_MAP(CWorkDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RDO_WORK_START, &CWorkDlg::OnBnClickedRdoWorkStart)
	ON_BN_CLICKED(IDC_RDO_WORK_STOP, &CWorkDlg::OnBnClickedRdoWorkStop)
	ON_BN_CLICKED(IDC_CHK_STRIP_STOP, &CWorkDlg::OnBnClickedChkStripStop)
	ON_BN_CLICKED(IDC_CHK_LOT_STOP, &CWorkDlg::OnBnClickedChkLotStop)
	ON_BN_CLICKED(IDC_CHK_SAMPLE_JOB, &CWorkDlg::OnBnClickedChkSampleJob)
	ON_BN_CLICKED(IDC_BTN_CONV_CLEAR, &CWorkDlg::OnBnClickedBtnConvClear)
	ON_BN_CLICKED(IDC_CHK_MES_USE, &CWorkDlg::OnBnClickedChkMESUse)

	//kty
	ON_BN_CLICKED(IDC_STC_LOT_ID_1, &CWorkDlg::OnBnClickedLotID)
	ON_BN_CLICKED(IDC_STC_LOT_ID_2, &CWorkDlg::OnBnClickedTrayCnt)
	ON_BN_CLICKED(IDC_STC_CM_CNT, &CWorkDlg::OnBnClickedCMCnt)
	ON_BN_CLICKED(IDC_BTN_BUZZER_OFF, &CWorkDlg::OnBnClickedBtnBuzzerOff)
	ON_BN_CLICKED(IDC_BTN_LOT_CANCEL, &CWorkDlg::OnBnClickedBtnLotCancel)

	ON_MESSAGE(UM_UPDATE_MODEL, OnUpdateModel)
	ON_MESSAGE(UM_UPDATE_RFID, OnUpdateRfid)
	ON_MESSAGE(UM_UPDATE_JOB_LIST, OnUpdateJobList)
	ON_MESSAGE(UM_UPDATE_SHIFT_LIST, OnUpdateShiftList)
	ON_MESSAGE(UM_UPDATE_LOTID, OnUpdateLotID)
	ON_MESSAGE(UM_LOT_START_END, &CWorkDlg::OnLotStartEnd)

	ON_BN_CLICKED(IDC_CHK_ALL_PASS, &CWorkDlg::OnBnClickedChkAllPass)

	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADPICK_NO_0,IDC_STC_LOADPICK_NO_3, OnStcLoadPickInfoClick)
	ON_BN_CLICKED(IDC_BTN_SEND1, &CWorkDlg::OnBnClickedBtnSend1)
END_MESSAGE_MAP()

// CWorkDlg 메시지 처리기입니다.

BOOL CWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_bAutoRunning = FALSE;
	m_bInitialOk = FALSE;

	m_rdoWorkStop.SetCheck(TRUE);
	m_rdoWorkStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

	//kty
	//m_chkStripStop.EnableWindow(FALSE);

	m_chkSampleJob.SetCheck(FALSE);
	m_chkSampleJob.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
//	m_chkSampleJob.SetWindowText("Clean Out");
	gData.bCleanOutMode = FALSE;
	m_stcConveyor.SetWindowText("0");

	//m_stcWarpValue.SetWindowText("");
	//m_stcElecValue.SetWindowText("");
	gData.nTrayJobCount = gData.nCMJobCount = 0;
	m_sCurLotID = "";
	gData.nLotIdsIndex = 0;

	if (!AfxSocketInit()) {
		AfxMessageBox(("Winsock 초기화 실패"));
		return FALSE;
	}

#ifdef AJIN_BOARD_USE
	CString ip = "192.168.1.12";
	UINT port = 21000;
#else
	CString ip = "127.0.0.1";
	UINT port = 21000;
#endif

	if (!m_sender.Create()) { AfxMessageBox("소켓 생성 실패"); return FALSE; }

	if (m_sender.Connect(ip, port) == FALSE) 
	{
		if (GetLastError() != WSAEWOULDBLOCK) 
		{
			AfxMessageBox("Connect 실패");
			return FALSE;
		}
	}

#ifdef PICKER_4
	m_ledIndexSlot[0][4].ShowWindow(FALSE);
	m_ledIndexSlot[1][4].ShowWindow(FALSE);
	m_ledIndexSlot[2][4].ShowWindow(FALSE);
	m_ledIndexSlot[3][4].ShowWindow(FALSE);
	m_ledIndexSlot[4][4].ShowWindow(FALSE);

	m_ledPicker[0][4].ShowWindow(FALSE);
	m_ledPicker[1][4].ShowWindow(FALSE);
	m_ledPicker[2][4].ShowWindow(FALSE);
	m_ledPicker[3][4].ShowWindow(FALSE);

	m_ledIndexSlot[0][5].ShowWindow(FALSE);
	m_ledIndexSlot[1][5].ShowWindow(FALSE);
	m_ledIndexSlot[2][5].ShowWindow(FALSE);
	m_ledIndexSlot[3][5].ShowWindow(FALSE);
	m_ledIndexSlot[4][5].ShowWindow(FALSE);

	m_ledPicker[0][5].ShowWindow(FALSE);
	m_ledPicker[1][5].ShowWindow(FALSE);
	m_ledPicker[2][5].ShowWindow(FALSE);
	m_ledPicker[3][5].ShowWindow(FALSE);

#endif

#ifdef PICKER_5
	m_ledIndexSlot[0][5].ShowWindow(FALSE);
	m_ledIndexSlot[1][5].ShowWindow(FALSE);
	m_ledIndexSlot[2][5].ShowWindow(FALSE);
	m_ledIndexSlot[3][5].ShowWindow(FALSE);
	m_ledIndexSlot[4][5].ShowWindow(FALSE);

	m_ledPicker[0][5].ShowWindow(FALSE);
	m_ledPicker[1][5].ShowWindow(FALSE);
	m_ledPicker[2][5].ShowWindow(FALSE);
	m_ledPicker[3][5].ShowWindow(FALSE);

#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CWorkDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CWorkDlg::PreTranslateMessage(MSG* pMsg)
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CWorkDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		CDataManager *pDataManager = CDataManager::Get_Instance();
		MODEL_DATA *pModelData = pDataManager->Get_pModelData();

		CString strText;

		m_stcModelName.SetWindowText(pModelData->sModelName);
//		if (pModelData->sModelName != "K62" && pModelData->sModelName != "K63") {
//			AfxMessageBox(_T("Model을 정상적으로 Loading 하지 못하였습니다..   Handler Program을 다시 실행해 주세요......."));
//			return;
//		}

		strText.Format("%d X %d", pModelData->nArrayL, pModelData->nArrayW);
		m_stcStripSize.SetWindowText(strText);

		strText.Format("%0.1lf X %0.1lf", pModelData->dPitchL, pModelData->dPitchW);
		m_stcStripType.SetWindowText(strText);

		CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();

		if (gData.sLotID.GetLength() < 1) gData.sLotID = "GSY123456789";
		m_stcLotId1.SetWindowText(gData.sLotID);

		strText.Format("%d", gData.nTrayJobCount);
		m_stcLotId2.SetWindowText(strText);
		strText.Format("%d", gData.nCMJobCount);
		m_stcCMCnt.SetWindowText(strText);

		EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
		m_chkMESUse.SetCheck(pEquipData->bUseMES);		

		gData.sRecipeName = pModelData->sModelName;	         
		gData.nArrayW	  = pModelData->nArrayW;		
		gData.nArrayL	  = pModelData->nArrayL;		
		gData.dTrayPitchW = pModelData->dPitchW;		
		gData.dTrayPitchL = pModelData->dPitchL;		
		gData.dUnPitchW   = pModelData->dUnPitchW;		
		gData.dUnPitchL   = pModelData->dUnPitchL;		
		//gData.dTrayFirstW = pModelData->dTrayFirstW; 
		//gData.dTrayFirstL = pModelData->dTrayFirstL; 
		gData.dTrayFirstW = 0; 
		gData.dTrayFirstL = 0; 
		gData.dCMSizeW    = pModelData->dCMWSize;
		gData.nCMMaxCount = pModelData->nCMCount;
		m_nDisCnt = 0;

		Display_LotInfo();

		SetTimer(0, 100, NULL);
	} else {
		KillTimer(0);
	}
}

void CWorkDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(0);

	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	CCommon *pCommon = CCommon::Get_Instance();

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();

	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
	

	if (pDX0->iStartSw && !m_rdoWorkStart.GetCheck()) {
		if (Check_Start()==FALSE) {
			SetTimer(0, 100, NULL);
			return;
		}
		CString sLog;
		sLog.Format("[Work Mode] START S/W push....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
		pLogFile->Save_HandlerLog(sLog);
		m_rdoWorkStart.SetCheck(TRUE);
		
		Display_Status();
		SetTimer(0, 100, NULL);
		return;
	} else if (pDX0->iStopSw && !m_rdoWorkStop.GetCheck()) {
		
		pLogFile->Save_HandlerLog("[Work Mode] STOP S/W push");
		m_rdoWorkStop.SetCheck(TRUE);
		
		pMainDlg->Set_MainState(STATE_INITEND);
	}

	if(gData.nLotInfoBlockDelay > 0)
	{
		gData.nLotInfoBlockDelay++;		
	}
	if(gData.nLotInfoBlockDelay > 30)
	{
		Enable_LotInfo(TRUE);
		gData.nLotInfoBlockDelay = 0;
	}

	Display_Status();

	if (m_rdoWorkStart.GetCheck()) {
		if (!gData.bCheckStartComplete) { SetTimer(0, 100, NULL); return; }
		if (!m_bAutoRunning) {	// First AutoRun
			if (m_bInitialOk) {
				m_bAutoRunning = TRUE;

				pMainDlg->Enable_ModeButton(FALSE);

				if (gAlm.nType==1) Set_AlaramLog();

				m_rdoWorkStart.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
				m_rdoWorkStart.Invalidate(FALSE);
				m_rdoWorkStop.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
				m_rdoWorkStop.Invalidate(FALSE);
				m_chkStripStop.EnableWindow(TRUE);
				
				g_objMES.m_bStart = TRUE;
				if (g_objMES.m_bMESUse==FALSE || g_objMES.m_nMESSequence==3 || gData.bCleanOutMode==TRUE) {
					CInspector *pInspector = CInspector::Get_Instance();
					pInspector->Set_StatusUpdate(INSPECTOR_VISION, 2);
					pSequenceMain->Begin_MainRunThread();
					g_objMES.Set_Status(1);
				} else {
					g_objMES.Set_LotStart(gData.sLotID, gData.nCMJobCount, gData.sOperID);
					CString sLog;
					
					sLog.Format("[Work Mode] MES Lot Started, LotID:%s, CM Count:%d, OperID: %s", gData.sLotID, gData.nCMJobCount, gData.sOperID);
					pLogFile->Save_HandlerLog(sLog);
				}

				pMainDlg->Set_MainState(STATE_RUN);
				if(m_sCurLotID != gData.sLotID) {	//새로운 Lot 시작때는 Lot Change로 표시
					m_sCurLotID = gData.sLotID;
					pMainDlg->Set_LotErrorLog("START", 903, "LOT Change");

				} else {
					pMainDlg->Set_LotErrorLog("START", 903, "Start");
				}

			} else {
				pCommon->Show_Error(40);		// 초기화 완료 에러
				m_rdoWorkStop.SetCheck(TRUE);
			}

		} else {				// Auto Running
			if (g_objMES.m_bMESUse==FALSE || g_objMES.m_nMESSequence==3 || gData.bCleanOutMode==TRUE) {
				if (!pSequenceMain->Get_ThreadMainRun()) {
					pLogFile->Save_HandlerLog("[Work Mode] Auto STOP");
					m_rdoWorkStop.SetCheck(TRUE);
				}
			}
		}

	} else if (m_rdoWorkStop.GetCheck()) {
		g_objMES.m_bStart = FALSE;
		if (m_bAutoRunning) {	// First AutoStop
			m_bAutoRunning = FALSE;

			pSequenceMain->End_MainRunThread();

			m_rdoWorkStart.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
			m_rdoWorkStart.Invalidate(FALSE);
			m_rdoWorkStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
			m_rdoWorkStop.Invalidate(FALSE);

			pMainDlg->Enable_ModeButton(TRUE);

			pMainDlg->Set_LotErrorLog("STOP", 904, "Stop");
			g_objMES.Set_Status(3);

		} else {				// Stop
			// Auto Start
			if (!gData.m_bErrorShow) {
				if (!pCommon->Check_MainEmgAir()) {	// Emg & Main Air
					SetTimer(0, 100, NULL);
					return;
				}
			}
		}
	}

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CWorkDlg::OnBnClickedRdoWorkStart()
{
	if (Check_Start()==FALSE) return;

	CString sLog;
	
	sLog.Format("[Work Mode] START button push....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
	pLogFile->Save_HandlerLog(sLog);	

	Enable_LotInfo(FALSE);
}

void CWorkDlg::OnBnClickedRdoWorkStop()
{
	
	pLogFile->Save_HandlerLog("[Work Mode] STOP button push");

	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
	pMainDlg->Set_MainState(STATE_INITEND);

	Enable_LotInfo(TRUE);
}

void CWorkDlg::OnBnClickedChkStripStop()
{
	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();

	if(gData.nNGTrayPos != 0){
		CCommon *pCommon = CCommon::Get_Instance();
		pCommon->Show_MsgBox(1, "Equipment Run Status Error,     NG Tray Position Error");
		return;
	}

	//Tray Data Clear..
	if (gData.bUseSeparationMode){
		if (pSequenceMain->Check_NGTrayFull(1)) {
			for(int i = 0; i<20; i++){
				for(int j=0; j<20; j++){
					gData.NG1TrayInfo[i][j] = 0;
				}
			}
		}
		if (pSequenceMain->Check_NGTrayFull(2)) {
			for(int i = 0; i<20; i++){
				for(int j=0; j<20; j++){
					gData.NG2TrayInfo[i][j] = 0;
				}
			}
		}
	} else {
		for(int i = 0; i<20; i++){
			for(int j=0; j<20; j++){
				gData.NG1TrayInfo[i][j] = 0;
				gData.NG2TrayInfo[i][j] = 0;
			}
		}
	}
	
	pSequenceMain->Set_RunCase(AUTO_NGTRAY, 100);

	Display_Tray();

}

void CWorkDlg::OnBnClickedChkSampleJob()
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (m_chkSampleJob.GetCheck()) {

		if (m_rdoWorkStart.GetCheck() && gData.nDoorInterlock18 != 1) {
			pCommon->Show_MsgBox(1, "Run중에는 Clean Out Mode를 설정 할수 없습니다........");
			m_chkSampleJob.SetCheck(FALSE);
			return;
		}

		if (pCommon->Show_MsgBox(2, "Are you sure you want to Clean Out?") == IDOK) {
			CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
			pSequenceMain->Set_RunCase(AUTO_INSPECT, 100);
			pSequenceMain->Set_RunCase(AUTO_BARCODE, 100);
			gData.bCleanOutMode = TRUE;

			CString sLog;
			sLog.Format("[Work Mode] Clean Out button push....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
			pLogFile->Save_HandlerLog(sLog);

		} else {
			m_chkSampleJob.SetCheck(FALSE);
		}	
	} else {
		gData.bCleanOutMode = FALSE;
	}
}

void CWorkDlg::OnBnClickedChkMESUse()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CDataManager *pDataManager = CDataManager::Get_Instance();

	if (m_rdoWorkStart.GetCheck() && gData.nDoorInterlock18 != 1) {
		pCommon->Show_MsgBox(1, "Can't change in Auto Run........");

		
		EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
		m_chkMESUse.SetCheck(pEquipData->bUseMES);
		return;
	}

	CIniFileCS INI("System/EquipData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("EquipData.ini File Not Found!!!");
		return;
	}
	INI.Set_Bool("OPTION", "MES_USE", m_chkMESUse.GetCheck());
	pDataManager->Read_EquipData();
	g_objMES.Set_MESUse(m_chkMESUse.GetCheck());

	CString sLog;
	sLog.Format("[Work Mode] MES Use Checked, MES USE =%d", m_chkMESUse.GetCheck());
	pLogFile->Save_HandlerLog(sLog);

}


BOOL CWorkDlg::Check_Start()
{
	gData.bCheckStartComplete = FALSE;
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
	DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();
	DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();
	DX_DATA_6 *pDX6 = pAJinAXL->Get_pDX6();
	CCommon *pCommon = CCommon::Get_Instance();

	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	CInspector *pInspector = CInspector::Get_Instance();
	pInspector->Set_FOBRequest(INSPECTOR_VISION);	// 시작전 FOB 모드 확인

	CSequenceInit *pSequenceInit = CSequenceInit::Get_Instance();
	if (pSequenceInit->Get_InitComplete()==FALSE) {
		m_rdoWorkStart.SetCheck(FALSE);
		pCommon->Show_MsgBox(1, "장비 초기화 처리를 먼저해 주세요......");
		return FALSE;
	}

	if(!pEquipData->bUseVisionInspect)
	{		
		if ( pCommon->Show_MsgBox(2, "Vision Option을 끄고 진행하시겠습니까?") != IDOK)
		{
			m_rdoWorkStart.SetCheck(FALSE);
			return FALSE;
		}		
	}

	if(!pDX3->iNGTray1Check || !pDX3->iNGTray2Check){
		m_rdoWorkStart.SetCheck(FALSE);
		pCommon->Show_MsgBox(1, "NG Stage에 Tray이 유무를 확인해 주세요.");
		return FALSE;
	}

	if(gData.nTrayJobCount > TRAY_MAX_CNT) {
		m_rdoWorkStart.SetCheck(FALSE);
		pCommon->Show_MsgBox(1, "Tray 수량 또는 CM 수량 확인해 주세요..........");
		return FALSE;
	}

	if(!pDX1->iLS_Load1FCheck && gData.nLoadTrayCount == 0) {
		m_rdoWorkStart.SetCheck(FALSE);
		pCommon->Show_MsgBox(1, "Load Tray를 확인해 주세요.");
		return FALSE;
	}
	if(!pDX6->iUS_Load1FCheck && gData.nLoadTrayCount == 0) {
		m_rdoWorkStart.SetCheck(FALSE);
		pCommon->Show_MsgBox(1, "Unload Tray(양품 Tray)를 확인해 주세요.");
		return FALSE;
	}	

	if(gData.sLotID.GetLength() < 5) {
		m_rdoWorkStart.SetCheck(FALSE);
		pCommon->Show_MsgBox(1, "Lot ID를 다시 입력해 주세요............(5자리 이상)");
		return FALSE;
	}

	//if(gData.nCMJobCount <= 0) {
	//	m_rdoWorkStart.SetCheck(FALSE);
	//	pCommon->Show_MsgBox(1, "CM Count 를 입력해 주세요.");
	//	return FALSE;
	//}
	
	if (gData.sOperID.GetLength() < 1) {
		m_rdoWorkStart.SetCheck(FALSE);
		pCommon->Show_MsgBox(1, "Operator화면에서 Operator ID를 입력해 주세요....");
		return FALSE;
	}

	int nCase = pSequenceMain->Get_RunCase(AUTO_NGTRAY);
	if (nCase == 320) {	//NG FULL Case
		m_rdoWorkStart.SetCheck(FALSE);
		pCommon->Show_MsgBox(1, "Tray Change 버튼을 누른후 시작해 주세요....");
		return FALSE;
	}

	if (gData.bUseAllPass && gData.bCapAttachWork == TRUE) {
		m_rdoWorkStart.SetCheck(FALSE);
		pCommon->Show_MsgBox(1, "Cap Attach 장비에서 Lot End 되지 않았습니다. Lot End 후 시작해 주세요....");
		return FALSE;
	}

	if (pEquipData->bUseDoorLock) {
		if (!pDX0->iMainDoor1Close) {
			m_rdoWorkStart.SetCheck(FALSE);
			pCommon->Show_MsgBox(1, "Main Door가 Open되어 있습니다... Door Close후 진행하세요.");
			return FALSE;
		}
	}
#ifdef AJIN_BOARD_USE
	// 비전만 사용할때 확인해주면 된다.
	if (!gData.bUseDryRun && !gData.bCleanOutMode && pEquipData->bUseVisionInspect) {
		int nTimeOut = 0;
		while(gData.nVisionFOBMode == -1) {
			nTimeOut++;
			if (nTimeOut > 50) break;	//Time Out 5초
			pCommon->Delay_Time(100);
		}
		if (gData.nVisionFOBMode == 1) {
			if (pCommon->Show_MsgBox(2,"Vision FOB Mode 상태 입니다. 진행 하시겠습니까?") != IDOK) {
				m_rdoWorkStart.SetCheck(FALSE);
				return FALSE;

			} else {
				// FOB 모드일때 시작하면 MES 꺼주고 시작한다.
				m_chkMESUse.SetCheck(FALSE);

				CIniFileCS INI("System/EquipData.ini");
				if (!INI.Check_File()) {
					AfxMessageBox("EquipData.ini File Not Found!!!");
					return FALSE;
				}
				INI.Set_Bool("OPTION", "MES_USE", FALSE);
				pDataManager->Read_EquipData();
				g_objMES.Set_MESUse(FALSE);
			}
		}
	}
#endif
	gData.bCheckStartComplete = TRUE;
	return TRUE;
}

void CWorkDlg::OnBnClickedBtnConvClear()
{
	m_stcConveyor.SetWindowText("0");
}

void CWorkDlg::OnBnClickedLotID()
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (m_rdoWorkStart.GetCheck() && gData.nDoorInterlock18 != 1) {
		pCommon->Show_MsgBox(1, "Run중에는 Lot ID를 수정 할수 없습니다........");
		return;
	}

	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcLotId1.SetWindowText(strKey);
		gData.sLotID = strKey;
	}

	CString sLog;
	sLog.Format("[Work Mode] Lot ID Input....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, gData.nCMJobCount, gData.sOperID);
	pLogFile->Save_HandlerLog(sLog);
}
void CWorkDlg::OnBnClickedTrayCnt()
{
	return;
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	if(!pEquipData->bUseMES)
	{
		m_stcLotId2.GetWindowText(strOld);
		if (pCommon->Show_NumPad(strOld, strNew) == IDOK)
		{
			m_stcLotId2.SetWindowText(strNew);
			gData.nTrayJobCount = atoi(strNew);

			gData.nCMJobCount = gData.nTrayJobCount * gData.nCMMaxCount;
			strOld.Format("%d", gData.nCMJobCount);
			m_stcCMCnt.SetWindowText(strOld);
		}
	}	
}

void CWorkDlg::OnBnClickedCMCnt()
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (m_rdoWorkStart.GetCheck() && gData.nDoorInterlock18 != 1) {
		pCommon->Show_MsgBox(1, "Run중에는 CM수량 입력을 할수 없습니다........");
		return;
	}
	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	if(!pEquipData->bUseMES)
	{
		CString strOld, strNew;
		int nCM, nCM1, nCM2; 
		m_stcCMCnt.GetWindowText(strOld);
		if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
			m_stcCMCnt.SetWindowText(strNew);
			nCM = atoi(strNew);
			gData.nCMJobCount = nCM;

			nCM1 = nCM / gData.nCMMaxCount;
			nCM2 = nCM % gData.nCMMaxCount;
			if(nCM2 > 0) nCM1++;
			gData.nTrayJobCount = nCM1;
			strNew.Format("%d", gData.nTrayJobCount);
			m_stcLotId2.SetWindowText(strNew);  
		}
	}	

	CString sLog;
	sLog.Format("[Work Mode] CMCnt push....  LotID[%s] CM[%d]", gData.sLotID, gData.nCMJobCount);
	pLogFile->Save_HandlerLog(sLog);
}


///////////////////////////////////////////////////////////////////////////////
// User Functions

void CWorkDlg::Initial_Controls() 
{
	for (int i = 0; i <= 2; i++) m_Group[i].Init_Ctrl("바탕", 13, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 4; i <= 6; i++) m_Group[i].Init_Ctrl("바탕", 13, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 0; i < 3; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x40, 0x80));	// Model
	for (int i = 6; i < 9; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x00, 0x80));	// RFID
	for (int i = 19; i < 22; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x80, 0x00));	// Test
	m_Label[3].Init_Ctrl("바탕", 10, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x80, 0x00));
	m_Label[29].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x80, 0x00));
	m_Label[37].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x80, 0x00));
	m_LabelDoor.Init_Ctrl("바탕", 40, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x80, 0x00));

	for (int i = 22; i < 24; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));	// Elect,Laser
	for (int i = 24; i < 29; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));	// Slot
	for (int i = 30; i < 35; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));	// Slot

	for (int i = 35; i < 37; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));	// List
	for (int i = 38; i < 39; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));	// Count  RGB(0x01, 0x80, 0x40)
//	for (int i = 39; i < 48; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT);
		
	m_stcModelName.Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xF0, 0xFF, 0xB0));
	m_stcStripSize.Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xF0, 0xFF, 0xB0));
	m_stcStripType.Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xF0, 0xFF, 0xB0));
	m_LabelstcCMCnt.Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x40, 0x80));
	
	m_stcLotId2.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xF0, 0xE0, 0xF0));
	m_stcPartNo2.Init_Ctrl("바탕", 10, FALSE, COLOR_DEFAULT, RGB(0xF0, 0xE0, 0xF0));
	m_stcCMCnt.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xF0, 0xE0, 0xF0));

	m_stcLotId1.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xF0, 0xE0, 0xF0));

	m_bmpImage.LoadBitmap(IDB_EQUIPMENT);
	m_Image.SetBitmap(m_bmpImage);
	m_Image.SetWindowPos(NULL, 0, 0, 691, 535, SWP_NOZORDER | SWP_NOMOVE);

	//m_stcElecValue.Init_Ctrl("바탕", 13, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0x01, 0x00, 0x00));
	//m_stcWarpValue.Init_Ctrl("바탕", 13, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0x01, 0x00, 0x00));

	for (int i = 0; i < 18; i++) m_stcWorkSlot[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x01, 0x00, 0x00));

	m_btnConvClear.Init_Ctrl("바탕", 11, FALSE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	m_stcConveyor.Init_Ctrl("바탕", 15, TRUE, RGB(0xF0, 0x20, 0x60), RGB(0xF0, 0xF0, 0xFF));
		
	m_stcLoadCount.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x01, 0x00, 0x00));
	m_stcUnloadCount.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x01, 0x00, 0x00));

	m_ledAutoStartEnable.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00), CLedCS::emGreen, CLedCS::em24);
	m_rdoWorkStart.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoWorkStop.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_chkStripStop.Init_Ctrl("바탕", 9, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_chkLotStop.Init_Ctrl("바탕", 10, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_chkSampleJob.Init_Ctrl("바탕", 10, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnBuzzerOff.Init_Ctrl("바탕", 8, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnLotCancel.Init_Ctrl("바탕", 8, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);

	for (int i = 0; i < 12; i++) m_stcWorkCase[i].Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 4; i++) m_stcTrayPos[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xF0, 0xFF, 0xB0));
	for (int i = 0; i < 6; i++) m_ledIndexJob[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			m_ledIndexSlot[i][j].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			m_ledPicker[i][j].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
		}
	}
	m_Label[9].Init_Ctrl("바탕", 10, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x00, 0x80));
	m_ledBarAlarm.Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	m_ledBarNG.Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	m_chkMESUse.Init_Ctrl("Arial", 12, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0xC0, 0x10, 0x30), CCheckCS::emRed, CCheckCS::emRight);
	m_chkAllPass.Init_Ctrl("Arial", 12, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0xC0, 0x10, 0x30), CCheckCS::emRed, CCheckCS::emRight);

	for (int i = 0; i < 4; i++) m_stcLoadPickNo[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));

	Initial_ShiftGrid();
}

void CWorkDlg::Display_Status()
{
	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();

	CString strTemp, strText;
	
	if (gData.bUseDoorLock==FALSE)	m_LabelDoor.ShowWindow(TRUE);
	else							m_LabelDoor.ShowWindow(FALSE);

	strText.Format("%d", gData.LoadTrayNo);
	m_stcWorkSlot[0].SetWindowText(strText);

	strText.Format("%d", gData.nTrayPos[0]);
	m_stcWorkSlot[1].SetWindowText(strText);

	strText.Format("%d", gData.nIndexPos);
	m_stcWorkSlot[2].SetWindowText(strText);

	for (int i = 0; i < 4; i++) 
	{ 
		strText.Format("%d-%d", gData.LoadTrayNo, (gData.nTrayPos[0]-1)*gData.nPickCnt + i); 
		m_stcLoadPickNo[i].SetWindowText(strText); 
	}


	int		i, j, nTCnt, nUPEH;
	double	dTackTime[3];
	SYSTEMTIME time;
	GetLocalTime(&time);
	
	gLot.sEndTime.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	i = time.wHour;
	nTCnt = 0;
	dTackTime[0] = dTackTime[1] = dTackTime[2] = 0.0;
	for(j=0; j<gTD.dTack[i][49]; j++) 
	{
		dTackTime[0] = dTackTime[0] + gTD.dTack[i][j];
		nTCnt++;
	}
	if (nTCnt>1) dTackTime[0] = dTackTime[0] / nTCnt;

	nTCnt = 0;
	if (i>=7 && i<=18) 
	{
		for(i=7; i<=18; i++) 
		{
			for(j=0; j<gTD.dTack[i][49]; j++) 
			{
				dTackTime[1] = dTackTime[1] + gTD.dTack[i][j];
				nTCnt++;
			}
		}
	} 
	else 
	{
		for(i=0; i<7; i++) 
		{
			for(j=0; j<gTD.dTack[i][49]; j++) 
			{
				dTackTime[1] = dTackTime[1] + gTD.dTack[i][j];
				nTCnt++;
			}
		}
		for(i=19; i<=23; i++)
		{
			for(j=0; j<gTD.dTack[i][49]; j++) 
			{
				dTackTime[1] = dTackTime[1] + gTD.dTack[i][j];
				nTCnt++;
			}
		}
	}
	if (nTCnt>1) dTackTime[1] = dTackTime[1] / nTCnt;

	nTCnt = 0;
	for(i=0; i<=23; i++) 
	{
		for(j=0; j<gTD.dTack[i][49]; j++)
		{
			dTackTime[2] = dTackTime[2] + gTD.dTack[i][j];
			nTCnt++;
		}
	}
	if (nTCnt>1) dTackTime[2] = dTackTime[2] / nTCnt;

	// Tack
	if (gTD.dTackTime==0) strText = "";
	else strText.Format("%0.5f", gTD.dTackTime);
	m_stcWorkSlot[3].SetWindowText(strText);

	if (dTackTime[0]==0) strText = "";
	else strText.Format("%0.5f", dTackTime[0]);
	m_stcWorkSlot[4].SetWindowText(strText);

	if (dTackTime[1]==0) strText = "";
	else strText.Format("%0.5f", dTackTime[1]);
	m_stcWorkSlot[5].SetWindowText(strText);

	if (dTackTime[2]==0) strText = "";
	else strText.Format("%0.5f", dTackTime[2]);
	m_stcWorkSlot[6].SetWindowText(strText);

	//UPEH
	if (gTD.dTackTime==0) strText = "";
	else { nUPEH = int(3600 / gTD.dTackTime); strText.Format("%d", nUPEH); }
	m_stcWorkSlot[7].SetWindowText(strText);

	if (dTackTime[0]==0) strText = "";
	else { nUPEH = int(3600 / dTackTime[0]); strText.Format("%d", nUPEH); }
	m_stcWorkSlot[8].SetWindowText(strText);

	if (dTackTime[1]==0) strText = "";
	else { nUPEH = int(3600 / dTackTime[1]); strText.Format("%d", nUPEH); }
	m_stcWorkSlot[10].SetWindowText(strText);

	if (dTackTime[2]==0) strText = "";
	else { nUPEH = int(3600 / dTackTime[2]); strText.Format("%d", nUPEH); }
	m_stcWorkSlot[11].SetWindowText(strText);

	//생산량
	if (gTD.dCount[0]==0) strText = "";
	else strText.Format("%d", gTD.dCount[0]);
	m_stcWorkSlot[12].SetWindowText(strText);

	if (gTD.dCount[1]==0) strText = "";
	else strText.Format("%d", gTD.dCount[1]);
	m_stcWorkSlot[13].SetWindowText(strText);

	if (gLot.nCMCount==0) strText = "";
	else strText.Format("%d", gLot.nCMCount);
	m_stcWorkSlot[14].SetWindowText(strText);

	if (gLot.nGoodCnt==0) strText = "";
	else strText.Format("%d", gLot.nGoodCnt);
	m_stcWorkSlot[15].SetWindowText(strText);

	if (gLot.nNGCnt==0) strText = "";
	else strText.Format("%d", gLot.nNGCnt);
	m_stcWorkSlot[16].SetWindowText(strText);

//	if (gLot.nMESNGCnt==0) strText = "";
//	else strText.Format("%d", gLot.nMESNGCnt);
//	m_stcWorkSlot[17].SetWindowText(strText);

	int nLoadCnt;
	nLoadCnt = gData.nTrayJobCount - gData.nLoadTrayCount;  
	if(nLoadCnt < 0) nLoadCnt = 0;
	strText.Format("%d", nLoadCnt);
	m_stcLoadCount.SetWindowText(strText);

	strText.Format("%d", gData.nEmptyTrayCount);
	m_stcUnloadCount.SetWindowText(strText);

	strText.Format("%d", gData.nGoodTrayCount);
	m_stcWorkSlot[9].SetWindowText(strText);

	CSequenceInit *pSequenceInit = CSequenceInit::Get_Instance();
	m_bInitialOk = pSequenceInit->Get_InitComplete();

	if (m_bInitialOk) m_ledAutoStartEnable.Set_On(TRUE);
	else m_ledAutoStartEnable.Set_On(FALSE);

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	for(int i=0; i<4; i++) 
	{
		for(int j=0; j<6; j++)
		{
			if(gData.PickerInfor[i][j] == 0) m_ledPicker[i][j].Set_On(FALSE);
			else							 m_ledPicker[i][j].Set_On(TRUE);
		}
	}

	if(gData.bUseBar2Alarm) m_ledBarAlarm.Set_On(TRUE);
	else					m_ledBarAlarm.Set_On(FALSE);
	//if(gData.bUseBar2NG) m_ledBarNG.Set_On(TRUE);
	if(gData.bUseDoorLock) m_ledBarNG.Set_On(TRUE);
	else				 m_ledBarNG.Set_On(FALSE);

 /*
	//NG barcode reading..
	CString sData;
	int nData;
	if(gData.bNGBarcodeUse == TRUE)
	{
		CExtBarcode_Honeywell *pExtBarcode = CExtBarcode_Honeywell::Get_Instance();
		pExtBarcode->GetBarcode(sData);
		nData = sData.GetLength();
		if(nData > 0) {
			m_stcPartNo2.SetWindowText(sData);
	
		}
	}
*/
	//LotID barcode reading..
	CString sData, sBarcode;
	int		nData, x;
	sData = "";
	CBarcode_DS1100 *pBarcode_DS1100 = CBarcode_DS1100::Get_Instance();
	pBarcode_DS1100->GetBarcode(sData);
			
	nData = sData.GetLength();
	if(nData > 0 && gData.nLotInfoBlockDelay == 0) 
	{
		m_stcLotId1.SetWindowText(sData);

		if (gData.sLotID != sData) {
			pDY0->oAlarmBuzzer2 = TRUE;
			pAJinAXL->Write_Output(0);
			Sleep(1000);
			pDY0->oAlarmBuzzer2 = FALSE;
			pAJinAXL->Write_Output(0);

			SendMessage(UM_UPDATE_LOTID, (WPARAM)NULL, (LPARAM)NULL);
		}
		gData.sLotID = sData;

		COperatorDlg *pOperatorDlg = COperatorDlg::Get_Instance();
		pOperatorDlg->m_stcOperLotID.SetWindowText(gData.sLotID);

		CString sLog;
		sLog.Format("[Work Mode] Barcode Input....  Barcode : [%s]", sData);
		pLogFile->Save_HandlerLog(sLog);

		sData.Empty();
		nData = 0;

	} 
	/*
	if		(gData.sLotID.Mid(0, 6) == "GSY481") sData = "K12";
	else if (gData.sLotID.Mid(0, 6) == "GSY487") sData = "K14";
	else if (gData.sLotID.Mid(0, 6) == "GSY518") sData = "K51";
	else if (gData.sLotID.Mid(0, 6) == "GSY555") sData = "K61";
//	else if (gData.sLotID.Mid(0, 5) == "GSY62")  sData = "K62";
//	else if (gData.sLotID.Mid(0, 5) == "GSY63")  sData = "K63";
	else										 sData = gData.sRecipeName;

	if (sData.GetLength() > 0 && sData != gData.sRecipeName) {
		CIniFileCS INI("System/EquipData.ini");
		INI.Set_String("MODEL", "CURRENT", sData);

		CDataManager *pDataManager = CDataManager::Get_Instance();
		pDataManager->Read_ModelData();
		MODEL_DATA *pModelData = pDataManager->Get_pModelData();

		m_stcModelName.SetWindowText(pModelData->sModelName);
		gData.sRecipeName = pModelData->sModelName;	         
	}
*/
	int nCase[12];
	pSequenceMain->Get_RunCase(nCase[0], nCase[1], nCase[2], nCase[3], nCase[4], nCase[5], nCase[6], nCase[7], nCase[8], nCase[9], nCase[10], nCase[11]);
	for (int i = 0; i < 12; i++) {
		strText.Format("%03d", nCase[i]);
		m_stcWorkCase[i].SetWindowText(strText);
	}
//	int nRunSts = pSequenceMain->Get_IsAutoRun();
//	if(nRunSts == 0) {
//		m_chkSampleJob.SetCheck(FALSE);
//		m_chkSampleJob.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
//		m_chkSampleJob.SetWindowText("Clean Out");
//	}

	for (int i = 0; i < 4; i++) {
		strText.Format("%d", gData.nTrayPos[i]);
		m_stcTrayPos[i].SetWindowText(strText);
	}
	strText.Format("%d", gData.nIndexPos);
	m_stcPartNo2.SetWindowText(strText);
	for (int i = 0; i < 6; i++) {
		if (gData.IndexJob[i] == 1) m_ledIndexJob[i].On();
		else						m_ledIndexJob[i].Off();
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (i==0) x = 0;
			if (i==1) x = 1;
			if (i==2) x = 2;
			if (i==3) x = 4;
			if (i==4) x = 6;
			if (gData.IndexInfo[x][j] == 0) m_ledIndexSlot[i][j].Off();
			else							m_ledIndexSlot[i][j].On();
		}
	}

	if (m_nDisCnt==0 || m_rdoWorkStart.GetCheck()) Display_Tray();
}

void CWorkDlg::Display_LotInfo()
{
	CString strText;

	for (int i = 6; i < 8; i++) m_Label[i].ShowWindow(SW_SHOW);
	m_LabelstcCMCnt.ShowWindow(SW_SHOW);
	m_stcLotId1.ShowWindow(SW_SHOW);
	m_stcLotId2.ShowWindow(SW_SHOW);
	m_stcCMCnt.ShowWindow(SW_SHOW);

	if (gData.sLotID.GetLength() < 1) gData.sLotID = "LOT_ID";
	m_stcLotId1.SetWindowText(gData.sLotID);

	strText.Format("%d", gData.nTrayJobCount);
	m_stcLotId2.SetWindowText(strText);

	strText.Format("%d", gData.nCMJobCount);
	m_stcCMCnt.SetWindowText(strText);
}



void CWorkDlg::Enable_LotInfo(BOOL on)
{
	m_stcLotId1.EnableWindow(on);
	m_stcLotId2.EnableWindow(on);
	m_stcCMCnt.EnableWindow(on);

}


DWORD CALLBACK CWorkDlg::StreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CFile *pFile = (CFile*)dwCookie;
	*pcb = pFile->Read(pbBuff, cb);
	return 0;
}

void CWorkDlg::Set_AutoRun(BOOL bAutoRun)
{
	if (bAutoRun) {
		m_rdoWorkStart.SetCheck(TRUE);
	} else {
		m_rdoWorkStop.SetCheck(TRUE);
	}
}

void CWorkDlg::Set_CleanOutMode()
{
	m_chkSampleJob.SetCheck(FALSE);
//	m_chkSampleJob.SetWindowText("Clean Out");
	gData.bCleanOutMode = FALSE;
}

void CWorkDlg::Set_AlaramLog()
{
	CString sData;
	SYSTEMTIME time;

	gAlm.nType = 0;
	GetLocalTime(&time);
	gAlm.lEndTime = GetTickCount();
	gAlm.sEndTime.Format("%04d%02d%02d_%02d%02d%02d %03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	gAlm.lProcTime = gAlm.lEndTime - gAlm.lStartTime;
	sData.Format("%s,%s,%s,%s,%s,%d", gAlm.sLotID, gAlm.sAlmNo, gAlm.sAlmMsg, gAlm.sStartTime, gAlm.sEndTime, gAlm.lProcTime);

	
	//pLogFile->Save_AlarmLog(sData);
	pLogFile->Save_AlarmResetLog(sData);

	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetMainWnd();
	pMainDlg->Set_LotErrorLog("RESET", 905, "Error Reset");
}

///////////////////////////////////////////////////////////////////////////////
// Message

LRESULT CWorkDlg::OnUpdateModel(WPARAM wParam, LPARAM lParam)
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	MODEL_DATA *pModelData = pDataManager->Get_pModelData();

	CString strText;

	m_stcModelName.SetWindowText(pModelData->sModelName);
	strText.Format("%d X %d", pModelData->nArrayL, pModelData->nArrayW);
	m_stcStripSize.SetWindowText(strText);

	strText.Format("%0.1lf X %0.1lf", pModelData->dPitchL, pModelData->dPitchW);
	m_stcStripType.SetWindowText(strText);

	return 0;
}

LRESULT CWorkDlg::OnUpdateRfid(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CWorkDlg::OnUpdateJobList(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CWorkDlg::OnUpdateShiftList(WPARAM wParam, LPARAM lParam)
{
	int nOp = (int)wParam;

	if (nOp == OP_CLEAR) {			// Clear
		Initial_ShiftGrid();
	} else if (nOp == OP_INSERT) {	// Insert
		Add_ShifeError();
	}

	return 0;
}

LRESULT CWorkDlg::OnUpdateLotID(WPARAM wParam, LPARAM lParam)
{
	if (gData.nDoorInterlock18 != 1) return 0;

	OnBnClickedCMCnt();

	CString strOper;
	int nOper;

	COperatorDlg *pOperatorDlg = COperatorDlg::Get_Instance();
	pOperatorDlg->m_stcOperCMCnt.GetWindowText(strOper);
	nOper = atoi(strOper);

	if (gData.nCMJobCount != nOper) {
		strOper.Format("%d", gData.nCMJobCount);
		pOperatorDlg->m_stcOperCMCnt.SetWindowText(strOper);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void CWorkDlg::Display_Tray()
{
	int xx, yy, xs, ys, xe, ye, aa, nCnt;
	int txs, tys, txe, tye, ttxs, ttys, ttxe, ttye;
	CString	sName;

	xs=2; ys=595;
	xe=1250; ye=260;
	txs = tys = txe = tye = 0;

	CClientDC pDC(this); // 현재 화면의 정보를 얻음
    CPen	penLine;	// 사용할 pen 의 셋팅
    CPen	*OldPen;	// 기존에 사용하던 설정으로 복구할 변수
    penLine.CreatePen(PS_SOLID,1,RGB(0,0,0));
    OldPen = pDC.SelectObject((&penLine));

    //////////////////////////////////////////////////////////////////////////
    // 실제 출력될 내용
	if (gData.nArrayL == 0) gData.nArrayL = 4;	//[L]=[X]=5
	if (gData.nArrayW == 0) gData.nArrayW = 3;	//[W]=[Y]=8

	int xxt = (310 / gData.nArrayL) - 4 - 2;
	int yyt = (260 / gData.nArrayW) - 4 - 2 ;

	xx = 6;
	for(int i=0; i<4; i++) {
		txs = xs + (xx*i) + (310*i);
		tys = ys;
		txe = 310;
		tye = ye;
		pDC.FillSolidRect(txs,tys,txe,tye,RGB(255,167,167));

		nCnt = 1;
		for(int y=0; y<gData.nArrayW; y++) {		//8
			for(int x=0; x<gData.nArrayL; x++) {	//5
				ttxs = (txs+10) + (4*x) + (xxt*x);
				ttys = (ys+8) + (4*y) + (yyt*y);
				ttxe = xxt;
				ttye = yyt;

				if      (i==0)	yy = gData.LoadTrayInfo[y][x];
				else if (i==1)	yy = gData.NG1TrayInfo[y][x];
				else if (i==2)	yy = gData.NG2TrayInfo[y][x];
				else			yy = gData.GoodTrayInfo[y][x];

				if      (yy== 0)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(255,255,255));//White
				else if (yy== 1)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(0,255,0));	//Green (Good)
				else if (yy== 2)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(255,0,0));	//Red   (NG) 
				else if (yy== 3)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(0,0,255));	//Blue  (NG-Barcode Reading OK)
				else if (yy== 7)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(255,255,0));	//Yellow(Barrel Lens NG)
				else if (yy== 8)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(255,0,255));	//Pink  (Side Fill NG)
				else if (yy==11)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(255,0,255));	//Pink  (Stiffener NG)
				else if (yy==12)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(255,0,255));	//Pink  (Lens 원자재 NG)
				else if (yy==13)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(255,0,255));	//Pink  (Lens Fiducial Notch Broken)
				else if (yy==14)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(255,128,0));	//Orange(Shiny Edge)
				else				pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(0,0,0));		//Black (NG-Barcode Reading Fail)

				if      (yy== 0)	pDC.SetTextColor(RGB(0,0,0));
				else if (yy== 1)	pDC.SetTextColor(RGB(0,0,0));		//Black
				else if (yy== 7)	pDC.SetTextColor(RGB(0,0,0));		//Black
				else if (yy==14)	pDC.SetTextColor(RGB(0,0,0));		//Black
				else				pDC.SetTextColor(RGB(255,255,255));

// 				if      (yy==0) pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(255,255,255));//White
// 				else if (yy==1)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(0,255,0));	//Green (Good)
// 				else if (yy==2)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(255,0,0));	//Red   (NG) 
// 				else if (yy==3)	pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(0,0,255));	//Blue  (NG-Barcode Reading OK)
// 				else			pDC.FillSolidRect(ttxs,ttys,ttxe,ttye,RGB(0,0,0));		//Black (NG-Barcode Reading Fail)
// 				
// 				if      (yy==0) pDC.SetTextColor(RGB(0,0,0));
// 				else if (yy==1)	pDC.SetTextColor(RGB(0,0,0));		//Black
// 				else if (yy==2)	pDC.SetTextColor(RGB(255,255,255));	//White
// 				else if (yy==3)	pDC.SetTextColor(RGB(255,255,255));
// 				else			pDC.SetTextColor(RGB(255,255,255));
				
								//pDC.SetTextColor(RGB(0,0,255));	//Blue
				sName.Format("%d", nCnt++);
				aa = 3 + (sName.GetLength()*2);
				pDC.TextOut(ttxs+(ttxe/2)-aa, ttys+(ttye/4), sName,  sName.GetLength());
			}
		}
	}
	// empty: RGB(255,255,255));
	// Good:  RGB(0,255,0));
	// NG:    RGB(255,0,0));

    //////////////////////////////////////////////////////////////////////////
    pDC.SelectObject(OldPen); // 기존의 상태로 복구
	m_nDisCnt++;
	if(m_nDisCnt>10) m_nDisCnt=0;
}

/*
LRESULT CWorkDlg::OnUpdateConvList(WPARAM wParam, LPARAM lParam)
{
	int nOp = (int)wParam;
	CString strValue = *(CString*)wParam;
	CString strLotid = *(CString*)lParam;

	if (nOp == OP_CLEAR) {			// Clear
		SetDlgItemInt(IDC_STC_CONVEYOR, 0);
	} else if (nOp == OP_INSERT) {	// Insert
		int nCount = GetDlgItemInt(IDC_STC_CONVEYOR);
		if (nCount < 100) SetDlgItemInt(IDC_STC_CONVEYOR, ++nCount);
	} else if (nOp == OP_DELETE) {	// Delete
		int nCount = GetDlgItemInt(IDC_STC_CONVEYOR);
		if (nCount > 0) SetDlgItemInt(IDC_STC_CONVEYOR, --nCount);
	}
	return 0;
}
	pWorkDlg->SendMessage(UM_UPDATE_RFID, (WPARAM)RFID_CH2, (LPARAM)NULL);
	if (m_strLotId1 != "") {
		CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
		pWorkDlg->SendMessage(UM_UPDATE_BUFF_LIST, (WPARAM)OP_INSERT, (LPARAM)&m_strLotId1);
	}
*/

void CWorkDlg::Initial_ShiftGrid()
{
	m_grdShiftList.Set_RowCount(1);
	m_grdShiftList.Set_ColCount(3);
	m_grdShiftList.Set_FixRowCount(1);
	m_grdShiftList.Set_FixColCount(1);

	m_grdShiftList.Set_ColWidth(0, 40);
	m_grdShiftList.Set_ColWidth(1, 80);
	m_grdShiftList.Set_ColWidth(2, 70);

	m_grdShiftList.Set_CellText(0, 0, "");
	m_grdShiftList.Set_CellText(0, 1, "NG-Tray No");
	m_grdShiftList.Set_CellText(0, 2, "Position");

	for (int i = 0; i < 3; i++) m_grdShiftList.Set_CellAlign(0, i, CELL_ALIGN_CENTER);
}

void CWorkDlg::Add_ShifeError()
{
	CString str;

	
	str.Format("Barcode Shift => LotID[%s] NG_Tray_NO[%d] Position[%d]", gLot.sLotID, gData.nNGTrayPos, gData.nNGPos);
	pLogFile->Save_HandlerLog(str);

	int nRows = m_grdShiftList.Get_RowCount();
	if (nRows>20) return;

	m_grdShiftList.Set_RowCount(nRows + 1);

	str.Format("%d", nRows);
	m_grdShiftList.Set_CellText(nRows, 0, str);

	str.Format("%d", gData.nNGTrayPos);
	m_grdShiftList.Set_CellText(nRows, 1, str);

	str.Format("%d", gData.nNGPos);
	m_grdShiftList.Set_CellText(nRows, 2, str);

	for (int j = 0; j < 3; j++) m_grdShiftList.Set_CellAlign(nRows, j, CELL_ALIGN_CENTER);

}

void CWorkDlg::OnBnClickedBtnLotCancel()
{
	CCommon *pCommon = CCommon::Get_Instance();
	if (m_rdoWorkStart.GetCheck()) {
		pCommon->Show_MsgBox(1, "You can't cancel the Lot during Run.........");
		return;
	}
	if (!m_chkMESUse.GetCheck()) {
		pCommon->Show_MsgBox(1, "You can't cancel the MES No_Use.........");
		return;
	}

	g_objMES.Set_LotCancel(gData.sLotID, gData.nCMJobCount, gData.sOperID);

	CString sLog;
	sLog.Format("Lot Cancel OK...  => Lot[%s] 취소를 MES에 전송하였습니다.", gData.sLotID);
//	pCommon->Show_MsgBox(1, sLog);
	AfxMessageBox(_T(sLog));

	pLogFile->Save_HandlerLog(sLog);
}

void CWorkDlg::AutoStop()
{
	m_rdoWorkStop.SetCheck(TRUE);
	m_rdoWorkStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
}

LRESULT CWorkDlg::OnLotStartEnd(WPARAM wParam, LPARAM lParam)
{
	CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetMainWnd();
	CCommon *pCommon = CCommon::Get_Instance();
	if (wParam == 1) {
		pMainDlg->Set_LotErrorLog("LOT START", 901, "Lot Start");
	} else if (wParam == 2) {
		pMainDlg->Set_LotErrorLog("LOT END", 902, "Lot End");
		if (gLot.nBsNGCnt > 0) {
			
			CString strMsg, strLog;
			strMsg.Format("Barcode Shift Error %d ea 발생!! NG Tray를 확인하여 주세요.........", gLot.nBsNGCnt);
			strLog.Format("[Barcode Shift] %s", strMsg);
			pLogFile->Save_HandlerLog(strLog);
			pCommon->Show_MsgBox(1, strMsg);
		}
	}
	return 0;
}

void CWorkDlg::OnBnClickedChkLotStop()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

	if (m_chkLotStop.GetCheck()) {
		pDY0->oInsideLamp = TRUE;
	} else {
		pDY0->oInsideLamp = FALSE;
	}		
	pAJinAXL->Write_Output(0);
}

void CWorkDlg::OnBnClickedBtnBuzzerOff()
{
	gData.m_bBuzzerOff = TRUE;

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();
	pDY0->oAlarmBuzzer1 = FALSE;
	pDY0->oAlarmBuzzer2 = FALSE;
	pAJinAXL->Write_Output(0);

#ifndef AJIN_BOARD_USE
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_Interlock(1);
#endif
}


void CWorkDlg::OnBnClickedChkAllPass()
{
	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();
	CDataManager *pDataManager = CDataManager::Get_Instance();

	CString sLog;

	if(m_chkAllPass.GetCheck())
	{
		if (pSequenceMain->Get_IsAutoRun()) 
		{
			pCommon->Show_MsgBox(1, "Can't change in Auto Run.");
			m_chkAllPass.SetCheck(FALSE);
			return;
		} 
		else
		{
			CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
			if (!INI.Check_File()) { AfxMessageBox("EquipData.ini File Not Found!!!"); return; }

			INI.Set_Integer("OPTION", "DRY_NG_COUNT", 0);
			gData.nNGPercent = 0;

			INI.Set_Integer("OPTION", "DRY_RUN_USE", FALSE);
			gData.bUseDryRun = FALSE;

			pDataManager->Read_EquipData();

			gData.bUseAllPass = TRUE;

			CLogFile *pLogFile = CLogFile::Get_Instance();
			sLog.Format("[Work Mode] All Pass push....  LotID[%s] CM[%d] bUseAllPass[%d]", gData.sLotID, gData.nCMJobCount, gData.bUseAllPass);
			pLogFile->Save_HandlerLog(sLog);	
		}
	}
	else if(!m_chkAllPass.GetCheck())
	{
		gData.bUseAllPass = FALSE;

		CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
		if (!INI.Check_File()) { AfxMessageBox("EquipData.ini File Not Found!!!"); return; }

		INI.Set_Bool("OPTION", "VISION_INSPECT", TRUE);
		pDataManager->Read_EquipData();


		CLogFile *pLogFile = CLogFile::Get_Instance();
		sLog.Format("[Work Mode] All Pass push....  LotID[%s] CM[%d] bUseAllPass[%d]", gData.sLotID, gData.nCMJobCount, gData.bUseAllPass);
		pLogFile->Save_HandlerLog(sLog);	
	}	
}


void CWorkDlg::UpdateLotInfoFromMES(int nCMCount)
{
	CString strOld, strNew;
	int nTemp, nTemp1, nTemp2; 

	strOld.Format("%d", nCMCount);
	
	m_stcCMCnt.SetWindowText(strOld);
	nTemp = nCMCount;
	gData.nCMJobCount = nTemp;

	nTemp1 = nTemp / gData.nCMMaxCount;
	nTemp2 = nTemp % gData.nCMMaxCount;
	if(nTemp2 > 0) nTemp1++;
	gData.nTrayJobCount = nTemp1;
	strNew.Format("%d", gData.nTrayJobCount);
	m_stcLotId2.SetWindowText(strNew);  
	
}


void CWorkDlg::OnStcLoadPickInfoClick(UINT nID)
{
	int ID = nID - IDC_STC_LOADPICK_NO_0;

	CCommon *pCommon = CCommon::Get_Instance();

	if(pCommon->Show_MsgBox(2, "해당 모듈 Dummy 입니까?") != IDOK) return;

	//나중에 NG로 빠지게 하면 될듯 지금 그렇게 해줄 이유가 없음 
	//gData.nCNoBtm1Pick[ID] = 0; //gData.nTNoBtm1Pick[ID] = 0;
	//gData.InfoBtm1Pick[ID] = gData.nCNoBtm1Pick[ID];
	
	
	m_stcLoadPickNo[ID].Set_Color(RGB(0xFF, 0x00, 0x00), RGB(0x0F, 0x0F, 0x0F));
	gData.LoadTrayInfo[gData.nTrayPos[0]-1][ID] = 2;

	CString strLog;
	
	strLog.Format("MES NG, Clicked, TrayNo(%d), LineNo(%d), CmIndex(%d)", gData.LoadTrayNo, gData.nTrayPos[0], ID);
	pLogFile->Save_HandlerLog(strLog);

	//CString strText;
	//strText.Format("%d-%d", gData.nTNoBtm1Pick[ID], gData.nCNoBtm1Pick[ID]); m_stcB1No[ID].Set_Text(strText);

}

void CWorkDlg::ResetInfoDisplay()
{
	for (int i = 0; i < gData.nPickCnt; i++) m_stcLoadPickNo[i].Set_Color(RGB(0x00, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
}

void CWorkDlg::ResetLotInfo()
{
	CString sTemp;
	int temp = 0;
	sTemp.Format("%d", temp);
	m_stcCMCnt.SetWindowText(sTemp);
	m_stcLotId2.SetWindowText(sTemp);
}


void CWorkDlg::OnBnClickedBtnSend1()
{
	CString filePath = _T("D:\\MES\\RecipeDownload\\RECIPEDOWNLOAD_20250904_09333865.ini");
    m_sender.SendFile(filePath);
}
void CWorkDlg::FileSend()
{	
	CString filePath;
	filePath = g_objMES.m_sMESDownLoadFile;
    m_sender.SendFile(filePath);
}