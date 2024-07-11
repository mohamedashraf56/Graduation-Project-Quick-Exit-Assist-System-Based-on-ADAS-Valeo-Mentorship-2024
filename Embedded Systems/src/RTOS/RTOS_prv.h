/*
 * RTOS_prv.h
 *
 *  Created on: Dec 18, 2023
 *      Author: asabe
 */

#ifndef RTOS_RTOS_PRV_H_
#define RTOS_RTOS_PRV_H_


typedef enum
{
	Suspended,
	Running
}RunState;


typedef struct
{
	void (*TaskHandler)(void)    ;
	uint16        Periodicity        ;
	uint8        FirstDelay         ;
	RunState  TaskRunState       ;
}Task;




#endif /* RTOS_RTOS_PRV_H_ */
