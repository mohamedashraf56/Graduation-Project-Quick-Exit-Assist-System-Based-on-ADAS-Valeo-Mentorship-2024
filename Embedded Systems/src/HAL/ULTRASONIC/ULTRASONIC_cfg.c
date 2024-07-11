/*
 * ULTRASONIC_cfg.c
 *
 *  Created on: Mar 23, 2024
 *      Author: asabe
 */
#include "../../MCAL/GPIO/GPIO_int_.h"
#include "ULTRASONIC.h"
Ultrasonic_Cfg_St UltraSonic_F_Cfg={
		 .Seleted_Timer = 5,
		 .Echo_Port = PORTA,
		 .Echo_Pin  = PIN0,
		 .Trig_Port = PORTA,
		 .Trig_Pin  = PIN5
 };
   Ultrasonic_Cfg_St UltraSonic_F_Left_Cfg={
		   .Seleted_Timer = 1,
		   .Echo_Port = PORTA,
		   .Echo_Pin  = PIN8,
		   .Trig_Port = PORTA,
		   .Trig_Pin  = PIN5
 };
 Ultrasonic_Cfg_St UltraSonic_F_Right_Cfg={
		 .Seleted_Timer = 3,
		 .Echo_Port = PORTA,
		 .Echo_Pin  = PIN6,
		 .Trig_Port = PORTA,
		 .Trig_Pin  = PIN5
};

 Ultrasonic_Cfg_St UltraSonic_B_Right_Cfg={
 		 .Seleted_Timer = 2,
 		 .Echo_Port = PORTA,
 		 .Echo_Pin  = PIN3,
 		 .Trig_Port = PORTA,
 		 .Trig_Pin  = PIN5
 };


 Ultrasonic_Cfg_St UltraSonic_B_Left_Cfg={
 		 .Seleted_Timer = 9,
 		 .Echo_Port = PORTA,
 		 .Echo_Pin  = PIN2,
 		 .Trig_Port = PORTA,
 		 .Trig_Pin  = PIN5
 };

