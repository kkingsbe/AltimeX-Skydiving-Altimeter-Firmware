/*
 * altimex_storage.c
 *
 *  Created on: Sep 21, 2023
 *      Author: kking
 */


#include "altimex_storage.h"

HAL_StatusTypeDef STORAGE_read(I2C_HandleTypeDef* i2cx, uint16_t offset, size_t len, uint8_t* data)
{
	HAL_StatusTypeDef read_res = HAL_I2C_Mem_Read(i2cx, 0xA0, offset, 2, data, len, 1000);
	HAL_Delay(100);
	return read_res;
}

HAL_StatusTypeDef STORAGE_write(I2C_HandleTypeDef* i2cx, uint16_t offset, size_t len, uint8_t* data)
{
	HAL_StatusTypeDef write_res = HAL_I2C_Mem_Write(i2cx, 0xA1, offset, 2, data, len, 1000);
	HAL_Delay(100);
	return write_res;
}