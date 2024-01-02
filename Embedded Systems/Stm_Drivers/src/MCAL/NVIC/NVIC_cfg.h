/*
 * NVIC_cfg.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Mamdouh
 */

#ifndef MCAL_NVIC_NVIC_CFG_H_
#define MCAL_NVIC_NVIC_CFG_H_


// case 0 all bits for group
#define GRUOP_4BITS    (0b000)
#define GRUOP_3BITS    (0b100)
#define GRUOP_2BITS    (0b101)
#define GRUOP_1BITS    (0b110)
#define GRUOP_0BITS    (0b111)

/* To select configuration of the Groups and subgroups bit
 * in the AIRCR REGISTER from 8 to 10 bits
 * and configure the range we will shift left to insert the
 * group and subgroup
*/
#define GROUP_CFG_SELECTED  GRUOP_2BITS

#if  GROUP_CFG_SELECTED == GRUOP_4BITS

#define GROUP_Range_Shift  0
#define Allowable_Group          16
#define Allowable_Sub            0

#endif

#if  GROUP_CFG_SELECTED == GRUOP_3BITS

#define GROUP_Range_Shift  1
#define Allowable_Group          8
#define Allowable_Sub            2

#endif

#if  GROUP_CFG_SELECTED == GRUOP_2BITS

#define GROUP_Range_Shift  2
#define Allowable_Group          4
#define Allowable_Sub            4

#endif

#if  GROUP_CFG_SELECTED == GRUOP_1BITS

#define GROUP_Range_Shift  3
#define Allowable_Group          2
#define Allowable_Sub            8

#endif

#if  GROUP_CFG_SELECTED == GRUOP_0BITS

#define GROUP_Range_Shift  4
#define Allowable_Group          0
#define Allowable_Sub            16
#endif








#endif /* MCAL_NVIC_NVIC_CFG_H_ */
