// ErrorDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "ErrorDlg.h"
#include "afxdialogex.h"

#include "CMI4200LDlg.h"
#include "Inspector.h"
#include "AJinAXL.h"
#include "Common.h"
#include "LogFile.h"
#include "SequenceMain.h"
#include "MESInterface.h"

// CErrorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CErrorDlg, CDialogEx)

CErrorDlg *CErrorDlg::m_pInstance = NULL;

CErrorDlg *CErrorDlg::Get_Instance(CWnd *pParent)
{
	if (!m_pInstance) {
		m_pInstance = new CErrorDlg(pParent);
		if (!m_pInstance->m_hWnd) {
			m_pInstance->Create(IDD_ERROR_DLG, pParent);
		}
	}
	return m_pInstance;
}

void CErrorDlg::Delete_Instance()
{
	if (m_pInstance->m_hWnd) m_pInstance->DestroyWindow();
	if (m_pInstance) delete m_pInstance;
	m_pInstance = NULL;
}

CErrorDlg::CErrorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CErrorDlg::IDD, pParent)
{
}

CErrorDlg::~CErrorDlg()
{
}

void CErrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_ERR_BACK_0 + i, m_stcErrBack[i]);
	DDX_Control(pDX, IDC_STC_ERR_TITLE, m_stcErrTitle);
	DDX_Control(pDX, IDC_IMAGE_0, m_Image);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_STC_ERR_POS_0 + i, m_stcErrPos[i]);
	DDX_Control(pDX, IDC_STC_ERR_NO, m_stcErrNo);
	DDX_Control(pDX, IDC_STC_ERR_MSG, m_stcErrMsg);
	DDX_Control(pDX, IDC_BTN_BUZZER_OFF, m_btnBuzzerOff);
	DDX_Control(pDX, IDC_BTN_ERR_SKIP, m_btnErrSkip);
	DDX_Control(pDX, IDC_BTN_ERR_RETRY, m_btnErrRetry);
	DDX_Control(pDX, IDC_BTN_ERR_OK, m_btnErrOK);
	DDX_Control(pDX, IDC_BTN_SYSTEM_EXIT, m_btnSystemExit);
}

BEGIN_MESSAGE_MAP(CErrorDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_BUZZER_OFF, &CErrorDlg::OnBnClickedBtnBuzzerOff)
	ON_BN_CLICKED(IDC_BTN_ERR_SKIP, &CErrorDlg::OnBnClickedBtnErrSkip)
	ON_BN_CLICKED(IDC_BTN_ERR_RETRY, &CErrorDlg::OnBnClickedBtnErrRetry)
	ON_BN_CLICKED(IDC_BTN_ERR_OK, &CErrorDlg::OnBnClickedBtnErrOk)
	ON_BN_CLICKED(IDC_BTN_SYSTEM_EXIT, &CErrorDlg::OnBnClickedBtnSystemExit)
END_MESSAGE_MAP()

// CErrorDlg 메시지 처리기입니다.

