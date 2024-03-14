/*
 *TIM10_11_prg.c
 *
 *  Created on: Dec 30, 2023
 *      Author: asabe
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"

#include "../RCC/RCC_int.h"
#include "../NVIC/NVIC_int.h"
#include "../GPIO/GPIO_int_.h"
#include "../TIM10_11_PWM/TIM10_11_cfg.h"
#include "../TIM10_11_PWM/TIM10_11_int.h"
#include "../TIM10_11_PWM/TIM10_11_prv.h"

/* ********************************************************************
 * Name            : TIM10_11_init
 * Description   :  Initialization for Timer 10 , 11  and set AF Timer 10 , 11  mode , Auto reload , prereload mode , Prescaler ,freq
 * Return  		  : NOTHING
 * Argument 1	  : Config struct for Timer Settings
 * Argument 2   : Timer number
 * TYPE       		  : SYNC
 ***********************************************************************/

void TIM10_11_init(TIM10_11_config_struct* PTR_config ,TIM10_11_MemMap *TIMERx )
{
	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOB);
	if (TIMERx== TIMER10)
	{
		RCC_Enable_Clock(RCC_APB2, RCC_TIM10);
		GPIO_Set_Pin_Direction(PORTB, PIN8, GPIO_MODE_ALTFUN);  //for timer 10
		GPIO_Alternate_Function(PORTB, PIN8, 3) ;
	}
	else {
		RCC_Enable_Clock(RCC_APB2, RCC_TIM11);
		GPIO_Set_Pin_Direction(PORTB, PIN9, GPIO_MODE_ALTFUN);  //for timer 11
		GPIO_Alternate_Function(PORTB, PIN9, 3) ;
	}

	SET_BIT(TIMERx->TIM10_11_CR1 , TIM10_11_CR1_ARPE_BIT); // Auto reload , prereload
	SET_BIT(TIMER11->TIM10_11_CCMR1 , TIM10_11_CCMR1_OC1PE_BIT); //, prereload
	INSERST_BITS(TIMER10->TIM10_11_PSC  , 0   ,  16  , PTR_config->TIM10_11_pre_scaler);  // Perscaler
	SET_BIT(TIMERx->TIM10_11_EGR , TIM10_11_EGR_UG_BIT); // Update generation
	INSERST_BITS(TIMERx->TIM10_11_ARR , 0 , 16 , PTR_config->TIM10_11_auto_reload_value);  // freq  / autoreload
}

/* ********************************************************************
 * Name            : TIM10_11_PWM
 * Description   :  Initialization for Timer 10 , 11  for generate PWM
 * Return  		  : NOTHING
 * Argument 1	  : Config struct for Timer Settings
 * Argument 2   : Timer number
 * TYPE       		  : SYNC
 ***********************************************************************/
void TIM10_11_PWM(TIM10_11_config_struct* PTR_config ,TIM10_11_MemMap *TIMERx )
{
	INSERST_BITS(TIMERx->TIM10_11_CCMR1 ,4  , 3 ,0b110);  // PWM_MODE1                                               ```********
	INSERST_BITS(TIMERx->TIM10_11_CCMR1 ,0  , 2 ,0b00);  // output                                                             ~~*******
	CLEAR_BIT(TIMERx->TIM10_11_CCER , TIM10_11_CCER_CC1NP_BIT); // output
	CLEAR_BIT(TIMERx->TIM10_11_CCER , TIM10_11_CCER_CC1P_BIT); // RIsing trigger polarity  if out and thes bit is with  CC1E to chose the trriger capture if input
	SET_BIT(TIMERx->TIM10_11_CCER , TIM10_11_CCER_CC1E_BIT); // Capture/Compare 1 output enable.      ~~~****
	INSERST_BITS(TIMERx->TIM10_11_CCR1 , 0 , 16 , PTR_config->TIM10_11_duty_cycle); // duty
	SET_BIT(TIMERx->TIM10_11_CR1 , TIM10_11_CR1_CEN_BIT);  // TIMER STSRT

}













/*void TIM10_11_Overflow(TIM10_11_config_struct* PTR_config ,TIM10_11_MemMap *TIMERx )
{
	SET_BIT(TIMERx->TIM10_11_DIER , TIM10_11_DIER_UIE_BIT);  // enable interrupt
	SET_BIT(TIMERx->TIM10_11_CR1 , TIM10_11_CR1_CEN_BIT);  // TIMER STSRT
}

void TIMER10_Set_CallBack(void (*ptr)(void))
{
	TIMER10_OF_CB  =  ptr ;
}
void TIMER11_Set_CallBack(void (*ptr)(void))
{
	TIMER11_OF_CB  =  ptr ;
}
void TIM11_IRQHandler(void)
{
	uint8 READ_to_clear;

	READ_to_clear = GET_BIT(TIMER11->TIM10_11_SR,TIM10_11_SR_UIF_BIT);
	CLEAR_BIT(TIMER11->TIM10_11_SR,TIM10_11_SR_UIF_BIT);

	READ_to_clear= GET_BIT(TIMER11->TIM10_11_SR,TIM10_11_SR_CC1IF_BIT);
	CLEAR_BIT(TIMER11->TIM10_11_SR,TIM10_11_SR_CC1IF_BIT);

	READ_to_clear= GET_BIT(TIMER11->TIM10_11_SR,TIM10_11_SR_CC1OF_BIT);
	CLEAR_BIT(TIMER11->TIM10_11_SR,TIM10_11_SR_CC1OF_BIT);


	if(TIMER10_OF_CB != NULL_PTR)
	{
		TIMER11_OF_CB();
	}
}

void TIM10_IRQHandler(void)
{
	uint8 READ_to_clear;

	READ_to_clear = GET_BIT(TIMER10->TIM10_11_SR,TIM10_11_SR_UIF_BIT);
	CLEAR_BIT(TIMER10->TIM10_11_SR,TIM10_11_SR_UIF_BIT);

	READ_to_clear= GET_BIT(TIMER10->TIM10_11_SR,TIM10_11_SR_CC1IF_BIT);
	CLEAR_BIT(TIMER10->TIM10_11_SR,TIM10_11_SR_CC1IF_BIT);

	READ_to_clear= GET_BIT(TIMER10->TIM10_11_SR,TIM10_11_SR_CC1OF_BIT);
	CLEAR_BIT(TIMER10->TIM10_11_SR,TIM10_11_SR_CC1OF_BIT);


	if(TIMER10_OF_CB != NULL_PTR)
	{
		TIMER10_OF_CB();
	}
}*/
