// InterfaceAgent.h : 헤더 파일
//
#pragma once

// CInterfaceAgent

class CInterfaceAgent : public CWnd
{
	DECLARE_DYNAMIC(CInterfaceAgent)

private:
	static CInterfaceAgent *m_pInstance;
	CRect m_ScreenRect;
	
	CRect Get_Position() { return m_ScreenRect; }
	void Set_Position(int left, int top, int right, int bottom) { m_ScreenRect = CRect(left, top, right, bottom); }
	
public:
	static CInterfaceAgent *Get_Instance();
	void Delete_Instance();
	
public:
	CInterfaceAgent();
	virtual ~CInterfaceAgent();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnClientConnect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientClose(WPARAM wParam, LPARAM lParam);

private:
	CClientSocketCS m_Client;

	CString	m_sRecvData;
	CString	m_strSend;

private:
	void Get_ReciveData();
	void Get_ConnectRequest();
	void Get_ConnectMESHost(CString sData);
	void Get_ResultData(CString sData);
	void Get_Error(CString strOp, CString strID, CString strData);

	void Send_Command(CString sSend);

public:
	void Initialize_Client();
	void Terminate_Client();

	void Set_ConnectReply();
	void Set_RequestLot(CString sLotID, int Count);
	void Set_RequestCM(CString sLotID, int Count, CString sCMData);
	void Set_CT();

	void Test_Set();
};

///////////////////////////////////////////////////////////////////////////////
