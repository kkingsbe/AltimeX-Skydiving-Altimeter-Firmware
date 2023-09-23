/*
 * altimex_serial.c
 *
 *  Created on: Sep 20, 2023
 *      Author: kking
 */

#include <usb.h>

UART_HandleTypeDef* STM_USB::uart = 0; //Set STM_USB::uart to dummy value

void STM_USB::init(UART_HandleTypeDef* _uart)
{
	STM_USB::uart = _uart; //Set STM_USB::uart to actual value
}

void STM_USB::printf(float data)
{
	char charData[64] = {'\0'};
	sprintf(charData, "%f", data);
	size_t len = strlen(charData);
	STM_USB::println(charData, len);
}

void STM_USB::printd(double data)
{
	char charData[64] = {'\0'};
	sprintf(charData, "%f", data);
	size_t len = strlen(charData);
	STM_USB::println(charData, len);
}

void STM_USB::print(char* data, size_t len)
{
	HAL_UART_Transmit(STM_USB::uart, (const uint8_t*)data, len, 100);
}

void STM_USB::println(char* data, size_t len)
{
	STM_USB::print(data, len);

	char newline[3] = "\r\n";
	STM_USB::print(newline, 2);
}