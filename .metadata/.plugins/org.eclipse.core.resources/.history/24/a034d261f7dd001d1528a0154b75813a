/*
 * bmp581.h
 *
 *  Created on: Apr 16, 2023
 *      Author: kking
 */

#include "stm32f1xx_hal.h"
//#include <stdint.h>

#ifndef INC_BMP581_H_
#define INC_BMP581_H_

#define BMP_DEFAULT_ADDRESS 71
#define BMP_TEMP_MSB_REG 0xFA
#define BMP_TEMP_LSB_REG 0xFB

struct BMP_Config {
	I2C_HandleTypeDef* i2c_config;
	uint16_t address;
};

enum BMP_Measurement_Mode {
	NONE,
	TEMPERATURE,
	PRESSURE
};

extern struct BMP_Config bmpConfig;
extern enum BMP_Measurement_Mode bmpCurrentMode;

void BMP_Init_Default_Addr(I2C_HandleTypeDef* i2c_config);
void BMP_Init(I2C_HandleTypeDef* i2c_config, uint16_t address);
uint8_t BMP_Get_Device_Status();
uint16_t BMP_Read_Temperature();

#endif /* INC_BMP581_H_ */
