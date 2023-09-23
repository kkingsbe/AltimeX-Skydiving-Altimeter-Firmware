/*
 * coloralti_state_controller.h
 *
 *  Created on: Apr 30, 2023
 *      Author: kking
 */

#ifndef INC_ALTIMEX_STATE_CONTROLLER_H_
#define INC_ALTIMEX_STATE_CONTROLLER_H_
#include "stm32f1xx_hal.h"
#include "altimex_config.h"
#include "math.h"

enum AltimexState {
	ALTIMEX_STANDBY,
	ALTIMEX_ASCENT,
	ALTIMEX_GEARCHECK,
	ALTIMEX_DETECT_FREEFALL_START,
	ALTIMEX_FREEFALL,
	ALTIMEX_APPROACHING_BREAKOFF,
	ALTIMEX_BREAKOFF,
	ALTIMEX_TRACK,
	ALTIMEX_DEPLOY,
	ALTIMEX_CANOPY
};

extern enum AltimexState StateController_currentState;

class AltimexStateController {
private:
	AltimexState currentState;
	AltimexConfig* config;
	bool testingAscent; //True while validating ascent
	uint32_t ascentTestStart; //ms, the timestamp of when the altitude crossed the ascentThreshold

	uint32_t gearCheckNotificationStart; //ms, the timestamp of when the gearcheck notification was displayed
	bool displayedGearCheck; //True once gearcheck has been shown

	double prevAlt = 0; //Stores the previous altitude
	bool freefallTest; //True while validating freefall start
	uint32_t freefallTestStart; //ms, the timestamp of when freefall test started
	double freefallStartAlt; //ft, the altitude where freefall may have begun

	double deployTestPrevAlt; //Stores the previous altitude while testing for deploy
	uint32_t deployTestPrevTime; //ms, the timestamp of the previous datapoint
	bool deployTest; //1 while validating deployment test
	uint32_t deployTestStart; //ms, the timestamp for starting to validate deployment
	double deployTestStartAlt; //ft, altitude at beginning of current deployment test
public:
	AltimexStateController(AltimexConfig* _config);
	void update_state(double alt);
	enum AltimexState get_state();
};

#endif /* INC_ALTIMEX_STATE_CONTROLLER_H_ */