/*
 * altimex_storage.h
 *
 *  Created on: Sep 21, 2023
 *      Author: kking
 */
#include "stm32f1xx_hal.h"

#ifndef INC_EEPROM_STORAGE_H_
#define INC_EEPROM_STORAGE_H_

class EepromStorage {
private:
	uint16_t currentOffset;
	uint16_t readAddress;
	uint16_t writeAddress;
	I2C_HandleTypeDef* i2cx;
public:
	EepromStorage(uint16_t _address, I2C_HandleTypeDef* _i2cx);
	HAL_StatusTypeDef read(uint16_t offset, size_t len, uint8_t* data);
	HAL_StatusTypeDef write(size_t size, uint8_t* data);
	HAL_StatusTypeDef write_from(uint16_t offset, size_t size, uint8_t* data);
	void set_offset(uint16_t newOffset);
};

#endif /* INC_EEPROM_STORAGE_H_ */