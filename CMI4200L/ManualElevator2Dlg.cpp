// ManualElevator2Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CMI4200L.h"
#include "ManualElevator2Dlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"
#include "ManualDlg.h"
#include "RfidManager.h"


// CManualElevator2Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualElevator2Dlg, CDialogEx)

CManualElevator2Dlg::CManualElevator2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualElevator2Dlg::IDD, pParent)
{

}

CManualElevator2Dlg::~CManualElevator2Dlg()
{
}

void CManualElevator2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_GROUP_6 + i, m_Group[i]);
	DDX_Control(pDX, IDC_STC_AXIS_POS_1, m_stcAxisPos[0]);
	DDX_Control(pDX, IDC_LABEL_1 , m_Label[0]);

	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_0 + i, m_ledGoodCVRearIO[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_0 + i, m_ledGoodCVMidIO[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_0 + i, m_ledGoodCVFrontIO[i]);

	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_6, m_ledGoodCVFrontIO[6]);

	DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_6, m_ledGoodCVRearIO[6]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_7, m_ledGoodCVRearIO[7]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_8, m_ledGoodCVRearIO[8]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_9, m_ledGoodCVRearIO[9]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_10, m_ledGoodCVRearIO[10]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_11, m_ledGoodCVRearIO[11]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_12, m_ledGoodCVRearIO[12]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_13, m_ledGoodCVRearIO[13]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_14, m_ledGoodCVRearIO[14]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_REAR_IO_15, m_ledGoodCVRearIO[15]);


	DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_8, m_ledGoodCVMidIO[8]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_9, m_ledGoodCVMidIO[9]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_10, m_ledGoodCVMidIO[10]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_11, m_ledGoodCVMidIO[11]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_12, m_ledGoodCVMidIO[12]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_13, m_ledGoodCVMidIO[13]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_14, m_ledGoodCVMidIO[14]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_15, m_ledGoodCVMidIO[15]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_16, m_ledGoodCVMidIO[16]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_MID_IO_17, m_ledGoodCVMidIO[17]);

	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_7, m_ledGoodCVFrontIO[7]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_8, m_ledGoodCVFrontIO[8]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_9, m_ledGoodCVFrontIO[9]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_10, m_ledGoodCVFrontIO[10]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_11, m_ledGoodCVFrontIO[11]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_12, m_ledGoodCVFrontIO[12]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_13, m_ledGoodCVFrontIO[13]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_14, m_ledGoodCVFrontIO[14]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_15, m_ledGoodCVFrontIO[15]);
	DDX_Control(pDX, IDC_LED_GOOD_CV_FRONT_IO_16, m_ledGoodCVFrontIO[16]);
	
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_REAR_0 , m_btnGoodCVRear[0]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_REAR_1 , m_btnGoodCVRear[1]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_REAR_2 , m_btnGoodCVRear[2]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_REAR_3 , m_btnGoodCVRear[3]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_REAR_4 , m_btnGoodCVRear[4]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_REAR_5 , m_btnGoodCVRear[5]);

	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_REAR_6 , m_btnGoodCVRear[6]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_REAR_7 , m_btnGoodCVRear[7]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_REAR_8 , m_btnGoodCVRear[8]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_REAR_9 , m_btnGoodCVRear[9]);

	


	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_GOOD_TRAY_ELEV_Z_0 + i, m_btnGoodElevZ[i]);
	
	DDX_Control(pDX, IDC_BTN_GD_TRAY_CV_MID_0 , m_btnGoodCVMid[0]);
	DDX_Control(pDX, IDC_BTN_GD_TRAY_CV_MID_1 , m_btnGoodCVMid[1]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_MID_2 , m_btnGoodCVMid[2]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_MID_3 , m_btnGoodCVMid[3]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_MID_4 , m_btnGoodCVMid[4]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_MID_5 , m_btnGoodCVMid[5]);

	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_MID_6 , m_btnGoodCVMid[6]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_MID_7 , m_btnGoodCVMid[7]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_MID_8 , m_btnGoodCVMid[8]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_MID_9 , m_btnGoodCVMid[9]);

	
					 
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_FRONT_0 , m_btnGoodCVFront[0]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_FRONT_1 , m_btnGoodCVFront[1]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_FRONT_2 , m_btnGoodCVFront[2]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_FRONT_3 , m_btnGoodCVFront[3]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_FRONT_4 , m_btnGoodCVFront[4]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_FRONT_5 , m_btnGoodCVFront[5]);

	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_FRONT_6 , m_btnGoodCVFront[6]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_FRONT_7 , m_btnGoodCVFront[7]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_FRONT_8 , m_btnGoodCVFront[8]);
	DDX_Control(pDX, IDC_BTN_GOOD_TRAY_CV_FRONT_9 , m_btnGoodCVFront[9]);


}


