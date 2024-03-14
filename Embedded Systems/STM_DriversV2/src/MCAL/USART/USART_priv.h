/*
 * USART_priv.h
 *
 *  Created on: Jan 27, 2024
 *      Author  : Sabet
 *      Version : 1.00
 */

#ifndef MCAL_USART_USART_PRIV_H_
#define MCAL_USART_USART_PRIV_H_

/**********************************************
			USART Register Structure
**********************************************/


#define USART_DIV_SAMPLING16(_PCLK_, _BAUD_)            ((uint32)((((uint64)(_PCLK_))*25U)/(4U*((uint64)(_BAUD_)))))
#define USART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (USART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define USART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        ((((USART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (USART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U) + 50U) / 100U)
 /* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
#define USART_BRR_SAMPLING16(_PCLK_, _BAUD_)            ((USART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
		(USART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U) + \
		(USART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

#define USART_DIV_SAMPLING8(_PCLK_, _BAUD_)             ((uint32)((((uint64)(_PCLK_))*25U)/(2U*((uint64)(_BAUD_)))))
#define USART_DIVMANT_SAMPLING8(_PCLK_, _BAUD_)         (USART_DIV_SAMPLING8((_PCLK_), (_BAUD_))/100U)
#define USART_DIVFRAQ_SAMPLING8(_PCLK_, _BAUD_)         ((((USART_DIV_SAMPLING8((_PCLK_), (_BAUD_)) - (USART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) * 100U)) * 8U) + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + ((UART DIVFRAQ & 0xF8) << 1) + (UART DIVFRAQ & 0x07U) */
#define USART_BRR_SAMPLING8(_PCLK_, _BAUD_)             ((USART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) << 4U) + \
		((USART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0xF8U) << 1U) + \
		(USART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0x07U))


/**********************************************
 				SR BITS Mapping
**********************************************/

#define USART_SR_PE_BIT	0

#define USART_SR_FE_BIT	1

#define USART_SR_NE_BIT	2

#define USART_SR_ORE_BIT	3

#define USART_SR_IDLE_BIT	4

#define USART_SR_RXNE_BIT	5

#define USART_SR_TC_BIT	6

#define USART_SR_TXE_BIT	7

#define USART_SR_LBD_BIT	8

#define USART_SR_CTS_BIT	9



/**********************************************
 				CR1 BITS Mapping
**********************************************/

#define USART_CR1_SBK_BIT	0

#define USART_CR1_RWU_BIT	1

#define USART_CR1_RE_BIT	2

#define USART_CR1_TE_BIT	3

#define USART_CR1_IDLEIE_BIT	4

#define USART_CR1_RXNEIE_BIT	5

#define USART_CR1_TCIE_BIT		6

#define USART_CR1_TXEIE_BIT	7

#define USART_CR1_PEIE_BIT		8

#define USART_CR1_PS_BIT		9

#define USART_CR1_PCE_BIT		10

#define USART_CR1_WAKE_BIT		11

#define USART_CR1_M_BIT		12

#define USART_CR1_UE_BIT		13

#define USART_CR1_OVER8_BIT    15

/**********************************************
                 CR2 BITS Mapping
**********************************************/

#define USART_CR2_ADD0_BIT		0

#define USART_CR2_ADD1_BIT		1

#define USART_CR2_ADD2_BIT		2

#define USART_CR2_ADD3_BIT		3

#define USART_CR2_LBDL_BIT	5

#define USART_CR2_LBDIE_BIT		6

#define USART_CR2_LBCL_BIT		8

#define USART_CR2_CPHA_BIT		9

#define USART_CR2_CPOL_BIT		10

#define USART_CR2_CLKEN_BIT	11

#define USART_CR2_STOP_BIT0	12

#define USART_CR2_STOP_BIT1	13

#define USART_CR2_LINEN_BIT	14


/**********************************************
 				CR3 BITS Mapping
**********************************************/

#define USART_CR3_CTSIE_BIT	10

#define USART_CR3_CTSE_BIT		9

#define USART_CR3_RTSE_BIT		8

#define USART_CR3_DMAT_BIT		7

#define USART_CR3_DMAR_BIT		6

#define USART_CR3_SCEN_BIT		5

#define USART_CR3_NACK_BIT		4

#define USART_CR3_HDSEL_BIT	3

#define USART_CR3_IRLP_BIT		2

#define USART_CR3_IREN_BIT		1

#define USART_CR3_EIE_BIT


#endif /* MCAL_USART_USART_PRIV_H_ */
