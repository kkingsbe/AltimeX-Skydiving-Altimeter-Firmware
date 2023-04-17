/*
 * header.c
 *
 *  Created on: Apr 15, 2023
 *      Author: kking
 */
#include "display.h"

TIM_HandleTypeDef* displayTimer = NULL;
struct DisplayPinConfig displayPinConfig;

void Display_Configure_Pins(uint16_t RD_pin, GPIO_TypeDef* RD_port, uint16_t WR_pin, GPIO_TypeDef* WR_port, uint16_t A0_pin, GPIO_TypeDef* A0_port)
{
	struct DisplayPinType RD = {
			RD_port,
			RD_pin
	};
	struct DisplayPinType WR = {
			WR_port,
			WR_pin
	};
	struct DisplayPinType A0 = {
			A0_port,
			A0_pin
	};

	displayPinConfig.RD = RD;
	displayPinConfig.WR = WR;
	displayPinConfig.A0 = A0;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
}

//data is an array of bits, starting from d7
void Display_Write_Byte(uint8_t* data, uint8_t A0, uint8_t RD, uint8_t WR)
{
	//AO
	if(A0 == 0x00)
	{
		HAL_GPIO_WritePin(displayPinConfig.A0.port, displayPinConfig.A0.pin_number, GPIO_PIN_RESET);
	}
	if(A0 == 0x01)
	{
		HAL_GPIO_WritePin(displayPinConfig.A0.port, displayPinConfig.A0.pin_number, GPIO_PIN_SET);
	}

	delay_ns(20);

	//RD
	if(RD == 0x00)
	{
		HAL_GPIO_WritePin(displayPinConfig.RD.port, displayPinConfig.RD.pin_number, GPIO_PIN_RESET);
	}
	if(RD == 0x01)
	{
		HAL_GPIO_WritePin(displayPinConfig.RD.port, displayPinConfig.RD.pin_number, GPIO_PIN_SET);
	}

	//WR
	if(WR == 0x00)
	{
		HAL_GPIO_WritePin(displayPinConfig.WR.port, displayPinConfig.WR.pin_number, GPIO_PIN_RESET);
	}
	if(WR == 0x01)
	{
		HAL_GPIO_WritePin(displayPinConfig.WR.port, displayPinConfig.WR.pin_number, GPIO_PIN_SET);
	}

	uint8_t bit1 = data[0];
	uint8_t bit2 = data[1];
	uint8_t bit3 = data[2];
	uint8_t bit4 = data[3];
	uint8_t bit5 = data[4];
	uint8_t bit6 = data[5];
	uint8_t bit7 = data[6];
	uint8_t bit8 = data[7];

	//Data bus
	if(data[0] == 0x00)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	}
	if(data[0] == 0x01)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
	}

	if(data[1] == 0x00)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	}
	if(data[1] == 0x01)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	}

	if(data[2] == 0x00)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	}
	if(data[2] == 0x01)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	}

	if(data[3] == 0x00)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	}
	if(data[3] == 0x01)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	}

	if(data[4] == 0x00)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	}
	if(data[4] == 0x01)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	}

	if(data[5] == 0x00)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	}
	if(data[5] == 0x01)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	}

	if(data[6] == 0x00)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	}
	if(data[6] == 0x01)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
	}

	if(data[7] == 0x00)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	}
	if(data[7] == 0x01)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	}

	delay_ns(40);

	//Invert WR
	if(WR == 0x00)
	{
		HAL_GPIO_WritePin(displayPinConfig.WR.port, displayPinConfig.WR.pin_number, GPIO_PIN_SET);
	}
	if(WR == 0x01)
	{
		HAL_GPIO_WritePin(displayPinConfig.WR.port, displayPinConfig.WR.pin_number, GPIO_PIN_RESET);
	}

	delay_ns(20);

	//Invert A0
	if(A0 == 0x00)
	{
		HAL_GPIO_WritePin(displayPinConfig.A0.port, displayPinConfig.A0.pin_number, GPIO_PIN_SET);
	}
	if(A0 == 0x01)
	{
		HAL_GPIO_WritePin(displayPinConfig.A0.port, displayPinConfig.A0.pin_number, GPIO_PIN_RESET);
	}

	//delay_ns(250);
}

void Display_Turn_On()
{
	uint8_t data[8] = {0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01};
	uint8_t A0 = 0x00;
	uint8_t RD = 0x01;
	uint8_t WR = 0x00;

	Display_Write_Byte(data, A0, RD, WR);
}

void Display_Turn_Off()
{
	uint8_t data[8] = {0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00};
	uint8_t A0 = 0x00;
	uint8_t RD = 0x01;
	uint8_t WR = 0x00;

	Display_Write_Byte(data, A0, RD, WR);
}

void Display_All_Points_On()
{
	uint8_t data[8] = {0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01};
	uint8_t A0 = 0x00;
	uint8_t RD = 0x01;
	uint8_t WR = 0x00;

	Display_Write_Byte(data, A0, RD, WR);
}

void Display_All_Points_Off()
{
	uint8_t data[8] = {0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00};
	uint8_t A0 = 0x00;
	uint8_t RD = 0x01;
	uint8_t WR = 0x00;

	Display_Write_Byte(data, A0, RD, WR);
}

void Display_Booster_Ratio_Set()
{
	uint8_t data[8] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00};
	uint8_t A0 = 0x00;
	uint8_t RD = 0x01;
	uint8_t WR = 0x00;

	Display_Write_Byte(data, A0, RD, WR);
}

void Display_Set_Timer(TIM_HandleTypeDef* _timer)
{
	HAL_TIM_Base_Start(_timer);
	displayTimer = _timer;
}

void Display_Data_Read()
{
	uint8_t data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01};
	uint8_t A0 = 0x01;
	uint8_t RD = 0x00;
	uint8_t WR = 0x01;

	Display_Write_Byte(data, A0, RD, WR);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//delay_ns(250);

	GPIO_PinState v8 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
	GPIO_PinState v9 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
	GPIO_PinState v10 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
	GPIO_PinState v11 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);
	GPIO_PinState v12 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
	GPIO_PinState v13 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
	GPIO_PinState v14 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
	GPIO_PinState v15 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
	//data = Display_Read_Byte(&data);
}

void delay_ns(uint16_t ns)
{
	__HAL_TIM_SET_COUNTER(displayTimer,0);
	while (__HAL_TIM_GET_COUNTER(displayTimer) < ns);
}
