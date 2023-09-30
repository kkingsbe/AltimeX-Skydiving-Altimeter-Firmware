/*
 * altimex.h
 *
 *  Created on: Sep 23, 2023
 *      Author: kking
 */

#ifndef INC_ALTIMEX_H_
#define INC_ALTIMEX_H_

#include "LPS22HB.h"
#include "usb.h"
#include "altimex_usb.h"
#include "altimex_led_controller.h"
#include "altimex_state_controller.h"
#include "altimex_eeprom.h"

class Altimex {
private:
	AltimexLedController* ledController;
	AltimexStateController* stateController;
	double tempF;
	double alt;
	uint32_t lastWrite; //When data was last written to storage
	uint16_t writeInterval; //How long between each write to storage
	AltimexConfig config;
	uint16_t step;
	LPS22HB* barometer;
	AltimexEeprom* eeprom;
public:
	Altimex(UART_HandleTypeDef* _uart, I2C_HandleTypeDef* i2c_config, TIM_HandleTypeDef* _timer, uint16_t _writeInterval);
	void tick();
	void print_config_to_usb();
};



#endif /* INC_ALTIMEX_H_ */
