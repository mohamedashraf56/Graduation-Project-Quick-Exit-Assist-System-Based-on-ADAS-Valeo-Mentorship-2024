
#include "lip/std_types.h"
#include "lip/common_macros.h"

#include "MCAL/RCC/RCC_int.h"
#include "MCAL/GPIO/GPIO_int_.h"

#include "MCAL/EXTI/EXTI_int.h"
#include "MCAL/NVIC/NVIC_int.h"
#include "MCAL/SYSTICK/SYSTICK_int.h"

#include "MCAL/TIM2/TIM2_int.h"
#include "HAL/LCD/LCD.h"
#include "HAL/ULTRASONIC/ULTRASONIC.h"

int main(void)

{
	// init RCC
	 MRCC_vInit();
	 // init systick timer
	 MSTK_vInit();
	 // enable clk on syscgf to enable the GPIOA port & C
	 MRCC_vEnableClock(RCC_AHB1,RCC_GPIOAEN);
	 MRCC_vEnableClock(RCC_AHB1,RCC_GPIOCEN);



	 GPIO_SetPin_Direction(GPIO_PORTC, PIN13, GPIO_MODE_OUTPUT);
	 GPIO_SetOutput_Speed(GPIO_PORTC, PIN13, LowSpeed);
	 GPIO_SetOutput_Type(GPIO_PORTC, PIN13, PUSH_PULL);



	 uint32 Distance = 0;
	 Ultrasonic_Init US1 ;

	 US1.Seleted_Timer = 2;
	 US1.Echo_Port = GPIO_PORTA;
	 US1.Echo_Pin  = PIN0;
	 US1.Trig_Port = GPIO_PORTA;
	 US1.Trig_Pin  = PIN5;
	 US_Init(&US1);

	while(1)
	{

		US_Set_Trigger(&US1);
		Distance = US_Get_Distance(&US1);
		if(Distance>50)
		{
			GPIO_SetPin_Value(GPIO_PORTC, PIN13, PIN_LOW);
		}
		else
		{
			GPIO_SetPin_Value(GPIO_PORTC, PIN13, PIN_HIGH);
		}
	}


return 0;
}

