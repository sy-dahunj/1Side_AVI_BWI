// ManualGripper2Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CMI4200L.h"
#include "ManualGripper2Dlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

#include "ManualDlg.h"
#include "LaserManager.h"
#include "ElectManager.h"


// CManualGripper2Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualGripper2Dlg, CDialogEx)

CManualGripper2Dlg::CManualGripper2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualGripper2Dlg::IDD, pParent)
{

}

CManualGripper2Dlg::~CManualGripper2Dlg()
{
}

void CManualGripper2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_BTN_GRIP1_Y_0 + i, m_btnGrip1Y[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_GRIP2_Y_0 + i, m_btnGrip2Y[i]);
	DDX_Control(pDX, IDC_BTN_GRIP_RAIL_W, m_btnGripRailW);
	DDX_Control(pDX, IDC_BTN_LASER_X, m_btnLaserX);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_GRIP1_IO_0 + i, m_btnGrip1Io[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_GRIP1_IO_0 + i, m_ledGrip1Io[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_GRIP2_IO_0 + i, m_btnGrip2Io[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_LED_GRIP2_IO_0 + i, m_ledGrip2Io[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_CHK_GRIP_IO_0 + i, m_chkGripIo[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_GRIP_RAIL_IO_0 + i, m_btnGripRailIo[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_LED_GRIP_RAIL_IO_0 + i, m_ledGripRailIo[i]);
	DDX_Control(pDX, IDC_STC_LASER_VALUE, m_stcLaserValue);
	DDX_Control(pDX, IDC_BTN_LASER_READ, m_btnLaserRead);
	DDX_Control(pDX, IDC_STC_ELECT_VALUE, m_stcElectValue);
	DDX_Control(pDX, IDC_BTN_ELECT_READ, m_btnElectRead);


	//for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_NG_TRAY_UNLOAD_Y_0 + i, m_btnNGTrayUnloadY[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_NG_BARCODE_Y_0 + i, m_btnUnloadNGBarcodeX[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_NG_BARCODE_X_0 + i, m_btnUnloadNGBarcodeY[i]);

	//DDX_Control(pDX, IDC_BTN_NG_TRAY_UNLOAD_Y_0 , m_btnNGTrayUnloadY[0]);
	DDX_Control(pDX, IDC_BTN_NG_TRAY_UNLOAD_Y_1 , m_btnNGTrayUnloadY[1]);
	DDX_Control(pDX, IDC_BTN_NG_TRAY_UNLOAD_Y_2 , m_btnNGTrayUnloadY[2]);
	//DDX_Control(pDX, IDC_BTN_NG_TRAY_UNLOAD_Y_4 , m_btnNGTrayUnloadY[3]);
	DDX_Control(pDX, IDC_BTN_NG_TRAY_UNLOAD_Y_5 , m_btnNGTrayUnloadY[3]);

	DDX_Control(pDX, IDC_STC_BARCODE_VALUE, m_stcBarcodeRead);
	DDX_Control(pDX, IDC_BTN_BARCODE_READ_V , m_btnBarcodeRead);
	
	DDX_Control(pDX, IDC_BTN_UNLOAD_NG_BARCODE_Y_3 , m_btnUnloadNGBarcodeY[4]);

}


BEGIN_MESSAGE_MAP(CManualGripper2Dlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_TRAY_UNLOAD_Y_1, IDC_BTN_NG_TRAY_UNLOAD_Y_2, OnBtnNGTrayYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_NG_BARCODE_X_0, IDC_BTN_UNLOAD_NG_BARCODE_X_2, OnBtnNGBarcodeXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_NG_BARCODE_Y_0, IDC_BTN_UNLOAD_NG_BARCODE_Y_2, OnBtnNGBarcodeYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_TRAY_UNLOAD_Y_5, IDC_BTN_NG_TRAY_UNLOAD_Y_5, OnBtnNGTrayYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_BARCODE_READ_V, IDC_BTN_BARCODE_READ_V, OnBtnBarcodeReadClick)



END_MESSAGE_MAP()


// CManualGripper2Dlg 메시지 처리기입니다.

BOOL CManualGripper2Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CManualGripper2Dlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CManualGripper2Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualGripper2Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		Display_Status();
	}
}


void CManualGripper2Dlg::OnBtnNGTrayYClick(UINT nID)	
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	if (!pAJinAXL->Is_Home(AX_NG_TRAY_UNLOAD_Y)) return;

	if (nID == IDC_BTN_NG_TRAY_UNLOAD_Y_0) {				     // Ready
		pCommon->Move_Position(AX_NG_TRAY_UNLOAD_Y, 0);
	} else if (nID == IDC_BTN_NG_TRAY_UNLOAD_Y_1) {		         // Loading 1
		pCommon->Move_Position(AX_NG_TRAY_UNLOAD_Y, 1);
	} else if (nID == IDC_BTN_NG_TRAY_UNLOAD_Y_2){	             // Unloading
		pCommon->Move_Position(AX_NG_TRAY_UNLOAD_Y, 2);    
	} else if (nID == IDC_BTN_NG_TRAY_UNLOAD_Y_5){	             // Loading 2
		pCommon->Move_Position(AX_NG_TRAY_UNLOAD_Y, 3);    
	}

}
void CManualGripper2Dlg::OnBtnNGBarcodeXClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	//if (!pAJinAXL->Is_Home(AX_BARCODE_X)) return;

	if (nID == IDC_BTN_UNLOAD_NG_BARCODE_X_0) {				// Ready
		pCommon->Move_Position(AX_BARCODE_X, 0);
	} else if (nID == IDC_BTN_UNLOAD_NG_BARCODE_X_1) {		    // Reading First Pos
		pCommon->Move_Position(AX_BARCODE_X, 1);
	} else if (nID == IDC_BTN_UNLOAD_NG_BARCODE_X_2){	        // Pitch 
		pCommon->Move_Position(AX_BARCODE_X, 2);    
	} 

}
void CManualGripper2Dlg::OnBtnNGBarcodeYClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	//if (!pAJinAXL->Is_Home(AX_BARCODE_Y)) return;

	if (nID == IDC_BTN_UNLOAD_NG_BARCODE_Y_0) {				// Ready
		pCommon->Move_Position(AX_BARCODE_Y, 0);
	} else if (nID == IDC_BTN_UNLOAD_NG_BARCODE_Y_1) {		    // Reading First Pos
		pCommon->Move_Position(AX_BARCODE_Y, 1);
	} else if (nID == IDC_BTN_UNLOAD_NG_BARCODE_Y_2){	        // Pitch
		pCommon->Move_Position(AX_BARCODE_Y, 2);    
	} 
}

 void CManualGripper2Dlg::OnBtnBarcodeReadClick(UINT nID)
 {
 //
 }




