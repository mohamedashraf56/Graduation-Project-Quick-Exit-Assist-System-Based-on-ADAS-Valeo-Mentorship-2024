/*
 * SYSTICK_prg.c
 *
 *  Created on: Dec 10, 2023
 *      Author: asabe
 */
#include "../../lip/common_macros.h"
#include "../../lip/std_types.h"

#include "SYSTICK_int.h"
#include "SYSTICK_cfg.h"
#include "SYSTICK_prv.h"

static  void (*call_back)(void) = NULL_PTR ;
static uint8 flag_interval =0 ;
void SysTick_Handler(void)
{
	if (call_back !=NULL_PTR )
	{
		if (flag_interval)
				   {
			                 call_back();
			                 CLEAR_BIT((SYSTICK->CTRL),CTR_TICKINT); //disable interrupt bit
			         }
     }
        call_back();
}


/************************************************************************************************/
/* Function Name : SYSTICK_INIT                                                                                                    */
/* Description : Inilization of SYSTICK Source                                                                               */
/* Fun. Return : void                                                                                                                         */
/************************************************************************************************/
void SYSTICK_INIT()
{
	//(SYSTICK->CTRL)=0; //reset the old value

	(SYSTICK->CTRL) |=( SYSTICK_INTERRUPT <<CTR_TICKINT);
	(SYSTICK->CTRL) |=( (SYSTICK_CLK) <<CTR_CLKSOURCE);
	(SYSTICK->CTRL) |=( SYSTICK_ENABLE <<CTR_ENABLE);
}

/******************************************************************************************************/
/* Function Name : SYSTICK_SET_BUSY_WAIT                                                                                         */
/* Description : Delay for Given Time (depend on the value of ticks in LOAD reg and the clock)       */
/* Fun. Argument1: Copy_u32TimeMs                                                                                                      */
/* Fun. Return : void                                                                                                                                    */
/*******************************************************************************************************/

void SYSTICK_SET_BUSY_WAIT(uint32 value)
{
	CLEAR_BIT((SYSTICK->CTRL),CTR_ENABLE);

	(SYSTICK->CTRL) |=( (SYSTICK_CLK) <<CTR_CLKSOURCE);


	(SYSTICK->VAL)=0 ;  //clear timer
	if( value < (1<<24) )
	{
	   (SYSTICK->LOAD)=value ;
	}
	else {
		 (SYSTICK->LOAD)=0 ; //wrong value
	}

	(SYSTICK->CTRL)|=( 1 <<CTR_ENABLE);

	while (GET_BIT((SYSTICK->CTRL),(CTR_COUNTFLAG))!=1);  // stuck in function until flag is set
	CLEAR_BIT((SYSTICK->CTRL),CTR_ENABLE);

}

/************************************************************************************************/
/* Function Name : SYSTICK_READ_CLEAR_FLAG                                                                          */
/* Description : Read the value of flag to clear it                                                                          */
/* Fun. Return : void                                                                                                                         */
/************************************************************************************************/

uint32 SYSTICK_READ_CLEAR_FLAG()
{
	return (GET_BIT ( (SYSTICK->CTRL),(CTR_COUNTFLAG) ) );
}

/************************************************************************************************/
/* Function Name : SYSTICK_DINIT                                                                                                */
/* Description : RESET all SYSTICK settings                                                                                    */
/* Fun. Return : uint32                                                                                                                     */
/************************************************************************************************/

void SYSTICK_DINIT()
{
	 (SYSTICK->CTRL)=0;
     (SYSTICK->LOAD)=0 ;
     (SYSTICK->VAL)=0 ;
}

/************************************************************************************************/
/* Function Name : SYSTICK_ENABLE_FUN                                                                                   */
/* Description : set bit in CTRL REG that enable the SYSTICK                                                       */
/* Fun. Return : void                                                                                                                         */
/************************************************************************************************/

void SYSTICK_ENABLE_FUN (void)
{
	(SYSTICK->CTRL)|=( 1 <<CTR_ENABLE);
}

/************************************************************************************************/
/* Function Name : SYSTICK_DISABLE_FUN                                                                                   */
/* Description : CLEAR bit in CTRL REG that enable the SYSTICK                                                  */
/* Fun. Argument1: value of LOAD REG                                                                                          */
/* Fun. Return : void                                                                                                                         */
/************************************************************************************************/

void SYSTICK_DISABLE_FUN (void)
{
	CLEAR_BIT((SYSTICK->CTRL),CTR_ENABLE);
}

/************************************************************************************************/
/* Function Name : SYSTICK_LOAD_VALUE                                                                                   */
/* Description : set value in LOAD REG                                                                                          */
/* Fun. Argument1: value of LOAD REG                                                                                          */
/* Fun. Return : void                                                                                                                         */
/************************************************************************************************/

