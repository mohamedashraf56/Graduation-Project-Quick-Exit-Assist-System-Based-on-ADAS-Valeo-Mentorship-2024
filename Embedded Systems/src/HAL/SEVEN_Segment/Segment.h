/*
 * Segment.h
 *
 *  Created on: Feb 3, 2024
 *      Author: Mamdouh
 */

#ifndef HAL_SEVEN_SEGMENT_SEGMENT_H_
#define HAL_SEVEN_SEGMENT_SEGMENT_H_

#define SEGMENT_A_Port         PORTB
#define SEGMENT_A_Pin          PIN12

#define SEGMENT_B_Port         PORTB
#define SEGMENT_B_Pin          PIN13

#define SEGMENT_C_Port         PORTB
#define SEGMENT_C_Pin          PIN14

#define SEGMENT_D_Port         PORTB
#define SEGMENT_D_Pin          PIN15

#define SEGMENT_E_Port         PORTA
#define SEGMENT_E_Pin          PIN8

#define SEGMENT_F_Port         PORTA
#define SEGMENT_F_Pin          PIN9

#define SEGMENT_G_Port         PORTA
#define SEGMENT_G_Pin          PIN10

#define SEGMENT_Dot_Port       PORTA
#define SEGMENT_Dot_Pin        PIN11


void SEGMENT_Init(void);
void SEGMENT_Display(uint8 Number);


#endif /* HAL_SEVEN_SEGMENT_SEGMENT_H_ */
