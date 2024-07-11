/*
 * DC_Motor.h
 *
 *  Created on: Mar 22, 2024
 *      Author: asabe
 */

#ifndef HAL_DC_MOROR_DC_MOTOR_H_
#define HAL_DC_MOROR_DC_MOTOR_H_
#include "../../lip/std_types.h"

void DCM_Init(void);
void DCM_MoveForward(uint8 DC_Move_speed);
void DCM_MoveBackward(uint8 DC_Move_speed);
void DCM_Stop(void) ;
void DCM_MoveRight(uint8 DC_Move_speed);
void DCM_MoveLeft(uint8 DC_Move_speed) ;



#endif /* HAL_DC_MOROR_DC_MOTOR_H_ */
