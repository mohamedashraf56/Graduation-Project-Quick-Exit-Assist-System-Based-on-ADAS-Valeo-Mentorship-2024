/*
 * GPIO_int_.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_GPIO_GPIO_INT__H_
#define MCAL_GPIO_GPIO_INT__H_




#define GPIO_PORTA     0
#define GPIO_PORTB     1
#define GPIO_PORTC     2

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

#define GPIO_MODE_RANGE    two_one

// for OTYBE REGISTER

#define PUSH_PULL    0
#define OPEN_DRAIN   1


//for OSPEED REGISTER

#define  LowSpeed      (0)
#define  MediumSpeed   (0b1)
#define  HighSpeed     (0b10)
#define  VeryHighSpeed (0b11)

// for PUPD REGISTER

#define NOPUPD    (0b0)
#define PULL_UP   (0b1)
#define PULL_DOWN (0b10)

#define GPIO_PUPD_RANGE   two_one

// FOR ODR REGISTER

#define PIN_HIGH      1
#define PIN_LOW       0


// FOR LOCKER LCKR REGISTER

#define BIT_LOCKED       1
#define BIT_NOT_LOCKED   0

// for ALFUNCTION
#define AFRH_RANGE_BITS  four_one
#define AFRL_RANGE_BITS  four_one


enum {
  AF_PIN0 = 0,
  AF_PIN1 = 4,
  AF_PIN2 = 8,
  AF_PIN3 = 12,
  AF_PIN4 = 16,
  AF_PIN5 = 20,
  AF_PIN6 = 24,
  AF_PIN7 = 28,
  AF_PIN8 = 0,
  AF_PIN9 = 4,
  AF_PIN10= 8,
  AF_PIN11= 12,
  AF_PIN12 =16,
  AF_PIN13 =20,
  AF_PIN14 =24,
  AF_PIN15 =28,
};



void GPIO_SetPin_Direction(uint8 PORTID,uint8 PIN_Nu,uint8 Mode);
void GPIO_SetPins_Direction (uint8 PORTID , uint8 First_Pin,uint32 Range,uint8 Mode);

void GPIO_SetOutput_Type(uint8 PORTID, uint8 PIN_Nu, uint8 Type);
void GPIO_SetPins_OutType(uint8 PORTID , uint8 First_Pin,uint32 Range,uint8 Mode);


void GPIO_SetOutput_Speed(uint8 PORTID, uint8 PIN_Nu,uint8 Speed);
void GPIO_SetPins_Speed (uint8 PORTID , uint8 First_Pin,uint32 Range,uint8 Mode);


void GPIO_SetInput_PuPd(uint8 PORTID, uint8 PIN_Nu,uint8 Mode);

uint8 GPIO_ReadPin(uint8 PORTDID, uint8 PIN_Nu);

void GPIO_SetPin_Value(uint8 PORTID, uint8 PIN_Nu, uint8 Value);
void GPIO_SetPins_Value (uint8 PORTID , uint8 First_Pin,uint32 Range,uint8 Value);


void GPIO_FastSet_Value(uint8 PORTID, uint8 PIN_Nu);
void GPIO_FastReset_Value(uint8 PORTID, uint8 PIN_Nu);


void GPIO_PinLock(uint8 PORTID, uint8 PIN_Nu, uint8 Mode);

void GPIO_HAlternate_Function(uint8 PORTID,uint8 PIN_Nu, uint8 Function);

void GPIO_LAlternate_Function(uint8 PORTID, uint8 PIN_Nu, uint8 Function);


void GPIO_PortLock(uint8 PORTID,uint8 Mode);


// for ports
void GPIO_Write_Pins(uint8 PORTID,uint8 PIN_Nu,uint8 Range,uint16 Value);

void GPIO_Write_Port(uint8 PORTID,uint16 Value);
uint16 GPIO_Read_Port(uint8 PORTID);







#endif /* MCAL_GPIO_GPIO_INT__H_ */
