/*
 * altimex_eeprom.h
 *
 *  Created on: Sep 23, 2023
 *      Author: kking
 */

#include "eeprom_storage.h"
#include "altimex_config.h"
#include "usb.h"

#ifndef INC_ALTIMEX_EEPROM_H_
#define INC_ALTIMEX_EEPROM_H_

#define CONFIGURATION_OFFSET 0x0
#define LOGS_OFFSET sizeof(AltimexConfig)

class AltimexEeprom {
private:
	EepromStorage* storage;
public:
	AltimexEeprom(uint16_t _address, I2C_HandleTypeDef* _i2cx);
	void save_configuration(AltimexConfig* config);
	void load_configuration(AltimexConfig* config);
};

#endif /* INC_ALTIMEX_EEPROM_H_ */
