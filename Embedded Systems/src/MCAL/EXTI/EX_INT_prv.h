/*
 * EX_INT_prv.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Sabet & Mamdoh
 *      version 0.01
 */

#ifndef MCAL_EXTI_EX_INT_PRV_H_
#define MCAL_EXTI_EX_INT_PRV_H_
#include "../../lip/std_types.h"
#define EX_INT_Base_Address (0x40013C00)
#define SYSCFG_Base_Address (0x40013800)

typedef struct{
uint32	IMR ;
uint32	EMR ;
uint32	RTSR ;
uint32	FTSR ;
uint32	SWIER ;
uint32	PR ;

} EX_INTMamap ;
#define EX_INT ((volatile EX_INTMamap*)(EX_INT_Base_Address))

typedef struct{                //SYSCFG REG to implement the external interrupt in which port
uint32	MEMRMP ;
uint32	PMC ;
uint32	EXTICR[4] ;  /*           arr[line/4]              start bit to change is (lin%4 *4) */
uint32	CMPCR ;
} SYSCFG_Mamap ;

#define SYSCFG ((volatile SYSCFG_Mamap*)(SYSCFG_Base_Address))

#endif /* MCAL_EXTI_EX_INT_PRV_H_ */
