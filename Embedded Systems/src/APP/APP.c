/*
 * APP.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Mamdouh & Sabet
 */

#include "APP.h"


uint8 G_u8BluetoothOrder;
uint8 G_u32SpeedIndicator;  //PWM_speed
uint8 G_u8CameraDetection ;
uint8 G_u8PassedCarFlag=1;
uint8 G_u8FlagRightInvalid=0;
uint8 G_u8EntranceFlag = 0;
uint32 G_u32USDistance=100;
uint8 G_u8HandShake=0;
uint8 G_u8RasspDummyData=0;
uint8 Car_RollOver_state=0;

MPU6050_t MPU_Data_St;



sint32 Water_Sensor_Value;

extern I2C_Config_St I2C1_Cf;

extern Ultrasonic_Cfg_St UltraSonic_F_Cfg;
extern Ultrasonic_Cfg_St UltraSonic_F_Left_Cfg;
extern Ultrasonic_Cfg_St UltraSonic_F_Right_Cfg;
extern Ultrasonic_Cfg_St UltraSonic_B_Right_Cfg;
extern Ultrasonic_Cfg_St UltraSonic_B_Left_Cfg;

extern WS_config_struct Water_Sensor;

extern USART_Confg_Struct USART1_cfg_struct;
extern USART_Confg_Struct USART6_cfg_struct;

uint32 UltraSonic_Dista_ARR [ Ultra_sonic_num ];

uint8 buzzer_flag =0 ;



void Hardware_Init(void)
{
	// RCC Initialization
		RCC_Init();
		RCC_Enable_Clock(RCC_AHB1, RCC_GPIOA);
		RCC_Enable_Clock(RCC_AHB1, RCC_GPIOC);
		RCC_Enable_Clock(RCC_AHB1, RCC_GPIOB);

		DC_Motor_Init();

		US_Init(&UltraSonic_F_Cfg);
		US_Init(&UltraSonic_F_Left_Cfg);
		US_Init(&UltraSonic_F_Right_Cfg);
		US_Init(&UltraSonic_B_Right_Cfg);
		// timer9 will be implemnted
		//US_Init(&UltraSonic_B_Left_Cfg);


		US_Start(&UltraSonic_F_Cfg);
		US_Start(&UltraSonic_F_Left_Cfg);
		US_Start(&UltraSonic_F_Right_Cfg);
		US_Start(&UltraSonic_B_Right_Cfg);
	//	US_Start(&UltraSonic_B_Left_Cfg);


		I2C_Init(&I2C1_Cf);
		I2C_Gpio_Config(&I2C1_Cf);
		MPU6050_Init(&I2C1_Cf, &MPU_Data_St);


		Water_Sensor_init(&Water_Sensor,1);

		// USART1 Initialization   >> for Raspberry
		USART_Init(&USART1_cfg_struct , USART1 );
		USART_Receiver_Transmiter(USART1 , &USART1_cfg_struct) ;
	    USART1_Set_CBF(RasPi_GetData);

		// USART6 Initialization   >> for Bluetooth
		USART_Init(&USART6_cfg_struct , USART6 );
		USART_Transmiter(USART6, &USART6_cfg_struct);
	    USART6_Set_CBF(Bluetooth_Get_Orded);
	 	USART_Receive_Byte_Async_Interrupt_En(USART6 , &USART6_cfg_struct);


	 	// for test pin
		// FOR BUZZER PIN

		GPIO_Set_Pin_Direction(PORTC, PIN13, GPIO_MODE_OUTPUT);
		GPIO_Set_Pin_Direction(PORTC, PIN14, GPIO_MODE_OUTPUT);
		GPIO_Set_Pin_Direction(Rullover_buzzer_port, Rullover_buzzer_pin, GPIO_MODE_OUTPUT);

		GPIO_Set_Pin_Direction(PORTB, PIN14, GPIO_MODE_OUTPUT);



}





