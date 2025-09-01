// ManualFlowDlg.cpp : ±∏«ˆ ∆ƒ¿œ¿‘¥œ¥Ÿ.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "ManualFlowDlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

#include "ManualDlg.h"

#include "ExtBarcode_Honeywell.h"

// CManualFlowDlg ¥Î»≠ ªÛ¿⁄¿‘¥œ¥Ÿ.

IMPLEMENT_DYNAMIC(CManualFlowDlg, CDialogEx)

CManualFlowDlg::CManualFlowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualFlowDlg::IDD, pParent)
{
}

CManualFlowDlg::~CManualFlowDlg()
{
}

void CManualFlowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	DDX_Control(pDX, IDC_BTN_LO_CONV_W, m_btnLoConvW);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_UP_CONV_W_0 + i, m_btnUpConvW[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_CHK_FLOW_IF_IO_0 + i, m_chkPIOOut[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_FLOW_IF_IO_0 + i, m_ledPIOIn[i]);
	DDX_Control(pDX, IDC_LED_FLOW_IF_IO_4, m_ledPIOIn[4]);
	DDX_Control(pDX, IDC_LED_FLOW_IF_IO_5, m_ledPIOIn[5]);
	DDX_Control(pDX, IDC_LED_FLOW_IF_IO_6, m_ledPIOIn[6]);
	DDX_Control(pDX, IDC_LED_FLOW_IF_IO_7, m_ledPIOIn[7]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_LOAD_IO_0 + i, m_btnLoadIo[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_CHK_LOAD_IO_0 + i, m_chkLoadIo[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_LOAD_IO_0 + i, m_ledLoadIo[i]);
	DDX_Control(pDX, IDC_LED_BUFFER_IO, m_ledBufferIo);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_IO_0 + i, m_btnUnloadIo[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_CHK_UNLOAD_IO_0 + i, m_chkUnloadIo[i]);
	for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_LED_UNLOAD_IO_0 + i, m_ledUnloadIo[i]);
	DDX_Control(pDX, IDC_STC_LOT_ID_2, m_stcLotId2);
	DDX_Control(pDX, IDC_STC_PART_NO_2, m_stcPartNo2);
	DDX_Control(pDX, IDC_CHK_READ_RFID_2, m_chkReadRfid2);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_LOAD_COUNT1 + i, m_ledCount[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_PIO_OUT1 + i, m_ledPIOOut[i]);
	DDX_Control(pDX, IDC_STC_TIMEOUT_T1, m_stcTimeOut[1]);
	DDX_Control(pDX, IDC_STC_TIMEOUT_T3, m_stcTimeOut[3]);
	DDX_Control(pDX, IDC_STC_TIMEOUT_T4, m_stcTimeOut[4]);
	DDX_Control(pDX, IDC_STC_TIMEOUT_T6, m_stcTimeOut[6]);

	DDX_Control(pDX, IDC_BTN_UNLOAD_UP, m_btnUnloadStage[0]);
	DDX_Control(pDX, IDC_BTN_UNLOAD_DN, m_btnUnloadStage[1]);
	DDX_Control(pDX, IDC_LED_UNLOAD_UP, m_ledUnloadStage[0]);
	DDX_Control(pDX, IDC_LED_UNLOAD_DN, m_ledUnloadStage[1]);
	DDX_Control(pDX, IDC_CHK_LOAD_IO_3, m_ckLoadRightConvRun);
	DDX_Control(pDX, IDC_CHK_UNLOAD_IO_4, m_chkUnloadRightConvRun);
}

BEGIN_MESSAGE_MAP(CManualFlowDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LO_CONV_W, IDC_BTN_LO_CONV_W, OnBtnLoConvWClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UP_CONV_W_0, IDC_BTN_UP_CONV_W_1, OnBtnUpConvWClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_FLOW_IF_IO_0, IDC_CHK_FLOW_IF_IO_3, OnChkFlowIfIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_IO_0, IDC_BTN_LOAD_IO_1, OnBtnLoadIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_LOAD_IO_0, IDC_CHK_LOAD_IO_2, OnChkLoadIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_IO_0, IDC_BTN_UNLOAD_IO_1, OnBtnUnloadIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_UNLOAD_IO_0, IDC_CHK_UNLOAD_IO_3, OnChkUnloadIoClick)
	ON_BN_CLICKED(IDC_CHK_READ_RFID_2, &CManualFlowDlg::OnBnClickedChkReadRfid2)
	ON_BN_CLICKED(IDC_BTN_PIO_RESET, &CManualFlowDlg::OnBnClickedBtnPioReset)
	ON_BN_CLICKED(IDC_STC_TIMEOUT_T1, &CManualFlowDlg::OnStcTimeOutT1)
	ON_BN_CLICKED(IDC_STC_TIMEOUT_T3, &CManualFlowDlg::OnStcTimeOutT3)
	ON_BN_CLICKED(IDC_STC_TIMEOUT_T4, &CManualFlowDlg::OnStcTimeOutT4)
	ON_BN_CLICKED(IDC_STC_TIMEOUT_T6, &CManualFlowDlg::OnStcTimeOutT6)
	ON_BN_CLICKED(IDC_BTN_TIMEOUT_SAVE, &CManualFlowDlg::OnBnClickedBtnTimeoutSave)
	ON_BN_CLICKED(IDC_BTN_TIMEOUT_CANCEL, &CManualFlowDlg::OnBnClickedBtnTimeoutCancel)
	ON_BN_CLICKED(IDC_BTN_UNLOAD_UP, &CManualFlowDlg::OnBnClickedBtnUnloadUp)
	ON_BN_CLICKED(IDC_BTN_UNLOAD_DN, &CManualFlowDlg::OnBnClickedBtnUnloadDn)
	ON_BN_CLICKED(IDC_CHK_LOAD_IO_3, &CManualFlowDlg::OnBnClickedChkLoadIo3)
	ON_BN_CLICKED(IDC_CHK_UNLOAD_IO_4, &CManualFlowDlg::OnBnClickedChkUnloadIo4)

END_MESSAGE_MAP()

// CManualFlowDlg ∏ﬁΩ√¡ˆ √≥∏Æ±‚¿‘¥œ¥Ÿ.

BOOL CManualFlowDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ø©±‚ø° √ﬂ∞° √ ±‚»≠ ¿€æ˜¿ª √ﬂ∞°«’¥œ¥Ÿ.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// øπø‹: OCX º”º∫ ∆‰¿Ã¡ˆ¥¬ FALSE∏¶ π›»Ø«ÿæﬂ «’¥œ¥Ÿ.
}

void CManualFlowDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CManualFlowDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualFlowDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		//CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
		//DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();
		//DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

		////// PIO-Out
		////if (pDY0->oRFPIO_L_REQ) m_chkPIOOut[0].SetCheck(TRUE);
		////else m_chkPIOOut[0].SetCheck(FALSE);

		////if (pDY0->oRFPIO_U_REQ) m_chkPIOOut[1].SetCheck(TRUE);
		////else m_chkPIOOut[1].SetCheck(FALSE);

		////if (pDY0->oRFPIO_ABORT) m_chkPIOOut[2].SetCheck(TRUE);
		////else m_chkPIOOut[2].SetCheck(FALSE);

		////if (pDY1->oRFPIO_READY) m_chkPIOOut[3].SetCheck(TRUE);
		////else m_chkPIOOut[3].SetCheck(FALSE);

		//// Load Part
		////if (pDY1->oLoadMzAlignerFwd) m_chkLoadIo[0].SetCheck(TRUE);
		////else m_chkLoadIo[0].SetCheck(FALSE);

		////if (pDY1->oLoConvRollerRun) m_chkLoadIo[1].SetCheck(TRUE);
		////else m_chkLoadIo[1].SetCheck(FALSE);

		//if (pDY1->oUpMzAlignerFwd) m_chkLoadIo[2].SetCheck(TRUE);
		//else m_chkLoadIo[2].SetCheck(FALSE);

		//// Unload Part
		////if (pDY1->oUnloadMzAlignerFwd) m_chkUnloadIo[0].SetCheck(TRUE);
		////else m_chkUnloadIo[0].SetCheck(FALSE);

		////if (pDY1->oUnloadRfidFwd) m_chkUnloadIo[1].SetCheck(TRUE);
		////else m_chkUnloadIo[1].SetCheck(FALSE);

		////if (pDY1->oUpConvRollerRun) m_chkUnloadIo[2].SetCheck(TRUE);
		////else m_chkUnloadIo[2].SetCheck(FALSE);

		//if (pDY1->oUpConvShutterUp) m_chkUnloadIo[3].SetCheck(TRUE);
		//else m_chkUnloadIo[3].SetCheck(FALSE);

		OHTTimeOut_Display();
	}
}

