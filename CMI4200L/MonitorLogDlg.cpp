// MonitorLogDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMI4200L.h"
#include "MonitorLogDlg.h"
#include "afxdialogex.h"
#include "ListBoxDlg.h"
// CMonitorLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMonitorLogDlg, CDialogEx)

CMonitorLogDlg::CMonitorLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonitorLogDlg::IDD, pParent)
{
}

CMonitorLogDlg::~CMonitorLogDlg()
{
}

void CMonitorLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	DDX_Control(pDX, IDC_LABEL_0, m_Label);
	DDX_Control(pDX, IDC_REDT_LOG_DISPLAY, m_redtLogDisplay);
	DDX_Control(pDX, IDC_STC_LOG_DATE, m_stcLogDate);
	DDX_Control(pDX, IDC_BTN_GO_TODAY, m_btnGoToday);
	DDX_Control(pDX, IDC_CAL_MONTH, m_calMonth);
	DDX_Control(pDX, IDC_RDO_LOG_ALARM, m_rdoLogAlarm);
	DDX_Control(pDX, IDC_RDO_LOG_JOB_LIST, m_rdoLogJobList);
	DDX_Control(pDX, IDC_RDO_LOG_HANDLER, m_rdoLogHandler);
	DDX_Control(pDX, IDC_RDO_LOG_INSPECTOR, m_rdoLogInspector);
}

BEGIN_MESSAGE_MAP(CMonitorLogDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_GO_TODAY, &CMonitorLogDlg::OnBnClickedBtnGoToday)
	ON_NOTIFY(MCN_SELCHANGE, IDC_CAL_MONTH, &CMonitorLogDlg::OnMcnSelchangeCalMonth)
	ON_BN_CLICKED(IDC_RDO_LOG_ALARM, &CMonitorLogDlg::OnBnClickedRdoLogAlarm)
	ON_BN_CLICKED(IDC_RDO_LOG_JOB_LIST, &CMonitorLogDlg::OnBnClickedRdoLogJobList)
	ON_BN_CLICKED(IDC_RDO_LOG_HANDLER, &CMonitorLogDlg::OnBnClickedRdoLogHandler)
	ON_BN_CLICKED(IDC_RDO_LOG_INSPECTOR, &CMonitorLogDlg::OnBnClickedRdoLogInspector)
END_MESSAGE_MAP()

// CMonitorLogDlg 메시지 처리기입니다.

BOOL CMonitorLogDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 	SetWindowPos(this, 120, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	SetWindowPos(this, 0, 70, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_rdoLogAlarm.SetCheck(TRUE);

	SYSTEMTIME time;
	GetLocalTime(&time);
	gData.sYYMMDD.Format("%04d%02d%02d", time.wYear, time.wMonth, time.wDay);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMonitorLogDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();
}

BOOL CMonitorLogDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMonitorLogDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		OnBnClickedBtnGoToday();
	}
}

