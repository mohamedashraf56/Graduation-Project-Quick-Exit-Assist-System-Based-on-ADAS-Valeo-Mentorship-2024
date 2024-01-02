/*
 * NVIC_int.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_NVIC_NVIC_INT_H_
#define MCAL_NVIC_NVIC_INT_H_


// Group selection bits change it from NVIC_cfg
#define GRUOP_4BITS    (0b000)
#define GRUOP_3BITS    (0b100)
#define GRUOP_2BITS    (0b101)
#define GRUOP_1BITS    (0b110)
#define GRUOP_0BITS    (0b111)

// this is the location of peripheral priority in vector table
enum{

	Memory_Management_Fault = -7,
	Bus_Fault,
	Usage_Fault,
	SVCall,
	PendSV,
	SysTick_Exception,

	 WWDG = 0,
	 EXTI16_PVD,
	 EXTI21_TAMP_STAMP,
	 EXTI22_RTC_WKUP,
	 FLASH,
	 RCC,
	 EXTI0,
	 EXTI1,
	 EXTI2,
	 EXTI3,
	 EXTI4,
	 DMA1_Stream0,
	 DMA1_Stream1 ,
	 DMA1_Stream2,
	 DMA1_Stream3,
	 DMA1_Stream4,
	 DMA1_Stream5,
	 DMA1_Stream6,
	 ADC,
	 EXTI9_5=23,
	 TIM1_BRK_TIM9,
	 TIM1_UP_TIM10,
	 TIM1_TRG_COM_TIM11,
	 TIM1_CC,
	 TIM2,
	 TIM3,
	 TIM4,
	 I2C1_EV,
	 I2C1_ER,
	 I2C2_EV,
	 I2C2_ER,
	 SPI1,
	 SPI2,
	 USART1,
	 USART2,
	 EXTI15_10=40,
	 EXTI17_RTC_Alarm,
	 EXTI18_OTG_FS_WKUP,
	 DMA1_Stream7=47,
	 SDIO=49,
	 TIM5,
	 SPI3,
	 DMA2_Stream0=56,
	 DMA2_Stream1,
	 DMA2_Stream2,
	 DMA2_Stream3,
	 DMA2_Stream4,
	 OTG_FS=67,
	 DMA2_Stream5,
	 DMA2_Stream6,
	 DMA2_Stream7,
	 USART6,
	 I2C3_EV,
	 I2C3_ER,
	 FPU=81,
	 SPI4=84,
};

void Nvic_En_Interrupt(uint8 Interrupt_Number);
void Nvic_Dis_Interrupt(uint8 Interrupt_Number);
uint8 Nvic_Read_Interrupt( uint8 Interrupt_Number);

void Nvic_Set_Pending_Flag(uint8 Interrupt_Number);
void Nvic_Clear_Pending_Flag( uint8 Interrupt_Number);
uint8 Nvic_Read_Pending_Flag(uint8 Interrupt_Number);

uint8 Nvic_Read_Active_Flag(uint8 Interrupt_Number);


/**********************************************************
 * Function : Nvic_SetPriorityCfg
 * Parameters : Priority Options
 * return : Nothing
 * Descprtion : this function sets the group and subgroup priority options
 * ********************************************************
 * Options : GPRUOP-4BITS ,GPRUOP-3BITS ,GPRUOP-2BITS, GPRUOP-1BITS ....
 * ********************************************************
 */
void Nvic_SetPriorityCfg(uint8 u8Priority_Option);


void Nvic_SetPriority(sint8 s8INTID,uint8 u8GroupPriority,uint8 u8SubPriority);




#endif /* MCAL_NVIC_NVIC_INT_H_ */
