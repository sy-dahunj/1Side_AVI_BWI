// ManualIndexDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "ManualIndexDlg.h"
#include "afxdialogex.h"
#include <math.h>

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"
#include "ManualDlg.h"
#include "Inspector.h"

// CManualIndexDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualIndexDlg, CDialogEx)

CManualIndexDlg::CManualIndexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualIndexDlg::IDD, pParent)
{
}

CManualIndexDlg::~CManualIndexDlg()
{
}

void CManualIndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	DDX_Control(pDX, IDC_STC_AXIS_POS_5, m_stcAxisPos[5]);

	DDX_Control(pDX, IDC_BTN_VISION_Y_0, m_btnVisionY[0]);
	DDX_Control(pDX, IDC_BTN_VISION_Y_1, m_btnVisionY[1]);
	DDX_Control(pDX, IDC_BTN_VISION_Y_2, m_btnVisionY[2]);
	DDX_Control(pDX, IDC_BTN_VISION_Y_3, m_btnVisionY[3]);
	DDX_Control(pDX, IDC_BTN_VISION_Y_4, m_btnVisionY[4]);
	DDX_Control(pDX, IDC_BTN_VISION_Y_5, m_btnVisionY[5]);
	DDX_Control(pDX, IDC_BTN_VISION_Y_6, m_btnVisionY[6]);
	DDX_Control(pDX, IDC_BTN_VISION_Y_7, m_btnVisionY[7]);
	DDX_Control(pDX, IDC_BTN_VISION_A_0, m_btnVisionA[0]);
	DDX_Control(pDX, IDC_BTN_VISION_Z_0, m_btnVisionZ[0]);
	DDX_Control(pDX, IDC_BTN_VISION_Z_1, m_btnVisionZ[1]);
	DDX_Control(pDX, IDC_BTN_BARCODE_A_0, m_btnBarcodeA[0]);
	DDX_Control(pDX, IDC_BTN_NGSTAGE_Y_0, m_btnNGStageY[0]);
	DDX_Control(pDX, IDC_BTN_NGSTAGE_Y_1, m_btnNGStageY[1]);
	DDX_Control(pDX, IDC_BTN_NGSTAGE_Y_2, m_btnNGStageY[2]);

	DDX_Control(pDX, IDC_BTN_TR_IO_0, m_btnTRIO[0]);
	DDX_Control(pDX, IDC_BTN_TR_IO_1, m_btnTRIO[1]);
	DDX_Control(pDX, IDC_BTN_TR_IO_2, m_btnTRIO[2]);
	DDX_Control(pDX, IDC_BTN_TR_IO_3, m_btnTRIO[3]);
	DDX_Control(pDX, IDC_BTN_TR_IO_4, m_btnTRIO[4]);
	DDX_Control(pDX, IDC_BTN_TR_IO_5, m_btnTRIO[5]);
	DDX_Control(pDX, IDC_BTN_TR_IO_6, m_btnTRIO[6]);
	DDX_Control(pDX, IDC_BTN_TR_IO_7, m_btnTRIO[7]);
	DDX_Control(pDX, IDC_BTN_TR_IO_8, m_btnTRIO[8]);
	DDX_Control(pDX, IDC_BTN_TR_IO_9, m_btnTRIO[9]);
	DDX_Control(pDX, IDC_BTN_TR_IO_10, m_btnTRIO[10]);
	DDX_Control(pDX, IDC_BTN_TR_IO_11, m_btnTRIO[11]);
	DDX_Control(pDX, IDC_BTN_TR_IO_12, m_btnTRIO[12]);
	DDX_Control(pDX, IDC_BTN_TR_IO_13, m_btnTRIO[13]);
	DDX_Control(pDX, IDC_BTN_TR_IO_14, m_btnTRIO[14]);
	DDX_Control(pDX, IDC_BTN_TR_IO_15, m_btnTRIO[15]);

	DDX_Control(pDX, IDC_BTN_VACUUM_IO_0, m_btnVacIO[0]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_1, m_btnVacIO[1]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_2, m_btnVacIO[2]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_3, m_btnVacIO[3]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_4, m_btnVacIO[4]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_5, m_btnVacIO[5]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_6, m_btnVacIO[6]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_7, m_btnVacIO[7]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_8, m_btnVacIO[8]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_9, m_btnVacIO[9]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_10, m_btnVacIO[10]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_11, m_btnVacIO[11]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_12, m_btnVacIO[12]);
	DDX_Control(pDX, IDC_BTN_VACUUM_IO_13, m_btnVacIO[13]);

	DDX_Control(pDX, IDC_BTN_NGVAC_IO_0,  m_btnNGVacIO[0]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_1,  m_btnNGVacIO[1]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_2,  m_btnNGVacIO[2]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_3,  m_btnNGVacIO[3]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_4,  m_btnNGVacIO[4]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_5,  m_btnNGVacIO[5]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_6,  m_btnNGVacIO[6]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_7,  m_btnNGVacIO[7]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_8,  m_btnNGVacIO[8]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_9,  m_btnNGVacIO[9]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_10, m_btnNGVacIO[10]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_11, m_btnNGVacIO[11]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_12, m_btnNGVacIO[12]);
	DDX_Control(pDX, IDC_BTN_NGVAC_IO_13, m_btnNGVacIO[13]);

	DDX_Control(pDX, IDC_BTN_GDVAC_IO_0,  m_btnGDVacIO[0]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_1,  m_btnGDVacIO[1]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_2,  m_btnGDVacIO[2]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_3,  m_btnGDVacIO[3]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_4,  m_btnGDVacIO[4]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_5,  m_btnGDVacIO[5]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_6,  m_btnGDVacIO[6]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_7,  m_btnGDVacIO[7]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_8,  m_btnGDVacIO[8]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_9,  m_btnGDVacIO[9]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_10, m_btnGDVacIO[10]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_11, m_btnGDVacIO[11]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_12, m_btnGDVacIO[12]);
	DDX_Control(pDX, IDC_BTN_GDVAC_IO_13, m_btnGDVacIO[13]);

	DDX_Control(pDX, IDC_LED_VACUUM_IO_0, m_ledVacIO[0]);
	DDX_Control(pDX, IDC_LED_VACUUM_IO_1, m_ledVacIO[1]);
	DDX_Control(pDX, IDC_LED_VACUUM_IO_2, m_ledVacIO[2]);
	DDX_Control(pDX, IDC_LED_VACUUM_IO_3, m_ledVacIO[3]);
	DDX_Control(pDX, IDC_LED_VACUUM_IO_4, m_ledVacIO[4]);
	DDX_Control(pDX, IDC_LED_VACUUM_IO_5, m_ledVacIO[5]);

	DDX_Control(pDX, IDC_LED_NGVAC_IO_0, m_ledNGVacIO[0]);
	DDX_Control(pDX, IDC_LED_NGVAC_IO_1, m_ledNGVacIO[1]);
	DDX_Control(pDX, IDC_LED_NGVAC_IO_2, m_ledNGVacIO[2]);
	DDX_Control(pDX, IDC_LED_NGVAC_IO_3, m_ledNGVacIO[3]);
	DDX_Control(pDX, IDC_LED_NGVAC_IO_4, m_ledNGVacIO[4]);
	DDX_Control(pDX, IDC_LED_NGVAC_IO_5, m_ledNGVacIO[5]);

	DDX_Control(pDX, IDC_LED_GDVAC_IO_0, m_ledGDVacIO[0]);
	DDX_Control(pDX, IDC_LED_GDVAC_IO_1, m_ledGDVacIO[1]);
	DDX_Control(pDX, IDC_LED_GDVAC_IO_2, m_ledGDVacIO[2]);
	DDX_Control(pDX, IDC_LED_GDVAC_IO_3, m_ledGDVacIO[3]);
	DDX_Control(pDX, IDC_LED_GDVAC_IO_4, m_ledGDVacIO[4]);
	DDX_Control(pDX, IDC_LED_GDVAC_IO_5, m_ledGDVacIO[5]);

	DDX_Control(pDX, IDC_LED_TR_IO_0, m_ledTRIO[0]);
	DDX_Control(pDX, IDC_LED_TR_IO_1, m_ledTRIO[1]);
	DDX_Control(pDX, IDC_LED_TR_IO_2, m_ledTRIO[2]);
	DDX_Control(pDX, IDC_LED_TR_IO_3, m_ledTRIO[3]);
	DDX_Control(pDX, IDC_LED_TR_IO_4, m_ledTRIO[4]);
	DDX_Control(pDX, IDC_LED_TR_IO_5, m_ledTRIO[5]);
	DDX_Control(pDX, IDC_LED_TR_IO_6, m_ledTRIO[6]);
	DDX_Control(pDX, IDC_LED_TR_IO_7, m_ledTRIO[7]);
	DDX_Control(pDX, IDC_LED_TR_IO_8, m_ledTRIO[8]);
	DDX_Control(pDX, IDC_LED_TR_IO_9, m_ledTRIO[9]);
	DDX_Control(pDX, IDC_LED_TR_IO_10, m_ledTRIO[10]);
	DDX_Control(pDX, IDC_LED_TR_IO_11, m_ledTRIO[11]);
	DDX_Control(pDX, IDC_LED_TR_IO_12, m_ledTRIO[12]);
	DDX_Control(pDX, IDC_LED_TR_IO_13, m_ledTRIO[13]);
	DDX_Control(pDX, IDC_LED_TR_IO_14, m_ledTRIO[14]);
	DDX_Control(pDX, IDC_LED_TR_IO_15, m_ledTRIO[15]);
	DDX_Control(pDX, IDC_LED_TR_IO_16, m_ledTRIO[16]);
	DDX_Control(pDX, IDC_LED_TR_IO_17, m_ledTRIO[17]);
	DDX_Control(pDX, IDC_LED_TR_IO_18, m_ledTRIO[18]);

	DDX_Control(pDX, IDC_BTN_PRESS_UP, m_btnBlock[0]);
	DDX_Control(pDX, IDC_BTN_PRESS_DOWN, m_btnBlock[1]);
	DDX_Control(pDX, IDC_LED_BLOCK_UP, m_ledBlock[0]);
	DDX_Control(pDX, IDC_LED_BLOCK_DOWN, m_ledBlock[1]);
}

