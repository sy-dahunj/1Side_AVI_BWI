// SetupModelDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "SetupModelDlg.h"
#include "afxdialogex.h"

#include "DataManager.h"
#include "Common.h"
#include "LogFile.h"
#include "MESInterface.h"

// CSetupModelDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupModelDlg, CDialogEx)

CSetupModelDlg::CSetupModelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupModelDlg::IDD, pParent)
{
}

CSetupModelDlg::~CSetupModelDlg()
{
}

void CSetupModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	DDX_Control(pDX, IDC_LABEL_10, m_Label[10]);

	DDX_Control(pDX, IDC_STC_CURRENT_MODEL, m_stcCurrentModel);
	DDX_Control(pDX, IDC_LST_MODEL_LIST, m_lstModelList);
	DDX_Control(pDX, IDC_BTN_MODEL_INSERT, m_btnModelInsert);
	DDX_Control(pDX, IDC_BTN_MODEL_DELETE, m_btnModelDelete);
	DDX_Control(pDX, IDC_BTN_MODEL_CHANGE, m_btnModelChange);
	DDX_Control(pDX, IDC_STC_SELECT_MODEL, m_stcSelectModel);

	DDX_Control(pDX, IDC_STC_PKG_X_COUNT, m_stcPkgXCount);
	DDX_Control(pDX, IDC_STC_PKG_Y_COUNT, m_stcPkgYCount);
	DDX_Control(pDX, IDC_STC_TRAY_PITCH_L, m_stcPitchL);
	DDX_Control(pDX, IDC_STC_TRAY_PITCH_W, m_stcPitchW);

	DDX_Control(pDX, IDC_STC_TRAY_FIRST_L, m_stcTrayFirstL);
	DDX_Control(pDX, IDC_STC_TRAY_FIRST_W, m_stcTrayFirstW);
	DDX_Control(pDX, IDC_STC_CM_W,         m_stcCMWsize);
	DDX_Control(pDX, IDC_STC_CM_COUNT,     m_stcCMCount);

	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CSetupModelDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(IDC_LST_MODEL_LIST, &CSetupModelDlg::OnLbnSelchangeLstModelList)
	ON_BN_CLICKED(IDC_BTN_MODEL_INSERT, &CSetupModelDlg::OnBnClickedBtnModelInsert)
	ON_BN_CLICKED(IDC_BTN_MODEL_DELETE, &CSetupModelDlg::OnBnClickedBtnModelDelete)
	ON_BN_CLICKED(IDC_BTN_MODEL_CHANGE, &CSetupModelDlg::OnBnClickedBtnModelChange)
	ON_STN_CLICKED(IDC_STC_PKG_X_COUNT, &CSetupModelDlg::OnStnClickedStcPkgXCount)
	ON_STN_CLICKED(IDC_STC_PKG_Y_COUNT, &CSetupModelDlg::OnStnClickedStcPkgYCount)

	ON_STN_CLICKED(IDC_STC_TRAY_PITCH_L, &CSetupModelDlg::OnStnClickedStcPitchL)
	ON_STN_CLICKED(IDC_STC_TRAY_PITCH_W, &CSetupModelDlg::OnStnClickedStcPitchW)

	ON_STN_CLICKED(IDC_STC_TRAY_FIRST_L, &CSetupModelDlg::OnStnClickedstcTrayFirstL)
	ON_STN_CLICKED(IDC_STC_TRAY_FIRST_W, &CSetupModelDlg::OnStnClickedStcTrayFirstW)
	ON_STN_CLICKED(IDC_STC_CM_W,		&CSetupModelDlg::OnStnClickedStcCMWsize)
	ON_STN_CLICKED(IDC_STC_CM_COUNT,	&CSetupModelDlg::OnStnClickedStcCMCount)

	ON_BN_CLICKED(IDC_BTN_SAVE, &CSetupModelDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSetupModelDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()

// CSetupModelDlg 메시지 처리기입니다.

BOOL CSetupModelDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 150, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSetupModelDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CSetupModelDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupModelDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		CDataManager *pDataManager = CDataManager::Get_Instance();
		MODEL_DATA *pModelData = pDataManager->Get_pModelData();

		m_stcCurrentModel.SetWindowText(pModelData->sModelName);
		Display_ModelList();
		int nIdx = m_lstModelList.FindStringExact(0, pModelData->sModelName);
		m_lstModelList.SetCurSel(nIdx);
		OnLbnSelchangeLstModelList();
	}
}

