/*
 * SYSTICK_int.h
 *
 *  Created on: Dec 10, 2023
 *      Author: asabe
 */

#ifndef MCAL_SYSTICK_INT_H_
#define MCAL_SYSTICK_INT_H_

void SYSTICK_INIT();
uint32 SYSTICK_READ_CLEAR_FLAG();
void SYSTICK_ENABLE_FUN (void);
void SYSTICK_DISABLE_FUN (void);
void SYSTICK_LOAD_VALUE(uint32 value);
void SYSTICK_UPDATE_TIMER_VALUE(uint32 value);
void SYSTICK_SET_BUSY_WAIT(uint32 value);
void SYSTICK_SET_INTERVAL_SINGEL(uint32 value , void (*fun_call)(void));
void SYSTICK_SET_INTERVAL_MULTI(uint32 value , void (*fun_call)(void));
void SYSTICK_STOP_INTERVAL();
uint32 SYSTICK_GET_ELAPSED_TIME(void);
uint32 SYSTICK_GET_REMAINING_TIME(void);
void _delay_ms(uint32 milliseconds);
void _delay_us(uint32 microseconds);




#endif /* MCAL_SYSTICK_INT_H_ */
