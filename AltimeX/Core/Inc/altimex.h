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
#include "altimex_led_controller.h"
#include "altimex_state_controller.h"

class Altimex {
private:
	AltimexLedController* ledController;
	AltimexStateController* stateController;
	double tempF;
	double alt;
	uint16_t step;
	LPS22HB* barometer;
public:
	Altimex(UART_HandleTypeDef* _uart, I2C_HandleTypeDef* i2c_config, TIM_HandleTypeDef* _timer, AltimexConfig* config);
	void tick();
};



#endif /* INC_ALTIMEX_H_ */