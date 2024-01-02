/*
 * ULTRASONIC.c
 *
 *  Created on: Jan 1, 2024
 *      Author: Mamdouh
 *
 *      v0.0 : need to make more configurations on choosing channels
 *           : and implement all the  timers in US_Init function
 *           : and configure choosing alternative function line 102
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"

#include "../../MCAL/RCC/RCC_int.h"
#include "../../MCAL/NVIC/NVIC_int.h"

#include "../../MCAL/SYSTICK/SYSTICK_int.h"
#include "../../MCAL/GPIO/GPIO_int_.h"
#include "../../MCAL/TIM2/TIM2_int.h"
#include "ULTRASONIC.h"

// assume there are ability to add 10 ultrasonic sensors
// Example .... Counter[2] have the value of timer2 counter
// which implemented in the Ultrasonic_timer2 which called in TIM2 Handler
uint32 Counter_Value[10] = {0};




/* ********************************************************************
 * Name     : US_Get_Distance
 * function : Calculate the distance
 * Return   : The distance in CM
 * input1   : Pointer to sturct type -> (US_Get_Distance)
 ***********************************************************************/
uint32 US_Get_Distance(Ultrasonic_Init * US_Conif_Struct)
{
	uint32 Distance = 0;
	Distance = (34000) * ((float)(Counter_Value[US_Conif_Struct->Seleted_Timer])/2000);
	return Distance;
}




/* ********************************************************************
 * Name     : US_Set_Trigger
 * function : set a trigger to ultrasonic to send wave and receive the echo
 * Return   : NOTHING
 * input1   : Pointer to sturct type -> (US_Get_Distance)
 ***********************************************************************/
void US_Set_Trigger(Ultrasonic_Init * US_Conif_Struct)
{
	MSTK_vSetBusWait(1600);
	GPIO_SetPin_Value(US_Conif_Struct->Trig_Port, US_Conif_Struct->Trig_Pin, PIN_HIGH);
	MSTK_vSetBusWait(1600);
	GPIO_SetPin_Value(US_Conif_Struct->Trig_Port, US_Conif_Struct->Trig_Pin, PIN_LOW);
}




/* ********************************************************************
 * Name     : US_Init
 * function :
 * Enable Clock on the selected timer
 * Enable interrupt on the selected timer from NVIC
 * configure prescaler for the timer -> need edit
 * Set Autoreload Register
 * Start the timer
 * Configure  the timer to work as ICU and Chossing channel -> need edit
 * Set call back function to Calulate the Echo time Examble (Ultrasonic_timer2) func
 * Configure pin as a Alterantive function -> need edit
 * Configure pin as a output pin to send trigger
 *
 * Return   : State
 * input1   : Pointer to sturct type -> (US_Get_Distance)
 * // Note that timer 6 & 7 are only for Dac and we cant use it here
   // Note that choosing the channel (Echo Pin) not implemented yet
 ***********************************************************************/
// test 1
uint8 US_Init(Ultrasonic_Init * US_Conif_Struct)
{
	uint8 state = 0;

	switch (US_Conif_Struct->Seleted_Timer)
	{
	case US_TIMER1_SELECTED :

		break;

	case US_TIMER2_SELECTED :
	{
		state = 1;
		 // enable clock on timer2
		 MRCC_vEnableClock(RCC_APB1,TIM2_EN);
		 Nvic_En_Interrupt(TIM2);
		 //25/16 in rcc.c
		 // 1562 to make 1 tick equal 1ms
		 TIMER2_Set_PSC(1562);
		 TIMER2_Set_Auto_Reload(50000);
		 TIMER2_Start_Stop(TIMAR2_Start);


		 // here in (TIMER2_ICU) i will make it more configure to choose channels (pins)
		 TIMER2_ICU();


		 TIMER2_Set_Call_Back(Ultrasonic_timer2);

		 // FOR ECHO PIN
		 GPIO_SetPin_Direction(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin, GPIO_MODE_ALTFUN);
		 // 1 reperesent to AF1 for timer2 // look register des 151
		 GPIO_LAlternate_Function(US_Conif_Struct->Echo_Port,US_Conif_Struct->Echo_Pin, 1);

		 // FOR TRIGGER PIN
		 GPIO_SetPin_Direction(US_Conif_Struct->Trig_Port, US_Conif_Struct->Trig_Pin, GPIO_MODE_OUTPUT);
		 GPIO_SetOutput_Speed(US_Conif_Struct->Trig_Port,  US_Conif_Struct->Trig_Pin, LowSpeed);
		 GPIO_SetOutput_Type(US_Conif_Struct->Trig_Port,  US_Conif_Struct->Trig_Pin, PUSH_PULL);
	}
		break;

	case US_TIMER3_SELECTED :

		break;
	case US_TIMER4_SELECTED :

		break;

	case US_TIMER5_SELECTED :

		break;

	case US_TIMER8_SELECTED :

		break;
	case US_TIMER9_SELECTED :

		break;

	case US_TIMER10_SELECTED :

		break;

	case US_TIMER11_SELECTED :

		break;

	}


	return state;
}



uint8 US_De_Init(Ultrasonic_Init * US_Conif_Struct)
{

	return 0;
}







// this is a handler for ICU_TIM2 INTERRUPT
void Ultrasonic_timer2(void)
{
	static uint8 state = 0;

	switch (state)
	{
	case 0 :
		TIMER2_Clear_Counter();
		// configure the icu to capture the failing edge
		TIMER2_ICU_Edges(ICU_Failing);
		state = 1;
		break;
	case 1 :
		Counter_Value[2] = TIMER2_ICU_Result();
		// configure the icu to capture the Rising edge
		TIMER2_ICU_Edges(ICU_Rising);
		state = 0;
		break;

	default :
		// wrong configuration
		break;
	}
}





