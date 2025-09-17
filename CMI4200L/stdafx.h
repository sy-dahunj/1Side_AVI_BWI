// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.
#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.
#include <afxdisp.h>        // MFC 자동화 클래스입니다.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원

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
#define LOG_DELETE_DAY	 180		//6개월
#define TRAY_MAX_CNT	 30			//30개
#define SIM_WAITTIMES	 1		//
#define SIM_WAITTIMEM	 1		//

//#define AJIN_BOARD_USE

//BWI Model Only(5x2)
#define EQ_TYPE_A1	//R44A,BWI
//#define EQ_TYPE_A2	//R44A,BWI

#if defined(EQ_TYPE_A1)		//R44A(MainAir1)
	#define MAIN_VERSION	"V3.5.02.a1"
	#define PICKER_4		// Load/Good/Unload Picker 5개 (최대 6개)
#elif defined(EQ_TYPE_A2)	//R44A(MainAir2)
	#define MAIN_VERSION	"V3.5.02.a2"
	#define ALIGN_NEW		// Main Air 2개 (기본 1개), 스테이지 Master/Slave I/O 순서 뒤바뀌어 있음.
	#define TRAY_CHECK2		// Tray Check Sensor 2개 (기본 1개)
	#define PICKER_4		// Load/Good/Unload Picker 5개 (최대 6개)
#endif

#define NG_PICKER_4

// #define PICKER_3			// Load/Good/Unload Picker 3
// #define PICKER_5			// Load/Good/Unload Picker 5개 (기본 6개)
// #define NG_PICKER_3
// #define MODEL_SC			// F2122, F2324 불리배출해야하는 불량이 Fiducial/Shiny edge 두가지 이다.
// #define CM_PRESS			// Only (K82), Vision Camera옆 실린더로 CM FPCB를 눌러주냐 마냐
// #define MOVE_DATA_COPY	// Only (K82), 모델별로 Move Data 따로 저장할꺼냐 말꺼냐
/*
//F21,22 Picker 5ea, Ngpicker 4ea/5ea
//R13B Picker 5ea, NgPicker 4ea difine : ALIGN_NEW, TRAY_CHECK2, NG_PICKER_3
*/

extern CString gsCurrentDir;	// 현재 프로젝트 폴더

