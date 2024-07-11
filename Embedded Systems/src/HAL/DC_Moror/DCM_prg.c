/*
 * DCM_prg.c
 *
 *  Created on: Mar 23, 2024
 *      Author: Zahraa Mohamed
 */



#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "../../MCAL/RCC/RCC_int.h"
#include "../../MCAL/GPIO/GPIO_int_.h"
#include "../../MCAL/TIM10_11_PWM/TIM10_11_int.h"

#include "DCM_int.h"
#include "DCM_cfg.h"

TIM10_11_config_struct DCM_cfg ={0,100,DCM_DUTY_CYCLE};

/* ********************************************************************
 * Name         : DC_Motor_Init
 * Description  : Initialize the DC motor (Setting the pin modes/Output type
 * 													& Initializing TIM 10,11)
 * Return  		: Void
 * Argument 	: Void
 ***********************************************************************/
void DC_Motor_Init(void)
{
	RCC_Enable_Clock(RCC_AHB1,RCC_GPIOB);

	TIM10_11_init(&DCM_cfg,TIMER10);
	TIM10_11_init(&DCM_cfg,TIMER11);

	GPIO_Set_Pin_Direction(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_LEFT,GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_LEFT,GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_RIGHT,GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_RIGHT,GPIO_MODE_OUTPUT);

	GPIO_Set_Output_Type(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_LEFT,PUSH_PULL);
	GPIO_Set_Output_Type(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_LEFT,PUSH_PULL);
	GPIO_Set_Output_Type(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_RIGHT,PUSH_PULL);
	GPIO_Set_Output_Type(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_RIGHT,PUSH_PULL);

}

/* ********************************************************************
 * Name         : DC_Motor_MoveForward
 * Description  : Moving the motor forward
 * Return  		: Void
 * Argument 	: Moving speed (1:100)
 ***********************************************************************/
void DC_Motor_MoveForward(uint8 DC_MovingSpeed)
{
	TIM10_11_config_struct DCM_Speed_cfg ={0,500,DC_MovingSpeed};
	TIM10_11_PWM(&DCM_Speed_cfg,TIMER10);
	TIM10_11_PWM(&DCM_Speed_cfg,TIMER11);

	//Move forward the two LEFT motors
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_LEFT,PIN_HIGH);
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_LEFT,PIN_LOW);

	//Move forward the two RIGHT motors
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_RIGHT,PIN_HIGH);
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_RIGHT,PIN_LOW);

}

/* ********************************************************************
 * Name         : DC_Motor_MoveBackward
 * Description  : Moving the motor backward
 * Return  		: Void
 * Argument 	: Moving speed (1:100)
 ***********************************************************************/
void DC_Motor_MoveBackward(uint8 DC_MovingSpeed)
{
	TIM10_11_config_struct DCM_Speed_cfg ={0,100,100};

	TIM10_11_config_struct DCM_cfg_LEFT ={0,100,50};

	TIM10_11_PWM(&DCM_cfg_LEFT,TIMER10);
	TIM10_11_PWM(&DCM_Speed_cfg,TIMER11);

	//Move backward the two LEFT motors
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_LEFT,PIN_LOW);
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_LEFT,PIN_HIGH);

	//Move backward the two RIGHT motors
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_RIGHT,PIN_LOW);
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_RIGHT,PIN_HIGH);

}

/* ********************************************************************
 * Name         : DC_Motor_Stop
 * Description  : Stopping the motor
 * Return  		: Void
 * Argument 	: Void
 ***********************************************************************/
void DC_Motor_Stop(void)
{
	// Stop the two LEFT motors
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_LEFT,PIN_LOW);
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_LEFT,PIN_LOW);

	// Stop the two RIGHT motors
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_RIGHT,PIN_LOW);
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_RIGHT,PIN_LOW);
}

/* ********************************************************************
 * Name         : DC_Motor_MoveRight
 * Description  : Moving the motor to right direction
 * Return  		: Void
 * Argument 	: Moving speed (1:100)
 ***********************************************************************/
void DC_Motor_MoveRight(uint8 DC_MovingSpeed)
{
	TIM10_11_config_struct DCM_Speed_cfg ={0,100,DC_MovingSpeed};
	TIM10_11_PWM(&DCM_Speed_cfg,TIMER10);
	TIM10_11_PWM(&DCM_Speed_cfg,TIMER11);

	// Stop the two LEFT motors
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_LEFT,PIN_LOW);
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_LEFT,PIN_LOW);

	//Move forward the two RIGHT motors
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_RIGHT,PIN_HIGH);
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_RIGHT,PIN_LOW);
}


/* ********************************************************************
 * Name         : DC_Motor_MoveLeft
 * Description  : Moving the motor to left direction
 * Return  		: Void
 * Argument 	: Moving speed (1:100)
 ***********************************************************************/
void DC_Motor_MoveLeft(uint8 DC_MovingSpeed)
{
	TIM10_11_config_struct DCM_Speed_cfg ={0,100,DC_MovingSpeed};
	TIM10_11_PWM(&DCM_Speed_cfg,TIMER10);
	TIM10_11_PWM(&DCM_Speed_cfg,TIMER11);

	// Stop the two RIGHT motors
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_RIGHT,PIN_LOW);
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_RIGHT,PIN_LOW);

	// Move forward the two LEFT motors
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_FWDir_PIN_LEFT,PIN_HIGH);
	GPIO_Set_Pin_Value(MOTOR_DRIVER_PORT,MDriver_BWDir_PIN_LEFT,PIN_LOW);

}