void CSetupModelDlg::OnLbnSelchangeLstModelList()
{
	int nSelect = m_lstModelList.GetCurSel();
	CString strModel;
	m_lstModelList.GetText(nSelect, strModel);
	m_stcSelectModel.SetWindowText(strModel);
	Display_ModelData(strModel);
}

void CSetupModelDlg::OnBnClickedBtnModelInsert()
{
	CString strOrigin, strTarget, strTemp;

	CCommon *pCommon = CCommon::Get_Instance();
	CString strKey;
	if (pCommon->Show_KeyPad(strKey) == IDOK) {
		m_stcSelectModel.GetWindowText(strTemp);
		strOrigin.Format("Model/%s.ini", strTemp);
		strTarget.Format("Model/%s.ini", strKey);

		if (!CopyFile(strOrigin, strTarget, TRUE)) {
			CCommon *pCommon = CCommon::Get_Instance();
			pCommon->Show_MsgBox(1, "A model that already exists.");
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////
#ifdef MOVE_DATA_COPY
		strTarget.Format("Model\\%s\\", strKey);
		pCommon->MakeFolder(strTarget);	// 새로운 모델 폴더 생성

		strTarget.Format("Model/%s/MoveData_0.ini", strKey);
		strOrigin.Format("System/MoveData_0.ini");

		if (!CopyFile(strOrigin, strTarget, FALSE)) {	// 새로운 모델 폴더에 Move Data 복사
			pCommon->Show_MsgBox(1, "Move data file copy fail.");
			return;
		}
#endif
		//////////////////////////////////////////////////////////////////////////////////

		Display_ModelList();
		int nIdx = m_lstModelList.FindStringExact(0, strKey);
		m_lstModelList.SetCurSel(nIdx);
		OnLbnSelchangeLstModelList();
	}
}

void CSetupModelDlg::OnBnClickedBtnModelDelete()
{
	CString strCurrentModel, strSelectModel;
	m_stcCurrentModel.GetWindowText(strCurrentModel);
	m_stcSelectModel.GetWindowText(strSelectModel);

	CCommon *pCommon = CCommon::Get_Instance();
	if (strCurrentModel == strSelectModel) {
		pCommon->Show_MsgBox(1, "Working model can not be deleted.");
		return;
	} else {
		if (pCommon->Show_MsgBox(2, "Are you sure you want to delete the selected model?") == IDOK) {
			CString strDelete;
			strDelete.Format("Model/%s.ini", strSelectModel);
			DeleteFile(strDelete);

			Display_ModelList();
			int nIdx = m_lstModelList.FindStringExact(0, strCurrentModel);
			m_lstModelList.SetCurSel(nIdx);
			OnLbnSelchangeLstModelList();
			Display_ModelList();

			// Folder Data Delete ////////////////////////////////////////
#ifdef MOVE_DATA_COPY
			strDelete.Format("Model/%s/MoveData_0.ini", strSelectModel);
			DeleteFile(strDelete);	// File Delete

			CFileFind Finder;
			strDelete.Format("Model/%s/*.ini", strSelectModel);
			BOOL bContinue = Finder.FindFile(strDelete, NULL);
			int nTimeOut = GetTickCount();
			while (bContinue) {	// Check File Delete 
				if (GetTickCount()-nTimeOut > 5000) {
					pCommon->Show_MsgBox(1, "File delete fail.");
					break;
				}
				bContinue = Finder.FindFile(strDelete, NULL);
				pCommon->DoEvents(10);
			}

			strDelete.Format("Model/%s", strSelectModel);
			RemoveDirectory(strDelete);
#endif
			//////////////////////////////////////////////////////////////
		}
	}
}

void CSetupModelDlg::OnBnClickedBtnModelChange()
{
	CString strCurrentModel, strSelectModel;
	m_stcCurrentModel.GetWindowText(strCurrentModel);
	m_stcSelectModel.GetWindowText(strSelectModel);

	CCommon *pCommon = CCommon::Get_Instance();
	if (strCurrentModel == strSelectModel) {
		pCommon->Show_MsgBox(1, "The selected model is currently working model.");
		return;
	} else {
		if (pCommon->Show_MsgBox(2, "Do you want to replace the selected model as a working model?") == IDOK) {
			//////////////////////////////////////////////////////////////////////////////////////////
#ifdef MOVE_DATA_COPY
			CString strOrigin, strTarget, strTemp;

			strOrigin.Format("Model/%s/MoveData_0.ini", strSelectModel);
			strTarget.Format("System/MoveData_0.ini");

			// 파일 유무 확인
			if (PathFileExists(strOrigin)) {
				if (!CopyFile(strOrigin, strTarget, FALSE)) {	// 바뀌는 모델 Move Data로 덮어씌워 준다.
					pCommon->Show_MsgBox(1, "Move data file copy fail.");
					return;
				}
			} else {
				strTarget.Format("Model/%s/MoveData_0.ini", strSelectModel);
				strOrigin.Format("System/MoveData_0.ini");

				if (!CopyFile(strOrigin, strTarget, FALSE)) {	// 모델 폴더에 Move Data가 없으면 기존 Data로 복사해놓는다.
					pCommon->Show_MsgBox(1, "Move data file copy fail.");
				}
			}
#endif
			//////////////////////////////////////////////////////////////////////////////////////////

			CIniFileCS INI("System/EquipData.ini");
			INI.Set_String("MODEL", "CURRENT", strSelectModel);

			CDataManager *pDataManager = CDataManager::Get_Instance();
			pDataManager->Read_EquipData();
			pDataManager->Read_ModelData();
			pDataManager->Read_MoveData();

			MODEL_DATA *pModelData = pDataManager->Get_pModelData();
			m_stcCurrentModel.SetWindowText(pModelData->sModelName);

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

			Display_ModelList();
			int nIdx = m_lstModelList.FindStringExact(0, pModelData->sModelName);
			m_lstModelList.SetCurSel(nIdx);
			OnLbnSelchangeLstModelList();
		}
	}
}

void CSetupModelDlg::OnStnClickedStcPkgXCount()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcPkgXCount.GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcPkgXCount.SetWindowText(strNew);

		int nCount = atoi(strNew);
		if (nCount < 2 || nCount > 20) {
			CCommon *pCommon = CCommon::Get_Instance();
			pCommon->Show_MsgBox(1, " Array L Count Error. (2~20)");
			return;
		}
	}
}

