// DataManager.cpp: 구현 파일
//
#include "stdafx.h"
#include "DataManager.h"
#include "LogFile.h"

CDataManager *CDataManager::m_pInstance = NULL;

CDataManager* CDataManager::Get_Instance()
{
	if (!m_pInstance)
		m_pInstance = new CDataManager();
	return m_pInstance;
}

void CDataManager::Delete_Instance()
{
	if (m_pInstance)
		delete m_pInstance;
	m_pInstance = NULL;
}

// CDataManager

CDataManager::CDataManager()
{
	Reset_EquipData();
	Reset_ModelData();
	Reset_MoveData();
}

CDataManager::~CDataManager()
{
}

void CDataManager::Reset_EquipData()
{
	m_EquipData.sCurrModel = "";
	m_EquipData.sEquipName = "";

	m_EquipData.bUseVisionInspect = FALSE;
	m_EquipData.bUseManagerMode = FALSE;
	m_EquipData.bUseBar2Alarm = FALSE;
	m_EquipData.bUseBar2NG = FALSE;
	m_EquipData.bUseMES = FALSE;
	m_EquipData.bUseMesApd = FALSE;
	m_EquipData.bUseDoorLock = FALSE;
	m_EquipData.bUseContinueLot = FALSE;

	m_EquipData.dMoldTrigPeriod = 10.0;
	m_EquipData.dMoldTrigWidth = 5.0;
	m_EquipData.dMoldScanOffset = 20.0;

}

void CDataManager::Reset_ModelData()
{
	m_ModelData.sModelName = "";
	m_ModelData.nStripSize = 0;
}

