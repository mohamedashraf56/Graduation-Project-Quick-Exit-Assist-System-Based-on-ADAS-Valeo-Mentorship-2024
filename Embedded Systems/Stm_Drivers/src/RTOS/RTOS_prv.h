/*
 * RTOS_prv.h
 *
 *  Created on: Dec 27, 2023
 *      Author: Mamdouh
 */

#ifndef RTOS_RTOS_PRV_H_
#define RTOS_RTOS_PRV_H_


typedef struct
{
	void(*TaskHandler)(void);
	uint8 Periodicity;
	uint8 FirstDelay;

}Task;


#endif /* RTOS_RTOS_PRV_H_ */
