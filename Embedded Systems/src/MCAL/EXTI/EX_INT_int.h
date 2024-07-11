/*
 * EX_INT_int.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Sabet & Mamdoh
 *      version 0.01
 */

#ifndef MCAL_EXTI_EX_INT_INT_H_
#define MCAL_EXTI_EX_INT_INT_H_
#include "../../lip/std_types.h"

typedef enum
{
	Rising_trigger,
	Falling_trigger,
	On_change_trigger
}EXI_Trigger_enum;

typedef enum
{
	EX_INT_PORTA,
	EX_INT_PORTB,
	EX_INT_PORTC
}PORT_enum;




enum
{
	EXTI_LINE_0,
	EXTI_LINE_1,
	EXTI_LINE_2,
	EXTI_LINE_3,
	EXTI_LINE_4,
	EXTI_LINE_5,
	EXTI_LINE_6,
	EXTI_LINE_7,
	EXTI_LINE_8,
	EXTI_LINE_9,
	EXTI_LINE_10,
	EXTI_LINE_11,
	EXTI_LINE_12,
	EXTI_LINE_13,
	EXTI_LINE_14,
	EXTI_LINE_15,


};


void EXTI_Enable_Line(uint8 PIN_line_num ,EXI_Trigger_enum trigger_mode ,PORT_enum port);
void EXTI_Disable_Line(uint8 PIN_line_num);
void EXTI_Set_Trigger(uint8 PIN_line_num ,EXI_Trigger_enum trigger_mode);
void EXTI_Generate_Sw_Int(uint8 PIN_line_num );
uint8 EXTI_Read_Trigger_Flag(uint8 PIN_line_num);
void EXTI_Clear_Flag(uint8 PIN_line_num);

/*********************CALL_BACK*********************/
void EXTI_Set_Call_Back(void (*ptr1)(void), uint8 interrupt_pin);


#endif /* MCAL_EXTI_EX_INT_INT_H_ */
