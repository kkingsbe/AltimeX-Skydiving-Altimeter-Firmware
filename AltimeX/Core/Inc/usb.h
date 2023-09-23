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

class STM_USB {
private:
	static UART_HandleTypeDef* uart;
public:
	static void init(UART_HandleTypeDef* _uart);
	static void print(char* data, size_t len);
	static void printf(float data);
	static void printd(double data);
	static void println(char* data, size_t len);
};

#endif /* INC_USB_H_ */