/*
 * MPU.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Mamdouh
 *
 *      v: 1.0
 */

#ifndef HAL_MPU_MPU_H_
#define HAL_MPU_MPU_H_

#define RAD_TO_DEG 57.295779513082320876798154814105

#define MPU6050_ADDRESS 0x68

#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43

// Setup MPU6050
#define MPU6050_ADDR 0xD0





typedef enum{
	// 0 is the idl state
    MPU_Idl_State,
	// 1 s a measuring state
   MPU_Measuring_State,
   // 2 Triggering state
   MPU_States_Num,

}MPU_States_Enum;



typedef enum{
	// 0 init not done
   MPU_Init_Not_Done,
   // 1 Init is done
   MPU_Init_Done,
   // 2 THE measuring not done
   MPU_Measuring_Not_Done,
   // 3 THE measuring not done
   MPU_Measuring_Done,

   MPU_Events_Num,
}MPU_Events_Enum;







// MPU6050 structure
typedef struct
{

    sint16 Accel_X_RAW;
    sint16 Accel_Y_RAW;
    sint16 Accel_Z_RAW;
    double Ax;
    double Ay;
    double Az;

    sint16 Gyro_X_RAW;
    sint16 Gyro_Y_RAW;
    sint16 Gyro_Z_RAW;
    double Gx;
    double Gy;
    double Gz;

    float Temperature;

    double KalmanAngleX;
    double KalmanAngleY;
    uint8 STATE[MPU_States_Num];
} MPU6050_t;





sint8 MPU6050_Init(I2C_Config_St * Config_St, MPU6050_t * Data_Struct);

sint8 MPU6050_Read_Accel(I2C_Config_St * Config_St, MPU6050_t * Data_Struct);


sint8 MPU6050_Read_Gyro(I2C_Config_St * Config_St, MPU6050_t * Data_Struct);


sint8 MPU6050_Read_Temp(I2C_Config_St * Config_St, MPU6050_t * Data_Struct);


sint8 MPU6050_Read_All(I2C_Config_St * Config_St, MPU6050_t * Data_Struct);

sint8 MPU6050_Get_States(MPU6050_t * Data_Struct);

#endif /* HAL_MPU_MPU_H_ */
