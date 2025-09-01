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
#include "CSSerialPort.h"
#include "CSUdpSocket.h"
#include "CSServerSocket.h"
#ifdef _DEBUG
	#pragma comment(lib, "CSControlsD.lib")
	#pragma comment(lib, "CSIniFileD.lib")
	#pragma comment(lib, "CSSerialPortD.lib")
	#pragma comment(lib, "CSUdpSocketD.lib")
	#pragma comment(lib, "CSServerSocketD.lib")
#else
	#pragma comment(lib, "CSControlsR.lib")
	#pragma comment(lib, "CSIniFileR.lib")
	#pragma comment(lib, "CSSerialPortR.lib")
	#pragma comment(lib, "CSUdpSocketR.lib")
	#pragma comment(lib, "CSServerSocketR.lib")
#endif

#define MAIN_VERSION	"V1.0.0"
#define SERIAL_NUMBER	"S1502-001D15"

//#define AJIN_BOARD_USE
#define INSPECTOR_USE
//#define HSMS_USE
//#define BARCODE_USE

// test시 (gjc)
//#define AJIN_BOARD_USE
//#define RFID_USE
//#define LASER_USE
//#define ELECT_USE
//#define INSPECTOR_USE
//#define HSMS_USE
//#define ADR_USE
//#define ADR_D_USE
//#define OHT_USE
//// #define FTP_USE


#ifdef AJIN_BOARD_USE
	#define AJIN_CONNECT
#endif

typedef struct {
	int		nTableSts;	// 0:wait, 1:Load Send, 2:Scan1, 3:Scan2, 4:Scan3, 5:Scan4, 6:Review, 7:Inspection
	int		nSendID;

	// 장비 Lot Data
	CString	sFileName;
	CString	sLotID;
	CString	sLotStartDate;
	CString	sLotStartTime;
	CString	sLotEndDate;
	CString	sLotEndTime;
	CString sVersion;
	CString sSerialNo;
	CString sShiftID;
	CString sOperID;
	CString sDeviceName;
	CString sModelName;
	CString sPackageName;
	CString sSID[100];	//1~60
	int		nMaxCnt;
	int		nTotCnt;

	// time
	long	lLotStart;
	long	lLotEnd;

	// 검사 Result Data
	int		nNGTotCnt;
	int		nRstCnt;
	CString sRstItem[20];
	int		nNGCnt[20];

	// ListBox
	int		nType;
	CString	sListName;
	CString	sYYMMDD;
} GLOVAL_DATA;
extern  GLOVAL_DATA	gData;

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