void CSetupModelDlg::OnStnClickedStcPkgYCount()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcPkgYCount.GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcPkgYCount.SetWindowText(strNew);

		int nCount = atoi(strNew);
		if (nCount < 2 || nCount > 20) {
			CCommon *pCommon = CCommon::Get_Instance();
			pCommon->Show_MsgBox(1, " Array W Count Error. (2~20)");
			return;
		}
	}
}

void CSetupModelDlg::OnStnClickedStcPitchL()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcPitchL.GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcPitchL.SetWindowText(strNew);

		double dData = atof(strNew);
		if (dData < 5) {
			CCommon *pCommon = CCommon::Get_Instance();
			pCommon->Show_MsgBox(1, "  Tray Pitch L Error. (5~)");
			return;
		}
	}
}

void CSetupModelDlg::OnStnClickedStcPitchW()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcPitchW.GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcPitchW.SetWindowText(strNew);

		double dData = atof(strNew);
		if (dData < 5) {
			CCommon *pCommon = CCommon::Get_Instance();
			pCommon->Show_MsgBox(1, "  Tray Pitch W Error. (5~)");
			return;
		}
	}
}

void CSetupModelDlg::OnStnClickedstcTrayFirstL()
{

	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcTrayFirstL.GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcTrayFirstL.SetWindowText(strNew);

		double dData = atof(strNew);
		if (dData < 5) {
			CCommon *pCommon = CCommon::Get_Instance();
			pCommon->Show_MsgBox(1, "  Unload Tray Pitch L Error. (5~)");
			return;
		}
	}
}
void CSetupModelDlg::OnStnClickedStcTrayFirstW()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcTrayFirstW.GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcTrayFirstW.SetWindowText(strNew);

		double dData = atof(strNew);
		if (dData < 5) {
			CCommon *pCommon = CCommon::Get_Instance();
			pCommon->Show_MsgBox(1, "  Unload Tray Pitch W Error. (5~)");
			return;
		}
	}
}

