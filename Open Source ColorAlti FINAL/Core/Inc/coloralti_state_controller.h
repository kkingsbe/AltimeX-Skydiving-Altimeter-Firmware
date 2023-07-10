/*
 * coloralti_state_controller.h
 *
 *  Created on: Apr 30, 2023
 *      Author: kking
 */

#ifndef INC_COLORALTI_STATE_CONTROLLER_H_
#define INC_COLORALTI_STATE_CONTROLLER_H_
#include "stm32f1xx_hal.h"
#include "coloralti_config.h"
#include "math.h"

enum ColorAltiState {
	COLORALTI_STANDBY,
	COLORALTI_ASCENT,
	COLORALTI_GEARCHECK,
	COLORALTI_DETECT_FREEFALL_START,
	COLORALTI_FREEFALL,
	COLORALTI_APPROACHING_BREAKOFF,
	COLORALTI_BREAKOFF,
	COLORALTI_TRACK,
	COLORALTI_DEPLOY,
	COLORALTI_CANOPY
};

extern enum ColorAltiState StateController_currentState;

void StateController_updateState(struct ColorAltiConfig* config, uint16_t alt);

#endif /* INC_COLORALTI_STATE_CONTROLLER_H_ */
