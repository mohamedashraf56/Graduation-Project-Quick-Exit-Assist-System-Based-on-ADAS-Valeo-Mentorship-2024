/*
 * RCC_cfg.h
 *
 *  Created on: Nov 30, 2023
 *      Author: Sabet & Mamdouh
 *      V 0.01
       */

#ifndef MCAL_RCC_RCC_CFG_H_
#define MCAL_RCC_RCC_CFG_H_

#define ENABLE   (1u)
#define DISABLE   (0u)


#define RCC_HSE_ENABLE     ENABLE
#define RCC_HSI_ENABLE     DISABLE
#define RCC_PLL_ENABLE     DISABLE

#define RCC_CSS_ENABLE     ENABLE
#define RCC_SYS_CLK           HSE



// wrong configuration with (ENABLE) WILL Edit it later
#if RCC_PLL_ENABLE == ENABLE

#define PLL_INPUT_CLK         HSE
// FOR PLLCFGR REGISTER
#define PLLM  12
#define PLLMLOCATION    0

#define PLLN  300
#define PLLNLOCATION    6

#define PLLP  6
#define PLLPLOCATION    16

// NOTE THAT THE EXTERNAL CLK = 25MHZ
// THIS EQUATION to make the PLL output 75MHZ
//to change it note that F = (FIN * PLLN)/(PLLM*PLLP)
#endif

/***************************************************************/

#define APB2_pre_value            APB_pre_0          //(2 , 4 , 8 )


#define APB1_pre_value            APB_pre_0         //(NO,2 , 4 , 8 )


#define AHB_pre_value               AHB_pre_0       //( NO, 2 , 4 ,8 ,16 , 64 , 128 , 256 , 512 )

/****************************************************************/




#endif /* MCAL_RCC_RCC_CFG_H_ */
