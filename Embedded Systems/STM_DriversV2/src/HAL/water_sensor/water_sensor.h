/*
 * water_sensor.h
 *
 *  Created on: Feb 1, 2024
 *      Author: asabe
 */

#ifndef HAL_WATER_SENSOR_WATER_SENSOR_H_
#define HAL_WATER_SENSOR_WATER_SENSOR_H_
/********************************************************************* Configrations ***************************************/

#define Number_of_Water_sensors             1

/****************************************************************************************************************************/


typedef enum{
	WS_Init_Not_Done,
	WS_Init_Done,
	WS_Measuring_Not_Done,
	WS_Measuring_Done,
	WS_Measuring_Error,
	WS_Events_num,
}WS_Events_Enum;


typedef struct
{
uint8  ADC_Channel;

}WS_config_struct;

sint8 Water_Sensor_init(WS_config_struct * ptr , uint8 WS_num ) ;
sint32 Water_Sensor_Get_Value_Async(WS_config_struct * ptr, uint8 WS_num  );
/********************************************************************************/
void Init_Not_Done_Action()    ;
void Measuring_Error_Acton();
void Measuring_Not_Done_Acton();








#endif /* HAL_WATER_SENSOR_WATER_SENSOR_H_ */
