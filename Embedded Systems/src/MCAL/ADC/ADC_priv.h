/*
 * ADC_priv.h
 *
 *  Created on: Jan 26, 2024
 *      Author: asabe
 */

#ifndef MCAL_ADC_ADC_PRIV_H_
#define MCAL_ADC_ADC_PRIV_H_
#include "../../lip/std_types.h"

/*define MADC1_MemMap_t*/

#define ADC_BASE_ADD  0x40012000

typedef struct
{
	uint32 SR              ;
	uint32 CR1             ;
	uint32 CR2             ;
	uint32 SMPR1           ;
	uint32 SMPR2           ;
	uint32 JOFR1           ;
	uint32 JOFR2           ;
	uint32 JOFR3           ;
	uint32 JOFR4           ;
	uint32 HTR              ;
	uint32 LTR               ;
	uint32 SQR [3]         ;
	uint32 JSQR            ;
	uint32 JDR1            ;
	uint32 JDR2            ;
	uint32 JDR3            ;
	uint32 JDR4            ;
	uint32 DR              ;
	uint32 REVERSE [55]    ;/*due to offset address of CCR is relative to ADC1 base address + 0x300*/
	uint32 CCR             ;
}MADC1_MemMap;

#define ADC ((volatile MADC1_MemMap *)(ADC_BASE_ADD))




#define ENABLE   (1u)
#define DISABLE   (0u)

/********************************************ADC status register (ADC_SR)***************************************/
#define ADC_SR_AWD_BIT      0
#define ADC_SR_EOC_BIT      1
#define ADC_SR_JEOC_BIT     2
#define ADC_SR_JSTRT_BIT    3
#define ADC_SR_STRT_BIT     4
#define ADC_SR_OVR_BIT      5

/*********************************************** ADC control register 1 (ADC_CR1)*******************************/
#define ADC_CR1_AWDCH_BIT0      0
#define ADC_CR1_AWDCH_BIT1      1
#define ADC_CR1_AWDCH_BIT2      2
#define ADC_CR1_AWDCH_BIT3      3
#define ADC_CR1_AWDCH_BIT4      4

#define ADC_CR1_EOCIE_BIT       5

#define ADC_CR1_AWDIE_BIT       6

#define ADC_CR1_JEOCIE_BIT      7

#define ADC_CR1_SCAN_BIT        8

#define ADC_CR1_AWDSGL_BIT      9

#define ADC_CR1_JAUTO_BIT       10

#define ADC_CR1_DISCEN_BIT      11

#define ADC_CR1_JDISCEN_BIT     12

#define ADC_CR1_DISCNUM_BIT0    13
#define ADC_CR1_DISCNUM_BIT1    14
#define ADC_CR1_DISCNUM_BIT2    15

#define ADC_CR1_JAWDEN_BIT      22

#define ADC_CR1_AWDEN_BIT       23

#define ADC_CR1_RES_BIT0        24
#define ADC_CR1_RES_BIT1        25

#define ADC_CR1_OVRIE_BIT       26

/**************************************** ADC control register 2 (ADC_CR2)***************************/

#define ADC_CR2_ADON_BIT      0

#define ADC_CR2_CONT_BIT      1

#define ADC_CR2_DMA_BIT       8

#define ADC_CR2_DDS_BIT       9

#define ADC_CR2_EOCS_BIT      10

#define ADC_CR2_ALIGN_BIT     11

#define ADC_CR2_JEXTSEL_BIT0  16
#define ADC_CR2_JEXTSEL_BIT1  17
#define ADC_CR2_JEXTSEL_BIT2  18
#define ADC_CR2_JEXTSEL_BIT3  19

#define ADC_CR2_JEXTEN_BIT0   20
#define ADC_CR2_JEXTEN_BIT1   21

#define ADC_CR2_JSWSTART_BIT  22

#define ADC_CR2_EXTSEL_BIT0   24
#define ADC_CR2_EXTSEL_BIT1   25
#define ADC_CR2_EXTSEL_BIT2   26
#define ADC_CR2_EXTSEL_BIT3   27

#define ADC_CR2_EXTEN_BIT0    28
#define ADC_CR2_EXTEN_BIT1    29

#define ADC_CR2_SWSTART_BIT   30

/****************************************ADC sample time register 1 (ADC_SMPR1)*****************************************/


#define ADC_CR2_ADCPRE_BIT0   16
#define ADC_CR2_ADCPRE_BIT1   17


#define ADC_CR2_VBATE_BIT     22


#define ADC_CR2_TSVREFE_BIT   23


#define ADC_SQR1_L_BIT0       20


#define ADC_SQR3_SQ1_BIT0       0
#define ADC_SQR3_SQ2_BIT0       5
#define ADC_SQR3_SQ3_BIT0       10
#define ADC_SQR3_SQ4_BIT0       15
#define ADC_SQR3_SQ5_BIT0       20
#define ADC_SQR3_SQ6_BIT0       25
#define ADC_SQR2_SQ7_BIT0       0
#define ADC_SQR2_SQ8_BIT0       5
#define ADC_SQR2_SQ9_BIT0       10
#define ADC_SQR2_SQ10_BIT0       15
#define ADC_SQR2_SQ11_BIT0       20
#define ADC_SQR2_SQ12_BIT0       25

#define ADC_SQR1_SQ13_BIT0       0
#define ADC_SQR1_SQ14_BIT0       5
#define ADC_SQR1_SQ15_BIT0       10
#define ADC_SQR1_SQ16_BIT0       15







#endif /* MCAL_ADC_ADC_PRIV_H_ */
