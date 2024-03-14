/*
 * Telt_sensor.h
 *
 *  Created on: Feb 2, 2024
 *      Author: asabe
 */

#ifndef HAL_TELT_SENSOR_TELT_SENSOR_H_
#define HAL_TELT_SENSOR_TELT_SENSOR_H_

/********************************************************************* Configrations ***************************************/

#define Number_of_Telet_sensors             1

/****************************************************************************************************************************/
typedef enum{
	 TS_Init_Not_Done,
	 TS_Init_Done,
	 TS_Measuring_Not_Done,
	 TS_Measuring_Done,
	 TS_Events_num,
}TS_Events_Enum;

typedef enum{
	 TS_UP,
	 TS_Down,
	 TS_Right,
	 TS_Left,
	 Measuring_States_num

}Measuring_States_Enum;


typedef struct {
    uint8  S1_Port;
    uint8  S1_Pin;
    uint8  S2_Port;
    uint8  S2_Pin;
} TS_config_struct;


sint8 Tilt_sensor_init(TS_config_struct *ptr,uint8  telet_num) ;
sint8 Tilt_sensor_Get_Value(TS_config_struct * ptr,uint8  telet_num ) ;
sint8 Tilt_sensor_State_getter(uint8  telet_num);

/********************************************************************************/
void Tilt_sensor_Init_Not_Done_Action();

void Tilt_sensor_Measuring_Not_Done_Acton();




#endif /* HAL_TELT_SENSOR_TELT_SENSOR_H_ */
