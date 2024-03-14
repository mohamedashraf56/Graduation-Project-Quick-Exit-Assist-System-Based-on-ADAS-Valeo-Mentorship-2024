/*
 * NVIC_prv.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Sabet & Mamdouh
 *       version  0.01
 */

#ifndef MCAL_NVIC_NVIC_PRV_H_
#define MCAL_NVIC_NVIC_PRV_H_
#include "../../lip/std_types.h"

#define NVIC_BASE_ADDR (0xE000E100)
#define SCB_BASE_ADDR (0xE000ED00)

#define GROUP_SUB_16_0   (0b000)
#define GROUP_SUB_8_2    (0b100)
#define GROUP_SUB_4_4    (0b101)
#define GROUP_SUB_2_8    (0b110)
#define GROUP_SUB_0_16   (0b111)
#define  GROUP_SUB_START_BIT_IN_REG (8)
#define AIRCR_RESET_VALUE (0x05FA0000)


typedef struct
{
	uint32 ISER[32];
	uint32 ICER[32];
	uint32 ISPR[32];
	uint32 ICPR[32];
	uint32 IABR[64];
	uint8  IPR[2560];
	uint32 STIR;

}NVIC_Memap;

typedef struct{
//uint32	ACTLR ;
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
uint32 MMAR;
uint32 BFAR;
uint32 AFSR;

}SCB_Memap;



#define NVIC ((volatile NVIC_Memap*)(NVIC_BASE_ADDR))
#define SCB  ((volatile SCB_Memap *)(SCB_BASE_ADDR))





// in SHPR1 REGISTER IN SCB in Programming manual

#define Memory_Bit_Location         4

#define Bus_Bit_Location            12

#define Usage_Bit_Location         20
// in SHPR2 REGISTER IN SCB in Programming manual

#define SVCall_Bit_Location        28

// in SHPR3 REGISTER IN SCB in Programming manual

#define PendSV_Bit_Location         20

#define SysTich_Bit_Location       28


#define IPR_Control_Bits           4



#endif /* MCAL_NVIC_NVIC_PRV_H_ */
