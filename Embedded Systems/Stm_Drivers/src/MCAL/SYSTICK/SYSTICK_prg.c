/*
 * SYSTICK_prg.c
 *
 *  Created on: Dec 12, 2023
 *      Author: Mamdouh
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"

#include "SYSTICK_int.h"
#include "SYSTICK_prv.h"
#include "SYSTICK_cfg.h"


uint8 MSTK_u8_ModeOfInterval ;
static void (*SYSTICK_CallBack)(void) = 0 ;



/* ********************************************************************
 * Name     : MSTK_vSetCallBack
 * function : copy the address of function in main to SYSTICK_CALLBack
 *          : which if called in ISR
 * Input1    : FUNCTION ADDRESS (Func Name)
 * Return   : NOTHING
 **********************************************************************/
void MSTK_vSetCallBack(void (*ptr)(void))
{
	SYSTICK_CallBack = ptr;
}



/* ********************************************************************
 * Name     : MSTK_vInit
 * function : initialize the SYSTEM TIMER /set Stop interrupt & stop the timer
 *           ONLY Sets Prescaler AHB or AHB/8
 * Return   : NOTHING
 **********************************************************************/
void MSTK_vInit(void)
{
	// TIMER INIT IS STOPED
	CLEAR_BIT(STK->CTRL,SYSTICK_ENABLE);
	// DISABLE THE INTERRUPT
	CLEAR_BIT(STK->CTRL,TICK_INT);
	// CLOCK AHB
	SET_BIT(STK->CTRL,CLK_SOURCE);
}



/* ********************************************************************
 * Name     : MSTK_Start
 * function : start the timer and the isr
 * Return   : NOTHING
 **********************************************************************/
void MSTK_Start(void)
{
	CLEAR_BIT(STK->CTRL,SYSTICK_ENABLE);

	STK->LOAD = 15000000;

	// TIMER START
	SET_BIT(STK->CTRL,SYSTICK_ENABLE);
	// enable THE INTERRUPT
	SET_BIT(STK->CTRL,TICK_INT);
}

/* ********************************************************************
 * Name     : MSTK_vSetBusWait
 * function : Delay function stuck in it until it finished counting
 * Return   : NOTHING
 **********************************************************************/

void MSTK_vSetBusWait(uint32 u32_Ticks)
{

	// STOP THE TIMER FIRST TO LOAD A VALUE
	CLEAR_BIT(STK->CTRL,SYSTICK_ENABLE);

	// LOAD A TICKS INTO THA LOAD REGISTER
	STK->LOAD = u32_Ticks;

	// ENABLE THE TIMER
	SET_BIT(STK->CTRL,SYSTICK_ENABLE);

	// WAIT UNTIL THE COUNTER COUNT TO 0
	while((GET_BIT(STK->CTRL,COUNT_FLAG)) == 0);

	// STOP THE TIMER AND CLEAR REGISTERS
	CLEAR_BIT(STK->CTRL,SYSTICK_ENABLE);
	STK->LOAD = 0;
	STK->VAL  = 0;
}



/* ********************************************************************
 * Name     : MSTK_vSetIntervalSingle
 * function : Call a given function after a specific time (only one time)
 * Input1   : Ticks in Microsecond
 * Input2   : FUNCTION ADDRESS (Func Name)
 * Return   : NOTHING
 **********************************************************************/
void MSTK_vSetIntervalSingle  (uint32 u32_Ticks , void (* ptr)(void))
{
	// STOP THE TIMER FIRST TO LOAD A VALUE
	CLEAR_BIT(STK->CTRL,SYSTICK_ENABLE);
	// LOAD A TICKS INTO THA LOAD REGISTER
	STK->LOAD = u32_Ticks;

	// COPY THE ADDRESS OF FUNCTION TO CALLBACK WHICH CALLED IN ISR
	SYSTICK_CallBack = ptr ;

	// THE THE MODE TO SINGLE (CALL ONE TIME ONLY)
	MSTK_u8_ModeOfInterval = Single_Interval;
	// START THE TIMER
	SET_BIT(STK->CTRL,SYSTICK_ENABLE);
	// ENABLE INTERRUPT
	SET_BIT(STK->CTRL,TICK_INT);

}







/* ********************************************************************
 * Name     : MSTK_vSetIntervalPeriodic
 * function : Call a given function after a specific time (many times until u stop it)
 * Input1   : Ticks in Microsecond
 * Input2   : FUNCTION ADDRESS (Func Name)
 * Return   : NOTHING
 **********************************************************************/
void MSTK_vSetIntervalPeriodic(uint32 u32_Ticks , void (* ptr)(void))
{
	// STOP THE TIMER FIRST TO LOAD A VALUE
		CLEAR_BIT(STK->CTRL,SYSTICK_ENABLE);
		// LOAD A TICKS INTO THA LOAD REGISTER
		STK->LOAD = u32_Ticks;

		// COPY THE ADDRESS OF FUNCTION TO CALLBACK WHICH CALLED IN ISR
		SYSTICK_CallBack = ptr ;

		// THE THE MODE TO SINGLE (CALL ONE TIME ONLY)
		MSTK_u8_ModeOfInterval = Periodic_Interval;
		// START THE TIMER
		SET_BIT(STK->CTRL,SYSTICK_ENABLE);
		// ENABLE INTERRUPT
		SET_BIT(STK->CTRL,TICK_INT);

}



/* ********************************************************************
 * Name     : MSTK_vStopInterval
 * function : Stop the IntervalPeriodic
 * input    : void
 * Return   : NOTHING
 **********************************************************************/
void MSTK_vStopInterval(void)
{
	// DISABLE THE TIMER
	CLEAR_BIT(STK->CTRL,SYSTICK_ENABLE);
	// DISABLE INTERUUPT
	CLEAR_BIT(STK->CTRL,TICK_INT);
	// ZERO LOAD REGISTER
	STK->LOAD = 0 ;
	// ZERO ON VAL REGISTER
	STK->VAL = 0;

}



/* ********************************************************************
 * Name     : MSTK_u32GetElapsedTime
 * function : Calculate the elapsed time
 * input    : void
 * Return   : the time after we start counting
 **********************************************************************/
uint32 MSTK_u32GetElapsedTime(void)
{
	uint32 result = 0;
	result = (STK->LOAD) - (STK->VAL);
	return result;
}



/* ********************************************************************
 * Name     : MSTK_u32GetRemainingTime
 * function : Calculate the remaining time
 * input    : void
 * Return   : the remaining time
 **********************************************************************/
uint32 MSTK_u32GetRemainingTime(void)
{
	return (STK->VAL);
}







void SysTick_Handler(void)
{

	if(MSTK_u8_ModeOfInterval == Single_Interval)
	{
		// STOP THE TIMER
		CLEAR_BIT(STK->CTRL,SYSTICK_ENABLE);
		// ENABLE INTERRUPT
		CLEAR_BIT(STK->CTRL,TICK_INT);
		//CLEAR LOAD REEG
		STK->LOAD = 0;
		//CLEAR VAL REG
		STK->VAL = 0;
	}

	// CALLL THE SINGLE OR PRIODIC FUNCTION
	if(SYSTICK_CallBack != 0)
	{
	SYSTICK_CallBack();
	}

	// CLEAR THE PENDING FLAG BY READING IT
	uint8 clear_flag ;
	clear_flag = GET_BIT(STK->CTRL,COUNT_FLAG);
}