BEGIN_MESSAGE_MAP(CManualIndexDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_Y_0, IDC_BTN_VISION_Y_0, OnBtnVisionYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_Y_1, IDC_BTN_VISION_Y_1, OnBtnVisionYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_Y_2, IDC_BTN_VISION_Y_2, OnBtnVisionYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_Y_3, IDC_BTN_VISION_Y_3, OnBtnVisionYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_Y_4, IDC_BTN_VISION_Y_4, OnBtnVisionYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_Y_5, IDC_BTN_VISION_Y_5, OnBtnVisionYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_Y_6, IDC_BTN_VISION_Y_6, OnBtnVisionYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_Y_7, IDC_BTN_VISION_Y_7, OnBtnVisionYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_A_0, IDC_BTN_VISION_A_0, OnBtnVisionAClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_Z_0, IDC_BTN_VISION_Z_0, OnBtnVisionZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_Z_1, IDC_BTN_VISION_Z_1, OnBtnVisionZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_BARCODE_A_0, IDC_BTN_BARCODE_A_0, OnBtnBarcoeAClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGSTAGE_Y_0, IDC_BTN_NGSTAGE_Y_0, OnBtnNGStageYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGSTAGE_Y_1, IDC_BTN_NGSTAGE_Y_1, OnBtnNGStageYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGSTAGE_Y_2, IDC_BTN_NGSTAGE_Y_2, OnBtnNGStageYClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_0, IDC_BTN_TR_IO_0, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_1, IDC_BTN_TR_IO_1, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_2, IDC_BTN_TR_IO_2, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_3, IDC_BTN_TR_IO_3, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_4, IDC_BTN_TR_IO_4, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_5, IDC_BTN_TR_IO_5, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_6, IDC_BTN_TR_IO_6, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_7, IDC_BTN_TR_IO_7, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_8, IDC_BTN_TR_IO_8, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_9, IDC_BTN_TR_IO_9, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_10, IDC_BTN_TR_IO_10, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_11, IDC_BTN_TR_IO_11, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_12, IDC_BTN_TR_IO_12, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_13, IDC_BTN_TR_IO_13, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_14, IDC_BTN_TR_IO_14, OnBtnTRIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TR_IO_15, IDC_BTN_TR_IO_15, OnBtnTRIOClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_0, IDC_BTN_VACUUM_IO_0, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_1, IDC_BTN_VACUUM_IO_1, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_2, IDC_BTN_VACUUM_IO_2, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_3, IDC_BTN_VACUUM_IO_3, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_4, IDC_BTN_VACUUM_IO_4, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_5, IDC_BTN_VACUUM_IO_5, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_6, IDC_BTN_VACUUM_IO_6, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_7, IDC_BTN_VACUUM_IO_7, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_8, IDC_BTN_VACUUM_IO_8, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_9, IDC_BTN_VACUUM_IO_9, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_10, IDC_BTN_VACUUM_IO_10, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_11, IDC_BTN_VACUUM_IO_11, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_12, IDC_BTN_VACUUM_IO_12, OnBtnVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VACUUM_IO_13, IDC_BTN_VACUUM_IO_13, OnBtnVacIOClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_0,  IDC_BTN_NGVAC_IO_0,  OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_1,  IDC_BTN_NGVAC_IO_1,  OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_2,  IDC_BTN_NGVAC_IO_2,  OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_3,  IDC_BTN_NGVAC_IO_3,  OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_4,  IDC_BTN_NGVAC_IO_4,  OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_5,  IDC_BTN_NGVAC_IO_5,  OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_6,  IDC_BTN_NGVAC_IO_6,  OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_7,  IDC_BTN_NGVAC_IO_7,  OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_8,  IDC_BTN_NGVAC_IO_8,  OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_9,  IDC_BTN_NGVAC_IO_9,  OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_10, IDC_BTN_NGVAC_IO_10, OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_11, IDC_BTN_NGVAC_IO_11, OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_12, IDC_BTN_NGVAC_IO_12, OnBtnNGVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NGVAC_IO_13, IDC_BTN_NGVAC_IO_13, OnBtnNGVacIOClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_0,  IDC_BTN_GDVAC_IO_0,  OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_1,  IDC_BTN_GDVAC_IO_1,  OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_2,  IDC_BTN_GDVAC_IO_2,  OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_3,  IDC_BTN_GDVAC_IO_3,  OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_4,  IDC_BTN_GDVAC_IO_4,  OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_5,  IDC_BTN_GDVAC_IO_5,  OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_6,  IDC_BTN_GDVAC_IO_6,  OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_7,  IDC_BTN_GDVAC_IO_7,  OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_8,  IDC_BTN_GDVAC_IO_8,  OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_9,  IDC_BTN_GDVAC_IO_9,  OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_10, IDC_BTN_GDVAC_IO_10, OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_11, IDC_BTN_GDVAC_IO_11, OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_12, IDC_BTN_GDVAC_IO_12, OnBtnGDVacIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GDVAC_IO_13, IDC_BTN_GDVAC_IO_13, OnBtnGDVacIOClick)

	ON_BN_CLICKED(IDC_BTN_PRESS_UP, &CManualIndexDlg::OnBnClickedBtnPressUp)
	ON_BN_CLICKED(IDC_BTN_PRESS_DOWN, &CManualIndexDlg::OnBnClickedBtnPressDown)
