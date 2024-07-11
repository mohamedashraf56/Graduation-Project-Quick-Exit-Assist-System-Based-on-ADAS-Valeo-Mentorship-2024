/*
 * ULTRASONIC.c
 *
 *  Created on: Jan 1, 2024
 *      Author: Mamdouh & Sabet
 *
 *      v1.0
 *      Updated 2/2/2024 by Mamdouh
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"


#include "../../MCAL/GPIO/GPIO_int_.h"
#include "../../MCAL/TIMER/TIMER_int.h"
#include "ULTRASONIC.h"


// assume there are ability to add 10 ultrasonic sensors
// Example .... Counter[2] have the value of timer2 counter
// which implemented in the Ultrasonic_timer2 which called in TIM2 Handler
uint32 Counter_Value[10] = {0};


// timer configuration to work with icu
// if u want more details check timer.h (config struct paramters)
TIMER_Init_Config_St Timer2 = {
		2,
		// please chech the system freq and make calculation to make
		// 1 tick equal MICROs
		//25 represents psc
		25,
		// set autoreload for timer 2 (timer compare value)
		50000,
		// init the icu for the timer 2 to detect the both edges
		ICU_Both,
		// this is to configure the channel in ULTRASONIC.h
		SELCTED_Channel_Timer_2,
		/*
		  this function will be the callback func for
		  Timer2 handler to calulate the Distance
		*/
		Ultrasonic_Timer2_Call_Back
};

TIMER_Init_Config_St Timer3 = {
		3,
		25,
		50000,
		ICU_Both,
		SELCTED_Channel_Timer_3,
		Ultrasonic_Timer3_Call_Back
};


TIMER_Init_Config_St Timer4 = {
		4,
		25,
		50000,
		ICU_Both,
		SELCTED_Channel_Timer_4,
		Ultrasonic_Timer4_Call_Back
};

TIMER_Init_Config_St Timer5 = {
		5,
		25,
		50000,
		ICU_Both,
		SELCTED_Channel_Timer_5,
		Ultrasonic_Timer5_Call_Back
};


TIMER_Init_Config_St Timer1 = {
		1,
		25,
		50000,
		ICU_Both,
		SELCTED_Channel_Timer_1,
		Ultrasonic_Timer1_Call_Back
};


TIMER_Init_Config_St Timer9 = {
		9,
		25,
		50000,
		ICU_Both,
		SELCTED_Channel_Timer_9,
		Ultrasonic_Timer9_Call_Back
};


/* ********************************************************************
 * Name     : US_Init
 * function :
 * Enable Clock on the selected timer
 * Enable interrupt on the selected timer from NVIC
 * configure prescaler for the timer
 * Set Autoreload Register
 * stop the timer
 * Configure  the timer to work as ICU and Chossing channel
 * Set call back function to Calulate the Echo time Examble (Ultrasonic_timer2) func
 * Configure pin as a Alterantive function
 * Configure pin as a output pin to send trigger
 *
 * Return   : State
 * input1   : Pointer to sturct type -> (US_Get_Distance)
 * // Note that timer 6 & 7 are only for Dac and we cant use it here
   // Note that choosing the channel (Echo Pin) not implemented yet
 ***********************************************************************/
