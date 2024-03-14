/*
 * Segment.c
 *
 *  Created on: Feb 3, 2024
 *      Author: Mamdouh
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"

#include "../../MCAL/GPIO/GPIO_int_.h"

#include "Segment.h"




void SEGMENT_Init(void)
{
	GPIO_Set_Pin_Direction(SEGMENT_A_Port, SEGMENT_A_Pin, GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(SEGMENT_B_Port, SEGMENT_B_Pin, GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(SEGMENT_C_Port, SEGMENT_C_Pin, GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(SEGMENT_D_Port, SEGMENT_D_Pin, GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(SEGMENT_E_Port, SEGMENT_E_Pin, GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(SEGMENT_F_Port, SEGMENT_F_Pin, GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(SEGMENT_G_Port, SEGMENT_G_Pin, GPIO_MODE_OUTPUT);
}



void SEGMENT_Display(uint8 Number)
{
	switch(Number)
	{
	case 0 :
	{
		GPIO_Set_Pin_Value(SEGMENT_A_Port, SEGMENT_A_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_B_Port, SEGMENT_B_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_C_Port, SEGMENT_C_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_D_Port, SEGMENT_D_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_E_Port, SEGMENT_E_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_F_Port, SEGMENT_F_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_G_Port, SEGMENT_G_Pin, PIN_LOW);
	}
	break;
	case 1 :
	{
		GPIO_Set_Pin_Value(SEGMENT_A_Port, SEGMENT_A_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_B_Port, SEGMENT_B_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_C_Port, SEGMENT_C_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_D_Port, SEGMENT_D_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_E_Port, SEGMENT_E_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_F_Port, SEGMENT_F_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_G_Port, SEGMENT_G_Pin, PIN_LOW);
	}
	break;
	case 2 :
	{
		GPIO_Set_Pin_Value(SEGMENT_A_Port, SEGMENT_A_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_B_Port, SEGMENT_B_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_C_Port, SEGMENT_C_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_D_Port, SEGMENT_D_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_E_Port, SEGMENT_E_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_F_Port, SEGMENT_F_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_G_Port, SEGMENT_G_Pin, PIN_HIGH);
	}
	break;
	case 3 :
	{
		GPIO_Set_Pin_Value(SEGMENT_A_Port, SEGMENT_A_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_B_Port, SEGMENT_B_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_C_Port, SEGMENT_C_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_D_Port, SEGMENT_D_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_E_Port, SEGMENT_E_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_F_Port, SEGMENT_F_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_G_Port, SEGMENT_G_Pin, PIN_HIGH);
	}
	break;
	case 4 :
	{
		GPIO_Set_Pin_Value(SEGMENT_A_Port, SEGMENT_A_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_B_Port, SEGMENT_B_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_C_Port, SEGMENT_C_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_D_Port, SEGMENT_D_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_E_Port, SEGMENT_E_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_F_Port, SEGMENT_F_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_G_Port, SEGMENT_G_Pin, PIN_HIGH);
	}
	break;
	case 5 :
	{
		GPIO_Set_Pin_Value(SEGMENT_A_Port, SEGMENT_A_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_B_Port, SEGMENT_B_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_C_Port, SEGMENT_C_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_D_Port, SEGMENT_D_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_E_Port, SEGMENT_E_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_F_Port, SEGMENT_F_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_G_Port, SEGMENT_G_Pin, PIN_HIGH);
	}
	break;
	case 6 :
	{
		GPIO_Set_Pin_Value(SEGMENT_A_Port, SEGMENT_A_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_B_Port, SEGMENT_B_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_C_Port, SEGMENT_C_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_D_Port, SEGMENT_D_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_E_Port, SEGMENT_E_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_F_Port, SEGMENT_F_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_G_Port, SEGMENT_G_Pin, PIN_HIGH);
	}
	break;
	case 7 :
	{
		GPIO_Set_Pin_Value(SEGMENT_A_Port, SEGMENT_A_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_B_Port, SEGMENT_B_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_C_Port, SEGMENT_C_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_D_Port, SEGMENT_D_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_E_Port, SEGMENT_E_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_F_Port, SEGMENT_F_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_G_Port, SEGMENT_G_Pin, PIN_LOW);
	}
	break;
	case 8 :
	{
		GPIO_Set_Pin_Value(SEGMENT_A_Port, SEGMENT_A_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_B_Port, SEGMENT_B_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_C_Port, SEGMENT_C_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_D_Port, SEGMENT_D_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_E_Port, SEGMENT_E_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_F_Port, SEGMENT_F_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_G_Port, SEGMENT_G_Pin, PIN_HIGH);
	}
	break;
	case 9 :
	{
		GPIO_Set_Pin_Value(SEGMENT_A_Port, SEGMENT_A_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_B_Port, SEGMENT_B_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_C_Port, SEGMENT_C_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_D_Port, SEGMENT_D_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_E_Port, SEGMENT_E_Pin, PIN_LOW);
		GPIO_Set_Pin_Value(SEGMENT_F_Port, SEGMENT_F_Pin, PIN_HIGH);
		GPIO_Set_Pin_Value(SEGMENT_G_Port, SEGMENT_G_Pin, PIN_HIGH);
	}
	break;
	}
}