typedef struct {
	CString sEnvPath;				// 환경설정 파일 경로
	CString sLogPath;				// LOG 파일 경로

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
	int			nArrayW;			//[W]=[Y]= 모델 데이터에서 불러온다
	int			nArrayL;			//[L]=[X]= 모델 데이터에서 불러온다 
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

	int			LoadTrayWaitNo;			//Load Tray Wait대기시 Tray 번호
	int			LoadTrayNo;				//Load Tray Tray 번호
	int			PickerLoadTrayNo;		//Load Picker Picker Up시 Tray 번호
	int			PickerLoadLineNo;		//Load Picker Picker Up시 Tray Line번호
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
	int			IDXInspec[8];			//1~8 (0:미검사, 1:검사)
	int			IndexInfo[8][6];		//0:Empty, 1:OK, 2:NG, 3:미검사,   (0:Load, 1:검사, 2:NG, 4:Good, 6:Unload)
	int			nIndexPos;				//1~8 (Index Table H/W sensor 위치)
	int			IndexJob[6];			//0:Wait, 1:OK  (0:Load, 1:검사, 2:Barcode, 3:NG, 4:Good, 5:Unload 작업완료 유무관리)

	int			NG1TrayInfo[20][20];	//0:Empty, 1:OK, 2:NG, 3:검사전 CM, 4:전공정 NG [y][x]=[w][l]
	int			NG2TrayInfo[20][20];	//0:Empty, 1:OK, 2:NG, 3:검사전 CM, 4:전공정 NG [y][x]=[w][l]
	int			LoadTrayInfo[20][20];	//0:Empty, 1:OK, 2:NG, 3:검사전 CM, 4:전공정 NG [y][x]=[w][l]
	int			GoodTrayInfo[20][20];	//0:Empty, 1:OK, 2:NG, 3:검사전 CM, 4:전공정 NG [y][x]=[w][l]

	int			nNGTrayPos;				//0:Ready 1:NG1(Front), 2:NG2(Rear), 3:Moving (NG Tray 위치)
	int			nTrayPos[4];			//0:Load 1:NG1 2:NG2, 3:Unload Tray (세로x=l 1^8 줄번호)

	int			nTotalCount;
	int			nStatus;				//1:Start, 2:Load_End, 3:NG_Tray후처리, 4:Load Sort,Index Home
	int			NGPicNo;				//작업가능 Picker no
	int			NGIdxNo;				//작업대상 Index no(1~6)
	int			GDPicNo;				//작업가능 Picker no
	int			GDIdxNo;				//작업대상 Index no(1~6)
	int			nPicNo;					//Load,Unload Picker no
	int			nUpNo;					//Unload Picker Up line no
	int			nDownNo;				//Unload Picker Down line no
	int			nDownX;					//Unload Picker Down line네 X Array
	int			NGJobPic[10];			//1:작업대상 NG Picker No

	int			nNGTrayCmNo;			//NG 트레이 몇번에 놓였는지 저장 

	int			nErrType;				//1:정보있음, 2:검사있음
	int			nErrCnt;				//Error 수량
	int			nIndexX;				//Index 1~8
	int			nIndexY[6];				//Index 번호(1~6)

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
	int		nSeparationNgCode;			// 분리배출 하는 NG Code
	BOOL	bGDPickerSort1;		// Index 1번 기준으로 모듈 정렬
	BOOL	bUnloadSortFront;	// Unload Tray 장비 정면 기준으로 모듈 적재
	BOOL	bUseDryRun;
	BOOL	bUseCMPress;
	int		nNGPercent;
	double	dNGCount;
	double	dNGSum;
	int		nDoorInterlock18;	//NG_Stage위치(1), Load Tray 투입위치(8) (0:Alarm, 1:No_Alarm)
	int		nDoorInterlock67;	//Unlaod Tray 투입(6), 배출(7)
	int		dDoorLockTime;		//Min
	DWORD	dwDoorStartTime;

	BOOL	bCapTrayLoad;
	CString sCLotID;
	int		nCGoodTrayCount;
	int		nCTrayCmCnt;
	int		nCUnloadLotIndex;

	BOOL	bCapAttachWork;	// CapAttach LotEnd되어야 새로운 랏을 투입할 수 있게 해준다.
	int		nPortNo;		// AVI LotEnd 되자마자 투입할 수 있도록 Cap Attach 장비에서 Port번호를 받는다.

	int		nLotIdsIndex;		// Lot Barcode 입력 순서

	int		nTrigDelayIns;
	int		nTrigSetIns;
	int		nTrigDelayBar;
	int		nTrigSetBar;
	int		nLight[8];

	int		nPickCnt;

	int		nVisionFOBMode;	// Vision에서 FOB 모드를 사용하는지 확인. -1: Send Command, 0: FOB Mode Off, 1: FOB Mode On
	BOOL	bCheckStartComplete;

	double	dAssyLoadCellAvg;		// APD에 입력할 CapForce 값.

	int		nVisionTimeOut;
	int		nMesTimeOut;
	BOOL	bAviApdRequest;			// Vision APD 데이터 요청
	BOOL	bAviApdReceive;			// Vision APD 데이터 받았나 확인
	BOOL	bAviApdSave;			// APD 파일 저장.
	BOOL	bAviApdFileChk;			// APD 결과 파일 확인.
	BOOL	bAPDResultErr;			// APD 결과 파일 항목 결과 확인.
	int		nAviApdCnt;				// Vision APD 이미지 GV값 개수
	CString sVisionGV[10];			// Single 이미지 수량은 4~6장 이다.
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

	// Inline Mode일때 캡 조립 완료 후 MES 완공하도록 정보 저장.
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
	int		nBarResult[30][60];	//OK=1, 전공정NG=4, Read Fail=5, Grab fail=6, Skip=9
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
	int		nCmJigNo[30][60][10]; // CM Jig 정보 저장 [Tray][CM][Unit]
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
	double	dTack[24][50];	//49:수량
	int		dCount[2];		//0:7~19h, 1:19~7h
} GLOVAL_TOTALDATA;
extern  GLOVAL_TOTALDATA	gTD;

typedef struct {
	int		nType;			//nType:1[정시], 2[해제] 3[설정]
	int		nWriteHH;		//등록시간
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
