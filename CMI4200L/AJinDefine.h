///////////////////////////////////////////////////////////////////////////////
// AJinDefine.h : AJin Structure
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Motion Axis
const int AXIS_COUNT = 23;		// Motion Module (PCI-N804 4EA, PCI-N404 1EA)

const int AX_LOAD_TRAY_X1			= 0;
const int AX_LOAD_TRAY_X2			= 1;
const int AX_LOAD_TRAY_Z1			= 2;
const int AX_LOAD_TRAY_Z2			= 3;
const int AX_LOAD_PICKER_Y1			= 4;
const int AX_LOAD_PICKER_Z			= 5;
const int AX_LOAD_PICKER_Y2			= 6;
const int AX_INDEX_R				= 7;
const int AX_BARCODE_A				= 8;
const int AX_INSPECTION_A			= 9;
const int AX_INSPECTION_Z			= 10;
const int AX_NG_PICKER_X			= 11;
const int AX_NG_PICKER_Z			= 12;
const int AX_NG_STAGE_Y				= 13;
const int AX_GOOD_PICKER_Y			= 14;
const int AX_GOOD_PICKER_Z			= 15;
const int AX_UNLOAD_PICKER_X1		= 16;
const int AX_UNLOAD_PICKER_Z		= 17;
const int AX_UNLOAD_PICKER_X2		= 18;
const int AX_UNLOAD_TRAY_Y1			= 19;
const int AX_UNLOAD_TRAY_Y2			= 20;
const int AX_UNLOAD_TRAY_Z1			= 21;
const int AX_UNLOAD_TRAY_Z2			= 22;

///////////////////////////////////////////////////////////////////////////////
// Motion Status

typedef struct tag_AXIS_STATUS {
	double dPos;		// Motor Current Position
	double dVel;		// Motor Current Velocity
	BOOL bSOn;			// Servo On Status
	BOOL bELP;			// End Limit Positive
	BOOL bELN;			// End Limit Negative
	BOOL bALM;			// Driver Alarm
	BOOL bInP;			// In Position
	BOOL bRun;			// Running
	BOOL bHom;			// Home Complete
} AXIS_STATUS;

///////////////////////////////////////////////////////////////////////////////
// Motion Parameter

typedef struct tag_AXIS_PARAM {
	double dMovSpeed;	// Move Speed
	double dJogSpeed;	// Jog Speed
} AXIS_PARAM;

///////////////////////////////////////////////////////////////////////////////
// DIO Count

const long DIO_MODULE_COUNT = 14;		// IO Module (PCI-DI64R 2EA, PCI-DO64R 2EA)
const int DI_COUNT = 224;				// Input Count
const int DO_COUNT = 224;				// Output Count

///////////////////////////////////////////////////////////////////////////////
// Input (X000 - X331)

typedef union tag_DX_DATA_0 {
	DWORD nValue;
	struct {
		DWORD iStartSw: 1;					// X000
		DWORD iStopSw: 1;					// X001
		DWORD iResetSw: 1;					// X002
		DWORD i003: 1;						// X003
		DWORD iMainAir1: 1;					// X004
		DWORD iMainAir2: 1;					// X005
		DWORD i006: 1;						// X006
		DWORD i007: 1;						// X007

		DWORD iMainDoor1Close: 1;			// X008
		DWORD iMainDoor2Close: 1;			// X009
		DWORD iMainDoor3Close: 1;			// X010
		DWORD iMainDoor4Close: 1;			// X011
		DWORD iMainDoor5Close: 1;			// X012
		DWORD iMainDoor6Close: 1;			// X013
		DWORD iMainDoor7Close: 1;			// X014
		DWORD iMainDoor8Close: 1;			// X015

		DWORD iEMS1: 1;						// X016
		DWORD iEMS2: 1;						// X017
		DWORD iEMS3: 1;						// X018
		DWORD iEMS4: 1;						// X019
		DWORD iEMS5: 1;						// X020
		DWORD iEMS6: 1;						// X021
		DWORD i022: 1;						// X022
		DWORD i023: 1;						// X023
			
		DWORD i024: 1;						// X024
		DWORD i025: 1;						// X025
		DWORD i026: 1;						// X026
		DWORD i027: 1;						// X027
		DWORD i028: 1;						// X028
		DWORD i029: 1;						// X029
		DWORD i030: 1;						// X030
		DWORD i031: 1;						// X031

	};
} DX_DATA_0;	// Digital Input 0

