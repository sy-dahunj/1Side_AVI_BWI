// LogFile.cpp: implementation of the CLogFile class.
//
#include "stdafx.h"
#include "LogFile.h"
#include "Common.h"
#include "AJinAXL.h"
#include "DataManager.h"

CLogFile *CLogFile::m_pInstance = NULL;

CCriticalSection g_csAlarmLog;
CCriticalSection g_csHandlerLog;
CCriticalSection g_csInspectorLog;
CCriticalSection g_csJobListLog;
CCriticalSection g_csMesAgentLog;
CCriticalSection g_csCapAttachLog;
CCriticalSection g_csCmTrackingLog;

CCriticalSection g_csMCCLog;

CLogFile* CLogFile::Get_Instance()
{
	if (!m_pInstance)
		m_pInstance = new CLogFile();
	return m_pInstance;
}

void CLogFile::Delete_Instance()
{
	if (m_pInstance)
		delete m_pInstance;
	m_pInstance = NULL;
}

// CLogFile

CLogFile::CLogFile()
{
	m_bThreadLog = FALSE;
}

CLogFile::~CLogFile()
{
}

///////////////////////////////////////////////////////////////////////////////

void CLogFile::Create_Folder(CString sPath)
{
	if (sPath == _T("")) return;
	if (sPath.Right(1) == _T("\\")) sPath = sPath.Left(sPath.GetLength() - 1);
	if (GetFileAttributes(sPath) != -1) return;	// Directory Exist!!!

	int nFound = sPath.ReverseFind('\\');
	Create_Folder(sPath.Left(nFound));

	CreateDirectory(sPath, NULL);
}

void CLogFile::MakeFolder(CString sPath)	//"D:\\Run\\Log\\LotData\\YYYY\\MM\\DD\\";
{
	CString sTemp;
	int nIdx = 0;

	while(true) {
		nIdx = sPath.Find("\\");
		sTemp += sPath.Mid(0, nIdx) + "\\";
		CreateDirectory(sTemp,FALSE);
		sPath = sPath.Mid(nIdx+1, sPath.GetLength());
		if(nIdx<0) break;
	}
}

///////////////////////////////////////////////////////////////////////////////