void CMonitorLogDlg::OnBnClickedBtnGoToday()
{
	CTime timeDate;

	m_calMonth.GetToday(timeDate);
	m_calMonth.SetCurSel(timeDate);

	CString strDate = timeDate.Format("%Y-%m-%d");
	m_stcLogDate.SetWindowText(strDate);

	SYSTEMTIME sysTime;
	m_calMonth.GetCurSel(&sysTime);
	gData.sYYMMDD.Format("%04d%02d%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay);

	Read_LogFile();
}

void CMonitorLogDlg::OnMcnSelchangeCalMonth(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 1. MS Bug ////////////////////////////////////////////////////////////
	// 	CTime timeDate;
	// 	m_calMonth.GetCurSel(timeDate);
	// 	
	// 	CString strDate = timeDate.Format("%Y-%m-%d");
	// 	m_stcLogDate.SetWindowText(strDate);
	/////////////////////////////////////////////////////////////////////////

	// 2. Bug 수정 //////////////////////////////////////////////////////////
	SYSTEMTIME sysTime;
	m_calMonth.GetCurSel(&sysTime);
	sysTime.wHour = sysTime.wMinute = sysTime.wSecond = sysTime.wMilliseconds = 0;

	CString strDate;
	strDate.Format("%04d-%02d-%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	m_stcLogDate.SetWindowText(strDate);
	gData.sYYMMDD.Format("%04d%02d%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	/////////////////////////////////////////////////////////////////////////

	Read_LogFile();

	*pResult = 0;
}

void CMonitorLogDlg::OnBnClickedRdoLogAlarm()
{
	Read_LogFile();
}

void CMonitorLogDlg::OnBnClickedRdoLogJobList()
{
	Read_LogFile();
}

void CMonitorLogDlg::OnBnClickedRdoLogHandler()
{
	gData.nType = 0;
	CListBoxDlg dlgListBox;
	int nRst = dlgListBox.DoModal();

	if(gData.sListName != "")
		Read_LogFile();
}

void CMonitorLogDlg::OnBnClickedRdoLogInspector()
{
	Read_LogFile();
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CMonitorLogDlg::Initial_Controls() 
{
	for (int i = 0; i < 2; i++) m_Group[i].Init_Ctrl("바탕", 14, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_Label.Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

//	m_fontREdit.CreatePointFont(110, "바탕");
//	m_fontREdit.CreatePointFont(110, "굴림체");
	m_fontREdit.CreatePointFont(110, "Lucida Console");
	m_redtLogDisplay.SetFont(&m_fontREdit, FALSE);

	m_stcLogDate.Init_Ctrl("바탕", 18, TRUE, RGB(0xFF, 0x20, 0x20), RGB(0xF0, 0xE0, 0xFF));

	m_btnGoToday.Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);

	//m_fontCalendar.CreatePointFont(220, "바탕");
	m_fontCalendar.CreatePointFont(150, "바탕");
	m_calMonth.SetFont(&m_fontCalendar, TRUE);

	m_rdoLogAlarm.Init_Ctrl("바탕", 14, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoLogJobList.Init_Ctrl("바탕", 14, TRUE, RGB(0x00, 0x80, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoLogHandler.Init_Ctrl("바탕", 14, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	m_rdoLogInspector.Init_Ctrl("바탕", 14, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
}

DWORD CALLBACK CMonitorLogDlg::StreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CFile *pFile = (CFile*)dwCookie;
	*pcb = pFile->Read(pbBuff, cb);
	return 0;
}

void CMonitorLogDlg::Read_LogFile()
{
// 	m_redtLogDisplay.Clear();
//	m_redtLogDisplay.ShowWindow(SW_HIDE);
//	m_redtLogDisplay.ShowWindow(SW_SHOW);

	m_redtLogDisplay.SetSel(0, -1);
	m_redtLogDisplay.SetWindowText("");

	SYSTEMTIME sysTime;
	m_calMonth.GetCurSel(&sysTime);
	sysTime.wHour = sysTime.wMinute = sysTime.wSecond = sysTime.wMilliseconds = 0;

	CString strDate, strFile;
	strDate.Format("%04d%02d%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay);

	if		(m_rdoLogAlarm.GetCheck()) strFile.Format("LOG/Alarm/%s_000000_Alarm.txt", strDate);
	else if (m_rdoLogJobList.GetCheck()) strFile.Format("LOG/JobList/%s_000000_JobList.txt", strDate);
	else if (m_rdoLogHandler.GetCheck()) strFile.Format("LOG/LotData/%04d/%02d/%02d/%s.txt", sysTime.wYear, sysTime.wMonth, sysTime.wDay, gData.sListName);
	else if (m_rdoLogInspector.GetCheck()) strFile.Format("LOG/Inspector/%s_000000_Inspector.txt", strDate);
	else return;

	CFileFind Finder;
	if (!Finder.FindFile(strFile, NULL)) return;

	CFile *pFile = NULL;
	try {
		pFile = new CFile(strFile, CFile::modeRead | CFile::shareDenyNone);

		EDITSTREAM strm;
		strm.dwCookie = (DWORD)pFile;
		strm.pfnCallback = StreamInCallback;

		long lResult = m_redtLogDisplay.StreamIn(SF_TEXT, strm);

		pFile->Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
	delete pFile;
}

///////////////////////////////////////////////////////////////////////////////
