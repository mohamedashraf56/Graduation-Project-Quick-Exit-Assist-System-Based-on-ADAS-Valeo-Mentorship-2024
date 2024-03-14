/*
 * TIM10_11_int.h
 *
 *  Created on: Dec 30, 2023
 *      Author: asabe
 */

#ifndef MCAL_TIM10_11_PWM_TIM10_11_INT_H_
#define MCAL_TIM10_11_PWM_TIM10_11_INT_H_

#define TIM10_BASE_ADDR  (0x40014400)
#define TIM11_BASE_ADDR  (0x40014800)


typedef struct
{
	uint32 TIM10_11_CR1;                 //0x00
	uint32 reserved;                            //0x04
	uint32 TIM10_11_SMCR;                // 0x08
	uint32 TIM10_11_DIER;                  //0x0C
	uint32 TIM10_11_SR;                 //0X10
	uint32 TIM10_11_EGR;              //0X14
	uint32 TIM10_11_CCMR1;         //0X18
	uint32 reserved0;                        //0X1C
	uint32 TIM10_11_CCER;          //0X20
	uint32 TIM10_11_CNT;           //0X24
	uint32 TIM10_11_PSC;              //0X28
	uint32 TIM10_11_ARR;            //0X2C
	uint32 reserved1;                     //0X30
	uint32 TIM10_11_CCR1;                 //0X34
	uint32 reserved2[7];            //
	uint32 TIM10_11_OR;
}TIM10_11_MemMap;

#define TIMER10  (( TIM10_11_MemMap *)(TIM10_BASE_ADDR))
#define TIMER11  (( TIM10_11_MemMap *)(TIM11_BASE_ADDR))


typedef struct
{
	uint16  TIM10_11_pre_scaler ;
	uint16  TIM10_11_auto_reload_value ;
	uint16  TIM10_11_duty_cycle;
}TIM10_11_config_struct;




//void  TIMER2_CHANNEL_Configs(channel_config_struct  *ptr);

void TIM10_11_init(TIM10_11_config_struct* PTR_config ,TIM10_11_MemMap *TIMERx );
void TIM10_11_PWM(TIM10_11_config_struct* PTR_config ,TIM10_11_MemMap *TIMERx );
void TIM10_11_Overflow(TIM10_11_config_struct* PTR_config ,TIM10_11_MemMap *TIMERx ) ;
void TIMER10_Set_CallBack(void (*ptr)(void));
void TIMER11_Set_CallBack(void (*ptr)(void));



uint32 TIMER_geter (void) ;



#endif /* MCAL_TIM10_11_PWM_TIM10_11_INT_H_ */
