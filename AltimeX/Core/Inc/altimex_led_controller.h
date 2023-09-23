/*
 * coloralti_led_controller.h
 *
 *  Created on: Apr 30, 2023
 *      Author: kking
 */

#ifndef INC_ALTIMEX_LED_CONTROLLER_H_
#define INC_ALTIMEX_LED_CONTROLLER_H_
#include <altimex_state_controller.h>
#include <led_strip.h>
#include "altimex_config.h"

class AltimexLedController {
private:
	AltimexConfig* config;
	LedStrip* ledStrip;
public:
	AltimexLedController(AltimexConfig* _config, TIM_HandleTypeDef* _timer);
	void display_leds(enum AltimexState state, uint16_t step, uint16_t alt);
};

#endif /* INC_ALTIMEX_LED_CONTROLLER_H_ */
