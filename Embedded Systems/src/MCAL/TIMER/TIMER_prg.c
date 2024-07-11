/*
 * TIM2_prg.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Mamdouh
 *      v: 1.00
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"

#include "../../MCAL/RCC/RCC_int.h"
#include "../../MCAL/NVIC/NVIC_int.h"

#include "TIMER_cfg.h"
#include "TIMER_int.h"
#include "TIMER_prv.h"

static void(*TIMER_Call_Back[6])(void) = {0,0,0,0,0,0};
// call back function for the timer 1 is call[4]




sint8 TIMER_Init(TIMER_Init_Config_St * TIMER_Config_St)
{
	sint8 state = 1;

	switch(TIMER_Config_St->TIMER_NUM)
	{
	case TIMER1_Selected :
	{
		RCC_Enable_Clock(RCC_APB2, RCC_TIM1);
		NVIC_En_Interrupt(NVIC_TIM1_CC);
	}
	break;
	case TIMER2_Selected :
	{
		RCC_Enable_Clock(RCC_APB1, RCC_TIM2);
		NVIC_En_Interrupt(NVIC_TIM2);
	}
	break;
	case TIMER3_Selected :
	{
		RCC_Enable_Clock(RCC_APB1, RCC_TIM3);
		NVIC_En_Interrupt(NVIC_TIM3);
	}
	break;
	case TIMER4_Selected :
	{
		RCC_Enable_Clock(RCC_APB1, RCC_TIM4);
		NVIC_En_Interrupt(NVIC_TIM4);
	}
	break;
	case TIMER5_Selected :
	{
		RCC_Enable_Clock(RCC_APB1, RCC_TIM5);
		NVIC_En_Interrupt(NVIC_TIM5);
	}
	break;
	case TIMER9_Selected :
		{
			RCC_Enable_Clock(RCC_APB2, RCC_TIM5);
			NVIC_En_Interrupt(NVIC_TIM1_BRK_TIM9);
		}
		break;

	default :
	{
		state = -1;
		// returning -1 if this is wrong init
		return state;
	}
	}

	return state;
}




// THIS FUNCTION SET THE PRESCALER TO THE TIMER
void TIMER_Set_Psc(TIMER_Init_Config_St * TIMER_Config_St)
{
	switch(TIMER_Config_St->TIMER_NUM)
	{
	case TIMER1_Selected :
		TIMER1->TIMx_PSC = TIMER_Config_St->SET_Psc -1 ;
		break;
	case TIMER2_Selected :
		TIMER2->TIMx_PSC = TIMER_Config_St->SET_Psc -1 ;
		break;

	case TIMER3_Selected :
		TIMER3->TIMx_PSC = TIMER_Config_St->SET_Psc -1 ;
		break;

	case TIMER4_Selected :
		TIMER4->TIMx_PSC = TIMER_Config_St->SET_Psc -1 ;
		break;

	case TIMER5_Selected :
		TIMER5->TIMx_PSC = TIMER_Config_St->SET_Psc -1 ;
		break;
	case TIMER9_Selected :
		TIMER9->TIMx_PSC = TIMER_Config_St->SET_Psc -1 ;
		break;
	}

}


/* ********************************************************************
 * Name     : TIMER2_Set_Auto_Reload
 * function : Set the Auto reload value which is autoload in counter
 * Input1    : Value u need to count
 * Return   : NOTHING
 **********************************************************************/
void TIMER_Set_Auto_Reload(TIMER_Init_Config_St * TIMER_Config_St)
{
	switch (TIMER_Config_St->TIMER_NUM)
	{
	case TIMER1_Selected :
		TIMER1->TIMx_ARR  = TIMER_Config_St->SET_Auto_Relaod - 1;
		break;
	case TIMER2_Selected :
		TIMER2->TIMx_ARR  = TIMER_Config_St->SET_Auto_Relaod - 1;
		break;
	case TIMER3_Selected :
		TIMER3->TIMx_ARR  = TIMER_Config_St->SET_Auto_Relaod - 1;
		break;
	case TIMER4_Selected :
		TIMER4->TIMx_ARR  = TIMER_Config_St->SET_Auto_Relaod - 1;
		break;
	case TIMER5_Selected :
		TIMER5->TIMx_ARR  = TIMER_Config_St->SET_Auto_Relaod - 1;
		break;
	case TIMER9_Selected :
		TIMER9->TIMx_ARR  = TIMER_Config_St->SET_Auto_Relaod - 1;
		break;
	}
}

