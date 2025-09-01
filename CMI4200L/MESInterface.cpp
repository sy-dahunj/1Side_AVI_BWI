// MESInterface.cpp : 구현 파일
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "MESInterface.h"
#include <vector>
#include "io.h"

#include "CMI4200LDlg.h"
#include "Common.h"
#include "WorkDlg.h"

#define RESULT_FOLDER			"D:\\MES\\VALIDATION\\"
#define MES_FOLDER_LOG			"D:\\MES\\LOG\\"
#define STATUS_FOLDER			"D:\\MES\\STATUS\\"
#define APD_FOLDER				"D:\\MES\\DATA\\"
#define MES_FOLDER_APD			"D:\\MES\\APD\\"
#define MES_FOLDER_RMS			"D:\\MES\\Recipe\\"
#define MES_FOLDER_APD_RESULT	"D:\\EVMS\\TP\\MES\\VALIDATION\\"

#define EQUIP_TYPE		"S"	//Single:S, Dual:D"
#define APD_COUNT		100	//전송Max수량
#define APD_MAX_COUNT	500	//전송Max수량
#define TIME_OUT		40	//40*500=20000(20초)

CMESInterface	 g_objMES;
CCriticalSection g_csMesLog;
CCriticalSection g_csMesData;
CCriticalSection g_csMesUse;
CCriticalSection g_csMesApd;

CMESInterface::CMESInterface(void)
{
	m_pThreadMES = NULL;
	m_bThreadMES = FALSE;
}

CMESInterface::~CMESInterface(void)
{
}

void CMESInterface::Initialize(BOOL bMESUse)
{
	MakeFolder(RESULT_FOLDER);
	MakeFolder(MES_FOLDER_LOG);
	MakeFolder(STATUS_FOLDER);
	MakeFolder(APD_FOLDER);
	MakeFolder(MES_FOLDER_APD);
	MakeFolder(MES_FOLDER_RMS);

	m_nTCount = m_nSNo = 0;
	g_objMES.m_nMESSequence = 0;

	Set_MESUse(bMESUse);		//On-Off Line Set
	Set_Status(3);				//Idle Set
}

/////////////////////////////////////////////////////////////////////////////
// Thread Function 
UINT CMESInterface::Thread_MES(LPVOID lpVoid)
{
	if (g_objMES.m_nMESSequence == 0) g_objMES.Clear_Result();	//수신 Folder All File 삭제

	g_objMES.m_nReadCnt = 0;
	while (g_objMES.m_bThreadMES) {
		Sleep(500);
		g_objMES.Read_Result();

		g_objMES.m_nReadCnt++;
		if (g_objMES.m_nReadCnt >= TIME_OUT) break;
		if (g_objMES.m_bStart==FALSE) break;
	}
	if (g_objMES.m_bStart==FALSE) {
		g_objMES.m_pThreadMES = NULL;
		return 0;
	}

	CCommon *pCommon = CCommon::Get_Instance();
	if (g_objMES.m_nReadCnt >= TIME_OUT) {			//TimeOver
		g_objMES.m_nMESSequence = 0; g_objMES.m_pThreadMES = NULL;
		pCommon->Show_Error(991);
		return 0;
	}
	if (g_objMES.m_sMESResult == "1") {				//Lot취소
		g_objMES.m_nMESSequence = 0; g_objMES.m_pThreadMES = NULL;
		pCommon->Show_Error(992);
		return 0;
	}
	if (g_objMES.m_sMESLotID != g_objMES.m_sOperLotID) {	//Lot정보 불일치
		g_objMES.m_nMESSequence = 2; g_objMES.m_pThreadMES = NULL;
		pCommon->Show_Error(993);
		return 0;
	}
	if (g_objMES.m_nMESCount != g_objMES.m_nOperCount) {	//Lot정보 불일치
		g_objMES.m_nMESSequence = 2; g_objMES.m_pThreadMES = NULL;
		pCommon->Show_Error(994);
		return 0;
	}

	g_objMES.Start_Send();

	g_objMES.m_nMESSequence = 3;
	CWorkDlg *pWorkDlg = CWorkDlg::Get_Instance();
	pWorkDlg->Set_AutoRunStatus(FALSE);

	g_objMES.m_bThreadMES = FALSE; g_objMES.m_pThreadMES = NULL;
	g_objMES.Clear_Result();	//수신 Folder All File 삭제

	return 0;
}
/////////////////////////////////////////////////////////////////////////////

