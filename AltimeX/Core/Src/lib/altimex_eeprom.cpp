/*
 * altimex_eeprom.cpp
 *
 *  Created on: Sep 23, 2023
 *      Author: kking
 */

#include "altimex_eeprom.h"

AltimexEeprom::AltimexEeprom(uint16_t _address, I2C_HandleTypeDef* _i2cx):
	storage(new EepromStorage(_address, _i2cx)),
	dataFrameWriteIndex(0)
{

}

void AltimexEeprom::save_configuration(AltimexConfig* config)
{
	uint8_t data[sizeof(AltimexConfig)]; // Create a byte array of the same size as the struct

	// Copy the struct data into the byte array
	memcpy(data, config, sizeof(AltimexConfig));

	storage->write_from(CONFIGURATION_OFFSET, sizeof(AltimexConfig), data);
}

void AltimexEeprom::load_configuration(AltimexConfig* config)
{
	uint8_t data[sizeof(AltimexConfig)];
	HAL_StatusTypeDef status = storage->read(CONFIGURATION_OFFSET, sizeof(AltimexConfig), data);

    if (status == HAL_OK) {
        // Copy the data from the byte array into the config struct
        memcpy(config, data, sizeof(AltimexConfig));
    	STM_USB::println("Loaded configuration!");
    } else {
    	STM_USB::println("Error loading configuration from EEPROM");
    }
}

void AltimexEeprom::save_dataframe(double tempF, double relAltFt, uint8_t state)
{
	if((dataFrameWriteIndex + 1) * sizeof(AltimexDataFrame) > STORAGE_SIZE_BYTES) {
		return;
	}

	float f_tempF = (float)tempF;
	float f_relAltFt = (float)relAltFt;

	AltimexDataFrame dataFrame = {
			f_tempF,
			f_relAltFt,
			state
	};

	uint8_t data_bytes[sizeof(AltimexDataFrame)];
	memcpy(data_bytes, &dataFrame, sizeof(AltimexDataFrame));
	HAL_StatusTypeDef status = storage->write_from(LOGS_OFFSET + (dataFrameWriteIndex * sizeof(AltimexDataFrame)), sizeof(AltimexDataFrame), data_bytes);
	//load_dataframe(dataFrameWriteIndex, &dataFrame);
	dataFrameWriteIndex ++;
}

void AltimexEeprom::load_dataframe(uint16_t index, AltimexDataFrame* dataFrame)
{
	uint8_t data[sizeof(AltimexDataFrame)];
	HAL_StatusTypeDef status = storage->read(LOGS_OFFSET + (sizeof(AltimexDataFrame) * index), sizeof(AltimexDataFrame), data);
	memcpy(dataFrame, data, sizeof(AltimexDataFrame));
}

void AltimexEeprom::load_dataframes(uint16_t index, uint16_t amount, AltimexDataFrame* dataFrames)
{
	uint8_t data[sizeof(AltimexDataFrame) * amount];
	HAL_StatusTypeDef status = storage->read(LOGS_OFFSET + (sizeof(AltimexDataFrame) * index), sizeof(AltimexDataFrame) * amount, data);

	for(uint16_t i = 0; i < amount; i++) {
		STM_USB::print(".");
		uint8_t dfdata[sizeof(AltimexDataFrame)];
		uint32_t start_offset = i * sizeof(AltimexDataFrame);
		for(uint16_t j = 0; j < sizeof(AltimexDataFrame); j++) {
			uint32_t location = start_offset + j;
			dfdata[j] = data[location];
		}
		memcpy(&dataFrames[i], dfdata, sizeof(AltimexDataFrame));
	}
}