void CManualFlowDlg::OnBtnLoConvWClick(UINT nID)
{
	//CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	//CCommon *pCommon = CCommon::Get_Instance();

	//if (!pAJinAXL->Is_Home(AX_LO_CONVEYOR_W)) return;
	//if (!pCommon->Check_MainDoor()) return;

	//CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	//pManualDlg->MainDoor_Lock();

	//pCommon->Move_Position(AX_LO_CONVEYOR_W, 1);
}

void CManualFlowDlg::OnBtnUpConvWClick(UINT nID) 
{
	//CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	//CCommon *pCommon = CCommon::Get_Instance();

	//if (!pAJinAXL->Is_Home(AX_UP_CONVEYOR_W)) return;
	//if (!pCommon->Check_MainDoor()) return;

	//CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	//pManualDlg->MainDoor_Lock();

	//if (nID == IDC_BTN_UP_CONV_W_0) {
	//	pCommon->Move_Position(AX_UP_CONVEYOR_W, 0);
	//} else if (nID == IDC_BTN_UP_CONV_W_1) {
	//	pCommon->Move_Position(AX_UP_CONVEYOR_W, 1);
	//}
}

void CManualFlowDlg::OnChkFlowIfIoClick(UINT nID) 
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();
	DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	//if (nID == IDC_CHK_FLOW_IF_IO_0) {
	//	if (m_chkPIOOut[0].GetCheck()) pDY0->oRFPIO_L_REQ = TRUE;
	//	else pDY0->oRFPIO_L_REQ = FALSE;
	//} else if (nID == IDC_CHK_FLOW_IF_IO_1) {
	//	if (m_chkPIOOut[1].GetCheck()) pDY0->oRFPIO_U_REQ = TRUE;
	//	else pDY0->oRFPIO_U_REQ = FALSE;
	//} else if (nID == IDC_CHK_FLOW_IF_IO_2) {
	//	if (m_chkPIOOut[2].GetCheck()) pDY0->oRFPIO_ABORT = TRUE;
	//	else pDY0->oRFPIO_ABORT = FALSE;
	//} else if (nID == IDC_CHK_FLOW_IF_IO_3) {
	//	if (m_chkPIOOut[3].GetCheck()) pDY1->oRFPIO_READY = TRUE;
	//	else pDY1->oRFPIO_READY = FALSE;
	//}
	//pAJinAXL->Write_Output(0);
	//pAJinAXL->Write_Output(1);
}

void CManualFlowDlg::OnBtnLoadIoClick(UINT nID) 
{
	//CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	//DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	//CCommon *pCommon = CCommon::Get_Instance();
	//if (!pCommon->Check_MainDoor()) return;

	//CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	//pManualDlg->MainDoor_Lock();

	//if (nID == IDC_BTN_LOAD_IO_0) {			// Load Stage Up
	//	pDY1->oUpConvShutterUp = TRUE;
	//	pDY1->oUpConvShutterDn = FALSE;
	//} else if (nID == IDC_BTN_LOAD_IO_1) {	// Load Stage Down
	//	pDY1->oUpConvShutterUp = FALSE;
	//	pDY1->oUpConvShutterDn = TRUE;
	//}
	//pAJinAXL->Write_Output(1);
}