BEGIN_MESSAGE_MAP(CManualElevator2Dlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_0, IDC_BTN_GOOD_TRAY_CV_REAR_0, OnBtnGoodCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_1, IDC_BTN_GOOD_TRAY_CV_REAR_1, OnBtnGoodCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_2, IDC_BTN_GOOD_TRAY_CV_REAR_2, OnBtnGoodCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_3, IDC_BTN_GOOD_TRAY_CV_REAR_3, OnBtnGoodCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_4, IDC_BTN_GOOD_TRAY_CV_REAR_4, OnBtnGoodCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_5, IDC_BTN_GOOD_TRAY_CV_REAR_5, OnBtnGoodCVRearClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_6, IDC_BTN_GOOD_TRAY_CV_REAR_6, OnBtnGoodCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_7, IDC_BTN_GOOD_TRAY_CV_REAR_7, OnBtnGoodCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_8, IDC_BTN_GOOD_TRAY_CV_REAR_8, OnBtnGoodCVRearClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_9, IDC_BTN_GOOD_TRAY_CV_REAR_9, OnBtnGoodCVRearClick)

	//ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_6, IDC_BTN_GOOD_TRAY_CV_REAR_5, OnBtnGoodCVRearClick)
	//ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_7, IDC_BTN_GOOD_TRAY_CV_REAR_5, OnBtnGoodCVRearClick)
	//ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_8, IDC_BTN_GOOD_TRAY_CV_REAR_5, OnBtnGoodCVRearClick)
	//ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_REAR_9, IDC_BTN_GOOD_TRAY_CV_REAR_5, OnBtnGoodCVRearClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_FRONT_0, IDC_BTN_GOOD_TRAY_CV_FRONT_0, OnBtnGoodCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_FRONT_1, IDC_BTN_GOOD_TRAY_CV_FRONT_1, OnBtnGoodCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_FRONT_2, IDC_BTN_GOOD_TRAY_CV_FRONT_2, OnBtnGoodCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_FRONT_3, IDC_BTN_GOOD_TRAY_CV_FRONT_3, OnBtnGoodCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_FRONT_4, IDC_BTN_GOOD_TRAY_CV_FRONT_4, OnBtnGoodCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_FRONT_5, IDC_BTN_GOOD_TRAY_CV_FRONT_5, OnBtnGoodCVFrontClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_ELEV_Z_0, IDC_BTN_GOOD_TRAY_ELEV_Z_3, OnBtnGoodElevZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GD_TRAY_CV_MID_0, IDC_BTN_GD_TRAY_CV_MID_1, OnBtnGoodCVMidClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_MID_2, IDC_BTN_GOOD_TRAY_CV_MID_5, OnBtnGoodCVMidClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_MID_6, IDC_BTN_GOOD_TRAY_CV_MID_6, OnBtnGoodCVMidClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_MID_7, IDC_BTN_GOOD_TRAY_CV_MID_7, OnBtnGoodCVMidClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_MID_8, IDC_BTN_GOOD_TRAY_CV_MID_8, OnBtnGoodCVMidClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_MID_9, IDC_BTN_GOOD_TRAY_CV_MID_9, OnBtnGoodCVMidClick)


	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_FRONT_6, IDC_BTN_GOOD_TRAY_CV_FRONT_6, OnBtnGoodCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_FRONT_7, IDC_BTN_GOOD_TRAY_CV_FRONT_7, OnBtnGoodCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_FRONT_8, IDC_BTN_GOOD_TRAY_CV_FRONT_8, OnBtnGoodCVFrontClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_TRAY_CV_FRONT_9, IDC_BTN_GOOD_TRAY_CV_FRONT_9, OnBtnGoodCVFrontClick)

	ON_BN_CLICKED(IDC_BUTTON2, &CManualElevator2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON17, &CManualElevator2Dlg::OnBnClickedButton17)
END_MESSAGE_MAP()


// CManualElevator2Dlg 메시지 처리기입니다.

