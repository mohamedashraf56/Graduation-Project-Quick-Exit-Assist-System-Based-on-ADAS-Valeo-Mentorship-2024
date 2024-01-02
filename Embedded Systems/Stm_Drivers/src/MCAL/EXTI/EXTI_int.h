/*
 * EXTI_int.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_EXTI_EXTI_INT_H_
#define MCAL_EXTI_EXTI_INT_H_

#define PORTA              0
#define PORTB              1
#define PORTC              2

#define Enable_Interrupt   1
#define Disable_Interrupt  0


#define Rising_Edge_EN    1
#define Rising_Edge_DIS   2

#define Failing_Edge_EN    3
#define Failing_Edge_DIS   4

#define OnChange_Edge_EN   5




// ENUM FOR ONLY FUNCTION IN THIS DRIVER
enum
{
	EXTI0_ID,
	EXTI1_ID,
	EXTI2_ID,
	EXTI3_ID,
	EXTI4_ID,
	EXTI5_ID,
	EXTI6_ID,
	EXTI7_ID,
	EXTI8_ID,
	EXTI9_ID,
	EXTI10_ID,
	EXTI11_ID,
	EXTI12_ID,
	EXTI13_ID,
	EXTI14_ID,
	EXTI15_ID,
};



void MEXTI_vInit(void);

void MEXTI_vEnable_Line(uint8 PORTID ,uint8 Line_Id , uint8 Trigger);

void MEXTI_vDisable_Line(uint8 Line_Id);

void MEXTI_vSoftware_Trigger(uint8 Line_Id);

void MEXTI_vSetTrigger(uint8 Line_Id , uint8 Trigger);

void MEXTI_vEvent_Enable(uint8 Line_Id);

void MEXTI_vSetCallBack(void (*ptr)(void),uint8 Line_Id);




#endif /* MCAL_EXTI_EXTI_INT_H_ */
