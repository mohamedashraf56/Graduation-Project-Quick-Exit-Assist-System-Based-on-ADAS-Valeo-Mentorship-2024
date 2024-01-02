/*
 * SYSTICK_int.h
 *
 *  Created on: Dec 12, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_SYSTICK_SYSTICK_INT_H_
#define MCAL_SYSTICK_SYSTICK_INT_H_

#define Single_Interval   0
#define Periodic_Interval 1


#define Divided_8     0
#define no_Divided    1

enum
{
	// CONTROL REGISTER
	SYSTICK_ENABLE,
	TICK_INT,
	CLK_SOURCE,
	COUNT_FLAG = 16,
	//CALIB REGISTER
	SKEW = 30,
	NO_REF,
};

void MSTK_vInit(void);
void MSTK_vSetBusWait(uint32 u8_Ticks);
void MSTK_vSetIntervalSingle  (uint32 u32_Ticks , void (* Ptr)(void));
void MSTK_vSetIntervalPeriodic(uint32 u32_Ticks , void (* Ptr)(void));
void MSTK_vStopInterval(void);

void MSTK_Start(void);

uint32 MSTK_u32GetElapsedTime(void);
uint32 MSTK_u32GetRemainingTime(void);

void MSTK_vSetCallBack(void (*ptr)(void));



#endif /* MCAL_SYSTICK_SYSTICK_INT_H_ */