// THIS FUNCTION ENABLE OR DISABLE THE TIMER2 INTERRUPT
// INPUT TIMER2_EN_INTERRUPT OR TIMER2_DIS_INTERRUPT
void TIMER_Enable_Interrupt(TIMER_Init_Config_St * TIMER_Config_St,uint8 Mode)
{
	switch (TIMER_Config_St->TIMER_NUM)
	{
	case TIMER1_Selected :
		insert_bit(TIMER1->TIMx_DIER,UIF, Mode);
		break;
	case TIMER2_Selected :
		insert_bit(TIMER2->TIMx_DIER,UIF, Mode);
		break;
	case TIMER3_Selected :
		insert_bit(TIMER3->TIMx_DIER,UIF, Mode);
		break;
	case TIMER4_Selected :
		insert_bit(TIMER4->TIMx_DIER,UIF, Mode);
		break;
	case TIMER5_Selected :
		insert_bit(TIMER5->TIMx_DIER,UIF, Mode);
		break;
	case TIMER9_Selected :
		insert_bit(TIMER9->TIMx_DIER,UIF, Mode);
		break;
	}
}

// THIS FUNCTION START OR STOP THE TIMER
// IMPUT TIMAR2_Start Or TIMER2_Stop
void TIMER_Start_Stop(TIMER_Init_Config_St * TIMER_Config_St,uint8 Mode)
{
	switch (TIMER_Config_St->TIMER_NUM)
	{
	case TIMER1_Selected :
		insert_bit(TIMER1->TIMx_CR1,TIM_CR1_CEN, Mode);
		break;
	case TIMER2_Selected :
		insert_bit(TIMER2->TIMx_CR1,TIM_CR1_CEN, Mode);
		break;
	case TIMER3_Selected :
		insert_bit(TIMER3->TIMx_CR1,TIM_CR1_CEN, Mode);
		break;
	case TIMER4_Selected :
		insert_bit(TIMER4->TIMx_CR1,TIM_CR1_CEN, Mode);
		break;
	case TIMER5_Selected :
		insert_bit(TIMER5->TIMx_CR1,TIM_CR1_CEN, Mode);
		break;
	case TIMER9_Selected :
		insert_bit(TIMER9->TIMx_CR1,TIM_CR1_CEN, Mode);
		break;
	}
}


// this function return the Value in the counter tha counted
uint32 TIMER_Read_Counter(TIMER_Init_Config_St * TIMER_Config_St)
{
	uint32 Timer_Counter;

	sint8 state  = 1;
	switch (TIMER_Config_St->TIMER_NUM)
	{
	case TIMER1_Selected :
		Timer_Counter = TIMER1->TIMx_CNT;
		break;
	case TIMER2_Selected :
		Timer_Counter = TIMER2->TIMx_CNT;
		break;
	case TIMER3_Selected :
		Timer_Counter = TIMER3->TIMx_CNT;
		break;
	case TIMER4_Selected :
		Timer_Counter = TIMER4->TIMx_CNT;
		break;
	case TIMER5_Selected :
		Timer_Counter = TIMER5->TIMx_CNT;
		break;
	case TIMER9_Selected :
		Timer_Counter = TIMER9->TIMx_CNT;
		break;
	default :
		// return -1 if the number of timer doesn't match one of 2,3,4,5
		state = -1;
		return state;
		break;

	}

	return Timer_Counter;
}


/* ********************************************************************
 * Name     : TIMER2_Set_Call_Back
 * function : Set call back
 * Input1    : FUNCTION ADDRESS (Func Name)
 * Return   : NOTHING
 **********************************************************************/
