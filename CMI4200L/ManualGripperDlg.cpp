// ManualGripperDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "ManualGripperDlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

#include "ManualDlg.h"
#include "LaserManager.h"
#include "ElectManager.h"
#include "ExtBarcode_Honeywell.h"

#include "SocketTCP.h"

// CManualGripperDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualGripperDlg, CDialogEx)

CManualGripperDlg::CManualGripperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualGripperDlg::IDD, pParent)
{
}

CManualGripperDlg::~CManualGripperDlg()
{
}

void CManualGripperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);

	DDX_Control(pDX, IDC_STC_NG_BARCODE_ID, m_stcNGBarcodeValue);
	DDX_Control(pDX, IDC_BTN_NG_BARCODE_READ, m_btnNGBarcodeRead);

	//for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_NG_TRAY_Y_0 + i, m_btnNGTrayY[i]);
	//for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_NG_BARCODE_X_0 + i, m_btnNGBarcodeX[i]);
	//for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_NG_BARCODE_Y_0 + i, m_btnNGBarcodeY[i]);
}

BEGIN_MESSAGE_MAP(CManualGripperDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()

	ON_BN_CLICKED(IDC_BTN_LASER_READ, &CManualGripperDlg::OnBnClickedBtnLaserRead)
	ON_BN_CLICKED(IDC_BTN_ELECT_READ, &CManualGripperDlg::OnBnClickedBtnElectRead)

	ON_BN_CLICKED(IDC_BTN_NG_BARCODE_READ, &CManualGripperDlg::OnBnClickedBtnNGBarcodeRead)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_TRAY_Y_0, IDC_BTN_NG_TRAY_Y_2, OnBtnNGTrayYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_BARCODE_X_0, IDC_BTN_NG_BARCODE_X_2, OnBtnNGBarcodeXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_BARCODE_Y_0, IDC_BTN_NG_BARCODE_Y_2, OnBtnNGBarcodeYClick)
END_MESSAGE_MAP()

// CManualGripperDlg 메시지 처리기입니다.

BOOL CManualGripperDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CManualGripperDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CManualGripperDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualGripperDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
		DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();
		DY_DATA_2 *pDY2 = pAJinAXL->Get_pDY2();

	}
}



void CManualGripperDlg::OnBtnNGTrayYClick(UINT nID)	
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	if (!pAJinAXL->Is_Home(AX_NG_TRAY_UNLOAD_Y)) return;

	if (nID == IDC_BTN_NG_TRAY_Y_0) {				     // Ready
		pCommon->Move_Position(AX_NG_TRAY_UNLOAD_Y, 0);
	} else if (nID == IDC_BTN_NG_TRAY_Y_1) {		     // Loading
		pCommon->Move_Position(AX_NG_TRAY_UNLOAD_Y, 1);
	} else if (nID == IDC_BTN_NG_TRAY_Y_2){	             // Unloading
		pCommon->Move_Position(AX_NG_TRAY_UNLOAD_Y, 2);    
	}

}
void CManualGripperDlg::OnBtnNGBarcodeXClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	//if (!pAJinAXL->Is_Home(AX_BARCODE_X)) return;

	if (nID == IDC_BTN_NG_BARCODE_X_0) {				// Ready
		pCommon->Move_Position(AX_BARCODE_X, 0);
	} else if (nID == IDC_BTN_NG_BARCODE_X_1) {		    // Reading First Pos
		pCommon->Move_Position(AX_BARCODE_X, 1);
	} else if (nID == IDC_BTN_NG_BARCODE_X_2){	        // Pitch 
		pCommon->Move_Position(AX_BARCODE_X, 2);    
	} 

}
void CManualGripperDlg::OnBtnNGBarcodeYClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	
	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	//if (!pAJinAXL->Is_Home(AX_BARCODE_Y)) return;

	if (nID == IDC_BTN_NG_BARCODE_Y_0) {				// Ready
		pCommon->Move_Position(AX_BARCODE_Y, 0);
	} else if (nID == IDC_BTN_NG_BARCODE_Y_1) {		    // Reading First Pos
		pCommon->Move_Position(AX_BARCODE_Y, 1);
	} else if (nID == IDC_BTN_NG_BARCODE_Y_2){	        // Pitch
		pCommon->Move_Position(AX_BARCODE_Y, 2);    
	} 
}

//////////////
void CManualGripperDlg::OnBnClickedBtnNGBarcodeRead()
{
	//barcode reading...
	CExtBarcode_Honeywell *m_pExtBarcode = CExtBarcode_Honeywell::Get_Instance();

	CString sData;
	m_pExtBarcode->GetBarcode(sData);
	if (sData.GetLength() < 1) {
		AfxMessageBox(_T("Barcode read data not found !!!"));
		return;
	}
	m_stcNGBarcodeValue.SetWindowText(sData);
}

void CManualGripperDlg::OnBnClickedBtnLaserRead()
{
	//CLaserManager *pLaserManager = CLaserManager::Get_Instance();
	//pLaserManager->Read_Laser();

	CSocketTCP *pSocketTCP = CSocketTCP::Get_Instance();

	CString strReceive;
	pSocketTCP->GetReceive(strReceive);



}

void CManualGripperDlg::OnBnClickedBtnElectRead()
{
	CElectManager *pElectManager = CElectManager::Get_Instance();
	pElectManager->Read_Elect();
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CManualGripperDlg::Initial_Controls() 
{
	for (int i = 0; i < 4; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x10, 0xB0), NULL);
	for (int i = 0; i < 3; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 3; i++) m_stcAxisPos[i].Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xB0));

	//for (int i = 0; i < 3; i++) m_btnNGTrayY[i].Init_Ctrl("바탕", 11, TRUE, NULL, NULL, 0, 0);
	//for (int i = 0; i < 3; i++) m_btnNGBarcodeX[i].Init_Ctrl("바탕", 11, TRUE, NULL, NULL, 0, 0);
	//for (int i = 0; i < 3; i++) m_btnNGBarcodeY[i].Init_Ctrl("바탕", 11, TRUE, NULL, NULL, 0, 0);
}

void CManualGripperDlg::Display_Status()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_2 *pDX2 = pAJinAXL->Get_pDX2();
	DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();

	CCommon *pCommon = CCommon::Get_Instance();

	CString strPos;
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(AX_NG_TRAY_UNLOAD_Y);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[0].SetWindowText(strPos);

	pStatus = pAJinAXL->Get_pStatus(AX_BARCODE_X);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[1].SetWindowText(strPos);

	pStatus = pAJinAXL->Get_pStatus(AX_BARCODE_Y);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[2].SetWindowText(strPos);


}

void CManualGripperDlg::Set_LaserValue(CString sLaserValue)
{
//
}

void CManualGripperDlg::Set_ElectValue(CString sElectValue)
{
//
}

///////////////////////////////////////////////////////////////////////////////


void CManualGripperDlg::OnBnClickedBtnGrip2Io1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
