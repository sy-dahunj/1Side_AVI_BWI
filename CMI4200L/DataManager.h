// DataManager.h : 헤더 파일
//
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Equip Data
typedef struct tag_EQUIP_DATA {
	CString sCurrModel;
	CString sEquipName;

	BOOL	bUseVisionInspect;
	BOOL	bUseBar2Alarm;
	BOOL	bUseBar2NG;
	BOOL	bUseMES;
	BOOL	bUseContinueLot;
	BOOL	bUseDoorLock;
	BOOL	bUseInlineMode;
	BOOL	bUseMesApd;			// AVI APD 파일을 남길껀지 아닌지. Lot End와 관련있어 옵션화.
	CString sLotBarcodePort;     //kty
	CString sNGBarcodePort;		 //kty
	CString sCapAttachIp;

	double	dMoldTrigPeriod;
	double	dMoldTrigWidth;
	double	dMoldScanOffset;

	BOOL	bUseManagerMode;
	BOOL	bUseVacuumCheck;
	BOOL	bUseCMCheck;
	BOOL	bUseTackLog;
	BOOL	bUseAllPick;
	BOOL	bTower[6][7];	// [0:None,1:Init,2:Ready,3:Run,4:Alarm,5:Emer][0:Green,1:Yellow,2:Red,3:Flicker,4:Buzz1,5:Buzz2,6:Flicker]
} EQUIP_DATA;

///////////////////////////////////////////////////////////////////////////////
// Model Data
typedef struct tag_MODEL_DATA {
	CString sModelName;
	int		nArrayL;		// 5~6
	int		nArrayW;		// 5~10
	double	dPitchL;
	double	dPitchW;
	double	dTrayFirstL;
	double	dTrayFirstW;
	double	dCMWSize;
	int		nCMCount;
	double	dUnPitchL;
	double	dUnPitchW;
	int		nStripSize;		// 1->77.5 X 240.0, 2->62.0 X 220.0
} MODEL_DATA;

///////////////////////////////////////////////////////////////////////////////
// Move Data
typedef struct tag_MOVE_DATA {
	double  dLoadTrayX1[5];
	double  dLoadTrayX2[5]; 
	double  dLoadTrayZ1[4]; 
	double  dLoadTrayZ2[4]; 
	double  dLoadPickerY1[3];   
	double  dLoadPickerZ[4];    
	double  dLoadPickerY2[5];   
	double  dIndexR[8];
	double  dBarCodeA[1];
	double  dInspectionA[1];    
	double  dInspectionZ[2];    
	double  dNGPickerX[8];      
	double  dNGPickerZ[7];      
	double  dNGStageY[4];
	double  dGdPickerY[7];      
	double  dGdPickerZ[13];      
	double  dUnloadPickerX1[3]; 
	double  dUnloadPickerZ[4];  
	double  dUnloadPickerX2[5]; 
	double  dUnloadTrayY1[5];   
	double  dUnloadTrayY2[5];   
	double  dUnloadTrayZ1[4];   
	double  dUnloadTrayZ2[4];   

	//Acc
	double  dDLoadTrayX1[5];
	double  dDLoadTrayX2[5]; 
	double  dDLoadTrayZ1[4]; 
	double  dDLoadTrayZ2[4]; 
	double  dDLoadPickerY1[3];   
	double  dDLoadPickerZ[4];    
	double  dDLoadPickerY2[5];   
	double  dDIndexR[8];
	double  dDBarCodeA[1];
	double  dDInspectionA[1];    
	double  dDInspectionZ[2];
	double  dDNGPickerX[8];      
	double  dDNGPickerZ[7];      
	double  dDNGStageY[4];
	double  dDGdPickerY[7];      
	double  dDGdPickerZ[13];      
	double  dDUnloadPickerX1[3]; 
	double  dDUnloadPickerZ[4];  
	double  dDUnloadPickerX2[5]; 
	double  dDUnloadTrayY1[5];   
	double  dDUnloadTrayY2[5];   
	double  dDUnloadTrayZ1[4];   
	double  dDUnloadTrayZ2[4];   
} MOVE_DATA;

////////////////////////////////ㅐ///////////////////////////////////////////////

class CDataManager
{
private:
	static CDataManager *m_pInstance;

public:
	static CDataManager* Get_Instance();
	void Delete_Instance();

public:
	CDataManager();
	virtual ~CDataManager();

private:
	EQUIP_DATA	m_EquipData;
	MODEL_DATA	m_ModelData;
	MOVE_DATA	m_MoveData;
	
public:	
	void Reset_EquipData();
	void Reset_ModelData();
	void Reset_MoveData();

	BOOL Read_EquipData();
	BOOL Read_ModelData();
	BOOL Read_MoveData();

	EQUIP_DATA *Get_pEquipData() { return &m_EquipData; }
	MODEL_DATA *Get_pModelData() { return &m_ModelData; }
	MOVE_DATA *Get_pMoveData() { return &m_MoveData; }

	BOOL Exist_PkgCode(CString sName);
	BOOL Exist_Model(CString sName);
	BOOL Change_Model(CString sName);

	BOOL Default_MoveData();
};

///////////////////////////////////////////////////////////////////////////////
