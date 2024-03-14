/*
 * ULTRASONIC.h
 *
 *  Created on: Jan 1, 2024
 *      Author: Mamdouh & Sabet
 *       *      v1.0
 *      Updated 2/2/2024 by Mamdouh
 */


#define SYSTEM_Freq      (25000000U)


#define SELCTED_Channel_Timer_2       4   // choose channels from 1 to 4
#define SELCTED_Channel_Timer_3       1
#define SELCTED_Channel_Timer_4       1
#define SELCTED_Channel_Timer_5       1


typedef enum{
	// 0 is the idl state
    US_Idl_State,
	// 1 s a measuring state
   US_Measuring_State,
   // 2 Triggering state
   US_Triggering_State,

   US_States_Num,

}States_Enum;


// for implementation use this config struct
typedef struct
{
	uint8 US_Number ;

	uint8 Seleted_Timer; // options (2,3,4,5)
	uint8 Trig_Port;
	uint8 Trig_Pin;
	uint8 Echo_Port;
	// look at the pinout diagram to choose the timer and his channel
	uint8 Echo_Pin;
	sint8 STATES_Prv[US_States_Num];
}Ultrasonic_Cfg_St;


// Note that timer 6 & 7 are only used by Dac and cant be used here
enum
{
	TIMER2_SELECTED = 2,
	TIMER3_SELECTED,
	TIMER4_SELECTED,
	TIMER5_SELECTED,
};



typedef enum{
	// 0 init not done
   US_Init_Not_Done,
   // 1 Init is done
   US_Init_Done,
   // 2 THE measuring not done
   US_Measuring_Stoped,
   // 3 THE measuring not done
   US_Measuring_Started,
   // 4 the triggering not done
   US_Triggering_Not_Done,
   // 5 The Triggerign done
   US_Triggering_Done,

   US_Events_Num,
}Events_Enum;

/*
typedef enum{
   US_UP,
   US_Down,
   US_Right,
   US_Left,
   Measuring_States_num

}Measuring_States_Enum;
*/

sint8 US_Init(Ultrasonic_Cfg_St * US_Conif_Struct);

sint8 US_Set_Trigger(Ultrasonic_Cfg_St * US_Conif_Struct);
uint32 US_Get_Distance(Ultrasonic_Cfg_St * US_Conif_Struct);
sint8 US_Start(Ultrasonic_Cfg_St * US_Conif_Struct);
sint8 US_Stop(Ultrasonic_Cfg_St * US_Conif_Struct);

void Ultrasonic_Timer2_Call_Back(void);
void Ultrasonic_Timer3_Call_Back(void);
void Ultrasonic_Timer4_Call_Back(void);
void Ultrasonic_Timer5_Call_Back(void);

void DELAY_Micro(uint32 duration_in_microseconds);