sint8 TIMER_Set_Call_Back(TIMER_Init_Config_St * TIMER_Config_St)
{
	sint8 state  = 1;

	switch (TIMER_Config_St->TIMER_NUM)
	{
	// call back function for the timer 1 is call[4] //////////// note for handler
	case TIMER1_Selected :
		TIMER_Call_Back[4] = TIMER_Config_St->SET_Timer_Call_Back;
		break;
	case TIMER2_Selected :
		TIMER_Call_Back[0] = TIMER_Config_St->SET_Timer_Call_Back;
		break;
	case TIMER3_Selected :
		TIMER_Call_Back[1] = TIMER_Config_St->SET_Timer_Call_Back;
		break;
	case TIMER4_Selected :
		TIMER_Call_Back[2] = TIMER_Config_St->SET_Timer_Call_Back;
		break;
	case TIMER5_Selected :
		TIMER_Call_Back[3] = TIMER_Config_St->SET_Timer_Call_Back;
		break;
	case TIMER9_Selected :
		TIMER_Call_Back[5] = TIMER_Config_St->SET_Timer_Call_Back;
		break;

	default :
		// return -1 if the number of timer doesn't match one of 2,3,4,5
		state = -1;
		return state;
		break;
	}

	// return 1 if everything is going well
	return state;
}



uint32 TIMER_ICU_Result(TIMER_Init_Config_St * TIMER_Config_St)
{
	sint8 state =1;

	switch (TIMER_Config_St->TIMER_NUM)
	{
	// TIM1 CCR registers are 16 bit not 32
	case TIMER1_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1:
			return (TIMER1->TIMx_CCR1);
			break;
		case CHANNEL_2:
			return (TIMER1->TIMx_CCR2);
			break;
		case CHANNEL_3:
			return (TIMER1->TIMx_CCR3);
			break;
		case CHANNEL_4:
			return (TIMER1->TIMx_CCR4);
			break;
		}
	}
		break;
	case TIMER2_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1:
			return (TIMER2->TIMx_CCR1);
			break;
		case CHANNEL_2:
			return (TIMER2->TIMx_CCR2);
			break;
		case CHANNEL_3:
			return (TIMER2->TIMx_CCR3);
			break;
		case CHANNEL_4:
			return (TIMER2->TIMx_CCR4);
			break;
		}
	}
		break;
	case TIMER3_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1:
			return (TIMER3->TIMx_CCR1);
			break;
		case CHANNEL_2:
			return (TIMER3->TIMx_CCR2);
			break;
		case CHANNEL_3:
			return (TIMER3->TIMx_CCR3);
			break;
		case CHANNEL_4:
			return (TIMER3->TIMx_CCR4);
			break;
		}
	}
		break;
	case TIMER4_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1:
			return (TIMER4->TIMx_CCR1);
			break;
		case CHANNEL_2:
			return (TIMER4->TIMx_CCR2);
			break;
		case CHANNEL_3:
			return (TIMER4->TIMx_CCR3);
			break;
		case CHANNEL_4:
			return (TIMER4->TIMx_CCR4);
			break;
		}
	}
		break;
	case TIMER5_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1:
			return (TIMER5->TIMx_CCR1);
			break;
		case CHANNEL_2:
			return (TIMER5->TIMx_CCR2);
			break;
		case CHANNEL_3:
			return (TIMER5->TIMx_CCR3);
			break;
		case CHANNEL_4:
			return (TIMER5->TIMx_CCR4);
			break;
		}
	}
	break;

	// TIM9 has only 2 channels
	case TIMER9_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1:
			return (TIMER9->TIMx_CCR1);
			break;
		case CHANNEL_2:
			return (TIMER9->TIMx_CCR2);
			break;
		}
	}
		break;
		break;

	default :
		// return -1 if the number of timer doesn't match one of 2,3,4,5
		state = -1;
		return state;
		break;
	}

	return state;
}


