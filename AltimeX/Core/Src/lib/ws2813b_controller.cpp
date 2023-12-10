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

TIM_HandleTypeDef* WS2813BController::timer = 0ull;
bool WS2813BController::data_sent_flag = false;

WS2813BController::WS2813BController(TIM_HandleTypeDef* _timer)
{
	WS2813BController::timer = _timer;
}

void WS2813BController::set_led (int LEDnum, int Red, int Green, int Blue)
{
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
}

#define PI 3.14159265

void WS2813BController::set_brightness (int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
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
		color = ((LED_Mod[i][1]<<16) | (LED_Mod[i][2]<<8) | (LED_Mod[i][3]));
#else
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));
#endif

		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				pwmData[indx] = 48;  // 75% of 64
			}

			else pwmData[indx] = 20;  // ~30% of 64

			indx++;
		}

	}

	//May need to be changed
	for (int i=0; i<50; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(timer, TIM_CHANNEL_2, (uint32_t *)pwmData, indx);
	while (!data_sent_flag){};
	data_sent_flag = false;
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
	set_led(LEDnum, rgb->r, rgb->g, rgb->b);
}

void WS2813BController::set_led_from_color_name(int LEDnum, enum COLOR color)
{
	struct RGB rgb;
	color_to_rgb(&rgb, color);
	set_led_from_rgb(LEDnum, &rgb);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(WS2813BController::timer, TIM_CHANNEL_2);
	WS2813BController::data_sent_flag = true;
}

void WS2813BController::clear()
{
	for(uint8_t i = 0; i < MAX_LED; i++)
	{
		set_led_from_color_name(i, CLEAR);
	}
}
