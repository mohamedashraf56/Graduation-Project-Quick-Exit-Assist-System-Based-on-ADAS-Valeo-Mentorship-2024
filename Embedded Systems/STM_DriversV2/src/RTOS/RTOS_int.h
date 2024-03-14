/*
 * RTOS_int.h
 *
 *  Created on: Dec 18, 2023
 *      Author: asabe
 */

#ifndef RTOS_RTOS_INT_H_
#define RTOS_RTOS_INT_H_

#include "../lip/std_types.h"

void RTOS_voidStartOS();
uint8 RTOS_u8CreateTask (  void(*Copy_Handler)(void) , uint16 Copy_u32Periodicity, uint8 Copy_u8Priority , uint8 Copy_FirstD  );
uint8 RTOS_u8DeleteTask(uint8 Copy_u8Priority) ;
uint8 RTOS_u8SuspendTask(uint8 Copy_u8Priority);
uint8 RTOS_u8ResumeTask(uint8 Copy_u8Priority);






#endif /* RTOS_RTOS_INT_H_ */
