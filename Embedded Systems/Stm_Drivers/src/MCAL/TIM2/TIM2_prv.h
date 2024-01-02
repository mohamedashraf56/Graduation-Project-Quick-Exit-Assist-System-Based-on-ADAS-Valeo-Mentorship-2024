/*
 * TIM2_prv.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_TIM2_TIM2_PRV_H_
#define MCAL_TIM2_TIM2_PRV_H_

#define TIM2_BASE_ADDR  (0X40000000U)

typedef struct
{
	uint32 TIMx_CR1;
	uint32 TIMx_CR2;
	uint32 TIMx_SMCR;
	uint32 TIMx_DIER;
	uint32 TIMx_SR;
	uint32 TIMx_EGR;
	uint32 TIMx_CCMR1;
	uint32 TIMx_CCMR2;
	uint32 TIMx_CCER;
	uint32 TIMx_CNT;
	uint32 TIMx_PSC;
	uint32 TIMx_ARR;
	uint32 reserved0;
	uint32 TIMx_CCR1;
	uint32 TIMx_CCR2;
	uint32 TIMx_CCR3;
	uint32 TIMx_CCR4;
	uint32 reserved1;
	uint32 TIMx_DCR;
	uint32 TIMx_DMAR;
	uint32 TIM2_OR;
	// look at the register descrip in page 375
	uint32 TIM5_OR;
}TIM2_MemMap;



#define TIMER2  ((volatile TIM2_MemMap *)(TIM2_BASE_ADDR))



#endif /* MCAL_TIM2_TIM2_PRV_H_ */
