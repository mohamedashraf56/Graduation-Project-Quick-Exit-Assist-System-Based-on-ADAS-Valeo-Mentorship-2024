/*
 * DCM_int.h
 *
 *  Created on: Mar 23, 2024
 *      Author: Zahraa Mohamed
 */

#ifndef HAL_DC_MOTOR_DCM_INT_H_
#define HAL_DC_MOTOR_DCM_INT_H_

void DC_Motor_Init(void);
void DC_Motor_MoveForward(uint8 DC_MovingSpeed);
void DC_Motor_MoveBackward(uint8 DC_MovingSpeed);
void DC_Motor_Stop(void);
void DC_Motor_MoveRight(uint8 DC_MovingSpeed);
void DC_Motor_MoveLeft(uint8 DC_MovingSpeed);

#endif /* HAL_DC_MOTOR_DCM_INT_H_ */
