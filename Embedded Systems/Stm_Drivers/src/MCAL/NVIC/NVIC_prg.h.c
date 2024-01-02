/*
 * NVIC_prg.h.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Mamdouh
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"

#include "NVIC_int.h"
#include "NVIC_prv.h"
#include "NVIC_cfg.h"

static uint32 GlobalStatic_Uint32Group ;



// Interrupt / 32 to reach the Register (0 to 7 Reg) i which the interrupt number is
// Interrupt %32 to reach the location of the bit which belongs to the interrupt

/* ********************************************************************
 * Name     : Nvic_En_Interrupt
 * function : Enable interrupt on specific Peripheral
 * Return   : NOTHING
 * input1   : WWDG , EXTI16_PVD , RCC, TIM1_CC USART1 from NVIC_int.h
 ***********************************************************************/
void Nvic_En_Interrupt(uint8 Interrupt_Number)
{
	NVIC->ISER[(Interrupt_Number/32)] = (1<<(Interrupt_Number%32));
}

/* ********************************************************************
 * Name     : Nvic_Dis_Interrupt
 * function : Disable interrupt on specific Peripheral
 * Return   : NOTHING
 * input1   : WWDG , EXTI16_PVD , RCC, TIM1_CC USART1 from NVIC_int.h
 ***********************************************************************/
void Nvic_Dis_Interrupt(uint8 Interrupt_Number)
{
	NVIC->ICER[(Interrupt_Number/32)] = (1<<(Interrupt_Number%32));
}


/* ********************************************************************
 * Name     : Nvic_Read_Interrupt
 * function : Disable interrupt on specific Peripheral
 * Return   : 0 indicates to disable 1 indicates to enable
 * input1   : WWDG , EXTI16_PVD , RCC, TIM1_CC USART1 from NVIC_int.h
 ***********************************************************************/
uint8 Nvic_Read_Interrupt( uint8 Interrupt_Number)
{
	uint8 result = 0;
	result = (NVIC->ISER[(Interrupt_Number/32)]) & (1<<(Interrupt_Number%32));
	return result;
}

/* ********************************************************************
 * Name     : Nvic_Set_Pending_Flag
 * function : Sets the pending flag for testing
 * Return   : Nothing
 * input1   : WWDG , EXTI16_PVD , RCC, TIM1_CC USART1 from NVIC_int.h
 ***********************************************************************/
void Nvic_Set_Pending_Flag( uint8 Interrupt_Number)
{
	NVIC->ISPR[(Interrupt_Number/32)] = (1<<(Interrupt_Number%32));
}


/* ********************************************************************
 * Name     : Nvic_Clear_Pending_Flag
 * function : Clears the pending flag for testing
 * Return   : Nothing
 * input1   : WWDG , EXTI16_PVD , RCC, TIM1_CC USART1 from NVIC_int.h
 ***********************************************************************/

void Nvic_Clear_Pending_Flag(uint8 Interrupt_Number)
{
	NVIC->ICPR[(Interrupt_Number/32)] = (1<<(Interrupt_Number%32));
}


/* ********************************************************************
 * Name     : Nvic_Read_Pending_Flag
 * function : Read the pending flag for testing
 * Return   : 0 indicates for no pending flags 1 indicates for interrupt is pending
 * input1   : WWDG , EXTI16_PVD , RCC, TIM1_CC USART1 from NVIC_int.h
 ***********************************************************************/

uint8 Nvic_Read_Pending_Flag(uint8 Interrupt_Number)
{
	uint8 result = 0;
	result = ( NVIC->ISPR[(Interrupt_Number/32)] ) & (1<<(Interrupt_Number%32));
	return result;
}


/* ********************************************************************
 * Name     : Nvic_Read_Active_Flag
 * function : Read the Active flag when an interrupt is occurs
 * Return   : 0 for no active interrupt 1 when an interrupt is executes
 * input1   : WWDG , EXTI16_PVD , RCC, TIM1_CC USART1 from NVIC_int.h
 ***********************************************************************/
uint8 Nvic_Read_Active_Flag( uint8 Interrupt_Number)
{
	uint8 result = 0;
	result = (NVIC->IABR[(Interrupt_Number/32)]) & (1<<(Interrupt_Number%32));
	return result;
}


/* ********************************************************************
 * Name     : Nvic_SetPriorityCfg
 * function : Set the configuration for 4bits how many bits for group and subgroup
 * Return   : Nothing
 * input1   : GRUOP_0BITS , GRUOP_1BITS , GRUOP_2BITS
 *            GRUOP_3BITS , GRUOP_4BITS
 *
 * Very important note : Before using this function check if your choice match
 * the GROUP_CFG_SELECTED in NVIC_cfg or not
 ***********************************************************************/

void Nvic_SetPriorityCfg(uint8 GROUP_cfg_Selected)
{
	GlobalStatic_Uint32Group = 0X05FA0000 | (GROUP_cfg_Selected << 8);
	SCB->AIRCR = GlobalStatic_Uint32Group;
}


/* ********************************************************************
 * Name     : Nvic_SetPriority
 * function : Sets the peripherals priority
 * Return   : Nothing
 * input1   : WWDG , EXTI16_PVD , RCC, TIM1_CC USART1 from NVIC_int.h
 * input2   : Group priority : 0 , 1 , 2 , 3  ....
 * input3   : SubGroup priority : 0 , 1 , 2 , 3 .....
 * Note     : 0 indicates for high priority
 ***********************************************************************/

void Nvic_SetPriority(sint8 s8INTID,uint8 u8GroupPriority,uint8 u8SubPriority)
{
	uint32 Priority = 0;
	// to make sure that the user insert a valid number of group and subgroup priority
	if((u8GroupPriority <= Allowable_Group) && (u8SubPriority <= Allowable_Sub))
	{
		Priority = u8SubPriority | (u8GroupPriority << GROUP_Range_Shift);
	}

	switch (s8INTID)
	{
	// cases for core peripherals
	case Memory_Management_Fault :

		INSERST_BITS(SCB->SHPR1,Priority,four_one,Memory_Bit_Location);

		break;

	case Bus_Fault :

		INSERST_BITS(SCB->SHPR1,Priority,four_one,Bus_Bit_Location);

		break ;

	case Usage_Fault :

		INSERST_BITS(SCB->SHPR1,Priority,four_one,Usage_Bit_Location);

		break ;

	case SVCall :

		INSERST_BITS(SCB->SHPR2,Priority,four_one,SVCall_Bit_Location);

		break;

	case PendSV :

		INSERST_BITS(SCB->SHPR3,Priority,four_one,PendSV_Bit_Location);

		break;

	case SysTick_Exception :

		INSERST_BITS(SCB->SHPR3,Priority,four_one,SysTich_Bit_Location);

		break;

	default :

		// for stm32 peripherals
		INSERST_BITS(NVIC->IPR[s8INTID],Priority,four_one,4);
		break;
	}


}


