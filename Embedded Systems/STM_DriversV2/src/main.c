#include "lip/std_types.h"
#include "lip/common_macros.h"
#include "HAL/LCD/lcd.h"
#include "MCAL/RCC/RCC_int.h"
#include "MCAL/GPIO/GPIO_int_.h"
#include "MCAL/SYSTICK/SYSTICK_int.h"
#include "MCAL/NVIC/NVIC_int.h"
#include "MCAL/ADC/ADC_init.h"
#include "MCAL/TIM10_11_PWM/TIM10_11_int.h"
#include "MCAL/USART/USART_init.h"
#include "HAL/water_sensor/water_sensor.h"
uint8  data =0 ;


/*uint8 flag=0;
uint32 xx , yy ;
void ADC_ISR()
{
	if (flag==0)
		{
		xx=ADC_Get_Value();
		flag=1;
		}
	else if (flag==1)
	{
		yy=ADC_Get_Value();
	    flag=0;
	}
}


int main(void) {
	uint32 test = 0  , test2=0 ;
	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOA);
	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOC);
	GPIO_Set_Pin_Direction(PORTC, PIN13, GPIO_MODE_OUTPUT);
 	GPIO_Set_Pin_Value(PORTC, PIN13, LOGIC_LOW);
    ADC_init ();
    ADC_Interrupt_CB (ADC_ISR);
    ADC_CHANIL_CONFIG(PIN0);
    ADC_CHANIL_CONFIG(PIN1);

    while (1) {

       // ADC_Interrupt_Start_Conver(PIN0);
   //     ADC_Interrupt_Start_Conver(PIN1);
//    	xx=ADC_Get_Value_Sync(PIN0) ;
    	ADC_Get_Value_Async(PIN0);

        test =xx;
        test2=yy;
         if (xx > 1600) {
        	 test=xx;
        	 	GPIO_Set_Pin_Value(PORTC, PIN13, LOGIC_HIGH );
        	 	GPIO_Set_Pin_Value(PORTC, PIN13, LOGIC_LOW);

        }


    }
}

*/

/*int main(void) {
	uint32 test = 0  ;
	RCC_Init();
	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOA);
	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOC);

	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOC);
	GPIO_Set_Pin_Direction(PORTC, PIN13, GPIO_MODE_OUTPUT);
 	GPIO_Set_Pin_Value(PORTC, PIN13, LOGIC_LOW);
 	WS_config_struct ptr = {ADC_CH_0};
 	Water_Sensor_init( &ptr,1);

    while (1) {

    	test=Water_Sensor_Get_Value_Async(&ptr , 1 );

         if (test< 100) {
        	 GPIO_Set_Pin_Value(PORTC, PIN13, LOGIC_LOW);
        }
         else
         {
        	 GPIO_Set_Pin_Value(PORTC, PIN13, LOGIC_HIGH);

         }


    }
}
//uint8  data =0 ;

*/

/*int main ()
{
	RCC_Init();
	 	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOA);
	 	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOC);
	 	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOB);
LCD_init();
LCD_clearScreen();
while(1)
{
    LCD_moveCursor(0, 0);
	LCD_intgerToString(88);

}
}*/

/*void res(void)
{
	data =  USART_Get_Data_Reg(USART2) ;
}*/

uint8 res_buffer[20] ;

void res_string(void)
{
	static uint8 i = 0 ;
	res_buffer[i] =  USART_Get_Data_Reg(USART2) ;
	if (res_buffer[i] == '\0')
	{
		i=0 ;
		USART_Receiver_Transmiter_Dis(USART2);

	}
	i++;
}


int main(void) {
 	RCC_Init();
 	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOA);
 	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOC);
 	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOB);

 	USART_Confg_Struct Send_ptr ={PIN9,PIN10,PORTA,PORTA,DATA_Reg_8bit ,OverSampling_8,StopBit_1,{0}};
 	USART_Confg_Struct Resive_ptr ={PIN2,PIN3,PORTA,PORTA,DATA_Reg_8bit ,OverSampling_8,StopBit_1,{0}};

 	USART_Init(&Send_ptr , USART1) ;
 	USART_Init(&Resive_ptr , USART2) ;

 	USART_Receiver_Transmiter(USART1 , &Send_ptr) ;
 	USART_Receiver_Transmiter(USART2 , &Resive_ptr) ;
  //  USART2_Set_CBF(res);
    USART2_Set_CBF(res_string);

 	USART_Receive_Byte_Async_Interrupt_En(USART2 , &Resive_ptr);

	//volatile uint8 test=0   ;
	uint8 tt[] ="Test Usart" ;

	while (1) {

		/*USART_Transmite_Byte_sync('A',USART1,&ptr1);
		DELAY_Micro(5000);
		if (data =='A')
		{
			test ++ ;
		}
		USART_Transmite_Byte_sync('B',USART1,&ptr1);
		DELAY_Micro(5000);
		if (data =='B')
			{
				test ++ ;
			}
		DELAY_Micro(5000);*/


	           	USART_Transmite_String_sync(tt,USART1,&Send_ptr);

	}

}







/*************************************************PWM TEST*************************************************/


/*int main() {

  //  TIM10_Generate_OnePulse_Config();
	RCC_Enable_Clock(RCC_AHB1, RCC_GPIOC);

	RCC_Init() ;

 	TIM10_11_config_struct TIM10_CONFIG={  0  , 100 , 20} ;
 	TIM10_11_config_struct TIM11_CONFIG={  0  , 100 , 1  }    ;


 	TIM10_11_init(& TIM10_CONFIG , TIMER10) ;
 	TIM10_11_init(& TIM10_CONFIG , TIMER11) ;

 	TIM10_11_PWM(& TIM10_CONFIG , TIMER10) ;
 	TIM10_11_PWM(& TIM11_CONFIG , TIMER11) ;

    while (1) {
    }
}
*/
