/*
 * NVIC_int.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Sabet & Mamdouh
 *       version  0.01
 */

#ifndef MCAL_NVIC_NVIC_INT_H_
#define MCAL_NVIC_NVIC_INT_H_


typedef enum{

	NVIC_MemManage =-7,
	NVIC_BusFault,
	NVIC_UsageFault,
	NVIC_SVCall,
	NVIC_Debug_Monitor,
	NVIC_PendSV,
	NVIC_Systick,

	 NVIC_WWDG,
	 NVIC_EXTI16_PVD,
	 NVIC_EXTI21_TAMP_STAMP,
	 NVIC_EXTI22_RTC_WKUP,
	 NVIC_FLASH,
	 NVIC_RCC,
	 NVIC_EXTI0,
	 NVIC_EXTI1,
	 NVIC_EXTI2,
	 NVIC_EXTI3,
	 NVIC_EXTI4,
	 NVIC_DMA1_Stream0,
	 NVIC_DMA1_Stream1 ,
	 NVIC_DMA1_Stream2,
	 NVIC_DMA1_Stream3,
	 NVIC_DMA1_Stream4,
	 NVIC_DMA1_Stream5,
	 NVIC_DMA1_Stream6,
	 NVIC_ADC,
	 NVIC_EXTI9_5=23,
	 NVIC_TIM1_BRK_TIM9,
	 NVIC_TIM1_UP_TIM10,
	 NVIC_TIM1_TRG_COM_TIM11,
	 NVIC_TIM1_CC,
	 NVIC_TIM2,
	 NVIC_TIM3,
	 NVIC_TIM4,
	 NVIC_I2C1_EV,
	 NVIC_I2C1_ER,
	 NVIC_I2C2_EV,
	 NVIC_I2C2_ER,
	 NVIC_SPI1,
	 NVIC_SPI2,
	 NVIC_USART1,
	 NVIC_USART2,
	 NVIC_EXTI15_10=40,
	 NVIC_EXTI17_RTC_Alarm,
	 NVIC_EXTI18_OTG_FS_WKUP,
	 NVIC_DMA1_Stream7=47,
	 NVIC_SDIO=49,
	 NVIC_TIM5,
	 NVIC_SPI3,
	 NVIC_DMA2_Stream0=56,
	 NVIC_DMA2_Stream1,
	 NVIC_DMA2_Stream2,
	 NVIC_DMA2_Stream3,
	 NVIC_DMA2_Stream4,
	 NVIC_OTG_FS=67,
	 NVIC_DMA2_Stream5,
	 NVIC_DMA2_Stream6,
	 NVIC_DMA2_Stream7,
	 NVIC_USART6,
	 NVIC_I2C3_EV,
	 NVIC_I2C3_ER,
	 NVIC_FPU=81,
	 NVIC_SPI4=84,

}interrupt_ID_enum;

void NVIC_En_Interrupt(interrupt_ID_enum interrupt_num);
void NVIC_Dis_Interrupt (interrupt_ID_enum interrupt_num);
void NVIC_Set_Pending_Flag (interrupt_ID_enum interrupt_num);
void NVIC_Clear_Pending_Flag (interrupt_ID_enum interrupt_num);
uint8 NVIC_Read_Interrupt_Active(interrupt_ID_enum interrupt_num);
void NVIC_Set_Priority_Cfg (void);
void NVIC_Set_Priority  (interrupt_ID_enum interrupt_num , uint8 group , uint8 subgroup );




#endif /* MCAL_NVIC_NVIC_INT_H_ */
