// Inspector.h : 헤더 파일
//
#pragma once

const int INSPECTOR_VISION	= 1;

// CInspector

class CInspector : public CWnd
{
	DECLARE_DYNAMIC(CInspector)

private:
	static CInspector *m_pInstance;
	CRect m_ScreenRect;
	
	CRect Get_Position() { return m_ScreenRect; }
	void Set_Position(int left, int top, int right, int bottom) { m_ScreenRect = CRect(left, top, right, bottom); }
	
public:
	static CInspector *Get_Instance();
	void Delete_Instance();
	
public:
	CInspector();
	virtual ~CInspector();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUdpReceive(WPARAM pstrIP, LPARAM pstrRecv);

	static UINT Thread_TriggerInspect(LPVOID lpVoid);
	static UINT Thread_TriggerBarcode(LPVOID lpVoid);


private:
	CUdpSocketCS m_UdpVision;

	BOOL	m_bConnectedVision;
	int		m_nStatusRequestLoop;
	int		m_nStatusVision;			// Mold Inspector PC 상태 (0:Not Ready, 1:Ready)
	
	void DoEvents(int nSleep = 0);

	void Get_ConnectRequest(int nInspector);
	void Get_ConnectReply(int nInspector);
	void Get_ConnectEnd(int nInspector);
	void Get_StatusRequest(int nInspector);
	void Get_StatusReply(int nInspector, CString sStatus);
	void Get_StatusUpdate(int nInspector, CString sStatus);
	void Get_ModelReply(int nInspector, CString sFlag);
	void Get_LotReply(int nInspector);
	void Get_LotResult(int nInspector, CString sNG);
	void Get_LoadReply(int nInspector);
	void Get_ScanRequest(int nInspector, CString sDir, CString sSpeed, CString sThickZ, CString sStartX);
	void Get_ScanComplete(int nInspector, CString sLotID, CString sTrayNo, CString sTRNo, CString sGbn);
	void Get_ScanReply(int nInspector);
	
	void Get_InspectResult(int nInspector, CString sResultFile);
	void Get_PositionRequest(int nInspector, CString sGbn);
	void Get_AMoveRequest(int nInspector, CString sX, CString sY, CString sZ, CString sGbn);
	void Get_RMoveRequest(int nInspector, CString sX, CString sY, CString sZ, CString sGbn);
	void Get_ZMoveRequest(int nInspector, CString sZ);
	void Get_TriggerRequest(int nInspector, CString sL1, CString sL2, CString sL3, CString sL4, CString sL5, CString sL6, CString sL7, CString sL8, CString sType);
	void Get_MoveReply(int nInspector);
	void Get_ErrorOccur(int nInspector, CString sType);
	void Get_ErrorPost(int nInspector, CString sAlmNo, CString sMsg);
	void Get_RecipeChanged(int nInspector, CString sRecipe);
	void Get_PmsUpload(int nInspector, CString sBarcode, CString sOrign);
	void Get_PmsResult(int nInspector, CString sBarcode, CString sMap);
	void Get_StripReply(int nInspector);
	void Get_AdrDataCopy(int nInspector);
	void Get_CalRequest(int nInspector, CString sDir, CString sSpeed, CString sStartX);
	void Get_CalReply(int nInspector);
	void Get_ElectReply(int nInspector);
	void Get_WarpReply(int nInspector);
	void Get_MThickComplete(int nInspector, CString sLotId, CString sStripId, CString sValue[]);
	void Get_CorrectComplete(int nInspector, CString sX, CString sY, CString sZ);
	void Get_TimeReply(int nInspector);
	void Get_NGBarcodeReply(int nInspector);

	void Get_AlarmRequest(int nInspector, CString sGbn, CString sLotId, CString sErrNo, CString sInfo1, CString sInfo2, CString sInfo3="");
	void Get_FOBUpdate(int nInspector, CString sStatus);
	void Get_FOBReply(int nInspector, CString sStatus);
	void Get_APDReply(int nInspector, CString strRecv);

	void Send_Command(int nInspector, CString strSend);
	
protected:
	static UINT Thread_AdrDataCopy(LPVOID lpVoid);

public:
	void Initialize_Inspector();
	void Terminate_Inspector();
	
	void Set_ConnectRequest(int nInspector);
	void Set_ConnectReply(int nInspector);
	void Set_ConnectEnd(int nInspector);
	void Set_StatusRequest(int nInspector);
	void Set_StatusReply(int nInspector, int nStatus);
	void Set_StatusUpdate(int nInspector, int nStatus);
	void Set_ModelUpdate(int nInspector, CString sModel, double dSizeX, double dSizeY, double dThick, int nBlockCnt, int nPkgXCnt, int nPkgYCnt, double dBallSize);
	void Set_LotStart(int nInspector);
	void Set_LotCount(int nInspector);
	void Set_LotComplete(int nInspector);
	void Set_LoadComplete(int nInspector, int nTrayNo, int nTRNo);
	void Set_ScanReply(int nInspector, int nNG);
	void Set_ScanComplete(int nInspector);
	void Set_InspectReply(int nInspector, int nErr);
	void Set_ReviewReply(int nInspector);
	void Set_PositionReply(int nInspector, double dX, double dY, double dZ, CString sGbn);
	void Set_AMoveReply(int nInspector, int nCanMove, CString sGbn);
	void Set_RMoveReply(int nInspector, int nCanMove, CString sGbn);
	void Set_TriggerReply(int nInspector, int nCanMove);
	void Set_MoveComplete(int nInspector, CString sGbn);
	void Set_ErrorReply(int nInspector);
	void Set_RecipeReply(int nInspector);
	void Set_PmsDownload(int nInspector, CString sBarcode, CString sMap);
	void Set_StripComplete(int nInspector, int nInspectId, CString sModel, CString sLotId, CString sPartNo, int nStripId, CString sStatus);
	void Set_AdrDataReply(int nInspector);
	void Set_CalReply(int nInspector);
	void Set_CalComplete(int nInspector);
	void Set_LaserReply(int nInspector, int nNG);
	void Set_LaserComplete(int nInspector);
	void Set_ElectComplete(int nInspector, CString sLotId, CString sStripId, double dValue, int nInOut);
	void Set_WarpComplete(int nInspector, CString sLotId, CString sStripId, double dValue);
	void Set_MThickReply(int nInspector);
	void Set_TimeUpdate(int nInspector);
	void Set_NGBarcode(int nInspector, CString sLodID, CString sBarcodeData, int TrayNo ,int nBarcodeX, int nBarcodeY);

	void Set_FOBRequest(int nInspector);
	void Set_APDRequest(int nInspector);


	// Inspector Connected
	BOOL Is_ConnectedVision() { return m_bConnectedVision; }

	// Inspector Status
	int	Read_StatusVision() { return m_nStatusVision; }
		
	// Barcode MES Check
	void Get_InspectComplete(int nInspector, CString sStripId);
//	BOOL Check_HostResult(CString sBarcode);
//	BOOL Check_CMExist(CString sBarcode);

	void Test_Command();
};

///////////////////////////////////////////////////////////////////////////////