typedef union tag_DX_DATA_1 {
	DWORD nValue;
	struct {
		DWORD iLS_LoadSupport1In: 1;		// X100
		DWORD iLS_LoadSupport1Out: 1;		// X101
		DWORD iLS_Load1FEmitter: 1;			// X102
		DWORD iLS_LoadSupport2In: 1;		// X103
		DWORD iLS_LoadSupport2Out: 1;		// X104
		DWORD iLS_Load1FCheck: 1;			// X105
		DWORD iLS_LoadFullCheck: 1;			// X106
		DWORD i107: 1;						// X107
				
		DWORD iLS_UnloadSupport1In: 1;		// X108
		DWORD iLS_UnloadSupport1Out: 1;		// X109
		DWORD iLS_Unload1FEmitter: 1;		// X110
		DWORD iLS_UnloadSupport2In: 1;		// X111
		DWORD iLS_UnloadSupport2Out: 1;		// X112
		DWORD iLS_Unload1FCheck: 1;			// X113
		DWORD iLS_UnloadFullCheck: 1;		// X114
		DWORD i115: 1;						// X115
               
		DWORD iLS_Z1Check1: 1;				// X116
		DWORD iLS_Z1CheckEmitter1: 1;		// X117
#ifdef ALIGN_NEW
		DWORD iLS_Z1AlignM34In: 1;			// X118
		DWORD iLS_Z1AlignM34Out: 1;			// X119
		DWORD iLS_Z1AlignS12In: 1;			// X120
		DWORD iLS_Z1AlignS12Out: 1;			// X121
#else
		DWORD iLS_Z1AlignS12In: 1;			// X118
		DWORD iLS_Z1AlignS12Out: 1;			// X119
		DWORD iLS_Z1AlignM34In: 1;			// X120
		DWORD iLS_Z1AlignM34Out: 1;			// X121
#endif
		DWORD iLS_Z1Check2: 1;				// X122
		DWORD iLS_Z1CheckEmitter2: 1;		// X123
				
		DWORD iLS_Z2Check1: 1;				// X124
		DWORD iLS_Z2CheckEmitter1: 1;		// X125
#ifdef ALIGN_NEW
		DWORD iLS_Z2AlignM34In: 1;			// X126
		DWORD iLS_Z2AlignM34Out: 1;			// X127
		DWORD iLS_Z2AlignS12In: 1;			// X128
		DWORD iLS_Z2AlignS12Out: 1;			// X129
#else
		DWORD iLS_Z2AlignS12In: 1;			// X126
		DWORD iLS_Z2AlignS12Out: 1;			// X127
		DWORD iLS_Z2AlignM34In: 1;			// X128
		DWORD iLS_Z2AlignM34Out: 1;			// X129
#endif
		DWORD iLS_Z2Check2: 1;				// X130
		DWORD iLS_Z2CheckEmitter2: 1;		// X131

	};
} DX_DATA_1;	// Digital Input 1

typedef union tag_DX_DATA_2 {
	DWORD nValue;
	struct {
		DWORD iMLPicker1Open: 1;			// X200
		DWORD iMLPicker2Open: 1;			// X201
		DWORD iMLPicker3Open: 1;			// X202
		DWORD iMLPicker4Open: 1;			// X203
		DWORD iMLPicker5Open: 1;			// X204
		DWORD iMLPicker6Open: 1;			// X205
		DWORD iMLPicker1CMCheck: 1;			// X206
		DWORD iMLPicker2CMCheck: 1;			// X207
               
		DWORD iMLPicker3CMCheck: 1;			// X208
		DWORD iMLPicker4CMCheck: 1;			// X209
		DWORD iMLPicker5CMCheck: 1;			// X210
		DWORD iMLPicker6CMCheck: 1;			// X211
		DWORD i212: 1;						// X212
		DWORD i213: 1;						// X213
		DWORD i214: 1;						// X214
		DWORD i215: 1;						// X215
               
		DWORD iCMPressUp: 1;				// X216
		DWORD iCMPressDn: 1;				// X217
		DWORD i218: 1;						// X218
		DWORD iInspCMAlign1In: 1;			// X219
		DWORD iInspCMAlign1Out: 1;			// X220
		DWORD iInspCMAlign2In: 1;			// X221
		DWORD iInspCMAlign2Out: 1;			// X222
		DWORD iInspCMAlign3In: 1;			// X223
		       
		DWORD iInspCMAlign3Out: 1;			// X224
		DWORD iInspCMAlign4In: 1;			// X225
		DWORD iInspCMAlign4Out: 1;			// X226
		DWORD iInspVacuumUp: 1;				// X227
		DWORD iInspVacuumDown: 1;			// X228
		DWORD iInspCMAlignCheck1: 1;		// X229
		DWORD iInspCMAlignCheck2: 1;		// X230
		DWORD iInspCMAlignCheck3: 1;		// X231

	};
} DX_DATA_2;	// Digital Input 2

