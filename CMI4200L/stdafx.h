// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.
#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.
#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����

#define BTN_FACE	RGB(0xE8, 0xE8, 0xE8)

// Library Add
#include "LedStatic.h"
#include "CSControls.h"
#include "CSIniFile.h" 
#include "CSUdpSocket.h"
#include "CSGrid.h"
#include "CSClientSocket.h"

#include <math.h>

#ifdef _DEBUG
	#pragma comment(lib, "CSControlsD.lib")
	#pragma comment(lib, "CSIniFileD.lib")
	#pragma comment(lib, "CSUdpSocketD.lib")
	#pragma comment(lib, "CSGridD.lib")
	#pragma comment(lib, "CSClientSocketD.lib")
#else
	#pragma comment(lib, "CSControlsR.lib")
	#pragma comment(lib, "CSIniFileR.lib")
	#pragma comment(lib, "CSUdpSocketR.lib")
	#pragma comment(lib, "CSGridR.lib")
	#pragma comment(lib, "CSClientSocketR.lib")
#endif

#define SERIAL_NUMBER	"P5_NGVACUUM_ALIGN"
#define ECM_LOG			"D:\\EVMS\\TP\\log\\"
#define LOG_DELETE_DAY	 180		//6����
#define TRAY_MAX_CNT	 30			//30��
#define SIM_WAITTIMES	 1		//
#define SIM_WAITTIMEM	 1		//

//#define AJIN_BOARD_USE

//BWI Model Only(5x2)
#define EQ_TYPE_A1	//R44A,BWI
//#define EQ_TYPE_A2	//R44A,BWI

#if defined(EQ_TYPE_A1)		//R44A(MainAir1)
	#define MAIN_VERSION	"V3.5.02.a1"
	#define PICKER_4		// Load/Good/Unload Picker 5�� (�ִ� 6��)
#elif defined(EQ_TYPE_A2)	//R44A(MainAir2)
	#define MAIN_VERSION	"V3.5.02.a2"
	#define ALIGN_NEW		// Main Air 2�� (�⺻ 1��), �������� Master/Slave I/O ���� �ڹٲ�� ����.
	#define TRAY_CHECK2		// Tray Check Sensor 2�� (�⺻ 1��)
	#define PICKER_4		// Load/Good/Unload Picker 5�� (�ִ� 6��)
#endif

#define NG_PICKER_4

// #define PICKER_3			// Load/Good/Unload Picker 3
// #define PICKER_5			// Load/Good/Unload Picker 5�� (�⺻ 6��)
// #define NG_PICKER_3
// #define MODEL_SC			// F2122, F2324 �Ҹ������ؾ��ϴ� �ҷ��� Fiducial/Shiny edge �ΰ��� �̴�.
// #define CM_PRESS			// Only (K82), Vision Camera�� �Ǹ����� CM FPCB�� �����ֳ� ����
// #define MOVE_DATA_COPY	// Only (K82), �𵨺��� Move Data ���� �����Ҳ��� ������
/*
//F21,22 Picker 5ea, Ngpicker 4ea/5ea
//R13B Picker 5ea, NgPicker 4ea difine : ALIGN_NEW, TRAY_CHECK2, NG_PICKER_3
*/

extern CString gsCurrentDir;	// ���� ������Ʈ ����

