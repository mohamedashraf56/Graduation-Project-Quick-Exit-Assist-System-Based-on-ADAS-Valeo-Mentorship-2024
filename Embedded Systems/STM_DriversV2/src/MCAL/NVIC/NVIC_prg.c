/*
 * NVIC_prg.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Sabet & Mamdouh
 *        version  0.01
 */
#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "NVIC_cfg.h"
#include "NVIC_int.h"
#include "NVIC_prv.h"

/******************************************************************************
*Function: NVIC_En_Interrupt	                         			          *
*I/P Parameters: interrupt_num             								      *
*Returns:it returns no thing	                            				  *
*Desc:This Function Enables the INT of the peripheral in NVIC		          *
******************************************************************************/

void NVIC_En_Interrupt(interrupt_ID_enum interrupt_num)
{
	SET_BIT(NVIC->ISER[interrupt_num/32],interrupt_num%32);
}


/******************************************************************************
*Function: NVIC_Dis_Interrupt
*I/P Parameters: interrupt_num
*Returns:it returns no thing
*Desc:This Function Disables the INT of the peripheral in NVIC
******************************************************************************/

void NVIC_Dis_Interrupt (interrupt_ID_enum interrupt_num)
{
	SET_BIT(NVIC->ICER[interrupt_num/32],interrupt_num%32);
}

/******************************************************************************
*Function: NVIC_Set_Pending_Flag
*I/P Parameters: interrupt_num ID
*Returns:it returns no thing
*Desc:This Function Sets pending flag of Peripheral
******************************************************************************/


void NVIC_Set_Pending_Flag (interrupt_ID_enum interrupt_num)
{
	SET_BIT(NVIC->ISPR[interrupt_num/32],interrupt_num%32);
}



/******************************************************************************
*Function: NVIC_Clear_Pending_Flag
*I/P Parameters: interrupt_num
*Returns:it returns no thing
*Desc:This Function Clears pending flag of Peripheral
******************************************************************************/


void NVIC_Clear_Pending_Flag (interrupt_ID_enum interrupt_num)
{
	SET_BIT(NVIC->ICPR[interrupt_num/32],interrupt_num%32);
}

/*****************************************************************************
*Function: NVIC_Read_Interrupt_Active
*I/P Parameters: interrupt_num
*Returns:it returns no thing
*Desc:This Function returns state of active flag in NVIC
*****************************************************************************/

uint8 NVIC_Read_Interrupt_Active(interrupt_ID_enum interrupt_num)
{
	uint8 value;
	value=GET_BIT(NVIC->IABR[interrupt_num/32],interrupt_num%32);

	return value;
}

/*****************************************************************************
*Function: NVIC_Set_Priority_Cfg
*I/P Parameters:  no thing
*Returns:it returns no thing
*Desc:This Function Sets the group and the sub priority configurations
********************************************************************************/

void NVIC_Set_Priority_Cfg (void)
{
	uint32 value ;
    value =AIRCR_RESET_VALUE  ;
    INSERST_BITS(value,8,3,GROUP_SUB_SELECT);
		(SCB->AIRCR)=value ;
}
/************************************************************************************
*
*Function: NVIC_Set_Priority
*I/P Parameters:      Iinterrupt_num,    group,           subgroup
*Return s: it returns no thing
*Desc:This Function Sets the group and the sub priority for required INT
*************************************************************************************
*
* Options:- GROUP_SUB_16_0    /   GROUP_SUB_8_2    /     GROUP_SUB_4_4    /  GROUP_SUB_2_8  /    GROUP_SUB_0_16
*****************************************************************************/


void NVIC_Set_Priority  (interrupt_ID_enum interrupt_num , uint8 group , uint8 subgroup )
{
	uint32 Priority = 0 ;

#if (GROUP_SUB_SELECT==GROUP_SUB_16_0)
	{
		INSERST_BITS ( Priority , 4 ,  4  , group);  //Setting all the 4 bits for grouping
	}

#elif (GROUP_SUB_SELECT==GROUP_SUB_8_2)
	{
		INSERST_BITS ((Priority) , 5 , 3 , group);    //Setting 3 bits for grouping "from bit 5 to 7"
	    INSERST_BITS ((Priority) , 4 , 1 , subgroup);  //Setting 1 bit for subgrouping "bit 4 "
	}
#elif (GROUP_SUB_SELECT==GROUP_SUB_4_4)
	{
	   INSERST_BITS ( Priority , 6 , 2 , group);   //Setting 2 bits for grouping " bit 6 and 7"
	   INSERST_BITS ( Priority , 4 , 2 , subgroup);  //Setting 2 bits for subgrouping ( bit 4 and 6)
	}
#elif (GROUP_SUB_SELECT==GROUP_SUB_2_8)
	{
		 INSERST_BITS((Priority)  , 7 , 1 , group);   //Setting 1 bits for grouping "bit 8"
		 INSERST_BITS ((Priority) , 4 , 3 , subgroup);  //Setting 3 bits for subgrouping (from bit 4 to 7)
	}
#elif (GROUP_SUB_SELECT==GROUP_SUB_0_16)
	{
		INSERST_BITS ((Priority) , 4 , 4 , subgroup);   //Setting all the 4 bits for subgrouping
	}
#endif


	switch (interrupt_num)
	{
	// cases for core peripherals
	case NVIC_MemManage  :

	case NVIC_BusFault   :

	case NVIC_UsageFault :

		INSERST_BITS(SCB->SHPR1,Usage_Bit_Location,4,Priority);

		break ;

	case NVIC_SVCall  :

		INSERST_BITS(SCB->SHPR2,SVCall_Bit_Location,4,Priority);

		break;

	case NVIC_PendSV  :

	case NVIC_Systick :

		INSERST_BITS(SCB->SHPR3,SysTich_Bit_Location,4,Priority);

		break;

	default :

		// for stm32 peripherals
		INSERST_BITS(NVIC->IPR[interrupt_num],IPR_Control_Bits,4,(Priority >> 4));
		break;
	}

}

