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

// test�� (gjc)
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

	// ��� Lot Data
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

	// �˻� Result Data
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
