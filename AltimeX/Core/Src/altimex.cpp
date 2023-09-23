/*
 * altimex.cpp
 *
 *  Created on: Sep 23, 2023
 *      Author: kking
 */
#include "altimex.h"

Altimex::Altimex(UART_HandleTypeDef* _uart, I2C_HandleTypeDef* i2c_config, TIM_HandleTypeDef* _timer, AltimexConfig* config):
	ledController(new AltimexLedController(config, _timer)),
	stateController(new AltimexStateController(config)),
	tempF(0.0),
	alt(0.0),
	barometer(new LPS22HB(i2c_config, LPS_DEFAULT_ADDRESS)),
	step(0)
{
	STM_USB::init(_uart);
	char message[] = "AltimeX Boot...";
	STM_USB::println(message, strlen(message));
	LPS22HB::LPS_INIT_STATUS baro_init_status = barometer->init();

	if(baro_init_status != LPS22HB::LPS_INIT_STATUS::SUCCESS) {
		while(true) {
			char message[] = "Error while initializing sensor.";
			STM_USB::println(message, strlen(message));
			HAL_Delay(1000);
		}
	}

	barometer->calibrate(10, 100);
	tempF = barometer->get_tempf();
}

void Altimex::tick()
{
	//STORAGE_write(&hi2c1, 0, 8, &data);
	//uint8_t data_read[8] = {'\0'};
	//STORAGE_read(&hi2c1, 0, 8, &data_read);
	//println(data_read, strlen(data_read), &huart1);

	tempF = barometer->get_tempf();
	STM_USB::printd(tempF);
	  /*
	  if(HAL_GetTick() > 10000 && HAL_GetTick() < 70000) alt = ((HAL_GetTick() - 10000) / (double)60000) * 12500;
	  if(alt < 0) alt = 12500;
	  if(HAL_GetTick() > 70000)
	  {
		if(alt < 2500) alt -= 5;
		else alt -= 29;
	  }
	*/

	  alt = barometer->get_relalt_ft();
	  stateController->update_state(alt);
	  ledController->display_leds(stateController->get_state(), step, alt);
	  step++;
	  if(step > 100) step = 0;

	  /*
	  char data[10];
	  sprintf(data, "%f", alt);
	  HAL_UART_Transmit(&huart1, data, sizeof(data), 100);
	  */

	  //printd(alt, &huart1);

	  //Data is received one byte at a time
	  //uint8_t Rx_data[1];
	  //HAL_UART_Receive(&huart1, Rx_data, 100, 100);

	  //HAL_Delay(100); //10hz
}
