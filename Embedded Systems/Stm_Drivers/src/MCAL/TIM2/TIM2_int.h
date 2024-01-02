/*
 * TIM2_int.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_TIM2_TIM2_INT_H_
#define MCAL_TIM2_TIM2_INT_H_


#define TIMER2_EN_INTERRUPT    1
#define TIMER2_DIS_INTERRUPT   0

#define TIMAR2_Start           1
#define TIMER2_Stop            0

// the interrupt flag register
#define TIM_SR_UIF             0
#define CC1IF                  1
// the interrupt bit enable / disable
#define UIF                    0
// the timer counter enable // disables
#define TIM_CR1_CEN            0


#define ICU_Rising             (0)
#define ICU_Failing            (0b001)
#define ICU_Both               (0b101)



void TIMER2_Set_PSC(uint32 PRESCALER);
void TIMER2_Set_Auto_Reload(uint32 Value);
void TIMER2_Enable_Interrupt(uint8 Value);
void TIMER2_Start_Stop(uint8 Mode);

uint32 TIMER2_Read_Counter(void);

void TIMER2_Set_Call_Back(void(*PTR_CALL_BACK)(void));

void TIMER2_Clear_Counter(void);

void TIMER2_ICU(void);
// return the result of the TIMx_CCR1 (copy the counter in this time)
uint32 TIMER2_ICU_Result(void);


void TIMER2_ICU_Edges(uint8 Type);


#endif /* MCAL_TIM2_TIM2_INT_H_ */
