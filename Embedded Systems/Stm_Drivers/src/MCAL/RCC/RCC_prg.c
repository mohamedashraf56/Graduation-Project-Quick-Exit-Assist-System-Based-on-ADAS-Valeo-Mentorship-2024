/*
 * RCC.c
 *
 *  Created on: Nov 29, 2023
 *      Author: Mamdouh
 */

#include "../../lip/common_macros.h"
#include "../../lip/std_types.h"

#include "RCC_int.h"
#include "RCC.prv.h"
#include "RCC_cfg.h"


void MRCC_vInit(void)
{

	//1- CSS (ON/OF)
	SET_BIT(RCC->CR,CSSON); // CSS IS ON

#if  RCC_PLL_ENABLE == ENABLE
	SET_BIT(RCC->CR,PLLON);
#endif
	// 2- HSE_BYP (ON/OF)
	CLEAR_BIT(RCC->CR,HSEBYP);// OSCILLATOR NOT BYPASSED

	// * 3- SELECT CLK SWITCH (HSI/HSE/PLL)
	// TO MAKE SW IN CFGR 01 TO SWITCH TO HSE


	SET_BIT(RCC->CFGR,SW0);
	CLEAR_BIT(RCC->CFGR,SW1);

	//4- BUS PRESCALER
	// 0 presents to no division look the data sheet
	// AHB clock divided 2 look the Register description page 109
	INSERST_BITS(RCC->CFGR,(0b1011),four_one,HPRE0);
	//APB2 clock not divided
	INSERST_BITS(RCC->CFGR,0,three_one,PPRE20);
	// HPRE: APB1 prescaler // no divided
	INSERST_BITS(RCC->CFGR,0,three_one,PPRE10);

	//5- PLL CONFIGRATION
#if  RCC_PLL_ENABLE == ENABLE
#if   PLLM <= 63 && PLLM >=2 // THIS CONDITION FROM DATA SHEET
   #if  PLLP == 2 || PLLP == 4 || PLLP == 6 || PLLP == 8
     #if PLLN >= 192 && PLLN <= 432

	// SET PLLM & PLLP & PLLN WITH A DEFFRENT VALUES TO CONFIG THE PLL

	INSERST_BITS(RCC->PLLCFGR,PLLM,six_one,PLLMLOCATION);
	INSERST_BITS(RCC->PLLCFGR,PLLN,nine_one,PLLNLOCATION);
	INSERST_BITS(RCC->PLLCFGR,PLLP,two_one,PLLPLOCATION);

     #endif
   #endif
#endif
#endif


	//6- ENABLE THE SELECTED CLK (HSION/HSEON/ PLL)
#if RCC_HSE_ENABLE == ENABLE
	// IT MUST BE THE LAST THING IN INIT FUNC to enable HSE/HSI/PLL
	SET_BIT(RCC->CR,HSEON);
#endif
}


/* ********************************************************************
 * Name :MRCC_vEnableClock
 * function : THIS FUNC TO ENABLE A CLK ON SPACIFIC PERIPHRAL
 * Return : NOTHING
 * input1 : RCC_AHB1, RCC_AHB2,RCC_APB1,RCC_APB2
 * input2 : RCC_GPIOAEN,RCC_GPIOBEN,RCC_CRCEN,RCC_DNA2EN,
 ***********************************************************************/
void MRCC_vEnableClock(uint8 BUSID, uint8 PERIPHERALID)
{

	switch (BUSID)
	{
	case RCC_AHB1 :
		SET_BIT(RCC->AHB1ENR,PERIPHERALID);
		break;

	case RCC_AHB2 :
		SET_BIT(RCC->AHB2ENR,PERIPHERALID);
		break;

	case RCC_APB1 :
		SET_BIT(RCC->APB1ENR,PERIPHERALID);
		break;

	case RCC_APB2 :
		SET_BIT(RCC->APB2ENR,PERIPHERALID);
		break;
	default :
		// bus id out of range
		break;
	}
}



void MRCC_vDisableClock(uint8 BUSID, uint8 PERIPHERALID)
{

	switch (BUSID)
	{
	case RCC_AHB1 :
		CLEAR_BIT(RCC->AHB1ENR,PERIPHERALID);
		break;

	case RCC_AHB2 :
		CLEAR_BIT(RCC->AHB2ENR,PERIPHERALID);
		break;

	case RCC_APB1 :
		CLEAR_BIT(RCC->APB1ENR,PERIPHERALID);
		break;

	case RCC_APB2 :
		CLEAR_BIT(RCC->APB2ENR,PERIPHERALID);
		break;
	}


}