END_MESSAGE_MAP()

// CManualIndexDlg 메시지 처리기입니다.

BOOL CManualIndexDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

#ifdef PICKER_3
	for (int i=6; i<12; i++) m_btnVacIO[i].ShowWindow(FALSE);
	for (int i=3; i<6; i++) m_ledVacIO[i].ShowWindow(FALSE);

	for (int i=6; i<12; i++) m_btnNGVacIO[i].ShowWindow(FALSE);
	for (int i=3; i<6; i++) m_ledNGVacIO[i].ShowWindow(FALSE);

	for (int i=6; i<12; i++) m_btnGDVacIO[i].ShowWindow(FALSE);
	for (int i=3; i<6; i++) m_ledGDVacIO[i].ShowWindow(FALSE);
#endif

#ifdef PICKER_5
	for (int i=10; i<12; i++) m_btnVacIO[i].ShowWindow(FALSE);
	for (int i=5; i<6; i++) m_ledVacIO[i].ShowWindow(FALSE);

	for (int i=10; i<12; i++) m_btnNGVacIO[i].ShowWindow(FALSE);
	for (int i=5; i<6; i++) m_ledNGVacIO[i].ShowWindow(FALSE);

	for (int i=10; i<12; i++) m_btnGDVacIO[i].ShowWindow(FALSE);
	for (int i=5; i<6; i++) m_ledGDVacIO[i].ShowWindow(FALSE);
#endif

#ifdef PICKER_4
	for (int i=8; i<12; i++) m_btnVacIO[i].ShowWindow(FALSE);
	for (int i=4; i<6; i++) m_ledVacIO[i].ShowWindow(FALSE);

	for (int i=8; i<12; i++) m_btnNGVacIO[i].ShowWindow(FALSE);
	for (int i=4; i<6; i++) m_ledNGVacIO[i].ShowWindow(FALSE);

	for (int i=8; i<12; i++) m_btnGDVacIO[i].ShowWindow(FALSE);
	for (int i=4; i<6; i++) m_ledGDVacIO[i].ShowWindow(FALSE);
#endif

	m_bThreadElevator1 = FALSE;
	m_pThreadElevator1 = NULL;
	m_nMRunCase = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CManualIndexDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CManualIndexDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualIndexDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		Display_Status();
	}
}