BOOL CManualElevator2Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CManualElevator2Dlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CManualElevator2Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualElevator2Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		Display_Status();
	}
}
///////////////////////////////////////////////////////////////////////////////
void CManualElevator2Dlg::OnBtnGoodCVRearClick(UINT nID)	// IDC_BTN_GOOD_TRAY_CV_REAR
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();
	
	if (nID == IDC_BTN_GOOD_TRAY_CV_REAR_0) {				// CV REAR -> MID
	   pCommon->Move_Position(AX_GOOD_TRAY_UNLOAD_CV_R, 0);
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_REAR_1) {		// CV MID -> FRONT
	   pCommon->Move_Position(AX_GOOD_TRAY_UNLOAD_CV_R, 1);
	   pCommon->Move_Position(AX_GOOD_TRAY_UNLOAD_CV_F, 0);
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_REAR_2) {	    // Stage Up
		pDY5->oGoodCVRearStageUp   = TRUE;
		pDY5->oGoodCVRearStageDown = FALSE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_REAR_3){       //  Stage Down
		pDY5->oGoodCVRearStageUp   = FALSE;
		pDY5->oGoodCVRearStageDown = TRUE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_REAR_4){      // Master Align 1,2 IN
		pDY5->oGoodCVRearAlignM12In = TRUE;
		pDY5->oGoodCVRearAlignM12Out = FALSE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_REAR_5){      // Align 1,2 OUT
		pDY5->oGoodCVRearAlignM12In  = FALSE;
		pDY5->oGoodCVRearAlignM12Out = TRUE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_REAR_6){      // Align 1,2 OUT
		pDY5->oGoodCVRearAlignS12In  = TRUE;
		pDY5->oGoodCVRearAlignS12Out = FALSE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_REAR_7){      // Align 1,2 OUT
		pDY5->oGoodCVRearAlignS12In  = FALSE;
		pDY5->oGoodCVRearAlignS12Out = TRUE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_REAR_8){      // Align 1,2 OUT
		pDY5->oGoodCVRearAlign12Up  = TRUE ;
		pDY5->oGoodCVRearAlign12Down = FALSE ;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_REAR_9){      // Align 1,2 OUT
		pDY5->oGoodCVRearAlign12Up  = FALSE;
		pDY5->oGoodCVRearAlign12Down = TRUE;
	}
	
	pAJinAXL->Write_Output(5);
}

