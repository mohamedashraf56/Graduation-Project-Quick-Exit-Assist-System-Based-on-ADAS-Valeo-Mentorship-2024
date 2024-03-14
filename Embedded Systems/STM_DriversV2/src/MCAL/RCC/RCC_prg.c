/*
 * RCC.c
 *
 *  Created on: Nov 29, 2023
 *      Author: Sabet & Mamdouh
 *      V 0.01
 *       */
#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "RCC_cfg.h"
#include "RCC_int.h"
#include "RCC_prv.h"


void RCC_Init(void)
{
#if (RCC_CSS_ENABLE) == ENABLE
	//1- CSS (ON/OF)
	SET_BIT(RCC->CR,CSSON); // CSS IS ON
#endif

#if  RCC_PLL_ENABLE == ENABLE
	SET_BIT(RCC->CR,PLLON);
#endif
	// 2- HSE_BYP (ON/OF)
	CLEAR_BIT(RCC->CR,HSEBYP);// OSCILLATOR NOT BYPASSED

	// * 3- SELECT SYSCLK SWITCH (HSI/HSE/PLL)
	//
	INSERST_BITS(RCC->CFGR,SW0,2,RCC_SYS_CLK);

	//4- BUS PRESCALER
	// 0 presents to no division look the data sheet
	// AHB clock divided 2 look the Register description page 109
	INSERST_BITS(RCC->CFGR,HPRE0,4,AHB_pre_value);
	//APB2 clock not divided
	INSERST_BITS(RCC->CFGR,PPRE20,3,APB2_pre_value);
	// HPRE: APB1 prescaler // no divided
	INSERST_BITS(RCC->CFGR,PPRE10,3,APB1_pre_value);

	//5- PLL CONFIGRATION
#if  RCC_PLL_ENABLE == ENABLE
#if   PLLM <= 63 && PLLM >=2 // THIS CONDITION FROM DATA SHEET
   #if  PLLP == 2 || PLLP == 4 || PLLP == 6 || PLLP == 8
     #if PLLN >= 192 && PLLN <= 432

#if PLL_INPUT_CLK == HSE
	SET_BIT(RCC->PLLCFGR,PLLSRC);
#endif
	// SET PLLM & PLLP & PLLN WITH A DEFFRENT VALUES TO CONFIG THE PLL

	INSERST_BITS(RCC->PLLCFGR,PLLMLOCATION,6,PLLM);
	INSERST_BITS(RCC->PLLCFGR,PLLNLOCATION,9,PLLN);
	INSERST_BITS(RCC->PLLCFGR,PLLPLOCATION,2,PLLP);

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
void RCC_Enable_Clock(BUSID_ENUM BUSID, uint8 PERIPHERALID)
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



void RCC_Disable_Clock(BUSID_ENUM BUSID, uint8 PERIPHERALID)
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





