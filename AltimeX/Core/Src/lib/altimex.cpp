/*
 * altimex.cpp
 *
 *  Created on: Sep 23, 2023
 *      Author: kking
 */
#include "altimex.h"

Altimex::Altimex(UART_HandleTypeDef* _uart, I2C_HandleTypeDef* i2c_config, TIM_HandleTypeDef* _timer, uint16_t _writeInterval):
	tempF(0.0),
	alt(0.0),
	barometer(new LPS22HB(i2c_config, LPS_DEFAULT_ADDRESS)),
	step(0),
	eeprom(new AltimexEeprom(0xA0, i2c_config)),
	lastWrite(0),
	writeInterval(_writeInterval)
{
	AltimexUsb::init(eeprom);
	STM_USB::init(_uart);
	STM_USB::println("\r\n\n\n\n\n\nAltimex Boot...");
	LPS22HB::LPS_INIT_STATUS baro_init_status = barometer->init();

	if(baro_init_status != LPS22HB::LPS_INIT_STATUS::SUCCESS) {
		while(true) {
			STM_USB::println("Error while initializing sensor.");
			HAL_Delay(1000);
		}
	}

	struct AltimexConfig loaded_config;

	STM_USB::println("Loading settings");
	eeprom->load_configuration(&loaded_config);

	config = loaded_config;
	ledController = new AltimexLedController(&config, _timer);
	stateController = new AltimexStateController(&config);

	print_config_to_usb();

	barometer->calibrate(10, 100);
	tempF = barometer->get_tempf();

	//struct AltimexDataFrame dataFrames[100] = {};
	//eeprom->load_dataframes(0, 100, dataFrames);
	//eeprom->load_dataframe(0, &dataFrame);

	STM_USB::println("Setup complete");
}

void Altimex::print_config_to_usb()
{
	STM_USB::print("Gear Check Notification Altitude: ");
	STM_USB::print(config.gearCheckAlt);

	STM_USB::print("Exit Altitude (ft): ");
	STM_USB::print(config.exit);

	STM_USB::print("Breakoff Altitude (ft): ");
	STM_USB::print(config.breakoff);

	STM_USB::print("Deployment Altitude (ft): ");
	STM_USB::print(config.deploy);

	STM_USB::print("Ascent Threshold: ");
	STM_USB::print(config.ascentThreshold);

	STM_USB::print("Ascent Threshold Time (ms): ");
	STM_USB::print(config.ascentThresholdTime);

	STM_USB::print("Deploy Test Threshold Time (ms): ");
	STM_USB::print(config.deployTestThresholdTime);

	STM_USB::print("Gear Check Notification Length (ms): ");
	STM_USB::print(config.gearCheckNotificationLength);

	STM_USB::print("Freefall Threshold Time (ms): ");
	STM_USB::print(config.freefallThresholdTime);

	STM_USB::print("Standby Flash On Length (ms): ");
	STM_USB::print(config.standbyFlashOnLength);

	STM_USB::print("Standby Flash Off Length (ms): ");
	STM_USB::print(config.standbyFlashOffLength);

	STM_USB::print("Brightness (0-40): ");
	STM_USB::print(config.brightness);

	STM_USB::print("Standby Brightness (0-40): ");
	STM_USB::print(config.standbyBrightness);
}

void Altimex::tick()
{
	tempF = barometer->get_tempf();
	AltimexUsb::handle_received_command();

	//STM_USB::printd(tempF);
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

	uint16_t temp = HAL_GetTick() - lastWrite;
	if(HAL_GetTick() - lastWrite > writeInterval) {
		eeprom->save_dataframe(tempF, alt, stateController->get_state());
		lastWrite = HAL_GetTick();
		STM_USB::println("Saved data to storage.");
	}

	step++;
	if(step > 100) step = 0;
}
