/*
 * bmp581.c
 *
 *  Created on: Apr 16, 2023
 *      Author: kking
 */
#include "bmp581.h"

struct BMP_Config bmpConfig;
enum BMP_Measurement_Mode bmpCurrentMode;

void BMP_Init_Default_Addr(I2C_HandleTypeDef* i2c_config)
{
	bmpConfig.i2c_config = i2c_config;
	bmpConfig.address = BMP_DEFAULT_ADDRESS;
	bmpCurrentMode = NONE;
}

void BMP_Init(I2C_HandleTypeDef* i2c_config, uint16_t address)
{
	HAL_Delay(1000);
	bmpConfig.i2c_config = i2c_config;
	bmpConfig.address = address;
	bmpCurrentMode = NONE;
}

uint8_t BMP_Get_Device_Status()
{
	HAL_StatusTypeDef res = HAL_I2C_IsDeviceReady(bmpConfig.i2c_config, (uint16_t)(bmpConfig.address<<1), 3, 5);

	if(res == HAL_OK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint16_t BMP_Read_Temperature()
{
	//Check if current mode is temperature mode
	//If not, switch modes
	if(bmpCurrentMode != TEMPERATURE)
	{
		HAL_StatusTypeDef res = HAL_I2C_Mem_Write(bmpConfig.i2c_config, (uint16_t)(bmpConfig.address<<1), 0xF4, 1, (uint8_t[]){0x2E}, 1, 5);
		HAL_Delay(10);
	}


	uint8_t rx_dat[2];
	HAL_I2C_Master_Transmit(bmpConfig.i2c_config, (uint16_t)(bmpConfig.address<<1), BMP_TEMP_MSB_REG, 1, 5);
	HAL_Delay(10);
	HAL_I2C_Master_Receive(bmpConfig.i2c_config, (uint16_t)(bmpConfig.address<<1), rx_dat, 2, 5);

	int16_t raw_temp = (rx_dat[0] << 8) | rx_dat[1];

	return 0;
}







