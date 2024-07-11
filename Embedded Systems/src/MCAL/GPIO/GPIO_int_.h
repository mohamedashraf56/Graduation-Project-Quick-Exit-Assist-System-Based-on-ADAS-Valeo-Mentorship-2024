/*
 * GPIO_int_.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Mamdouh & Sabet
 *    v   0.01
 */

#ifndef MCAL_GPIO_GPIO_INT__H_
#define MCAL_GPIO_GPIO_INT__H_
#include "../../lip/std_types.h"


#ifndef PORTA
#define PORTA              0
#endif

#ifndef  PORTB
#define PORTB              1
#endif

#ifndef PORTC
#define PORTC              2
#endif

#define PIN0     0
#define PIN1     1
#define PIN2     2
#define PIN3     3
#define PIN4     4
#define PIN5     5
#define PIN6     6
#define PIN7     7
#define PIN8     8
#define PIN9     9
#define PIN10    10
#define PIN11    11
#define PIN12    12
#define PIN13    13
#define PIN14    14
#define PIN15    15

// for MODER REGISTER
#define GPIO_MODE_INPUT     (0b00)
#define GPIO_MODE_OUTPUT    (0b01)
#define GPIO_MODE_ALTFUN    (0b10)
#define GPIO_MODE_ANALOG    (0b11)


// for OTYBE REGISTER

#define PUSH_PULL    0
#define OPEN_DRAIN   1


//for OSPEED REGISTER

#define  LowSpeed      (0)
#define  MediumSpeed   (0b1)
#define  HighSpeed     (0b10)
#define  VeryHighSpeed (0b11)

// for PUPD REGISTER

#define NO_PUPD    (0b0)
#define PULL_UP   (0b1)
#define PULL_DOWN (0b10)


// FOR ODR REGISTER

#define PIN_HIGH      1
#define PIN_LOW       0


// FOR LOCKER LCKR REGISTER

#define BIT_LOCKED       1
#define BIT_NOT_LOCKED   0




void GPIO_Set_Pin_Direction(uint8 PORTID,uint8 PIN_Nu,uint8 Mode);
void GPIO_Set_Port_Direction(uint8 port_id , uint8 pin_start_num,uint8 pin_end_num , uint8 pin_mode);

void GPIO_Set_Output_Type(uint8 PORTID, uint8 PIN_Nu, uint8 Type);
void GPIO_Set_Pins_OutType(uint8 PORTID , uint8 First_Pin,uint32 Range,uint8 Mode);


void GPIO_Set_Output_Speed(uint8 PORTID, uint8 PIN_Nu,uint8 Speed);


void GPIO_Set_Input_Pullup_Pulldown(uint8 PORTID, uint8 PIN_Nu,uint8 Mode);

uint8 GPIO_Read_Pin(uint8 PORTDID, uint8 PIN_Nu);

void GPIO_Set_Pin_Value(uint8 PORTID, uint8 PIN_Nu, uint8 Value);
void GPIO_Set_Port_Value(uint8 port_id , uint8 pin_start_num , uint8 value);

void GPIO_Set_Port_Direction(uint8 port_id , uint8 pin_start_num,uint8 pin_end_num , uint8 pin_mode);



void GPIO_Fast_Set_Value(uint8 PORTID, uint8 PIN_Nu);
void GPIO_Fast_Reset_Value(uint8 PORTID, uint8 PIN_Nu);

void GPIO_Pin_Lock(uint8 PORTID, uint8 PIN_Nu, uint8 Mode);
void GPIO_Port_Lock(uint8 PORTID);

void GPIO_Alternate_Function(uint8 PORTID,uint8 PIN_Nu, uint8 Function);


#endif /* MCAL_GPIO_GPIO_INT__H_ */
