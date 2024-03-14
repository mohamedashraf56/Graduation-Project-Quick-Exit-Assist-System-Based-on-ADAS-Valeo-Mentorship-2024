/*
 * I2C_prv.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Mamdouh & SABET
 */

#ifndef MCAL_I2C_I2C_PRV_H_
#define MCAL_I2C_I2C_PRV_H_

#define I2C_1_Base_Address  0X40005400
#define I2C_2_Base_Address  0X40005800
#define I2C_3_Base_Address  0X40005C00




typedef struct
{
	uint32 I2C_CR1;
	uint32 I2C_CR2;
	uint32 I2C_OAR1;
	uint32 I2C_OAR2;
	uint32 I2C_DR;
	uint32 I2C_SR1;
	uint32 I2C_SR2;
	uint32 I2C_CCR;
	uint32 I2C_TRISE;
	uint32 I2C_FLTR;
}I2C_MemMap_t;


#define I2C_1 ((volatile I2C_MemMap_t *)(I2C_1_Base_Address))
#define I2C_2 ((volatile I2C_MemMap_t *)(I2C_2_Base_Address))
#define I2C_3 ((volatile I2C_MemMap_t *)(I2C_3_Base_Address))


#endif /* MCAL_I2C_I2C_PRV_H_ */
