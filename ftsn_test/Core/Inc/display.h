/*
 * display.h
 *
 *  Created on: Apr 15, 2023
 *      Author: kking
 */
#include "stm32f1xx_hal.h"
#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

/**
 * RD: PA5
 * WR: PA2
 * A0: PA4
 * Data Bus: PB8-PB15
 */

struct DisplayPinType {
	GPIO_TypeDef* port;
	uint16_t pin_number;
};

struct DisplayPinConfig {
	struct DisplayPinType RD;
	struct DisplayPinType WR;
	struct DisplayPinType A0;
};

extern struct DisplayPinConfig displayPinConfig;
extern TIM_HandleTypeDef* displayTimer;

void Display_Configure_Pins(uint16_t RD_pin, GPIO_TypeDef* RD_port, uint16_t WR_pin, GPIO_TypeDef* WR_port, uint16_t A0_pin, GPIO_TypeDef* A0_port);
void Display_Write_Byte(uint8_t* data, uint8_t A0, uint8_t RD, uint8_t WR);
void Display_Turn_On();
void Display_Turn_Off();
void Display_All_Points_On();
void Display_All_Points_Off();
//May be needed
void Display_Booster_Ratio_Set();
void Display_Data_Read();
void Display_Set_Timer(TIM_HandleTypeDef* _timer);
void delay_ns(uint16_t ns);

#endif /* INC_DISPLAY_H_ */