typedef union tag_DX_DATA_3 {
	DWORD nValue;
	struct {
		DWORD iInspVacuumPad1Check: 1;		// X300
		DWORD iInspVacuumPad2Check: 1;		// X301
		DWORD iInspVacuumPad3Check: 1;		// X302
		DWORD iInspVacuumPad4Check: 1;		// X303
		DWORD iInspVacuumPad5Check: 1;		// X304
		DWORD iInspVacuumPad6Check: 1;		// X305
		DWORD i306: 1;						// X306
		DWORD i307: 1;						// X307
							
		DWORD iNGPicker1Open: 1;			// X308
		DWORD iNGPicker2Open: 1;			// X309
		DWORD iNGPicker3Open: 1;			// X310
		DWORD iNGPicker4Open: 1;			// X311
		DWORD iNGPicker5Open: 1;			// X312
		DWORD iNGPicker1Up: 1;				// X313
		DWORD iNGPicker1Down: 1;			// X314
		DWORD iNGPicker2Up: 1;				// X315
               
		DWORD iNGPicker2Down: 1;			// X316
		DWORD iNGPicker3Up: 1;				// X317
		DWORD iNGPicker3Down: 1;			// X318
		DWORD iNGPicker4Up: 1;				// X319
		DWORD iNGPicker4Down: 1;			// X320
		DWORD iNGPicker5Up: 1;				// X321
		DWORD iNGPicker5Down: 1;			// X322
		DWORD iNGPicker1CMCheck: 1;			// X323
		       
		DWORD iNGPicker2CMCheck: 1;			// X324
		DWORD iNGPicker3CMCheck: 1;			// X325
		DWORD iNGPicker4CMCheck: 1;			// X326
		DWORD iNGPicker5CMCheck: 1;			// X327
		DWORD iNGTray1Check: 1;				// X328
		DWORD iNGTray2Check: 1;				// X329
		DWORD iNGTray1CheckEmitter: 1;		// X330
		DWORD iNGTray2CheckEmitter: 1;		// X331

	};
} DX_DATA_3;	// Digital Input 3

typedef union tag_DX_DATA_4 {
	DWORD nValue;
	struct {
		DWORD iGoodPicker1Open: 1;			// X400
		DWORD iGoodPicker2Open: 1;			// X401
		DWORD iGoodPicker3Open: 1;			// X402
		DWORD iGoodPicker4Open: 1;			// X403
		DWORD iGoodPicker5Open: 1;			// X404
		DWORD iGoodPicker6Open: 1;			// X405
		DWORD iGoodPicker1Up: 1;			// X406
		DWORD iGoodPicker1Down: 1;			// X407
					
		DWORD iGoodPicker2Up: 1;			// X408
		DWORD iGoodPicker2Down: 1;			// X409
		DWORD iGoodPicker3Up: 1;			// X410
		DWORD iGoodPicker3Down: 1;			// X411
		DWORD iGoodPicker4Up: 1;			// X412
		DWORD iGoodPicker4Down: 1;			// X413
		DWORD iGoodPicker5Up: 1;			// X414
		DWORD iGoodPicker5Down: 1;			// X415
					
		DWORD iGoodPicker6Up: 1;			// X416
		DWORD iGoodPicker6Down: 1;			// X417
		DWORD iGoodPicker1CMCheck: 1;		// X418
		DWORD iGoodPicker2CMCheck: 1;		// X419
		DWORD iGoodPicker3CMCheck: 1;		// X420
		DWORD iGoodPicker4CMCheck: 1;		// X421
		DWORD iGoodPicker5CMCheck: 1;		// X422
		DWORD iGoodPicker6CMCheck: 1;		// X423
				
		DWORD i424: 1;						// X424
		DWORD i425: 1;						// X425
		DWORD i426: 1;						// X426
		DWORD i427: 1;						// X427
		DWORD iNGPicker6Open: 1;			// X428
		DWORD iNGPicker6Up: 1;				// X429
		DWORD iNGPicker6Down: 1;			// X430
		DWORD iNGPicker6CMCheck: 1;			// X431

	};
} DX_DATA_4;	// Digital Input 4