sint8 TIMER_Mode_ICU(TIMER_Init_Config_St * TIMER_Config_St)
{
	sint8 state = 1;

	switch (TIMER_Config_St->TIMER_NUM)
	{
	case TIMER1_Selected :
		{
			switch(TIMER_Config_St->SET_Icu_Channel)
			{
			case CHANNEL_1:
				// Configure channel 1 in input capture mode
				SET_BIT(TIMER1->TIMx_CCMR1,0);
				// Set the polarity to capture (Rising , failing _ Both)
				INSERST_BITS(TIMER1->TIMx_CCER,1,3,(TIMER_Config_St->SET_Edge_Type));
				// ENABLE CAPTURE / COMPARE
				SET_BIT(TIMER1->TIMx_CCER,0);
			    // Enable the capture/compare interrupt for Channel 1
				SET_BIT(TIMER1->TIMx_DIER,1);
				break;
			case CHANNEL_2 :
				SET_BIT(TIMER1->TIMx_CCMR1,8);
				INSERST_BITS(TIMER1->TIMx_CCER,5,3,(TIMER_Config_St->SET_Edge_Type));
				SET_BIT(TIMER1->TIMx_CCER,4);
				SET_BIT(TIMER1->TIMx_DIER,2);
				break;
			case CHANNEL_3:
				SET_BIT(TIMER1->TIMx_CCMR2,0);
				INSERST_BITS(TIMER1->TIMx_CCER,9,3,(TIMER_Config_St->SET_Edge_Type));
				SET_BIT(TIMER1->TIMx_CCER,8);
				SET_BIT(TIMER1->TIMx_DIER,3);
				break;
			case CHANNEL_4 :
				SET_BIT(TIMER1->TIMx_CCMR2,8);
				INSERST_BITS(TIMER1->TIMx_CCER,13,3,(TIMER_Config_St->SET_Edge_Type));
				SET_BIT(TIMER1->TIMx_CCER,12);
				SET_BIT(TIMER1->TIMx_DIER,4);
				break;
			}
		}
			break;

	case TIMER2_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1:
			// Configure channel 1 in input capture mode
			SET_BIT(TIMER2->TIMx_CCMR1,0);
			// Set the polarity to capture (Rising , failing _ Both)
			INSERST_BITS(TIMER2->TIMx_CCER,1,3,(TIMER_Config_St->SET_Edge_Type));
			// ENABLE CAPTURE / COMPARE
			SET_BIT(TIMER2->TIMx_CCER,0);
		    // Enable the capture/compare interrupt for Channel 1
			SET_BIT(TIMER2->TIMx_DIER,1);
			break;
		case CHANNEL_2 :
			SET_BIT(TIMER2->TIMx_CCMR1,8);
			INSERST_BITS(TIMER2->TIMx_CCER,5,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER2->TIMx_CCER,4);
			SET_BIT(TIMER2->TIMx_DIER,2);
			break;
		case CHANNEL_3:
			SET_BIT(TIMER2->TIMx_CCMR2,0);
			INSERST_BITS(TIMER2->TIMx_CCER,9,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER2->TIMx_CCER,8);
			SET_BIT(TIMER2->TIMx_DIER,3);
			break;
		case CHANNEL_4 :
			SET_BIT(TIMER2->TIMx_CCMR2,8);
			INSERST_BITS(TIMER2->TIMx_CCER,13,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER2->TIMx_CCER,12);
			SET_BIT(TIMER2->TIMx_DIER,4);
			break;
		}
	}
		break;

	case TIMER3_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1:
			// Configure channel 1 in input capture mode
			SET_BIT(TIMER3->TIMx_CCMR1,0);
			// Set the polarity to capture (Rising , failing _ Both)
			INSERST_BITS(TIMER3->TIMx_CCER,1,3,(TIMER_Config_St->SET_Edge_Type));
			// ENABLE CAPTURE / COMPARE
			SET_BIT(TIMER3->TIMx_CCER,0);
		    // Enable the capture/compare interrupt for Channel 1
			SET_BIT(TIMER3->TIMx_DIER,1);
			break;
		case CHANNEL_2 :
			SET_BIT(TIMER3->TIMx_CCMR1,8);
			INSERST_BITS(TIMER3->TIMx_CCER,5,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER3->TIMx_CCER,4);
			SET_BIT(TIMER3->TIMx_DIER,2);
			break;
		case CHANNEL_3:
			SET_BIT(TIMER3->TIMx_CCMR2,0);
			INSERST_BITS(TIMER3->TIMx_CCER,9,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER3->TIMx_CCER,8);
			SET_BIT(TIMER3->TIMx_DIER,3);
			break;
		case CHANNEL_4 :
			SET_BIT(TIMER3->TIMx_CCMR2,8);
			INSERST_BITS(TIMER3->TIMx_CCER,13,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER3->TIMx_CCER,12);
			SET_BIT(TIMER3->TIMx_DIER,4);
			break;
		}
	}
		break;
	case TIMER4_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1:
			// Configure channel 1 in input capture mode
			SET_BIT(TIMER4->TIMx_CCMR1,0);
			// Set the polarity to capture (Rising , failing _ Both)
			INSERST_BITS(TIMER4->TIMx_CCER,1,3,(TIMER_Config_St->SET_Edge_Type));
			// ENABLE CAPTURE / COMPARE
			SET_BIT(TIMER4->TIMx_CCER,0);
		    // Enable the capture/compare interrupt for Channel 1
			SET_BIT(TIMER4->TIMx_DIER,1);
			break;
		case CHANNEL_2 :
			SET_BIT(TIMER4->TIMx_CCMR1,8);
			INSERST_BITS(TIMER4->TIMx_CCER,5,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER4->TIMx_CCER,4);
			SET_BIT(TIMER4->TIMx_DIER,2);
			break;
		case CHANNEL_3:
			SET_BIT(TIMER4->TIMx_CCMR2,0);
			INSERST_BITS(TIMER4->TIMx_CCER,9,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER4->TIMx_CCER,8);
			SET_BIT(TIMER4->TIMx_DIER,3);
			break;
		case CHANNEL_4 :
			SET_BIT(TIMER4->TIMx_CCMR2,8);
			INSERST_BITS(TIMER4->TIMx_CCER,13,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER4->TIMx_CCER,12);
			SET_BIT(TIMER4->TIMx_DIER,4);
			break;
		}
	}
		break;
	case TIMER5_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1:
			// Configure channel 1 in input capture mode
			SET_BIT(TIMER5->TIMx_CCMR1,0);
			// Set the polarity to capture (Rising , failing _ Both)
			INSERST_BITS(TIMER5->TIMx_CCER,1,3,(TIMER_Config_St->SET_Edge_Type));
			// ENABLE CAPTURE / COMPARE
			SET_BIT(TIMER5->TIMx_CCER,0);
		    // Enable the capture/compare interrupt for Channel 1
			SET_BIT(TIMER5->TIMx_DIER,1);
			break;
		case CHANNEL_2 :
			SET_BIT(TIMER5->TIMx_CCMR1,8);
			INSERST_BITS(TIMER5->TIMx_CCER,5,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER5->TIMx_CCER,4);
			SET_BIT(TIMER5->TIMx_DIER,2);
			break;
		case CHANNEL_3:
			SET_BIT(TIMER5->TIMx_CCMR2,0);
			INSERST_BITS(TIMER5->TIMx_CCER,9,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER5->TIMx_CCER,8);
			SET_BIT(TIMER5->TIMx_DIER,3);
			break;
		case CHANNEL_4 :
			SET_BIT(TIMER5->TIMx_CCMR2,8);
			INSERST_BITS(TIMER5->TIMx_CCER,13,3,(TIMER_Config_St->SET_Edge_Type));
			SET_BIT(TIMER5->TIMx_CCER,12);
			SET_BIT(TIMER5->TIMx_DIER,4);
			break;
		}
	}
		break;
	//TIM9 has only 2 channels
	case TIMER9_Selected :
		{
			switch(TIMER_Config_St->SET_Icu_Channel)
			{
			case CHANNEL_1:
				// Configure channel 1 in input capture mode
				SET_BIT(TIMER9->TIMx_CCMR1,0);
				// Set the polarity to capture (Rising , failing _ Both)
				INSERST_BITS(TIMER9->TIMx_CCER,1,3,(TIMER_Config_St->SET_Edge_Type));
				// ENABLE CAPTURE / COMPARE
				SET_BIT(TIMER9->TIMx_CCER,0);
			    // Enable the capture/compare interrupt for Channel 1
				SET_BIT(TIMER9->TIMx_DIER,1);
				break;
			case CHANNEL_2 :
				SET_BIT(TIMER9->TIMx_CCMR1,8);
				INSERST_BITS(TIMER1->TIMx_CCER,5,3,(TIMER_Config_St->SET_Edge_Type));
				SET_BIT(TIMER9->TIMx_CCER,4);
				SET_BIT(TIMER9->TIMx_DIER,2);
				break;
			}
		}
			break;
	default :
		// return -1 if the number of timer doesn't match one of 2,3,4,5
		state = -1;
		return state;
		break;
	}

	 return state;
}



