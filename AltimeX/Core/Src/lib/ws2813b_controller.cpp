/*
 * ws2813b.cpp
 *
 *  Created on: Apr 14, 2023
 *      Author: kking
 */
#include <ws2813b_controller.h>
/*
uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];  // for brightness

uint16_t pwmData[(24*MAX_LED)+50];
uint8_t datasentflag = 0;
*/

WS2813BController::WS2813BController(TIM_HandleTypeDef* _timer): timer(_timer)
{

}

void WS2813BController::set_led (int LEDnum, int Red, int Green, int Blue)
{
	this->LED_Data[LEDnum][0] = LEDnum;
	this->LED_Data[LEDnum][1] = Green;
	this->LED_Data[LEDnum][2] = Red;
	this->LED_Data[LEDnum][3] = Blue;
}

#define PI 3.14159265

void WS2813BController::set_brightness (int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		this->LED_Mod[i][0] = this->LED_Data[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			this->LED_Mod[i][j] = (this->LED_Data[i][j])/(tan(angle));
		}
	}

#endif

}

void WS2813BController::send ()
{
	uint32_t indx=0;
	uint32_t color;


	for (int i= 0; i<MAX_LED; i++)
	{
#if USE_BRIGHTNESS
		color = ((this->LED_Mod[i][1]<<16) | (this->LED_Mod[i][2]<<8) | (this->LED_Mod[i][3]));
#else
		color = ((this->LED_Data[i][1]<<16) | (this->LED_Data[i][2]<<8) | (this->LED_Data[i][3]));
#endif

		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				this->pwmData[indx] = 48;  // 75% of 64
			}

			else this->pwmData[indx] = 20;  // ~30% of 64

			indx++;
		}

	}

	//May need to be changed
	for (int i=0; i<50; i++)
	{
		this->pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(this->timer, TIM_CHANNEL_2, (uint32_t *)this->pwmData, indx);
	while (!this->data_sent_flag){};
	this->data_sent_flag = 0;
}

void WS2813BController::color_to_rgb(struct RGB* rgb, enum COLOR color)
{
	if(color == GREEN) {
		rgb->r = 0;
		rgb->g = 255;
		rgb->b = 20;
	}

	if(color == YELLOW) {
		rgb->r = 255;
		rgb->g = 255;
		rgb->b = 0;
	}

	if(color == RED) {
		rgb->r = 255;
		rgb->g = 0;
		rgb->b = 0;
	}

	if(color == PURPLE) {
		rgb->r = 255;
		rgb->g = 0;
		rgb->b = 255;
	}

	if(color == SKYBLUE) {
		rgb->r = 0;
		rgb->g = 255;
		rgb->b = 200;
	}

	if(color == CLEAR) {
		rgb->r = 0;
		rgb->g = 0;
		rgb->b = 0;
	}
}

void WS2813BController::set_led_from_rgb(int LEDnum, struct RGB* rgb)
{
	this->set_led(LEDnum, rgb->r, rgb->g, rgb->b);
}

void WS2813BController::set_led_from_color_name(int LEDnum, enum COLOR color)
{
	struct RGB rgb;
	this->color_to_rgb(&rgb, color);
	this->set_led_from_rgb(LEDnum, &rgb);
}

void WS2813BController::hal_tim_pwm_pulse_finished_callback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(this->timer, TIM_CHANNEL_2);
	this->data_sent_flag=1;
}

void WS2813BController::clear()
{
	for(uint8_t i = 0; i < MAX_LED; i++)
	{
		this->set_led_from_color_name(i, CLEAR);
	}
}