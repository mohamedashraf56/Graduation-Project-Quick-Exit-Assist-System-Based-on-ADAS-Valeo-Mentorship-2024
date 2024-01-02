/*
 * RTOS_int.h
 *
 *  Created on: Dec 27, 2023
 *      Author: Mamdouh
 */

#ifndef RTOS_RTOS_INT_H_
#define RTOS_RTOS_INT_H_



uint8 RTOS_u8CreateTask( void(*Copy_Handler)(void) , uint8 Copy_u8Periodicity, uint8 Copy_u8Priority , uint8 Copy_FirstDelay);



void Scheduler(void);




#endif /* RTOS_RTOS_INT_H_ */
