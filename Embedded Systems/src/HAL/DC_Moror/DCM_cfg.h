/*
 * DCM_cfg.h
 *
 *  Created on: Mar 23, 2024
 *      Author: Zahraa Mohamed
 */

#ifndef HAL_DC_MOTOR_DCM_CFG_H_
#define HAL_DC_MOTOR_DCM_CFG_H_

#define MOTOR_DRIVER_PORT  PORTB

/* Motor Driver pins of the two LEFT motors*/
#define MDriver_FWDir_PIN_LEFT	PIN0    // IN1 pin of the motor diver (writing 1 to this pin make the motor move forward)
#define MDriver_BWDir_PIN_LEFT	PIN1    // IN2 pin of the motor diver (writing 1 to this pin make the motor move backward)

/* Motor Driver pins of the two RIGHT motors */
#define MDriver_FWDir_PIN_RIGHT	PIN2   // IN3 pin of the motor diver (writing 1 to this pin make the motor move forward)
#define MDriver_BWDir_PIN_RIGHT	PIN3   // IN4 pin of the motor diver (writing 1 to this pin make the motor move backward)

#define	DCM_DUTY_CYCLE 	50

#endif /* HAL_DC_MOTOR_DCM_CFG_H_ */
