/*
 * MPU.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Mamdouh
 *
 *       *      v: 1.0
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "../../MCAL/I2C/I2C_int.h"
#include "MPU.h"
const double Accel_Z_corrector = 14418.0;




sint8 MPU6050_Init(I2C_Config_St * Config_St, MPU6050_t * Data_Struct)
{
	uint8 Data;
	sint8 State;
	Data = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0x75);

	// check register who am i
	if(Data == 104)
	{
		I2C_Write_Byte(Config_St, MPU6050_ADDRESS, PWR_MGMT_1_REG  , 0);

		I2C_Write_Byte(Config_St, MPU6050_ADDRESS, SMPLRT_DIV_REG  , 0X07);

		I2C_Write_Byte(Config_St, MPU6050_ADDRESS, ACCEL_CONFIG_REG  , 0);

		I2C_Write_Byte(Config_St, MPU6050_ADDRESS, GYRO_CONFIG_REG  , 0);
		Data_Struct->STATE[MPU_Idl_State] = MPU_Init_Done;
	}
	else
	{
		Data_Struct->STATE[MPU_Idl_State] = MPU_Init_Not_Done;
		State = MPU_Init_Not_Done;
	}
	return State;
}






sint8 MPU6050_Read_Accel(I2C_Config_St * Config_St, MPU6050_t * Data_Struct)
{
	sint8 State = 0;
	uint8 TEMP_Data[6];
	if(Data_Struct->STATE[MPU_Idl_State] == MPU_Init_Done)
	{
		Data_Struct->STATE[MPU_Measuring_State] = MPU_Measuring_Not_Done;

		TEMP_Data[0] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X3B);
		TEMP_Data[1] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X3C);
		TEMP_Data[2] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X3D);
		TEMP_Data[3] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X3E);
		TEMP_Data[4] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X3F);
		TEMP_Data[5] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X40);

		Data_Struct->Accel_X_RAW = (sint16)(TEMP_Data[0] << 8 | TEMP_Data[1]);
		Data_Struct->Accel_Y_RAW = (sint16)(TEMP_Data[2] << 8 | TEMP_Data[3]);
		Data_Struct->Accel_Z_RAW = (sint16)(TEMP_Data[4] << 8 | TEMP_Data[5]);

		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> 2g
		// FS_SEL = 0. So dividing by 16384.0
		Data_Struct->Ax = Data_Struct->Accel_X_RAW / 16384.0;
		Data_Struct->Ay = Data_Struct->Accel_Y_RAW / 16384.0;
		Data_Struct->Az = Data_Struct->Accel_Z_RAW / Accel_Z_corrector;

		Data_Struct->STATE[MPU_Measuring_State] = MPU_Measuring_Done;
		State = Data_Struct->STATE[MPU_Measuring_State];
	}
	else
	{
		State = Data_Struct->STATE[MPU_Idl_State];
	}

	return State;
}







sint8 MPU6050_Read_Gyro(I2C_Config_St * Config_St, MPU6050_t * Data_Struct)
{
	uint16 State;


	uint8 TEMP_Data[6];
	if(Data_Struct->STATE[MPU_Idl_State] == MPU_Init_Done)
	{
		Data_Struct->STATE[MPU_Measuring_State] = MPU_Measuring_Not_Done;

		TEMP_Data[0] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X43);
		TEMP_Data[1] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X44);
		TEMP_Data[2] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X45);
		TEMP_Data[3] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X46);
		TEMP_Data[4] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X47);
		TEMP_Data[5] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X48);

		Data_Struct->Gyro_X_RAW = (sint16)(TEMP_Data[0] << 8 | TEMP_Data[1]);
		Data_Struct->Gyro_Y_RAW = (sint16)(TEMP_Data[2] << 8 | TEMP_Data[3]);
		Data_Struct->Gyro_Z_RAW = (sint16)(TEMP_Data[4] << 8 | TEMP_Data[5]);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> 250/s

		// FS_SEL = 0. So dividing by 131.0

		Data_Struct->Gx = Data_Struct->Gyro_X_RAW / 131.0;
		Data_Struct->Gy = Data_Struct->Gyro_Y_RAW / 131.0;
		Data_Struct->Gz = Data_Struct->Gyro_Z_RAW / 131.0;

		Data_Struct->STATE[MPU_Measuring_State] = MPU_Measuring_Done;
		State = Data_Struct->STATE[MPU_Measuring_State];
	}
	else
	{
		State = Data_Struct->STATE[MPU_Idl_State];
	}

	return State;
}





sint8 MPU6050_Read_Temp(I2C_Config_St * Config_St, MPU6050_t * Data_Struct)
{
	sint8 State;

	if(Data_Struct->STATE[MPU_Idl_State] == MPU_Init_Done)
	{
		Data_Struct->STATE[MPU_Measuring_State] = MPU_Measuring_Not_Done;

		uint8 TEMP_Data[2];
		sint16 Temperature;

		TEMP_Data[0] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X41);
		TEMP_Data[1] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X42);

		Temperature = (sint16)(TEMP_Data[0] << 8 | TEMP_Data[1]);
		Data_Struct->Temperature = (float)((sint16)Temperature / (float)340.0 + (float)36.53 );

		Data_Struct->STATE[MPU_Measuring_State] = MPU_Measuring_Done;
		State = Data_Struct->STATE[MPU_Measuring_State];
	}
	else
	{
		State = Data_Struct->STATE[MPU_Idl_State];
	}

	return State;
}



sint8 MPU6050_Read_All(I2C_Config_St * Config_St, MPU6050_t * Data_Struct)
{
	sint8 State;


	uint8 TEMP_Accel_Data[6];
	uint8 TEMP_Gyro_Data[6];
	uint8 TEMP_Temp_Data[6];

	if(Data_Struct->STATE[MPU_Idl_State] == MPU_Init_Done)
	{

		/*******************************  ACCEL ***************************************/
		Data_Struct->STATE[MPU_Measuring_State] = MPU_Measuring_Not_Done;

		TEMP_Accel_Data[0] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X3B);
		TEMP_Accel_Data[1] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X3C);
		TEMP_Accel_Data[2] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X3D);
		TEMP_Accel_Data[3] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X3E);
		TEMP_Accel_Data[4] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X3F);
		TEMP_Accel_Data[5] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X40);

		Data_Struct->Accel_X_RAW = (sint16)(TEMP_Accel_Data[0] << 8 | TEMP_Accel_Data[1]);
		Data_Struct->Accel_Y_RAW = (sint16)(TEMP_Accel_Data[2] << 8 | TEMP_Accel_Data[3]);
		Data_Struct->Accel_Z_RAW = (sint16)(TEMP_Accel_Data[4] << 8 | TEMP_Accel_Data[5]);

		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> 2g
		// FS_SEL = 0. So dividing by 16384.0
		Data_Struct->Ax = Data_Struct->Accel_X_RAW / 16384.0;
		Data_Struct->Ay = Data_Struct->Accel_Y_RAW / 16384.0;
		Data_Struct->Az = Data_Struct->Accel_Z_RAW / Accel_Z_corrector;

		/*********************************************************************************/

		/*******************************  Gyro *******************************************/
		TEMP_Gyro_Data[0] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X43);
		TEMP_Gyro_Data[1] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X44);
		TEMP_Gyro_Data[2] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X45);
		TEMP_Gyro_Data[3] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X46);
		TEMP_Gyro_Data[4] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X47);
		TEMP_Gyro_Data[5] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X48);

		Data_Struct->Gyro_X_RAW = (sint16)(TEMP_Gyro_Data[0] << 8 | TEMP_Gyro_Data[1]);
		Data_Struct->Gyro_Y_RAW = (sint16)(TEMP_Gyro_Data[2] << 8 | TEMP_Gyro_Data[3]);
		Data_Struct->Gyro_Z_RAW = (sint16)(TEMP_Gyro_Data[4] << 8 | TEMP_Gyro_Data[5]);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> 250/s

		// FS_SEL = 0. So dividing by 131.0

		Data_Struct->Gx = Data_Struct->Gyro_X_RAW / 131.0;
		Data_Struct->Gy = Data_Struct->Gyro_Y_RAW / 131.0;
		Data_Struct->Gz = Data_Struct->Gyro_Z_RAW / 131.0;

		/*********************************************************************************/

		/****************************** Temperature *************************************/

		sint16 Temperature;

		TEMP_Temp_Data[0] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X41);
		TEMP_Temp_Data[1] = I2C_Read_Byte(Config_St, MPU6050_ADDRESS, 0X42);

		Temperature = (sint16)(TEMP_Temp_Data[0] << 8 | TEMP_Temp_Data[1]);
		Data_Struct->Temperature = (float)((sint16)Temperature / (float)340.0 + (float)36.53 );

		/*********************************************************************************/

		Data_Struct->STATE[MPU_Measuring_State] = MPU_Measuring_Done;
		State = Data_Struct->STATE[MPU_Measuring_State];
	}
	else
	{
		State = Data_Struct->STATE[MPU_Idl_State];
	}

	return State;
}


sint8 MPU6050_Get_States(MPU6050_t * Data_Struct)
{
	sint8 State;

	if(Data_Struct->STATE[MPU_Idl_State] == MPU_Init_Done)
	{
		State = Data_Struct->STATE[MPU_Measuring_State];
	}
	else
	{
		State = Data_Struct->STATE[MPU_Idl_State];
	}

	return State;
}