void CMESInterface::Begin_MESThread()
{
	if (m_pThreadMES) return;

	m_bThreadMES = TRUE;
	m_pThreadMES = AfxBeginThread(Thread_MES, NULL);
}

void CMESInterface::End_MESThread()
{
	if (m_pThreadMES) {
		m_bThreadMES = FALSE;
		WaitForSingleObject(m_pThreadMES->m_hThread, INFINITE);
	}
}

void CMESInterface::Create_Folder(CString sPath)
{
	if (sPath == _T("")) return;
	if (sPath.Right(1) == _T("\\")) sPath = sPath.Left(sPath.GetLength() - 1);
	if (GetFileAttributes(sPath) != -1) return;

	int nFound = sPath.ReverseFind('\\');
	Create_Folder(sPath.Left(nFound));

	CreateDirectory(sPath, NULL);
}

void CMESInterface::MakeFolder(CString sPath)	//"D:\\Run\\Log\\LotData\\YYYY\\MM\\DD\\";
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

void CMESInterface::Clear_Result()
{
	m_sMESResult = m_sMESLotID = m_sReasonCode = m_sReasonText = "";
	m_nMESCount = 0;
	m_nTCount = m_nSNo = m_nReadCnt = 0;

	FileAllDelete(RESULT_FOLDER);
}

void CMESInterface::Read_Result()
{
	CString strFile, strData, sDataA, sResult[10];

	ResultFileSearch();
	if(m_sResultFileName.GetLength() < 4) return;

	strFile = m_sResultFileName;
	CFile file;
	if (!file.Open(strFile, CFile::modeRead)) return;

	int nSize = (int)file.GetLength();
	char *pBuff = new char[nSize + 1];
	pBuff[nSize] = '\0';

	file.Read(pBuff, nSize);
	strData.Format("%s", pBuff);
	strData.Replace("\r\n", ",");

	file.Close();
	delete pBuff;

	char chSepA = '=';
	char chSepB = ',';
	for(int i=0; i<8; i++) {
		AfxExtractSubString(sDataA, strData, i, chSepA);
		if (i>0) {
			AfxExtractSubString(sResult[i-1], sDataA, 0, chSepB);
		}
	}

	m_sMESResult = sResult[1];
	m_sReasonCode = sResult[2];
//	m_sReasonText = sResult[3];
	m_sReasonText.Empty();
	m_sReasonText.Insert(0, UTF8ToANSI(sResult[3]));
	m_sMESLotID = sResult[4];
	m_nMESCount = atoi(sResult[6]);

	g_objMES.m_bThreadMES = FALSE;
}

void CMESInterface::Clear_APDResult()
{
	CString strLog;
	strLog.Format("[MESInterface] Clear_APDResult.");
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog(strLog);

	CString strPath, strFile;
	strPath.Format("%s*.*", MES_FOLDER_APD_RESULT);

	CFileFind finder;
	BOOL bRes = finder.FindFile(strPath);

	while (bRes) {
		bRes = finder.FindNextFile();
		if (finder.IsDirectory()) continue;
		strFile = finder.GetFilePath();
		DeleteFile(strFile);
	}
}

