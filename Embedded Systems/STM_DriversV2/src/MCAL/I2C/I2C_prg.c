/*
 * I2C_prg.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Mamdouh & SABET
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "../RCC/RCC_int.h"
#include "../NVIC/NVIC_int.h"
#include "../GPIO/GPIO_int_.h"
#include "I2C_cfg.h"
#include "I2C_prv.h"
#include "I2C_int.h"



sint8 I2C_Init(I2C_Config_St * Config_St)
{
	sint8 state;
	switch (Config_St->I2C_Number)
	{
	case 1 :
	{
		// enable the clock on the periphral
		RCC_Enable_Clock(RCC_APB1, RCC_I2C1);
		// enable event interrupt
		NVIC_En_Interrupt(NVIC_I2C1_EV);
		// enable error interrupt
		NVIC_En_Interrupt(NVIC_I2C1_ER);
		// Disable the periphral
		CLEAR_BIT(I2C_1->I2C_CR1,0);
		// select periphral freq on APB1 BUS
		// IN This case the freq i will choos 20Mhz
		INSERST_BITS(I2C_1->I2C_CR2,0,6,20);
		// Disable event and error interrupts
		//SET_BIT(I2C_1->I2C_CR2,8);
		//SET_BIT(I2C_1->I2C_CR2,9);
		// choose the fast mode in CCR REGISTER
		SET_BIT(I2C_1->I2C_CCR,15);
		// make duty = 1 to reach 400khz
		SET_BIT(I2C_1->I2C_CCR,14);
		// CCR CALULATION TO CONFIGURE THE CLOCK WITH 400K AND SYSCLCOK IS 20MHZ
		// CCR = 2 ;
		INSERST_BITS(I2C_1->I2C_CCR,0,12,2);
		// CONFIGURE THE Trise TIME with 400khz clock i2c and 20mhz Freq i2c
		// in this case TRISE IS EQUAL 7
		INSERST_BITS(I2C_1->I2C_TRISE,0,6,7);
		// CLOCK STRETCHING ENABLE
		CLEAR_BIT(I2C_1->I2C_CR1,7);
		// GENERAL CALL DISABLED
		CLEAR_BIT(I2C_1->I2C_CR1,6);




		SET_BIT(I2C_1->I2C_CR1,0);

	}
	break;
	case 2 :
	{

	}
	break;
	case 3 :
	{

	}
	break;
	default :
		state = -1;
		break;

	}


	return state;
}






sint8 I2C_Gpio_Config(I2C_Config_St * Config_St)
{
	sint8 state ;
	switch (Config_St->I2C_Number)
	{
	case 1 : // PINS PB6 SCL1   PB7 SDA1
	{
		// ENABLE CLOCK ON GPIOB
		RCC_Enable_Clock(RCC_AHB1,RCC_GPIOB);
		// SET AF FUNCTION TO IC2

		GPIO_Set_Pin_Direction(PORTB, PIN6, GPIO_MODE_ALTFUN);
		GPIO_Set_Pin_Direction(PORTB, PIN7, GPIO_MODE_ALTFUN);

		GPIO_Alternate_Function(PORTB, PIN6, (0b0100));
		GPIO_Alternate_Function(PORTB, PIN7, (0b0100));

		// SELECT THE OPEN DRAIN
		GPIO_Set_Output_Type(PORTB, PIN6, OPEN_DRAIN);
		GPIO_Set_Output_Type(PORTB, PIN7, OPEN_DRAIN);

		// select the output speed very high
		GPIO_Set_Output_Speed(PORTB, PIN6, VeryHighSpeed);
		GPIO_Set_Output_Speed(PORTB, PIN7, VeryHighSpeed);

		// SELSE INTERNAL PULLUP
		//GPIO_Set_Input_Pullup_Pulldown(PORTB, PIN6, PULL_UP);
		//GPIO_Set_Input_Pullup_Pulldown(PORTB, PIN7, PULL_UP);
	}
	break;
	case 2 :
	{
		// ENABLE CLOCK ON GPIOB
			RCC_Enable_Clock(RCC_AHB1,RCC_GPIOB);
			// SET AF FUNCTION TO IC2
			GPIO_Alternate_Function(PORTB, PIN10, (0b1001));
			GPIO_Alternate_Function(PORTB, PIN3, (0b1001));

			// SELECT THE OPEN DRAIN
			GPIO_Set_Output_Type(PORTB, PIN10, OPEN_DRAIN);
			GPIO_Set_Output_Type(PORTB, PIN3, OPEN_DRAIN);

			// select the output speed very high
			GPIO_Set_Output_Speed(PORTB, PIN10, VeryHighSpeed);
			GPIO_Set_Output_Speed(PORTB, PIN3, VeryHighSpeed);

			// SELSE INTERNAL PULLUP
			GPIO_Set_Input_Pullup_Pulldown(PORTB, PIN10, PULL_UP);
			GPIO_Set_Input_Pullup_Pulldown(PORTB, PIN3, PULL_UP);
	}
	break;
	case 3 : // NEED EDIT
	{
		// ENABLE CLOCK ON GPIOB
		// ENABLE CLOCK ON GPIOA
			RCC_Enable_Clock(RCC_AHB1,RCC_GPIOB);
			RCC_Enable_Clock(RCC_AHB1,RCC_GPIOA);

			// SET AF FUNCTION TO IC2
			GPIO_Alternate_Function(PORTB, PIN10, (0b1001));
			GPIO_Alternate_Function(PORTB, PIN3, (0b1001));

			// SELECT THE OPEN DRAIN
			GPIO_Set_Output_Type(PORTB, PIN10, OPEN_DRAIN);
			GPIO_Set_Output_Type(PORTB, PIN3, OPEN_DRAIN);

			// select the output speed very high
			GPIO_Set_Output_Speed(PORTB, PIN10, VeryHighSpeed);
			GPIO_Set_Output_Speed(PORTB, PIN3, VeryHighSpeed);

			// SELSE INTERNAL PULLUP
			GPIO_Set_Input_Pullup_Pulldown(PORTB, PIN10, PULL_UP);
			GPIO_Set_Input_Pullup_Pulldown(PORTB, PIN3, PULL_UP);
	}
	break;
	default :
		state = -1;
		break;

	}




	return state;
}








uint8 I2C_Read_Byte(I2C_Config_St * Config_St,uint8 SLAVE_Address,uint8 REGISTER_Address)
{
	uint8 RECEIVED_Data = 0 ;

	switch (Config_St->I2C_Number)
	{
	case 1 :
	{
		// check if the bus is busy
		while(BIT_IS_SET(I2C_1->I2C_SR2,1))
		{

	    }

		// Generate a start condition
		SET_BIT(I2C_1->I2C_CR1,8);
		// wait untill start condition is generated
		// clear by reading
		while(BIT_IS_CLEAR(I2C_1->I2C_SR1,0))
			{

			}
		(void)I2C_1->I2C_SR1;

		// send slave address + write
		I2C_1->I2C_DR = (   (SLAVE_Address << 1)  |  (0)   );

		// WAIT untill address matched flag is 1
		while(BIT_IS_CLEAR(I2C_1->I2C_SR1,1))
		{

		}
		// IMPORTANT NOTE : to clear addr we must read both SR1 AND SR2 REGISTERS

		(void)I2C_1->I2C_SR2;
		// Send register address
		I2C_1->I2C_DR = REGISTER_Address ;
		// wait untill Byte transfer finished
		while(BIT_IS_CLEAR(I2C_1->I2C_SR1,2))
		{

		}
		// Send repeated start condition
		SET_BIT(I2C_1->I2C_CR1,8);
		// wait untill start condition is generated
		while(BIT_IS_CLEAR(I2C_1->I2C_SR1,0))
		{

		}
		// Send slave address + read

		I2C_1->I2C_DR = (   (SLAVE_Address << 1)  |  (1) );
		// WAIT untill address matched flag is 1
		while(BIT_IS_CLEAR(I2C_1->I2C_SR1,1))
		{

		}
		// Clear ADDR flag
		(void)I2C_1->I2C_SR2;
		// Disable ACK
		CLEAR_BIT(I2C_1->I2C_CR1,10);
		// WAIT TO READ DATA
		while(BIT_IS_CLEAR(I2C_1->I2C_SR1,6))
		{

		}

		RECEIVED_Data = I2C_1->I2C_DR;

		// Generate a stop condition
		SET_BIT(I2C_1->I2C_CR1,9);

	}
	break;
	case 2 :
	{

	}
	break;
	case 3 :
	{

	}
	break;
	default :
		return 0;
		break;
	}


	return RECEIVED_Data;
}







uint8 I2C_Write_Byte(I2C_Config_St * Config_St,uint8 SLAVE_Address,uint8 REGISTER_Address, uint8 Data)
{

	switch (Config_St->I2C_Number)
	{
	case 1 :
	{
		// check if the bus is busy
		while(BIT_IS_SET(I2C_1->I2C_SR2,1))
		{

	    }
		// Generate a start condition
		SET_BIT(I2C_1->I2C_CR1,8);
		// wait untill start condition is generated
		// clear by reading
		while(BIT_IS_CLEAR(I2C_1->I2C_SR1,0))
			{

			}
		(void)I2C_1->I2C_SR1;

		// send slave address + write
		I2C_1->I2C_DR = (   (SLAVE_Address << 1)  |  (0)   );

		// WAIT untill address matched flag is 1
		while(BIT_IS_CLEAR(I2C_1->I2C_SR1,1))
		{

		}
		// IMPORTANT NOTE : to clear addr we must read both SR1 AND SR2 REGISTERS
		(void)I2C_1->I2C_SR2;


		// Send register address
		I2C_1->I2C_DR = REGISTER_Address ;
		// wait untill Byte transfer finished
		while(BIT_IS_CLEAR(I2C_1->I2C_SR1,7))
		{

		}


		I2C_1->I2C_DR = Data;
		// WAIT TO Write DATA
		while(BIT_IS_CLEAR(I2C_1->I2C_SR1,7))
		{

		}
		// Generate a stop condition
		SET_BIT(I2C_1->I2C_CR1,9);

	}
	break;
	case 2 :
	{

	}
	break;
	case 3 :
	{

	}
	break;
	default :
		return 0;
		break;
	}








	return 0 ;
}














void I2C1_EV_IRQHandler(void)
{
}



void I2C1_ER_IRQHandler(void)
{
}









