/*
 * coloralti_led_controller.h
 *
 *  Created on: Apr 30, 2023
 *      Author: kking
 */

#ifndef INC_COLORALTI_LED_CONTROLLER_H_
#define INC_COLORALTI_LED_CONTROLLER_H_
#include "coloralti_state_controller.h"
#include "led_strip.h"

void ColorAlti_displayLeds(enum ColorAltiState state, uint16_t alt);

#endif /* INC_COLORALTI_LED_CONTROLLER_H_ */
