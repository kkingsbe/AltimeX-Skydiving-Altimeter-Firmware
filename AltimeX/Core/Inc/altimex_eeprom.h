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
#define STORAGE_SIZE_BYTES 1000000

struct AltimexDataFrame {
	float tempF;
	float relAltFt;
	uint8_t state;
};

class AltimexEeprom {
private:
	EepromStorage* storage;
	uint16_t dataFrameWriteIndex;
public:
	AltimexEeprom(uint16_t _address, I2C_HandleTypeDef* _i2cx);
	void save_configuration(AltimexConfig* config);
	void load_configuration(AltimexConfig* config);
	void save_dataframe(double tempF, double relAltFt, uint8_t state);
	void load_dataframe(uint16_t index, AltimexDataFrame* dataFrame);
	void load_dataframes(uint16_t index, uint16_t amount, AltimexDataFrame* dataFrames);
};

#endif /* INC_ALTIMEX_EEPROM_H_ */