void CSetupModelDlg::OnStnClickedStcCMWsize()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcCMWsize.GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcCMWsize.SetWindowText(strNew);

		double dData = atof(strNew);
		if (dData < 5) {
			CCommon *pCommon = CCommon::Get_Instance();
			pCommon->Show_MsgBox(1, "  CM W Size Error. (5~)");
			return;
		}
	}
}
void CSetupModelDlg::OnStnClickedStcCMCount()
{
	CCommon *pCommon = CCommon::Get_Instance();
	CString strOld, strNew;
	m_stcCMCount.GetWindowText(strOld);
	if (pCommon->Show_NumPad(strOld, strNew) == IDOK) {
		m_stcCMCount.SetWindowText(strNew);

		int nCount = atoi(strNew);
		if (nCount < 10) {
			CCommon *pCommon = CCommon::Get_Instance();
			pCommon->Show_MsgBox(1, " CM Use Max Count Error. (10~)");
			return;
		}
	}
}

void CSetupModelDlg::OnBnClickedBtnSave()
{
	CString strSection, strData;
	int nDataL, nDataW, nCMCount;
	double dDataL, dDataW, dTrayFirstLData, dTrayFirstWData, dCMWSizeData;


	m_stcPkgXCount.GetWindowText(strData); g_objMES.Save_AviRmsData("ARRAY_L_COUNT", strData);
	nDataL = atoi(strData);
	m_stcPkgYCount.GetWindowText(strData); g_objMES.Save_AviRmsData("ARRAY_W_COUNT", strData);
	nDataW = atoi(strData);
	m_stcPitchL.GetWindowText(strData); g_objMES.Save_AviRmsData("TRAY_L_PITCH", strData);
	dDataL = atof(strData);
	m_stcPitchW.GetWindowText(strData); g_objMES.Save_AviRmsData("TRAY_W_PITCH", strData);
	dDataW = atof(strData);

	m_stcTrayFirstL.GetWindowText(strData); g_objMES.Save_AviRmsData("UNLOAD_L_PITCH", strData);
	dTrayFirstLData = atof(strData);
	m_stcTrayFirstW.GetWindowText(strData); g_objMES.Save_AviRmsData("UNLOAD_W_PITCH", strData);
	dTrayFirstWData = atof(strData);
	m_stcCMWsize.GetWindowText(strData); g_objMES.Save_AviRmsData("CM_W_SIZE", strData);
	dCMWSizeData = atof(strData);
	m_stcCMCount.GetWindowText(strData);
	nCMCount = atoi(strData);

	//if (nDataL < 5 || nDataL > 6) {
	//	CCommon *pCommon = CCommon::Get_Instance();
	//	pCommon->Show_MsgBox(1, " Array L Count Error. (5~6)");
	//	return;
	//}
	//if (nDataW < 6 || nDataW > 10) {
	//	CCommon *pCommon = CCommon::Get_Instance();
	//	pCommon->Show_MsgBox(1, " Array W Count Error. (6~10)");
	//	return;
	//}
	//if (dDataL < 20 || dDataL > 30) {
	//	CCommon *pCommon = CCommon::Get_Instance();
	//	pCommon->Show_MsgBox(1, "  Tray Pitch L Error. (20~30)");
	//	return;
	//}
	//if (dDataW < 20 || dDataW > 30) {
	//	CCommon *pCommon = CCommon::Get_Instance();
	//	pCommon->Show_MsgBox(1, "  Tray Pitch W Error. (20~30)");
	//	return;
	//}


	CString strSelectModel;
	m_stcSelectModel.GetWindowText(strSelectModel);

	CString strModelFile;
	strModelFile.Format("Model/%s.ini", strSelectModel);

	CIniFileCS INI(strModelFile);

	strSection = "MODEL_DATA";
	INI.Set_Integer(strSection, "ARRAY_L_COUNT", nDataL);
	INI.Set_Integer(strSection, "ARRAY_W_COUNT", nDataW);
	INI.Set_Double(strSection, "TRAY_L_PITCH", dDataL, "%0.3lf");
	INI.Set_Double(strSection, "TRAY_W_PITCH", dDataW, "%0.3lf");
	INI.Set_Double(strSection, "TRAY_FIRST_L", 0.0, "%0.3lf");
	INI.Set_Double(strSection, "TRAY_FIRST_W", 0.0, "%0.3lf");
	INI.Set_Double(strSection, "UNLOAD_L_PITCH", dTrayFirstLData, "%0.3lf");
	INI.Set_Double(strSection, "UNLOAD_W_PITCH", dTrayFirstWData, "%0.3lf");
	INI.Set_Double(strSection, "CM_W_SIZE", dCMWSizeData,  "%0.3lf");
	INI.Set_Integer(strSection, "CM_MAX_COUNT", nCMCount);

	CDataManager *pDataManager = CDataManager::Get_Instance();
	MODEL_DATA *pModelData = pDataManager->Get_pModelData();
	if (strSelectModel == pModelData->sModelName) {
		pDataManager->Read_EquipData();
		pDataManager->Read_ModelData();
		pDataManager->Read_MoveData();
	}

	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog("[Setup - Model Dialog] save");

	Display_ModelData(strSelectModel);
}

