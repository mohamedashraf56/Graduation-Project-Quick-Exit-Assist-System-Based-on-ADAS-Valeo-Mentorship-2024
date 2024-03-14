/*
 * I2C_int.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Mamdouh  & SABET
 */

#ifndef MCAL_I2C_I2C_INT_H_
#define MCAL_I2C_I2C_INT_H_

#define I2C_Fast_Mode        1
#define I2C_Standard_Mode    0

#define DUTY_Fast_Mode_400khz    1

typedef struct
{
	uint8 I2C_Number; // 1,2,3
	uint8 FREQ_Mhz;  // 2Mhz , 4Mhz ..... 50Mhz
	uint8 I2C_Mode_Selection; // I2C_Fast_Mode , I2C_Standard_Mode
	uint8 I2C_Duty;  // DUTY_Fast_Mode_400khz
	uint8 STATE;

}I2C_Config_St;




sint8 I2C_Init(I2C_Config_St * Config_St);
sint8 I2C_Gpio_Config(I2C_Config_St * Config_St);

uint8 I2C_Read_Byte(I2C_Config_St * Config_St,uint8 SLAVE_Address,uint8 REGISTER_Address);

uint8 I2C_Write_Byte(I2C_Config_St * Config_St,uint8 SLAVE_Address,uint8 REGISTER_Address, uint8 Data);


#endif /* MCAL_I2C_I2C_INT_H_ */
