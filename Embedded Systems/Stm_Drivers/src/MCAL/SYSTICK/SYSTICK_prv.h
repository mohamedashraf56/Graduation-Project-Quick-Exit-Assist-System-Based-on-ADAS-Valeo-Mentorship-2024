/*
 * SYSTICK_prv.h
 *
 *  Created on: Dec 12, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_SYSTICK_SYSTICK_PRV_H_
#define MCAL_SYSTICK_SYSTICK_PRV_H_

#define SYSTICK_BASE_ADDR 0XE000E010



typedef struct
{
	uint32 CTRL;
	uint32 LOAD;
	uint32 VAL;
	uint32 CALIB;
}SYSTICK_MemMap;


#define STK ((volatile SYSTICK_MemMap *)(SYSTICK_BASE_ADDR))



#endif /* MCAL_SYSTICK_SYSTICK_PRV_H_ */