void CSetupModelDlg::OnBnClickedBtnCancel()
{
	CString strSelectModel;
	m_stcSelectModel.GetWindowText(strSelectModel);

	Display_ModelData(strSelectModel);

}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupModelDlg::Initial_Controls() 
{
	m_Group[0].Init_Ctrl("바탕", 15, TRUE, RGB(0x10, 0x50, 0x40), COLOR_DEFAULT);
	m_Group[1].Init_Ctrl("바탕", 15, TRUE, RGB(0x80, 0x20, 0x30), COLOR_DEFAULT);
	for (int i = 0; i < 3; i++) m_Label[i].Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 3; i < 12; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	m_stcCurrentModel.Init_Ctrl("바탕", 24, TRUE, RGB(0xFF, 0x00, 0x00), RGB(0xFF, 0xB0, 0xB0));

	m_lstModelList.Init_Ctrl("바탕", 20, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xFF));

	m_btnModelInsert.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0xA0, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnModelDelete.Init_Ctrl("바탕", 15, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnModelChange.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);

	m_stcSelectModel.Init_Ctrl("바탕", 24, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xF0, 0xFF, 0x90));

	m_stcPkgXCount.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	m_stcPkgYCount.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));

	m_stcPitchL.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	m_stcPitchW.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));

	m_stcTrayFirstL.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	m_stcTrayFirstW.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	m_stcCMWsize.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	m_stcCMCount.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));

	m_btnSave.Init_Ctrl("바탕", 15, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnCancel.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
}