///////////////////////////////////////////////////////////////////////////////
// User Functions

void CManualGripper2Dlg::Initial_Controls() 
{
	for (int i = 0; i < 4; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x10, 0xB0), NULL);
	for (int i = 0; i < 6; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 2; i++) m_stcAxisPos[i].Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xB0));
	for (int i = 2; i < 4; i++) m_stcAxisPos[i].Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0xB0, 0x10, 0x20));

	for (int i = 1; i < 4; i++) m_btnNGTrayUnloadY[i].Init_Ctrl("바탕", 11, TRUE, NULL, NULL, 0, 0);
	for (int i = 0; i < 3; i++) m_btnUnloadNGBarcodeX[i].Init_Ctrl("바탕", 11, TRUE, NULL, NULL, 0, 0);
	for (int i = 0; i < 3; i++) m_btnUnloadNGBarcodeY[i].Init_Ctrl("바탕", 11, TRUE, NULL, NULL, 0, 0);

	m_stcBarcodeRead.Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xB0));
	m_btnBarcodeRead.Init_Ctrl("바탕", 11, TRUE, NULL, NULL, 0, 0);

}

void CManualGripper2Dlg::Display_Status()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();

	CString strPos, strText;
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(AX_NG_TRAY_UNLOAD_Y);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[0].SetWindowText(strPos);

}


///////////////////////////////////////////////////////////////////////////////
