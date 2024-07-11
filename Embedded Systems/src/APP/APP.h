/*
 * APP.h
 *
 *  Created on: Mar 23, 2024
 *      Author: Sabet & Mamdouh
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include "../lip/std_types.h"
#include "../lip/common_macros.h"


#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int_.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"
#include "../MCAL/TIMER/TIMER_int.h"
#include "../MCAL/TIM10_11_PWM/TIM10_11_int.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/USART/USART_init.h"
#include "../MCAL/I2C/I2C_int.h"

#include "../HAL/MPU/MPU.h"
#include "../HAL/water_sensor/water_sensor.h"
#include "../RTOS/RTOS_int.h"

/*******************************************************************************
 *                          	HAL Components                                 *
 *******************************************************************************/

#include "../HAL/ULTRASONIC/ULTRASONIC.h"
#include "../HAL/DC_Moror/DCM_int.h"
/*******************************************************************************
 *                          	Global Defenations                             *
 *******************************************************************************/


/********************************************************************************/



#define RED 						   		    1
#define OBJECT_DETECTED  				       	1
#define OBJECT_NOT_DETECTED	 					0

#define REQ_FOR_RASPBERRY_FOR_DUMMY				'R'
#define REQ_FOR_RASPBERRY_FOR_CAMERA			'C'

#define VEHICLE_DETECTED 						'V'
#define VEHICLE_NOT_DETECTED 					'O'

#define Danger_DISTANCE          10.0
#define UN_SAFE_DISTANCE         20.0

#define Forward                    0
#define F_Left                     1
#define F_Right                    2
#define B_Right                    3
#define B_Left                     4

#define Ultra_sonic_num            5


#define Rullover_buzzer_port PORTB
#define Rullover_buzzer_pin  PIN15


#define Car_No_RollOver 0

#define Car_RollOver_Right 1

#define Car_RollOver_Left 2


typedef struct
{
	uint8 car_u8color;
	uint8 car_u8speed;
	uint8 car_u8objectDetected;

}CAR_t;

CAR_t Dummy_Car_Data;

typedef enum
{
	RIGHT_OVT,
	LEFT_OVT

}OVER_TAKE_DIR_t;


void GET_US_Distance(void);
void RasPi_GetData (void);
void  Bluetooth_Get_Orded (void);
void Car_Moving_System (void);

void US_Trigger_All(void);

void Hardware_Init(void);

void US_Take_Action(void);

void Buzzer_Toggle(void);

void Blind_Spot_Warrning(void);

void MPU_Take_Actoin(void);

void Buzzer_RullOver_Toggle(void);

void Update_MPU_Data(void);

void Water_Sensor_Update(void);

void Water_Sensor_Take_Action(void);

void Water_Sensor_Toggle(void);

#endif /* APP_APP_H_ */
