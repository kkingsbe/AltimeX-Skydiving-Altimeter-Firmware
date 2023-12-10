/*
 * led_strip.c
 *
 *  Created on: Apr 15, 2023
 *      Author: kking
 */

#include <led_strip.h>

LedStrip::LedStrip(TIM_HandleTypeDef* _timer): timer(_timer), controller(new WS2813BController(timer))
{

}

void LedStrip::progress_bar_single_color(uint8_t num_filled, enum COLOR color)
{
	this->clear();
	if(num_filled > MAX_LED) num_filled = MAX_LED;
	for(uint8_t i = 0; i < num_filled; i++) {
		controller->set_led_from_color_name(i, color);
	}
}

void LedStrip::clear()
{
	controller->clear();
}

void LedStrip::send()
{
	controller->send();
}

void LedStrip::set_brightness(int brightness)
{
	controller->set_brightness(brightness);
}