// test 1
sint8 US_Init(Ultrasonic_Cfg_St * US_Conif_Struct)
{
	sint8 State = US_Init_Not_Done;

	switch (US_Conif_Struct->Seleted_Timer)
	{
	case TIMER2_SELECTED :
	{
		TIMER_Init(&Timer2);
		TIMER_Set_Psc(&Timer2);
		TIMER_Set_Auto_Reload(&Timer2);
		TIMER_Set_Call_Back(&Timer2);
		TIMER_Start_Stop(&Timer2,TIMER_Stop);
		TIMER_Mode_ICU(&Timer2);
		GPIO_Set_Pin_Direction(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin, GPIO_MODE_ALTFUN);
		GPIO_Alternate_Function(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin, 1);
		GPIO_Set_Pin_Direction(US_Conif_Struct->Trig_Port, US_Conif_Struct->Trig_Pin, GPIO_MODE_OUTPUT);

		State = US_Init_Done;
		US_Conif_Struct->STATES_Prv[US_Idl_State] = State;
	}
		break;

	case TIMER3_SELECTED :
	{
		TIMER_Init(&Timer3);
		TIMER_Set_Psc(&Timer3);
		TIMER_Set_Auto_Reload(&Timer3);
		TIMER_Set_Call_Back(&Timer3);
		TIMER_Start_Stop(&Timer3,TIMER_Stop);
		TIMER_Mode_ICU(&Timer3);
		GPIO_Set_Pin_Direction(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin, GPIO_MODE_ALTFUN);
		// THIS IS AF CONFIGURATION FOR TIM3,,TIM5
		GPIO_Alternate_Function(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin,(0b0010));
		GPIO_Set_Pin_Direction(US_Conif_Struct->Trig_Port, US_Conif_Struct->Trig_Pin, GPIO_MODE_OUTPUT);

		State = US_Init_Done;
		US_Conif_Struct->STATES_Prv[US_Idl_State] = State;	}
		break;

	case TIMER1_SELECTED :
	{
		TIMER_Init(&Timer1);
		TIMER_Set_Psc(&Timer1);
		TIMER_Set_Auto_Reload(&Timer1);
		TIMER_Set_Call_Back(&Timer1);
		TIMER_Start_Stop(&Timer1,TIMER_Stop);
		TIMER_Mode_ICU(&Timer1);
		GPIO_Set_Pin_Direction(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin, GPIO_MODE_ALTFUN);
		GPIO_Alternate_Function(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin,(0b0001));
		GPIO_Set_Pin_Direction(US_Conif_Struct->Trig_Port, US_Conif_Struct->Trig_Pin, GPIO_MODE_OUTPUT);

		State = US_Init_Done;
		US_Conif_Struct->STATES_Prv[US_Idl_State] = State;
	}
		break;
	case TIMER5_SELECTED :
	{
		TIMER_Init(&Timer5);
		TIMER_Set_Psc(&Timer5);
		TIMER_Set_Auto_Reload(&Timer5);
		TIMER_Set_Call_Back(&Timer5);
		TIMER_Start_Stop(&Timer5,TIMER_Stop);
		TIMER_Mode_ICU(&Timer5);
		GPIO_Set_Pin_Direction(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin, GPIO_MODE_ALTFUN);
		GPIO_Alternate_Function(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin,(0b0010));
		GPIO_Set_Pin_Direction(US_Conif_Struct->Trig_Port, US_Conif_Struct->Trig_Pin, GPIO_MODE_OUTPUT);

		State = US_Init_Done;
		US_Conif_Struct->STATES_Prv[US_Idl_State] = State;
	}
		break;
	case TIMER9_SELECTED :
	{

		TIMER_Init(&Timer9);
		TIMER_Set_Psc(&Timer9);
		TIMER_Set_Auto_Reload(&Timer9);
		TIMER_Set_Call_Back(&Timer9);
		TIMER_Start_Stop(&Timer9,TIMER_Stop);
		TIMER_Mode_ICU(&Timer9);
		GPIO_Set_Pin_Direction(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin, GPIO_MODE_ALTFUN);
		GPIO_Alternate_Function(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin, (0b0011));
		GPIO_Set_Pin_Direction(US_Conif_Struct->Trig_Port, US_Conif_Struct->Trig_Pin, GPIO_MODE_OUTPUT);

		State = US_Init_Done;
		US_Conif_Struct->STATES_Prv[US_Idl_State] = State;

	}
		break;

	default :
		State = US_Init_Not_Done;
		US_Conif_Struct->STATES_Prv[US_Idl_State] = State;
		return State;
		break;
	}

	return State;
}



/* ********************************************************************
 * Name     : US_Get_Distance
 * function : Calculate the distance
 * Return   : The distance in CM
 * input1   : Pointer to sturct type -> (US_Get_Distance)
 ***********************************************************************/
uint32 US_Get_Distance(Ultrasonic_Cfg_St * US_Conif_Struct)
{
	uint8 State = US_Conif_Struct->STATES_Prv[US_Triggering_State];

	if(State == US_Triggering_Done)
	{
	uint32 Distance = 0;
	Distance = ((float)34000) * ((float)(Counter_Value[US_Conif_Struct->Seleted_Timer])/2000000);
	return Distance;
	}
	else
	{
		State = US_Triggering_Not_Done;
		US_Conif_Struct->STATES_Prv[US_Triggering_State] = State;
		return US_Triggering_Not_Done;
	}

	return State;
}




