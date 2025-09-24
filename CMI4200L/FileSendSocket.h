// FileSendSocket.h  (VS2010¿ë)
#pragma once
#include "stdafx.h"
#include <afxsock.h>
#include <afx.h>
#include <string>
#include "NetEndian.h"
#include <math.h>
#include <stdint.h>

class CFileSendSocket : public CAsyncSocket {
public:
	enum SEND_STATE { SEND_IDLE, SEND_HEADER, SEND_NAME, SEND_DATA, SEND_DONE, SEND_ERR };

	CFileSendSocket();
	virtual ~CFileSendSocket();

	BOOL BeginSend(const CString& path, const CString& sendName = _T(""));
	BOOL ConnectToServer(LPCTSTR ip, UINT port);  
    BOOL SendFile(const CString& path);         
	void Disconnect();    
protected:
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
private:
	SEND_STATE m_state;
	BOOL m_bConnected;
    CString m_lastFilePath; 

	CFile    m_in;
	uint64_t m_fileSize;

	struct HEADER {
		uint64_t fileSizeN;
		uint32_t nameLenN;
	} m_hdr;
	size_t m_hdrSent;

	std::string m_name;
	size_t      m_nameSent;

	uint64_t m_dataSent;

	int SafeSend(const void* buf, int len);
};