/*
 * GPIO_prg.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Mamdouh
 */
#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "GPIO_int_.h"
#include "GPIO_prv.h"
#include "GPIO_cfg.h"



void GPIO_SetPin_Direction(uint8 PORTID,uint8 PIN_NO,uint8 Mode)
{

	// *2 to reach the bit location in the register
	/* and GPIO_MODE_RANGE IS 0B11 which is defined in lip/common macros /
	   Means that i want to change or insert in 2 bits to  change pin mode
	  */
	PIN_NO = PIN_NO * 2 ;
	switch (PORTID)
	{
	case GPIO_PORTA :

		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		INSERST_BITS(GPIOA->MODER,Mode,GPIO_MODE_RANGE,PIN_NO);
		break;
	case GPIO_PORTB :
		INSERST_BITS(GPIOB->MODER,Mode,GPIO_MODE_RANGE,PIN_NO);
		break ;
	case GPIO_PORTC :
		INSERST_BITS(GPIOC->MODER,Mode,GPIO_MODE_RANGE,PIN_NO);
		break;
	default :
		// this is wrong configuration
		break;
	}
}

void GPIO_SetPins_Direction (uint8 PORTID , uint8 First_Pin,uint32 Range,uint8 Mode)
{
	uint8 counter;
	switch(PORTID)
	{
	case GPIO_PORTA :

		for(counter = First_Pin; counter<(Range*2); counter = counter + 2)
		{
			// two_one is 0b11 this is the range of
			// bits to control one pin direction
			INSERST_BITS(GPIOA->MODER,Mode,two_one,counter);
		}

		break;
	case GPIO_PORTB :
		for(counter = First_Pin; counter<Range; counter = counter + 2)
		{
			INSERST_BITS(GPIOB->MODER,Mode,two_one,counter);
		}
		break;
	case GPIO_PORTC :
		for(counter = First_Pin; counter<Range; counter = counter + 2)
		{
			INSERST_BITS(GPIOC->MODER,Mode,two_one,counter);
		}
		break;
	default :
		// wrong configuration
		break;
	}
}



void GPIO_SetOutput_Type(uint8 PORTID, uint8 PIN_NO, uint8 Type)
{
	switch (PORTID)
	{
	case GPIO_PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
	    insert_bit(GPIOA->OTYPER,PIN_NO,Type);
		break ;
	case GPIO_PORTB :
		insert_bit(GPIOB->OTYPER,PIN_NO,Type);
		break;
	case GPIO_PORTC :
		insert_bit(GPIOC->OTYPER,PIN_NO,Type);
		break;
	default :
		// this is wrong configuration
		break;
	}
}


void GPIO_SetPins_OutType(uint8 PORTID , uint8 First_Pin,uint32 Range,uint8 Mode)
{
	uint8 counter;
		switch(PORTID)
		{
		case GPIO_PORTA :

			for(counter = First_Pin; counter<Range; counter++ )
			{
				insert_bit(GPIOA->OTYPER,counter,Mode);
			}

			break;
		case GPIO_PORTB :
			for(counter = First_Pin; counter<Range; counter++)
			{
				insert_bit(GPIOB->OTYPER,counter,Mode);
			}
			break;
		case GPIO_PORTC :
			for(counter = First_Pin; counter<Range; counter++)
			{
				insert_bit(GPIOB->OTYPER,counter,Mode);
			}
			break;
		default :
			// wrong configuration
			break;
		}
}




void GPIO_SetOutput_Speed(uint8 PORTID,uint8 PIN_NO,uint8 Speed)
{
	// *2 to reach the bit location in the register
	/* and GPIO_MODE_RANGE IS 0B11 which is defined in lip/common macros /
	   Means that i want to change or insert in 2 bits to  change pin mode
	  */
	PIN_NO = PIN_NO * 2 ;
	switch (PORTID)
		{
		case GPIO_PORTA :
			// for programmer pins
			if((PIN_NO == 13) || (PIN_NO == 14))
			{
				break;
			}
		    INSERST_BITS(GPIOA->OSPEEDR,Speed,two_one,PIN_NO);
			break ;
		case GPIO_PORTB :
			INSERST_BITS(GPIOB->OSPEEDR,Speed,two_one,PIN_NO);
			break;
		case GPIO_PORTC :
			INSERST_BITS(GPIOC->OSPEEDR,Speed,two_one,PIN_NO);
			break;
		default :
			// this is wrong configuration
			break;
		}
}



