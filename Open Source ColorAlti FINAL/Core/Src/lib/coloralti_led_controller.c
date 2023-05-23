/*
 * coloralti_led_controller.c
 *
 *  Created on: Apr 30, 2023
 *      Author: kking
 */

#include "coloralti_led_controller.h"

uint32_t standbyLastFlash = 0;
uint32_t standbyFlashOnLength = 1000;
uint32_t standbyFlashOffLength = 20000-1000;

void ColorAlti_displayLeds(enum ColorAltiState state, uint16_t alt)
{
	if(state == COLORALTI_STANDBY)
	{
		uint32_t standbyFlashLength = standbyFlashOnLength + standbyFlashOffLength;
		if(HAL_GetTick() > standbyLastFlash + standbyFlashLength) {
			standbyLastFlash = HAL_GetTick();
		}
		else
		{
			if(standbyLastFlash + standbyFlashOnLength < HAL_GetTick())
			{
				Strip_Progress_Bar_Single_Color(1, GREEN);
			}
			else
			{
				Strip_Clear();
			}
		}
	}

	if(state == COLORALTI_ASCENT)
	{

	}

	if(state == COLORALTI_GEARCHECK)
	{

	}

	if(state == COLORALTI_DETECT_FREEFALL_START)
	{

	}

	if(state == COLORALTI_FREEFALL)
	{

	}

	if(state == COLORALTI_APPROACHING_BREAKOFF)
	{

	}

	if(state == COLORALTI_BREAKOFF)
	{

	}

	if(state == COLORALTI_TRACK)
	{

	}

	if(state == COLORALTI_DEPLOY)
	{

	}

	if(state == COLORALTI_CANOPY)
	{

	}

	Strip_Send();
}