void CDataManager::Reset_MoveData()
{
	for (int i = 0; i < 5; i++) m_MoveData.dLoadTrayX1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dLoadTrayX2[i] = 0.0;
	for (int i = 0; i < 4; i++) m_MoveData.dLoadTrayZ1[i] = 0.0;
	for (int i = 0; i < 4; i++) m_MoveData.dLoadTrayZ2[i] = 0.0;
	for (int i = 0; i < 3; i++) m_MoveData.dLoadPickerY1[i] = 0.0;
	for (int i = 0; i < 4; i++) m_MoveData.dLoadPickerZ[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dLoadPickerY2[i] = 0.0;
	for (int i = 0; i < 8; i++) m_MoveData.dIndexR[i] = 0.0;
	for (int i = 0; i < 1; i++) m_MoveData.dBarCodeA[i] = 0.0;
	for (int i = 0; i < 1; i++) m_MoveData.dInspectionA[i] = 0.0; 
	for (int i = 0; i < 2; i++) m_MoveData.dInspectionZ[i] = 0.0;
	for (int i = 0; i < 8; i++) m_MoveData.dNGPickerX[i] = 0.0;
	for (int i = 0; i < 7; i++) m_MoveData.dNGPickerZ[i] = 0.0;
	for (int i = 0; i < 4; i++) m_MoveData.dNGStageY[i] = 0.0;
	for (int i = 0; i < 7; i++) m_MoveData.dGdPickerY[i] = 0.0; 
	for (int i = 0; i < 13; i++) m_MoveData.dGdPickerZ[i] = 0.0;  
	for (int i = 0; i < 3; i++) m_MoveData.dUnloadPickerX1[i] = 0.0;
	for (int i = 0; i < 4; i++) m_MoveData.dUnloadPickerZ[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dUnloadPickerX2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dUnloadTrayY1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dUnloadTrayY2[i] = 0.0;
	for (int i = 0; i < 4; i++) m_MoveData.dUnloadTrayZ1[i] = 0.0;
	for (int i = 0; i < 4; i++) m_MoveData.dUnloadTrayZ2[i] = 0.0;
}

BOOL CDataManager::Read_EquipData()
{
	CIniFileCS INI("System/EquipData.ini");
	if (!INI.Check_File()) return FALSE;

	CString strSection, strKey;

	strSection = "MODEL";
	m_EquipData.sCurrModel = INI.Get_String(strSection, "CURRENT", "");

	strSection = "OPTION";
	m_EquipData.sEquipName = INI.Get_String(strSection, "EQUIP_NAME", "");
	gData.sDeviceName = m_EquipData.sEquipName;

	m_EquipData.bUseVisionInspect = INI.Get_Bool(strSection, "VISION_INSPECT", FALSE);
	m_EquipData.bUseBar2Alarm = INI.Get_Bool(strSection, "BARCODE_ALARM", FALSE);
	gData.bUseBar2Alarm= m_EquipData.bUseBar2Alarm;
	m_EquipData.bUseBar2NG = INI.Get_Bool(strSection, "BARCODE_NG", FALSE);
	gData.bUseBar2NG= m_EquipData.bUseBar2NG;

	m_EquipData.bUseMES = INI.Get_Bool(strSection, "MES_USE", FALSE);
	m_EquipData.bUseMesApd = INI.Get_Bool(strSection, "MES_APD", FALSE);
	m_EquipData.bUseDoorLock = INI.Get_Bool(strSection, "DOOR_LOCK", FALSE);
	gData.bUseDoorLock= m_EquipData.bUseDoorLock;
	m_EquipData.bUseContinueLot = INI.Get_Bool(strSection, "CONTINUE_LOT", FALSE);
//	gCM.bMESLog = INI.Get_Bool(strSection, "MES_LOG", FALSE);

	m_EquipData.sLotBarcodePort = INI.Get_String(strSection, "LOT_BARCODE_PORT", "");
	m_EquipData.sNGBarcodePort  = INI.Get_String(strSection, "NG_BARCODE_PORT", "");

	gData.dIndexPitch = INI.Get_Double(strSection, "INDEX_PITCH", 0.0);
	m_EquipData.bUseManagerMode = INI.Get_Bool(strSection, "MANAGER_MODE", FALSE);
//	m_EquipData.bUseVacuumCheck = INI.Get_Bool(strSection, "VACUUM_CHECK", FALSE);
//	m_EquipData.bUseCMCheck = INI.Get_Bool(strSection, "CM_CHECK", FALSE);
	m_EquipData.bUseTackLog = INI.Get_Bool(strSection, "TACK_LOG", FALSE);
	m_EquipData.bUseAllPick = INI.Get_Bool(strSection, "GOOD_ALL_PICK", FALSE);
	gData.bUnloadTraySort = INI.Get_Bool(strSection, "UNLOAD_TRAY_SORTING", FALSE);
	gData.bUseNGVacuum = INI.Get_Bool(strSection, "VACUUM_NG_USE", FALSE);
	gData.bUseGDVacuum = INI.Get_Bool(strSection, "VACUUM_GOOD_USE", FALSE);
	m_EquipData.bUseInlineMode = INI.Get_Bool(strSection, "INLINE_MODE_USE", FALSE);
	gData.bNgSortFront = INI.Get_Bool(strSection, "NG_SORT_DIR", TRUE);
	gData.bUseSeparationMode = INI.Get_Bool(strSection, "SEPARATION_MODE_USE", FALSE);
	gData.nSeparationNgCode = INI.Get_Integer(strSection, "SEPARATION_NG_CODE", 7);
	gData.bGDPickerSort1 = INI.Get_Bool(strSection, "GOOD_PICKER_SORT_DIR", FALSE);
	gData.bUnloadSortFront = INI.Get_Bool(strSection, "UNLOAD_SORT_DIR", FALSE);

	gData.bUseDryRun	= INI.Get_Bool(strSection, "DRY_RUN_USE", FALSE);
	gData.nNGPercent	= INI.Get_Integer(strSection, "DRY_NG_COUNT", 0);
	gData.dDoorLockTime = INI.Get_Integer(strSection, "DOOR_LOCK_TIME", 0);

	CLogFile *pLogFile = CLogFile::Get_Instance();
	if (gIt.nOpenStart == 0 && m_EquipData.bUseDoorLock == FALSE) pLogFile->Save_Interlock(2);
	if (gIt.nOpenStart == 1 && m_EquipData.bUseDoorLock == TRUE)  pLogFile->Save_Interlock(3);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			strKey.Format("%d%d", i, j);
			m_EquipData.bTower[i][j] = INI.Get_Bool("TOWER", strKey, FALSE);
		}
	}

	CIniFileCS INI_Ins("System/Inspection.ini");
	if (!INI_Ins.Check_File()) {
		gData.nTrigDelayBar = 0;
		gData.nTrigSetBar = 5;
		gData.nTrigDelayIns = 0;
		gData.nTrigSetIns = 5;
		return TRUE;
	}

	strSection = "OPTION";
	gData.nTrigDelayBar = INI_Ins.Get_Integer(strSection, "TRIG_SET_DELAY_BARCODE", 0);
	gData.nTrigSetBar   = INI_Ins.Get_Integer(strSection, "TRIG_SET_TIME_BARCODE", 0);
	gData.nTrigDelayIns = INI_Ins.Get_Integer(strSection, "TRIG_SET_DELAY_INSPECTION", 0);
	gData.nTrigSetIns   = INI_Ins.Get_Integer(strSection, "TRIG_SET_TIME_INSPECTION", 0);

	m_EquipData.sCapAttachIp = INI.Get_String("CAPATTACH", "CAP_IP", "");

	if (gData.nTrigSetBar < 2) gData.nTrigSetBar = 5;
	if (gData.nTrigSetIns < 2) gData.nTrigSetIns = 5;
	return TRUE;
}

