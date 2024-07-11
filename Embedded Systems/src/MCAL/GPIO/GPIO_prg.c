/*
 * GPIO_prg.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Mamdouh & Sabet
 *      v   0.01
 *
  */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "GPIO_cfg.h"
#include "GPIO_int_.h"
#include "GPIO_prv.h"

void GPIO_Set_Pin_Direction(uint8 PORTID,uint8 PIN_NO,uint8 Mode)
{

	// *2 to reach the bit location in the register
	/* and GPIO_MODE_RANGE IS 0B11 which is defined in lip/common macros /
	   Means that i want to change or insert in 2 bits to  change pin mode
	 */
	PIN_NO = PIN_NO * 2 ;
	switch (PORTID)
	{
	case PORTA :

		// for programmer pins
		/*if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		else*/
		INSERST_BITS(GPIOA->MODER,PIN_NO,GPIO_MODE_RANGE,Mode);
		break;
	case PORTB :
		INSERST_BITS(GPIOB->MODER,PIN_NO,GPIO_MODE_RANGE,Mode);
		break ;
	case PORTC :
		INSERST_BITS(GPIOC->MODER,PIN_NO,GPIO_MODE_RANGE,Mode);
		break;
	default :
		// this is wrong configuration
		break;
	}
}

void GPIO_Set_Port_Direction(uint8 port_id , uint8 pin_start_num,uint8 pin_end_num , uint8 pin_mode)
{
	{
		uint8 counter=0;
		for (counter=pin_start_num*2 ; counter<=pin_end_num*2;counter+=2)
		{
			switch (port_id) {
			case PORTA:
				INSERST_BITS(GPIOA->MODER ,counter, 2 ,pin_mode );
				break;
			case PORTB:
				INSERST_BITS(GPIOB->MODER ,counter, 2 ,pin_mode );
				break;
			case PORTC:
				INSERST_BITS(GPIOC->MODER ,counter, 2 ,pin_mode );
				break;
			default:
				break;
			}

		}

	}

}

void GPIO_Set_Output_Type(uint8 PORTID, uint8 PIN_NO, uint8 Type)
{
	switch (PORTID)
	{
	case PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		insert_bit(GPIOA->OTYPER,PIN_NO,Type);
		break ;
	case PORTB :
		insert_bit(GPIOB->OTYPER,PIN_NO,Type);
		break;
	case PORTC :
		insert_bit(GPIOC->OTYPER,PIN_NO,Type);
		break;
	default :
		// this is wrong configuration
		break;
	}
}