/* ********************************************************************
 * Name     : US_Set_Trigger
 * function : set a trigger to ultrasonic to send wave and receive the echo
 * Return   : NOTHING
 * input1   : Pointer to sturct type -> (US_Get_Distance)
 ***********************************************************************/
sint8 US_Set_Trigger(Ultrasonic_Cfg_St * US_Conif_Struct)
{
	sint8 State = US_Conif_Struct->STATES_Prv[US_Measuring_State];
	if( State == US_Measuring_Started )
	{
	DELAY_Micro(15);
	GPIO_Set_Pin_Value(US_Conif_Struct->Trig_Port, US_Conif_Struct->Trig_Pin, PIN_HIGH);
	DELAY_Micro(15);
	GPIO_Set_Pin_Value(US_Conif_Struct->Trig_Port, US_Conif_Struct->Trig_Pin, PIN_LOW);

	State = US_Triggering_Done;
	US_Conif_Struct->STATES_Prv[US_Triggering_State] = State;

	return State;
	}
	else
	{
		State = US_Measuring_Stoped;
		US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;
		return State;
	}
	return State;
}




sint8 US_Start(Ultrasonic_Cfg_St * US_Conif_Struct)
{
	sint8 State = US_Conif_Struct->STATES_Prv[US_Measuring_State];
	if(US_Conif_Struct->STATES_Prv[US_Idl_State] == US_Init_Done)
	{
		switch(US_Conif_Struct->Seleted_Timer)
		{
		case TIMER2_SELECTED :
		{
			TIMER_Start_Stop(&Timer2,TIMAR_Start);
			State = US_Measuring_Started;
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;
		}
		break ;
		case TIMER3_SELECTED :
		{
			TIMER_Start_Stop(&Timer3,TIMAR_Start);
			State = US_Measuring_Started;
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;
		}
		break ;
		case TIMER1_SELECTED :
		{
			TIMER_Start_Stop(&Timer1,TIMAR_Start);
			State = US_Measuring_Started;
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;
		}
		break ;
		case TIMER5_SELECTED :
		{
			TIMER_Start_Stop(&Timer5,TIMAR_Start);
			State = US_Measuring_Started;
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;
		}
		break ;
		case TIMER9_SELECTED :
		{

			TIMER_Start_Stop(&Timer9,TIMAR_Start);
			State = US_Measuring_Started;
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;

		}
		break ;

		default :
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = US_Measuring_Stoped;
			// state wrong will implemented
			break;
		}
	}
	else
	{
		State = US_Init_Not_Done;
		US_Conif_Struct->STATES_Prv[US_Idl_State] = State;
	}
	return State;
}



sint8 US_Stop(Ultrasonic_Cfg_St * US_Conif_Struct)
{
	sint8 State = US_Conif_Struct->STATES_Prv[US_Measuring_State];
	if(US_Conif_Struct->STATES_Prv[US_Idl_State] == US_Init_Done)
	{
		switch(US_Conif_Struct->Seleted_Timer)
		{
		case TIMER2_SELECTED :
		{
			TIMER_Start_Stop(&Timer2,TIMER_Stop);
			State = US_Measuring_Stoped;
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;
		}
		break ;
		case TIMER3_SELECTED :
		{
			TIMER_Start_Stop(&Timer3,TIMER_Stop);
			State = US_Measuring_Stoped;
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;
		}
		break ;
		case TIMER1_SELECTED :
		{
			TIMER_Start_Stop(&Timer1,TIMER_Stop);
			State = US_Measuring_Stoped;
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;
		}
		break ;
		case TIMER5_SELECTED :
		{
			TIMER_Start_Stop(&Timer5,TIMER_Stop);
			State = US_Measuring_Stoped;
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;
		}
		break ;
		case TIMER9_SELECTED :
		{

			TIMER_Start_Stop(&Timer9,TIMER_Stop);
			State = US_Measuring_Stoped;
			US_Conif_Struct->STATES_Prv[US_Measuring_State] = State;

		}
		break ;
		default :
			// state wrong will implemented
			break;

		}
	}
	else
	{
		State = US_Init_Not_Done;
		US_Conif_Struct->STATES_Prv[US_Idl_State] = State;
	}

	return State;
}