void CManualIndexDlg::Initial_Controls() 
{
	for (int i = 0; i < 6; i++) m_stcAxisPos[i].Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xB0));
	for (int i = 0; i < 19; i++) m_ledTRIO[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 6; i++) m_ledVacIO[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	
	for (int i = 0; i < 2; i++) m_ledBlock[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
}

void CManualIndexDlg::Display_Status()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_2 *pDX2 = pAJinAXL->Get_pDX2();
	DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();
	DX_DATA_5 *pDX5 = pAJinAXL->Get_pDX5();

	CString strPos;
	AXIS_STATUS *pStatus = pAJinAXL->Get_pStatus(AX_INDEX_R);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[0].SetWindowText(strPos);

	pStatus = pAJinAXL->Get_pStatus(AX_INSPECTION_A);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[1].SetWindowText(strPos);

	pStatus = pAJinAXL->Get_pStatus(AX_INSPECTION_Z);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[2].SetWindowText(strPos);

	pStatus = pAJinAXL->Get_pStatus(AX_BARCODE_A);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[3].SetWindowText(strPos);

	pStatus = pAJinAXL->Get_pStatus(AX_NG_STAGE_Y);
	strPos.Format("%0.3lf", pStatus->dPos);
	m_stcAxisPos[4].SetWindowText(strPos);

	strPos.Format("%d", gData.nIndexPos);
	m_stcAxisPos[5].SetWindowText(strPos);

	if (pDX2->iInspCMAlign1In) m_ledTRIO[0].Set_On(TRUE);
	else m_ledTRIO[0].Set_On(FALSE);
	if (pDX2->iInspCMAlign1Out) m_ledTRIO[1].Set_On(TRUE);
	else m_ledTRIO[1].Set_On(FALSE);
	if (pDX2->iInspCMAlign2In) m_ledTRIO[2].Set_On(TRUE);
	else m_ledTRIO[2].Set_On(FALSE);
	if (pDX2->iInspCMAlign2Out) m_ledTRIO[3].Set_On(TRUE);
	else m_ledTRIO[3].Set_On(FALSE);
	if (pDX2->iInspCMAlign3In) m_ledTRIO[4].Set_On(TRUE);
	else m_ledTRIO[4].Set_On(FALSE);
	if (pDX2->iInspCMAlign3Out) m_ledTRIO[5].Set_On(TRUE);
	else m_ledTRIO[5].Set_On(FALSE);
	if (pDX2->iInspCMAlign4In) m_ledTRIO[6].Set_On(TRUE);
	else m_ledTRIO[6].Set_On(FALSE);
	if (pDX2->iInspCMAlign4Out) m_ledTRIO[7].Set_On(TRUE);
	else m_ledTRIO[7].Set_On(FALSE);
	if (pDX2->iInspVacuumUp) m_ledTRIO[8].Set_On(TRUE);
	else m_ledTRIO[8].Set_On(FALSE);
	if (pDX2->iInspVacuumDown) m_ledTRIO[9].Set_On(TRUE);
	else m_ledTRIO[9].Set_On(FALSE);
	if (pDX2->iInspCMAlignCheck1) m_ledTRIO[10].Set_On(TRUE);
	else m_ledTRIO[10].Set_On(FALSE);
	if (pDX2->iInspCMAlignCheck2) m_ledTRIO[11].Set_On(TRUE);
	else m_ledTRIO[11].Set_On(FALSE);
	if (pDX2->iInspCMAlignCheck3) m_ledTRIO[12].Set_On(TRUE);
	else m_ledTRIO[12].Set_On(FALSE);

	if (pDX5->iNGVacuumUp) m_ledTRIO[15].Set_On(TRUE);
	else m_ledTRIO[15].Set_On(FALSE);
	if (pDX5->iNGVacuumDown) m_ledTRIO[16].Set_On(TRUE);
	else m_ledTRIO[16].Set_On(FALSE);
	if (pDX5->iGoodVacuumUp) m_ledTRIO[17].Set_On(TRUE);
	else m_ledTRIO[17].Set_On(FALSE);
	if (pDX5->iGoodVacuumDown) m_ledTRIO[18].Set_On(TRUE);
	else m_ledTRIO[18].Set_On(FALSE);

	if (pDX3->iNGTray1Check) m_ledTRIO[13].Set_On(TRUE);
	else m_ledTRIO[13].Set_On(FALSE);
	if (pDX3->iNGTray2Check) m_ledTRIO[14].Set_On(TRUE);
	else m_ledTRIO[14].Set_On(FALSE);

	if (pDX3->iInspVacuumPad1Check) m_ledVacIO[0].Set_On(TRUE);
	else m_ledVacIO[0].Set_On(FALSE);
	if (pDX3->iInspVacuumPad2Check) m_ledVacIO[1].Set_On(TRUE);
	else m_ledVacIO[1].Set_On(FALSE);
	if (pDX3->iInspVacuumPad3Check) m_ledVacIO[2].Set_On(TRUE);
	else m_ledVacIO[2].Set_On(FALSE);
	if (pDX3->iInspVacuumPad4Check) m_ledVacIO[3].Set_On(TRUE);
	else m_ledVacIO[3].Set_On(FALSE);
	if (pDX3->iInspVacuumPad5Check) m_ledVacIO[4].Set_On(TRUE);
	else m_ledVacIO[4].Set_On(FALSE);
	if (pDX3->iInspVacuumPad6Check) m_ledVacIO[5].Set_On(TRUE);
	else m_ledVacIO[5].Set_On(FALSE);

	if (pDX5->iNGVacuumPad1Check) m_ledNGVacIO[0].Set_On(TRUE);
	else m_ledNGVacIO[0].Set_On(FALSE);
	if (pDX5->iNGVacuumPad2Check) m_ledNGVacIO[1].Set_On(TRUE);
	else m_ledNGVacIO[1].Set_On(FALSE);
	if (pDX5->iNGVacuumPad3Check) m_ledNGVacIO[2].Set_On(TRUE);
	else m_ledNGVacIO[2].Set_On(FALSE);
	if (pDX5->iNGVacuumPad4Check) m_ledNGVacIO[3].Set_On(TRUE);
	else m_ledNGVacIO[3].Set_On(FALSE);
	if (pDX5->iNGVacuumPad5Check) m_ledNGVacIO[4].Set_On(TRUE);
	else m_ledNGVacIO[4].Set_On(FALSE);
	if (pDX5->iNGVacuumPad6Check) m_ledNGVacIO[5].Set_On(TRUE);
	else m_ledNGVacIO[5].Set_On(FALSE);

	if (pDX5->iGoodVacuumPad1Check) m_ledGDVacIO[0].Set_On(TRUE);
	else m_ledGDVacIO[0].Set_On(FALSE);
	if (pDX5->iGoodVacuumPad2Check) m_ledGDVacIO[1].Set_On(TRUE);
	else m_ledGDVacIO[1].Set_On(FALSE);
	if (pDX5->iGoodVacuumPad3Check) m_ledGDVacIO[2].Set_On(TRUE);
	else m_ledGDVacIO[2].Set_On(FALSE);
	if (pDX5->iGoodVacuumPad4Check) m_ledGDVacIO[3].Set_On(TRUE);
	else m_ledGDVacIO[3].Set_On(FALSE);
	if (pDX5->iGoodVacuumPad5Check) m_ledGDVacIO[4].Set_On(TRUE);
	else m_ledGDVacIO[4].Set_On(FALSE);
	if (pDX5->iGoodVacuumPad6Check) m_ledGDVacIO[5].Set_On(TRUE);
	else m_ledGDVacIO[5].Set_On(FALSE);

	if (pDX2->iCMPressUp) m_ledBlock[0].Set_On(TRUE);
	else				  m_ledBlock[0].Set_On(FALSE);
	if (pDX2->iCMPressDn) m_ledBlock[1].Set_On(TRUE);
	else				  m_ledBlock[1].Set_On(FALSE);

	BOOL bShow = FALSE;
	if (gData.bUseNGVacuum) bShow = TRUE;
	m_ledTRIO[15].ShowWindow(bShow);
	m_ledTRIO[16].ShowWindow(bShow);
	//for(int i=0; i<6; i++) m_ledNGVacIO[i].ShowWindow(bShow);
	//for(int i=0; i<14; i++) m_btnNGVacIO[i].ShowWindow(bShow);
	m_btnTRIO[12].ShowWindow(bShow);
	m_btnTRIO[13].ShowWindow(bShow);

	bShow = FALSE;
	if (gData.bUseGDVacuum) bShow = TRUE;
	m_ledTRIO[17].ShowWindow(bShow);
	m_ledTRIO[18].ShowWindow(bShow);
	//for(int i=0; i<6; i++) m_ledGDVacIO[i].ShowWindow(bShow);
	//for(int i=0; i<14; i++) m_btnGDVacIO[i].ShowWindow(bShow);
	m_btnTRIO[14].ShowWindow(bShow);
	m_btnTRIO[15].ShowWindow(bShow);

#ifdef PICKER_3
	// Vacuum4,5,6번 disable처리
	bShow = FALSE;
	for (int i=6; i<12; i++) m_btnVacIO[i].ShowWindow(bShow);
	for (int i=3; i<6; i++) m_ledVacIO[i].ShowWindow(bShow);

	for (int i=6; i<12; i++) m_btnNGVacIO[i].ShowWindow(bShow);
	for (int i=3; i<6; i++) m_ledNGVacIO[i].ShowWindow(FALSE);

	for (int i=6; i<12; i++) m_btnGDVacIO[i].ShowWindow(bShow);
	for (int i=3; i<6; i++) m_ledGDVacIO[i].ShowWindow(bShow);
#endif

#ifdef PICKER_4
	// Vacuum4,5,6번 disable처리
	bShow = FALSE;
	for (int i=8; i<12; i++) m_btnVacIO[i].ShowWindow(bShow);
	for (int i=4; i<6; i++) m_ledVacIO[i].ShowWindow(bShow);

	for (int i=8; i<12; i++) m_btnNGVacIO[i].ShowWindow(bShow);
	for (int i=4; i<6; i++) m_ledNGVacIO[i].ShowWindow(FALSE);

	for (int i=8; i<12; i++) m_btnGDVacIO[i].ShowWindow(bShow);
	for (int i=4; i<6; i++) m_ledGDVacIO[i].ShowWindow(bShow);
#endif

#ifdef PICKER_5
	// Vacuum6번 disable처리
	bShow = FALSE;
	m_ledVacIO[5].ShowWindow(bShow);
	m_btnVacIO[10].ShowWindow(bShow);
	m_btnVacIO[11].ShowWindow(bShow);
	m_ledNGVacIO[5].ShowWindow(bShow);
	m_btnNGVacIO[10].ShowWindow(bShow);
	m_btnNGVacIO[11].ShowWindow(bShow);
	m_ledGDVacIO[5].ShowWindow(bShow);
	m_btnGDVacIO[10].ShowWindow(bShow);
	m_btnGDVacIO[11].ShowWindow(bShow);
#endif

	CDataManager *pDataManager = CDataManager::Get_Instance();
	EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();

	bShow = FALSE;
	if (pEquipData->bUseManagerMode) bShow = TRUE;

	m_btnVisionY[0].ShowWindow(bShow);
	m_btnVisionA[0].ShowWindow(bShow);
	m_btnVisionZ[0].ShowWindow(bShow);
	m_btnBarcodeA[0].ShowWindow(bShow);

	m_btnVisionZ[1].ShowWindow(gData.bUseCMPress);
	for(int i=0; i<2; i++) m_btnBlock[i].ShowWindow(gData.bUseCMPress);
	for(int i=0; i<2; i++) m_ledBlock[i].ShowWindow(gData.bUseCMPress);
}

