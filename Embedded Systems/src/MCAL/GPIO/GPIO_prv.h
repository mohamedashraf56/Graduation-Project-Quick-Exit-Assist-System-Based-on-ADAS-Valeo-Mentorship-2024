/*
 * GPIO_prv.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Mamdouh & Sabet
 *      v   0.01
 *
  */

#ifndef MCAL_GPIO_GPIO_PRV_H_
#define MCAL_GPIO_GPIO_PRV_H_

#define GPIOA_BASE_ADDR  0X40020000
#define GPIOB_BASE_ADDR  0X40020400
#define GPIOC_BASE_ADDR  0X40020800



typedef struct
{
	uint32 MODER;
	uint32 OTYPER;
	uint32 OSPEEDR;
	uint32 PUPDR;
	uint32 IDR;
	uint32 ODR;
	uint32 BSRR;
	uint32 LCKR;
	uint32 AFRL;
	uint32 AFRH;
}GPIO_MemMap_t;


#define GPIO_MODE_RANGE    2
#define GPIO_PUPD_RANGE   2
// for ALFUNCTION
#define AFRH_RANGE_BITS  4
#define AFRL_RANGE_BITS  4


#define PORT_LOCKED    1
#define PORT_UNLOCKED  0

#define ALL_PINS_LOCKED  (0XFFFF)

#define GPIOA ((volatile GPIO_MemMap_t *)(GPIOA_BASE_ADDR))
#define GPIOB ((volatile GPIO_MemMap_t *)(GPIOB_BASE_ADDR))
#define GPIOC ((volatile GPIO_MemMap_t *)(GPIOC_BASE_ADDR))


#endif /* MCAL_GPIO_GPIO_PRV_H_ */