void GPIO_Set_Pins_OutType(uint8 PORTID , uint8 First_Pin,uint32 Range,uint8 Mode)
{
	uint8 counter;
	switch(PORTID)
	{
	case PORTA :

		for(counter = First_Pin; counter<Range; counter++ )
		{
			insert_bit(GPIOA->OTYPER,counter,Mode);
		}

		break;
	case PORTB :
		for(counter = First_Pin; counter<Range; counter++)
		{
			insert_bit(GPIOB->OTYPER,counter,Mode);
		}
		break;
	case PORTC :
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




void GPIO_Set_Output_Speed(uint8 PORTID,uint8 PIN_NO,uint8 Speed)
{
	// *2 to reach the bit location in the register
	/* and GPIO_MODE_RANGE IS 0B11 which is defined in lip/common macros /
	   Means that i want to change or insert in 2 bits to  change pin mode
	 */
	PIN_NO = PIN_NO * 2 ;
	switch (PORTID)
	{
	case PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		INSERST_BITS(GPIOA->OSPEEDR,PIN_NO,2,Speed);
		break ;
	case PORTB :
		INSERST_BITS(GPIOB->OSPEEDR,PIN_NO,2,Speed);
		break;
	case PORTC :
		INSERST_BITS(GPIOC->OSPEEDR,PIN_NO,2,Speed);
		break;
	default :
		// this is wrong configuration
		break;
	}
}





void GPIO_Set_Input_Pullup_Pulldown(uint8 PORTID, uint8 PIN_NO, uint8 Mode)
{
	// *2 to reach the bit location in the register
	/* and GPIO_MODE_RANGE IS 0B11 which is defined in lip/common macros /
	   Means that i want to change or insert in 2 bits to  change pin mode
	 */
	PIN_NO = PIN_NO * 2 ;
	switch (PORTID)
	{
	case PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		INSERST_BITS(GPIOA->PUPDR,PIN_NO,GPIO_PUPD_RANGE,Mode);
		break;
	case PORTB :
		INSERST_BITS(GPIOB->PUPDR,PIN_NO,GPIO_PUPD_RANGE,Mode);
		break ;
	case PORTC :
		INSERST_BITS(GPIOC->PUPDR,PIN_NO,GPIO_PUPD_RANGE,Mode);
		break;
	default :
		// this is wrong configuration
		break;
	}
}

uint8 GPIO_Read_Pin(uint8 PORTID, uint8 PIN_NO)
{
	uint8 result = 0;
	switch (PORTID)
	{
	case PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		result = (GET_BIT(GPIOA->IDR,PIN_NO));
		break;
	case PORTB :
		result = (GET_BIT(GPIOB->IDR,PIN_NO));
		break;
	case PORTC :
		result = (GET_BIT(GPIOC->IDR,PIN_NO));
		break;
	default :
		// wrong configuration
		break;
	}

	return result;
}

void GPIO_Set_Pin_Value(uint8 PORTID, uint8 PIN_NO, uint8 Value)
{
	switch (PORTID)
	{
	case PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		insert_bit(GPIOA->ODR,PIN_NO,Value);
		break;
	case PORTB :
		insert_bit(GPIOB->ODR,PIN_NO,Value);
		break;
	case PORTC :
		insert_bit(GPIOC->ODR,PIN_NO,Value);
		break;
	default :
		// wrong configuration
		break;
	}
}


void GPIO_Set_Port_Value(uint8 port_id , uint8 pin_start_num , uint8 value)
{
	switch (port_id) {
	case PORTA:

		GPIOA->BSRR=(value<<pin_start_num);
		GPIOA->BSRR=((~value)<<(pin_start_num+16));

		break;
	case PORTB:

		GPIOB->BSRR=(value<<pin_start_num);
		GPIOB->BSRR=((~value)<<(pin_start_num+16));

		break;

	case PORTC:

		GPIOC->BSRR=(value<<pin_start_num);
		GPIOC->BSRR=((~value)<<(pin_start_num+16));

		break;

	default:
		break;
	}
}


void GPIO_Fast_Set_Value(uint8 PORTID, uint8 PIN_NO)
{
	switch(PORTID)
	{
	case PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		GPIOA->BSRR = (1<<PIN_NO);
		break;
	case PORTB :
		GPIOB->BSRR = (1<<PIN_NO);
		break;
	case PORTC :
		GPIOB->BSRR = (1<<PIN_NO);
		break;
	default :
		// wrong configuration
		break;
	}
}

void GPIO_Fast_Reset_Value(uint8 PORTID, uint8 PIN_NO)
{
	switch(PORTID)
	{
	case PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		GPIOA->BSRR = (1<<(PIN_NO+16));
		break;
	case PORTB :
		GPIOB->BSRR = (1<<(PIN_NO+16));
		break;
	case PORTC :
		GPIOB->BSRR = (1<<(PIN_NO+16));
		break;
	default :
		// wrong configuration
		break;
	}
}


void GPIO_Port_Lock(uint8 PORTID)
{
	switch (PORTID)
	{
	case PORTA :

		insert_bit(GPIOA->LCKR,16,PORT_LOCKED);
		INSERST_BITS(GPIOA->LCKR,0,16,ALL_PINS_LOCKED);
		break;
	case PORTB :
		insert_bit(GPIOB->LCKR,16,PORT_LOCKED);
		INSERST_BITS(GPIOB->LCKR,0,16,ALL_PINS_LOCKED);

		break ;
	case PORTC :
		insert_bit(GPIOC->LCKR,16,PORT_LOCKED);
		INSERST_BITS(GPIOC->LCKR,0,16,ALL_PINS_LOCKED);

		break;
	default :
		// this is wrong configuration
		break;
	}
}



void GPIO_Pin_Lock(uint8 PORTID, uint8 PIN_NO, uint8 Mode)
{
	switch (PORTID)
	{
	case PORTA :
		// for programmer pins
		if((PIN_NO == 13) || (PIN_NO == 14))
		{
			break;
		}
		insert_bit(GPIOA->LCKR,16,PORT_LOCKED);
		insert_bit(GPIOA->LCKR,PIN_NO,Mode);
		break;
	case PORTB :
		insert_bit(GPIOB->LCKR,16,PORT_LOCKED);
		insert_bit(GPIOB->LCKR,PIN_NO,Mode);
		break ;
	case PORTC :
		insert_bit(GPIOC->LCKR,16,PORT_LOCKED);
		insert_bit(GPIOC->LCKR,PIN_NO,Mode);
		break;
	default :
		// this is wrong configuration
		break;
	}
}

void GPIO_Alternate_Function(uint8 PORTID,uint8 PIN_NO, uint8 Function)
{
	if(PIN_NO < 8)
	{

		// This equation to reach the bit location in the register
		/* and GPIO_MODE_RANGE IS 0B1111 which is defined in lip/common macros /
	   Means that i want to change or insert in 4 bits to  change pin mode
		 */
		PIN_NO = PIN_NO * 4;
		switch (PORTID)
		{
		case PORTA :
			// for programmer pins
			if((PIN_NO == 13) || (PIN_NO == 14))
			{
				break;
			}
			INSERST_BITS(GPIOA->AFRL, PIN_NO,AFRH_RANGE_BITS,Function);
			break;
		case PORTB :
			INSERST_BITS(GPIOB->AFRL, PIN_NO,AFRH_RANGE_BITS,Function);
			break;
		case PORTC :
			INSERST_BITS(GPIOC->AFRL, PIN_NO,AFRH_RANGE_BITS,Function);
			break;
		default :
			// wrong configuration
			break;
		}

	}

	else if((PIN_NO >= 8) && (PIN_NO <= 15))
	{
		// *4 to reach the bit location in the register
		/* and GPIO_MODE_RANGE IS 0B1111 which is defined in lip/common macros /
		   Means that i want to change or insert in 4 bits to  change pin mode
		 */
		PIN_NO = (PIN_NO-8) * 4;
		switch (PORTID)
		{
		case PORTA :
			// for programmer pins
			if((PIN_NO == 13) || (PIN_NO == 14))
			{
				break;
			}
			INSERST_BITS(GPIOA->AFRH, PIN_NO,AFRH_RANGE_BITS,Function);
			break;
		case PORTB :
			INSERST_BITS(GPIOB->AFRH, PIN_NO,AFRH_RANGE_BITS,Function);
			break;
		case PORTC :
			INSERST_BITS(GPIOC->AFRH, PIN_NO,AFRH_RANGE_BITS,Function);
			break;
		default :
			// wrong configuration
			break;
		}
	}

}