typedef union tag_DX_DATA_5 {
	DWORD nValue;
	struct {
		DWORD iMUPicker1Open: 1;			// X500
		DWORD iMUPicker2Open: 1;			// X501
		DWORD iMUPicker3Open: 1;			// X502
		DWORD iMUPicker4Open: 1;			// X503
		DWORD iMUPicker5Open: 1;			// X504
		DWORD iMUPicker6Open: 1;			// X505
		DWORD iMUPicker1CMCheck: 1;			// X506
		DWORD iMUPicker2CMCheck: 1;			// X507
						
		DWORD iMUPicker3CMCheck: 1;			// X508
		DWORD iMUPicker4CMCheck: 1;			// X509
		DWORD iMUPicker5CMCheck: 1;			// X510
		DWORD iMUPicker6CMCheck: 1;			// X511
		DWORD i512: 1;						// X512
		DWORD i513: 1;						// X513
		DWORD i514: 1;						// X514
		DWORD i515: 1;						// X515
								
		DWORD iNGVacuumUp: 1;				// X516
		DWORD iNGVacuumDown: 1;				// X517
		DWORD iNGVacuumPad1Check: 1;		// X518
		DWORD iNGVacuumPad2Check: 1;		// X519
		DWORD iNGVacuumPad3Check: 1;		// X520
		DWORD iNGVacuumPad4Check: 1;		// X521
		DWORD iNGVacuumPad5Check: 1;		// X522
		DWORD iNGVacuumPad6Check: 1;		// X523
								
		DWORD iGoodVacuumUp: 1;				// X524
		DWORD iGoodVacuumDown: 1;			// X525
		DWORD iGoodVacuumPad1Check: 1;		// X526
		DWORD iGoodVacuumPad2Check: 1;		// X527
		DWORD iGoodVacuumPad3Check: 1;		// X528
		DWORD iGoodVacuumPad4Check: 1;		// X529
		DWORD iGoodVacuumPad5Check: 1;		// X530
		DWORD iGoodVacuumPad6Check: 1;		// X531

	};
} DX_DATA_5;	// Digital Input 5

