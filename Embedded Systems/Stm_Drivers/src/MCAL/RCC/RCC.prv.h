/*
 * RCC.prv.h
 *
 *  Created on: Nov 30, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_RCC_RCC_PRV_H_
#define MCAL_RCC_RCC_PRV_H_



#define RCC_BASE_ADDR   0X40023800


typedef struct
{
	uint32 CR;
	uint32 PLLCFGR;
	uint32 CFGR;
	uint32 CIR;
	uint32 AHB1RSTR;
	uint32 AHB2RSTR;
	uint32 reserved1;
	uint32 reserved2;
	uint32 APB1RSTR;
	uint32 APB2RSTR;
	uint32 reserved3;
	uint32 reserved4;
	uint32 AHB1ENR;
	uint32 AHB2ENR;
	uint32 reserved5;
	uint32 reserved6;
	uint32 APB1ENR;
	uint32 APB2ENR;
	uint32 reserved7;
	uint32 reserved8;
	uint32 AHB1LPENR;
	uint32 AHB2LPENR;
	uint32 reserved9;
	uint32 reserved10;
	uint32 APB1LPENR;
	uint32 APB2LPENR;
	uint32 reserved11;
	uint32 reserved12;
	uint32 BDCR;
	uint32 CSR;
	uint32 reserved13;
	uint32 reserved14;
	uint32 SSCGR;
	uint32 PLLI2SCFGR;
	uint32 reserved15;
	uint32 DCKCFGR;
}RCC_MemMap_t;

// this is a ptr mn el no3 RCC_MemMap_t
#define RCC ((volatile RCC_MemMap_t*)(RCC_BASE_ADDR))


#endif /* MCAL_RCC_RCC_PRV_H_ */