void CLogFile::Save_AlarmLog(CString strLog)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile;
	strFile.Format("LOG/Alarm/%04d%02d%02d_000000_Alarm.txt", time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			CString strSave;
			strSave.Format("[%02d:%02d:%02d.%03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_AlarmResetLog(CString strLog)
{
	g_csAlarmLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile;
	strFile.Format("LOG/Alarm/Log/%04d%02d%02d_000000_AlarmLog.txt", time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			CString strSave;
			strSave.Format("[%02d:%02d:%02d.%03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csAlarmLog.Unlock();

	Save_ECMLog(1, strLog);
}

void CLogFile::Save_HistoryLog(CString strLog)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile;
	strFile.Format("LOG/Handler/History/%04d%02d%02d_000000_HistoryLog.txt", time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			CString strSave;
			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_JobListLog(CString strLog)
{
	g_csJobListLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);
	
	CString strFile, sTitle, sLogData;
	strFile.Format("LOG/JobList/%04d%02d%02d_000000_JobList.txt", time.wYear, time.wMonth, time.wDay);
	sTitle.Format("Time,Station,Type,LotID,Start_Time,End_Time,Tack_Time,Tray_Count,CM_Count,Tack,Good_Count,NG_Count,BarrelNG_Count\r\n");

	sLogData.Format("%s,%s,%s", gData.sComName, gData.sRecipeName, strLog);
	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			CString strSave;
			if (file.GetLength() <= 0) {
				strSave.Format("%s%02d:%02d:%02d,%s\r\n", sTitle, time.wHour, time.wMinute, time.wSecond, sLogData);
			} else {
				strSave.Format("%02d:%02d:%02d,%s\r\n", time.wHour, time.wMinute, time.wSecond, sLogData);
			}

			file.SeekToEnd();	
			file.Write(strSave, strSave.GetLength());
			file.Close();
		
		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csJobListLog.Unlock();

	Save_ECMLog(2, strLog);
}

void CLogFile::Save_HandlerLog(CString strLog)
{
	g_csHandlerLog.Lock();

	CString strPath = gData.sLogPath + "\\Handler";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile;
	strFile.Format("LOG/Handler/%04d%02d%02d_000000_Handler.txt", time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			CString strSave;
			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csHandlerLog.Unlock();

	Save_ECMLog(4, strLog);
}

void CLogFile::Save_InspectorLog(CString strLog)
{
	g_csInspectorLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath = gData.sLogPath + "\\Inspector";
	Create_Folder(strPath);
	
	CString strFile;
	strFile.Format("LOG/Inspector/%04d%02d%02d_000000_Inspector.txt", time.wYear, time.wMonth, time.wDay);
	
	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();
		
			CString strSave;
			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);
		
			file.Write(strSave, strSave.GetLength());
			file.Close();
		
		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csInspectorLog.Unlock();

//	Save_ECMLog(3, strLog);
}

void CLogFile::Save_SBCNgLog(CString strLog)
{
	g_csInspectorLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString sCreFile, strFile, strTitle;
	CCommon *pCommon = CCommon::Get_Instance();
	sCreFile.Format("D:\\CMI4200L\\Run\\LOG\\SBCNg\\%04d\\%02d\\%02d\\", time.wYear, time.wMonth, time.wDay);
	pCommon->MakeFolder(sCreFile);

	if (gLot.sLotID == "") gLot.sLotID = "LOT_ID_DEFAULT";
	strFile.Format("%s%s.csv", sCreFile, gData.sLotID);	

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

			CString strSave;
			strSave.Format("[%02d:%02d:%02d %03d]w %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csInspectorLog.Unlock();
}

void CLogFile::Save_AgentLog(CString strLog)
{
//	if (gCM.bMESLog==FALSE) return;
	g_csMesAgentLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile;
	strFile.Format("LOG/MESAgent/%04d%02d%02d_000000_Agent.txt", time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			CString strSave;
			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csMesAgentLog.Unlock();

}

void CLogFile::Save_TestLog(CString strLog)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile;
	strFile.Format("Test/%04d%02d%02d_000000_Test.txt", time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			CString strSave;
			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_ECMLog(int nType, CString strLog)	//nType:1[Alarm], 2[Joblist] 3[Inspect]
{
	CString strFile, sTitle, strTime, strSave;

	SYSTEMTIME time;
	GetLocalTime(&time);
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	if (nType == 1) sTitle.Format("Time,Station,Type,LotNum,Error Code,Error,Start_Time,End_Time,Lead_Time\r\n");
	if (nType == 2) sTitle.Format("Time,Station,Type,LotNum,Start_Time,End_Time,Tack_Time,Tray_Count,CM_Count,Tack,Good_Count,NG_Count,MESNG_Count\r\n");
	if (nType == 3) sTitle.Format("Time,Station,Type,LotNum,Load_Pick,Inspect,Barcode,NG_Pick,Good_Pick,Trans_Pick\r\n");
	if (nType == 4) sTitle.Format("Time,Station,Type");

	if (nType == 1) strFile.Format("%s%s_%04d%02d%02d%02d_Alarm.csv", ECM_LOG, gAlm.sLotID, time.wYear, time.wMonth, time.wDay, time.wHour);
	if (nType == 2) strFile.Format("%s%s_%04d%02d%02d%02d_JobList.csv", ECM_LOG, gLot.sLotID, time.wYear, time.wMonth, time.wDay, time.wHour);
	if (nType == 3) strFile.Format("%s%s_%04d%02d%02d%02d_Inspector.csv", ECM_LOG, gLot.sLotID, time.wYear, time.wMonth, time.wDay, time.wHour);
	if (nType == 4) strFile.Format("%s%s_%04d%02d%02d%02d_Handler.csv", ECM_LOG, gLot.sLotID, time.wYear, time.wMonth, time.wDay, time.wHour);
	

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(sTitle, sTitle.GetLength());

		strSave.Format("%s,%s,%s,%s\r\n", strTime, gData.sComName, gData.sRecipeName, strLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_LotLog(CString strLog)
{
	CString sFileName, strFile, strCreDate, sCreFile, sTemp, sData, sInsResult, sBarResult;
	SYSTEMTIME time;
	GetLocalTime(&time);

	if (gLot.sLotID == "") gLot.sLotID = "LOT_ID_DEFAULT";
	strCreDate.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	strFile.Format("LOG/LotData/%04d/%02d/%02d/%s_%s.txt", time.wYear, time.wMonth, time.wDay, gLot.sLotID, strCreDate);
	sFileName = strFile;

	CCommon *pCommon = CCommon::Get_Instance();
	sCreFile.Format("D:\\CMI4200L\\Run\\LOG\\LotData\\%04d\\%02d\\%02d\\", time.wYear, time.wMonth, time.wDay);
	pCommon->MakeFolder(sCreFile);

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	sTemp.Format("LotID,%s,Start_Time,%s,End_Time,%s,Tray_Count,%02d,CM_Count,%04d,Tack,%0.7lf,\r\n\r\n", gLot.sLotID, gLot.sStartTime, gLot.sEndTime, gLot.nTrayCount, gLot.nCMCount, gLot.dTackTime);
	sData.Format("%sTray_No,Pocket_No,ID,Inspection Result,ID Result,\r\n", sTemp);
	file.Write(sData, sData.GetLength());

	try {
		int	nCMCount = 0;
		for(int i=0; i<30; i++) {
			if (nCMCount > gLot.nCMCount) break;

			for(int j=0; j<60; j++){
				if (j >= gData.nCMUseCount) break;

				nCMCount++;
				if (nCMCount > gLot.nCMCount) break;

				file.SeekToEnd();

				if		(gLot.nInsResult[i][j] == 1) sInsResult = "OK";
				else if (gLot.nInsResult[i][j] == 2) sInsResult = "NG";
				else if (gLot.nInsResult[i][j] == 3) sInsResult = "NG";
				else								 sInsResult = "Skip";
				if		(gLot.nBarResult[i][j] == 1) sBarResult = "OK";
				else if	(gLot.nBarResult[i][j] == 2) sBarResult = "NG";
				else if	(gLot.nBarResult[i][j] == 3) sBarResult = "Shift";
				else if	(gLot.nBarResult[i][j] == 4) sBarResult = "NG";
				else if	(gLot.nBarResult[i][j] == 5) sBarResult = "Read Fail";
				else if	(gLot.nBarResult[i][j] == 6) sBarResult = "Grab Fail";
				else								 sBarResult = "Skip";

				sData.Format("%d,%d,%s,%s,%s,\r\n", i+1, j+1, gLot.sBarLoad[i][j], sInsResult, sBarResult);
				file.Write(sData, sData.GetLength());
			}
		}

		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}


void CLogFile::Save_AVIError(CString sLog)
{
	CString strPath1 = "D:\\EVMS\\TP\\Log";
	CString strPath2 = "D:\\EVMS\\TP\\Backup";

	Create_Folder(strPath1);
	Create_Folder(strPath2);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile1, strFile2, strTitle, strDateTime, strPcName, strSave;
	strFile1.Format("%s\\%s_%04d%02d%02d%02d_AVIError.csv", strPath1, gData.sLotID, time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile2.Format("%s\\%s_%04d%02d%02d%02d_AVIError.csv", strPath2, gData.sLotID, time.wYear, time.wMonth, time.wDay, time.wHour);

	CFile file;
	if (!file.Open(strFile1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	strTitle.Format("Time,Station,Model,Version,lotNum,Event,Error Code,event,ActionTime\r\n");

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		strDateTime.Format("%04d-%02d-%02d %02d:%02d:%02d:%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		char szPcName[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
		GetComputerName(szPcName, &dwNameSize);

		strSave.Format("%s,%s,%s\r\n", strDateTime, szPcName, sLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();

		CopyFile(strFile1, strFile2, FALSE);	// Backup

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_CapAttachLog(CString strLog)
{
	g_csCapAttachLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath = gData.sLogPath + "\\CapAttach";

	Create_Folder(strPath);

	
	CString strFile;
	strFile.Format("LOG/CapAttach/%04d%02d%02d_000000_CapAttach.txt", time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			CString strSave;
			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csCapAttachLog.Unlock();

	//	Save_ECMLog(3, strLog);
}

void CLogFile::Save_Interlock(int nType)	//nType:1[정시], 2[해제] 3[설정]
{
	CString strFile, sTitle, sTitle1, strTime, strSave, strSave1, strSave2, strSave3, strSave4, strLotID, strDoor[8], sInterUse;

	SYSTEMTIME time;
	GetLocalTime(&time);

	if (nType == 1)	strTime.Format("%04d-%02d-%02d %02d:00:00.000", time.wYear, time.wMonth, time.wDay, time.wHour);
	else			strTime.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	sTitle1 = "Door I/L 11,Door I/L 12,Door I/L 13,Door I/L 14,Door I/L 15,Door I/L 16,Door I/L 17,Door I/L 18,Door I/L 19,Door I/L 20,Door I/L 21,Door I/L 22,Door I/L 23,Door I/L 24,Door I/L 25,Door I/L 26,Door I/L 27,Door I/L 28,Door I/L 29,Door I/L 30";
	sTitle.Format("time,station,lotNum,barcode,SWversion,State,site,Line,Machine,operator,result,Interlock,Interlock off Time,Interlock Coverage,Door I/L 1,Door I/L 2,Door I/L 3,Door I/L 4,Door I/L 5,Door I/L 6,Door I/L 7,Door I/L 8,Door I/L 9,Door I/L 10,%s\r\n", sTitle1);
	strFile.Format("%sGSY827ADOOR1_%04d%02d%02d%02d_InterlockResult.csv", ECM_LOG, time.wYear, time.wMonth, time.wDay, time.wHour);

	if (gData.nStatus > 0) strLotID = gData.sLotID;
	else				   strLotID = "";

	int	   nNGTime;
	double dTime, dPer;
	if (nType == 1) {
		if (gIt.nOpenStart == 1) {
			nNGTime = (GetTickCount() - gIt.dwOpenStartTime) / 1000;
			gIt.nOpenTime = gIt.nOpenTime + nNGTime;
		}
		if (gIt.nOpenTime > 0) {
			if (gIt.nOpenTime > 3600) gIt.nOpenTime = 3600;
			dTime = gIt.nOpenTime / 60.0;
			dPer = ((3600.0 - gIt.nOpenTime) / 3600.0) * 100.0;
		} else {
			dTime = 0.0; dPer = 100.0;
		}
		gIt.dwOpenStartTime = GetTickCount();
		gIt.nOpenTime = 0;
		gIt.nWriteHH = time.wHour;

		CDataManager *pDataManager = CDataManager::Get_Instance();
		EQUIP_DATA *pEquipData = pDataManager->Get_pEquipData();
		if (pEquipData->bUseDoorLock) sInterUse = "OK";
		else						  sInterUse = "NG";
	}
	if (nType == 2) {
		sInterUse = "NG";
		gIt.nOpenStart = 1;
		gIt.dwOpenStartTime = GetTickCount();
	}
	if (nType == 3) {
		sInterUse = "OK";
		gIt.nOpenStart = 0;
		nNGTime = (GetTickCount() - gIt.dwOpenStartTime) / 1000;
		gIt.nOpenTime = gIt.nOpenTime + nNGTime;
	}
	if (nType == 4) {
		sInterUse = "OK";
		gIt.nOpenStart = gIt.nOpenTime = 0;
	}

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(sTitle, sTitle.GetLength());
		else {
			if (nType == 1) { file.Close(); Save_Interlock(4); return; }
		}

		strSave1.Format("%s,%s,%s,,%s,MP,Gumi Campus 3 Area,Campus 3 FOL,Cosmetic AVI,%s", strTime, gData.sComName, strLotID, MAIN_VERSION, gData.sOperID);
		if (nType == 1) strSave2.Format("A1,%s,%0.2lf,%0.1lf", sInterUse, dTime, dPer);
		if (nType == 2) strSave2.Format("F,NG,,");
		if (nType >= 3) strSave2.Format("A2,OK,,");

		CAJinAXL *pAJinAXL = CAJinAXL::Get_Instance();
		DX_DATA_0 *pDX0 = pAJinAXL->Get_pDX0();
		if (pDX0->iMainDoor1Close) strDoor[0] = "Close"; else strDoor[0] = "Open";
		if (pDX0->iMainDoor2Close) strDoor[1] = "Close"; else strDoor[1] = "Open";
		if (pDX0->iMainDoor3Close) strDoor[2] = "Close"; else strDoor[2] = "Open";
	 	if (pDX0->iMainDoor4Close) strDoor[3] = "Close"; else strDoor[3] = "Open";
	 	if (pDX0->iMainDoor5Close) strDoor[4] = "Close"; else strDoor[4] = "Open";
		if (pDX0->iMainDoor6Close) strDoor[5] = "Close"; else strDoor[5] = "Open";
		if (pDX0->iMainDoor7Close) strDoor[6] = "Close"; else strDoor[6] = "Open";
		if (pDX0->iMainDoor8Close) strDoor[7] = "Close"; else strDoor[7] = "Open";
		strSave3.Format("%s,%s,%s,%s,%s,%s,%s,%s,-,-", strDoor[0], strDoor[1], strDoor[2], strDoor[3], strDoor[4], strDoor[5], strDoor[6], strDoor[7]);
		strSave4 = "-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-";

		strSave.Format("%s,%s,%s,%s\r\n", strSave1, strSave2, strSave3, strSave4);
		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_CmTrackingLog(CString strOut, int nTrayCount, int nPosX, int nPosY, int nTrayNo, int nCmNo)
{
	if (nTrayNo < 1 || nTrayNo > 30 || nCmNo < 1 || nCmNo > 60) return;

	g_csCmTrackingLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strTitle, strSave, strJudge;
	strPath.Format("%s\\LOG\\Tracking\\%04d-%02d-%02d", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	if (gLot.sLotID == "") gLot.sLotID = "LOT_ID";
	strFile.Format("%s\\%s_AVITracking.csv", strPath, gLot.sLotID);

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

//	strTitle.Format("Time,Barcode,Judge,Port No,Tray No,CM No,Load Stage,Load Picker,Index Load,Index Load Jig,Unload Picker,NG Tray,NG Y,NG X,Ship Tray,Ship Y,Ship X\r\n");
	strTitle.Format("Time,Station,LotNum,Barcode,Judge,Port No,Tray No,CM No,Load Stage,Load Picker,Index Load,Index Load Jig,NG Picker,Good Picker,Unload Picker,NG Tray,NG Y,NG X,Ship Tray,Ship Y,Ship X\r\n");

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		// Unit 0:Load Stage, 1:Load Picker, 2:Index Load No, 3:Index Jig No, 4:NG Picker, 5:Good Picker, 6:Unload Picker
		int nLdStageNo, nLdPick, nIdxLdNo, nIdxLdJig, nNGPick, nGDPick, nUlPick;
		nLdStageNo	= gLot.nCmJigNo[nTrayNo-1][nCmNo-1][0];
		nLdPick		= gLot.nCmJigNo[nTrayNo-1][nCmNo-1][1];
		nIdxLdNo	= gLot.nCmJigNo[nTrayNo-1][nCmNo-1][2];
		nIdxLdJig	= gLot.nCmJigNo[nTrayNo-1][nCmNo-1][3];

		if(strOut == "GOOD") nNGPick = 0;
		else {	nNGPick	= gLot.nCmJigNo[nTrayNo-1][gData.nNGTrayCmNo-1][4];	}//gLot.nCmJigNo[nTrayNo-1][nCmNo-1][4]; //몇번 NG 피커가 집었는지 

		nGDPick		= gLot.nCmJigNo[nTrayNo-1][nCmNo-1][5];
		nUlPick		= gLot.nCmJigNo[nTrayNo-1][nCmNo-1][6];
		
		if (strOut == "GOOD") {
			strSave.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d,%s,%s,%s,G,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n", time.wYear, time.wMonth, time.wDay,
				time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, gData.sComName, gData.sLotID, gLot.sBarLoad[nTrayNo-1][nCmNo-1], 1, nTrayNo, nCmNo, 
				nLdStageNo, nLdPick, nIdxLdNo, nIdxLdJig, nNGPick, nGDPick, nUlPick,
				0, 0, 0, nTrayCount, nPosY, nPosX);
		} else {
			strSave.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d,%s,%s,%s,N,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n", time.wYear, time.wMonth, time.wDay,
				time.wHour, time.wMinute, time.wSecond,time.wMilliseconds, gData.sComName, gData.sLotID, gLot.sBarLoad[nTrayNo-1][nCmNo-1], 1, nTrayNo, nCmNo, 
				nLdStageNo, nLdPick, nIdxLdNo, nIdxLdJig, nNGPick, nGDPick, nUlPick,
				nTrayCount, nPosY, nPosX, 0, 0, 0);
		}
		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
	Save_ECMTracking(strSave, nTrayCount, nPosX, nPosY, nTrayNo, nCmNo);

	g_csCmTrackingLog.Unlock();
}

void CLogFile::Save_ECMTracking(CString sLog, int nTrayCount, int nPosX, int nPosY, int nTrayNo, int nCmNo)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strTitle;
	strPath = "D:\\EVMS\\TP\\Log";
	Create_Folder(strPath);

	if (gLot.sLotID == "") gLot.sLotID = "LOT_ID";
	strFile.Format("%s\\%s_%04d%02d%02d%02d_AVITracking.csv", strPath, gLot.sLotID, time.wYear, time.wMonth, time.wDay, time.wHour);

//	strTitle.Format("Time,Barcode,Judge,Port No,Tray No,CM No,Load Stage,Load Picker,Index Load,Index Load Jig,NG Picker,NG Stage,Good Picker,Index Good No,Index Good Jig,Transfer Picker,NG Tray,NG Y,NG X,Ship Tray,Ship Y,Ship X\r\n");
	strTitle.Format("Time,Station,LotNum,Barcode,Judge,Port No,Tray No,CM No,Load Stage,Load Picker,Index Load,Index Load Jig,NG Picker,Good Picker,Unload Picker,NG Tray,NG Y,NG X,Ship Tray,Ship Y,Ship X\r\n");

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		file.Write(sLog, sLog.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}


void CLogFile::Save_PCLog(CString sLog)
{
	CString strPath1 = "D:\\EVMS\\TP\\Log";
	CString strPath2 = "D:\\EVMS\\TP\\Backup";

	Create_Folder(strPath1);
	Create_Folder(strPath2);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile1, strFile2, strTitle, strTime, strPcName, strSave;
	strFile1.Format("%s\\%s_%04d%02d%02d%02d_PC.csv", strPath1, gData.sLotID, time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile2.Format("%s\\%s_%04d%02d%02d%02d_PC.csv", strPath2, gData.sLotID, time.wYear, time.wMonth, time.wDay, time.wHour);

	CFile file;
	if (!file.Open(strFile1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	strTitle.Format("Time,Station,LotID,ModuleConfig,CPU,RAM,HardDisk\r\n");

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		strTime.Format("%04d-%02d-%02d %02d:%02d:%02d:%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		char szPcName[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
		GetComputerName(szPcName, &dwNameSize);

		strSave.Format("%s,%s,%s\r\n", strTime, szPcName, sLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();

		CopyFile(strFile1, strFile2, FALSE);	// Backup

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}


void CLogFile::Save_MCCLog(CString strLog)
{
	g_csMCCLog.Lock();

	CString strPath = gData.sLogPath + "\\MCC";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile;
	strFile.Format("%s\\%04d%02d%02d_MCC.txt", strPath, time.wYear, time.wMonth, time.wDay);

	//strFile.Format("LOG/Handler/History/%04d%02d%02d_000000_HistoryLog.txt", time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try 
		{
			file.SeekToEnd();

			CString strSave;
			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		}
		catch (CFileException *pEx)
		{
			pEx->Delete();
		}
	}
	g_csMCCLog.Unlock();
}




///////////////////////////////////////////////////////////////////////////////
