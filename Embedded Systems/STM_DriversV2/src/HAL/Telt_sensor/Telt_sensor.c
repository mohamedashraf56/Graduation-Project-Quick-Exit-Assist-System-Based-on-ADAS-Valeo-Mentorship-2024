/*
 * Telt_sensor.c
 *
 *  Created on: Feb 2, 2024
 *      Author: asabe
 */
#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "../../MCAL/GPIO/GPIO_int_.h"
#include "Telt_sensor.h"
#include "../../HAL/LCD/lcd.h"

static sint8 sg_au8_TSstate[Number_of_Telet_sensors] ;

/* ********************************************************************
 * Name            : Tilt_sensor_init
 * Description   :  Initialization for Tilt_sensor
 * Return  		  : State
 * Argument 1	  : Config struct for Tilt_sensor pins
 * Argument 2   : Tilt_sensor number
 * TYPE       		  : SYNC
 ***********************************************************************/
sint8 Tilt_sensor_init(TS_config_struct *ptr , uint8  telet_num) {

	telet_num=telet_num-1 ;     // to make the right index for array  /  (if telet_num = 1) so it will be index 0
	sg_au8_TSstate[telet_num]= TS_Init_Not_Done;


    GPIO_Set_Pin_Direction(ptr->S1_Port, ptr->S1_Pin, GPIO_MODE_INPUT);
    GPIO_Set_Pin_Direction(ptr->S2_Port, ptr->S2_Pin, GPIO_MODE_INPUT);
    GPIO_Set_Input_Pullup_Pulldown(ptr->S2_Port, ptr->S2_Pin, PULL_UP);
    GPIO_Set_Input_Pullup_Pulldown(ptr->S1_Port, ptr->S1_Pin, PULL_UP);


    sg_au8_TSstate[telet_num] = TS_Init_Done;
    return  sg_au8_TSstate[telet_num] ;

}

/* ********************************************************************
 * Name            : Tilt_sensor_Get_Value
 * Description   :  Get the sensor state
 * Return  		  : direction
 * Argument 1	  : Config struct for Tilt_sensor pins
 * Argument 2   : Tilt_sensor number
 * TYPE       		  : SYNC
 ***********************************************************************/

sint8 Tilt_sensor_Get_Value(TS_config_struct * ptr , uint8  telet_num )
{
	uint8 direction ;
	telet_num=telet_num - 1 ;     // to make the right index for array  /  (if telet_num = 1) so it will be index 0
	sg_au8_TSstate[telet_num] = TS_Measuring_Not_Done;
	if ( sg_au8_TSstate[telet_num]==TS_Init_Not_Done)
			{
		Tilt_sensor_Init_Not_Done_Action();
				return -1 ; // Indicate to error
			}

	else
	{

		if (GPIO_Read_Pin(ptr->S1_Port, ptr->S1_Pin)==LOGIC_HIGH &&GPIO_Read_Pin(ptr->S2_Port, ptr->S2_Pin)==LOGIC_LOW )//(1,0)
		{
			direction=TS_UP;
		}

		else if (GPIO_Read_Pin(ptr->S1_Port, ptr->S1_Pin)==LOGIC_LOW  &&  GPIO_Read_Pin(ptr->S2_Port, ptr->S2_Pin)==LOGIC_HIGH )//(0,1)
		{
			direction=TS_Down;
		}
		else if (GPIO_Read_Pin(ptr->S1_Port, ptr->S1_Pin)==LOGIC_LOW  &&  GPIO_Read_Pin(ptr->S2_Port, ptr->S2_Pin)==LOGIC_LOW )//(0,0)
		{
			direction=TS_Right;
		}
		else//(1,1)
		{
			direction=TS_Left;
		}
		sg_au8_TSstate[telet_num] = TS_Measuring_Done;

	}
	if ( (sg_au8_TSstate[telet_num] != TS_Measuring_Done)  )
	{
		 Tilt_sensor_Measuring_Not_Done_Acton();
		 return -1 ;

	}
	else{
	return direction ;
	}
}

/* ********************************************************************
 * Name            : Tilt_sensor_State_getter
 * Description   :  Get the state in run time
 * Return  		  : state
 * Argument 1   : Tilt_sensor number
 * TYPE       		  : SYNC
 ***********************************************************************/
/*****************************************************************************************/
sint8 Tilt_sensor_State_getter(uint8  telet_num)
{
	return sg_au8_TSstate[telet_num] ;
}
/****************************************************************************************/
void Tilt_sensor_Init_Not_Done_Action()
{
//	LCD_init();
    LCD_displayString("TS Error !!");
}
/*****************************************************************************************/
void Tilt_sensor_Measuring_Not_Done_Acton()
{
	//	LCD_init();
	    LCD_displayString("Measuring Error !!");
}
