/*
 * altimex_storage.h
 *
 *  Created on: Sep 21, 2023
 *      Author: kking
 */

#ifndef INC_ALTIMEX_STORAGE_H_
#define INC_ALTIMEX_STORAGE_H_

#include "stm32f1xx_hal.h"
HAL_StatusTypeDef STORAGE_read(I2C_HandleTypeDef* i2cx, uint16_t offset, size_t len, uint8_t* data);
HAL_StatusTypeDef STORAGE_write(I2C_HandleTypeDef* i2cx, uint16_t offset, size_t len, uint8_t* data);

#endif /* INC_ALTIMEX_STORAGE_H_ */
