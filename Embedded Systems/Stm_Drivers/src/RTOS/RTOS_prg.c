/*
 * RTOS_prg.c
 *
 *  Created on: Dec 27, 2023
 *      Author: Mamdouh
 */

#include "../lip/std_types.h"
#include "../lip/common_macros.h"

#include "../MCAL/SYSTICK/SYSTICK_int.h"

#include "RTOS_cfg.h"
#include "RTOS_int.h"
#include "RTOS_prv.h"


Task SystemTasks[Number_Of_Tasks] = {0};

uint8 TaskTiming[Number_Of_Tasks] = {0};

/* ********************************************************************
 * Name     : RTOS_u8CreateTask
 * function : copy the address of function in main to SYSTICK_CALLBack
 *          : which if called in ISR
 * Input1    : FUNCTION ADDRESS (Func Name)
 * Return   : NOTHING
 **********************************************************************/
uint8 RTOS_u8CreateTask( void(*Copy_Handler)(void) , uint8 Copy_u8Periodicity, uint8 Copy_u8Priority , uint8 Copy_FirstDelay )
{
	uint8 Local_state = 0;
	// verify if the priority index in the correct range
	if(Copy_u8Priority < Number_Of_Tasks)
	{
 	    if(SystemTasks[Copy_u8Priority].TaskHandler == 0)
 	    {
 	    	// COPY the address of the function (task) in the index of system tasks
		    SystemTasks[Copy_u8Priority].TaskHandler = Copy_Handler;
		    // Copy the task Priority to the index
		    SystemTasks[Copy_u8Priority].Periodicity = Copy_u8Periodicity;
		    /* copy First delay only one time to the
		     *  Task timing for the first time
		     *  for the dynamic design
		     */
		    TaskTiming[Copy_u8Priority] = Copy_FirstDelay;
	    }
 	    else
 	    {
 	    	// this location of task is reserved
 	    	Local_state = 2;
 	    }
	}
	else
	{
		// wrong priority
		Local_state = 1;
	}



	return Local_state;
}






/* ********************************************************************
 * Name     : Scheduler
 * function : copy the address of function in main to SYSTICK_CALLBack
 *          : which if called in ISR
 * Input1    : FUNCTION ADDRESS (Func Name)
 * Return   : NOTHING
 **********************************************************************/
void Scheduler(void)
{

	uint8 Local_Counter = 0;
	// loop on all tasks
	for(Local_Counter = 0 ; Local_Counter < Number_Of_Tasks; Local_Counter++)
	{
		// check if the task is found or not found
		if(SystemTasks[Local_Counter].TaskHandler != 0)
		{
			// checking if its time to call
			if(TaskTiming[Local_Counter] == 0)
			{
				// calling the task (Run the task)
				SystemTasks[Local_Counter].TaskHandler;
				// we need to update the tasktiming
				// copy the Periodicity from the systemtasks struct to the tasktiming
				TaskTiming[Local_Counter] = SystemTasks[Local_Counter].Periodicity;
			}
			else
			{
				TaskTiming[Local_Counter]--;
			}
		}
	}
}