typedef struct {
	CString sEnvPath;				// ȯ�漳�� ���� ���
	CString sLogPath;				// LOG ���� ���

	CString		sLotID;
	CString		sLotsID[5];
	CString		sOperID;
	CString		sDeviceName;
	int			nTrayJobCount;
	int			nTraysUseCnt[5];
	int			nCMJobCount;
	int			nCmsUseCnt[5];
	int			nLoadTrayCount;
	int			nEmptyTrayCount;
	int			nGoodTrayCount;
	int			nGoodTrayNo;
	BOOL		bOpMode;
	BOOL		bContinueLotEnd[5];

	CString		sRecipeName;		//Recipe Item
	int			nArrayW;			//[W]=[Y]= �� �����Ϳ��� �ҷ��´�
	int			nArrayL;			//[L]=[X]= �� �����Ϳ��� �ҷ��´� 
	double		dCMSizeW;
	double		dCMSizeL;
	double		dTrayFirstW;
	double		dTrayFirstL;
	double		dTrayPitchW;	//[W]=[Y]=20
	double		dTrayPitchL;	//[L]=[X]=33.6
	int			nCMMaxCount;
	double		dUnPitchW;		//[W]=[Y]
	double		dUnPitchL;		//[L]=[X]
	double		dIndexPitch;	//Index Pitch(28)

	int			LoadTrayWaitNo;			//Load Tray Wait���� Tray ��ȣ
	int			LoadTrayNo;				//Load Tray Tray ��ȣ
	int			PickerLoadTrayNo;		//Load Picker Picker Up�� Tray ��ȣ
	int			PickerLoadLineNo;		//Load Picker Picker Up�� Tray Line��ȣ
	int			PickerInfor[4][6];		//0:Empty, 1:OK, 2:NG	(0:Load, 1:NG, 2:Good, 3:Unload)

	int			PickerNGTrayNo;			//NG Picker Load Tray No
	int			PickerNGPoNo[6];		//NG Picker Load Pocket No
	int			PickerGdTrayNo[6];		//Good Picker Load Tray No
	int			PickerGdPoNo[6];		//Good Picker Load Pocket No
	int			PickerUnTrayNo[6];		//Unload Picker Load Tray No
	int			PickerUnPoNo[6];		//Unload Picker Load Pocket No
	int			IDXPoNo[8][6];			//

	int			IDXTrayNo[8][6];		//1~20
	int			IDXLineNo[8];			//1~8
	int			IDXInspec[8];			//1~8 (0:�̰˻�, 1:�˻�)
	int			IndexInfo[8][6];		//0:Empty, 1:OK, 2:NG, 3:�̰˻�,   (0:Load, 1:�˻�, 2:NG, 4:Good, 6:Unload)
	int			nIndexPos;				//1~8 (Index Table H/W sensor ��ġ)
	int			IndexJob[6];			//0:Wait, 1:OK  (0:Load, 1:�˻�, 2:Barcode, 3:NG, 4:Good, 5:Unload �۾��Ϸ� ��������)

	int			NG1TrayInfo[20][20];	//0:Empty, 1:OK, 2:NG, 3:�˻��� CM, 4:������ NG [y][x]=[w][l]
	int			NG2TrayInfo[20][20];	//0:Empty, 1:OK, 2:NG, 3:�˻��� CM, 4:������ NG [y][x]=[w][l]
	int			LoadTrayInfo[20][20];	//0:Empty, 1:OK, 2:NG, 3:�˻��� CM, 4:������ NG [y][x]=[w][l]
	int			GoodTrayInfo[20][20];	//0:Empty, 1:OK, 2:NG, 3:�˻��� CM, 4:������ NG [y][x]=[w][l]

	int			nNGTrayPos;				//0:Ready 1:NG1(Front), 2:NG2(Rear), 3:Moving (NG Tray ��ġ)
	int			nTrayPos[4];			//0:Load 1:NG1 2:NG2, 3:Unload Tray (����x=l 1^8 �ٹ�ȣ)

	int			nTotalCount;
	int			nStatus;				//1:Start, 2:Load_End, 3:NG_Tray��ó��, 4:Load Sort,Index Home
	int			NGPicNo;				//�۾����� Picker no
	int			NGIdxNo;				//�۾���� Index no(1~6)
	int			GDPicNo;				//�۾����� Picker no
	int			GDIdxNo;				//�۾���� Index no(1~6)
	int			nPicNo;					//Load,Unload Picker no
	int			nUpNo;					//Unload Picker Up line no
	int			nDownNo;				//Unload Picker Down line no
	int			nDownX;					//Unload Picker Down line�� X Array
	int			NGJobPic[10];			//1:�۾���� NG Picker No

	int			nNGTrayCmNo;			//NG Ʈ���� ����� �������� ���� 

	int			nErrType;				//1:��������, 2:�˻�����
	int			nErrCnt;				//Error ����
	int			nIndexX;				//Index 1~8
	int			nIndexY[6];				//Index ��ȣ(1~6)

	BOOL	bNGPickerUse[6];	//TRUE:Use, False:NotUse
	BOOL	bGoPickerUse[6];	//TRUE:Use, False:NotUse
	BOOL	bCleanOutMode;
	BOOL	bUseBar2Alarm;
	BOOL	bUseBar2NG;
	BOOL	bUnloadTraySort;
	BOOL	bUseDoorLock;
	BOOL	bUseNGVacuum;
	BOOL	bUseGDVacuum;
	BOOL	bNgSortFront;
	BOOL	bUseSeparationMode;
	int		nSeparationNgCode;			// �и����� �ϴ� NG Code
	BOOL	bGDPickerSort1;		// Index 1�� �������� ��� ����
	BOOL	bUnloadSortFront;	// Unload Tray ��� ���� �������� ��� ����
	BOOL	bUseDryRun;
	BOOL	bUseCMPress;
	int		nNGPercent;
	double	dNGCount;
	double	dNGSum;
	int		nDoorInterlock18;	//NG_Stage��ġ(1), Load Tray ������ġ(8) (0:Alarm, 1:No_Alarm)
	int		nDoorInterlock67;	//Unlaod Tray ����(6), ����(7)
	int		dDoorLockTime;		//Min
	DWORD	dwDoorStartTime;

	BOOL	bCapTrayLoad;
	CString sCLotID;
	int		nCGoodTrayCount;
	int		nCTrayCmCnt;
	int		nCUnloadLotIndex;

	BOOL	bCapAttachWork;	// CapAttach LotEnd�Ǿ�� ���ο� ���� ������ �� �ְ� ���ش�.
	int		nPortNo;		// AVI LotEnd ���ڸ��� ������ �� �ֵ��� Cap Attach ��񿡼� Port��ȣ�� �޴´�.

	int		nLotIdsIndex;		// Lot Barcode �Է� ����

	int		nTrigDelayIns;
	int		nTrigSetIns;
	int		nTrigDelayBar;
	int		nTrigSetBar;
	int		nLight[8];

	int		nPickCnt;

	int		nVisionFOBMode;	// Vision���� FOB ��带 ����ϴ��� Ȯ��. -1: Send Command, 0: FOB Mode Off, 1: FOB Mode On
	BOOL	bCheckStartComplete;

	double	dAssyLoadCellAvg;		// APD�� �Է��� CapForce ��.

	int		nVisionTimeOut;
	int		nMesTimeOut;
	BOOL	bAviApdRequest;			// Vision APD ������ ��û
	BOOL	bAviApdReceive;			// Vision APD ������ �޾ҳ� Ȯ��
	BOOL	bAviApdSave;			// APD ���� ����.
	BOOL	bAviApdFileChk;			// APD ��� ���� Ȯ��.
	BOOL	bAPDResultErr;			// APD ��� ���� �׸� ��� Ȯ��.
	int		nAviApdCnt;				// Vision APD �̹��� GV�� ����
	CString sVisionGV[10];			// Single �̹��� ������ 4~6�� �̴�.
	CString sAPDNgItem;
	//// ListBox
	int		nType;
	CString	sListName;
	CString	sYYMMDD;
	int		nNGPos;
	CString	sComName;
	CString	sCaption[10];

	CString sAlarmTime[3];
	CString sAlarmList[3];

	int		m_nMS;
	BOOL	m_bTowerOn;
	BOOL	m_bBuzzerOff;
	BOOL	m_bErrorShow;

	int		nInsTrayNo;
	int		nInsLineNo;
	int		nLotInfoBlockDelay;

	BOOL	bUseAllPass;
} GLOVAL_DATA;
extern  GLOVAL_DATA	gData;