typedef union tag_DX_DATA_6 {
	DWORD nValue;
	struct {
		DWORD iUS_UnloadSupport1In: 1;		// X600
		DWORD iUS_UnloadSupport1Out: 1;		// X601
		DWORD iUS_Unload1FEmitter: 1;		// X602
		DWORD iUS_UnloadSupport2In: 1;		// X603
		DWORD iUS_UnloadSupport2Out: 1;		// X604
		DWORD iUS_Unload1FCheck: 1;			// X605
		DWORD iUS_UnloadFullCheck: 1;		// X606
		DWORD i607: 1;						// X607
				                               
		DWORD iUS_LoadSupport1In: 1;		// X608
		DWORD iUS_LoadSupport1Out: 1;		// X609
		DWORD iUS_Load1FEmitter: 1;			// X610
		DWORD iUS_LoadSupport2In: 1;		// X611
		DWORD iUS_LoadSupport2Out: 1;		// X612
		DWORD iUS_Load1FCheck: 1;			// X613
		DWORD iUS_LoadFullCheck: 1;			// X614
		DWORD i615: 1;						// X615
                                               
		DWORD iUS_Z1Check1: 1;				// X616
		DWORD iUS_Z1CheckEmitter1: 1;		// X617
#ifdef ALIGN_NEW
		DWORD iUS_Z1AlignM34In: 1;			// X618
		DWORD iUS_Z1AlignM34Out: 1;			// X619
		DWORD iUS_Z1AlignS12In: 1;			// X620
		DWORD iUS_Z1AlignS12Out: 1;			// X621
#else
		DWORD iUS_Z1AlignS12In: 1;			// X618
		DWORD iUS_Z1AlignS12Out: 1;			// X619
		DWORD iUS_Z1AlignM34In: 1;			// X620
		DWORD iUS_Z1AlignM34Out: 1;			// X621
#endif
		DWORD iUS_Z1Check2: 1;				// X622
		DWORD iUS_Z1CheckEmitter2: 1;		// X623
				                               
		DWORD iUS_Z2Check1: 1;				// X624
		DWORD iUS_Z2CheckEmitter1: 1;		// X625
#ifdef ALIGN_NEW
		DWORD iUS_Z2AlignM34In: 1;			// X626
		DWORD iUS_Z2AlignM34Out: 1;			// X627
		DWORD iUS_Z2AlignS12In: 1;			// X628
		DWORD iUS_Z2AlignS12Out: 1;			// X629
#else
		DWORD iUS_Z2AlignS12In: 1;			// X626
		DWORD iUS_Z2AlignS12Out: 1;			// X627
		DWORD iUS_Z2AlignM34In: 1;			// X628
		DWORD iUS_Z2AlignM34Out: 1;			// X629
#endif
		DWORD iUS_Z2Check2: 1;				// X630
		DWORD iUS_Z2CheckEmitter2: 1;		// X631
	};
} DX_DATA_6;	// Digital Input 6

///////////////////////////////////////////////////////////////////////////////
// Output (Y000 - Y331)

typedef union tag_DY_DATA_0 {
	DWORD nValue;
	struct {
		DWORD oStartLamp: 1;				// Y000
		DWORD oStopLamp: 1;					// Y001
		DWORD oResetLamp: 1;				// Y002
		DWORD oTowerGreen: 1;				// Y003
		DWORD oTowerYellow: 1;				// Y004
		DWORD oTowerRed: 1;					// Y005
		DWORD oAlarmBuzzer1: 1;				// Y006
		DWORD oAlarmBuzzer2: 1;				// Y007
                    
		DWORD oInsideLamp: 1;				// Y008
		DWORD o009: 1;						// Y009
		DWORD o010: 1;						// Y010
		DWORD o011: 1;						// Y011
		DWORD oCameraTrigger: 1;			// Y012
		DWORD oBarcodeTrigger: 1;			// Y013
		DWORD o014: 1;						// Y014
		DWORD o015: 1;						// Y015
                      
		DWORD oLight11: 1;					// Y016
		DWORD oLight12: 1;					// Y017
		DWORD oLight13: 1;					// Y018
		DWORD oLight14: 1;					// Y019
		DWORD oLight21: 1;					// Y020
		DWORD oLight22: 1;					// Y021
		DWORD oLight23: 1;					// Y022
		DWORD oLight24: 1;					// Y023
								
		DWORD oLightBarcode: 1;				// Y024
		DWORD oLight32: 1;					// Y025
		DWORD oLight33: 1;					// Y026
		DWORD oLight34: 1;					// Y027
		DWORD oLight41: 1;					// Y028
		DWORD oLight42: 1;					// Y029
		DWORD oLight43: 1;					// Y030
		DWORD oLight44: 1;					// Y031

	};
} DY_DATA_0;		// Digital Output 0

