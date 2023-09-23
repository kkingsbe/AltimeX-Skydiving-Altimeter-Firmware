/*
 * coloralti_state_controller.c
 *
 *  Created on: Apr 30, 2023
 *      Author: kking
 */

#include <altimex_state_controller.h>

AltimexStateController::AltimexStateController(AltimexConfig* _config):
		config(_config),
		currentState(ALTIMEX_STANDBY),
		testingAscent(false),
		ascentTestStart(0),
		gearCheckNotificationStart(0),
		displayedGearCheck(false),
		prevAlt(0.0),
		freefallTest(true),
		freefallTestStart(0),
		freefallStartAlt(0.0),
		deployTestPrevAlt(0.0),
		deployTestPrevTime(0),
		deployTest(false),
		deployTestStart(0),
		deployTestStartAlt(0.0)
{

}

enum AltimexState AltimexStateController::get_state()
{
	return this->currentState;
}

void AltimexStateController::update_state(double alt)
{
	if(currentState == ALTIMEX_STANDBY)
	{
		//If the altitude is above the ascent threshold altitude
		if(alt > config->ascentThreshold)
		{
			//If this is the first tick where above ascent threshold altitude
			if(testingAscent == 0)
			{
				testingAscent = 1;
				ascentTestStart = HAL_GetTick();
			}

			//If it was already above the ascent threshold altitude
			if(testingAscent == 1)
			{
				//If ascentThresholdTime has elapsed, transition to ASCENT state
				if(HAL_GetTick() - ascentTestStart >= config->ascentThresholdTime)
				{
					currentState = ALTIMEX_ASCENT;
				}
			}
		}

		//If the altitude is below the ascent threshold altitude
		if(alt < config->ascentThreshold)
		{
			//Set testingAscent to false if it was true
			if(testingAscent == 1)
			{
				testingAscent = 0;
			}
		}
	}

	if(currentState == ALTIMEX_ASCENT)
	{
		//If the altitude is above 10k ft, change to gear check state
		if(alt > config->gearCheckAlt)
		{
			currentState = ALTIMEX_GEARCHECK;
		}
	}

	if(currentState == ALTIMEX_GEARCHECK)
	{
		//Gear check notificiation is shown while in GEARCHECK state
		if(displayedGearCheck == 0)
		{
			gearCheckNotificationStart = HAL_GetTick();
			displayedGearCheck = 1;
		}

		//If gearCheckNotificaitonLength has elapsed, transition out of GEARCHECK state
		if(displayedGearCheck & HAL_GetTick() > gearCheckNotificationStart + config->gearCheckNotificationLength)
		{
			currentState = ALTIMEX_DETECT_FREEFALL_START;
		}
	}

	if(currentState == ALTIMEX_DETECT_FREEFALL_START)
	{
		/**
		 * What alt do we think freefall started at?
		 * What is our current altitude?
		 * How much time has elapsed?
		 * (Calculate average speed from that)
		 * If current altitude is above where we think freefall started, then start over :)
		 */

		//NOTE TO FUTURE SELF: If there are any issues with it not detecting freefall, it is probably due to sensor noise. Use a filter / moving average on the sensor data to smooth

		//If currently lower than the previously calculated altitude
		if(prevAlt > alt)
		{
			//If not currently testing for freefall, start testing for freefall
			if(freefallTest == 0)
			{
				freefallTest = 1;
				freefallTestStart = HAL_GetTick();
				freefallStartAlt = alt;
			}

			//If we have been successfully testing for freefall for longer than the threshold time
			if(freefallTest == 1 && HAL_GetTick() > freefallTestStart + config->freefallThresholdTime)
			{
				double elapsedTimeSec = (double)(HAL_GetTick() - freefallTestStart) / 1000;
				double avgSpeedFps = ((double)(freefallStartAlt - alt) / elapsedTimeSec);

				//If average speed is above 80mph
				if(avgSpeedFps >= 117.0) //80mph to fps
				{
					currentState = ALTIMEX_FREEFALL;
				}
			}
		}

		//If currently higher than previously calculated altitude
		if(prevAlt < alt)
		{
			//Stop testing for freefall
			if(freefallTest == 1)
			{
				freefallTest = 0;
			}
		}

		prevAlt = alt;
	}

	if(currentState == ALTIMEX_FREEFALL)
	{
		if(alt < config->breakoff + 1500.0)
		{
			currentState = ALTIMEX_APPROACHING_BREAKOFF;
		}
	}

	if(currentState == ALTIMEX_APPROACHING_BREAKOFF)
	{
		if(alt < config->breakoff)
		{
			currentState = ALTIMEX_BREAKOFF;
		}
	}

	if(currentState == ALTIMEX_BREAKOFF)
	{
		if(alt < config->breakoff - 500.0)
		{
			currentState = ALTIMEX_TRACK;
		}
	}

	if(currentState == ALTIMEX_TRACK)
	{
		if(alt < config->deploy)
		{
			currentState = ALTIMEX_DEPLOY;
		}
	}

	if(currentState == ALTIMEX_DEPLOY)
	{

		if(deployTest == 0)
		{
			//If average vertical speed over last two measurements is less than than 50mph
			double elapsedTimeSec = (double)(HAL_GetTick() - deployTestStart) / 1000;
			double avgSpeedFps = fabs((double)(deployTestStartAlt - alt) / elapsedTimeSec);
			if(avgSpeedFps <= 73.0) //50mph to fps
			{
				deployTest = 1;
				deployTestStart = HAL_GetTick();
				deployTestStartAlt = alt;
			}
		}
		if(deployTest == 1)
		{
			//If average vertical speed has been < 50mph for deployThresholdTime
			if(((double)(deployTestStartAlt - alt) / (double)(HAL_GetTick() - deployTestStart)) <= 73.0)
			{
				if(HAL_GetTick() > deployTestStart + config->deployTestThresholdTime)
				{
					currentState = ALTIMEX_CANOPY;
				}
			}
		}

		deployTestPrevTime = HAL_GetTick();
		deployTestPrevAlt = alt;
	}

	if(currentState == ALTIMEX_CANOPY)
	{
		/*
		//Go back into standby mode once under 100ft
		if(alt <= 100)
		{
			StateController_currentState = COLORALTI_STANDBY;
		}
		*/
	}
}