BOOL CDataManager::Read_ModelData()
{
	CString strModelFile;
	strModelFile.Format("Model/%s.ini", m_EquipData.sCurrModel);
	CIniFileCS INI(strModelFile);
	if (!INI.Check_File()) return FALSE;

	CString strSection = "MODEL_DATA";

	m_ModelData.sModelName	= m_EquipData.sCurrModel;
	m_ModelData.nArrayL		= INI.Get_Integer(strSection, "ARRAY_L_COUNT", 0);
	m_ModelData.nArrayW		= INI.Get_Integer(strSection, "ARRAY_W_COUNT", 0);
	m_ModelData.dPitchL		= INI.Get_Double(strSection, "TRAY_L_PITCH", 0.0);
	m_ModelData.dPitchW		= INI.Get_Double(strSection, "TRAY_W_PITCH", 0.0);
	m_ModelData.dTrayFirstL = INI.Get_Double(strSection, "TRAY_FIRST_L", 0.0);
	m_ModelData.dTrayFirstW = INI.Get_Double(strSection, "TRAY_FIRST_W", 0.0);
	m_ModelData.dUnPitchL   = INI.Get_Double(strSection, "UNLOAD_L_PITCH", 0.0);
	m_ModelData.dUnPitchW   = INI.Get_Double(strSection, "UNLOAD_W_PITCH", 0.0);
	m_ModelData.dCMWSize	= INI.Get_Double(strSection, "CM_W_SIZE", 0.0);
	m_ModelData.nCMCount	= INI.Get_Integer(strSection, "CM_MAX_COUNT", 0);

	gData.sRecipeName = m_ModelData.sModelName;	         
	gData.nArrayW	  = m_ModelData.nArrayW;		
	gData.nArrayL	  = m_ModelData.nArrayL;		
	gData.dTrayPitchW = m_ModelData.dPitchW;		
	gData.dTrayPitchL = m_ModelData.dPitchL;		
	gData.dUnPitchW   = m_ModelData.dUnPitchW;		
	gData.dUnPitchL   = m_ModelData.dUnPitchL;		
	gData.dTrayFirstW = 0; 
	gData.dTrayFirstL = 0; 
	gData.dCMSizeW    = m_ModelData.dCMWSize;
	gData.nCMUseCount = m_ModelData.nCMCount;

	return TRUE;
}