sint8 TIMER_Clear_Counter(TIMER_Init_Config_St * TIMER_Config_St)
{
	sint8 state = 1;

	switch (TIMER_Config_St->TIMER_NUM)
	{
	case TIMER1_Selected :
		TIMER1->TIMx_CNT = 0;
		break;
	case TIMER2_Selected :
		TIMER2->TIMx_CNT = 0;
		break;
	case TIMER3_Selected :
		TIMER3->TIMx_CNT = 0;
		break;
	case TIMER4_Selected :
		TIMER4->TIMx_CNT = 0;
		break;
	case TIMER5_Selected :
		TIMER5->TIMx_CNT = 0;
		break;
	case TIMER9_Selected :
		TIMER9->TIMx_CNT = 0;
		break;
	default :
		// return -1 if the number of timer doesn't match one of 2,3,4,5
		state = -1;
		return state;
		break;
	}
	// returning 1 if everything is going well
	return state;
}



// input : ICU_Rising ICU_Failing ICU_Both
sint8 TIMER_Set_ICU_Edges(TIMER_Init_Config_St * TIMER_Config_St,uint8 Type)
{
	sint8 state = 1;

	switch (TIMER_Config_St->TIMER_NUM)
	{
	case TIMER1_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1 :
			INSERST_BITS(TIMER1->TIMx_CCER,1,3,Type);
			break;
		case CHANNEL_2 :
			INSERST_BITS(TIMER1->TIMx_CCER,5,3,Type);
			break;
		case CHANNEL_3 :
			INSERST_BITS(TIMER1->TIMx_CCER,9,3,Type);
			break;
		case CHANNEL_4 :
			INSERST_BITS(TIMER1->TIMx_CCER,13,3,Type);
			break;
		}
	}
		break;
	case TIMER2_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1 :
			INSERST_BITS(TIMER2->TIMx_CCER,1,3,Type);
			break;
		case CHANNEL_2 :
			INSERST_BITS(TIMER2->TIMx_CCER,5,3,Type);
			break;
		case CHANNEL_3 :
			INSERST_BITS(TIMER2->TIMx_CCER,9,3,Type);
			break;
		case CHANNEL_4 :
			INSERST_BITS(TIMER2->TIMx_CCER,13,3,Type);
			break;
		}
	}
		break;

	case TIMER3_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1 :
			INSERST_BITS(TIMER3->TIMx_CCER,1,3,Type);
			break;
		case CHANNEL_2 :
			INSERST_BITS(TIMER3->TIMx_CCER,5,3,Type);
			break;
		case CHANNEL_3 :
			INSERST_BITS(TIMER3->TIMx_CCER,9,3,Type);
			break;
		case CHANNEL_4 :
			INSERST_BITS(TIMER3->TIMx_CCER,13,3,Type);
			break;
		}
	}
		break;

	case TIMER4_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1 :
			INSERST_BITS(TIMER4->TIMx_CCER,1,3,Type);
			break;
		case CHANNEL_2 :
			INSERST_BITS(TIMER4->TIMx_CCER,5,3,Type);
			break;
		case CHANNEL_3 :
			INSERST_BITS(TIMER4->TIMx_CCER,9,3,Type);
			break;
		case CHANNEL_4 :
			INSERST_BITS(TIMER4->TIMx_CCER,13,3,Type);
			break;
		}
	}
		break;

	case TIMER5_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1 :
			INSERST_BITS(TIMER5->TIMx_CCER,1,3,Type);
			break;
		case CHANNEL_2 :
			INSERST_BITS(TIMER5->TIMx_CCER,5,3,Type);
			break;
		case CHANNEL_3 :
			INSERST_BITS(TIMER5->TIMx_CCER,9,3,Type);
			break;
		case CHANNEL_4 :
			INSERST_BITS(TIMER5->TIMx_CCER,13,3,Type);
			break;
		}
	}
		break;
	case TIMER9_Selected :
	{
		switch(TIMER_Config_St->SET_Icu_Channel)
		{
		case CHANNEL_1 :
			INSERST_BITS(TIMER9->TIMx_CCER,1,3,Type);
			break;
		case CHANNEL_2 :
			INSERST_BITS(TIMER9->TIMx_CCER,5,3,Type);
			break;
		}
	}
		break;
	default :
		// return -1 if the number of timer doesn't match one of 2,3,4,5
		state = -1;
		return state;
		break;
	}


	 return state;
}





