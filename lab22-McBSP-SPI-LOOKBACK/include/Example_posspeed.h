// TI File $Revision: /main/6 $
// Checkin $Date: August 9, 2007   17:15:33 $
//###########################################################################
//
// FILE:	Example_posspeed.h
//
// TITLE:	Pos/speed measurement using EQEP peripheral
//
// DESCRIPTION:
//
// Header file containing data type and object definitions and 
// initializers. 
//
//###########################################################################
// Original Author: SD
//
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#ifndef __POSSPEED__
#define __POSSPEED__

#include "IQmathLib.h"         // Include header for IQmath library
/*-----------------------------------------------------------------------------
Define the structure of the POSSPEED Object 
-----------------------------------------------------------------------------*/
typedef struct {int theta_elec;     	// Output: Motor Electrical angle (Q15)  
                int theta_mech;     	// Output: Motor Mechanical Angle (Q15) 
                int DirectionQep;      	// Output: Motor rotation direction (Q0) 
                int QEP_cnt_idx; 	 	// Variable: Encoder counter index (Q0)
                int theta_raw;     		// Variable: Raw angle from Timer 2 (Q0)            
                int mech_scaler;    	// Parameter: 0.9999/total count, total count = 4000 (Q26)
                int pole_pairs;     	// Parameter: Number of pole pairs (Q0) 
                int cal_angle;     		// Parameter: Raw angular offset between encoder and phase a (Q0) 
                int index_sync_flag; 	// Output: Index sync status (Q0)                   

                Uint32 SpeedScaler;     // Parameter :  Scaler converting 1/N cycles to a GLOBAL_Q speed (Q0) - independently with global Q
                _iq Speed_pr;           // Output :  speed in per-unit
                Uint32 BaseRpm;         // Parameter : Scaler converting GLOBAL_Q speed to rpm (Q0) speed - independently with global Q
                int32 SpeedRpm_pr;      // Output : speed in r.p.m. (Q0) - independently with global Q                               

                _iq  oldpos;  			// Input: Electrical angle (pu) 
                _iq Speed_fr;           // Output :  speed in per-unit
                int32 SpeedRpm_fr;     	// Output : Speed in rpm  (Q0) - independently with global Q
                void (*init)();     	// Pointer to the init funcion          
                void (*calc)();    		// Pointer to the calc funtion        
                }  POSSPEED;

/*-----------------------------------------------------------------------------
Define a POSSPEED_handle
-----------------------------------------------------------------------------*/
typedef POSSPEED *POSSPEED_handle;

/*-----------------------------------------------------------------------------
Default initializer for the POSSPEED Object.
-----------------------------------------------------------------------------*/

#if (CPU_FRQ_150MHZ)
  #define POSSPEED_DEFAULTS {0x0, 0x0,0x0,0x0,0x0,16776,2,0,0x0,\
        94,0,6000,0,\
        0,0,0,\
        (void (*)(long))POSSPEED_Init,\
        (void (*)(long))POSSPEED_Calc }
#endif
#if (CPU_FRQ_100MHZ)
  #define POSSPEED_DEFAULTS {0x0, 0x0,0x0,0x0,0x0,16776,2,0,0x0,\
        63,0,6000,0,\
        0,0,0,\
        (void (*)(long))POSSPEED_Init,\
        (void (*)(long))POSSPEED_Calc }
#endif


/*-----------------------------------------------------------------------------
Prototypes for the functions in posspeed.c                                 
-----------------------------------------------------------------------------*/
void POSSPEED_Init(void);                                              
void POSSPEED_Calc(POSSPEED_handle);
                
#endif /*  __POSSPEED__ */