void CManualIndexDlg::OnBtnVisionYClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();
	DX_DATA_2 *pDX2 = pAJinAXL->Get_pDX2();
	DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();
	DX_DATA_4 *pDX4 = pAJinAXL->Get_pDX4();
	DX_DATA_5 *pDX5 = pAJinAXL->Get_pDX5();

	if (!pAJinAXL->Is_Home(AX_INDEX_R)) return;
	if (!pCommon->Check_MainDoor()) return;

	if (pDX2->iInspVacuumUp || !pDX2->iInspVacuumDown) {
		AfxMessageBox(_T("Index Load Vacuum Down후 진행하세요............."));
		return;
	}
	if (gData.bUseNGVacuum==TRUE && (pDX5->iNGVacuumUp || !pDX5->iNGVacuumDown)) {
		AfxMessageBox(_T("Index NG Vacuum Down후 진행하세요............."));
		return;
	}
	if (gData.bUseGDVacuum==TRUE && (pDX5->iGoodVacuumUp || !pDX5->iGoodVacuumDown)) {
		AfxMessageBox(_T("Index Good Vacuum Down후 진행하세요............."));
		return;
	}
#ifdef NG_PICKER_3
	if (!pDX3->iNGPicker1Up  || !pDX3->iNGPicker2Up  || !pDX3->iNGPicker3Up ||
		pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down ) {
			AfxMessageBox(_T("NG Picker Up후 진행하세요............."));
			return;
	}
#endif
#ifdef NG_PICKER_4
	if (!pDX3->iNGPicker1Up  || !pDX3->iNGPicker2Up  || !pDX3->iNGPicker3Up || !pDX3->iNGPicker4Up  || 
	    pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down || pDX3->iNGPicker4Down ) {
		AfxMessageBox(_T("NG Picker Up후 진행하세요............."));
		return;
	}
#endif

#ifdef NG_PICKER_5
	if (!pDX3->iNGPicker1Up  || !pDX3->iNGPicker2Up  || !pDX3->iNGPicker3Up || !pDX3->iNGPicker4Up  || !pDX3->iNGPicker5Up ||
	    pDX3->iNGPicker1Down || pDX3->iNGPicker2Down || pDX3->iNGPicker3Down || pDX3->iNGPicker4Down || pDX3->iNGPicker5Down ) {
		AfxMessageBox(_T("NG Picker Up후 진행하세요............."));
		return;
	}
#endif

#ifdef PICKER_3
	if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
		pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down )
#endif	

#ifdef PICKER_4
		if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
			!pDX4->iGoodPicker4Up || 
			pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down || 
			pDX4->iGoodPicker4Down )
#endif	

#ifdef PICKER_5
	if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
		!pDX4->iGoodPicker4Up || !pDX4->iGoodPicker5Up ||
		pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down || 
		pDX4->iGoodPicker4Down || pDX4->iGoodPicker5Down )
#endif	
#ifdef PICKER_6
	if (!pDX4->iGoodPicker1Up || !pDX4->iGoodPicker2Up || !pDX4->iGoodPicker3Up || 
		!pDX4->iGoodPicker4Up || !pDX4->iGoodPicker5Up || !pDX4->iGoodPicker6Up ||
		pDX4->iGoodPicker1Down || pDX4->iGoodPicker2Down || pDX4->iGoodPicker3Down || 
		pDX4->iGoodPicker4Down || pDX4->iGoodPicker5Down || pDX4->iGoodPicker6Down )