BOOL CMESInterface::Read_APDResult()
{
	CString strPath, strFile, strData, sDataA, sResult[47], strLog;
	CString strLotID, strItem, strTemp;
	strPath.Format("%s*.*", MES_FOLDER_APD_RESULT);

	CFileFind finder;
	BOOL bRes = finder.FindFile(strPath);

	while (bRes) {
		bRes = finder.FindNextFile();
		if (finder.IsDirectory()) continue;
		strFile = finder.GetFilePath();
		if (strFile.GetLength() > 10 && strFile.Find("APD_Result") != -1 ) break;
	}

	//파일명: APD_Result_YYYYMMDD_hhmmssff.txt
	if (strFile.Find("APD_Result") == -1) return FALSE;

	CFile file;
	if (!file.Open(strFile, CFile::modeRead)) return FALSE;

	int nSize = (int)file.GetLength();
	char *pBuff = new char[nSize + 1];
	pBuff[nSize] = '\0';

	file.Read(pBuff, nSize);
	strData.Format("%s", pBuff);
	strData.Replace("\r\n", ",");

	file.Close();
	delete pBuff;

	char chSepA = ',', chSepB = '=';
	int nChkCnt = gData.nAviApdCnt + 1;
	strItem = "";
	gData.sAPDNgItem = "";
	gData.bAPDResultErr = FALSE;
	for (int i = 0; i < nChkCnt; i++) {
		AfxExtractSubString(sDataA, strData, i, chSepA);
		if (i == 0) AfxExtractSubString(strLotID, sDataA, 1, chSepB);
		if (i > 0) {
			AfxExtractSubString(sResult[i-1], sDataA, 1, chSepB);
			if (sResult[i-1] == "NG") { strTemp.Format("%d.", i - 1); strItem += strTemp; gData.bAPDResultErr = TRUE;}
		}
	}

	gData.sAPDNgItem.Format("#==> LotID:%s, NG Item No:%s", strLotID, strItem);
	strLog.Format("[MESInterface] Read_APDResult. (LotID:%s, NG Item No:%s)", strLotID, strItem);
	CLogFile *pLogFile = CLogFile::Get_Instance();
	pLogFile->Save_HandlerLog(strLog);

	gData.bAviApdFileChk = TRUE;
	return TRUE;
}

char* CMESInterface::UTF8ToANSI(const char *pszCode)
{
    BSTR    bstrWide;
    char*   pszAnsi;
    int     nLength;
  
    nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, NULL, NULL);
    bstrWide = SysAllocStringLen(NULL, nLength);
  
    MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, bstrWide, nLength);
  
    nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
    pszAnsi = new char[nLength];
  
    WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
    SysFreeString(bstrWide);
  
    return pszAnsi;
}

void CMESInterface::Start_Send()
{
	g_csMesLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strSave, sState;
	strPath.Format("%s%04d%02d%02d", MES_FOLDER_LOG, time.wYear, time.wMonth, time.wDay);
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();
			 
			sState = "LotStart";
			strSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],%s,UNITID=1000,TYPE=%s,LOTID=%s,COUNT=%d,USERID=%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, sState, EQUIP_TYPE, m_sMESLotID, m_nMESCount, m_sOperID);
			file.Write(strSave, strSave.GetLength());

			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csMesLog.Unlock();
}

///////////////////////////////////////////////////////////////////////////////

void CMESInterface::Set_MESUse(BOOL bMESUse)
{
	int nStatus;

	g_csMesUse.Lock();

	m_bMESUse = bMESUse;
	if(m_bMESUse) nStatus = 1;
	else		  nStatus = 0;

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strSave;
	strPath.Format("%s%04d%02d%02d", STATUS_FOLDER, time.wYear, time.wMonth, time.wDay);
	strFile.Format("%s\\ValidationSet_%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],CONTROL_STATE=%d\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, nStatus);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	g_csMesUse.Unlock();
}

void CMESInterface::Set_Status(int nStste)	//1:Run, 2:Stop, 3:Idle
{
	if(!g_objMES.m_bMESUse) return;

	g_csMesLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strSave, sState;
	strPath.Format("%s%04d%02d%02d", MES_FOLDER_LOG, time.wYear, time.wMonth, time.wDay);
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	if		(nStste == 1) sState = "RUN";
	else if (nStste == 2) sState = "STOP";
	else				  sState = "IDLE";

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],StateChange,UNITID=1000,WorkMode=%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, sState);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	g_csMesLog.Unlock();
}

void CMESInterface::Set_Alarm(int nType, int nAlarmID, CString sText )	//1:발생, 2:해제
{
	if(!g_objMES.m_bMESUse) return;

	g_csMesLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strSave, sState;
	strPath.Format("%s%04d%02d%02d", MES_FOLDER_LOG, time.wYear, time.wMonth, time.wDay);
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	if (nType == 1) sState = "AlarmSet";
	else			sState = "AlarmReset";

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],%s,UNITID=1000,ALARMID=%d,ALARMTYPE=H,ALARMTEXT=%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, sState, nAlarmID, sText);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csMesLog.Unlock();

	if (nType == 1) Set_Status(2);	//Stop Set
	if (nType == 2) Set_Status(3);	//Idle Set
}

