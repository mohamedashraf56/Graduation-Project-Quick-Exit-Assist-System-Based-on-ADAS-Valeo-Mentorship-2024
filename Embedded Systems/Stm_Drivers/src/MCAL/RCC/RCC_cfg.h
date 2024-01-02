/*
 * RCC_cfg.h
 *
 *  Created on: Nov 30, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_RCC_RCC_CFG_H_
#define MCAL_RCC_RCC_CFG_H_


#define RCC_HSE_ENABLE     ENABLE
#define RCC_HSI_ENABLE     DISABLE
#define RCC_PLL_ENABLE     DISABLE

#define RCC_CSS_ENABLE     ENABLE
#define RCC_SYS_CLK        RCC_HSE


// FOR PLLCFGR REGISTER
#define PLLM  12
#define PLLMLOCATION    0

#define PLLN  300
#define PLLNLOCATION    6

#define PLLP  6
#define PLLPLOCATION    16

// NOTE THAT THE EXTERNAL CLK = 18MHZ
// THIS EQUATION to make the PLL output 75MHZ
//to change it note that F = (FIN * PLLN)/(PLLM*PLLP)


#endif /* MCAL_RCC_RCC_CFG_H_ */
