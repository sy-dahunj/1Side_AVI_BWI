// ManualLoadTrayDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CMI4200L.h"
#include "ManualLoadTrayDlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "ManualDlg.h"

// CManualLoadTrayDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualLoadTrayDlg, CDialogEx)

CManualLoadTrayDlg::CManualLoadTrayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualLoadTrayDlg::IDD, pParent)
{

}

CManualLoadTrayDlg::~CManualLoadTrayDlg()
{
}

void CManualLoadTrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO_0, m_ledShuttle[0]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO_1, m_ledShuttle[1]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO_2, m_ledShuttle[2]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO_3, m_ledShuttle[3]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO_4, m_ledShuttle[4]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO_5, m_ledShuttle[5]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO2_0, m_ledShuttle2[0]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO2_1, m_ledShuttle2[1]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO2_2, m_ledShuttle2[2]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO2_3, m_ledShuttle2[3]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO2_4, m_ledShuttle2[4]);
	DDX_Control(pDX, IDC_LED_SHUTTLE_IO2_5, m_ledShuttle2[5]);
	DDX_Control(pDX, IDC_BTN_LD_TRAY_IO_0, m_btnShuttleIO[0]);
	DDX_Control(pDX, IDC_BTN_LD_TRAY_IO_1, m_btnShuttleIO[1]);
	DDX_Control(pDX, IDC_BTN_UN_TRAY_IO_0, m_btnShuttleIO2[0]);
	DDX_Control(pDX, IDC_BTN_UN_TRAY_IO_1, m_btnShuttleIO2[1]);

	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_TR1_IO_0 + i, m_btnTR1IO[i]);
	DDX_Control(pDX, IDC_BTN_TR1_IO_8, m_btnTR1IO[4]);
	DDX_Control(pDX, IDC_BTN_TR1_IO_9, m_btnTR1IO[5]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_TR2_IO_0 + i, m_btnTR2IO[i]);
	DDX_Control(pDX, IDC_BTN_TR2_IO_4, m_btnTR2IO[4]);
	DDX_Control(pDX, IDC_BTN_TR2_IO_5, m_btnTR2IO[5]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LED_TR1_IO_0 + i, m_ledTR1[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LED_TR2_IO_0 + i, m_ledTR2[i]);

	DDX_Control(pDX, IDC_BTN_TR1_Y_0, m_btnTR1Y[0]);
	DDX_Control(pDX, IDC_BTN_TR1_Y_1, m_btnTR1Y[1]);
	DDX_Control(pDX, IDC_BTN_TR1_Y_2, m_btnTR1Y[2]);
	DDX_Control(pDX, IDC_BTN_TR1_Z_0, m_btnTR1Z[0]);
	DDX_Control(pDX, IDC_BTN_TR1_Z_1, m_btnTR1Z[1]);
	DDX_Control(pDX, IDC_BTN_TR1_Z_2, m_btnTR1Z[2]);
	DDX_Control(pDX, IDC_BTN_TR1_Z_3, m_btnTR1Z[3]);

	DDX_Control(pDX, IDC_BTN_TR2_Y_0, m_btnTR2Y[0]);
	DDX_Control(pDX, IDC_BTN_TR2_Y_1, m_btnTR2Y[1]);
	DDX_Control(pDX, IDC_BTN_TR2_Y_2, m_btnTR2Y[2]);
	DDX_Control(pDX, IDC_BTN_TR2_Z_0, m_btnTR2Z[0]);
	DDX_Control(pDX, IDC_BTN_TR2_Z_1, m_btnTR2Z[1]);
	DDX_Control(pDX, IDC_BTN_TR2_Z_2, m_btnTR2Z[2]);
	DDX_Control(pDX, IDC_BTN_TR2_Z_3, m_btnTR2Z[3]);

}