void SYSTICK_LOAD_VALUE(uint32 value)
{
	if( value < (1<<24) )
	{
	   (SYSTICK->LOAD)=value ;
	}
	else {
		 (SYSTICK->LOAD)=0 ; //wrong value
	}
}

/******************************************************************************************************/
/* Function Name : SYSTICK_UPDATE_TIMER_VALUE                                                                             */
/* Description : UPDATE value of  VAL REG in the runtime                                                         	       */
/* Fun. Argument1: value of LOAD REG                                                                                                    */
/* Fun. Return : void                                                                                                                                    */
/*******************************************************************************************************/

void SYSTICK_UPDATE_TIMER_VALUE(uint32 value)
{
	(SYSTICK->VAL)=0 ;         //clear timer

	if( value < (1<<24) )  // load new value ;
	{
	   (SYSTICK->LOAD)=value ;
	}
	else {
		 (SYSTICK->LOAD)=0 ; //wrong value
	}
	(SYSTICK->CTRL)|=( SYSTICK_ENABLE <<CTR_ENABLE);
}

/******************************************************************************************************/
/* Function Name : SYSTICK_SET_INTERVAL_SINGEL                                                                              */
/* Description : call a specific function after the timer ends just one call                                     	        */
/* Fun. Argument1: value of LOAD REG                                                    										       	*/
/* Fun. Argument  :   function name (pointer)                                                                            			    */
/* Fun. Return : void                                                                                                                                   */
/******************************************************************************************************/

void SYSTICK_SET_INTERVAL_SINGEL(uint32 value , void (*fun_call)(void))
{
	CLEAR_BIT((SYSTICK->CTRL),CTR_ENABLE);
	call_back=fun_call ;
	SET_BIT((SYSTICK->CTRL),CTR_TICKINT);
	flag_interval=1;


	      (SYSTICK->VAL)=0 ;         //clear timer

		   (SYSTICK->LOAD)=value ;


			(SYSTICK->CTRL)|=( 1 <<CTR_ENABLE);


}
/***************************************************************************************************************************/
/* Function Name : SYSTICK_SET_INTERVAL_MULTI                                                                         									    */
/* Description : call a specific function after the timer ends multiple call  until calling 'STOP_INTERVAL' function         */
/* Fun. Argument1: value of LOAD REG                                                    										    									*/
/* Fun. Argument  :   function name (pointer)                                                                            			 								    */
/* Fun. Return : void                                                                                                                        								            */
/**************************************************************************************************************************/

void SYSTICK_SET_INTERVAL_MULTI(uint32 value , void (*fun_call)(void))
{
	(SYSTICK->VAL)=0 ;         //clear timer

			if( value < (1<<24) )  // load new value ;
			{
			   (SYSTICK->LOAD)=value ;
			}
			else {
				 (SYSTICK->LOAD)=0 ; //wrong value
			}

			(SYSTICK->CTRL)|=( 1 <<CTR_ENABLE);

			call_back=fun_call ;

			SET_BIT((SYSTICK->CTRL),CTR_TICKINT);

			flag_interval=0;

}
/************************************************************************************************/
/* Function Name : SYSTICK_STOP_INTERVAL                                                                                */
/* Description : stop    "SYSTICK_SET_INTERVAL_MULTI" function                                                */
/* Fun. Return : void                                                                                                                         */
/************************************************************************************************/
void SYSTICK_STOP_INTERVAL()
{
	flag_interval=1;
    CLEAR_BIT((SYSTICK->CTRL),CTR_TICKINT); //disable interrupt bit
}

/************************************************************************************************/
/* Function Name : SYSTICK_GET_ELAPSED_TIME                                                                        */
/* Description : return  ELAPSED_TIME   starts from enabling the SYSTICK                                */
/* Fun. Return : uint32                                                                                                                      */
/************************************************************************************************/

uint32 SYSTICK_GET_ELAPSED_TIME(void)
{
	return ((uint32)((SYSTICK->LOAD)) - (uint32)((SYSTICK->VAL)));
}

/************************************************************************************************/
/* Function Name : SYSTICK_GET_ELAPSED_TIME                                                                       */
/* Description : return  REMAINING_TIME   before the SYSTICK ends                                      */
/* Fun. Return : uint32                                                                                                                 */
/********************************************************************************************/

uint32 SYSTICK_GET_REMAINING_TIME(void)
{
	return ((SYSTICK->VAL));
}


void _delay_us(uint32 microseconds)
{
    // Calculate the number of cycles required for the desired delay
    uint32 cycles = microseconds;

    // Perform the delay loop
    for (uint32 i = 0; i < (cycles/4); i++)
    {
        // Do nothing
        __asm__("nop");
    }
}