void CMESInterface::Set_TackTime(double dTack, CString sLotID, int nCount, CString sStartTime, CString sEndTime)	//sStartTime="2017/12/04 14:00:10:
{
	if(!g_objMES.m_bMESUse) return;

	g_csMesLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strSave, sState;
	strPath.Format("%s%04d%02d%02d", MES_FOLDER_LOG, time.wYear, time.wMonth, time.wDay);
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],TackTime,UNITID=1000,TackTime=%0.3lf,LotID=%s,Count=%d,StartTime=%s,EndTime=%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, dTack, sLotID, nCount, sStartTime, sEndTime);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	g_csMesLog.Unlock();
}

void CMESInterface::Set_LotStart(CString sLotID, int nCount, CString sOperID)
{
	m_sOperLotID = sLotID;	m_nOperCount = nCount;	m_sOperID = sOperID;

	Set_Status(1);	//Run Set
	Begin_MESThread();
	if (g_objMES.m_nMESSequence!=0) return;

	g_csMesLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strSave, sState;
	strPath.Format("%s%04d%02d%02d", MES_FOLDER_LOG, time.wYear, time.wMonth, time.wDay);
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			sState = "JobReady";
			strSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],%s,UNITID=1000,TYPE=%s,LOTID=%s,COUNT=%d,USERID=%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, sState, EQUIP_TYPE, sLotID, nCount, sOperID);
			file.Write(strSave, strSave.GetLength());

			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_objMES.m_nMESSequence = 1;

	g_csMesLog.Unlock();
}

void CMESInterface::Set_LotCancel(CString sLotID, int nCount, CString sOperID)
{
	m_sOperLotID = sLotID;	m_nOperCount = nCount;	m_sOperID = sOperID;
	g_csMesLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strSave, sState;
	strPath.Format("%s%04d%02d%02d", MES_FOLDER_LOG, time.wYear, time.wMonth, time.wDay);
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			sState = "LotCancel";
			strSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],%s,UNITID=1000,TYPE=%s,LOTID=%s,COUNT=%d,USERID=%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, sState, EQUIP_TYPE, sLotID, nCount, sOperID);
			file.Write(strSave, strSave.GetLength());

			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	g_objMES.Clear_Result();	//수신 Folder All File 삭제

	g_csMesLog.Unlock();
}

void CMESInterface::Set_LotEnd(CString sLotID, int nCount, CString sOperID, int nOKCount, int nNGCount)
{
	if(!g_objMES.m_bMESUse) return;

	g_csMesLog.Lock();

	Write_APD();
	m_nSNo = 0;

	SYSTEMTIME time;
	GetLocalTime(&time);

	// 2019.8.1 Tack Time 이후에 APD 로그가 남아서 Tack Time 로그 위치를 바꿔주었다.
	long lTime = gLot.lLotEnd - gLot.lLotStart;
	double dMESTack = double(lTime/1000);
	CString sEndTime;
	sEndTime.Format("%04d/%02d/%02d %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	Set_TackTime(dMESTack, gLot.sLotID, gLot.nCMCount, gLot.sMESStartTime, sEndTime);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CString strPath, strFile, strSave, sState;
	strPath.Format("%s%04d%02d%02d", MES_FOLDER_LOG, time.wYear, time.wMonth, time.wDay);
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	sState = "LotEnd";
	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],%s,UNITID=1000,TYPE=%s,LOTID=%s,GoodCount=%d,NGCount=%d,USERID=%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, sState, EQUIP_TYPE, sLotID, nOKCount, nNGCount, sOperID);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	g_csMesLog.Unlock();

	g_objMES.Clear_Result();	//수신 Folder All File 삭제
	Set_Status(3);	//Idle Set
}