void CManualFlowDlg::OnChkLoadIoClick(UINT nID) 
{
	//CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	//DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	//CCommon *pCommon = CCommon::Get_Instance();
	//if (!pCommon->Check_MainDoor()) return;

	//CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	//pManualDlg->MainDoor_Lock();

	//if (nID == IDC_CHK_LOAD_IO_0) {			// Load MZ Aligner Forward
	//	if (m_chkLoadIo[0].GetCheck()) pDY1->oUpMzAlignerFwd = TRUE;
	//	else pDY1->oUpMzAlignerFwd = FALSE;
	//} else if (nID == IDC_CHK_LOAD_IO_1) {	// Lower Conveyor Roller Run
	//	if (m_chkLoadIo[1].GetCheck()) pDY1->oUpLeftConvRollerRun = TRUE;
	//	else pDY1->oUpLeftConvRollerRun = FALSE;
	//} else if (nID == IDC_CHK_LOAD_IO_2) {	// Conveyor MZ Aligner Forward
	//	if (m_chkLoadIo[2].GetCheck()) pDY1->oUpMzAlignerFwd = TRUE;
	//	else pDY1->oUpMzAlignerFwd = FALSE;
	//}
	//pAJinAXL->Write_Output(1);
}

void CManualFlowDlg::OnBtnUnloadIoClick(UINT nID) 
{
	//barcode reading...
	CExtBarcode_Honeywell *m_pExtBarcode = CExtBarcode_Honeywell::Get_Instance();

	m_stcPartNo2.SetWindowText("");
	
	CString sData;
	m_pExtBarcode->GetBarcode(sData);
	m_stcLotId2.SetWindowText(sData);


	/* 
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	pManualDlg->MainDoor_Lock();
	*/
	//if (nID == IDC_BTN_UNLOAD_IO_0) {			// Unload RFID Turn Up
	//	pDY1->oUnloadRfidTurnUp = TRUE;
	//	pDY1->oUnloadRfidTrunDn = FALSE;
	//} else if (nID == IDC_BTN_UNLOAD_IO_1) {	// Unload RFID Turn Down
	//	pDY1->oUnloadRfidTurnUp = FALSE;
	//	pDY1->oUnloadRfidTrunDn = TRUE;
	//}
	//pAJinAXL->Write_Output(1);
}

void CManualFlowDlg::OnChkUnloadIoClick(UINT nID) 
{
	//CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	//DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	//CCommon *pCommon = CCommon::Get_Instance();
	//if (!pCommon->Check_MainDoor()) return;

	//CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	//pManualDlg->MainDoor_Lock();

	//if (nID == IDC_CHK_UNLOAD_IO_0) {			// Unload MZ Aligner Forward
	//	if (m_chkUnloadIo[0].GetCheck()) pDY1->oLoMzAlignerFwd = TRUE;
	//	else pDY1->oLoMzAlignerFwd = FALSE;
	//} else if (nID == IDC_CHK_UNLOAD_IO_1) {	// Unload RFID Forward 
	//	//if (m_chkUnloadIo[1].GetCheck()) pDY1->oUnloadRfidFwd = TRUE;
	//	//else pDY1->oUnloadRfidFwd = FALSE;
	//} else if (nID == IDC_CHK_UNLOAD_IO_2) {	// Upper Conveyor Roller Run
	//	if (m_chkUnloadIo[2].GetCheck()) pDY1->oLoLeftConvRollerRun = TRUE;
	//	else pDY1->oLoLeftConvRollerRun = FALSE;
	//} else if (nID == IDC_CHK_UNLOAD_IO_3) {	// Upper Conveyor Shutter Up
	//	//if (m_chkUnloadIo[3].GetCheck()) pDY1->oUpConvShutterUp = TRUE;
	//	//else pDY1->oUpConvShutterUp = FALSE;
	//}
	//pAJinAXL->Write_Output(1);
}

