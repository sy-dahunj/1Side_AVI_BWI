#pragma once

// CDataSocket 명령 대상입니다.
class CData;

class CDataSocket : public CSocket
{
public:
	CDataSocket();
	virtual ~CDataSocket();

public:
	void Init(CWnd *pWnd, UINT nMSG = WM_USER + 2);
	void Send(CData *pData);
	void Receive(CData *pData);
	void operator << (CData &data);
	void operator >> (CData &data);
	void Flush();

	void Reset();

	CArchive	*m_pArchiveIn;
	CArchive	*m_pArchiveOut;

	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);


protected:
	CWnd		*m_pWndParent;
	CSocketFile *m_pFile;
	UINT		m_nMSG;

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

public:
	BOOL SetTimeOut(int nTimeOut);
	BOOL KillTimeOut();
protected:
	virtual BOOL OnMessagePending();
private:
	int		m_nTimerID;
	DWORD	m_dwStart;
	DWORD	m_dwTimeOut;
	BOOL	m_bCheck;
	
};