void CMESInterface::Set_Cancel(CString sLotID, int nCount, CString sOperID) //Lot Cancel
{
	g_csMesLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strSave, sState;
	strPath.Format("%s%04d%02d%02d", MES_FOLDER_LOG, time.wYear, time.wMonth, time.wDay);
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	sState = "LotCancel";
	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],%s,UNITID=1000,TYPE=%s,LOTID=%s,COUNT=%d,USERID=%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, sState, EQUIP_TYPE, sLotID, nCount, sOperID);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	g_csMesLog.Unlock();
}

void CMESInterface::Set_Result(CString sLotID, CString sBarID, CString sJudge, CString sNGCode, CString NGText, int nLTray, int nLPno, int nUTray, int nUPno,int nNGTray, int nNGPno)
{
	if (!g_objMES.m_bMESUse) return;
	if (gData.bCleanOutMode) return;
					
	int nBarErr = 0;
	SYSTEMTIME time;
	GetLocalTime(&time);

	m_sLotID = sLotID;
	if (m_nTCount == 0) {
		m_sDate[0].Format("%04d", time.wYear);
		m_sDate[1].Format("%02d", time.wMonth);
		m_sDate[2].Format("%02d", time.wDay);
	}
	m_sTime[m_nTCount].Format("%04d/%02d/%02d %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	if(sBarID.GetLength()<12) {
		nBarErr = 1;
		m_sBarID[m_nTCount].Format("%04d%02d%02d%02d%02d%02d%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	} else {
		m_sBarID[m_nTCount] = sBarID;
	}
	m_sJudge[m_nTCount] = sJudge;
	if (sJudge == "NG") {
		if (sNGCode.GetLength() < 1)	sNGCode = "1";
		if (NGText.GetLength() < 1)		NGText = "NON";
		nNGTray = gLot.nNGT+1;
		nNGPno = gLot.nNGC+1;
		nUTray = nUPno = 0;
		gLot.nNGC++;
		if (gLot.nNGC >= gData.nCMUseCount) { gLot.nNGT++; gLot.nNGC=0; }
	} else {
		nUTray = gLot.nGDT+1;
		nUPno = gLot.nG1DC+1;
		nNGTray = nNGPno = 0;
		gLot.nG1DC++;
		if (gLot.nG1DC >= gData.nCMUseCount) { gLot.nGDT++; gLot.nG1DC=0; }
	}
	m_sNGCode[m_nTCount] = sNGCode;
	m_sNGText[m_nTCount] = NGText;
	m_nLoadTray[m_nTCount] = nLTray;
	m_nLoadPocket[m_nTCount] = nLPno;
	m_nOKTray[m_nTCount] = nUTray;
	m_nOKPocket[m_nTCount] = nUPno;
	m_nNGTray[m_nTCount] = nNGTray;
	m_nNGPocket[m_nTCount] = nNGPno;
	m_nTCount++;

	if (m_nTCount >= APD_COUNT) Write_APD();

	if (nBarErr==1) Sleep(5);
}

void CMESInterface::Write_APD()
{
	if (m_nTCount < 1) return;
	m_nSNo++;

	CString strPathAPD, strFileAPD, strSaveAPD;
	strPathAPD.Format("%s%s%s%s", APD_FOLDER, m_sDate[0], m_sDate[1], m_sDate[2]);
	strFileAPD.Format("%s\\%s_%03d.dat", strPathAPD, m_sLotID, m_nSNo);
	Create_Folder(strPathAPD);

	CFile fileAPD;
	if (fileAPD.Open(strFileAPD, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			for(int i=0; i<m_nTCount; i++) {
				strSaveAPD.Format("[%s],%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\r\n", m_sTime[i], EQUIP_TYPE, m_sLotID,
					m_sBarID[i], m_sJudge[i], m_sNGCode[i], m_sNGText[i], m_nLoadTray[i], m_nLoadPocket[i], m_nOKTray[i], m_nOKPocket[i], m_nNGTray[i], m_nNGPocket[i]);

				fileAPD.Write(strSaveAPD, strSaveAPD.GetLength());
			}
			fileAPD.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	CString strPath, strFile, strSave;
	strPath.Format("%s%s%s%s", MES_FOLDER_LOG, m_sDate[0], m_sDate[1], m_sDate[2]);
	strFile.Format("%s\\%s%s%s.txt", strPath, m_sDate[0], m_sDate[1], m_sDate[2]);
	Create_Folder(strPath);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%s],APD,PATH=%s\r\n",m_sTime[0], strFileAPD);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	m_nTCount = 0;
}

void CMESInterface::Save_AviApdData(CString sLotID, int nPortNo, CString sOperID)
{
	g_csMesApd.Lock();

	Clear_APDResult();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strSave, strData;
	strPath.Format("%s%04d%02d%02d", MES_FOLDER_APD, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	strFile.Format("%s\\%s_%04d%02d%02d.txt", strPath, sLotID, time.wYear, time.wMonth, time.wDay);
	char szPcName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerName(szPcName, &dwNameSize);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();

			//[2022/12/16 11:52:39],Station=KCMAPST001,Operator=101004,LotNum=GSY847AI4N30,
			//CM1P1AVI00=255.00,CM1P1AVI01=255.00,CM1P1AVI02=255.00,CM1P1AVI03=255.00,CM1P1AVI04=255.00,CM1P1AVI05=255.00,CM1P1AVI06=0.800
			strSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],Station=%s,Operator=%s,LotNum=%s",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, szPcName, sOperID, sLotID);

			for (int i = 0; i < gData.nAviApdCnt; i++) {
				strData.Format(",CM1P1AVI%02d=%s", i, gData.sVisionGV[i]);
				strSave += strData;
			}
			strData.Format(",CM1P1AVI%02d=%0.3lf\r\n", gData.nAviApdCnt, gData.dAssyLoadCellAvg);
			strSave += strData;

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	CString strMesPath, strMesFile, strMesSave;
	strMesPath.Format("%s%04d%02d%02d", MES_FOLDER_LOG, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strMesPath);

	strMesFile.Format("%s\\%04d%02d%02d.txt", strMesPath, time.wYear, time.wMonth, time.wDay);

	CFile fileMes;
	if (fileMes.Open(strMesFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			fileMes.SeekToEnd();

			strMesSave.Format("[%04d/%02d/%02d %02d:%02d:%02d],APD,PATH=%s\r\n", 
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, strFile);
			fileMes.Write(strMesSave, strMesSave.GetLength());

			fileMes.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	gData.bAviApdSave = TRUE;	// MES 보고 완료.

	g_csMesApd.Unlock();
}

void CMESInterface::Save_AviRmsData(CString sKey, CString sValue)
{
	CString strFile = (CString)MES_FOLDER_RMS + "Current_Recipe.txt";
	
	CFileFind finder;
	if (!finder.FindFile(strFile)) {
		CopyFile(gsCurrentDir + "\\System\\Current_Recipe_Org.txt", strFile, FALSE);
	}

	CIniFileCS INI(strFile);
	if (!INI.Check_File()) { AfxMessageBox("Current_Recipe.txt File Not Found!!!"); return; }

	INI.Set_String("Current_Recipe", "Recipe_Name_Handler", gData.sRecipeName);	// Model
	INI.Set_String("Current_Recipe", sKey, sValue);	// Change Data
}

void CMESInterface::FileAllDelete(CString sPath)
{
	BOOL bRes;
    CString path, file_path, file_name;

    path.Format("%s*.*", sPath);
    CFileFind finder;
    bRes = finder.FindFile(path);

    while(bRes) {
        bRes = finder.FindNextFile();
        if(!finder.IsDirectory()) {
            file_name = finder.GetFileName();
            file_path.Format("%s%s", sPath, file_name);

			DeleteFile(file_path);
        }
    }
}

void CMESInterface::ResultFileSearch()
{
	BOOL bRes;
    CString path, file_path, file_name;

	m_sResultFileName = "";
    path.Format("%s*.*", RESULT_FOLDER);
    CFileFind finder;
    bRes = finder.FindFile(path);

    while(bRes) {
        bRes = finder.FindNextFile();
        if(!finder.IsDirectory()) {
            file_name = finder.GetFileName();
            file_path.Format("%s%s", RESULT_FOLDER, file_name);

			m_sResultFileName = file_path;
			return;
        }
    }
}
