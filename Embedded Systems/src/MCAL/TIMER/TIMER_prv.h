/*
 * TIM2_prv.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Mamdouh
 *      v: 1.00
 */

#ifndef MCAL_TIMER_TIMER_PRV_H_
#define MCAL_TIMER_TIMER_PRV_H_

#define TIM1_BASE_ADDR  (0X40010000U)
#define TIM2_BASE_ADDR  (0X40000000U)
#define TIM3_BASE_ADDR  (0X40000400U)
#define TIM4_BASE_ADDR  (0X40000800U)
#define TIM5_BASE_ADDR  (0X40000C00U)
#define TIM9_BASE_ADDR  (0x40014000U)


typedef struct
{
	uint32 TIMx_CR1;
	uint32 TIMx_CR2;
	uint32 TIMx_SMCR;
	uint32 TIMx_DIER;
	uint32 TIMx_SR ;
	uint32 TIMx_EGR;
	uint32 TIMx_CCMR1;
	uint32 TIMx_CCMR2;
	uint32 TIMx_CCER;
	uint32 TIMx_CNT;
	uint32 TIMx_PSC;
	uint32 TIMx_ARR;
	uint32 TIMx_RCR;
	uint32 TIMx_CCR1;
	uint32 TIMx_CCR2;
	uint32 TIMx_CCR3;
	uint32 TIMx_CCR4;
	uint32 TIMx_BDTR;
	uint32 TIMx_DCR;
	uint32 TIMx_DMAR;
}TIM1_MemMap;

typedef struct
{
	uint32 TIMx_CR1;
	uint32 TIMx_CR2;
	uint32 TIMx_SMCR;
	uint32 TIMx_DIER;
	uint32 TIMx_SR ;
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

typedef struct
{
	uint32 TIMx_CR1;
	uint32 Reserved1;
	uint32 TIMx_SMCR;
	uint32 TIMx_DIER;
	uint32 TIMx_SR ;
	uint32 TIMx_EGR;
	uint32 TIMx_CCMR1;
	uint32 Reserved2;
	uint32 TIMx_CCER;
	uint32 TIMx_CNT;
	uint32 TIMx_PSC;
	uint32 TIMx_ARR;
	uint32 Reserved3;
	uint32 TIMx_CCR1;
	uint32 TIMx_CCR2;
	uint32 Reserved4[5];
}TIM9_MemMap;

#define TIMER1  ((volatile TIM1_MemMap *)(TIM1_BASE_ADDR))

#define TIMER2  ((volatile TIM2_MemMap *)(TIM2_BASE_ADDR))
#define TIMER3  ((volatile TIM2_MemMap *)(TIM3_BASE_ADDR))
#define TIMER4  ((volatile TIM2_MemMap *)(TIM4_BASE_ADDR))
#define TIMER5  ((volatile TIM2_MemMap *)(TIM5_BASE_ADDR))

#define TIMER9  ((volatile TIM9_MemMap *)(TIM9_BASE_ADDR))




#endif /* MCAL_TIMER_TIMER_PRV_H_ */