void CManualFlowDlg::OnBnClickedChkReadRfid2()
{
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CManualFlowDlg::Initial_Controls() 
{
	for (int i = 0; i < 5; i++) m_Group[i].Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x00, 0x10, 0xB0), COLOR_DEFAULT);
	m_Group[5].Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x70, 0x20, 0x80), COLOR_DEFAULT);
	for (int i = 6; i < 11; i++) m_Group[i].Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0xB0, 0x10, 0x20), COLOR_DEFAULT);
	m_Group[11].Init_Ctrl("πŸ≈¡", 12, TRUE, RGB(0x70, 0x20, 0x80), COLOR_DEFAULT);

	for (int i = 0; i < 4; i++) m_Label[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	m_stcAxisPos[0].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xB0));
	m_stcAxisPos[1].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0xB0, 0x10, 0x20));

	m_btnLoConvW.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnUpConvW[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);

	for (int i = 0; i < 4; i++) m_chkPIOOut[i].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_ledPIOIn[i].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

	for (int i = 0; i < 2; i++) m_btnLoadIo[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_chkLoadIo[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_ledLoadIo[i].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	m_ledBufferIo.Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

	for (int i = 0; i < 2; i++) m_btnUnloadIo[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_chkUnloadIo[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 11; i++) m_ledUnloadIo[i].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

	m_stcLotId2.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x70, 0x20, 0x80));
	m_stcPartNo2.Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x70, 0x20, 0x80));
	m_chkReadRfid2.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);

	for (int i = 0; i < 8; i++) m_ledCount[i].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 4; i++) m_ledPIOOut[i].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

	m_stcTimeOut[1].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xA0, 0xF0, 0xC0));
	m_stcTimeOut[3].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xA0, 0xF0, 0xC0));
	m_stcTimeOut[4].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xA0, 0xF0, 0xC0));
	m_stcTimeOut[6].Init_Ctrl("πŸ≈¡", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xA0, 0xF0, 0xC0));

	for (int i = 0; i < 2; i++) m_btnUnloadStage[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_ledUnloadStage[i].Init_Ctrl("πŸ≈¡", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);


	m_ckLoadRightConvRun.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_chkUnloadRightConvRun.Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
}

void CManualFlowDlg::Display_Status()
{
//
}

///////////////////////////////////////////////////////////////////////////////

void CManualFlowDlg::OnBnClickedBtnPioReset()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();
	DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	//pDY0->oRFPIO_L_REQ = FALSE;
	//pDY0->oRFPIO_U_REQ = FALSE;
	//pDY0->oRFPIO_ABORT = FALSE;
	//pDY1->oRFPIO_READY = FALSE;

	//pAJinAXL->Write_Output(0);
	//pAJinAXL->Write_Output(1);

	//// PIO-Out
	//if (pDY0->oRFPIO_L_REQ) m_chkPIOOut[0].SetCheck(TRUE);
	//else m_chkPIOOut[0].SetCheck(FALSE);

	//if (pDY0->oRFPIO_U_REQ) m_chkPIOOut[1].SetCheck(TRUE);
	//else m_chkPIOOut[1].SetCheck(FALSE);

	//if (pDY0->oRFPIO_ABORT) m_chkPIOOut[2].SetCheck(TRUE);
	//else m_chkPIOOut[2].SetCheck(FALSE);

	//if (pDY1->oRFPIO_READY) m_chkPIOOut[3].SetCheck(TRUE);
	//else m_chkPIOOut[3].SetCheck(FALSE);
}

void CManualFlowDlg::OnStcTimeOutT1()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcTimeOut[1].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcTimeOut[1].SetWindowText(strNew);
	}
}

void CManualFlowDlg::OnStcTimeOutT3()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcTimeOut[3].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcTimeOut[3].SetWindowText(strNew);
	}
}

void CManualFlowDlg::OnStcTimeOutT4()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcTimeOut[4].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcTimeOut[4].SetWindowText(strNew);
	}
}

void CManualFlowDlg::OnStcTimeOutT6()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcTimeOut[6].GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcTimeOut[6].SetWindowText(strNew);
	}
}

