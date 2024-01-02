/*
 * EXTI_prg.c
 *
 *  Created on: Dec 10, 2023
 *      Author: Mamdouh
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"

#include "EXTI_int.h"
#include "EXTI_prv.h"
#include "EXTI_cfg.h"

// creating an array of pointers to handlers to callback functions
static void (*EXTI_LINE0_CallBack[7])(void) = {0,0,0,0,0,0,0};

void MEXTI_vInit(void)
{
	/* Clear all flags by writing 1 on all bits in PR register */
	EXTI->PR = 0XFFFFFFFF;
}



/* ********************************************************************
 * Name     : MEXTI_vEnable_Line
 * function : Enable interrupt on specific line & sets its trigger
 * Return   : NOTHING
 * input1   : PORTA , PORTB , PORTC, from EXTI_int.h
 * input2   : EXTI0_ID , EXTI9_ID .... EXT  from EXTI_int.h
 * input3   : Rising_Edge_EN , Failing_Edge_EN ,OnChange_Edge_EN
 ***********************************************************************/

void MEXTI_vEnable_Line(uint8 PORTID ,uint8 Line_Id , uint8 Trigger)
{
	uint8 EXTICR_id = 0;
	if((Line_Id < 16))
	{
		EXTICR_id = 0;
	}
	else if ((Line_Id >=4 ) && (Line_Id <= 7))
	{
		EXTICR_id = 1;
	}
	else if ((Line_Id >=8 ) && (Line_Id <= 11))
	{
		EXTICR_id = 2;
	}
	else if ((Line_Id >=12 ) && (Line_Id <= 15))
	{
		EXTICR_id = 3;
	}
	else
	{
		return ;
	}

	// to enable interrupt on a specific line
	if((Line_Id < 16))
	{
	     SET_BIT((EXTI->IMR),Line_Id); // to enable interrupt on a specific line
	}
	else
	{
		return;
	}


	// EXTICR_id indicate to register from 1 to 4 in SESCFG peripheral
	// (LINE_id)%4*4 indicate to reach the location of the first bit in
	// the register to insert the value
	// ( four one ) the range which cleared to insert in
	switch (PORTID)
	{
	case PORTA :
		INSERST_BITS(SYSCFG->EXTICR[EXTICR_id],0,four_one,((Line_Id % 4)*4));
		break;

	case PORTB :
		INSERST_BITS(SYSCFG->EXTICR[EXTICR_id],1,four_one,((Line_Id % 4)*4));
		break ;

	case PORTC :
		INSERST_BITS(SYSCFG->EXTICR[EXTICR_id],2,four_one,((Line_Id % 4)*4));
		break ;

	default :
		// wrong configuration
		break;
	}

	// TO Choose the trigger type
	switch (Trigger)
	{
	case Rising_Edge_EN :
		SET_BIT(EXTI->RTSR,Line_Id);
		CLEAR_BIT(EXTI->FTSR,Line_Id);
		break;

	case Failing_Edge_EN :
		SET_BIT(EXTI->FTSR,Line_Id);
		CLEAR_BIT(EXTI->RTSR,Line_Id);
		break;

	case OnChange_Edge_EN :
		SET_BIT(EXTI->RTSR,Line_Id);
		SET_BIT(EXTI->FTSR,Line_Id);
		break;
	default :
		// wrong configuration
		break;
	}

}
/* ********************************************************************
 * Name :MEXTI_vDisable_Line
 * function : Disable interrupt on specific line & sets its trigger
 * Return : NOTHING
 * input1 : EXTI0_ID , EXTI1_ID .... EXTI15_ID  from EXTI_int.h
 ***********************************************************************/

void MEXTI_vDisable_Line(uint8 Line_Id)
{
	if((Line_Id < 16))
		{
		    CLEAR_BIT(EXTI->IMR,Line_Id); // to Disable  interrupt on a specific line
		}
}

/* ********************************************************************
 * Name :MEXTI_vSoftware_Trigger
 * function : Generate a software interrupt or event
 * Return : NOTHING
 * input1 : EXTI0_ID , EXTI1_ID .... EXTI15_ID  from EXTI_int.h
 **********************************************************************/

void MEXTI_vSoftware_Trigger(uint8 Line_Id)
{
	if((Line_Id < 16))
	{
	     SET_BIT(EXTI->SWIER,Line_Id);
	}
}
/* ********************************************************************
 * Name :MEXTI_vSetTrigger
 * function : Set the type of Trigger will be detected
 * Return : NOTHING
 * input1 : EXTI0_ID , EXTI1_ID .... EXTI15_ID
 * input2 : Rising_Edge_EN , Failing_Edge_EN ,OnChange_Edge_EN
 **********************************************************************/