typedef struct {
	CString	sLotID;
	CString sStartTime;
	CString sEndTime;
	CString sMESStartTime;
	long	lLotStart;
	long	lLotEnd;
	int		nTrayCount;
	int		nCMCount;
	double  dTackTime;

	// Inline Mode�϶� ĸ ���� �Ϸ� �� MES �ϰ��ϵ��� ���� ����.
	CString sCALotID;
	CString sCAStartTime;
	CString sCAEndTime;
	DWORD	dwCALotStart;
	DWORD	dwCALotEnd;
	int		nCATrayCount;
	int		nCACmCount;
	int		nCAGoodCount;
	int		nCANgCount;

	long	lTackData[10];
	int		nLog[10];

	CString sBarLoad[30][60];
	CString sNGCode[30][60];
	CString sNGText[30][60];
	int		nInsResult[30][60];	//Good=1, NG=2,
	int		nBarResult[30][60];	//OK=1, ������NG=4, Read Fail=5, Grab fail=6, Skip=9
	int		nInsNG[30][60];		//
	int		nGoodCnt;
	int		nNGCnt;
	int		nLfNGCnt;
	int		nSeNGCnt;
	int		nBsNGCnt;
	int		nNGT;
	int		nNGC;
	int		nGDT;
	int		nG1DC;
	int		nCmJigNo[30][60][10]; // CM Jig ���� ���� [Tray][CM][Unit]
								 // Unit 0:Load Stage, 1:Load Picker, 2:Index Load No, 3:Index Jig No, 4:NG Picker, 5:Good Picker, 6:Unload Picker
} GLOVAL_LOTDATA;
extern  GLOVAL_LOTDATA	gLot;

typedef struct {
	int		nType;		//1:Start
	CString	sLotID;
	CString sAlmNo;
	CString sAlmMsg;
	CString sStartTime;
	CString sEndTime;
	long	lStartTime;
	long	lEndTime;
	long	lProcTime;
} GLOVAL_ALARMDATA;
extern  GLOVAL_ALARMDATA	gAlm;

typedef struct {
	int		nType;			//1:Clear
	double  dTackTime;
	double	dTack[24][50];	//49:����
	int		dCount[2];		//0:7~19h, 1:19~7h
} GLOVAL_TOTALDATA;
extern  GLOVAL_TOTALDATA	gTD;

typedef struct {
	int		nType;			//nType:1[����], 2[����] 3[����]
	int		nWriteHH;		//��Ͻð�
	int		nOpenStart;		//1:Start
	DWORD	dwOpenStartTime;
	int		nOpenTime;
} GLOVAL_INTERLOCKDATA;
extern  GLOVAL_INTERLOCKDATA	gIt;

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
