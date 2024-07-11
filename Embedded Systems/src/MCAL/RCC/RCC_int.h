/*
 * RCC.h
 *
 *  Created on: Nov 29, 2023
 *      Author: Sabet & Mamdouh
 *      V 0.01
 */

#ifndef MCAL_RCC_RCC_INT_H_
#define MCAL_RCC_RCC_INT_H_

// Choose busID
typedef enum
{
	RCC_AHB1,
	RCC_AHB2,
	RCC_APB1,
	RCC_APB2
}BUSID_ENUM;



// for AHB1ENR REGISTER
enum
{
	RCC_GPIOA,
	RCC_GPIOB,
	RCC_GPIOC,
	RCC_GPIOD,
	RCC_GPIOE,
	RCC_GPIOH =7,
	RCC_CRC = 12,
	RCC_DMA1 = 21,
	RCC_DNA2,
};
// FOR APB2ENR REGISTER
enum
{
	RCC_TIM1,
	RCC_USART1 = 4,
	RCC_USART6,
	RCC_ADC1 = 8,
	RCC_SDIO = 11,
	RCC_SPI1,
	RCC_SPI4,
	RCC_SYSCFG,
	RCC_TIM9 = 16,
	RCC_TIM10 ,
	RCC_TIM11,
};

// for APB1ENR REGISTER
enum
{
	RCC_TIM2,
	RCC_TIM3,
	RCC_TIM4,
	RCC_TIM5,
	RCC_WWDG = 11,
	RCC_SPI2 = 14,
	RCC_SPI3,
	RCC_USART2 = 17,
	RCC_I2C1 = 21,
	RCC_I2C2,
	RCC_I2C3,
	RCC_PWR = 28
};



enum {
	APB_pre_0,
	APB_pre_2=4,
	APB_pre_4,
	APB_pre_8,
	APB_pre_16,
};
enum {
	AHB_pre_0,
	AHB_pre_2=8,
	AHB_pre_4,
	AHB_pre_8,
	AHB_pre_16,
	AHB_pre_64,
	AHB_pre_128,
	AHB_pre_256,
	AHB_pre_512
};




void RCC_Init(void);
void RCC_Enable_Clock(BUSID_ENUM BUSID, uint8 PERIPHERALID);
void RCC_Disable_Clock(BUSID_ENUM BUSID, uint8 PERIPHERALID);



#endif /* MCAL_RCC_RCC_INT_H_ */
