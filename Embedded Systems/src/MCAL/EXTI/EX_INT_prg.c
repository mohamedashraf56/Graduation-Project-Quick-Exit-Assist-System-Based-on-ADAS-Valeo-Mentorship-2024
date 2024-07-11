/*
 * EX_INT_prg.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Sabet & Mamdoh
 *      version 0.01
 */
#include "../../lip/common_macros.h"
#include "../../lip/std_types.h"
#include "../EXTI/EX_INT_cfg.h"
#include "../EXTI/EX_INT_int.h"
#include "../EXTI/EX_INT_prv.h"

static void (*volatile EXT_INTERRUPT_CB[7])(void) = { NULL_PTR };   //note ARRAY of 7 element look at data sheet we just have 7 ISR for EXI


/* ********************************************************************
 * Name     : EXTI_Enable_Line
 * function : Enable interrupt on specific line & sets its trigger
 * Return   : NOTHING
 * input1   : PORTA , PORTB , PORTC, from EXTI_int.h
 * input2   : EXTI_LINE_0 , EXTI_LINE_2 .... EXT  from EXTI_int.h
 * input3   : Rising_trigger , Falling_trigger ,On_change_trigger
 ***********************************************************************/

void EXTI_Enable_Line(uint8 PIN_line_num ,EXI_Trigger_enum trigger_mode ,PORT_enum port)
{
	// to enable interrupt on a specific line
	if (PIN_line_num<16  )
	{

		SET_BIT(EX_INT->IMR,PIN_line_num);   // enable line

	}
	else
	{
		// wronge configuration
	}
	INSERST_BITS(SYSCFG->EXTICR[PIN_line_num/4],(PIN_line_num%4)*4 ,  4 , port);     // to implement the port                    /*           arr[line/4]              start bit to change is (lin%4 *4) */

	if (PIN_line_num<16 && trigger_mode<3 )
	{

		SET_BIT(EX_INT->IMR,PIN_line_num);   // enable line

		switch (trigger_mode) {
		case Rising_trigger:
			SET_BIT(EX_INT->RTSR,PIN_line_num);
			CLEAR_BIT(EX_INT->FTSR,PIN_line_num);


			break;

		case Falling_trigger:
			SET_BIT(EX_INT->FTSR,PIN_line_num);
			CLEAR_BIT(EX_INT->RTSR,PIN_line_num);

			break;

		case On_change_trigger:
			SET_BIT(EX_INT->RTSR,PIN_line_num);
			SET_BIT(EX_INT->FTSR,PIN_line_num);
			break;
		default:
			break;
		}
	}

}


/******************************************************************************
*Function: EXTI_Disable_Line
*I/P Parameters: PIN_line_num  ,
*Returns:it returns no thing
*Desc:This Function disables the external interrupt for specific pin
******************************************************************************/



void EXTI_Disable_Line(uint8 PIN_line_num)
{

	if (PIN_line_num<16  )
	{

		CLEAR_BIT(EX_INT->IMR,PIN_line_num);   // disables line

	}

}

/* ********************************************************************
 * Name     : EXTI_Set_Trigger
 * function : Enable interrupt on specific line & sets its trigger
 * Return   : NOTHING
 * input1   : PORTA , PORTB , PORTC, from EXTI_int.h
 * input2   : EXTI_LINE_0 , EXTI_LINE_2 .... EXT  from EXTI_int.h
 * input3   : Rising_trigger , Falling_trigger ,On_change_trigger
 ***********************************************************************/
void EXTI_Set_Trigger(uint8 PIN_line_num ,EXI_Trigger_enum trigger_mode)
{

	if (trigger_mode<3  && PIN_line_num<16   ) // trigger_mode to be sure that mode not out of (falling , rising ,on change)
	{

		switch (trigger_mode) {
		case Rising_trigger:
			SET_BIT(EX_INT->RTSR,PIN_line_num);
			CLEAR_BIT(EX_INT->FTSR,PIN_line_num);


			break;

		case Falling_trigger:
			SET_BIT(EX_INT->FTSR,PIN_line_num);
			CLEAR_BIT(EX_INT->RTSR,PIN_line_num);

			break;

		case On_change_trigger:
			SET_BIT(EX_INT->RTSR,PIN_line_num);
			SET_BIT(EX_INT->FTSR,PIN_line_num);
			break;
		default:
			break;
		}
	}

}

/******************************************************************************
*Function: EXTI_Generate_Sw_Int
*I/P Parameters: PIN_line_num
*Returns:it returns no thing
*Desc:This Function Generate software external interrupt for specific pin and 	trigger mode
*REQUIRED : Enables the external interrupt for this pin line in reg 'IMR'
******************************************************************************/


void EXTI_Generate_Sw_Int(uint8 PIN_line_num )
{
	SET_BIT(EX_INT->SWIER,PIN_line_num);
}

