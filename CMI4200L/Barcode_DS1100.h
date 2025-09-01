#pragma once

#include "SerialInterface.h"
// CBarcode_DS1100

class CBarcode_DS1100 : public CWnd
{
	DECLARE_DYNAMIC(CBarcode_DS1100)

private:
	static CBarcode_DS1100 *m_pInstance;

public:
	static CBarcode_DS1100* Get_Instance();
	void Delete_Instance();

public:
	CBarcode_DS1100();
	virtual ~CBarcode_DS1100();

protected:
	DECLARE_MESSAGE_MAP()

public:
	int Initialize();
	int UnInitialize();
	int Save();
	int Load();
	
	int Connect();
	int Connect(LPCTSTR lpFileName, DWORD dwBaudRate, BYTE ByteSize, BYTE byParity, BYTE byStopBits, DWORD dwXonoff);
	int Disconnect();
	BOOL IsConnected() const;
	
	int GetBarcode(CString& strBarcode);
	BOOL IsChanged() const;
	int ResetChanged();
	
	int SetMessage(HWND hWnd, UINT Msg);

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