#endif
	{
		AfxMessageBox(_T("Good Picker Up후 진행하세요............."));
		return;
	}
	if (!pCommon->Check_Position(AX_LOAD_PICKER_Z, 0)) {
		AfxMessageBox(_T("Load Picker Z Ready Position 위치후에 진행하세요....."));
		return;
	}
	if (!pCommon->Check_Position(AX_UNLOAD_PICKER_Z, 0)) {
		AfxMessageBox(_T("Unload Picker Z Ready Position 위치후에 진행하세요....."));
		return;
	}
	if (gData.bUseCMPress) {
		if (!pDX2->iCMPressUp || pDX2->iCMPressDn) {
			AfxMessageBox(_T("CM Press Block Up후에 진행하세요....."));
			return;
		}
	}

	if (pDX2->iInspCMAlign1In && !pDX2->iInspCMAlign1Out && pDX2->iInspCMAlign2In && !pDX2->iInspCMAlign2Out && 
		pDX2->iInspCMAlign3In && !pDX2->iInspCMAlign3Out && pDX2->iInspCMAlign4In && !pDX2->iInspCMAlign4Out ) {
		if (nID == IDC_BTN_VISION_Y_0) {
			pCommon->Move_Position(AX_INDEX_R, 0);
		} else if (nID == IDC_BTN_VISION_Y_1) {
			pCommon->Move_Position(AX_INDEX_R, 0);
		} else if (nID == IDC_BTN_VISION_Y_2) {
			pCommon->Move_Position(AX_INDEX_R, 0);
		} else if (nID == IDC_BTN_VISION_Y_3) {
			pCommon->Move_Position(AX_INDEX_R, 0);
		} else if (nID == IDC_BTN_VISION_Y_4) {
			pCommon->Move_Position(AX_INDEX_R, 0);
		} else if (nID == IDC_BTN_VISION_Y_5) {
			pCommon->Move_Position(AX_INDEX_R, 0);
		} else if (nID == IDC_BTN_VISION_Y_6) {
			pCommon->Move_Position(AX_INDEX_R, 0);
		} else if (nID == IDC_BTN_VISION_Y_7) {
			pCommon->Move_Position(AX_INDEX_R, 0);
		}
	} else {
		AfxMessageBox(_T("Index Align 1~4 In후 진행하세요............."));
		return;
	}
}

void CManualIndexDlg::OnBtnVisionAClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();
	DX_DATA_1 *pDX1 = pAJinAXL->Get_pDX1();

	if (!pAJinAXL->Is_Home(AX_INSPECTION_A)) return;
	if (!pCommon->Check_MainDoor()) return;

	if (nID == IDC_BTN_VISION_A_0) {
		pCommon->Move_Position(AX_INSPECTION_A, 0);
	}
/* else if (nID == IDC_BTN_COVER1_Z_1) {
		if (!pCommon->Check_Position(AX_INSPECT_TRAY_TR_R, 1) ) {
			AfxMessageBox(_T("Tray Transfer R축이 Ready일경우만 가능합니다.............."));
			return;
		}

		pCommon->Move_Position(AX_COVER_1_Z, 1);
	} else if (nID == IDC_BTN_COVER1_Z_2){
		if (!pCommon->Check_Position(AX_INSPECT_TRAY_TR_R, 1) ) {
			AfxMessageBox(_T("Tray Transfer R축이 Ready일경우만 가능합니다.............."));
			return;
		}

		pAJinAXL->Is_Home(AX_COVER_1_Z);
	}
*/
}

void CManualIndexDlg::OnBtnVisionZClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();
	DX_DATA_2 *pDX2 = pAJinAXL->Get_pDX2();

	if (!pAJinAXL->Is_Home(AX_INSPECTION_Z)) return;
	if (!pCommon->Check_MainDoor()) return;

	if (nID == IDC_BTN_VISION_Z_0) {
		if (gData.bUseCMPress) {
			if (pDX2->iCMPressUp || !pDX2->iCMPressDn) {
				AfxMessageBox(_T("CM Press Block Down일 경우만 가능합니다.............."));
				return;
			}
		}
		pCommon->Move_Position(AX_INSPECTION_Z, 0);	// Work
	} else {
		pCommon->Move_Position(AX_INSPECTION_Z, 1);	// Up
	}
}

void CManualIndexDlg::OnBtnBarcoeAClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();

	if (!pAJinAXL->Is_Home(AX_BARCODE_A)) return;
	if (!pCommon->Check_MainDoor()) return;

	if (nID == IDC_BTN_BARCODE_A_0) {
		pCommon->Move_Position(AX_BARCODE_A, 0);
	}
}

void CManualIndexDlg::OnBtnNGStageYClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();
	DX_DATA_3 *pDX3 = pAJinAXL->Get_pDX3();

	if (!pAJinAXL->Is_Home(AX_NG_STAGE_Y)) return;
	if (!pCommon->Check_MainDoor()) return;

#ifdef NG_PICKER_3
	if (pDX3->iNGPicker1Up   && pDX3->iNGPicker2Up    && pDX3->iNGPicker3Up &&
		!pDX3->iNGPicker1Down && !pDX3->iNGPicker2Down && !pDX3->iNGPicker3Down ) {
#endif
#ifdef NG_PICKER_4
	if (pDX3->iNGPicker1Up   && pDX3->iNGPicker2Up    && pDX3->iNGPicker3Up &&  pDX3->iNGPicker4Up && 
	   !pDX3->iNGPicker1Down && !pDX3->iNGPicker2Down && !pDX3->iNGPicker3Down && !pDX3->iNGPicker4Down  ) {
#endif
#ifdef NG_PICKER_5
	if (pDX3->iNGPicker1Up   && pDX3->iNGPicker2Up    && pDX3->iNGPicker3Up &&  pDX3->iNGPicker4Up && pDX3->iNGPicker5Up && 
	   !pDX3->iNGPicker1Down && !pDX3->iNGPicker2Down && !pDX3->iNGPicker3Down && !pDX3->iNGPicker4Down && !pDX3->iNGPicker5Down ) {
#endif

		if (nID == IDC_BTN_NGSTAGE_Y_0) {
			pCommon->Move_Position(AX_NG_STAGE_Y, 0);
		} else if (nID == IDC_BTN_NGSTAGE_Y_1) {
			pCommon->Move_Position(AX_NG_STAGE_Y, 1);
		} else if (nID == IDC_BTN_NGSTAGE_Y_2) {
			pCommon->Move_Position(AX_NG_STAGE_Y, 2);
		}
	} else {
		AfxMessageBox(_T("NG Picker Up후 진행하세요............."));
		return;
	}
}

void CManualIndexDlg::OnBtnVacIOClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_3 *pDY3 = pAJinAXL->Get_pDY3();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	if (nID == IDC_BTN_VACUUM_IO_0) {
		pDY3->oInspVacuumPad1On = TRUE;
	} else if (nID == IDC_BTN_VACUUM_IO_1) {
		pDY3->oInspVacuumPad1On = FALSE;
	} else if (nID == IDC_BTN_VACUUM_IO_2) {
		pDY3->oInspVacuumPad2On = TRUE;
	} else if (nID == IDC_BTN_VACUUM_IO_3) {
		pDY3->oInspVacuumPad2On = FALSE;
	} else if (nID == IDC_BTN_VACUUM_IO_4) {
		pDY3->oInspVacuumPad3On = TRUE;
	} else if (nID == IDC_BTN_VACUUM_IO_5) {
		pDY3->oInspVacuumPad3On = FALSE;
	} else if (nID == IDC_BTN_VACUUM_IO_6) {
		pDY3->oInspVacuumPad4On = TRUE;
	} else if (nID == IDC_BTN_VACUUM_IO_7) {
		pDY3->oInspVacuumPad4On = FALSE;
	} else if (nID == IDC_BTN_VACUUM_IO_8) {
		pDY3->oInspVacuumPad5On = TRUE;
	} else if (nID == IDC_BTN_VACUUM_IO_9) {
		pDY3->oInspVacuumPad5On = FALSE;
	} else if (nID == IDC_BTN_VACUUM_IO_10) {
		pDY3->oInspVacuumPad6On = TRUE;
	} else if (nID == IDC_BTN_VACUUM_IO_11) {
		pDY3->oInspVacuumPad6On = FALSE;
	} else if (nID == IDC_BTN_VACUUM_IO_12) {
		pDY3->oInspVacuumPad1On = TRUE;
		pDY3->oInspVacuumPad2On = TRUE;
		pDY3->oInspVacuumPad3On = TRUE;

#ifdef PICKER_4
		pDY3->oInspVacuumPad4On = TRUE;
#endif

#ifdef PICKER_5
		pDY3->oInspVacuumPad4On = TRUE;
		pDY3->oInspVacuumPad5On = TRUE;
#endif
#ifdef PICKER_6
		pDY3->oInspVacuumPad4On = TRUE;
		pDY3->oInspVacuumPad5On = TRUE;
		pDY3->oInspVacuumPad6On = TRUE;
#endif
	} else if (nID == IDC_BTN_VACUUM_IO_13) {
		pDY3->oInspVacuumPad1On = FALSE;
		pDY3->oInspVacuumPad2On = FALSE;
		pDY3->oInspVacuumPad3On = FALSE;
#ifdef PICKER_4
		pDY3->oInspVacuumPad4On = FALSE;
#endif
#ifdef PICKER_5
		pDY3->oInspVacuumPad4On = FALSE;
		pDY3->oInspVacuumPad5On = FALSE;
#endif
#ifdef PICKER_6
		pDY3->oInspVacuumPad4On = FALSE;
		pDY3->oInspVacuumPad5On = FALSE;
		pDY3->oInspVacuumPad6On = FALSE;
#endif
	}
	pAJinAXL->Write_Output(3);
}