typedef union tag_DY_DATA_1 {
	DWORD nValue;
	struct {
		DWORD oLS_LoadSupport12In: 1;		// Y100
		DWORD oLS_LoadSupport12Out: 1;		// Y101
		DWORD o102: 1;						// Y102
		DWORD o103: 1;						// Y103
		DWORD o104: 1;						// Y104
		DWORD o105: 1;						// Y105
		DWORD o106: 1;						// Y106
		DWORD o107: 1;						// Y107
        
		DWORD oLS_UnloadSupport12In: 1;		// Y108
		DWORD oLS_UnloadSupport12Out: 1;	// Y109
		DWORD o110: 1;						// Y110
		DWORD o111: 1;						// Y111
		DWORD o112: 1;						// Y112
		DWORD o113: 1;						// Y113
		DWORD o114: 1;						// Y114
		DWORD o115: 1;						// Y115
            
		DWORD o116: 1;						// Y116
		DWORD o117: 1;						// Y117
#ifdef ALIGN_NEW
		DWORD oLS_Z1AlignM34In: 1;			// Y118
		DWORD oLS_Z1AlignM34Out: 1;			// Y119
		DWORD oLS_Z1AlignS12In: 1;			// Y120
		DWORD oLS_Z1AlignS12Out: 1;			// Y121
#else
		DWORD oLS_Z1AlignS12In: 1;			// Y118
		DWORD oLS_Z1AlignS12Out: 1;			// Y119
		DWORD oLS_Z1AlignM34In: 1;			// Y120
		DWORD oLS_Z1AlignM34Out: 1;			// Y121
#endif
		DWORD o122: 1;						// Y122
		DWORD o123: 1;						// Y123
			
		DWORD o124: 1;						// Y124
		DWORD o125: 1;						// Y125
#ifdef ALIGN_NEW
		DWORD oLS_Z2AlignM34In: 1;			// Y126
		DWORD oLS_Z2AlignM34Out: 1;			// Y127
		DWORD oLS_Z2AlignS12In: 1;			// Y128
		DWORD oLS_Z2AlignS12Out: 1;			// Y129
#else
		DWORD oLS_Z2AlignS12In: 1;			// Y126
		DWORD oLS_Z2AlignS12Out: 1;			// Y127
		DWORD oLS_Z2AlignM34In: 1;			// Y128
		DWORD oLS_Z2AlignM34Out: 1;			// Y129
#endif
		DWORD o130: 1;						// Y130
		DWORD o131: 1;						// Y131

	};
} DY_DATA_1;		// Digital Output 1

typedef union tag_DY_DATA_2 {
	DWORD nValue;
	struct {
		DWORD oMLPicker1Open: 1;			// Y200
		DWORD oMLPicker1Close: 1;			// Y201
		DWORD oMLPicker2Open: 1;			// Y202
		DWORD oMLPicker2Close: 1;			// Y203
		DWORD oMLPicker3Open: 1;			// Y204
		DWORD oMLPicker3Close: 1;			// Y205
		DWORD oMLPicker4Open: 1;			// Y206
		DWORD oMLPicker4Close: 1;			// Y207
              
		DWORD oMLPicker5Open: 1;			// Y208
		DWORD oMLPicker5Close: 1;			// Y209
		DWORD oMLPicker6Open: 1;			// Y210
		DWORD oMLPicker6Close: 1;			// Y211
		DWORD o212: 1;						// Y212
		DWORD o213: 1;						// Y213
		DWORD o214: 1;						// Y214
		DWORD o215: 1;						// Y215
              
		DWORD oCMPressUp: 1;				// Y216
		DWORD oCMPressDn: 1;				// Y217
		DWORD o218: 1;						// Y218
		DWORD oInspCMAlign1In: 1;			// Y219
		DWORD oInspCMAlign1Out: 1;			// Y220
		DWORD oInspCMAlign2In: 1;			// Y221
		DWORD oInspCMAlign2Out: 1;			// Y222
		DWORD oInspCMAlign3In: 1;			// Y223
			
		DWORD oInspCMAlign3Out: 1;			// Y224
		DWORD oInspCMAlign4In: 1;			// Y225
		DWORD oInspCMAlign4Out: 1;			// Y226
		DWORD oInspVacuumUp: 1;				// Y227
		DWORD oInspVacuumDown: 1;			// Y228
		DWORD o229: 1;						// Y229
		DWORD o230: 1;						// Y230
		DWORD o231: 1;						// Y231

	};
} DY_DATA_2;		// Digital Output 2

