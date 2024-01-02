/*
 * TIM2_prg.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Mamdouh
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"

#include "TIM2_cfg.h"
#include "TIM2_prv.h"
#include "TIM2_int.h"

static void(*TIMER2_Call_Back)(void) = 0;

// THIS FUNCTION SET THE PRESCALER TO THE TIMER
void TIMER2_Set_PSC(uint32 PRESCALER)
{
	TIMER2->TIMx_PSC = PRESCALER -1 ;
}


/* ********************************************************************
 * Name     : TIMER2_Set_Auto_Reload
 * function : Set the Auto reload value which is autoload in counter
 * Input1    : Value u need to count
 * Return   : NOTHING
 **********************************************************************/
void TIMER2_Set_Auto_Reload(uint32 Value)
{
	TIMER2->TIMx_ARR  = Value - 1;
}

// THIS FUNCTION ENABLE OR DISABLE THE TIMER2 INTERRUPT
// INPUT TIMER2_EN_INTERRUPT OR TIMER2_DIS_INTERRUPT
void TIMER2_Enable_Interrupt(uint8 Value)
{
	insert_bit(TIMER2->TIMx_DIER,UIF, Value);
}

// THIS FUNCTION START OR STOP THE TIMER
// IMPUT TIMAR2_Start Or TIMER2_Stop
void TIMER2_Start_Stop(uint8 Mode)
{
	insert_bit(TIMER2->TIMx_CR1,TIM_CR1_CEN, Mode);
}


// this function return the Value in the counter tha counted
uint32 TIMER2_Read_Counter(void)
{
	uint32 Timer2_Counter;
	Timer2_Counter = TIMER2->TIMx_CNT;

	return Timer2_Counter;
}


/* ********************************************************************
 * Name     : TIMER2_Set_Call_Back
 * function : Set call back
 * Input1    : FUNCTION ADDRESS (Func Name)
 * Return   : NOTHING
 **********************************************************************/
void TIMER2_Set_Call_Back(void(*PTR_CALL_BACK)(void))
{
	TIMER2_Call_Back = PTR_CALL_BACK;
}



uint32 TIMER2_ICU_Result(void)
{
	return (TIMER2->TIMx_CCR1);
}


void TIMER2_ICU(void)
{
	 INSERST_BITS(TIMER2->TIMx_CCMR1,0b01,two_one,0);
	 INSERST_BITS(TIMER2->TIMx_CCMR1,0b1100,four_one,4);
	 // reset is 0 no need to reset it
	 /*
	  * Select the edge of the active transition on the TI1 channel by writing the CC1P and
      CC1NP bits to 00 in the TIMx_CCER register (rising edge in this case)
	  */
	 // this for both edges
	 INSERST_BITS(TIMER2->TIMx_CCER,ICU_Both,three_one,1);

	 // ENABLE CAPTURE / COMPARE
	 SET_BIT(TIMER2->TIMx_CCER,0);
	 // enable for the ICU interrput
	 SET_BIT(TIMER2->TIMx_DIER,1);

}



void TIM2_IRQHandler(void)
{
	uint8 State;

	State = GET_BIT(TIMER2->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER2->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER2->TIMx_SR,CC1IF);

	if(State)
	{
		// CLEAR THE INTERRUPT FLAG
		CLEAR_BIT(TIMER2->TIMx_SR,TIM_SR_UIF);
	}

	if(TIMER2_Call_Back != 0)
	{
		TIMER2_Call_Back();
	}

}


void TIMER2_Clear_Counter(void)
{
	TIMER2->TIMx_CNT = 0;
}



// input : ICU_Rising ICU_Failing ICU_Both
void TIMER2_ICU_Edges(uint8 Type)
{
	 INSERST_BITS(TIMER2->TIMx_CCER,Type,three_one,1);
}



