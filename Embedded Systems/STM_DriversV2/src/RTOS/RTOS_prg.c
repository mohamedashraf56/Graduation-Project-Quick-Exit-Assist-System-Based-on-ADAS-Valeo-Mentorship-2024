/*
 * RTOS_prg.c
 *
 *  Created on: Dec 18, 2023
 *      Author: asabe
 */

#include "../lip/std_types.h"
#include "../lip/common_macros.h"

#include "../MCAL/SYSTICK/SYSTICK_int.h"

#include "RTOS_int.h"
#include "RTOS_cfg.h"
#include "RTOS_prv.h"
void Scheduler(void);



Task SystemTasks[MAX_NUM_OF_TASKS] = {0};         // Ready queue
uint32   TaskTiming [MAX_NUM_OF_TASKS];     //note that every element take struct' task' so it may over flow

Task Empty = {0};

void RTOS_voidStartOS()
{
	SYSTICK_SET_INTERVAL_MULTI(TickTime,Scheduler) ;
}

uint8 RTOS_u8CreateTask (  void(*Copy_Handler)(void) , uint16 Copy_u16Periodicity, uint8 Copy_u8Priority , uint8 Copy_FirstD  )
{
	uint8 Local_ErrorState = 0;

	/* Verify that the priority index within the correct range */
	if (Copy_u8Priority < MAX_NUM_OF_TASKS)
	{

		if (SystemTasks[Copy_u8Priority].TaskHandler == 0)
		{
			SystemTasks[Copy_u8Priority].TaskHandler  = Copy_Handler;
			SystemTasks[Copy_u8Priority].Periodicity  = Copy_u16Periodicity;

			TaskTiming [Copy_u8Priority]                     = Copy_FirstD;
			SystemTasks[Copy_u8Priority].TaskRunState = Running;
		}

		else
		{
			/* The required priority is alread reserved */
			Local_ErrorState = 2;
		}
	}

	else
	{
		/* Wrong priority */
		Local_ErrorState = 1;

	}

	return Local_ErrorState;
}


void Scheduler(void)
{
	uint8 Local_Counter=0;

	/* Loop on all Taks */
	for (Local_Counter =0; Local_Counter < MAX_NUM_OF_TASKS; Local_Counter++)
	{
		/* Is there a registered task ... ? */
		if (SystemTasks[Local_Counter].TaskHandler != 0)
		{
			if (SystemTasks[Local_Counter].TaskRunState == Running )
			{
				if (TaskTiming[Local_Counter] == 0)
				{
					/* Run the task */
					SystemTasks[Local_Counter].TaskHandler();



					/* Reload the periodicity */
					TaskTiming[Local_Counter] = SystemTasks[Local_Counter].Periodicity  ;
				}

				else
				{
					TaskTiming[Local_Counter]--;
				}
			}
		}
	}
}

uint8 RTOS_u8DeleteTask(uint8 Copy_u8Priority)
{
	uint8 Local_ErrorState = 0;
	if (SystemTasks[Copy_u8Priority].TaskHandler != 0)
	{
		/* Task exist, execute the removal */
		SystemTasks[Copy_u8Priority] = Empty;
	}

	else
	{
		/* Task not exist */
		Local_ErrorState = 1;
	}

	return Local_ErrorState;

}


uint8 RTOS_u8SuspendTask(uint8 Copy_u8Priority)
{
	uint8 Local_ErrorState = 0;
	if (SystemTasks[Copy_u8Priority].TaskHandler != 0)
	{

		SystemTasks[Copy_u8Priority].TaskRunState = Suspended;
	}

	else
	{
		/* Task not exist */
		Local_ErrorState = 1;
	}

	return Local_ErrorState;
}

uint8 RTOS_u8ResumeTask(uint8 Copy_u8Priority)
{
	uint8 Local_ErrorState = 0;
	if (SystemTasks[Copy_u8Priority].TaskHandler != 0)
	{

		SystemTasks[Copy_u8Priority].TaskRunState = Running;
	}

	else
	{
		/* Task not exist */
		Local_ErrorState = 1;
	}

	return Local_ErrorState;
}