typedef union tag_DY_DATA_3 {
	DWORD nValue;
	struct {
		DWORD oInspVacuumPad1On: 1;			// Y300
		DWORD o301: 1;						// Y301
		DWORD oInspVacuumPad2On: 1;			// Y302
		DWORD o303: 1;						// Y303
		DWORD oInspVacuumPad3On: 1;			// Y304
		DWORD o305: 1;						// Y305
		DWORD oInspVacuumPad4On: 1;			// Y306
		DWORD o307: 1;						// Y307
              
		DWORD oInspVacuumPad5On: 1;			// Y308
		DWORD o309: 1;						// Y309
		DWORD oInspVacuumPad6On: 1;			// Y310
		DWORD o311: 1;						// Y311
		DWORD oNGPicker1Open: 1;			// Y312
		DWORD oNGPicker1Close: 1;			// Y313
		DWORD oNGPicker2Open: 1;			// Y314
		DWORD oNGPicker2Close: 1;			// Y315
              
		DWORD oNGPicker3Open: 1;			// Y316
		DWORD oNGPicker3Close: 1;			// Y317
		DWORD oNGPicker4Open: 1;			// Y318
		DWORD oNGPicker4Close: 1;			// Y319
		DWORD oNGPicker5Open: 1;			// Y320
		DWORD oNGPicker5Close: 1;			// Y321
		DWORD oNGPicker1Up: 1;				// Y322
		DWORD oNGPicker1Down: 1;			// Y323
			
		DWORD oNGPicker2Up: 1;				// Y324
		DWORD oNGPicker2Down: 1;			// Y325
		DWORD oNGPicker3Up: 1;				// Y326
		DWORD oNGPicker3Down: 1;			// Y327
		DWORD oNGPicker4Up: 1;				// Y328
		DWORD oNGPicker4Down: 1;			// Y329
		DWORD oNGPicker5Up: 1;				// Y330
		DWORD oNGPicker5Down: 1;			// Y331

	};
} DY_DATA_3;		// Digital Output 3

typedef union tag_DY_DATA_4 {
	DWORD nValue;
	struct {
		DWORD oGoodPicker1Open: 1;			// Y400
		DWORD oGoodPicker1Close: 1;			// Y401
		DWORD oGoodPicker2Open: 1;			// Y402
		DWORD oGoodPicker2Close: 1;			// Y403
		DWORD oGoodPicker3Open: 1;			// Y404
		DWORD oGoodPicker3Close: 1;			// Y405
		DWORD oGoodPicker4Open: 1;			// Y406
		DWORD oGoodPicker4Close: 1;			// Y407
             
		DWORD oGoodPicker5Open: 1;			// Y408
		DWORD oGoodPicker5Close: 1;			// Y409
		DWORD oGoodPicker6Open: 1;			// Y410
		DWORD oGoodPicker6Close: 1;			// Y411
		DWORD oGoodPicker1Up: 1;			// Y412
		DWORD oGoodPicker1Down: 1;			// Y413
		DWORD oGoodPicker2Up: 1;			// Y414
		DWORD oGoodPicker2Down: 1;			// Y415
              
		DWORD oGoodPicker3Up: 1;			// Y416
		DWORD oGoodPicker3Down: 1;			// Y417
		DWORD oGoodPicker4Up: 1;			// Y418
		DWORD oGoodPicker4Down: 1;			// Y419
		DWORD oGoodPicker5Up: 1;			// Y420
		DWORD oGoodPicker5Down: 1;			// Y421
		DWORD oGoodPicker6Up: 1;			// Y422
		DWORD oGoodPicker6Down: 1;			// Y423
			
		DWORD o424: 1;						// Y424
		DWORD o425: 1;						// Y425
		DWORD o426: 1;						// Y426
		DWORD o427: 1;						// Y427
		DWORD oNGPicker6Open: 1;			// Y428
		DWORD oNGPicker6Close: 1;			// Y429
		DWORD oNGPicker6Up: 1;				// Y430
		DWORD oNGPicker6Down: 1;			// Y431

	};
} DY_DATA_4;		// Digital Output 4