BEGIN_MESSAGE_MAP(CManualLoadTrayDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LD_TRAY_IO_0, IDC_BTN_LD_TRAY_IO_0, OnBtnShuttleIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LD_TRAY_IO_1, IDC_BTN_LD_TRAY_IO_1, OnBtnShuttleIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UN_TRAY_IO_0, IDC_BTN_UN_TRAY_IO_0, OnBtnShuttleIO2Click)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UN_TRAY_IO_1, IDC_BTN_UN_TRAY_IO_1, OnBtnShuttleIO2Click)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR1_Y_0, IDC_BTN_TR1_Y_0, OnBtnTR1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR1_Y_1, IDC_BTN_TR1_Y_1, OnBtnTR1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR1_Y_2, IDC_BTN_TR1_Y_2, OnBtnTR1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR1_Z_0, IDC_BTN_TR1_Z_0, OnBtnTR1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR1_Z_1, IDC_BTN_TR1_Z_1, OnBtnTR1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR1_Z_2, IDC_BTN_TR1_Z_2, OnBtnTR1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR1_Z_3, IDC_BTN_TR1_Z_3, OnBtnTR1ZClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR2_Y_0, IDC_BTN_TR2_Y_0, OnBtnTR2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR2_Y_1, IDC_BTN_TR2_Y_1, OnBtnTR2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR2_Y_2, IDC_BTN_TR2_Y_2, OnBtnTR2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR2_Z_0, IDC_BTN_TR2_Z_0, OnBtnTR2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR2_Z_1, IDC_BTN_TR2_Z_1, OnBtnTR2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR2_Z_2, IDC_BTN_TR2_Z_2, OnBtnTR2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR2_Z_3, IDC_BTN_TR2_Z_3, OnBtnTR2ZClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR1_IO_0, IDC_BTN_TR1_IO_3, OnBtnTR1IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR1_IO_8, IDC_BTN_TR1_IO_8, OnBtnTR1IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR1_IO_9, IDC_BTN_TR1_IO_9, OnBtnTR1IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR2_IO_0, IDC_BTN_TR2_IO_3, OnBtnTR2IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR2_IO_4, IDC_BTN_TR2_IO_4, OnBtnTR2IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR2_IO_5, IDC_BTN_TR2_IO_5, OnBtnTR2IOClick)
END_MESSAGE_MAP()

// CManualLoadTrayDlg 메시지 처리기입니다.
BOOL CManualLoadTrayDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CManualLoadTrayDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CManualLoadTrayDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualLoadTrayDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		Display_Status();
	}
}

void CManualLoadTrayDlg::Initial_Controls() 
{
	for (int i = 0; i < 4; i++) m_stcAxisPos[i].Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xB0));
	for (int i = 0; i < 6; i++) m_ledShuttle[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 6; i++) m_ledShuttle2[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 6; i++) m_ledTR1[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 6; i++) m_ledTR2[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
}