void CManualElevator2Dlg::OnBtnGoodCVMidClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();
	
	if (nID == IDC_BTN_GD_TRAY_CV_MID_0) {				 // Stage Up
		pDY5->oGoodCVMIDStageUp   = TRUE;
		pDY5->oGoodCVMIDStageDown = FALSE;
	} else if (nID == IDC_BTN_GD_TRAY_CV_MID_1) {		 // Stage Down
		pDY5->oGoodCVMIDStageUp   = FALSE;
		pDY5->oGoodCVMIDStageDown = TRUE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_MID_2) {	     // Stopper Up
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_MID_3){          // Stopper Down
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_MID_4){          // Align 1,2 IN
		pDY5->oGoodCVMIDAlignM12In  = TRUE;
		pDY5->oGoodCVMIDAlignM12Out = FALSE;	
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_MID_5){          // Align 1,2 OUT
		pDY5->oGoodCVMIDAlignM12In  = FALSE;
		pDY5->oGoodCVMIDAlignM12Out = TRUE;	
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_MID_6){          // Align 1,2 OUT
		pDY5->oGoodCVMIDAlignS12In  = TRUE;
		pDY5->oGoodCVMIDAlignS12Out = FALSE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_MID_7){          // Align 1,2 OUT
		pDY5->oGoodCVMIDAlignS12In  = FALSE;
		pDY5->oGoodCVMIDAlignS12Out = TRUE;	
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_MID_8){          // Align 1,2 OUT
		pDY5->oGoodCVMIDAlign12Up   = TRUE;
		pDY5->oGoodCVMIDAlign12Down = FALSE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_MID_9){          // Align 1,2 OUT
		pDY5->oGoodCVMIDAlign12Up  = FALSE;
		pDY5->oGoodCVMIDAlign12Down = TRUE;	
	}

	
	pAJinAXL->Write_Output(5);

}
void CManualElevator2Dlg::OnBtnGoodCVFrontClick(UINT nID)	
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();

	if (nID == IDC_BTN_GOOD_TRAY_CV_FRONT_0) {				// Align 1,2 IN
		pDY5->oGoodCVFrontAlignM12In = TRUE;
		pDY5->oGoodCVFrontAlignM12Out = FALSE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_FRONT_1) {		// Align 1,2 OUT
		pDY5->oGoodCVFrontAlignM12In = FALSE;
		pDY5->oGoodCVFrontAlignM12Out = TRUE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_FRONT_2){	    // CV CW 
	   pCommon->Move_Position(AX_GOOD_TRAY_UNLOAD_CV_F, 0);
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_FRONT_3){       // CV CCW 
	   //
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_FRONT_4){       // Tray Support IN
		pDY5->oGoodCVFrontTray12In = FALSE;
		pDY5->oGoodCVFrontTray12Out = TRUE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_FRONT_5){      // Tray Support OUT
		pDY5->oGoodCVFrontTray12In = TRUE;
		pDY5->oGoodCVFrontTray12Out = FALSE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_FRONT_6){      // Tray Support OUT
		pDY5->oGoodCVFrontDAlignS12In  = TRUE;
		pDY5->oGoodCVFrontDAlignS12Out = FALSE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_FRONT_7){      // Tray Support OUT
		pDY5->oGoodCVFrontDAlignS12In  = FALSE;
		pDY5->oGoodCVFrontDAlignS12Out = TRUE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_FRONT_8){
		pDY5->oGoodCVFrontAlignUp  = TRUE;
		pDY5->oGoodCVFrontAlignDown = FALSE;
	} else if (nID == IDC_BTN_GOOD_TRAY_CV_FRONT_9){
		pDY5->oGoodCVFrontAlignUp  = FALSE;
		pDY5->oGoodCVFrontAlignDown = TRUE;
	}

	pAJinAXL->Write_Output(5);

}
void CManualElevator2Dlg::OnBtnGoodElevZClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	if (!pAJinAXL->Is_Home(AX_GOOD_TRAY_ELEV_Z)) return;

	if (nID == IDC_BTN_GOOD_TRAY_ELEV_Z_0) {				// Down pos
		pCommon->Move_Position(AX_GOOD_TRAY_ELEV_Z, 0);
	} else if (nID == IDC_BTN_GOOD_TRAY_ELEV_Z_1) {		    // Align up
		pCommon->Move_Position(AX_GOOD_TRAY_ELEV_Z, 1);
	} else if (nID == IDC_BTN_GOOD_TRAY_ELEV_Z_2){	        // Tray Up
		pCommon->Move_Position(AX_GOOD_TRAY_ELEV_Z, 2);    
	} else if (nID == IDC_BTN_GOOD_TRAY_ELEV_Z_3){	        // Support Up 
		pCommon->Move_Position(AX_GOOD_TRAY_ELEV_Z, 3);    
	}
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CManualElevator2Dlg::Initial_Controls() 
{
	//for (int i = 0; i < 6; i++) m_btnGoodCVRear[i].Init_Ctrl("바탕", 11, TRUE, NULL, NULL, 0, 0);
	//for (int i = 0; i < 6; i++) m_btnGoodCVMid[i].Init_Ctrl("바탕", 11, TRUE, NULL, NULL, 0, 0);
	//for (int i = 0; i < 6; i++) m_btnGoodCVFront[i].Init_Ctrl("바탕", 10, TRUE, NULL, NULL, 0, 0);
	//for (int i = 0; i < 4; i++) m_btnGoodElevZ[i].Init_Ctrl("바탕", 11, TRUE, NULL, NULL, 0, 0);

	for (int i = 0; i < 16; i++) m_ledGoodCVRearIO[i].Init_Ctrl("바탕", 11, FALSE, NULL, NULL, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 18; i++) m_ledGoodCVMidIO[i].Init_Ctrl("바탕", 11, FALSE, NULL, NULL, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 17; i++) m_ledGoodCVFrontIO[i].Init_Ctrl("바탕", 9, FALSE, NULL, NULL, CLedCS::emGreen, CLedCS::em16);

}

