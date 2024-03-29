/*
 * altimex_serial.h
 *
 *  Created on: Sep 20, 2023
 *      Author: kking
 */

#ifndef INC_USB_H_
#define INC_USB_H_
#include "stm32f1xx_hal.h"
#include "string.h"
#include<stdio.h>
#define USB_BUFFER_SIZE 1024 //Change as needed. This sets the buffer size and also the maximum word length

class STM_USB {
private:
	static UART_HandleTypeDef* uart;
	static uint8_t buffer[USB_BUFFER_SIZE]; //Data received over usb will be put into this buffer
	static uint16_t read_index;
	static void increment_read_index();
	static void consume_next();
public:
	static void init(UART_HandleTypeDef* _uart);
	static void print(char* data);
	static void print(float data);
	static void print(double data);
	static void print(uint8_t data);
	static void print(uint16_t data);
	static void print(uint32_t data);
	static void println(char* data);
	static void readln(char* data);
	static void readto(char* data, char flag);
	static char read_next();
	static bool data_ready();
	static uint16_t get_buffer_size();
	static uint16_t get_max_buffer_size();
};

#endif /* INC_USB_H_ */
