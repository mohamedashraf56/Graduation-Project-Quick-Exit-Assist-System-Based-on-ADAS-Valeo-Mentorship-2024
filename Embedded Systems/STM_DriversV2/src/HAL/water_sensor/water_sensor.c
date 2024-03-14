/*
 * water_sensor.c
 *
 *  Created on: Feb 1, 2024
 *      Author: asabe
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "../../MCAL/ADC/ADC_init.h"
#include "water_sensor.h"
#include "../../HAL/LCD/lcd.h"

  static sint8 sg_au8_WSstate[Number_of_Water_sensors] ;
uint8 *ADC_Channel_Cpy_Error ;  // take copy from ADC_Channel if their are an error "we can protect these resource by take semaphore in free RTOS"

sint32 sg_s32Sensor_Read ;

/* ********************************************************************
 * Name            : ADC_ISR_CallBack_GET_VALUE
 * Description   :  Call back function to get value from ADC
 * Return  		  : State
 * Argument 1	  : void
 * Argument 2   : void
 * TYPE       		  : static SYNC
 ***********************************************************************/

static void ADC_ISR_CallBack_GET_VALUE(void)
{
	sg_s32Sensor_Read = ADC_Get_Value() ;
}


/* ********************************************************************
 * Name            : Water_Sensor_init
 * Description   :  Initialization for Water_sensor
 * Return  		  : State
 * Argument 1	  : Config struct for Water_sensor Channels
 * Argument 2   : Water_sensor number
 * TYPE       		  : SYNC
 ***********************************************************************/
sint8 Water_Sensor_init(WS_config_struct * ptr , uint8 WS_num )
{
	WS_num=WS_num-1 ;
	sg_au8_WSstate[WS_num] = WS_Init_Not_Done ;
	ADC_init ();
    ADC_Interrupt_CB (ADC_ISR_CallBack_GET_VALUE);
	ADC_CHANIL_CONFIG(ptr->ADC_Channel);
	sg_au8_WSstate[WS_num]=WS_Init_Done ;
	return sg_au8_WSstate[WS_num] ;

}

/* ********************************************************************
 * Name            : Water_Sensor_Get_Value_Async
 * Description   :  Getter function to return the ADC reading for Water_sensor
 * Return  		  : ADC_read
 * Argument 1	  : Config struct for Water_sensor Channels
 * Argument 2   : Water_sensor number
 * TYPE       		  : ASYNC
 ***********************************************************************/

sint32 Water_Sensor_Get_Value_Async(WS_config_struct * ptr, uint8 WS_num  )
{
	WS_num=WS_num-1 ;
	if ( sg_au8_WSstate[WS_num]==WS_Init_Not_Done)
		{
			Init_Not_Done_Action();
			return -1 ; // Indicate to error and no need to measure with problem in init "
		}
	   sg_au8_WSstate[WS_num] =WS_Measuring_Not_Done;
		ADC_Get_Value_Async(ptr->ADC_Channel);          // reading sensor value
	if ((sg_s32Sensor_Read<0 )|| (sg_s32Sensor_Read>5000) ||  ( (sg_s32Sensor_Read>700)&&(sg_s32Sensor_Read<750) )  ) //for errors with sensor       &&    errors with pins

	{
		sg_au8_WSstate[WS_num] =WS_Measuring_Error;
		*ADC_Channel_Cpy_Error = ptr->ADC_Channel ;
		Measuring_Error_Acton();

	}
	else{                                                                                        // reading is done correctly
		sg_au8_WSstate[WS_num] =WS_Measuring_Done;
		return sg_s32Sensor_Read ;
	}
	if (sg_au8_WSstate[WS_num]==WS_Measuring_Not_Done)
	{
		*ADC_Channel_Cpy_Error = ptr->ADC_Channel ;
		Measuring_Not_Done_Acton();
	}
	return -1 ; // Indicate to error while Measuring "Measuring_Not_Done" or "Measuring_Error"

}

/*************************************************************************************************************************************/
void Init_Not_Done_Action()           // Reinitializing the sensor configurations
{
	//LCD_init();
  //  LCD_displayString("WS Init  Not Done!!");
}

void Measuring_Error_Acton()
{
	//  os delay (500) ;               // OS delay
	sg_s32Sensor_Read=(sint32)ADC_Get_Value_Sync(*ADC_Channel_Cpy_Error);   // try to re measuring after OS delay
	if (sg_s32Sensor_Read<0 || sg_s32Sensor_Read>5000)
	{
		//LCD_init();
	   // LCD_displayString("WS Measuring Error");
	}
}

void Measuring_Not_Done_Acton()
{
	//LCD_init();
   // LCD_displayString("WS Measuring  Not Done");

}
