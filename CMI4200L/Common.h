// Common.h : 헤더 파일
// bb
#pragma once

#include "afxinet.h"	// FTP Connection

#define	INITIAL_MAIN			1
#define	INITIAL_LOAD1			2
#define	INITIAL_LOAD2			3
#define	INITIAL_UNLOAD1			4
#define	INITIAL_UNLOAD2			5
#define	INITIAL_INSPECT			6
#define	INITIAL_NGPICKER		7
#define	INITIAL_GDPICKER		8
#define	INITIAL_LDPICKER		9
#define	INITIAL_ULPICKER		10
#define	INITIAL_INDEXT			11
#define	INITIAL_NGTRAY			12

#define	AUTO_LOAD1				21
#define	AUTO_LOAD2				22
#define	AUTO_UNLOAD1			23
#define	AUTO_UNLOAD2			24
#define	AUTO_INSPECT			25
#define	AUTO_NGPICKER			26
#define	AUTO_GDPICKER			27
#define	AUTO_LDPICKER			28
#define	AUTO_ULPICKER			29
#define	AUTO_INDEXT				30
#define	AUTO_NGTRAY				31
#define	AUTO_BARCODE			32

// Network Drive
#define NETWORK_ADR_DRIVE	"R:"
#define NETWORK_ADR_FOLDER	"\\Inspection"

#define NETWORK_EQP_DRIVE	"S:"
#define NETWORK_EQP_FOLDER	"\\eqpmnt"

#define NETWORK_FTP_FOLDER	"\\Inspection"

#define TYPE_AUTO			0
#define TYPE_LOAD			1
#define TYPE_UNLOAD			2

// CCommon

class CCommon : public CWnd
{
	DECLARE_DYNAMIC(CCommon)

private:
	static CCommon *m_pInstance;
	CRect m_ScreenRect;

	CRect Get_Position() { return m_ScreenRect; }
	void Set_Position(int left, int top, int right, int bottom) { m_ScreenRect = CRect(left, top, right, bottom); }

public:
	static CCommon *Get_Instance();
	void Delete_Instance();

public:
	CCommon();
	virtual ~CCommon();

protected:
	DECLARE_MESSAGE_MAP()

private:
	DWORD	m_dwLoopInitMainStart,		m_dwLoopInitMainDelay;
	DWORD	m_dwLoopInitLoadS1Start,	m_dwLoopInitLoadS1Delay;
	DWORD	m_dwLoopInitLoad2Start,		m_dwLoopInitLoad2Delay;
	DWORD	m_dwLoopInitUnload1Start,	m_dwLoopInitUnload1Delay;
	DWORD	m_dwLoopInitUnload2Start,	m_dwLoopInitUnload2Delay;
	DWORD	m_dwLoopInitInspectStart,	m_dwLoopInitInspectDelay;
	DWORD	m_dwLoopInitNGPickStart,	m_dwLoopInitNGPickDelay;
	DWORD	m_dwLoopInitGDPickStart,	m_dwLoopInitGDPickDelay;
	DWORD	m_dwLoopInitLDPickStart,	m_dwLoopInitLDPickDelay;
	DWORD	m_dwLoopInitULPickStart,	m_dwLoopInitULPickDelay;
	DWORD	m_dwLoopInitIndexStart,		m_dwLoopInitIndexDelay;
	DWORD	m_dwLoopInitNGTrayStart,	m_dwLoopInitNGTrayDelay;

	DWORD	m_dwLoopLoadS1Start,		m_dwLoopLoadS1Delay;
	DWORD	m_dwLoopLoad2Start,			m_dwLoopLoad2Delay;
	DWORD	m_dwLoopUnload1Start,		m_dwLoopUnload1Delay;
	DWORD	m_dwLoopUnload2Start,		m_dwLoopUnload2Delay;
	DWORD	m_dwLoopInspectStart,		m_dwLoopInspectDelay;
	DWORD	m_dwLoopNGPickStart,		m_dwLoopNGPickDelay;
	DWORD	m_dwLoopGDPickStart,		m_dwLoopGDPickDelay;
	DWORD	m_dwLoopLDPickStart,		m_dwLoopLDPickDelay;
	DWORD	m_dwLoopULPickStart,		m_dwLoopULPickDelay;
	DWORD	m_dwLoopIndexStart,			m_dwLoopIndexDelay;
	DWORD	m_dwLoopNGTrayStart,		m_dwLoopNGTrayDelay;
	DWORD	m_dwLoopBarcodeStart,		m_dwLoopBarcodeDelay;