BOOL CErrorDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetForegroundWindow();
	SetActiveWindow();
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

	Initial_Controls();

	m_nErrNo = 0;
	m_nBackColorLoop = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CErrorDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CErrorDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CErrorDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		CString strErrNo, strLog, strLine, sTotLog;

		gData.m_bErrorShow = TRUE;
		strErrNo.Format("%04d", m_nErrNo);
		m_stcErrNo.SetWindowText(strErrNo);
		
		Load_ErrorImage(m_nErrNo);

		CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();
		CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
		DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();

		strLog = "";
		if(m_nErrNo < 9999) {
			CIniFileCS Ini("System/ErrorList.ini");
			sTotLog = Ini.Get_String("ERROR", strErrNo, "");
		
			if (m_nErrNo == 8300) {
				int nUL1 = pSequenceMain->Get_RunCase(AUTO_UNLOAD1);
				int nUL2 = pSequenceMain->Get_RunCase(AUTO_UNLOAD2);
				strLog.Format("==> UL Stage1 Case No.[%d]. UL Stage2 Case No.[%d].", nUL1, nUL2);

			} else if(m_nErrNo == 5150 || m_nErrNo == 5250 || m_nErrNo == 5151 || m_nErrNo == 5251) {
				strLog.Format("Error NG Picker Down.... Picker_No[%d] Index_No[%d]", gData.NGPicNo, gData.NGIdxNo);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if (m_nErrNo == 5162 || m_nErrNo == 5166) {
				strLog.Format("Error NG Picker Close... Picker_No[%d] Index_No[%d]", gData.NGPicNo, gData.NGIdxNo);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if (m_nErrNo == 5170 || m_nErrNo == 5270 || m_nErrNo == 5171 || m_nErrNo == 5271) {
				strLog.Format("Error NG Picker Up.... Picker_No[%d] Index_No[%d]", gData.NGPicNo, gData.NGIdxNo);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if (m_nErrNo == 5260 || m_nErrNo == 5261) {
				strLog.Format("Error NG Picker Open... Picker_No[%d] Index_No[%d]", gData.NGPicNo, gData.NGIdxNo);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if (m_nErrNo == 5180 || m_nErrNo == 5240 || m_nErrNo == 5181 || m_nErrNo == 5241) {
				strLog.Format("Error NG CM Check... Picker_No[%d] Index_No[%d]", gData.NGPicNo, gData.NGIdxNo);
			} else if (m_nErrNo == 5301) {
				strLog.Format("Error NG CM Check = Off... Picker_No[%d]", gData.nPicNo);
			} else if(m_nErrNo == 5220 || m_nErrNo == 5222) {
				strLog.Format("NG Picker.. Picker_No[%d] Index_No[%d] Tray[%d]", gData.NGPicNo, gData.NGIdxNo, gData.nNGTrayPos);

			} else if(m_nErrNo == 6150 || m_nErrNo == 6240 || m_nErrNo == 6310) {
				strLog.Format("Error Good Picker Down.... Picker_No[%d] Index_No[%d]", gData.GDPicNo, gData.GDIdxNo);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if (m_nErrNo == 6162 || m_nErrNo == 6322) {
				strLog.Format("Error Good Picker Close... Picker_No[%d] Index_No[%d]", gData.GDPicNo, gData.GDIdxNo);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if (m_nErrNo == 6170 || m_nErrNo == 6260 || m_nErrNo == 6330) {
				strLog.Format("Error Good Picker Up.... Picker_No[%d] Index_No[%d]", gData.GDPicNo, gData.GDIdxNo);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if (m_nErrNo == 6250) {
				strLog.Format("Error Good Picker Open... Picker_No[%d] Index_No[%d]", gData.GDPicNo, gData.GDIdxNo);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if (m_nErrNo == 6180 || m_nErrNo == 6230 || m_nErrNo == 6340) {
				strLog.Format("Error Good CM Check... Picker_No[%d] Index_No[%d]", gData.GDPicNo, gData.GDIdxNo);
				//m_stcErrMsg.SetWindowText(strLog);

			} else if(m_nErrNo == 7140 || m_nErrNo == 7150 || m_nErrNo == 7201 || m_nErrNo == 7220) {
				strLog.Format("==> Load Picker_No[%d]", gData.nPicNo);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if(m_nErrNo == 8142 || m_nErrNo == 8150 || m_nErrNo == 8170 || m_nErrNo == 8220 || m_nErrNo == 8250 || m_nErrNo == 8350 || m_nErrNo == 8370 || m_nErrNo == 8410) {
				strLog.Format("==> Unload Picker_No[%d]", gData.nPicNo);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if(m_nErrNo == 9140 || m_nErrNo == 9143) {
				strLog.Format("==> Vacuum Off_No[%d] Index_Position[%d]", gData.nPicNo, gData.nIndexPos);
				//m_stcErrMsg.SetWindowText(strLog);
			} else if(m_nErrNo == 9200) {
				strLog.Format("Index Sequence가 완료되지 않았습니다......");
				if (gData.nPicNo==1) strLog.Format("Load Sequence가 완료되지 않았습니다......");
				if (gData.nPicNo==2) strLog.Format("검사가 완료되지 않았습니다......");
				if (gData.nPicNo==3) strLog.Format("2D Barcode 검사가 완료되지 않았습니다......");
				if (gData.nPicNo==4) strLog.Format("NG Picker Sequence가 완료되지 않았습니다......");
				if (gData.nPicNo==5) strLog.Format("Good Picker Sequence가 완료되지 않았습니다......");
				if (gData.nPicNo==6) strLog.Format("Unload Picker Sequence가 완료되지 않았습니다......");
				if (gData.nPicNo==11) strLog.Format("Index Align 1번이 In 되었는지 확인해 주세요........");
				if (gData.nPicNo==12) strLog.Format("Index Align 2번이 In 되었는지 확인해 주세요........");
				if (gData.nPicNo==13) strLog.Format("Index Align 3번이 In 되었는지 확인해 주세요........");
				if (gData.nPicNo==14) strLog.Format("Index Align 4번이 In 되었는지 확인해 주세요........");
				//m_stcErrMsg.SetWindowText(strLog);
			} else if(m_nErrNo == 4300) {
				if (gData.nErrType==1) strLog.Format("==> 수량정보(CM 있음:O) - 검사결과(CM 없음:X)");
				if (gData.nErrType==2) strLog.Format("==> 수량정보(CM 없음:X) - 검사결과(CM 있음:O)");
				if (gData.nErrType==9) strLog.Format("==> 검사결과(Tray no 밎 수량 정보 Error.....)");
			} else if (m_nErrNo == 9950 || m_nErrNo == 9960) {	// 9950: 다발 불량, 9960: Barcode Shift 불량
				strLog = m_strErrSubMsg;
			}

			if(m_nErrNo > 990 && m_nErrNo < 995) {
				if(m_nErrNo == 992) { g_objMES.m_sReasonText.TrimRight(); strLog.Format("==> Reason[%s] Text[%s]..", g_objMES.m_sReasonCode, g_objMES.m_sReasonText); }
				if(m_nErrNo == 993) strLog.Format("==> User_LotID[%s] != MES_LotID[%s]..", gData.sLotID, g_objMES.m_sMESLotID);
				if(m_nErrNo == 994) strLog.Format("==> User_Count[%d] != MES_Count[%d]..", gData.nCMJobCount, g_objMES.m_nMESCount);
			}

			m_strErrMsg.Format("%s %s",sTotLog, strLog);
			m_stcErrMsg.SetWindowText(m_strErrMsg);

			// MTBA 계산
			//ErrorTimeEdit();
		} else {
			m_stcErrMsg.SetWindowText(m_strErrMsg);
		}

		CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
		CLogFile *pLogFile = CLogFile::Get_Instance();

		if (m_nErrNo != 9500) {	// NG Tray Full 에러는 로그에 남기지 않는다.
			strLog.Format(",%s,%s,%s", gLot.sLotID, strErrNo, m_strErrMsg);
			pLogFile->Save_AlarmLog(strLog);

			Set_ErrorLog(strErrNo, m_strErrMsg);
			pMainDlg->Set_LotErrorLog("ERROR", m_nErrNo, m_strErrMsg);
		}

		int nCase[12];
		pSequenceMain->Get_RunCase(nCase[0], nCase[1], nCase[2], nCase[3], nCase[4], nCase[5], nCase[6], nCase[7], nCase[8], nCase[9], nCase[10], nCase[11]);
		strLog.Format("[Error Mode] ==> (No : %s) Seq(%d-%d-%d-%d-%d  %d-%d-%d-%d-%d  %d-%d) (Ver: %s)", strErrNo, nCase[0], nCase[1], nCase[2], nCase[3], nCase[4], nCase[5], nCase[6], nCase[7], nCase[8], nCase[9], nCase[10], nCase[11], MAIN_VERSION);
		pLogFile->Save_HandlerLog(strLog);

		m_nBackColorLoop = 0;
		
		m_btnErrSkip.EnableWindow(FALSE);
		m_btnErrRetry.EnableWindow(FALSE);
		m_btnErrOK.EnableWindow(TRUE);

		if (m_nErrNo <= 20) {
			if (m_nErrNo >= 1 && m_nErrNo <= 6) {
				CSequenceInit *pSequenceInit = CSequenceInit::Get_Instance();
				pSequenceInit->Set_InitComplete(FALSE);
			}
			pMainDlg->Set_MainState(STATE_EMER);
		} else {
			pMainDlg->Set_MainState(STATE_ALARM);
		}
		g_objMES.Set_Alarm(1, m_nErrNo, m_strErrMsg);

		if (m_nErrNo > 1000 && m_nErrNo < 2000) {			// Initial Error
			if (m_nErrNo > 1100 && m_nErrNo < 1200) {

			} else if (m_nErrNo > 1200 && m_nErrNo < 1299) {	// Load
				m_stcErrPos[0].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
			} else if (m_nErrNo > 1300 && m_nErrNo < 1399) {	// Unload
				m_stcErrPos[8].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
			} else if (m_nErrNo > 1400 && m_nErrNo < 1499) {	// Elevator
				m_stcErrPos[5].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
			} else if (m_nErrNo > 1500 && m_nErrNo < 1599) {	// Gripper
				m_stcErrPos[2].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
			} else if (m_nErrNo > 1600 && m_nErrNo < 1699) {	// Picker
				m_stcErrPos[4].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
			} else if (m_nErrNo > 1700 && m_nErrNo < 1799) {	// Inspector
				m_stcErrPos[3].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
			} else if (m_nErrNo > 1800 && m_nErrNo < 1899) {	// Inspector
				m_stcErrPos[7].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
			} else if (m_nErrNo > 1900 && m_nErrNo < 1950) {	// Inspector
				m_stcErrPos[6].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
			} else if (m_nErrNo > 1950 && m_nErrNo < 1999) {	// Inspector
				m_stcErrPos[1].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
			}
		} else if (m_nErrNo > 2000 && m_nErrNo < 2999) {	// Loader Error
			m_stcErrPos[0].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
		} else if (m_nErrNo > 3000 && m_nErrNo < 3999) {	// Unloader Error
			m_stcErrPos[8].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
		} else if (m_nErrNo > 4000 && m_nErrNo < 4999) {	// Elevator Error
			m_stcErrPos[5].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
		} else if (m_nErrNo > 5000 && m_nErrNo < 5999) {	// Gripper Error
			m_stcErrPos[2].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
		} else if (m_nErrNo > 6000 && m_nErrNo < 6999) {	// Left Picker Error
			m_stcErrPos[4].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
		} else if (m_nErrNo > 7000 && m_nErrNo < 7999) {	// Right Picker Error
			m_stcErrPos[3].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
		} else if (m_nErrNo > 8000 && m_nErrNo < 8999) {	// Mold Error
			m_stcErrPos[7].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
		} else if (m_nErrNo > 9000 && m_nErrNo < 9500) {	// PCB Error
			m_stcErrPos[6].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
		} else if (m_nErrNo > 9500 && m_nErrNo < 9900) {	// 3D Error
			m_stcErrPos[1].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
		}

		CInspector *pInspector = CInspector::Get_Instance();
		pInspector->Set_StatusUpdate(INSPECTOR_VISION, 4);

		for(int i=1; i>=0; i--) {
			gData.sAlarmTime[i+1] = gData.sAlarmTime[i];
			gData.sAlarmList[i+1] = gData.sAlarmList[i];
		}
		SYSTEMTIME time;
		GetLocalTime(&time);

		gData.sAlarmTime[0].Format("%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
		gData.sAlarmList[0].Format("%s: %s", strErrNo, m_strErrMsg);

		SetTimer(0, 100, NULL);

	} else {
		for (int i = 0; i < 9; i++) m_stcErrPos[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));

		KillTimer(0);

		CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
		pMainDlg->Set_MainState(STATE_INITEND);
		g_objMES.Set_Alarm(2, m_nErrNo, m_strErrMsg);
		gData.m_bErrorShow = FALSE;
	}
}

void CErrorDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(0);

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();

	if (pDX0->iResetSw && m_nErrNo != 4300) {
		OnBnClickedBtnErrOk();
		return;
	}

	if (m_nBackColorLoop == 1) {
		for (int i = 0; i < 4; i++) m_stcErrBack[i].Set_Color(COLOR_DEFAULT, RGB(0x00, 0x00, 0xFF));
		for (int i = 0; i < 4; i++) m_stcErrBack[i].Invalidate(FALSE);

	} else if (m_nBackColorLoop == 6) {
		for (int i = 0; i < 4; i++) m_stcErrBack[i].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));
		for (int i = 0; i < 4; i++) m_stcErrBack[i].Invalidate(FALSE);

	} else if (m_nBackColorLoop == 10) m_nBackColorLoop = 0;

	m_nBackColorLoop++;

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CErrorDlg::OnBnClickedBtnBuzzerOff()
{
	gData.m_bBuzzerOff = TRUE;

	CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
	DY_DATA_0 *pDY0 = pAJinAXL->Get_pDY0();
	pDY0->oAlarmBuzzer1 = FALSE;
	pDY0->oAlarmBuzzer2 = FALSE;
	pAJinAXL->Write_Output(0);
}

void CErrorDlg::OnBnClickedBtnErrSkip()
{
/*
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Error Mode] SKIP button push");

	for(int i=0; i<gData.nErrCnt; i++) {
		int j = gData.nIndexY[i];
		if (gData.nErrType==1) gData.IndexInfo[gData.nIndexX][j] = 2;
		if (gData.nErrType==2) gData.IndexInfo[gData.nIndexX][j] = 0;
	}
*/
	ShowWindow(SW_HIDE);
}

void CErrorDlg::OnBnClickedBtnErrRetry()
{
/*
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Error Mode] RETRY button push");

	for(int i=0; i<gData.nErrCnt; i++) {
		int j = gData.nIndexY[i];
		if (gData.nErrType==1) gData.IndexInfo[gData.nIndexX][j] = 0;
		if (gData.nErrType==2) gData.IndexInfo[gData.nIndexX][j] = 2;
	}
*/
	ShowWindow(SW_HIDE);
}

void CErrorDlg::OnBnClickedBtnErrOk()
{
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Error Mode] OK button push");

	CSequenceMain *pSequenceMain = CSequenceMain::Get_Instance();

	if (m_nErrNo == 4170) pSequenceMain->Set_RunCase(AUTO_INSPECT, 150);
	if (m_nErrNo == 4370) pSequenceMain->Set_RunCase(AUTO_BARCODE, 150);
	if (m_nErrNo == 9500) {
		if (gData.nStatus < 3 && pSequenceMain->Check_NGTrayJobEnd()==TRUE) {
			pSequenceMain->Set_RunCase(AUTO_NGTRAY, 290);
			gData.nStatus = 3;
		}
 		else {
 			pSequenceMain->Set_RunCase(AUTO_NGTRAY, 100);
 		}
	}

	ShowWindow(SW_HIDE);
}

void CErrorDlg::OnBnClickedBtnSystemExit()
{
	CCommon *pCommon = CCommon::Get_Instance();
	//if (pCommon->Show_MsgBox(2, "프로그램을 종료하시겠습니까?") == IDOK) {
	if (pCommon->Show_MsgBox(2, "Are you sure you want to exit the program?") == IDOK) {
		CCMI4200LDlg *pMainDlg = (CCMI4200LDlg*)AfxGetApp()->m_pMainWnd;
		pMainDlg->Exit_System(EXIT_SYSTEM_NONE);
	}
}

void CErrorDlg::Set_ErrorLog(CString sErrNo, CString sErrMsg)
{
	SYSTEMTIME time;

	gAlm.nType = 1;
	gAlm.sLotID = gLot.sLotID;
	gAlm.sAlmNo = sErrNo;
	gAlm.sAlmMsg = sErrMsg;
	GetLocalTime(&time);
	gAlm.lStartTime = GetTickCount();
	gAlm.sStartTime.Format("%04d%02d%02d_%02d%02d%02d %03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
}

void CErrorDlg::ErrorTimeEdit()
{
	long lSTime, lETime, lTTime, laTime, lmax;
	if(m_nErrNo > 9900 || (m_nErrNo > 10 && m_nErrNo < 30) || (m_nErrNo > 1100 && m_nErrNo < 2000)) return;

	lmax = 4294960000;
	CIniFileCS Ini_LotData("System/LotData.ini");
	lSTime = Ini_LotData.Get_Long("TOTAL_DATA", "ERROR_STIME", 0);
	lTTime = Ini_LotData.Get_Long("TOTAL_DATA", "ERROR_MTIME", 0);

	lETime = GetTickCount();
	if(lETime >= lSTime) {
		laTime = lETime - lSTime;
	} else {
		laTime = lETime + (lmax - lSTime);
	}
	if (laTime < 1) return;

	if (lTTime <= 0) lTTime = laTime;
	else			 lTTime = (lTTime + laTime) / 2;

	Ini_LotData.Set_Long("TOTAL_DATA", "ERROR_STIME", lETime);
	Ini_LotData.Set_Long("TOTAL_DATA", "ERROR_MTIME", lTTime);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CErrorDlg::Initial_Controls() 
{
	for (int i = 0; i < 2; i++) m_Label[i].Init_Ctrl("바탕", 14, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 4; i++) m_stcErrBack[i].Set_Color(COLOR_DEFAULT, RGB(0x00, 0x00, 0xFF));

	m_stcErrTitle.Init_Ctrl("바탕", 24, TRUE, RGB(0xFF, 0xFF, 0xFF),RGB(0xFF, 0x00, 0x00));

	m_bmpImage.LoadBitmap(IDB_EQUIP_ERROR);
	m_Image.SetBitmap(m_bmpImage);
	m_Image.SetWindowPos(NULL, 0, 0, 630, 720, SWP_NOZORDER | SWP_NOMOVE);

	for (int i = 0; i < 9; i++) m_stcErrPos[i].Init_Ctrl("바탕", 12, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));

	m_stcErrNo.Init_Ctrl("바탕", 20, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xF0, 0xE0));
	m_stcErrMsg.Init_Ctrl("바탕", 18, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE0, 0xF0, 0xF0));

	m_btnBuzzerOff.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrSkip.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrRetry.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrOK.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_OK, CButtonCS::emLeft);
	m_btnSystemExit.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);

	Invalidate(TRUE);
}

void CErrorDlg::Load_ErrorImage(int nErrNo)
{
	for (int i = 0; i < 9; i++) m_stcErrPos[i].ShowWindow(FALSE);

	CString strImageDir = gsCurrentDir + "\\System\\Error_Image\\";
	CString strImagePath = "";
	strImagePath.Format("%s%04d.bmp", strImageDir, nErrNo);
	CImage img1;
	int dimx = 630, dimy = 720;
	HRESULT hResult = img1.Load(strImagePath);

	if(FAILED(hResult))
	{
		for (int i = 0; i < 9; i++) m_stcErrPos[i].ShowWindow(TRUE);

		m_Image.SetBitmap(m_bmpImage);
		m_Image.SetWindowPos(NULL, 0, 0, 630, 720, SWP_NOZORDER | SWP_NOMOVE);

		return;
	}

	CDC *screenDC = GetDC();
	CDC *pMDC = new CDC;
	pMDC->CreateCompatibleDC(screenDC);

	CBitmap *pb = new CBitmap;
	pb->CreateCompatibleBitmap(screenDC, dimx, dimy);

	CBitmap *pob = pMDC->SelectObject(pb);
	pMDC->SetStretchBltMode(HALFTONE);

	img1.BitBlt(pMDC->m_hDC,0,0,630,720,0,0,SRCCOPY); //hdc, 출력 x좌표, 출력 y좌표, 너비, 높이, 이미지 출력 x좌표, 이미지 출력 y좌표

	pMDC->SelectObject(pob);

	CImage new_image;
	new_image.Attach((HBITMAP)(*pb));
	m_Image.SetBitmap(new_image.Detach());
	ReleaseDC(screenDC);

}
///////////////////////////////////////////////////////////////////////////////