void CManualLoadTrayDlg::Display_Status()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();

	CString strPos;
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(AX_LOAD_TRAY_X1);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[0].SetWindowText(strPos);

	pStatus = pAJinAXL->Get_pStatus(AX_LOAD_TRAY_X2);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[1].SetWindowText(strPos);

	pStatus = pAJinAXL->Get_pStatus(AX_LOAD_TRAY_Z1);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[2].SetWindowText(strPos);

	pStatus = pAJinAXL->Get_pStatus(AX_LOAD_TRAY_Z2);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[3].SetWindowText(strPos);

	if (pDX1->iLS_Z1AlignM34In) m_ledTR1[0].Set_On(TRUE);
	else m_ledTR1[0].Set_On(FALSE);
	if (pDX1->iLS_Z1AlignS12In) m_ledTR1[1].Set_On(TRUE);
	else m_ledTR1[1].Set_On(FALSE);
	if (pDX1->iLS_Z1AlignM34Out) m_ledTR1[2].Set_On(TRUE);
	else m_ledTR1[2].Set_On(FALSE);
	if (pDX1->iLS_Z1AlignS12Out) m_ledTR1[3].Set_On(TRUE);
	else m_ledTR1[3].Set_On(FALSE);
	if (pDX1->iLS_Z1Check1) m_ledTR1[4].Set_On(TRUE);
	else m_ledTR1[4].Set_On(FALSE);
	if (pDX1->iLS_Z1Check2) m_ledTR1[5].Set_On(TRUE);
	else m_ledTR1[5].Set_On(FALSE);

	if (pDX1->iLS_Z2AlignM34In) m_ledTR2[0].Set_On(TRUE);
	else m_ledTR2[0].Set_On(FALSE);
	if (pDX1->iLS_Z2AlignS12In) m_ledTR2[1].Set_On(TRUE);
	else m_ledTR2[1].Set_On(FALSE);
	if (pDX1->iLS_Z2AlignM34Out) m_ledTR2[2].Set_On(TRUE);
	else m_ledTR2[2].Set_On(FALSE);
	if (pDX1->iLS_Z2AlignS12Out) m_ledTR2[3].Set_On(TRUE);
	else m_ledTR2[3].Set_On(FALSE);
	if (pDX1->iLS_Z2Check1) m_ledTR2[4].Set_On(TRUE);
	else m_ledTR2[4].Set_On(FALSE);
	if (pDX1->iLS_Z2Check2) m_ledTR2[5].Set_On(TRUE);
	else m_ledTR2[5].Set_On(FALSE);

	if (pDX1->iLS_LoadSupport1In) m_ledShuttle[0].Set_On(TRUE);
	else m_ledShuttle[0].Set_On(FALSE);
	if (pDX1->iLS_LoadSupport2In) m_ledShuttle[1].Set_On(TRUE);
	else m_ledShuttle[1].Set_On(FALSE);
	if (pDX1->iLS_LoadSupport1Out) m_ledShuttle[2].Set_On(TRUE);
	else m_ledShuttle[2].Set_On(FALSE);
	if (pDX1->iLS_LoadSupport2Out) m_ledShuttle[3].Set_On(TRUE);
	else m_ledShuttle[3].Set_On(FALSE);
	if (pDX1->iLS_Load1FCheck) m_ledShuttle[4].Set_On(TRUE);
	else m_ledShuttle[4].Set_On(FALSE);
	if (pDX1->iLS_LoadFullCheck) m_ledShuttle[5].Set_On(TRUE);
	else m_ledShuttle[5].Set_On(FALSE);

	if (pDX1->iLS_UnloadSupport1In) m_ledShuttle2[0].Set_On(TRUE);
	else m_ledShuttle2[0].Set_On(FALSE);
	if (pDX1->iLS_UnloadSupport2In) m_ledShuttle2[1].Set_On(TRUE);
	else m_ledShuttle2[1].Set_On(FALSE);
	if (pDX1->iLS_UnloadSupport1Out) m_ledShuttle2[2].Set_On(TRUE);
	else m_ledShuttle2[2].Set_On(FALSE);
	if (pDX1->iLS_UnloadSupport2Out) m_ledShuttle2[3].Set_On(TRUE);
	else m_ledShuttle2[3].Set_On(FALSE);
	if (pDX1->iLS_Unload1FCheck) m_ledShuttle2[4].Set_On(TRUE);
	else m_ledShuttle2[4].Set_On(FALSE);
	if (pDX1->iLS_UnloadFullCheck) m_ledShuttle2[5].Set_On(TRUE);
	else m_ledShuttle2[5].Set_On(FALSE);

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
	BOOL bShow = FALSE;

	if (pEquipData->bUseManagerMode) bShow = TRUE;
	for(int i=0; i<3; i++) {
		m_btnTR1Y[i].ShowWindow(bShow);
		m_btnTR2Y[i].ShowWindow(bShow);
	}
	for(int i=0; i<4; i++) {
		m_btnTR1Z[i].ShowWindow(bShow);
		m_btnTR2Z[i].ShowWindow(bShow);
	}
}


void CManualLoadTrayDlg::OnBtnShuttleIOClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	pManualDlg->MainDoor_Lock();

	if (nID == IDC_BTN_LD_TRAY_IO_0) {
		pDY1->oLS_LoadSupport12In = TRUE;
		pDY1->oLS_LoadSupport12Out = FALSE;
	} else if (nID == IDC_BTN_LD_TRAY_IO_1) {
		pDY1->oLS_LoadSupport12In = FALSE;
		pDY1->oLS_LoadSupport12Out = TRUE;
	}
	pAJinAXL->Write_Output(1);
}

