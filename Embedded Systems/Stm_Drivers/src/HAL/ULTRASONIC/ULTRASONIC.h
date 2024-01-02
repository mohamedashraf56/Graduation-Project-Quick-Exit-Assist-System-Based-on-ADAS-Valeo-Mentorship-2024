/*
 * ULTRASONIC.h
 *
 *  Created on: Jan 1, 2024
 *      Author: Mamdouh
 */

typedef struct
{
	uint8 US_Number ;
	uint8 Seleted_Timer;
	uint8 Trig_Port;
	uint8 Trig_Pin;
	uint8 Echo_Port;
	uint8 Echo_Pin;
}Ultrasonic_Init;


// Note that timer 6 & 7 are only used by Dac and cant be used here
enum
{
	US_TIMER1_SELECTED = 1,
	US_TIMER2_SELECTED,
	US_TIMER3_SELECTED,
	US_TIMER4_SELECTED,
	US_TIMER5_SELECTED,
	US_TIMER8_SELECTED = 8,
	US_TIMER9_SELECTED,
	US_TIMER10_SELECTED,
	US_TIMER11_SELECTED,
};


uint8 US_Init(Ultrasonic_Init * US_Conif_Struct);
uint8 US_De_Init(Ultrasonic_Init * US_Conif_Struct);

void Ultrasonic_timer2(void);
void US_Set_Trigger(Ultrasonic_Init * US_Conif_Struct);
uint32 US_Get_Distance(Ultrasonic_Init * US_Conif_Struct);


