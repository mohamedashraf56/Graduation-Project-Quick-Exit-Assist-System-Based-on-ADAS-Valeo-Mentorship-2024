
#include "APP/APP.h"



void main (void)
{

	DELAY_Micro(250000);

	Hardware_Init();


	RTOS_u8CreateTask(GET_US_Distance, 10 , 5 , 10);
	//RTOS_u8CreateTask(Car_Moving_System, 100 , 1, 200);
	RTOS_u8CreateTask(US_Trigger_All, 8 , 2, 55);
	RTOS_u8CreateTask(US_Take_Action, 15 , 0, 50);

	RTOS_u8CreateTask(Buzzer_Toggle, 25 , 10, 40);// if u need to change Priority make sure to change it in app functions
	RTOS_u8SuspendTask(10);

	RTOS_u8CreateTask(MPU_Take_Actoin, 53 , 16, 20);

	RTOS_u8CreateTask(Buzzer_RullOver_Toggle, 30 , 15, 40);// if u need to change Priority make sure to change it in app functions

	RTOS_u8SuspendTask(15);

	RTOS_u8CreateTask(Blind_Spot_Warrning, 12 , 11, 20);

	RTOS_u8CreateTask(Water_Sensor_Update,20 , 3, 9 );

	RTOS_u8CreateTask(Update_MPU_Data, 50, 14, 20);

	RTOS_u8CreateTask(Water_Sensor_Toggle, 5, 17, 20);
	RTOS_u8SuspendTask(17);

	RTOS_u8CreateTask(Water_Sensor_Take_Action, 10, 18, 27);

	//RTOS_u8CreateTask(TEST_Periodicity, 50 , 3, 50);


	RTOS_voidStartOS();



	while (1)
	{


	}

}