void CManualLoadTrayDlg::OnBtnShuttleIO2Click(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	pManualDlg->MainDoor_Lock();

	if (nID == IDC_BTN_UN_TRAY_IO_0) {
		pDY1->oLS_UnloadSupport12In = TRUE;
		pDY1->oLS_UnloadSupport12Out = FALSE;
	} else if (nID == IDC_BTN_UN_TRAY_IO_1) {
		pDY1->oLS_UnloadSupport12In = FALSE;
		pDY1->oLS_UnloadSupport12Out = TRUE;
	}
	pAJinAXL->Write_Output(1);
}
void CManualLoadTrayDlg::OnBtnTR1YClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();
	CCommon *pCommon = CCommon::Get_Instance();

	if (!pAJinAXL->Is_Home(AX_LOAD_TRAY_X1)) return;
	if (!pCommon->Check_MainDoor()) return;

	if(!(pCommon->Check_Position(AX_LOAD_PICKER_Z, 0))) {
		AfxMessageBox(_T("Load Picker Z Axis Ready Position 이동후 진행하세요. ...."));
		return;
	}

	if(!pDX1->iLS_Z1AlignS12In || pDX1->iLS_Z1AlignS12Out || !pDX1->iLS_Z1AlignM34In || pDX1->iLS_Z1AlignM34Out)
	{
		AfxMessageBox(_T("Tray Aliner Master/Slave In 후 진행하세요. ...."));
		return;
	}

	if((pCommon->Check_Position(AX_LOAD_TRAY_Z1, 0) && pCommon->Check_Position(AX_LOAD_TRAY_Z2, 1)) ||
	   (pCommon->Check_Position(AX_LOAD_TRAY_Z1, 1) && pCommon->Check_Position(AX_LOAD_TRAY_Z2, 0)) ) {
		if (nID == IDC_BTN_TR1_Y_0) {
			pCommon->Move_Position(AX_LOAD_TRAY_X1, 0);
		} else if (nID == IDC_BTN_TR1_Y_1) {
			pCommon->Move_Position(AX_LOAD_TRAY_X1, 2);
		} else if (nID == IDC_BTN_TR1_Y_2) {
			pCommon->Move_Position(AX_LOAD_TRAY_X1, 3);
		}
	} else {
		AfxMessageBox(_T("Load Tray 1 Z1 - Z2 Axis Position Error...."));
		return;
	}
}

void CManualLoadTrayDlg::OnBtnTR1ZClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();
	CCommon *pCommon = CCommon::Get_Instance();

	if (!pAJinAXL->Is_Home(AX_LOAD_TRAY_Z1)) return;
	if (!pCommon->Check_MainDoor()) return;

	if((pCommon->Check_Position(AX_LOAD_TRAY_X1, 0) && pCommon->Check_Position(AX_LOAD_TRAY_X2, 0)) ||
	   (pCommon->Check_Position(AX_LOAD_TRAY_X1, 2) && pCommon->Check_Position(AX_LOAD_TRAY_X2, 2)) ||
	   (pCommon->Check_Position(AX_LOAD_TRAY_X1, 3) && pCommon->Check_Position(AX_LOAD_TRAY_X2, 3)) ) {
		AfxMessageBox(_T("Load Tray X1_X2 Axis Position Error...."));
		return;
	}

	if (nID == IDC_BTN_TR1_Z_0) {
		pCommon->Move_Position(AX_LOAD_TRAY_Z1, 0);
	} else if (nID == IDC_BTN_TR1_Z_1) {
		pCommon->Move_Position(AX_LOAD_TRAY_Z1, 1);
	} else if (nID == IDC_BTN_TR1_Z_2) {
		if (pDX1->iLS_Z1Check1 && pCommon->Check_Position(AX_LOAD_TRAY_X1, 0) && pDX1->iLS_LoadSupport1In) {
			AfxMessageBox(_T("Can not Move (Load Tray 1 = Tray Exist and Load Support = In)"));
			return;
		}
		if (pDX1->iLS_Z1Check1 && pCommon->Check_Position(AX_LOAD_TRAY_X1, 3) && pDX1->iLS_UnloadSupport1In) {
			AfxMessageBox(_T("Can not Move (Load Tray 1 = Tray Exist and Unload Support = In)"));
			return;
		}

		if (pCommon->Check_Position(AX_LOAD_TRAY_X1, 0) || pCommon->Check_Position(AX_LOAD_TRAY_X1, 3)) {
			pCommon->Move_Position(AX_LOAD_TRAY_Z1, 2);
		} else {
			AfxMessageBox(_T("Load Tray 1 X Axis Position Error...."));
			return;
		}
	} else if (nID == IDC_BTN_TR1_Z_3) {
		if (pCommon->Check_Position(AX_LOAD_TRAY_X1, 0) || pCommon->Check_Position(AX_LOAD_TRAY_X1, 3)) {
			pCommon->Move_Position(AX_LOAD_TRAY_Z1, 3);
		} else {
			AfxMessageBox(_T("Load Tray 1 X Axis Position Error...."));
			return;
		}
	}
}

