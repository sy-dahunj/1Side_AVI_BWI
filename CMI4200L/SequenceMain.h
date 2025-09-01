// SequenceMain.h : 헤더 파일
//
#pragma once

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "LogFile.h"

class CSequenceMain  
{
private:
	static CSequenceMain *m_pInstance;
	
public:
	static CSequenceMain* Get_Instance();
	void Delete_Instance();
	
public:
	CSequenceMain();
	virtual ~CSequenceMain();
	
private:
	CAJinAXL	*m_pAJinAXL;
	AXIS_STATUS *m_pStatus[AXIS_COUNT];
	AXIS_PARAM	*m_pParam[AXIS_COUNT];
	
	DX_DATA_0	*m_pDX0;	// Input (X000 - X031)
	DX_DATA_1	*m_pDX1;	// Input (X100 - X131)
	DX_DATA_2	*m_pDX2;	// Input (X200 - X231)
	DX_DATA_3	*m_pDX3;	// Input (X300 - X331)
	DX_DATA_4	*m_pDX4;	// Input (X400 - X431)
	DX_DATA_5	*m_pDX5;	// Input (X500 - X531)
	DX_DATA_6	*m_pDX6;	// Input (X600 - X631)

	DY_DATA_0	*m_pDY0;	// Output (Y000 - Y031)
	DY_DATA_1	*m_pDY1;	// Output (Y100 - Y131)
	DY_DATA_2	*m_pDY2;	// Output (Y200 - Y231)
	DY_DATA_3	*m_pDY3;	// Output (Y300 - Y331)
	DY_DATA_4	*m_pDY4;	// Output (Y400 - Y431)
	DY_DATA_5	*m_pDY5;	// Output (Y500 - Y531)
	DY_DATA_6	*m_pDY6;	// Output (Y600 - Y631)
	
	CDataManager *m_pDataManager;
	EQUIP_DATA	 *m_pEquipData;
	MODEL_DATA	 *m_pModelData;
	MOVE_DATA	 *m_pMoveData;
	CCommon		 *m_pCommon;

	int		m_nLoad1Case, m_nLoad2Case, m_nUnload1Case, m_nUnload2Case, m_nNGTrayCase, m_nIndexTCase;
	int		m_nLDPickerCase, m_nNGPickerCase, m_nGDPickerCase, m_nULPickerCase, m_nInspectCase, m_nBarcodeCase;

	int		m_nUnloadLotIndex;		// Unload 배출 Lot Index (Continue Lot)
	int		m_nUnloadLotCmCnt;		// Unload 배출 Lot CM Count (Continue Lot)
	CString m_sLog;

	CLogFile *pLogFile;

protected:
	BOOL		m_bThreadMainRun;
	CWinThread	*m_pThreadMainRun;
	static UINT	Thread_MainRun(LPVOID lpVoid);
/*
	BOOL		m_bThreadTilt1Run;
	CWinThread	*m_pThreadTilt1Run;
	static UINT	Thread_Tilt1Run(LPVOID lpVoid);

	BOOL		m_bThreadTilt2Run;
	CWinThread	*m_pThreadTilt2Run;
	static UINT	Thread_Tilt2Run(LPVOID lpVoid);
*/
private:

	BOOL Load1_Run();		// 1.  (Error : 2100)
	BOOL Load2_Run();		// 2.  (Error : 2600)
	BOOL Unload1_Run();		// 3.  (Error : 3100)
	BOOL Unload2_Run();		// 4.  (Error : 3600)
	BOOL Inspect_Run();		// 5.  (Error : 4100)
	BOOL Barcode_Run();		// 5.  (Error : 4300)
	BOOL NGPicker_Run();	// 6.  (Error : 5100)
	BOOL GDPicker_Run();	// 7.  (Error : 6100)
	BOOL LDPicker_Run();	// 8.  (Error : 7100)
	BOOL ULPicker_Run();	// 9.  (Error : 8100)
	BOOL IndexT_Run();		// 10. (Error : 9100)
	BOOL NGTray_Run();		// 11. (Error : 9600)
	BOOL Run_Simulation();				// 99.

public:
	double	m_dNGStageY, m_dLoadTrayX[2], m_dUnloadTrayY[2], m_dVisionPosA, m_dBarcodePosA, m_dVisionPosZ;
	double	m_dNGPickerX, m_dNGPickerZ, m_dGDPickerY, m_dGDPickerZ;

	void Begin_MainRunThread();
	void End_MainRunThread();
	void Run_Replay();
//	void Begin_Tilt1RunThread();
//	void Begin_Tilt2RunThread();
//	void End_Tilt1RunThread();
//	void End_Tilt2RunThread();
	
	BOOL Get_ThreadMainRun() { return m_bThreadMainRun; }
	
	int  Get_RunCase(int nRun);
	void Set_RunCase(int nRun, int nCase);
	void Get_RunCase(int &nCase1, int &nCase2, int &nCase3, int &nCase4, int &nCase5, int &nCase6, int &nCase7, int &nCase8, int &nCase9, int &nCase10, int &nCase11, int &nCase12);
	void Set_RunCase(int nCase1, int nCase2, int nCase3, int nCase4, int nCase5, int nCase6, int nCase7, int nCase8, int nCase9, int nCase10, int nCase11, int nCase12);
	int  Get_IsAutoRun(int nType=0);	//1: APD 확인
	void Set_ClearRunData(int nType);

	BOOL Check_NGPickerAllUp();
	BOOL Check_GdPickerAllUp();
	BOOL Check_NGTrayEmpty(int nNo);
	BOOL Check_NGTrayFull(int nNo);
	BOOL Check_NGTrayMoving();
	BOOL Check_GoodTrayEmpty(int nLine);	//0:all >0:줄
	BOOL Check_LoadTrayCM();
	BOOL Check_InspecEnd(int nPos);
	BOOL Check_InspecDone();
	BOOL Check_IndexEmpty(int nPos);
	BOOL Check_IndexNGJobExist();
	BOOL Check_IndexGoodJobExist();
	BOOL Check_GoodPickJobUp();
	BOOL Check_GoodAllPick();
	BOOL Check_PickerEmpty();
	BOOL Check_LotEnd();
	BOOL Check_LastTray();
	BOOL Check_UnloadTraySort();
	BOOL Check_UnloadTraySortJob();

	void Check_NGPickUpSelect();
	void Check_NGPickDownSelect();
	BOOL Check_NGTray1PickDownSelect();
	BOOL Check_NGTray2PickDownSelect();
	void Check_GoodPickUpSelect();
	void Check_GoodPickDownSelect();
	void Set_LoadTray();
	void Set_IndexEnd();
	void Set_GoodTrayEmpty();
	int	 Get_GoodTrayCmCnt();
	void Set_TackLog(int nNo);

	void Set_UnloadPickerOpen(int nCmd);	//nCmd=0(Close), 1(Open)
	BOOL Check_UnloadPickerOpen(int nCmd);	//nCmd=0(Close), 1(Open)
	BOOL Check_UnloadPickerCM();

	void Job_LotStart();
	void Job_LotEnd();
	void Beep_Post(int nTime);
	int  Select_PikerNo(int nPicker, int nNo);	//nPicker:0(NG Picker), 1(Good Picker)
	int  Count_PikerNotUse(int nPicker);		//nPicker:0(NG Picker), 1(Good Picker)
	int  Get_TrayLineConvert(int nLine);		//Line->Array no로 변한
	BOOL Check_NGTrayJobEnd();
};

///////////////////////////////////////////////////////////////////////////////
