/*
 * ADC_prog.c
 *
 *  Created on: Jan 26, 2024
 *      Author: asabe
 */
#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "ADC_cfg.h"
#include "ADC_init.h"
#include "ADC_priv.h"
#include "../RCC/RCC_int.h"
#include "../NVIC/NVIC_int.h"
#include "../GPIO/GPIO_int_.h"

void (*ADC_CB_FUN)(void) = NULL_PTR ;

void ADC_init (void)
{
	RCC_Init();
	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOA);
	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOB);
	RCC_Enable_Clock(RCC_APB2, RCC_ADC1);
	NVIC_En_Interrupt(NVIC_ADC);

	INSERST_BITS(ADC->CR1,ADC_CR1_EOCIE_BIT, 1 , ADC_INTERRUPT_EN);   // set ADC interrupt state
	INSERST_BITS(ADC->CR1,ADC_CR1_RES_BIT0, 2 , ADC_Resolution);   // set ADC in 12 bit mode
	INSERST_BITS(ADC->CR2,ADC_CR2_EXTEN_BIT0, 2 , 0);          // no External trigger
	CLEAR_BIT (ADC->CR2 , ADC_CR2_ALIGN_BIT) ;                      // Data alignment (right)
	INSERST_BITS(ADC->CCR,ADC_CR2_ADCPRE_BIT0 , 2 , ADC_PRESCALER);   // SET PRE SCALER*/
	SET_BIT(ADC->CR2,ADC_CR2_ADON_BIT);   // ENABLE ADC

}

void ADC_CHANIL_CONFIG(uint8 channel_num)
{
	if (channel_num>10)
	{
		return ;
	}

	else {
		if (channel_num<=7)
		{
			GPIO_Set_Pin_Direction(PORTA, channel_num, GPIO_MODE_ANALOG); // channels on port A
		}
		else if (channel_num==8)
		{
			GPIO_Set_Pin_Direction(PORTB, 0, GPIO_MODE_ANALOG) ;        // channel on port B

		}
		else if (channel_num==9)
		{
			GPIO_Set_Pin_Direction(PORTB, 1 ,  GPIO_MODE_ANALOG);        // channel on port B
		}

	}

}

uint32 ADC_Get_Value_Sync (uint8 channel_num)
{

	INSERST_BITS(ADC->SQR[2],0 , 5 , channel_num);   // make channel as sequence 1 to execute first

	//start conversion and slect channel
	SET_BIT(ADC->CR2 , ADC_CR2_SWSTART_BIT) ;

//wait to end of conversion
	while(BIT_IS_CLEAR(ADC->SR,ADC_SR_EOC_BIT) );


	//clear end of conversion flag
	CLEAR_BIT(ADC->SR,ADC_SR_EOC_BIT) ;

//	 return ADC Data
	return ADC->DR ;
}

void ADC_Interrupt_CB (void(*ptr)(void))
{

		if (ADC_CB_FUN==NULL_PTR)
		{
			ADC_CB_FUN=ptr;
		}
		else
		{
                 // DO nothing
		}

}

void  ADC_Get_Value_Async(uint8 channel_num)
{

	INSERST_BITS(ADC->SQR[2],0 , 5 , channel_num);   // make channel as sequence 1 to execute first

	//start conversion and slect channel
	SET_BIT(ADC->CR2 , ADC_CR2_SWSTART_BIT) ;


}

void ADC_IRQHandler(void)
{
	if (ADC_CB_FUN != NULL_PTR)
	{
		ADC_CB_FUN () ;

		/* Clear Regular channel end of conversion */
		CLEAR_BIT(ADC->SR , ADC_SR_EOC_BIT) ;
	}
}

uint16 ADC_Get_Value ()
{
	return ADC->DR ;
}