void GPIO_SetPins_Speed (uint8 PORTID , uint8 First_Pin,uint32 Range,uint8 Mode)
{
	uint8 counter;
	switch(PORTID)
	{
	case GPIO_PORTA :

		for(counter = First_Pin; counter<(Range*2); counter = counter + 2)
		{
			// two_one is 0b11 this is the range of
			// bits to control one pin direction
			INSERST_BITS(GPIOA->OSPEEDR,Mode,two_one,counter);
		}

		break;
	case GPIO_PORTB :
		for(counter = First_Pin; counter<Range; counter = counter + 2)
		{
			INSERST_BITS(GPIOB->OSPEEDR,Mode,two_one,counter);
		}
		break;
	case GPIO_PORTC :
		for(counter = First_Pin; counter<Range; counter = counter + 2)
		{
			INSERST_BITS(GPIOC->OSPEEDR,Mode,two_one,counter);
		}
		break;
	default :
		// wrong configuration
		break;
	}
}



void GPIO_SetInput_PuPd(uint8 PORTID, uint8 PIN_NO, uint8 Mode)
{
	// *2 to reach the bit location in the register
	/* and GPIO_MODE_RANGE IS 0B11 which is defined in lip/common macros /
	   Means that i want to change or insert in 2 bits to  change pin mode
	  */
	PIN_NO = PIN_NO * 2 ;
	switch (PORTID)
		{
		case GPIO_PORTA :
			// for programmer pins
			if((PIN_NO == 13) || (PIN_NO == 14))
			{
				break;
			}
			INSERST_BITS(GPIOA->PUPDR,Mode,GPIO_PUPD_RANGE,PIN_NO);
			break;
		case GPIO_PORTB :
			INSERST_BITS(GPIOB->PUPDR,Mode,GPIO_PUPD_RANGE,PIN_NO);
			break ;
		case GPIO_PORTC :
			INSERST_BITS(GPIOC->PUPDR,Mode,GPIO_PUPD_RANGE,PIN_NO);
			break;
		default :
			// this is wrong configuration
			break;
		}
}

uint8 GPIO_ReadPin(uint8 PORTID, uint8 PIN_NO)
{
	uint8 result = 0;
	switch (PORTID)
	{
	case GPIO_PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		result = (GET_BIT(GPIOA->IDR,PIN_NO));
		break;
	case GPIO_PORTB :
		result = (GET_BIT(GPIOB->IDR,PIN_NO));
		break;
	case GPIO_PORTC :
		result = (GET_BIT(GPIOC->IDR,PIN_NO));
		break;
	default :
		// wrong configuration
		break;
	}

	return result;
}

void GPIO_SetPin_Value(uint8 PORTID, uint8 PIN_NO, uint8 Value)
{
	switch (PORTID)
	{
	case GPIO_PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
	insert_bit(GPIOA->ODR,PIN_NO,Value);
	break;
	case GPIO_PORTB :
		insert_bit(GPIOB->ODR,PIN_NO,Value);
		break;
	case GPIO_PORTC :
		insert_bit(GPIOC->ODR,PIN_NO,Value);
		break;
	default :
		// wrong configuration
		break;
	}
}



void GPIO_SetPins_Value (uint8 PORTID , uint8 First_Pin,uint32 Range,uint8 Value)
{
	uint8 counter;
		switch(PORTID)
		{
		case GPIO_PORTA :

			for(counter = First_Pin; counter<Range; counter++ )
			{
				insert_bit(GPIOA->ODR,counter,Value);
			}

			break;
		case GPIO_PORTB :
			for(counter = First_Pin; counter<Range; counter++)
			{
				insert_bit(GPIOB->ODR,counter,Value);
			}
			break;
		case GPIO_PORTC :
			for(counter = First_Pin; counter<Range; counter++)
			{
				insert_bit(GPIOB->ODR,counter,Value);
			}
			break;
		default :
			// wrong configuration
			break;
		}
}



void GPIO_FastSet_Value(uint8 PORTID, uint8 PIN_NO)
{
	switch(PORTID)
	{
	case GPIO_PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		GPIOA->BSRR = (1<<PIN_NO);
		break;
	case GPIO_PORTB :
		GPIOB->BSRR = (1<<PIN_NO);
		break;
	case GPIO_PORTC :
		GPIOB->BSRR = (1<<PIN_NO);
		break;
	default :
	// wrong configuration
		break;
	}
}

void GPIO_FastReset_Value(uint8 PORTID, uint8 PIN_NO)
{
	switch(PORTID)
	{
	case GPIO_PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		GPIOA->BSRR = (1<<(PIN_NO+16));
		break;
	case GPIO_PORTB :
		GPIOB->BSRR = (1<<(PIN_NO+16));
		break;
	case GPIO_PORTC :
		GPIOB->BSRR = (1<<(PIN_NO+16));
		break;
	default :
	// wrong configuration
		break;
	}
}