/******************************************************************************
*Function: EXTI_Generate_Sw_Int
*I/P Parameters: PIN_line_num
*Returns: it returns ('0' if No trigger request occurred  and , '1' if selected trigger request occurred)
*Desc:This Function return the flag value and check if trigger request occurred
*REQUIRED : Enables the external interrupt for this pin line in reg 'IMR'
******************************************************************************/

uint8 EXTI_Read_Trigger_Flag(uint8 PIN_line_num)
{
	uint8 flag_value;
	flag_value =GET_BIT(EX_INT->PR,PIN_line_num);     // copy the flag value
	SET_BIT(EX_INT->PR,PIN_line_num)		;                    // reset the flag by writing '1' on it
	return flag_value ;
}
/******************************************************************************
*Function: EXTI_Clear_Flag
*I/P Parameters: PIN_line_num
*Returns: it returns   Nothing
*Desc:This Function clear interrupt flag
******************************************************************************/

void EXTI_Clear_Flag(uint8 PIN_line_num)
{
	SET_BIT(EX_INT->PR,PIN_line_num)		;                    // reset the flag by writing '1' on it
}


/******************************************************************************
*Function: EXTI_Set_Call_Back
*I/P Parameters: pointer to function and the pin
*Returns: it returns   Nothing
*Desc:This Function setting the callback function
******************************************************************************/
void EXTI_Set_Call_Back(void (*ptr1)(void), uint8 interrupt_pin)
{

    if (EXT_INTERRUPT_CB[interrupt_pin] ==(NULL_PTR))
    {
    	switch(interrupt_pin)
    			{
    			case 0 :
    			case 1 :
    			case 2 :
    			case 3 :
    			case 4 :

    	                   			EXT_INTERRUPT_CB[interrupt_pin] = ptr1;


    			break;


    			case 5 :
    			case 6 :
    			case 7 :
    			case 8 :
    			case 9 :
    			                 	EXT_INTERRUPT_CB[5] = ptr1;

    				break;

    			case 10 :
    			case 11 :
    			case 12 :
    			case 13 :
    			case 14 :
    			case 15 :
    			              	EXT_INTERRUPT_CB[6] = ptr1;
    				break;

    			default :
    				break;


    			}
        // Assign the function pointer to the corresponding array element
    }
    else {
    	// do nothing

    }
}
/****************************************************************************************************************************************************/

/********************************************************************************************************************************************/
void EXTI0_IRQHandler(void)
{
	if (EXT_INTERRUPT_CB[0] !=NULL_PTR )
	{
		EXT_INTERRUPT_CB[0]() ;                                //    call back notify
		SET_BIT(EX_INT->PR,EXTI_LINE_0)		;  //clearing the flag by setting '1' **
	}
}


void EXTI1_IRQHandler(void)
{
    if (EXT_INTERRUPT_CB[1] != NULL_PTR)
    {
    	EXT_INTERRUPT_CB[1]();                                   //    call back notify
		SET_BIT(EX_INT->PR,EXTI_LINE_1)		;     //clearing the flag by setting '1' **
    }
}

void EXTI2_IRQHandler(void)
{
    if (EXT_INTERRUPT_CB[2] != NULL_PTR)
    {
    	EXT_INTERRUPT_CB[2]();                             //    call back notify
		SET_BIT(EX_INT->PR,EXTI_LINE_2)		;   //clearing the flag by setting '1' **
    }
}


void EXTI3_IRQHandler(void)
{
    if (EXT_INTERRUPT_CB[3] != NULL_PTR)
    {
    	EXT_INTERRUPT_CB[3]();                                //    call back notify
		SET_BIT(EX_INT->PR,EXTI_LINE_3)		;   //clearing the flag by setting '1' **
    }
}

void EXTI4_IRQHandler(void)
{
    if (EXT_INTERRUPT_CB[4] != NULL_PTR)
    {
    	EXT_INTERRUPT_CB[4]();                                //    call back notify
		SET_BIT(EX_INT->PR,EXTI_LINE_4)		;    //clearing the flag by setting '1' **
    }
}


void EXTI9_5_IRQHandler(void)
{
    if (EXT_INTERRUPT_CB[5] != NULL_PTR)
    {
    	EXT_INTERRUPT_CB[5]();                                              //    call back notify
    	INSERST_BITS(EX_INT->PR,5,5,0b11111);             //clearing the flag by setting '1' **
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXT_INTERRUPT_CB[6] != NULL_PTR)
    {
    	EXT_INTERRUPT_CB[6]();                                                //    call back notify
    	INSERST_BITS(EX_INT->PR,10,5,0b11111);             //clearing the flag by setting '1' **


    }
}


/***************************************************************************************************************************/

