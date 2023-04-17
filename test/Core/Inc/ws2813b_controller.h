/*
 * ws2813b.h
 *
 *  Created on: Apr 14, 2023
 *      Author: kking
 */

#include "stm32f1xx_hal.h"
#include "math.h"

#ifndef INC_WS2813B_H_
#define INC_WS2813B_H_

#define MAX_LED 5
#define USE_BRIGHTNESS 1

extern uint8_t LED_Data[MAX_LED][4];
extern uint8_t LED_Mod[MAX_LED][4];  // for brightness

extern uint16_t pwmData[(24*MAX_LED)+50];
extern uint8_t datasentflag;

void Set_LED (int LEDnum, int Red, int Green, int Blue);
void Set_Brightness (int brightness);  // 0-45
void WS2813_Send (TIM_HandleTypeDef htim2);


#endif /* INC_WS2813B_H_ */