void CManualElevator2Dlg::Display_Status()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_6 *pDX6 = pAJinAXL->Get_pDX6();
	
	CString strPos, strText;
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(AX_GOOD_TRAY_ELEV_Z);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[0].SetWindowText(strPos);

	//Good Unload C/V Rear Axis
	if (pDX6->iGoodCVRearTrayCheck) m_ledGoodCVRearIO[0].Set_On(TRUE);
	else m_ledGoodCVRearIO[0].Set_On(FALSE);

	if (pDX6->iGoodCVRearStageTrayChk) m_ledGoodCVRearIO[1].Set_On(TRUE);
	else m_ledGoodCVRearIO[1].Set_On(FALSE);

	if (pDX6->iGoodCVRearStageUp) m_ledGoodCVRearIO[2].Set_On(TRUE);
	else m_ledGoodCVRearIO[2].Set_On(FALSE);

	if (pDX6->iGoodCVRearStageDown) m_ledGoodCVRearIO[3].Set_On(TRUE);
	else m_ledGoodCVRearIO[3].Set_On(FALSE);

	if (pDX6->iGoodCVRearAlign1MIn) m_ledGoodCVRearIO[4].Set_On(TRUE);
	else m_ledGoodCVRearIO[4].Set_On(FALSE);

	if (pDX6->iGoodCVRearAlign2MIn) m_ledGoodCVRearIO[5].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[5].Set_On(FALSE);
	
	if (pDX6->iGoodCVRearAlign1MOut) m_ledGoodCVRearIO[6].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[6].Set_On(FALSE);
	
	if (pDX6->iGoodCVRearAlign2MOut) m_ledGoodCVRearIO[7].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[7].Set_On(FALSE);

	if (pDX6->iGoodCVRearAlign1SIn) m_ledGoodCVRearIO[8].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[8].Set_On(FALSE);
	if (pDX6->iGoodCVRearAlign2SIn) m_ledGoodCVRearIO[9].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[9].Set_On(FALSE);

	if (pDX6->iGoodCVRearAlign1SOut) m_ledGoodCVRearIO[10].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[10].Set_On(FALSE);
	if (pDX6->iGoodCVRearAlign2SOut) m_ledGoodCVRearIO[11].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[11].Set_On(FALSE);

	if (pDX6->iGoodCVRearAlign1Up) m_ledGoodCVRearIO[12].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[12].Set_On(FALSE);
	if (pDX6->iGoodCVRearAlign2Up) m_ledGoodCVRearIO[13].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[13].Set_On(FALSE);

	if (pDX6->iGoodCVRearAlign1Down) m_ledGoodCVRearIO[14].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[14].Set_On(FALSE);
	if (pDX6->iGoodCVRearAlign2Down) m_ledGoodCVRearIO[15].Set_On(TRUE);  //TRUE
	else m_ledGoodCVRearIO[15].Set_On(FALSE);


	//Good Middle C/V
	if (pDX6->iGoodCVMIDTrayCheck) m_ledGoodCVMidIO[0].Set_On(TRUE);
	else m_ledGoodCVMidIO[0].Set_On(FALSE);

	if (pDX6->iGoodCVMIDStageTrayChk) m_ledGoodCVMidIO[1].Set_On(TRUE);
	else m_ledGoodCVMidIO[1].Set_On(FALSE);

	if (pDX6->iGoodCVMIDStageUp) m_ledGoodCVMidIO[2].Set_On(TRUE);
	else m_ledGoodCVMidIO[2].Set_On(FALSE);

	if (pDX6->iGoodCVMIDStageDown) m_ledGoodCVMidIO[3].Set_On(TRUE);
	else m_ledGoodCVMidIO[3].Set_On(FALSE);

	if (pDX6->iGoodCVMIDAlign1MIn) m_ledGoodCVMidIO[6].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[6].Set_On(FALSE);
	if (pDX6->iGoodCVMIDAlign2MIn) m_ledGoodCVMidIO[7].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[7].Set_On(FALSE);

	if (pDX6->iGoodCVMIDAlign1MOut) m_ledGoodCVMidIO[8].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[8].Set_On(FALSE);
	if (pDX6->iGoodCVMIDAlign2MOut) m_ledGoodCVMidIO[9].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[9].Set_On(FALSE);

	if (pDX6->iGoodCVMIDAlign1SIn) m_ledGoodCVMidIO[10].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[10].Set_On(FALSE);
	if (pDX6->iGoodCVMIDAlign2SIn) m_ledGoodCVMidIO[11].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[11].Set_On(FALSE);

	if (pDX6->iGoodCVMIDAlign1SOut) m_ledGoodCVMidIO[12].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[12].Set_On(FALSE);
	if (pDX6->iGoodCVMIDAlign2SOut) m_ledGoodCVMidIO[13].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[13].Set_On(FALSE);

	if (pDX6->iGoodCVMIDAlign1Up) m_ledGoodCVMidIO[14].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[14].Set_On(FALSE);
	if (pDX6->iGoodCVMIDAlign1Down) m_ledGoodCVMidIO[16].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[16].Set_On(FALSE);

	if (pDX6->iGoodCVMIDTrayCheck2) m_ledGoodCVMidIO[15].Set_On(TRUE);  //TRUE
	else m_ledGoodCVMidIO[15].Set_On(FALSE);