void CManualIndexDlg::OnBtnNGVacIOClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	if (nID == IDC_BTN_NGVAC_IO_0) {
		pDY5->oNGVacuumPad1On = TRUE;
	} else if (nID == IDC_BTN_NGVAC_IO_1) {
		pDY5->oNGVacuumPad1On = FALSE;
	} else if (nID == IDC_BTN_NGVAC_IO_2) {
		pDY5->oNGVacuumPad2On = TRUE;
	} else if (nID == IDC_BTN_NGVAC_IO_3) {
		pDY5->oNGVacuumPad2On = FALSE;
	} else if (nID == IDC_BTN_NGVAC_IO_4) {
		pDY5->oNGVacuumPad3On = TRUE;
	} else if (nID == IDC_BTN_NGVAC_IO_5) {
		pDY5->oNGVacuumPad3On = FALSE;
	} else if (nID == IDC_BTN_NGVAC_IO_6) {
		pDY5->oNGVacuumPad4On = TRUE;
	} else if (nID == IDC_BTN_NGVAC_IO_7) {
		pDY5->oNGVacuumPad4On = FALSE;
	} else if (nID == IDC_BTN_NGVAC_IO_8) {
		pDY5->oNGVacuumPad5On = TRUE;
	} else if (nID == IDC_BTN_NGVAC_IO_9) {
		pDY5->oNGVacuumPad5On = FALSE;
	} else if (nID == IDC_BTN_NGVAC_IO_10) {
		pDY5->oNGVacuumPad6On = TRUE;
	} else if (nID == IDC_BTN_NGVAC_IO_11) {
		pDY5->oNGVacuumPad6On = FALSE;
	} else if (nID == IDC_BTN_NGVAC_IO_12) {
		pDY5->oNGVacuumPad1On = TRUE;
		pDY5->oNGVacuumPad2On = TRUE;
		pDY5->oNGVacuumPad3On = TRUE;
#ifdef PICKER_4
		pDY5->oNGVacuumPad4On = TRUE;
#endif
#ifdef PICKER_5
		pDY5->oNGVacuumPad4On = TRUE;
		pDY5->oNGVacuumPad5On = TRUE;
#endif
#ifdef PICKER_6
		pDY5->oNGVacuumPad4On = TRUE;
		pDY5->oNGVacuumPad5On = TRUE;
		pDY5->oNGVacuumPad6On = TRUE;
#endif
	} else if (nID == IDC_BTN_NGVAC_IO_13) {
		pDY5->oNGVacuumPad1On = FALSE;
		pDY5->oNGVacuumPad2On = FALSE;
		pDY5->oNGVacuumPad3On = FALSE;
#ifdef PICKER_4
		pDY5->oNGVacuumPad4On = FALSE;
#endif
#ifdef PICKER_5
		pDY5->oNGVacuumPad4On = FALSE;
		pDY5->oNGVacuumPad5On = FALSE;
#endif
#ifdef PICKER_6
		pDY5->oNGVacuumPad4On = FALSE;
		pDY5->oNGVacuumPad5On = FALSE;
		pDY5->oNGVacuumPad6On = FALSE;
#endif
	}
	pAJinAXL->Write_Output(5);
}

void CManualIndexDlg::OnBtnGDVacIOClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	if (nID == IDC_BTN_GDVAC_IO_0) {
		pDY5->oGoodVacuumPad1On = TRUE;
	} else if (nID == IDC_BTN_GDVAC_IO_1) {
		pDY5->oGoodVacuumPad1On = FALSE;
	} else if (nID == IDC_BTN_GDVAC_IO_2) {
		pDY5->oGoodVacuumPad2On = TRUE;
	} else if (nID == IDC_BTN_GDVAC_IO_3) {
		pDY5->oGoodVacuumPad2On = FALSE;
	} else if (nID == IDC_BTN_GDVAC_IO_4) {
		pDY5->oGoodVacuumPad3On = TRUE;
	} else if (nID == IDC_BTN_GDVAC_IO_5) {
		pDY5->oGoodVacuumPad3On = FALSE;
	} else if (nID == IDC_BTN_GDVAC_IO_6) {
		pDY5->oGoodVacuumPad4On = TRUE;
	} else if (nID == IDC_BTN_GDVAC_IO_7) {
		pDY5->oGoodVacuumPad4On = FALSE;
	} else if (nID == IDC_BTN_GDVAC_IO_8) {
		pDY5->oGoodVacuumPad5On = TRUE;
	} else if (nID == IDC_BTN_GDVAC_IO_9) {
		pDY5->oGoodVacuumPad5On = FALSE;
	} else if (nID == IDC_BTN_GDVAC_IO_10) {
		pDY5->oGoodVacuumPad6On = TRUE;
	} else if (nID == IDC_BTN_GDVAC_IO_11) {
		pDY5->oGoodVacuumPad6On = FALSE;
	} else if (nID == IDC_BTN_GDVAC_IO_12) {
		pDY5->oGoodVacuumPad1On = TRUE;
		pDY5->oGoodVacuumPad2On = TRUE;
		pDY5->oGoodVacuumPad3On = TRUE;
#ifdef PICKER_4
		pDY5->oGoodVacuumPad4On = TRUE;
#endif
#ifdef PICKER_5
		pDY5->oGoodVacuumPad4On = TRUE;
		pDY5->oGoodVacuumPad5On = TRUE;
#endif
#ifdef PICKER_6
		pDY5->oGoodVacuumPad4On = TRUE;
		pDY5->oGoodVacuumPad5On = TRUE;
		pDY5->oGoodVacuumPad6On = TRUE;
#endif
	} else if (nID == IDC_BTN_GDVAC_IO_13) {
		pDY5->oGoodVacuumPad1On = FALSE;
		pDY5->oGoodVacuumPad2On = FALSE;
		pDY5->oGoodVacuumPad3On = FALSE;
#ifdef PICKER_4
		pDY5->oGoodVacuumPad4On = FALSE;
#endif
#ifdef PICKER_5
		pDY5->oGoodVacuumPad4On = FALSE;
		pDY5->oGoodVacuumPad5On = FALSE;
#endif
#ifdef PICKER_6
		pDY5->oGoodVacuumPad4On = FALSE;
		pDY5->oGoodVacuumPad5On = FALSE;
		pDY5->oGoodVacuumPad6On = FALSE;
#endif
	}
	pAJinAXL->Write_Output(5);
}

