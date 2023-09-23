/*
 * coloralti_led_controller.c
 *
 *  Created on: Apr 30, 2023
 *      Author: kking
 */

#include <altimex_led_controller.h>

uint32_t standbyLastFlash = 0;
uint32_t lastLedTurnonTime = 0;

AltimexLedController::AltimexLedController(AltimexConfig* _config, TIM_HandleTypeDef* _timer):
		config(_config),
		ledStrip(new LedStrip(_timer))
{
	this->ledStrip->clear();
}

void AltimexLedController::display_leds(enum AltimexState state, uint16_t step, uint16_t alt)
{
	//Periodically flashes to show that the device is on
	if(state == ALTIMEX_STANDBY)
	{
		uint32_t standbyFlashLength = this->config->standbyFlashOnLength + this->config->standbyFlashOffLength;
		this->ledStrip->set_brightness(this->config->standbyBrightness);

		//If board has just been turned on
		if(standbyLastFlash == 0 && HAL_GetTick() < 3000)
		{
			uint8_t on = (step) % 2 == 0;
			uint8_t leds = on * this->config->numLeds;
			this->ledStrip->progress_bar_single_color(leds, PURPLE);
		}
		else {
			//If the current time is greater than the last flash time + the flash length, we are onto a new flash now.
			if(HAL_GetTick() > standbyLastFlash + standbyFlashLength) {
				standbyLastFlash = HAL_GetTick();
			}
			else
			{
				//If the current time is greater than the last flash time + the flash, we are in the on portion of the flash.
				if(standbyLastFlash + this->config->standbyFlashOffLength < HAL_GetTick())
				{
					this->ledStrip->progress_bar_single_color(this->config->numLeds, GREEN);
				}
				else
				{
					this->ledStrip->clear();
				}
			}
		}
	}

	//Led bar with top led flashing. Full when at gear check altitude
	if(state == ALTIMEX_ASCENT)
	{
		this->ledStrip->set_brightness(this->config->brightness);
		uint32_t standbyFlashLength = this->config->standbyFlashOnLength + this->config->standbyFlashOffLength;

		//If the current time is greater than the last flash time + the flash length, we are onto a new flash now.
		if(HAL_GetTick() > standbyLastFlash + standbyFlashLength) {
			standbyLastFlash = HAL_GetTick();
		}
		else
		{
			//If the current time is greater than the last flash time + the flash, we are in the on portion of the flash.
			if(standbyLastFlash + this->config->standbyFlashOffLength < HAL_GetTick())
			{
				this->ledStrip->progress_bar_single_color(this->config->numLeds, YELLOW);
			}
			else
			{
				this->ledStrip->clear();
			}
		}

		/*
		uint8_t flash = (step / 5) % 2 == 0;
		uint8_t i = (config->numLeds * (alt / (double)config->gearCheckAlt)) + 1;
		if(flash) i++;
		Strip_Progress_Bar_Single_Color(i, GREEN);
		*/
	}

	//Flashes green for a few secs
	if(state == ALTIMEX_GEARCHECK)
	{
		this->ledStrip->set_brightness(this->config->brightness);
		uint8_t flash = (step / 7) % 2 == 0;
		this->ledStrip->progress_bar_single_color(flash * this->config->numLeds, GREEN);
	}

	//Solid blue while awaiting jump
	if(state == ALTIMEX_DETECT_FREEFALL_START)
	{
		this->ledStrip->set_brightness(this->config->brightness);
		this->ledStrip->progress_bar_single_color(this->config->numLeds, SKYBLUE);
	}

	//LED bar fills up approaching breakoff altitude + 1500ft
	if(state == ALTIMEX_FREEFALL)
	{
		this->ledStrip->set_brightness(this->config->brightness);
		uint8_t leds = (this->config->numLeds) * (1-(float)(alt - (this->config->breakoff + 1500)) / (this->config->exit - (this->config->breakoff + 1500)));
		this->ledStrip->progress_bar_single_color(leds + 1, SKYBLUE);
	}

	//LED bar fills up approaching breakoff altitude
	if(state == ALTIMEX_APPROACHING_BREAKOFF)
	{
		this->ledStrip->set_brightness(this->config->brightness);
		uint8_t leds = (this->config->numLeds + 1) * (1-(float)(alt - this->config->breakoff) / ((this->config->breakoff + 1500) - this->config->breakoff));
		this->ledStrip->progress_bar_single_color(leds, GREEN);
	}

	//Flashes green for a few secs
	if(state == ALTIMEX_BREAKOFF)
	{
		this->ledStrip->set_brightness(this->config->brightness);
		uint8_t on = (step) % 2 == 0;
		uint8_t leds = on * this->config->numLeds;
		this->ledStrip->progress_bar_single_color(leds, GREEN);
	}

	//LED bar fills up approaching deployment altitude
	if(state == ALTIMEX_TRACK)
	{
		this->ledStrip->set_brightness(this->config->brightness);
		uint8_t leds = (this->config->numLeds + 1) * (1-(float)(alt - this->config->deploy) / ((this->config->deploy + 500) - this->config->deploy));
		this->ledStrip->progress_bar_single_color(leds, RED);
	}

	//Flashes red until detects canopy deployment
	if(state == ALTIMEX_DEPLOY)
	{
		this->ledStrip->set_brightness(this->config->brightness);
		uint8_t on = (step) % 2 == 0;
		uint8_t leds = on * this->config->numLeds;
		this->ledStrip->progress_bar_single_color(leds, RED);
	}

	//Flashes purple
	if(state == ALTIMEX_CANOPY)
	{
		this->ledStrip->set_brightness(this->config->brightness);
		uint8_t on = (step/10) % 2 == 0;
		uint8_t leds = on * this->config->numLeds;
		this->ledStrip->progress_bar_single_color(leds, PURPLE);
	}

	this->ledStrip->send();
}