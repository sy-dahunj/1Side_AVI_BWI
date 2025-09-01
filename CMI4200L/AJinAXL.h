// AJinAXL.h : 헤더 파일
//
#pragma once

// *** AJin Test Configuration ****************************
// Motion Board    : PCI-N804 (3EA), PC-N404 (1EA)
// D-In Board      : PCI-DI64R (2EA)
// D-Out Board     : PCI-DO64R (2EA)
// Library Version : EzSoftwareRM_V1.3.5.2113
// ********************************************************

#include "AJinDefine.h"

class CAJinAXL
{
private:
	static CAJinAXL *m_pInstance;

public:
	static CAJinAXL* Get_Instance();
	void Delete_Instance();

public:
	CAJinAXL();
	virtual ~CAJinAXL();

private:
	DX_DATA_0	m_DX0;					// Input (X000 - X031)
	DX_DATA_1	m_DX1;					// Input (X100 - X131)
	DX_DATA_2	m_DX2;					// Input (X200 - X231)
	DX_DATA_3	m_DX3;					// Input (X300 - X331)
	DX_DATA_4	m_DX4;					// Input (X400 - X431)
	DX_DATA_5	m_DX5;					// Input (X500 - X531)
	DX_DATA_6	m_DX6;					// Input (X600 - X631)

	DY_DATA_0	m_DY0;					// Output (Y000 - Y031)
	DY_DATA_1	m_DY1;					// Output (Y100 - Y131)
	DY_DATA_2	m_DY2;					// Output (Y200 - Y231)
	DY_DATA_3	m_DY3;					// Output (Y300 - Y331)
	DY_DATA_4	m_DY4;					// Output (Y400 - Y431)
	DY_DATA_5	m_DY5;					// Output (Y500 - Y531)
	DY_DATA_6	m_DY6;					// Output (Y600 - Y631)

	AXIS_STATUS	m_Status[AXIS_COUNT];	// Axis Status Data
	AXIS_PARAM	m_Param[AXIS_COUNT];	// Axis Parameter Data

protected:
	BOOL		m_bThreadAJin;
	CWinThread *m_pThreadAJin;
	static UINT	Thread_AJinRun(LPVOID lpVoid);

	void Sim_SetMotion(int nNo, int nAxis, double dPos);
	void Sim_SetOutToIn(int nNo);

public:
	int	m_nGoodCnt, m_nEmptyCnt;

	BOOL Initialize_AJin();
	void Terminate_AJin();

	void Read_Input();					// DI Read
	void Read_Output();					// DO Read
	void Write_Output(int nModule);		// DO Write

	void Read_MotionStatus();			// Motion Status
	void Status_Monitoring();

	void Set_ServoOn(int nAxis, BOOL bOnOff);
	void Home_Search(int nAxis);
	void Set_Home(int nAxis);
	void Move_Absolute(int nAxis, double dPos);
	void Move_Relative(int nAxis, double dPos);
	void Jog_Positive(int nAxis);
	void Jog_Negative(int nAxis);
	void Stop_Motion(int nAxis);
	void EStop_Motion(int nAxis);
	void Alarm_Reset(int nAxis);

	void Move_Abs_Accel(int nAxis, double dPos, double dAcc);

	BOOL Is_Done(int nAxis);
	BOOL Is_Home(int nAxis);
	BOOL Is_MoveDone(int nAxis, double dPos);

	void Set_CVActPos(int nAxis); 

	void Read_MotionParam(int nAxis);
	void Save_MotionParam(int nAxis, double dMovSp, double dJogSp);
	void Save_RmsMotionSpeed(int nAxis, double dSpeedM);

	BOOL Is_ServoAxis(int nAxis);
	BOOL Use_OrgAxis(int nAxis);
	BOOL Use_ElpAxis(int nAxis);
	BOOL Use_ElnAxis(int nAxis);

	DX_DATA_0 *Get_pDX0() { return &m_DX0; }
	DX_DATA_1 *Get_pDX1() { return &m_DX1; }
	DX_DATA_2 *Get_pDX2() { return &m_DX2; }
	DX_DATA_3 *Get_pDX3() { return &m_DX3; }
	DX_DATA_4 *Get_pDX4() { return &m_DX4; }
	DX_DATA_5 *Get_pDX5() { return &m_DX5; }
	DX_DATA_6 *Get_pDX6() { return &m_DX6; }

	DY_DATA_0 *Get_pDY0() { return &m_DY0; }
	DY_DATA_1 *Get_pDY1() { return &m_DY1; }
	DY_DATA_2 *Get_pDY2() { return &m_DY2; }
	DY_DATA_3 *Get_pDY3() { return &m_DY3; }
	DY_DATA_4 *Get_pDY4() { return &m_DY4; }
	DY_DATA_5 *Get_pDY5() { return &m_DY5; }
	DY_DATA_6 *Get_pDY6() { return &m_DY6; }

	AXIS_STATUS *Get_pStatus(int nAxis) { return &m_Status[nAxis]; }
	AXIS_PARAM *Get_pParam(int nAxis) { return &m_Param[nAxis]; }
};

///////////////////////////////////////////////////////////////////////////////