void CManualLoadTrayDlg::OnBtnTR1IOClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	pManualDlg->MainDoor_Lock();

	if (nID == IDC_BTN_TR1_IO_0) {
//		if (!pCommon->Check_Position(AX_LOAD_TRAY_TR_1_Y, 1)) {
//			AfxMessageBox(_T("TR1 Y Not Loading Position !!!"));
//			return;
//		}
		pDY1->oLS_Z1AlignM34In = TRUE;
		pDY1->oLS_Z1AlignM34Out = FALSE;
		pAJinAXL->Write_Output(1);
	} else if (nID == IDC_BTN_TR1_IO_1) {
		pDY1->oLS_Z1AlignS12In = TRUE;
		pDY1->oLS_Z1AlignS12Out = FALSE;
		pAJinAXL->Write_Output(1);
	} else if (nID == IDC_BTN_TR1_IO_2) {
		pDY1->oLS_Z1AlignM34In = FALSE;
		pDY1->oLS_Z1AlignM34Out = TRUE;
		pAJinAXL->Write_Output(1);
	} else if (nID == IDC_BTN_TR1_IO_3) {
		pDY1->oLS_Z1AlignS12In = FALSE;
		pDY1->oLS_Z1AlignS12Out = TRUE;
		pAJinAXL->Write_Output(1);
	} else if (nID == IDC_BTN_TR1_IO_8) {
		pDY1->oLS_Z1AlignM34In = TRUE;
		pDY1->oLS_Z1AlignM34Out = FALSE;
		pAJinAXL->Write_Output(1);
		pCommon->Wait_Time(500);
		pDY1->oLS_Z1AlignS12In = TRUE;
		pDY1->oLS_Z1AlignS12Out = FALSE;
		pAJinAXL->Write_Output(1);
	} else if (nID == IDC_BTN_TR1_IO_9) {
		pDY1->oLS_Z1AlignS12In = FALSE;
		pDY1->oLS_Z1AlignS12Out = TRUE;
		pAJinAXL->Write_Output(1);
		pCommon->Wait_Time(500);
		pDY1->oLS_Z1AlignM34In = FALSE;
		pDY1->oLS_Z1AlignM34Out = TRUE;
		pAJinAXL->Write_Output(1);
	} 
}

void CManualLoadTrayDlg::OnBtnTR2YClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();
	CCommon *pCommon = CCommon::Get_Instance();

	if (!pAJinAXL->Is_Home(AX_LOAD_TRAY_X2)) return;
	if (!pCommon->Check_MainDoor()) return;

	if(!(pCommon->Check_Position(AX_LOAD_PICKER_Z, 0) )) {
		AfxMessageBox(_T("Load Picker Z Axis Ready Position 이동후 진행하세요. ...."));
		return;
	}

	if(!pDX1->iLS_Z2AlignS12In || pDX1->iLS_Z2AlignS12Out || !pDX1->iLS_Z2AlignM34In || pDX1->iLS_Z2AlignM34Out)
	{
		AfxMessageBox(_T("Tray Aliner Master/Slave In 후 진행하세요. ...."));
		return;
	}

	if((pCommon->Check_Position(AX_LOAD_TRAY_Z2, 0) && pCommon->Check_Position(AX_LOAD_TRAY_Z1, 1)) ||
	   (pCommon->Check_Position(AX_LOAD_TRAY_Z2, 1) && pCommon->Check_Position(AX_LOAD_TRAY_Z1, 0)) ) {
		if (nID == IDC_BTN_TR2_Y_0) {
			pCommon->Move_Position(AX_LOAD_TRAY_X2, 0);
		} else if (nID == IDC_BTN_TR2_Y_1) {
			pCommon->Move_Position(AX_LOAD_TRAY_X2, 2);
		} else if (nID == IDC_BTN_TR2_Y_2) {
			pCommon->Move_Position(AX_LOAD_TRAY_X2, 3);
		}
	} else {
		AfxMessageBox(_T("Load Tray 2 Z1 - Z2 Axis Position Error...."));
		return;
	}
}