void CSetupModelDlg::Display_ModelList()
{
	m_lstModelList.ResetContent();

	CString strModelFile;
	int nFileLength;

	CFileFind Finder;
	
	BOOL bContinue = Finder.FindFile("Model/*.ini", NULL);
	while (bContinue) {
		bContinue = Finder.FindNextFile();
		if (Finder.IsDots()) continue;
		else if (Finder.IsDirectory()) continue;
		else {
			strModelFile = Finder.GetFileName();
			nFileLength = strModelFile.GetLength() - 4;
			m_lstModelList.AddString(strModelFile.Left(nFileLength));
		}
	}
}

void CSetupModelDlg::Display_ModelData(CString sModel)
{
	CString strModelFile;
	strModelFile.Format("Model/%s.ini", sModel);

	CIniFileCS INI(strModelFile);

	CString strSection, strData;
	int nData;
	double dData;

	strSection = "MODEL_DATA";

	nData = INI.Get_Integer(strSection, "ARRAY_L_COUNT", 0);
	strData.Format("%d", nData);
	m_stcPkgXCount.SetWindowText(strData);

	nData = INI.Get_Integer(strSection, "ARRAY_W_COUNT", 0);
	strData.Format("%d", nData);
	m_stcPkgYCount.SetWindowText(strData);

	dData = INI.Get_Double(strSection, "TRAY_L_PITCH", 0.0);
	strData.Format("%0.3lf", dData);
	m_stcPitchL.SetWindowText(strData);

	dData = INI.Get_Double(strSection, "TRAY_W_PITCH", 0.0);
	strData.Format("%0.3lf", dData);
	m_stcPitchW.SetWindowText(strData);

	dData = INI.Get_Double(strSection, "UNLOAD_L_PITCH", 0.0);
	strData.Format("%0.3lf", dData);
	m_stcTrayFirstL.SetWindowText(strData);

	dData = INI.Get_Double(strSection, "UNLOAD_W_PITCH", 0.0);
	strData.Format("%0.3lf", dData);
	m_stcTrayFirstW.SetWindowText(strData);
/*
	dData = INI.Get_Double(strSection, "TRAY_FIRST_L", 0.0);
	strData.Format("%0.3lf", dData);
	m_stcTrayFirstL.SetWindowText(strData);

	dData = INI.Get_Double(strSection, "TRAY_FIRST_W", 0.0);
	strData.Format("%0.3lf", dData);
	m_stcTrayFirstW.SetWindowText(strData);
*/
	dData = INI.Get_Double(strSection, "CM_W_SIZE", 0.0);
	strData.Format("%0.3lf", dData);
	m_stcCMWsize.SetWindowText(strData);

	nData = INI.Get_Integer(strSection, "CM_MAX_COUNT", 0);
	strData.Format("%d", nData);
	m_stcCMCount.SetWindowText(strData);
}

void CSetupModelDlg::Set_ModelChange(CString sModel)
{
	if (sModel.GetLength() != 3) return;

	CIniFileCS INI("System/EquipData.ini");
	INI.Set_String("MODEL", "CURRENT", sModel);

	//////////////////////////////////////////////////////////////////////////////////////////
#ifdef MOVE_DATA_COPY
	CString strOrigin, strTarget, strTemp;

	strOrigin.Format("Model/%s/MoveData_0.ini", sModel);
	strTarget.Format("System/MoveData_0.ini");

	if (!CopyFile(strOrigin, strTarget, FALSE)) {	// 바뀌는 모델 Move Data로 덮어씌워 준다.
		CCommon *pCommon = CCommon::Get_Instance();
		pCommon->Show_MsgBox(1, "Move data file copy fail.");
		return;
	}
#endif
	//////////////////////////////////////////////////////////////////////////////////////////

	CDataManager *pDataManager = CDataManager::Get_Instance();
	pDataManager->Read_EquipData();
	pDataManager->Read_ModelData();
	pDataManager->Read_MoveData();

	MODEL_DATA *pModelData = pDataManager->Get_pModelData();
	m_stcCurrentModel.SetWindowText(pModelData->sModelName);

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

}
///////////////////////////////////////////////////////////////////////////////