typedef union tag_DY_DATA_5 {
	DWORD nValue;
	struct {
		DWORD oMUPicker1Open: 1;			// Y500
		DWORD oMUPicker1Close: 1;			// Y501
		DWORD oMUPicker2Open: 1;			// Y502
		DWORD oMUPicker2Close: 1;			// Y503
		DWORD oMUPicker3Open: 1;			// Y504
		DWORD oMUPicker3Close: 1;			// Y505
		DWORD oMUPicker4Open: 1;			// Y506
		DWORD oMUPicker4Close: 1;			// Y507
        
		DWORD oMUPicker5Open: 1;			// Y508
		DWORD oMUPicker5Close: 1;			// Y509
		DWORD oMUPicker6Open: 1;			// Y510
		DWORD oMUPicker6Close: 1;			// Y511
		DWORD o512: 1;						// Y512
		DWORD o513: 1;						// Y513
		DWORD o514: 1;						// Y514
		DWORD o515: 1;						// Y515
    
		DWORD oNGVacuumUp: 1;				// Y516
		DWORD oNGVacuumDown: 1;				// Y517
		DWORD oNGVacuumPad1On: 1;			// Y518
		DWORD oNGVacuumPad2On: 1;			// Y519
		DWORD oNGVacuumPad3On: 1;			// Y520
		DWORD oNGVacuumPad4On: 1;			// Y521
		DWORD oNGVacuumPad5On: 1;			// Y522
		DWORD oNGVacuumPad6On: 1;			// Y523
	
		DWORD oGoodVacuumUp: 1;				// Y524
		DWORD oGoodVacuumDown: 1;			// Y525
		DWORD oGoodVacuumPad1On: 1;			// Y526
		DWORD oGoodVacuumPad2On: 1;			// Y527
		DWORD oGoodVacuumPad3On: 1;			// Y528
		DWORD oGoodVacuumPad4On: 1;			// Y529
		DWORD oGoodVacuumPad5On: 1;			// Y530
		DWORD oGoodVacuumPad6On: 1;			// Y531

	};
} DY_DATA_5;		// Digital Output 5

typedef union tag_DY_DATA_6 {
	DWORD nValue;
	struct {
		DWORD oUS_UnloadSupport12In: 1;		// Y600
		DWORD oUS_UnloadSupport12Out: 1;	// Y601
		DWORD o602: 1;						// Y602
		DWORD o603: 1;						// Y603
		DWORD o604: 1;						// Y604
		DWORD o605: 1;						// Y605
		DWORD o606: 1;						// Y606
		DWORD o607: 1;						// Y607
               
		DWORD oUS_LoadSupport12In: 1;		// Y608
		DWORD oUS_LoadSupport12Out: 1;		// Y609
		DWORD o610: 1;						// Y610
		DWORD o611: 1;						// Y611
		DWORD o612: 1;						// Y612
		DWORD o613: 1;						// Y613
		DWORD o614: 1;						// Y614
		DWORD o615: 1;						// Y615
              
		DWORD o616: 1;						// Y616
		DWORD o617: 1;						// Y617
#ifdef ALIGN_NEW
		DWORD oUS_Z1AlignM34In: 1;			// Y618
		DWORD oUS_Z1AlignM34Out: 1;			// Y619
		DWORD oUS_Z1AlignS12In: 1;			// Y620
		DWORD oUS_Z1AlignS12Out: 1;			// Y621
#else
		DWORD oUS_Z1AlignS12In: 1;			// Y618
		DWORD oUS_Z1AlignS12Out: 1;			// Y619
		DWORD oUS_Z1AlignM34In: 1;			// Y620
		DWORD oUS_Z1AlignM34Out: 1;			// Y621
#endif
		DWORD o622: 1;						// Y622
		DWORD o623: 1;						// Y623
				
		DWORD o624: 1;						// Y624
		DWORD o625: 1;						// Y625
#ifdef ALIGN_NEW
		DWORD oUS_Z2AlignM34In: 1;			// Y626
		DWORD oUS_Z2AlignM34Out: 1;			// Y627
		DWORD oUS_Z2AlignS12In: 1;			// Y628
		DWORD oUS_Z2AlignS12Out: 1;			// Y629
#else
		DWORD oUS_Z2AlignS12In: 1;			// Y626
		DWORD oUS_Z2AlignS12Out: 1;			// Y627
		DWORD oUS_Z2AlignM34In: 1;			// Y628
		DWORD oUS_Z2AlignM34Out: 1;			// Y629
#endif
		DWORD o630: 1;						// Y630
		DWORD o631: 1;						// Y631
	};
} DY_DATA_6;		// Digital Output 6

///////////////////////////////////////////////////////////////////////////////
