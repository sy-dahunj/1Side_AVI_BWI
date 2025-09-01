// CapAttachUDP.h : 헤더 파일
//
#pragma once

// CCapAttachUDP

class CCapAttachUDP : public CWnd
{
	DECLARE_DYNAMIC(CCapAttachUDP)

public:
	CCapAttachUDP();
	virtual ~CCapAttachUDP();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUdpReceive(WPARAM wLocalPort, LPARAM lParam);

private:
	CUdpSocketCS	m_UdpCapAttach;

	CString		m_strRecvCmd;

	BOOL	m_bOpened;
	BOOL	m_bConnected;
	int		m_nStatusCapAttach;
	
	BOOL	m_bJudgeReq[2][40][45];	// 판정 요청
	DWORD	m_dwReqStart[2][40][45];	// 요청 시작
	BOOL	m_bJudgeDone[2][40][45];	// 판정 완료

	void Get_ConnectRequest();
	void Get_ConnectReply();
	void Get_ConnectEnd();
	void Get_StatusRequest();
	void Get_StatusReply(CString sStatus);
	void Get_StatusUpdate(CString sStatus);
	void Get_TrayUnload();
	void Get_LotReply(CString sPortNo);
	void Get_LotEnd(CString sLotID, CString sPortNo);
	void Get_TimeUpdate(CString sTime);
	void Get_APDReply(CString sCapForceAvg);

	void Send_Command(CString strSend);

public:
	BOOL Initialize();
	void Terminate();
	void Reset();
	void PortReset(int PNo);

	void Set_ConnectRequest();
	void Set_ConnectReply();
	void Set_ConnectEnd();
	void Set_StatusRequest();
	void Set_StatusReply(int nStatus);
	void Set_StatusUpdate(int nStatus);
	void Set_LotStart(int nPortNo);
	void Set_LotEnd(int nPortNo);
	void Set_ContinueLotInfo();
	void Set_TrayLoad(int nPortNo);
	void Set_TrayEnd(int nPortNo);
	void Set_BarcodeUpdate(int nPortNo, int nTrayNo, int nCmNo, CString sBarcode);
	void Set_APDRequest();
	void Set_TestLoad();
	void Set_TimeUpdate();

	BOOL Is_Opened() { return m_bOpened; }

	void Test_Command(int nNo);
};

extern CCapAttachUDP g_objCapAttachUDP;

///////////////////////////////////////////////////////////////////////////////
