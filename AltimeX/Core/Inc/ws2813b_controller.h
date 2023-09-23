/*
 * ws2813b.h
 *
 *  Created on: Apr 14, 2023
 *      Author: kking
 */


#ifndef INC_WS2813B_CONTROLLER_H_
#define INC_WS2813B_CONTROLLER_H_
#include "stm32f1xx_hal.h"
#include "math.h"

#define MAX_LED 10
#define USE_BRIGHTNESS 1

struct RGB {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

enum COLOR {
	GREEN,
	YELLOW,
	RED,
	PURPLE,
	SKYBLUE,
	CLEAR
};

class WS2813BController {
private:
	uint8_t LED_Data[MAX_LED][4];
	uint8_t LED_Mod[MAX_LED][4];
	uint16_t pwmData[(24*MAX_LED) + 50];
public:
	static TIM_HandleTypeDef* timer;
	static bool data_sent_flag;

	WS2813BController(TIM_HandleTypeDef* _timer);
	void set_led (int LEDnum, int Red, int Green, int Blue);
	void set_brightness (int brightness);  // 0-45
	void send ();
	void color_to_rgb(struct RGB* rgb, enum COLOR color);
	void set_led_from_rgb(int LEDnum, struct RGB* rgb);
	void set_led_from_color_name(int LEDnum, enum COLOR color);
	void clear();
};
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);


#endif /* INC_WS2813B_CONTROLLER_H_ */