BOOL CDataManager::Read_MoveData()
{
	CString strMotionFile;
	strMotionFile.Format("System/MoveData_%d.ini", m_ModelData.nStripSize);
	CIniFileCS INI(strMotionFile);
	if (!INI.Check_File()) return FALSE;

	CString strSection, strKey;
	
	strSection = "LOAD_TRAY_X1";
	for (int i = 0; i < 5; i++) {
		strKey.Format("X%02d", i);
		m_MoveData.dLoadTrayX1[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDLoadTrayX1[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "LOAD_TRAY_X2";
	for (int i = 0; i < 5; i++) {
		strKey.Format("X%02d", i);
		m_MoveData.dLoadTrayX2[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDLoadTrayX2[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "LOAD_TRAY_Z1";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Z%02d", i);
		m_MoveData.dLoadTrayZ1[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDLoadTrayZ1[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "LOAD_TRAY_Z2";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Z%02d", i);
		m_MoveData.dLoadTrayZ2[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDLoadTrayZ2[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "LOAD_PICKER_Y1";
	for (int i = 0; i < 3; i++) {
		strKey.Format("Y%02d", i);
		m_MoveData.dLoadPickerY1[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDLoadPickerY1[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "LOAD_PICKER_Z";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Z%02d", i);
		m_MoveData.dLoadPickerZ[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDLoadPickerZ[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "LOAD_PICKER_Y2";
	for (int i = 0; i < 5; i++) {
		strKey.Format("Y%02d", i);
		m_MoveData.dLoadPickerY2[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDLoadPickerY2[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "INDEX_R";
	for (int i = 0; i < 8; i++) {
		strKey.Format("R%02d", i);
		m_MoveData.dIndexR[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDIndexR[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "BARCODE_A";
	for (int i = 0; i < 1; i++) {
		strKey.Format("A%02d", i);
		m_MoveData.dBarCodeA[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDBarCodeA[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "INSPECTION_A";
	for (int i = 0; i < 1; i++) {
		strKey.Format("A%02d", i);
		m_MoveData.dInspectionA[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDInspectionA[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "INSPECTION_Z";
	for (int i = 0; i < 2; i++) {
		strKey.Format("Z%02d", i);
		m_MoveData.dInspectionZ[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDInspectionZ[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "NG_PICKER_X";
	for (int i = 0; i < 8; i++) {
		strKey.Format("X%02d", i);
		m_MoveData.dNGPickerX[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDNGPickerX[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "NG_PICKER_Z";
	for (int i = 0; i < 7; i++) {
		strKey.Format("Z%02d", i);
		m_MoveData.dNGPickerZ[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDNGPickerZ[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "NG_STAGE_Y";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Y%02d", i);
		m_MoveData.dNGStageY[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDNGStageY[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "GOOD_PICKER_Y";
	for (int i = 0; i < 7; i++) {
		strKey.Format("Y%02d", i);
		m_MoveData.dGdPickerY[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDGdPickerY[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "GOOD_PICKER_Z";
	for (int i = 0; i < 13; i++) {
		strKey.Format("Z%02d", i);
		m_MoveData.dGdPickerZ[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDGdPickerZ[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "UNLOAD_PICKER_X1";
	for (int i = 0; i < 3; i++) {
		strKey.Format("X%02d", i);
		m_MoveData.dUnloadPickerX1[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDUnloadPickerX1[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "UNLOAD_PICKER_Z";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Z%02d", i);
		m_MoveData.dUnloadPickerZ[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDUnloadPickerZ[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "UNLOAD_PICKER_X2";
	for (int i = 0; i < 5; i++) {
		strKey.Format("X%02d", i);
		m_MoveData.dUnloadPickerX2[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDUnloadPickerX2[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "UNLOAD_TRAY_Y1";
	for (int i = 0; i < 5; i++) {
		strKey.Format("Y%02d", i);
		m_MoveData.dUnloadTrayY1[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDUnloadTrayY1[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "UNLOAD_TRAY_Y2";
	for (int i = 0; i < 5; i++) {
		strKey.Format("Y%02d", i);
		m_MoveData.dUnloadTrayY2[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDUnloadTrayY2[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "UNLOAD_TRAY_Z1";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Z%02d", i);
		m_MoveData.dUnloadTrayZ1[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDUnloadTrayZ1[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "UNLOAD_TRAY_Z2";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Z%02d", i);
		m_MoveData.dUnloadTrayZ2[i] = INI.Get_Double(strSection, strKey, 0.0);
		strKey.Format("D%02d", i);
		m_MoveData.dDUnloadTrayZ2[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	return TRUE;
}

BOOL CDataManager::Exist_PkgCode(CString sName)
{
	if (sName == "") return FALSE;

	CString strModelFile;
	strModelFile.Format("Model/%s*.ini", sName);

	CFileFind Finder;
	BOOL bExist = Finder.FindFile(strModelFile, NULL);

	return bExist;
}

BOOL CDataManager::Exist_Model(CString sName)
{
	if (sName == "") return FALSE;
	
	CString strModelFile;
	strModelFile.Format("Model/%s.ini", sName);

	CFileFind Finder;
	BOOL bExist = Finder.FindFile(strModelFile, NULL);

	return bExist;
}

BOOL CDataManager::Change_Model(CString sName)
{
	if (sName == "") return FALSE;

	CString strModelFile;
	strModelFile.Format("Model/%s.ini", sName);
	
	CFileFind Finder;
	BOOL bExist = Finder.FindFile(strModelFile, NULL);
	
	if (!bExist) return FALSE;

	CIniFileCS INI("System/EquipData.ini");
	INI.Set_String("MODEL", "CURRENT", sName);
	
	Read_EquipData();
	Read_ModelData();
	Read_MoveData();
	
	return TRUE;
}

BOOL CDataManager::Default_MoveData()
{
/*
	CString strMotionFile = "System/MoveData_1.ini";
	CIniFileCS INI(strMotionFile);
	if (!INI.Check_File()) return FALSE;

	CString strSection, strKey;
	
	strSection = "SHUTTLE_X";
	for (int i = 0; i < 2; i++) {
		strKey.Format("X%d", i);
		m_MoveData.dShuttleX[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "LOAD_TRAY_TR_1_Y";
	for (int i = 0; i < 7; i++) {
		strKey.Format("Y%d", i);
		m_MoveData.dLoadTrayTR1Y[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "LOAD_TRAY_TR_1_Z";
	for (int i = 0; i < 5; i++) {
		strKey.Format("Z%d", i);
		m_MoveData.dLoadTrayTR1Z[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "LOAD_TRAY_TR_2_Y";
	for (int i = 0; i < 7; i++) {
		strKey.Format("Y%d", i);
		m_MoveData.dLoadTrayTR2Y[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "LOAD_TRAY_TR_2_Z";
	for (int i = 0; i < 5; i++) {
		strKey.Format("Z%d", i);
		m_MoveData.dLoadTrayTR2Z[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "VISION_X";
	for (int i = 0; i < 3; i++) {
		strKey.Format("X%d", i);
		m_MoveData.dVisionX[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "COVER_1_Z";
	for (int i = 0; i < 2; i++) {
		strKey.Format("Z%d", i);
		m_MoveData.dCover1Z[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "COVER_1_Z";
	for (int i = 0; i < 2; i++) {
		strKey.Format("Z%d", i);
		m_MoveData.dCover2Z[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "INSPECT_TRAY_TR_X";
	for (int i = 0; i < 7; i++) {
		strKey.Format("X%d", i);
		m_MoveData.dInspectTrayTRX[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "INSPECT_TRAY_TR_R";
	for (int i = 0; i < 2; i++) {
		strKey.Format("R%d", i);
		m_MoveData.dInspectTrayTRR[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "NG_PICKER_X";
	for (int i = 0; i < 5; i++) {
		strKey.Format("X%d", i);
		m_MoveData.dNGPickerX[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "NG_PICKER_Y";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Y%d", i);
		m_MoveData.dNGPickerY[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "NG_PICKER_Z";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Z%d", i);
		m_MoveData.dNGPickerZ[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "GOOD_PICKER_X";
	for (int i = 0; i < 4; i++) {
		strKey.Format("X%d", i);
		m_MoveData.dGoodPickerX[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "GOOD_PICKER_Y";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Y%d", i);
		m_MoveData.dGoodPickerY[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "GOOD_PICKER_Z";
	for (int i = 0; i < 3; i++) {
		strKey.Format("Z%d", i);
		m_MoveData.dGoodPickerZ[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "EMPTY_TRAY_UNLOAD_ELEV_Z";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Z%d", i);
		m_MoveData.dEmptyTrayElevZ[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "GOOD_TRAY_UNLOAD_ELEV_Z";
	for (int i = 0; i < 4; i++) {
		strKey.Format("Z%d", i);
		m_MoveData.dGoodTrayUnloadElevZ[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "NG_TRAY_UNLOAD_Y";
	for (int i = 0; i < 3; i++) {
		strKey.Format("Y%d", i);
		m_MoveData.dNGTrayUnloadY[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "BARCODE_X";
	for (int i = 0; i < 1; i++) {
		strKey.Format("X%d", i);
		m_MoveData.dBarcodeX[i] = INI.Get_Double(strSection, strKey, 0.0);
	}

	strSection = "BARCODE_Y";
	for (int i = 0; i < 1; i++) {
		strKey.Format("Y%d", i);
		m_MoveData.dBarcodeY[i] = INI.Get_Double(strSection, strKey, 0.0);
	}
*/
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
