/*
 * altimex_serial.c
 *
 *  Created on: Sep 20, 2023
 *      Author: kking
 */

#include <usb.h>

UART_HandleTypeDef* STM_USB::uart = 0; //Set STM_USB::uart to dummy value
uint8_t STM_USB::buffer[USB_BUFFER_SIZE] = {'\0'};

void STM_USB::init(UART_HandleTypeDef* _uart)
{
	STM_USB::uart = _uart; //Set STM_USB::uart to actual value
	HAL_UART_Receive_DMA(_uart, STM_USB::buffer, USB_BUFFER_SIZE);
}

void STM_USB::print(float data)
{
	char charData[64] = {'\0'};
	sprintf(charData, "%f", data);
	STM_USB::println(charData);
}

void STM_USB::print(double data)
{
	char charData[64] = {'\0'};
	sprintf(charData, "%f", data);
	STM_USB::println(charData);
}

void STM_USB::print(uint8_t data)
{
	char charData[64] = {'\0'};
	sprintf(charData, "%d", data);
	STM_USB::println(charData);
}

void STM_USB::print(uint16_t data)
{
	char charData[64] = {'\0'};
	sprintf(charData, "%d", data);
	STM_USB::println(charData);
}

void STM_USB::print(uint32_t data)
{
	char charData[64] = {'\0'};
	sprintf(charData, "%d", data);
	STM_USB::println(charData);
}

void STM_USB::print(char* data)
{
	HAL_UART_Transmit(STM_USB::uart, (const uint8_t*)data, strlen(data), 100);
}

void STM_USB::println(char* data)
{
	STM_USB::print(data);

	char newline[3] = "\r\n";
	STM_USB::print(newline);
}

void STM_USB::readln(char* data)
{
	STM_USB::readto(data, '\n');
}

void STM_USB::readto(char* data, char flag)
{
	uint16_t i = 0;
	char next_char = {'\0'};
	do {
		next_char = read_next();
		data[i] = next_char;
		i++;
	} while(i < USB_BUFFER_SIZE && next_char != flag && next_char != '\0');
}

//Reads the next character from the buffer
char STM_USB::read_next()
{
	char next = STM_USB::buffer[0];
	STM_USB::shift_buffer();
	return next;
}

void STM_USB::shift_buffer()
{
	uint16_t i = 0;
	while(i < USB_BUFFER_SIZE - 1) {
		STM_USB::buffer[i] = STM_USB::buffer[i + 1];
		i++;
	}
	STM_USB::buffer[USB_BUFFER_SIZE - 1] = {'\0'};
}

bool STM_USB::has_buffer_overrun()
{
	return get_buffer_size() >= USB_BUFFER_SIZE;
}

bool STM_USB::data_ready()
{
	return get_buffer_size() > 0;
}

uint16_t STM_USB::get_buffer_size()
{
	return strlen((const char*)STM_USB::buffer);
}