void Car_Moving_System (void)
{
	if ((G_u8BluetoothOrder >='0' && G_u8BluetoothOrder<='9')||(G_u8BluetoothOrder=='q'))
			{
				if (G_u8BluetoothOrder=='q')
				{
					G_u32SpeedIndicator=100 ; // max speed
				}
				else {
					G_u32SpeedIndicator=(G_u8BluetoothOrder-48)*10 ;  //covert ascii to integer
				}
			}

			else if (G_u8BluetoothOrder == 'R')  //if driver need to go right
			{
				if(UltraSonic_Dista_ARR[F_Right] < UN_SAFE_DISTANCE)
				{
					GPIO_Set_Pin_Value(PORTB, PIN8, LOGIC_HIGH); //buzzer or led on
					if ( UltraSonic_Dista_ARR[Forward] >  UN_SAFE_DISTANCE )
					{
						DC_Motor_MoveForward(G_u32SpeedIndicator);
					}
					else {
						DC_Motor_Stop() ;
					}
				}
				else
				{
					GPIO_Set_Pin_Value(PORTB, PIN8, LOGIC_LOW); //buzzer or led off
					DC_Motor_MoveRight(G_u32SpeedIndicator);
				}
			}

			else if (G_u8BluetoothOrder == 'L')
			{
				if(UltraSonic_Dista_ARR[F_Left] < UN_SAFE_DISTANCE)
				{
					GPIO_Set_Pin_Value(PORTB, PIN9, LOGIC_HIGH); //buzzer or led on
					if (UltraSonic_Dista_ARR[Forward]>UN_SAFE_DISTANCE)
					{
						DC_Motor_MoveForward(G_u32SpeedIndicator);
					}
					else
					{
						DC_Motor_Stop() ;
					}
				}
				else
				{
					GPIO_Set_Pin_Value(PORTB, PIN9, LOGIC_LOW); //buzzer or led off
					DC_Motor_MoveLeft(G_u32SpeedIndicator);
				}
			}

			else if (G_u8BluetoothOrder == 'F')
			{
				if(UltraSonic_Dista_ARR[Forward] < UN_SAFE_DISTANCE)
				{
					GPIO_Set_Pin_Value(PORTB, PIN9, LOGIC_HIGH); //buzzer or led on
					DC_Motor_Stop() ;
				}
				else
				{
					GPIO_Set_Pin_Value(PORTB, PIN9, LOGIC_LOW); //buzzer or led off
					DC_Motor_MoveForward(G_u32SpeedIndicator);
				}
			}
}



void US_Trigger_All(void)
{
	// All ultrasonic are connected with PINA5 here we dont need to trigger
	// each one we can trigger only one time
	// if we want make every ultrasonic has its own triger pin we will remove this comments
	US_Set_Trigger(&UltraSonic_F_Cfg); // all will be trigered
	US_Set_Trigger(&UltraSonic_F_Left_Cfg);
	US_Set_Trigger(&UltraSonic_F_Right_Cfg);
	US_Set_Trigger(&UltraSonic_B_Right_Cfg);
//	US_Set_Trigger(&UltraSonic_B_Left_Cfg);


	// timer 9 here
//	US_Set_Trigger(&UltraSonic_B_Left_Cfg);

}


void GET_US_Distance(void)
{
	UltraSonic_Dista_ARR[F_Right]      =US_Get_Distance(&UltraSonic_F_Right_Cfg);
	UltraSonic_Dista_ARR[F_Left]        = US_Get_Distance(&UltraSonic_F_Left_Cfg);
	UltraSonic_Dista_ARR[Forward] = US_Get_Distance(&UltraSonic_F_Cfg);
	UltraSonic_Dista_ARR[B_Right]      =US_Get_Distance(&UltraSonic_B_Right_Cfg);
//	UltraSonic_Dista_ARR[B_Left]      =US_Get_Distance(&UltraSonic_B_Left_Cfg);

}
/*******************************************************************************
 *                          	Callback fun                               *
 *******************************************************************************/
