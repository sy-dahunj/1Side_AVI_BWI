#pragma once


#include "SerialInterface.h"
//#include "IExtBarcode.h"

// CExtBarcode_Honeywell

class CExtBarcode_Honeywell : public CWnd
{
	DECLARE_DYNAMIC(CExtBarcode_Honeywell)

private:
	static CExtBarcode_Honeywell *m_pInstance;

public:
	static CExtBarcode_Honeywell* Get_Instance();
	void Delete_Instance();

public:
	CExtBarcode_Honeywell();
	virtual ~CExtBarcode_Honeywell();

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual int Initialize();
	virtual int UnInitialize();
	virtual int Save();
	virtual int Load();

	virtual int Connect();
	virtual int Connect(LPCTSTR lpFileName, DWORD dwBaudRate, BYTE ByteSize, BYTE byParity, BYTE byStopBits, DWORD dwXonoff);
	virtual int Disconnect();
	virtual BOOL IsConnected() const;
	
	virtual int GetBarcode(CString& strBarcode);
	virtual BOOL IsChanged() const;
	virtual int ResetChanged();

	virtual int SetMessage(HWND hWnd, UINT Msg);

protected:
	BOOL	m_bConnected;
	BOOL	m_bChanged;

	HWND	m_hWndParent;
	UINT	m_nMSG;


protected:
	CString				m_strRead;
	CString				m_strBarcode;
	CSerialInterface	m_Rs232c;
	CWinThread*			m_pThread;

	static UINT	ThreadFunc(LPVOID opThreadParam);

	int ReadProcess();
	int AddChar(char ch);
};


