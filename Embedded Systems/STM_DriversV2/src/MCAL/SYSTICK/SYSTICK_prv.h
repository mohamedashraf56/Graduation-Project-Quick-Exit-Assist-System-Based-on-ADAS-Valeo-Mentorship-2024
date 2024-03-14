/*
 * SYSTICK_prv.h
 *
 *  Created on: Dec 10, 2023
 *      Author: asabe
 */

#ifndef MCAL_SYSTICK_PRV_H_
#define MCAL_SYSTICK_PRV_H_
#include "../../lip/std_types.h"

#define SYSTICK_BASE_ADDRESS (0xE000E010)

#define 	disable          0
#define 	enable          1

#define	AHB_PRE_8   0
#define	AHB               1


typedef struct{
	uint32 CTRL;
	uint32 LOAD;
	uint32 VAL;
	uint32 CALIB;

}SYSTICK_Memap;
#define SYSTICK ((volatile SYSTICK_Memap*)(SYSTICK_BASE_ADDRESS))


enum { // CTRL reg bits
	CTR_ENABLE ,
	CTR_TICKINT ,
	CTR_CLKSOURCE ,
	CTR_COUNTFLAG=16 ,
};


#endif /* MCAL_SYSTICK_PRV_H_ */
