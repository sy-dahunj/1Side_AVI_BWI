// LogFile.h : 헤더 파일
//
#pragma once

class CLogFile  
{
private:
	static CLogFile *m_pInstance;

	BOOL m_bThreadLog;

public:
	static CLogFile* Get_Instance();
	void Delete_Instance();
	
	void Create_Folder(CString sPath);
	void MakeFolder(CString sPath);

public:
	CLogFile();
	virtual ~CLogFile();

public:
	void Save_AlarmLog(CString strLog);
	void Save_AlarmResetLog(CString strLog);
	void Save_HistoryLog(CString strLog);
	void Save_JobListLog(CString strLog);
	void Save_HandlerLog(CString strLog);
	void Save_InspectorLog(CString strLog);
	void Save_SBCNgLog(CString strLog);
	void Save_LotLog(CString strLog);
	void Save_AgentLog(CString strLog);
	void Save_TestLog(CString strLog);
	void Save_ECMLog(int nType, CString strLog);	//nType:1[Alarm], 2[Joblist] 3[Inspect]
	void Save_AVIError(CString sLog);
	void Save_CapAttachLog(CString strLog);
	void Save_Interlock(int nType);					//nType:1[정시], 2[해제] 3[설정]
	void Save_CmTrackingLog(CString strOut, int nTrayCount, int nPosX, int nPosY, int nTrayNo, int nCmNo);
	void Save_ECMTracking(CString sLog, int nTrayCount, int nPosX, int nPosY, int nTrayNo, int nCmNo);
	void Save_PCLog(CString sLog);
	void Save_MCCLog(CString strLog);


	void Set_ThreadLog(BOOL bOn) { m_bThreadLog = bOn; }
	BOOL Get_ThreadLog() { return m_bThreadLog; }
};

///////////////////////////////////////////////////////////////////////////////