//	if (pDX6->iGoodCVMIDAlign2Down) m_ledGoodCVMidIO[17].Set_On(TRUE);  //TRUE
//	else m_ledGoodCVMidIO[17].Set_On(FALSE);

	//Good Unload C/V Front Axis
	if (pDX6->iGoodCVFrontTrayCheck) m_ledGoodCVFrontIO[0].Set_On(TRUE);
	else m_ledGoodCVFrontIO[0].Set_On(FALSE);

	if (pDX6->iGoodCVFrontStageTrayChk) m_ledGoodCVFrontIO[1].Set_On(TRUE);
	else m_ledGoodCVFrontIO[1].Set_On(FALSE);

	if (pDX6->iGoodCVFrontAlign1MIn) m_ledGoodCVFrontIO[2].Set_On(TRUE);
	else m_ledGoodCVFrontIO[2].Set_On(FALSE);

	if (pDX6->iGoodCVFrontAlign2MIn) m_ledGoodCVFrontIO[3].Set_On(TRUE);
	else m_ledGoodCVFrontIO[3].Set_On(FALSE);

	if (pDX6->iGoodCVFrontTray1In) m_ledGoodCVFrontIO[4].Set_On(TRUE);
	else m_ledGoodCVFrontIO[4].Set_On(FALSE);

	if (pDX6->iGoodCVFrontTray2In) m_ledGoodCVFrontIO[5].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[5].Set_On(FALSE);

	if (pDX6->iGoodCVFrontTray1FCheck) m_ledGoodCVFrontIO[6].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[6].Set_On(FALSE);

	if (pDX6->iGoodCVFrontAlign1MOut) m_ledGoodCVFrontIO[7].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[7].Set_On(FALSE);
	if (pDX6->iGoodCVFrontAlign2MOut) m_ledGoodCVFrontIO[8].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[8].Set_On(FALSE);

	if (pDX6->iGoodCVFrontAlign1SIn) m_ledGoodCVFrontIO[9].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[9].Set_On(FALSE);
	if (pDX6->iGoodCVFrontAlign1SOut) m_ledGoodCVFrontIO[11].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[11].Set_On(FALSE);

	if (pDX6->iGoodCVFrontTrayCheck2) m_ledGoodCVFrontIO[10].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[10].Set_On(FALSE);
//	if (pDX6->iGoodCVFrontAlign2SOut) m_ledGoodCVFrontIO[12].Set_On(TRUE);  //TRUE
//	else m_ledGoodCVFrontIO[12].Set_On(FALSE);

	if (pDX6->iGoodCVFrontTray1Out) m_ledGoodCVFrontIO[13].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[13].Set_On(FALSE);
	if (pDX6->iGoodCVFrontTray2Out) m_ledGoodCVFrontIO[14].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[14].Set_On(FALSE);

	if (pDX6->iGoodCVFrontAlignUp) m_ledGoodCVFrontIO[15].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[15].Set_On(FALSE);
	if (pDX6->iGoodCVFrontAlignDown) m_ledGoodCVFrontIO[16].Set_On(TRUE);  //TRUE
	else m_ledGoodCVFrontIO[16].Set_On(FALSE);


}

///////////////////////////////////////////////////////////////////////////////


void CManualElevator2Dlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();

	pDY5->oGoodCVRearAlignM12In = TRUE;
	pDY5->oGoodCVRearAlignM12Out = FALSE;
	pAJinAXL->Write_Output(5);

	Sleep(400);

	pDY5->oGoodCVRearAlignS12In  = TRUE;
	pDY5->oGoodCVRearAlignS12Out = FALSE;
	pAJinAXL->Write_Output(5);

}


void CManualElevator2Dlg::OnBnClickedButton17()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();
	
	pDY5->oGoodCVRearAlignS12In  = FALSE;
	pDY5->oGoodCVRearAlignS12Out = TRUE;
	pAJinAXL->Write_Output(5);

	Sleep(400);

	pDY5->oGoodCVRearAlignM12In = FALSE;
	pDY5->oGoodCVRearAlignM12Out = TRUE;
	pAJinAXL->Write_Output(5);
}
