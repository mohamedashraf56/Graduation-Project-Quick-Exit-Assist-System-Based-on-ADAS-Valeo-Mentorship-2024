/*
 * RCC.prv.h
 *
 *  Created on: Nov 30, 2023
 *      Author: Sabet & Mamdouh
 *      V 0.01
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




// pin numbers for CR reg
enum
{
	HSION,
	HSEON = 16,
	HSEBYP = 18,
	CSSON = 19,
	PLLON = 24,
};



// FOR CFGR REG
enum
{
	SW0,
	SW1,
	HPRE0 = 4,
	HPRE1,
	HPRE2,
	HPRE3,
	PPRE10 = 10,
	PPRE11,
	PPRE12,
	PPRE20,
	PPRE21,
	PPRE22,
	RTCPRE0,
	RTCPRE1,
	RTCPRE2,
	RTCPRE3,
	RTCPRE4,
	MCO1 = 22,
	I2SSCR,
	 MCO1_PRE0,
	 MCO1_PRE1,
	 MCO1_PRE2,
	 MCO2_PRE0,
	 MCO2_PRE1,
	 MCO2_PRE2,
	 MCO2 = 31,
};

// for RCC_PLLCFGR register
enum
{
	PLLSRC = 22,
};

#define HSI  0
#define HSE 1
#define PLL  2



#endif /* MCAL_RCC_RCC_PRV_H_ */