void CManualIndexDlg::OnBtnTRIOClick(UINT nID)
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_2 *pDY2 = pAJinAXL->Get_pDY2();
	DY_DATA_5 *pDY5 = pAJinAXL->Get_pDY5();

	CCommon *pCommon = CCommon::Get_Instance();
	if (!pCommon->Check_MainDoor()) return;

	if (nID == IDC_BTN_TR_IO_0) {
		pDY2->oInspCMAlign1In = TRUE;
		pDY2->oInspCMAlign1Out = FALSE;
	} else if (nID == IDC_BTN_TR_IO_1) {
		pDY2->oInspCMAlign1In = FALSE;
		pDY2->oInspCMAlign1Out = TRUE;
	} else if (nID == IDC_BTN_TR_IO_2) {
		pDY2->oInspCMAlign2In = TRUE;
		pDY2->oInspCMAlign2Out = FALSE;
	} else if (nID == IDC_BTN_TR_IO_3) {
		pDY2->oInspCMAlign2In = FALSE;
		pDY2->oInspCMAlign2Out = TRUE;
	} else if (nID == IDC_BTN_TR_IO_4) {
		pDY2->oInspCMAlign3In = TRUE;
		pDY2->oInspCMAlign3Out = FALSE;
	} else if (nID == IDC_BTN_TR_IO_5) {
		pDY2->oInspCMAlign3In = FALSE;
		pDY2->oInspCMAlign3Out = TRUE;
	} else if (nID == IDC_BTN_TR_IO_6) {
		pDY2->oInspCMAlign4In = TRUE;
		pDY2->oInspCMAlign4Out = FALSE;
	} else if (nID == IDC_BTN_TR_IO_7) {
		pDY2->oInspCMAlign4In = FALSE;
		pDY2->oInspCMAlign4Out = TRUE;
	} else if (nID == IDC_BTN_TR_IO_8) {
		pDY2->oInspVacuumUp = TRUE;
		pDY2->oInspVacuumDown = FALSE;
	} else if (nID == IDC_BTN_TR_IO_9) {
		pDY2->oInspVacuumUp = FALSE;
		pDY2->oInspVacuumDown = TRUE;
	} else if (nID == IDC_BTN_TR_IO_10) {
		pDY2->oInspCMAlign1In = TRUE;
		pDY2->oInspCMAlign1Out = FALSE;
		pDY2->oInspCMAlign2In = TRUE;
		pDY2->oInspCMAlign2Out = FALSE;
		pDY2->oInspCMAlign3In = TRUE;
		pDY2->oInspCMAlign3Out = FALSE;
		pDY2->oInspCMAlign4In = TRUE;
		pDY2->oInspCMAlign4Out = FALSE;
		pAJinAXL->Write_Output(2);
		return;
	} else if (nID == IDC_BTN_TR_IO_11) {
		pDY2->oInspCMAlign1In = FALSE;
		pDY2->oInspCMAlign1Out = TRUE;
		pDY2->oInspCMAlign2In = FALSE;
		pDY2->oInspCMAlign2Out = TRUE;
		pDY2->oInspCMAlign3In = FALSE;
		pDY2->oInspCMAlign3Out = TRUE;
		pDY2->oInspCMAlign4In = FALSE;
		pDY2->oInspCMAlign4Out = TRUE;
		pAJinAXL->Write_Output(2);
		return;
	} else if (nID == IDC_BTN_TR_IO_12) {
		pDY5->oNGVacuumUp = TRUE;
		pDY5->oNGVacuumDown = FALSE;
		pAJinAXL->Write_Output(5);
		return;
	} else if (nID == IDC_BTN_TR_IO_13) {
		pDY5->oNGVacuumUp = FALSE;
		pDY5->oNGVacuumDown = TRUE;
		pAJinAXL->Write_Output(5);
		return;
	} else if (nID == IDC_BTN_TR_IO_14) {
		pDY5->oGoodVacuumUp = TRUE;
		pDY5->oGoodVacuumDown = FALSE;
		pAJinAXL->Write_Output(5);
		return;
	} else if (nID == IDC_BTN_TR_IO_15) {
		pDY5->oGoodVacuumUp = FALSE;
		pDY5->oGoodVacuumDown = TRUE;
		pAJinAXL->Write_Output(5);
		return;
	}

	pAJinAXL->Write_Output(2);
}

void CManualIndexDlg::OnBnClickedBtnPressUp()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();
	DY_DATA_2 *pDY2 = pAJinAXL->Get_pDY2();

	if (!pAJinAXL->Is_Home(AX_INSPECTION_Z)) return;
	if (!pCommon->Check_MainDoor()) return;

	if (!pCommon->Check_Position(AX_INSPECTION_Z, 1) ) {
		AfxMessageBox(_T("Inspection Z축이 Up일 경우만 가능합니다.............."));
		return;
	}

	pDY2->oCMPressUp = TRUE;
	pDY2->oCMPressDn = FALSE;
	pAJinAXL->Write_Output(2);
}


void CManualIndexDlg::OnBnClickedBtnPressDown()
{
	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	CCommon *pCommon = CCommon::Get_Instance();
	DY_DATA_2 *pDY2 = pAJinAXL->Get_pDY2();

	if (!pCommon->Check_MainDoor()) return;

	pDY2->oCMPressUp = FALSE;
	pDY2->oCMPressDn = TRUE;
	pAJinAXL->Write_Output(2);

}
