/*
 * USART.cfg.c
 *
 *  Created on: Mar 23, 2024
 *      Author: asabe
 */
#include "../../MCAL/GPIO/GPIO_int_.h"

#include "USART_init.h"

USART_Confg_Struct USART1_cfg_struct ={
			.USART_TX_PIN= PIN9,
			.USART_RX_PIN =PIN10,
			.USART_TX_PORT = PORTA,
			.USART_RX_PORT  = PORTA,
			.USART_Data_Lengh = DATA_Reg_8bit,
			.USART_OverSampling = OverSampling_8,
			.USART_StopBit = StopBit_1,
	};
	USART_Confg_Struct USART2_cfg_struct ={
			.USART_TX_PIN= PIN2,
			.USART_RX_PIN =PIN3,
			.USART_TX_PORT = PORTA,
			.USART_RX_PORT  = PORTA,
			.USART_Data_Lengh = DATA_Reg_8bit,
			.USART_OverSampling = OverSampling_8,
			.USART_StopBit = StopBit_1,
	};

	USART_Confg_Struct USART6_cfg_struct ={
			.USART_TX_PIN= PIN11,
			.USART_RX_PIN =PIN12,
			.USART_TX_PORT = PORTA,
			.USART_RX_PORT  = PORTA,
			.USART_Data_Lengh = DATA_Reg_8bit,
			.USART_OverSampling = OverSampling_8,
			.USART_StopBit = StopBit_1,
	};