void TIM1_CC_IRQHandler(void)
{
	uint8 State;

	State = GET_BIT(TIMER1->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER1->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER1->TIMx_SR,CC1IF);
	CLEAR_BIT(TIMER1->TIMx_SR,CC2IF);
	CLEAR_BIT(TIMER1->TIMx_SR,CC3IF);
	CLEAR_BIT(TIMER1->TIMx_SR,CC4IF);
	if(State)
	{
		// CLEAR THE INTERRUPT FLAG
		CLEAR_BIT(TIMER1->TIMx_SR,TIM_SR_UIF);
	}

	if(TIMER_Call_Back[4] != 0)
	{
		TIMER_Call_Back[4]();
	}
}

void TIM2_IRQHandler(void)
{
	uint8 State;

	State = GET_BIT(TIMER2->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER2->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER2->TIMx_SR,CC1IF);
	CLEAR_BIT(TIMER2->TIMx_SR,CC2IF);
	CLEAR_BIT(TIMER2->TIMx_SR,CC3IF);
	CLEAR_BIT(TIMER2->TIMx_SR,CC4IF);
	if(State)
	{
		// CLEAR THE INTERRUPT FLAG
		CLEAR_BIT(TIMER2->TIMx_SR,TIM_SR_UIF);
	}

	if(TIMER_Call_Back[0] != 0)
	{
		TIMER_Call_Back[0]();
	}
}




