/*
 * altimex_serial.c
 *
 *  Created on: Sep 20, 2023
 *      Author: kking
 */

#include "altimex_serial.h"

void printf(float data, UART_HandleTypeDef* uart)
{
	char charData[64] = {'\0'};
	sprintf(charData, "%f", data);
	size_t len = strlen(charData);
	println(charData, len, uart);
}

void printd(double data, UART_HandleTypeDef* uart)
{
	char charData[64] = {'\0'};
	sprintf(charData, "%f", data);
	size_t len = strlen(charData);
	println(charData, len, uart);
}

void print(char* data, size_t len, UART_HandleTypeDef* uart)
{
	HAL_UART_Transmit(uart, data, len, 100);
}

void println(char* data, size_t len, UART_HandleTypeDef* uart)
{
	print(data, len, uart);

	char newline[2] = "\r\n";
	print(newline, 2, uart);
}