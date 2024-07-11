/*
 * TIM2_int.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Mamdouh
 *      v: 1.00
 */

#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

#define TIMER1_Selected       1

#define TIMER2_Selected       2
#define TIMER3_Selected       3
#define TIMER4_Selected       4
#define TIMER5_Selected       5

#define TIMER9_Selected       9



#define CHANNEL_1             1
#define CHANNEL_2             2
#define CHANNEL_3             3
#define CHANNEL_4             4


#define TIMER_EN_INTERRUPT    1
#define TIMER_DIS_INTERRUPT   0

#define TIMAR_Start           1
#define TIMER_Stop            0

// the interrupt flag register
#define TIM_SR_UIF             0
#define CC1IF                  1
#define CC2IF                  2
#define CC3IF                  3
#define CC4IF                  4

// the interrupt bit enable / disable
#define UIF                    0
// the timer counter enable // disables
#define TIM_CR1_CEN            0


#define ICU_Rising             (0)
#define ICU_Failing            (0b001)
#define ICU_Both               (0b101)


typedef struct
{
	uint8  TIMER_NUM;
	uint32 SET_Psc;
	uint32 SET_Auto_Relaod;
	uint8  SET_Edge_Type;
	uint8  SET_Icu_Channel;
	void(*SET_Timer_Call_Back)(void);

}TIMER_Init_Config_St;




sint8 TIMER_Init(TIMER_Init_Config_St * TIMER_Config_St);

void TIMER_Set_Psc(TIMER_Init_Config_St * TIMER_Config_St);
void TIMER_Set_Auto_Reload(TIMER_Init_Config_St * TIMER_Config_St);
void TIMER_Enable_Interrupt(TIMER_Init_Config_St * TIMER_Config_St,uint8 Mode);
void TIMER_Start_Stop(TIMER_Init_Config_St * TIMER_Config_St,uint8 Mode);

uint32 TIMER_Read_Counter(TIMER_Init_Config_St * TIMER_Config_St);

sint8 TIMER_Set_Call_Back(TIMER_Init_Config_St * TIMER_Config_St);

sint8 TIMER_Clear_Counter(TIMER_Init_Config_St * TIMER_Config_St);

sint8 TIMER_Mode_ICU(TIMER_Init_Config_St * TIMER_Config_St);
// return the result of the TIMx_CCR1 (copy the counter in this time)
uint32 TIMER_ICU_Result(TIMER_Init_Config_St * TIMER_Config_St);


sint8 TIMER_Set_ICU_Edges(TIMER_Init_Config_St * TIMER_Config_St,uint8 Type);


#endif /* MCAL_TIMER_TIMER_INT_H_ */
