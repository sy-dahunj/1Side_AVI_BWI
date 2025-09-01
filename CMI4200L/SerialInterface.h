#pragma once


#define	MAX_COM_BUFFER	8192

#define ASCII_XON		0x11
#define ASCII_XOFF		0x13

#define ASCII_STX		0x02
#define ASCII_ETX		0x03
#define ASCII_ACK		0x06
#define ASCII_BEL		0x07
#define	ASCII_LF		0x0A
#define	ASCII_VT		0x0B
#define	ASCII_CR		0x0D
#define ASCII_NAK		0x15
#define ASCII_ETB		0x17
#define ASCII_RS		0x1E
#define ASCII_US		0x1F
#define ASCII_SHARP		0x23
#define ASCII_DOLLAR	0x24
#define ASCII_AND		0x26

// Queue 클래스 정의 //
class CQueue
{
public:
	CQueue();

	BYTE	buff[MAX_COM_BUFFER];
	int		m_iHead; 
	int		m_iTail;

	void	Clear();
	int		GetSize();
	bool	PutByte(BYTE b);		// 1 byte 넣기
	bool	GetByte(BYTE *pb);		// 1 byte 꺼내기
};

// CSerialInterface

class CSerialInterface : public CWnd
{
	DECLARE_DYNAMIC(CSerialInterface)

public:
	BOOL WaitCOMEvent(LPDWORD lpEvtMask, LPOVERLAPPED lpOverlapped=NULL);
	void CloseOS();
	bool SetEventDefault();
	// Variable ----------------------------------------------------------------------------------
	bool		m_bConnected;
	HANDLE		m_hComm;

	// Function ----------------------------------------------------------------------------------
	bool		bDisConnect();
	bool		bConnect(LPCTSTR lpFileName, DWORD dwBaudRate, BYTE ByteSize, BYTE byParity, BYTE byStopBits, DWORD dwXonoff);
	DWORD		ReadComm(BYTE *pBuff, DWORD nToRead);
	DWORD		WriteComm(BYTE *pBuff, DWORD nToWrite);

	//--------- 통신 버퍼 ------------------------------------------------------------------------
	CQueue		m_QueueRead;

	CSerialInterface();
	virtual ~CSerialInterface();

protected:
	DECLARE_MESSAGE_MAP()

	// Variable ----------------------------------------------------------------------------------
	DWORD		m_dwMaxBuffer;
	OVERLAPPED	m_osRead;
	OVERLAPPED	m_osWrite;
	OVERLAPPED  m_Os;

	// Function ----------------------------------------------------------------------------------
	bool		bCheckCOM(HANDLE hComm);

private:
	static CString m_sStrConvError;
};