	BOOL	m_bPowerOffRelay;		// Y101 : Power Off Relay
	BOOL	m_bSystemReadyRelay;	// Y013 : System Ready (Reset SW)

	int		m_nStatus;				// ADR Server Machine Status Update Loop
	BOOL	m_bInsideLamp;			// Y015 : Inner Light

	CString Get_AdrIpAddress(CString sName);	// Adr Ip
	CString Get_MonitorName(CString sName);		// Monitor File

	BOOL Open_Ftp();
	void Close_Ftp();

	CInternetSession	m_Session;
	CFtpConnection		*m_pFtp;

public:
	CString	m_sMessage;

	void DoEvents(int nSleep = 0);
	void Delay_Time(DWORD msec);

	void Set_LoopTime(int nRun, DWORD msec);
	BOOL Over_LoopTime(int nRun);
	BOOL Delay_LoopTime(int nRun, DWORD msec);

	BOOL Check_Position(int nAxis, int nMoveIdx = -1);
	void Move_Position(int nAxis, int nMoveIdx = -1);

	void Show_Error(int nErrNo);
	void Set_ErrorSubMessage(CString sErrMsg) { m_sMessage = sErrMsg; }
	int Show_MsgBox(int nBtnCnt, CString sMsg);
	int Show_NumPad(CString sOld, CString &sNew);
	int Show_KeyPad(CString &sKey);
	int Show_Password();

	BOOL Check_MainEmgAir();
	BOOL Check_MainDoor();

	BOOL Check_ServoOn();
	BOOL Check_DirveAlarm();
	BOOL Check_EndLimit();
	BOOL Check_HomeDone();
	BOOL Check_Run(int nAxis);

	void Locking_MainDoor(BOOL bLock, BOOL bAuto = FALSE);

	void Check_InsideLamp();
	void Check_SystemReady();
	void Check_PowerOffSw();

	void Check_MonitorEQP(int nStatus);
	BOOL Connect_NetworkDrive(CString sDrive, CString sFolder);
	void Copy_AdrData();
	void Copy_AdrDData();
	///////////////////////

	void Get_RAMSize(CString &strRAM);
	void Get_CPUInfo(CString &strCPU);
	void Get_HardInfo(CString &strHardDisk);

	void Backup_File(CString strPath, CString strName);	// System Folder
	int	 Get_Random(int nStart, int nEnd);
///////////////////////////////////////////////////////////////////////////
	void	Wait_Time(DWORD msec);
	void	MakeFolder(CString sPath);
	void	MakeFTPFolder(CString sPath);
	CString	Make_HexToChar(CString sRecv);
	long	Make_CharToLong(CString sRecv);
	int		Make_HexToInt1st(long lValue);
	int		Make_HexToInt2nd(long lValue);
	void	Make_LongToSplit(long lValue);
	long	Make_LongToMix(long l1st, long l2nd);
	CString Make_HashKey(CString sGlassID, int Seq);
	DWORD	setAbit(DWORD x, int n, int b);
	void	Set_TimeUpdate(CString sTime);	// sTime: "2000--0011 12:30:30 000"

///////////////////////////////////////////////////////////////////////////
	double	m_dP1X[2], m_dP1Y1, m_dP1Y2, m_dP1Z;	//Load
	double	m_dP2X1, m_dP2X2, m_dP2Y[2], m_dP2Z;	//Unload
	double	m_dP3X, m_dP3Y, m_dP3Z;				//NG Picker
	double	m_dP4Y, m_dP4Z;						//Good Picker

	void	PickerNG_UpMove(int nPNo, int nXX);							// => m_dP3Z, m_dP3X
	void	PickerNG_DnMove(int nPNo, int nXX, int nYY, int nTrayNo);	// => m_dP3Z, m_dP3X(Picker)
	void	PickerNGStageMove(int nLine, int nTrayNo);					// => m_dP3Y(Stage)
	void	PickerLoad_Move(int nType, int nYY, int nTrayNo);	//Load Picker(1)
	void	PickerUnload_Move(int nType, int nYY, int nTrayNo);	//Unload Picker(2)
	void	PickerGood_Move(int nType, int nPNo, int nYY);		//Good Picker(3)

	void	Set_NGPickerUp(int nNo);
	void	Set_NGPickerDown(int nNo);
	BOOL	Get_NGPickerDown(int nNo);
	void	Set_NGPickerClose(int nNo);
	BOOL	Get_NGPickerClose(int nNo);
};

///////////////////////////////////////////////////////////////////////////////