void CManualFlowDlg::OnBnClickedBtnTimeoutSave()
{
	int		nData;
	CString sData;

	CIniFileCS INI("System/EquipData.ini");

	m_stcTimeOut[1].GetWindowText(sData);
	nData = atoi(sData);
	INI.Set_Integer("OHT", "TIMEOUT_T1", nData);

	m_stcTimeOut[3].GetWindowText(sData);
	nData = atoi(sData);
	INI.Set_Integer("OHT", "TIMEOUT_T3", nData);

	m_stcTimeOut[4].GetWindowText(sData);
	nData = atoi(sData);
	INI.Set_Integer("OHT", "TIMEOUT_T4", nData);

	m_stcTimeOut[6].GetWindowText(sData);
	nData = atoi(sData);
	INI.Set_Integer("OHT", "TIMEOUT_T6", nData);

	OHTTimeOut_Display();
}


void CManualFlowDlg::OnBnClickedBtnTimeoutCancel()
{
	OHTTimeOut_Display();
}

void CManualFlowDlg::OHTTimeOut_Display()
{
	CDataManager *pDataManager = CDataManager::Get_Instance();
	pDataManager->Read_EquipData();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
/*
	CString sData;
	sData.Format("%d", pEquipData->nTimeOutT1);
	m_stcTimeOut[1].SetWindowText(sData);
	sData.Format("%d", pEquipData->nTimeOutT3);
	m_stcTimeOut[3].SetWindowText(sData);
	sData.Format("%d", pEquipData->nTimeOutT4);
	m_stcTimeOut[4].SetWindowText(sData);
	sData.Format("%d", pEquipData->nTimeOutT6);
	m_stcTimeOut[6].SetWindowText(sData);
*/
}

void CManualFlowDlg::OnBnClickedBtnUnloadUp()
{
	//CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	//DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	//CCommon *pCommon = CCommon::Get_Instance();
	//if (!pCommon->Check_MainDoor()) return;

	//CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	//pManualDlg->MainDoor_Lock();

	//pDY1->oLoConvShutterUp = TRUE;
	//pDY1->oLoConvShutterDn = FALSE;
	//pAJinAXL->Write_Output(1);
}


void CManualFlowDlg::OnBnClickedBtnUnloadDn()
{
	//CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	//DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	//CCommon *pCommon = CCommon::Get_Instance();
	//if (!pCommon->Check_MainDoor()) return;

	//CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	//pManualDlg->MainDoor_Lock();

	//pDY1->oLoConvShutterUp = FALSE;
	//pDY1->oLoConvShutterDn = TRUE;
	//pAJinAXL->Write_Output(1);
}


void CManualFlowDlg::OnBnClickedChkLoadIo3()
{
	// TODO: ??? ??? ?? ??? ??? 

	//CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	//DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	//CCommon *pCommon = CCommon::Get_Instance();
	//if (!pCommon->Check_MainDoor()) return;

	//CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	//pManualDlg->MainDoor_Lock();

	//if( m_ckLoadRightConvRun.GetCheck() )
	//{
	//	pDY1->oUpRightConvRollerRun = TRUE;
	//}
	//else
	//{
	//	pDY1->oUpRightConvRollerRun = FALSE;
	//}

	//pAJinAXL->Write_Output(1);
}


void CManualFlowDlg::OnBnClickedChkUnloadIo4()
{
	// TODO: ??? ??? ?? ??? ??? ?????.

	//CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	//DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	//CCommon *pCommon = CCommon::Get_Instance();
	//if (!pCommon->Check_MainDoor()) return;

	//CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	//pManualDlg->MainDoor_Lock();

	//if( m_chkUnloadRightConvRun.GetCheck() )
	//{
	//	pDY1->oLoRightConvRollerRun = TRUE;
	//}
	//else
	//{
	//	pDY1->oLoRightConvRollerRun = FALSE;
	//}

	//pAJinAXL->Write_Output(1);

}