void GPIO_PortLock(uint8 PORTID,uint8 Mode)
{
	switch (PORTID)
			{
			case GPIO_PORTA :

				insert_bit(GPIOA->LCKR,16,Mode);
				break;
			case GPIO_PORTB :
				insert_bit(GPIOB->LCKR,16,Mode);
				break ;
			case GPIO_PORTC :
				insert_bit(GPIOC->LCKR,16,Mode);
				break;
			default :
				// this is wrong configuration
				break;
			}
}



void GPIO_PinLock(uint8 PORTID, uint8 PIN_NO, uint8 Mode)
{
	switch (PORTID)
			{
			case GPIO_PORTA :
				// for programmer pins
				if((PIN_NO == 13) || (PIN_NO == 14))
				{
					break;
				}
				insert_bit(GPIOA->LCKR,PIN_NO,Mode);
				break;
			case GPIO_PORTB :
				insert_bit(GPIOB->LCKR,PIN_NO,Mode);
				break ;
			case GPIO_PORTC :
				insert_bit(GPIOC->LCKR,PIN_NO,Mode);
				break;
			default :
				// this is wrong configuration
				break;
			}
}

void GPIO_HAlternate_Function(uint8 PORTID,uint8 PIN_NO, uint8 Function)
{
	// This equation to reach the bit location in the register
	/* and GPIO_MODE_RANGE IS 0B1111 which is defined in lip/common macros /
	   Means that i want to change or insert in 4 bits to  change pin mode
	  */
	PIN_NO = (PIN_NO-8) * 4;

	switch (PORTID)
	{
	case GPIO_PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		    INSERST_BITS(GPIOA->AFRH, Function,AFRH_RANGE_BITS,PIN_NO);
		break;
	case GPIO_PORTB :
			INSERST_BITS(GPIOB->AFRH, Function,AFRH_RANGE_BITS,PIN_NO);
			break;
	case GPIO_PORTC :
			INSERST_BITS(GPIOC->AFRH, Function,AFRH_RANGE_BITS,PIN_NO);
			break;
	default :
		// wrong configuration
		break;
	}

}

void GPIO_LAlternate_Function(uint8 PORTID, uint8 PIN_NO, uint8 Function)
{
	// *4 to reach the bit location in the register
	/* and GPIO_MODE_RANGE IS 0B1111 which is defined in lip/common macros /
	   Means that i want to change or insert in 4 bits to  change pin mode
	  */
	PIN_NO = PIN_NO * 4;
	switch (PORTID)
		{
		case GPIO_PORTA :
			// for programmer pins
			if((PIN_NO == 13) || (PIN_NO == 14))
			{
				break;
			}
			    INSERST_BITS(GPIOA->AFRL, Function,AFRH_RANGE_BITS,PIN_NO);
			break;
		case GPIO_PORTB :
				INSERST_BITS(GPIOB->AFRL, Function,AFRH_RANGE_BITS,PIN_NO);
				break;
		case GPIO_PORTC :
				INSERST_BITS(GPIOC->AFRL, Function,AFRH_RANGE_BITS,PIN_NO);
				break;
		default :
			// wrong configuration
			break;
		}
}


void GPIO_Write_Port(uint8 PORTID,uint16 Value)
{

	switch(PORTID)
	{
	case GPIO_PORTA :
		INSERST_BITS(GPIOA->ODR,Value,0XFFFF,0);
		break;
	case GPIO_PORTB :
			INSERST_BITS(GPIOB->ODR,Value,0XFFFF,0);
			break;
	case GPIO_PORTC :
			INSERST_BITS(GPIOB->ODR,Value,0XFFFF,0);
			break;
	default :
		// wrong configuration
		break;
	}
}


void GPIO_Write_Pins(uint8 PORTID,uint8 PIN_Nu,uint8 Range,uint16 Value)
{

	switch(PORTID)
	{
	case GPIO_PORTA :
		INSERST_BITS(GPIOA->ODR,Value,Range,PIN_Nu);
		break;
	case GPIO_PORTB :
			INSERST_BITS(GPIOB->ODR,Value,Range,PIN_Nu);
			break;
	case GPIO_PORTC :
			INSERST_BITS(GPIOB->ODR,Value,Range,PIN_Nu);
			break;
	default :
		// wrong configuration
		break;
	}
}



uint16 GPIO_Read_Port(uint8 PORTID)
{
	uint16 result = 0;

	switch(PORTID)
		{
		case GPIO_PORTA :
			result = GPIOA->IDR;
			break;
		case GPIO_PORTB :
			result = GPIOB->IDR;
				break;
		case GPIO_PORTC :
			result = GPIOC->IDR;
				break;
		default :
			// wrong configuration
			break;
		}

	return result;
}

