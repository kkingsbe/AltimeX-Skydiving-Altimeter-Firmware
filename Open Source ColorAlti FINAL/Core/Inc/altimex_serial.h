/*
 * altimex_serial.h
 *
 *  Created on: Sep 20, 2023
 *      Author: kking
 */

#ifndef INC_ALTIMEX_SERIAL_H_
#define INC_ALTIMEX_SERIAL_H_
#include "stm32f1xx_hal.h"

void print(char* data, size_t len, UART_HandleTypeDef* uart);
void printf(float data, UART_HandleTypeDef* uart);
void printd(double data, UART_HandleTypeDef* uart);
void println(char* data, size_t len, UART_HandleTypeDef* uart);

#endif /* INC_ALTIMEX_SERIAL_H_ */