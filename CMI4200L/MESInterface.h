// MESInterface.h : 헤더 파일
//
#pragma once

class CMESInterface
{
public:
	CMESInterface();
	virtual ~CMESInterface();

private:
	int		m_nReadCnt;
	CString	m_sOperLotID;
	CString	m_sOperID;
	int		m_nOperCount;
	CString	m_sResultFileName;

	// APD Data
	int		m_nTCount;
	int		m_nSNo;
	CString	m_sLotID;
	CString	m_sDate[3];		//[0]:년, [1]:월, [2]:일
	CString	m_sTime[500];
	CString	m_sBarID[500];
	CString	m_sJudge[500];
	CString	m_sNGCode[500];
	CString	m_sNGText[500];
	int		m_nLoadTray[500];
	int		m_nLoadPocket[500];
	int		m_nOKTray[500];
	int		m_nOKPocket[500];
	int		m_nNGTray[500];
	int		m_nNGPocket[500];

	void Read_Result();
	void Clear_Result();
	void Write_APD();
	void Start_Send();
	void Set_Cancel(CString sLotID, int nCount, CString sOperID);	//Lot Cancel

	void Begin_MESThread();
	void End_MESThread();
	BOOL Get_ThreadMES() { return m_bThreadMES; }

	void Create_Folder(CString sPath);
	void MakeFolder(CString sPath);
	void FileAllDelete(CString sPath);
	void ResultFileSearch();
	char* UTF8ToANSI(const char *pszCode);

protected:
	BOOL	m_bThreadMES;
	CWinThread *m_pThreadMES;
	static UINT	Thread_MES(LPVOID lpVoid);

public:
	BOOL	m_bMESUse, m_bStart;
	CString	m_sMESResult, m_sMESLotID, m_sReasonCode, m_sReasonText;	//m_MESResult:0[OK], 1[NG]
	int		m_nMESCount, m_nMESSequence;	//0:Idle, 1:Start, 2:Started

	void Initialize(BOOL bMESUse);		//pEquipData->bUseMES
	void Set_MESUse(BOOL bMESUse);		//pEquipData->bUseMES
	void Set_Status(int	nStste);								//1:Run, 2:Stop, 3:Idle
	void Set_Alarm(int nType, int nAlarmID, CString sText );	//1:발생, 2:해제
	void Set_LotStart(CString sLotID, int nCount, CString sOperID);
	void Set_LotCancel(CString sLotID, int nCount, CString sOperID);
	void Set_LotEnd(CString sLotID, int nCount, CString sOperID, int nOKCount, int nNGCount);
	void Set_TackTime(double dTack, CString sLotID, int nCount, CString sStartTime, CString sEndTime);	//sStartTime="2017/12/04 14:00:10:
	void Set_Result(CString sLotID, CString sBarID, CString sJudge, CString sNGCode, CString NGText, int nLTray, int nLPno, int nUTray, int nUPno,int nNGTray, int nNGPno);
	void Save_AviApdData(CString sLotID, int nPortNo, CString sOperID);
	void Save_AviRmsData(CString sKey, CString sValue);

	void Clear_APDResult();
	BOOL Read_APDResult();
};

extern CMESInterface g_objMES;

///////////////////////////////////////////////////////////////////////////////
