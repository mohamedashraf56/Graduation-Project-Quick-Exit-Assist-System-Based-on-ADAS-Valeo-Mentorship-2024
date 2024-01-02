/*
 * NVIC_prv.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_NVIC_NVIC_PRV_H_
#define MCAL_NVIC_NVIC_PRV_H_

#define NVIC_BASE_ADDR     0XE000E100
#define SCB_BASE_ADDR      0XE000ED00


// in SHPR1 REGISTER IN SCB in Programming manual

#define Memory_Bit_Location         4

#define Bus_Bit_Location            12

#define Usage_Bit_Location         20
// in SHPR2 REGISTER IN SCB in Programming manual

#define SVCall_Bit_Location        28

// in SHPR3 REGISTER IN SCB in Programming manual

#define PendSV_Bit_Location         20

#define SysTich_Bit_Location       28



typedef struct
{
	uint32 ISER[32];
	uint32 ICER[32];
	uint32 ISPR[32];
	uint32 ICPR[32];
	uint32 IABR[64];
	uint8  IPR[2560];
	uint32 STIR;

}NVIC_MemMap;

typedef struct
{
	uint32 CPUID;
	uint32 ICSR;
	uint32 VTOR;
	uint32 AIRCR;
	uint32 SCR;
	uint32 CCR;
	uint32 SHPR1;
	uint32 SHPR2;
	uint32 SHPR3;
	uint32 SHCSR;
	uint32 CFSR;
	uint32 HFSR;
	uint32 RESERVED;
	uint32 MMAR;
	uint32 BFAR;

}SCB_MemMap;


#define NVIC ((volatile NVIC_MemMap*)(NVIC_BASE_ADDR))

#define SCB ((volatile SCB_MemMap *)(SCB_BASE_ADDR))



#endif /* MCAL_NVIC_NVIC_PRV_H_ */
