/*
 * TIM10_11_prv.h
 *
 *  Created on: Dec 30, 2023
 *      Author: asabe
 */

#ifndef MCAL_TIM10_11_PWM_TIM10_11_PRV_H_
#define MCAL_TIM10_11_PWM_TIM10_11_PRV_H_


/****************************************************************/
/**     (General-purpose timers)Timer10 and Timer11 register      **/
/****************************************************************/
/****************************************************************/
/**     Timer10 and Timer11 control register1 bits(CR1)           **/
/****************************************************************/
/*  Counter enable                 */
#define TIM10_11_CR1_CEN_BIT   0
/*  Update disable                 */
#define TIM10_11_CR1_UDIS_BIT  1
/*  Update request source          */
#define TIM10_11_CR1_URS_BIT   2
/*  One pulse mode                 */
#define TIM10_11_CR1_OPM_BIT   3
/*  Direction                      */
/*  Auto-reload preload enable     */
#define TIM10_11_CR1_ARPE_BIT  7
/*  Clock division                 */
#define TIM10_11_CR1_CKD_BIT0  8
#define TIM10_11_CR1_CKD_BIT1  9

/****************************************************************/
/**        Timer10 and Timer11 control register2 bits(CR2)        **/
/****************************************************************/
/*  TI1 selection                         */
#define TIM2_TO_TIM5_CR2_CCDS_BIT     3
/*  Master mode selection                 */
#define TIM2_TO_TIM5_CR2_MMS_BIT0     4
#define TIM2_TO_TIM5_CR2_MMS_BIT1     5
#define TIM2_TO_TIM5_CR2_MMS_BIT2     6
/*  Capture/compare DMA selection         */
#define TIM2_TO_TIM5_CR2_TI1S_BIT     7


/****************************************************************/
/**    Timer10 and Timer11 DMA/interrupt enable register(DIER)    **/
/****************************************************************/
/*  Update interrupt enable               */
#define TIM10_11_DIER_UIE_BIT        0
/*  Capture/Compare 1 interrupt enable    */
#define TIM10_11_DIER_CC1IE_BIT      1
/*  Capture/Compare 2 interrupt enable    */

/****************************************************************/
/**             Timer10 and Timer11 status register (SR)             **/
/****************************************************************/
/*  Update interrupt flag               */
#define TIM10_11_SR_UIF_BIT       0
/*  Capture/Compare 1 interrupt flag    */
#define TIM10_11_SR_CC1IF_BIT     1
/*  Capture/Compare 2 interrupt flag    */

#define TIM10_11_SR_CC1OF_BIT     9

/****************************************************************/
/**     TIMER2 TO TIIMER5 event generation register (EGR)      **/
/****************************************************************/
/*  Update generation                          */
#define TIM10_11_EGR_UG_BIT      0
/*  Capture/Compare 1 generation               */
#define TIM10_11_EGR_CC1G_BIT    1

/****************************************************************/
/** TTimer10 and Timer11 capture/compare mode register 1 (CCMR1)  **/
/****************************************************************/
/*****************Output compare mode****************************/
/*  Capture/Compare 1 selection      */
#define TIM10_11_CCMR1_CC1S_BIT0      0
#define TIM10_11_CCMR1_CC1S_BIT1      1
/*  Output Compare 1 fast enable     */
#define TIM10_11_CCMR1_OC1FE_BIT      2
/*  Output Compare 1 preload enable  */
#define TIM10_11_CCMR1_OC1PE_BIT      3
/*  Output Compare 1 mode            */
#define TIM10_11_CCMR1_OC1M_BIT0      4
#define TIM10_11_CCMR1_OC1M_BIT1      5
#define TIM10_11_CCMR1_OC1M_BIT2      6

/*****************Output compare mode****************************/
/*  Input capture 1 prescaler        */
#define TIM10_11_CCMR1_IC1PSC_BIT0    2
#define TIM10_11_CCMR1_IC1PSC_BIT1    3
/*  Input capture 1 filter           */
#define TIM10_11_CCMR1_IC1F_BIT0      4
#define TIM10_11_CCMR1_IC1F_BIT1      5
#define TIM10_11_CCMR1_IC1F_BIT2      6
#define TIM10_11_CCMR1_IC1F_BIT3      7

/****************************************************************/
/**  Timer10 and Timer11 capture/compare enable register (CCER)  **/
/****************************************************************/
/*  Capture/Compare 1 output enable                  */
#define TIM10_11_CCER_CC1E_BIT     0
/*  Capture/Compare 1 output polarity                */
#define TIM10_11_CCER_CC1P_BIT     1
/*  Capture/Compare 1 complementary output polarity  */
#define TIM10_11_CCER_CC1NP_BIT    3
/*  Capture/Compare 2 output enable                  */




#endif /* MCAL_TIM10_11_PWM_TIM10_11_PRV_H_ */