void CManualLoadTrayDlg::OnBtnTR2ZClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();
	CCommon *pCommon = CCommon::Get_Instance();

	if (!pAJinAXL->Is_Home(AX_LOAD_TRAY_Z2)) return;
	if (!pCommon->Check_MainDoor()) return;

	if((pCommon->Check_Position(AX_LOAD_TRAY_X1, 0) && pCommon->Check_Position(AX_LOAD_TRAY_X2, 0)) ||
	   (pCommon->Check_Position(AX_LOAD_TRAY_X1, 2) && pCommon->Check_Position(AX_LOAD_TRAY_X2, 2)) ||
	   (pCommon->Check_Position(AX_LOAD_TRAY_X1, 3) && pCommon->Check_Position(AX_LOAD_TRAY_X2, 3)) ) {
		AfxMessageBox(_T("Load Tray X1_X2 Axis Position Error...."));
		return;
	}

	if (nID == IDC_BTN_TR2_Z_0) {
		pCommon->Move_Position(AX_LOAD_TRAY_Z2, 0);
	} else if (nID == IDC_BTN_TR2_Z_1) {
		pCommon->Move_Position(AX_LOAD_TRAY_Z2, 1);
	} else if (nID == IDC_BTN_TR2_Z_2) {
		if (pDX1->iLS_Z2Check1 && pCommon->Check_Position(AX_LOAD_TRAY_X2, 0) && pDX1->iLS_LoadSupport1In) {
			AfxMessageBox(_T("Can not Move (Load Tray 2 = Tray Exist and Load Support = In)"));
			return;
		}
		if (pDX1->iLS_Z2Check1 && pCommon->Check_Position(AX_LOAD_TRAY_X2, 3) && pDX1->iLS_UnloadSupport1In) {
			AfxMessageBox(_T("Can not Move (Load Tray 2 = Tray Exist and Unload Support = In)"));
			return;
		}

		if (pCommon->Check_Position(AX_LOAD_TRAY_X2, 0) || pCommon->Check_Position(AX_LOAD_TRAY_X2, 3)) {
			pCommon->Move_Position(AX_LOAD_TRAY_Z2, 2);
		} else {
			AfxMessageBox(_T("Load Tray 2 X Axis Position Error...."));
			return;
		}
	} else if (nID == IDC_BTN_TR2_Z_3) {
		if (pCommon->Check_Position(AX_LOAD_TRAY_X2, 0) || pCommon->Check_Position(AX_LOAD_TRAY_X2, 3)) {
			pCommon->Move_Position(AX_LOAD_TRAY_Z2, 3);
		} else {
			AfxMessageBox(_T("Load Tray 2 X Axis Position Error...."));
			return;
		}
	}
}

void CManualLoadTrayDlg::OnBtnTR2IOClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_1 *pDY1 = pAJinAXL->Get_pDY1();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	CManualDlg *pManualDlg = CManualDlg::Get_Instance();
	pManualDlg->MainDoor_Lock();

	if (nID == IDC_BTN_TR2_IO_0) {
//		if (!pCommon->Check_Position(AX_LOAD_TRAY_TR_1_Y, 1)) {
//			AfxMessageBox(_T("TR1 Y Not Loading Position !!!"));
//			return;
//		}
		pDY1->oLS_Z2AlignM34In = TRUE;
		pDY1->oLS_Z2AlignM34Out = FALSE;
		pAJinAXL->Write_Output(1);
	} else if (nID == IDC_BTN_TR2_IO_1) {
		pDY1->oLS_Z2AlignS12In = TRUE;
		pDY1->oLS_Z2AlignS12Out = FALSE;
		pAJinAXL->Write_Output(1);
	} else if (nID == IDC_BTN_TR2_IO_2) {
		pDY1->oLS_Z2AlignM34In = FALSE;
		pDY1->oLS_Z2AlignM34Out = TRUE;
		pAJinAXL->Write_Output(1);
	} else if (nID == IDC_BTN_TR2_IO_3) {
		pDY1->oLS_Z2AlignS12In = FALSE;
		pDY1->oLS_Z2AlignS12Out = TRUE;
		pAJinAXL->Write_Output(1);
	} else if (nID == IDC_BTN_TR2_IO_4) {
		pDY1->oLS_Z2AlignM34In = TRUE;
		pDY1->oLS_Z2AlignM34Out = FALSE;
		pAJinAXL->Write_Output(1);
		pCommon->Wait_Time(500);
		pDY1->oLS_Z2AlignS12In = TRUE;
		pDY1->oLS_Z2AlignS12Out = FALSE;
		pAJinAXL->Write_Output(1);
	} else if (nID == IDC_BTN_TR2_IO_5) {
		pDY1->oLS_Z2AlignS12In = FALSE;
		pDY1->oLS_Z2AlignS12Out = TRUE;
		pAJinAXL->Write_Output(1);
		pCommon->Wait_Time(500);
		pDY1->oLS_Z2AlignM34In = FALSE;
		pDY1->oLS_Z2AlignM34Out = TRUE;
		pAJinAXL->Write_Output(1);
	} 
}