void Ultrasonic_Timer1_Call_Back(void)
{
	static uint8 state = 0;

	switch (state)
	{
	case 0 :
		TIMER_Clear_Counter(&Timer1);
		// configure the icu to capture the failing edge
		TIMER_Set_ICU_Edges(&Timer1,ICU_Failing);
		state = 1;
		break;
	case 1 :
		Counter_Value[1] = TIMER_ICU_Result(&Timer1);
		// configure the icu to capture the Rising edge
		TIMER_Set_ICU_Edges(&Timer1,ICU_Rising);
		state = 0;
		break;

	default :
		// wrong configuration
		break;
	}
}


// this is a handlerS for ICU_TIM2 INTERRUPT
void Ultrasonic_Timer2_Call_Back(void)
{
	static uint8 state = 0;

	switch (state)
	{
	case 0 :
		TIMER_Clear_Counter(&Timer2);
		// configure the icu to capture the failing edge
		TIMER_Set_ICU_Edges(&Timer2,ICU_Failing);
		state = 1;
		break;
	case 1 :
		Counter_Value[2] = TIMER_ICU_Result(&Timer2);
		// configure the icu to capture the Rising edge
		TIMER_Set_ICU_Edges(&Timer2,ICU_Rising);
		state = 0;
		break;

	default :
		// wrong configuration
		break;
	}
}

void Ultrasonic_Timer3_Call_Back(void)
{
	static uint8 state = 0;

	switch (state)
	{
	case 0 :
		TIMER_Clear_Counter(&Timer3);
		// configure the icu to capture the failing edge
		TIMER_Set_ICU_Edges(&Timer3,ICU_Failing);
		state = 1;
		break;
	case 1 :
		Counter_Value[3] = TIMER_ICU_Result(&Timer3);
		// configure the icu to capture the Rising edge
		TIMER_Set_ICU_Edges(&Timer3,ICU_Rising);
		state = 0;
		break;

	default :
		// wrong configuration
		break;
	}
}



void Ultrasonic_Timer4_Call_Back(void)
{
	static uint8 state = 0;

	switch (state)
	{
	case 0 :
		TIMER_Clear_Counter(&Timer4);
		// configure the icu to capture the failing edge
		TIMER_Set_ICU_Edges(&Timer4,ICU_Failing);
		state = 1;
		break;
	case 1 :
		Counter_Value[4] = TIMER_ICU_Result(&Timer4);
		// configure the icu to capture the Rising edge
		TIMER_Set_ICU_Edges(&Timer4,ICU_Rising);
		state = 0;
		break;

	default :
		// wrong configuration
		break;
	}
}

void Ultrasonic_Timer5_Call_Back(void)
{
	static uint8 state = 0;

	switch (state)
	{
	case 0 :
		TIMER_Clear_Counter(&Timer5);
		// configure the icu to capture the failing edge
		TIMER_Set_ICU_Edges(&Timer5,ICU_Failing);
		state = 1;
		break;
	case 1 :
		Counter_Value[5] = TIMER_ICU_Result(&Timer5);
		// configure the icu to capture the Rising edge
		TIMER_Set_ICU_Edges(&Timer5,ICU_Rising);
		state = 0;
		break;

	default :
		// wrong configuration
		break;
	}
}




void Ultrasonic_Timer9_Call_Back(void)
{
	static uint8 state = 0;

	switch (state)
	{
	case 0 :
		TIMER_Clear_Counter(&Timer9);
		// configure the icu to capture the failing edge
		TIMER_Set_ICU_Edges(&Timer9,ICU_Failing);
		state = 1;
		break;
	case 1 :
		Counter_Value[9] = TIMER_ICU_Result(&Timer9);
		// configure the icu to capture the Rising edge
		TIMER_Set_ICU_Edges(&Timer9,ICU_Rising);
		state = 0;
		break;

	default :
		// wrong configuration
		break;
	}
}



void DELAY_Micro(uint32 duration_in_microseconds)
{
	//
    // Calculate the number of cycles required for the given duration
    uint32 cycles = (SYSTEM_Freq / 1000000) * duration_in_microseconds ;
    //to avoid the context switch time delay
    cycles = cycles /5;
    // Execute the delay loop
    for (uint32 i = 0; i < cycles; i++)
    {
        // Do nothing (NOP instruction)
        __asm__("nop");
    }
}