void MEXTI_vSetTrigger(uint8 Line_Id , uint8 Trigger)
{
	switch (Trigger)
	{
	case Rising_Edge_EN :
		SET_BIT(EXTI->RTSR,Line_Id);
		CLEAR_BIT(EXTI->FTSR,Line_Id);
		break;

	case Failing_Edge_EN :
		SET_BIT(EXTI->FTSR,Line_Id);
		CLEAR_BIT(EXTI->RTSR,Line_Id);
		break;

	case OnChange_Edge_EN :
		SET_BIT(EXTI->RTSR,Line_Id);
		SET_BIT(EXTI->FTSR,Line_Id);
		break;
	}
}

/* ********************************************************************
 * Name :MEXTI_vEvent_Enable
 * function : Enable Event on external interrupt to check the flag instead of isr
 * Return : NOTHING
 * input1 : EXTI0_ID , EXTI1_ID .... EXTI15_ID
 **********************************************************************/

void MEXTI_vEvent_Enable(uint8 Line_Id)
{
	if((Line_Id < 16))
	{
	     SET_BIT(EXTI->EMR,Line_Id);
	}
}



/* ********************************************************************
 * Name     : MEXTI_vSetCallBack
 * function : Copy the address of a function in main (app) to
 *          : the pointer to function which is called in ISR (Callback)
 * Return   : NOTHING
 * input1   : function address (name)
 * input2   : EXTI0_ID , EXTI9_ID .... EXT  from EXTI_int.h
 ***********************************************************************/
void MEXTI_vSetCallBack(void (*ptr)(void),uint8 Line_Id)
{
	switch (Line_Id)
	{
	case EXTI0_ID :
		EXTI_LINE0_CallBack[0] = ptr;
		break;
	case EXTI1_ID :
		EXTI_LINE0_CallBack[1] = ptr;
		break;
	case EXTI2_ID :
		EXTI_LINE0_CallBack[2] = ptr;
		break;
	case EXTI3_ID :
		EXTI_LINE0_CallBack[3] = ptr;
		break;
	case EXTI4_ID :
		EXTI_LINE0_CallBack[4] = ptr;
		break;
	case EXTI5_ID :
	case EXTI6_ID :
	case EXTI7_ID :
	case EXTI8_ID :
	case EXTI9_ID :
		EXTI_LINE0_CallBack[5] = ptr;
		break;
	case EXTI10_ID :
	case EXTI11_ID :
	case EXTI12_ID :
	case EXTI13_ID :
	case EXTI14_ID :
	case EXTI15_ID :
		EXTI_LINE0_CallBack[5] = ptr;
		break;
	default :
		// wrong configuration
		break;
	}
}







// ISR FOR EXTI0
void EXTI0_IRQHandler(void)
{
	if( EXTI_LINE0_CallBack[0] != 0)
	{
		EXTI_LINE0_CallBack[0]();
	}
	// CLEAR THE PENDING FLAG-
	SET_BIT(EXTI->PR,EXTI0_ID);
}

void EXTI1_IRQHandler(void)
{
	if( EXTI_LINE0_CallBack[1] != 0)
		{
			EXTI_LINE0_CallBack[1]();
		}
	// CLEAR THE PENDING FLAG-
	SET_BIT(EXTI->PR,EXTI1_ID);

}



void EXTI2_IRQHandler(void)
{
	if( EXTI_LINE0_CallBack[2] != 0)
		{
			EXTI_LINE0_CallBack[2]();
		}
	SET_BIT(EXTI->PR,EXTI2_ID);
}


void EXTI3_IRQHandler(void)
{
	if( EXTI_LINE0_CallBack[3] != 0)
		{
			EXTI_LINE0_CallBack[3]();
		}
	// CLEAR THE PENDING FLAG
	SET_BIT(EXTI->PR,EXTI3_ID);
}

void EXTI4_IRQHandler(void)
{
	if( EXTI_LINE0_CallBack[4] != 0)
		{
			EXTI_LINE0_CallBack[4]();
		}
	// CLEAR THE PENDING FLAG
	SET_BIT(EXTI->PR,EXTI4_ID);
}


void EXTI9_5_IRQHandler(void)
{
	if( EXTI_LINE0_CallBack[5] != 0)
		{
			EXTI_LINE0_CallBack[5]();
		}
	// CLEAR THE PENDING FLAG
	SET_BIT(EXTI->PR,EXTI5_ID);
	SET_BIT(EXTI->PR,EXTI6_ID);
	SET_BIT(EXTI->PR,EXTI7_ID);
	SET_BIT(EXTI->PR,EXTI8_ID);
	SET_BIT(EXTI->PR,EXTI9_ID);

}



void EXTI15_10_IRQHandler(void)
{
	if( EXTI_LINE0_CallBack[6] != 0)
		{
			EXTI_LINE0_CallBack[6]();
		}
	// CLEAR THE PENDING FLAG
	SET_BIT(EXTI->PR,EXTI10_ID);
	SET_BIT(EXTI->PR,EXTI11_ID);
	SET_BIT(EXTI->PR,EXTI12_ID);
	SET_BIT(EXTI->PR,EXTI13_ID);
	SET_BIT(EXTI->PR,EXTI14_ID);
	SET_BIT(EXTI->PR,EXTI15_ID);

}
