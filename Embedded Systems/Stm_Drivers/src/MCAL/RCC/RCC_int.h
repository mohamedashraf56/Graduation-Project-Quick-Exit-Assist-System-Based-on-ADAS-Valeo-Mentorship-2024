/*
 * RCC.h
 *
 *  Created on: Nov 29, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_RCC_RCC_INT_H_
#define MCAL_RCC_RCC_INT_H_


// for switch case int prg function
#define RCC_AHB1 0
#define RCC_AHB2 1
#define RCC_APB1 2
#define RCC_APB2 3


// pin numbers for CR reg
enum
{
	HSION,
	HSEON = 16,
	HSEBYP = 18,
	CSSON = 19,
	PLLON = 24,
};



// FOR CFGR REG
enum
{
	SW0,
	SW1,
	HPRE0 = 4,
	HPRE1,
	HPRE2,
	HPRE3,
	PPRE10 = 10,
	PPRE11,
	PPRE12,
	PPRE20,
	PPRE21,
	PPRE22,
	RTCPRE0,
	RTCPRE1,
	RTCPRE2,
	RTCPRE3,
	RTCPRE4,
	MCO1 = 22,
	I2SSCR,
	 MCO1_PRE0,
	 MCO1_PRE1,
	 MCO1_PRE2,
	 MCO2_PRE0,
	 MCO2_PRE1,
	 MCO2_PRE2,
	 MCO2 = 31,
};



// for AHB1ENR REGISTER
enum
{
	RCC_GPIOAEN,
	RCC_GPIOBEN,
	RCC_GPIOCEN,
	RCC_GPIODEN,
	RCC_GPIOEEN,
	RCC_GPIOHEN =7,
	RCC_CRCEN = 12,
	RCC_DMA1EN = 21,
	RCC_DNA2EN,
};
// FOR APB2ENR REGISTER
enum
{
	RCC_TIM1_EN,
	RCC_USART1_EN = 4,
	RCC_USART6_EN,
	RCC_ADC1_EN = 8,
	RCC_SDIO_EN = 11,
	RCC_SPI1_EN,
	RCC_SPI4_EN,
	RCC_SYSCFG_EN,
	RCC_TIM9_EN = 16,
	RCC_TIM10_EN ,
	RCC_TIM11_EN,
};

// for APB1ENR REGISTER
enum
{
	TIM2_EN,
	TIM3_EN,
	TIM4_EN,
	TIM5_EN,
	WWDG_EN = 11,
	SPI2_EN = 14,
	SPI3_EN,
	USART2_EN = 17,
	I2C1_EN = 21,
	I2C2_EN,
	I2C3_EN,
	PWR_EN = 28
};

// please import RCC_APB1ENR and RCC_APB1ENR in data sheet 116 page


void MRCC_vInit(void);
void MRCC_vEnableClock(uint8 BUSID, uint8 PERIPHERALID);
void MRCC_vDisableClock(uint8 BUSID, uint8 PERIPHERALID);



#endif /* MCAL_RCC_RCC_INT_H_ */
