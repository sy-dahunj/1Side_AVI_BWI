#pragma once

#include "DataSocket.h"

class CSocketTCP : public CWnd
{
	DECLARE_DYNAMIC(CSocketTCP)

private:
	static CSocketTCP *m_pInstance;

public:
	static CSocketTCP* Get_Instance();
	void Delete_Instance();

public:
	CSocketTCP();
	virtual ~CSocketTCP();

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual int SetParams_MSG( CWnd* pWnd, const UINT& nMsgAccept, const UINT& nMsgReceive, const UINT& nMsgClient );
	virtual int SetParams_Client( const CString& strIP, const UINT& nPort, const int& nTimeOut );

	virtual int Connect();
	virtual int Reconnect();
	virtual int Disconnect();

	virtual int GetReceive( CString& strReceive );
	virtual int GetReceive_Client( CString& strReceive );

	virtual int SendData( const CString& strData );
	virtual int SendByte( BYTE data[], int nLength );

	virtual int GetSocketName_Client( CString& strIPAddress, UINT& nPort );

	virtual BOOL IsConnected_Client();

protected:
	CDataSocket m_DataSocket;
	CDataSocket m_DataSocket_Client;

	CWnd*	m_pWndParent;
	
	UINT	m_nMsgAccept;
	UINT	m_nMsgReceive_Client;
	BOOL	m_bConnected_Client;

	UINT	m_nPort_Client;
	UINT	m_nTimeOut;

	CString m_strIPAddress;

};


