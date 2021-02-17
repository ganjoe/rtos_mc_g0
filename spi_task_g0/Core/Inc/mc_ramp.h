/*
 * mc_ramp.h
 *
 *  Created on: 17.02.2021
 *      Author: pymd02
 */

#ifndef INC_MC_RAMP_H_
#define INC_MC_RAMP_H_



typedef struct
	{
	float    TargetValue; 	// Input: Target input (pu)
	uint32_t RampDelayMax;	// Parameter: Maximum delay rate (Q0) - independently with global Q
	float    RampLowLimit;	// Parameter: Minimum limit (pu)
	float    RampHighLimit;	// Parameter: Maximum limit (pu)
	uint32_t RampDelayCount; // Variable: Incremental delay (Q0) - independently with global Q
	float    SetpointValue;	// Output: Target output (pu)
	uint32_t EqualFlag;		// Output: Flag output (Q0) - independently with global Q
	float	Tmp;			// Variable: Temp variable
	} RMPCNTL;


/*-----------------------------------------------------------------------------
Default initalizer for the RMPCNTL object.
-----------------------------------------------------------------------------*/
#define RMPCNTL_DEFAULTS {  0, 		 \
                            5,		 \
                           float(-1),  \
                           float(1),   \
                            0,       \
                          	0,       \
                          	0,       \
                          	0,       \
                   		  }

/*------------------------------------------------------------------------------
 	RAMP Controller Macro Definition
------------------------------------------------------------------------------*/

#define RC_MACRO(v)																	\
	v.Tmp = v.TargetValue - v.SetpointValue;										\
/*  0.0000305 is resolution of Q15 */												\
if (abs(v.Tmp) >= float(0.0000305))				    						\
{																					\
	v.RampDelayCount++	;															\
		if (v.RampDelayCount >= v.RampDelayMax)										\
		{																			\
			if (v.TargetValue >= v.SetpointValue)									\
				v.SetpointValue += float(0.0000305);								\
			else																	\
				v.SetpointValue -= float(0.0000305);								\
																					\
			v.SetpointValue=floatsat(v.SetpointValue,v.RampHighLimit,v.RampLowLimit);\
			v.RampDelayCount = 0;													\
																					\
		}																			\
}																					\
else v.EqualFlag = 0x7FFFFFFF;



#endif /* INC_MC_RAMP_H_ */