void RasPi_GetData (void)
{
	G_u8RasspDummyData = USART_Get_Data_Reg(USART1) ;
}

void  Bluetooth_Get_Orded (void)
{
	G_u8BluetoothOrder=USART_Get_Data_Reg(USART6) ;
}




void US_Take_Action(void)
{
	if(UltraSonic_Dista_ARR[Forward] < 20 &&  UltraSonic_Dista_ARR[Forward] > 0)
	{

		DC_Motor_Stop();
		//DC_Motor_MoveRight(10);

	}
	else if(UltraSonic_Dista_ARR[F_Left] < 20 &&  UltraSonic_Dista_ARR[F_Left] > 0)
	{

		DC_Motor_Stop();
		//DC_Motor_MoveRight(10);

	}
	else if(UltraSonic_Dista_ARR[F_Right] < 20 &&  UltraSonic_Dista_ARR[F_Right] > 0)
	{

		DC_Motor_Stop();
		//DC_Motor_MoveRight(10);

	}
	else
	{
		DC_Motor_MoveBackward(70);
	}
}



void Buzzer_Toggle(void)
{
	static uint8 toggle = 0;
	toggle = toggle ^ 1 ;
	GPIO_Set_Pin_Value(PORTC, PIN14, toggle);
}

void Buzzer_RullOver_Toggle(void)
{
	static uint8 toggle = 0;
	toggle = toggle ^ 1 ;
	GPIO_Set_Pin_Value(Rullover_buzzer_port, Rullover_buzzer_pin, toggle);
}

void Blind_Spot_Warrning(void)
{
	if(UltraSonic_Dista_ARR[B_Right]<30 && UltraSonic_Dista_ARR[B_Right] > 0 )
	{
		RTOS_u8ChangePeriodicity(&SystemTasks[10],UltraSonic_Dista_ARR[B_Right]);
		// 10 IS REPERSENT to task buzzer toggle on os (Priority number)
		RTOS_u8ResumeTask(10);
	}

	else
	{
		GPIO_Set_Pin_Value(PORTC, PIN14, PIN_LOW);
		RTOS_u8SuspendTask(10);
	}
}



void Update_MPU_Data(void)
{
	MPU6050_Read_All(&I2C1_Cf, &MPU_Data_St);
}

void MPU_Take_Actoin(void)
{
	if((MPU_Data_St.Ax)>(double)(0.2))
	{
		RTOS_u8ResumeTask(15);// buzzer toggle function
		Car_RollOver_state = Car_RollOver_Left ;
	    USART_Transmite_Byte_sync (101 ,USART1 ,&USART1_cfg_struct);

	}
	else if((MPU_Data_St.Ax)<(double)(-0.2))
	{
		RTOS_u8ResumeTask(15);// buzzer toggle function

	    Car_RollOver_state = Car_RollOver_Right ;
	    USART_Transmite_Byte_sync (102 ,USART1 ,&USART1_cfg_struct);

	}
	else
	{
		RTOS_u8SuspendTask(15);
		GPIO_Set_Pin_Value(Rullover_buzzer_port, Rullover_buzzer_pin, 0);
		 Car_RollOver_state = Car_No_RollOver ;
	}
}

void Water_Sensor_Update(void)
{
	Water_Sensor_Value = Water_Sensor_Get_Value_Async(&Water_Sensor,1);
}


void Water_Sensor_Take_Action(void)
{
	if (Water_Sensor_Value < 100)
	{
	    USART_Transmite_Byte_sync (123 ,USART1 ,&USART1_cfg_struct);

		RTOS_u8ResumeTask(17);
	}
	else
	{
		RTOS_u8SuspendTask(17);
		GPIO_Set_Pin_Value(PORTB, PIN14, 0);

	}
}


void Water_Sensor_Toggle(void)
{
	static uint8 toggle = 0;
	toggle = toggle ^ 1 ;
	GPIO_Set_Pin_Value(PORTB, PIN14, toggle);
}