void TIM3_IRQHandler(void)
{
	uint8 State;

	State = GET_BIT(TIMER3->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER3->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER3->TIMx_SR,CC1IF);
	CLEAR_BIT(TIMER3->TIMx_SR,CC2IF);
	CLEAR_BIT(TIMER3->TIMx_SR,CC3IF);
	CLEAR_BIT(TIMER3->TIMx_SR,CC4IF);

	if(State)
	{
		// CLEAR THE INTERRUPT FLAG
		CLEAR_BIT(TIMER3->TIMx_SR,TIM_SR_UIF);
	}

	if(TIMER_Call_Back[1] != 0)
	{
		TIMER_Call_Back[1]();
	}
}



void TIM4_IRQHandler(void)
{
	uint8 State;

	State = GET_BIT(TIMER4->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER4->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER4->TIMx_SR,CC1IF);
	CLEAR_BIT(TIMER4->TIMx_SR,CC2IF);
	CLEAR_BIT(TIMER4->TIMx_SR,CC3IF);
	CLEAR_BIT(TIMER4->TIMx_SR,CC4IF);


	if(State)
	{
		// CLEAR THE INTERRUPT FLAG
		CLEAR_BIT(TIMER4->TIMx_SR,TIM_SR_UIF);
	}

	if(TIMER_Call_Back[2] != 0)
	{
		TIMER_Call_Back[2]();
	}
}



void TIM5_IRQHandler(void)
{
	uint8 State;

	State = GET_BIT(TIMER5->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER5->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER5->TIMx_SR,CC1IF);
	CLEAR_BIT(TIMER5->TIMx_SR,CC2IF);
	CLEAR_BIT(TIMER5->TIMx_SR,CC3IF);
	CLEAR_BIT(TIMER5->TIMx_SR,CC4IF);

	if(State)
	{
		// CLEAR THE INTERRUPT FLAG
		CLEAR_BIT(TIMER5->TIMx_SR,TIM_SR_UIF);
	}

	if(TIMER_Call_Back[3] != 0)
	{
		TIMER_Call_Back[3]();
	}
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
	uint8 State;

	State = GET_BIT(TIMER9->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER9->TIMx_SR,TIM_SR_UIF);
	CLEAR_BIT(TIMER9->TIMx_SR,CC1IF);
	CLEAR_BIT(TIMER9->TIMx_SR,CC2IF);
	if(State)
	{
		// CLEAR THE INTERRUPT FLAG
		CLEAR_BIT(TIMER9->TIMx_SR,TIM_SR_UIF);
	}

	if(TIMER_Call_Back[5] != 0)
	{
		TIMER_Call_Back[5]();
	}
}




