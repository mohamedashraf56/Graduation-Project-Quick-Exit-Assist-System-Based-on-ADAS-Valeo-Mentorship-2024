/*
 * EXTI_prv.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_EXTI_EXTI_PRV_H_
#define MCAL_EXTI_EXTI_PRV_H_


#define EXTI_BASE_ADDR     0X40013C00

#define SYSCFG_BASE_ADDR   0X40013800

typedef struct
{
	uint32 IMR;
	uint32 EMR;
	uint32 RTSR;
	uint32 FTSR;
	uint32 SWIER;
	uint32 PR;

}MEXTI_MemMap;


typedef struct
{
	uint32 MEMRMP;
	uint32 PMC;
	uint32 EXTICR[4];
	uint32 reserved;
	uint32 CMPCR;
}MSYSCFG_MemMap;



#define EXTI  ((volatile MEXTI_MemMap *)(EXTI_BASE_ADDR))
#define SYSCFG  ((volatile MSYSCFG_MemMap *) (SYSCFG_BASE_ADDR))





#endif /* MCAL_EXTI_EXTI_PRV_H_ */
