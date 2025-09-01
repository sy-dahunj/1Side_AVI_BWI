// SequenceInit.h : 헤더 파일
//
#pragma once

#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

class CSequenceInit  
{
private:
	static CSequenceInit *m_pInstance;

public:
	static CSequenceInit* Get_Instance();
	void Delete_Instance();

public:
	CSequenceInit();
	virtual ~CSequenceInit();
	
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
	EQUIP_DATA *m_pEquipData;
	MODEL_DATA *m_pModelData;
	MOVE_DATA *m_pMoveData;
	
	CCommon *m_pCommon;

	// Initial Sequence
	int		m_nInitMainCase;
	int		m_nInitLoad1Case, m_nInitLoad2Case, m_nInitUnload1Case, m_nInitUnload2Case, m_nInitNGTrayCase, m_nInitIndexTCase;
	int		m_nInitLDPickerCase, m_nInitNGPickerCase, m_nInitGDPickerCase, m_nInitULPickerCase, m_nInitInspectCase, m_nInitTestCase;

	BOOL	m_bInitComplete;
	
protected:
	BOOL		m_bThreadInitial;
	CWinThread	*m_pThreadInitial;
	static UINT	Thread_Initial(LPVOID lpVoid);

private:
	BOOL Initial_MainRun();			// 0.  (Error : 1100)
	BOOL Initial_Load1Run();		// 1.  (Error : 1210)
	BOOL Initial_Load2Run();		// 2.  (Error : 1260)
	BOOL Initial_Unload1Run();		// 3.  (Error : 1310)
	BOOL Initial_Unload2Run();		// 4.  (Error : 1360)
	BOOL Initial_InspectRun();		// 5.  (Error : 1410)
	BOOL Initial_NGPickerRun();		// 6.  (Error : 1510)
	BOOL Initial_GDPickerRun();		// 7.  (Error : 1610)
	BOOL Initial_LDPickerRun();		// 8.  (Error : 1710)
	BOOL Initial_ULPickerRun();		// 9.  (Error : 1810)
	BOOL Initial_IndexTRun();		// 10. (Error : 1910)
	BOOL Initial_NGTrayRun();		// 11. (Error : 1960)
	BOOL Initial_TestRun();			// 13. (Error : 1930)
	BOOL Initial_Simulation();		// 99. (Simulation)
	BOOL Get_NGPickerTest();

public:
	BOOL Get_ThreadInitial() { return m_bThreadInitial; }
	BOOL Get_InitComplete() { return m_bInitComplete; }
	void Set_InitComplete(BOOL bInitComp) { m_bInitComplete = bInitComp; }	
	
	void Get_InitCase(int &nMain, int &nCase1, int &nCase2, int &nCase3, int &nCase4, int &nCase5, int &nCase6, int &nCase7, int &nCase8, int &nCase9, int &nCase10, int &nCase11);

	void Begin_InitialThread();
	void End_InitialThread();
	void Reset_InitialCase();
};

///////////////////////////////////////////////////////////////////////////////
