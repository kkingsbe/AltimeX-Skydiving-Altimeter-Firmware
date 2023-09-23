/*
 * LPS22HB.c
 *
 *  Created on: Jul 6, 2023
 *      Author: Kyle Kingsberry
 */
#include "LPS22HB.h"

LPS22HB::LPS22HB(I2C_HandleTypeDef* i2c_config, uint16_t address, UART_HandleTypeDef* uart): i2c_config(i2c_config), address(address), uart(uart)
{
	HAL_Delay(1000);

	//Make sure the sensor is powered on and discovered on the I2C bus
	HAL_StatusTypeDef i2c_status = HAL_I2C_IsDeviceReady(i2c_config, (uint16_t)(LPS_DEFAULT_ADDRESS<<1), 3, 5);
	if(i2c_status == HAL_BUSY) {
		return 0;
	}

	//Set the ouptut data rate (odr)
	LPS_Set_Odr(ODR_75hz);

	//Make sure the odr matches the desired odr
	enum LPS_ODR odr = LPS_Get_Odr();
	if(odr != ODR_75hz) {
		return 0;
	}

	//Set FIFO mode to BYPASS
	LPS_Configure_Fifo(BYPASS);

	//Enable low pass filter
	//LPS_Configure_LPFP(ODR_9);

	//return 1;
}

void LPS22HB::reg_read(uint16_t reg_addr, uint16_t reg_size, uint8_t* data_output)
{
	HAL_I2C_Mem_Read(this.i2c_config, (uint16_t)(this.address<<1), reg_addr, 1, data_output, reg_size, 100);
}

//Configures the output data rate (ODR)
void LPS22HB::set_odr(enum LPS_ODR new_odr)
{
	//Read the existing configuration from the CTRL_REG 1
	uint8_t existingConfig[1];
	this.reg_read(CTRL_REG1, 1, existingConfig);

	//Clear top 4 bits from the existing config
	uint8_t newConfig[1];
	newConfig[0] = existingConfig[0] & 0x0F;

	//Store the new ODR configuration
	newConfig[0] |= (new_odr << 4);

	//Write new ODR to register
	HAL_I2C_Mem_Write(this.i2c_config, (uint16_t)(this.address<<1), CTRL_REG1, 1, newConfig, 1, 100);

	/*
	uint8_t actualNewConfig[1];
	LPS_Reg_Read(CTRL_REG1, 1, actualNewConfig);
	*/
}

//Reads the sensors odr
enum LPS_ODR LPS22HB::get_odr()
{
	uint8_t existingConfig[1];
	this.reg_read(CTRL_REG1, 1, existingConfig);
	uint8_t odr_code = (existingConfig[0] >> 4);

	return odr_code;
}

//Configures the FIFO for the desired mode
void LPS22HB::configure_fifo(enum LPS_FIFO desiredFifo)
{
	//Only supports bypass mode for now
	if(desiredFifo != BYPASS) {
		return;
	}

	//Read existing FIFO config from sensor
	uint8_t existingConfig[1];
	this.reg_read(FIFO_CTRL, 1, existingConfig);

	//Clear the top 3 bits from the existing config
	uint8_t newConfig[1];
	newConfig[0] = existingConfig[0] & 0x1F;

	//Write new FIFO config to sensor
	HAL_I2C_Mem_Write(this.i2c_config, (uint16_t) (this.address<<1), FIFO_CTRL, 1, newConfig, 1, 100);
}

//Returns the pressure read by the sensor in HPA
double LPS22HB::get_pressure()
{
	double SCALING_FACTOR = 4096.0;

	uint8_t press_out_h[1];
	uint8_t press_out_l[1];
	uint8_t press_out_xl[1];

	this.reg_read(PRESS_OUT_H, 1, press_out_h);
    this.reg_read(PRESS_OUT_L, 1, press_out_l);
    this.reg_read(PRESS_OUT_XL, 1, press_out_xl);

	uint32_t pressure = (press_out_h[0] << 16) + (press_out_l[0] << 8) + press_out_xl[0];

	return pressure / SCALING_FACTOR;
}

//Returns the temperature read by the sensor in C
double LPS22HB::get_temp()
{
	double SCALING_FACTOR = 100.0;
	uint8_t temp_out_h[1];
	uint8_t temp_out_l[1];

    this.reg_read(TEMP_OUT_H, 1, temp_out_h);
    this.reg_read(TEMP_OUT_L, 1, temp_out_l);

	uint32_t temperature = (temp_out_h[0] << 8) + temp_out_l[0];

	return temperature / SCALING_FACTOR;
}

double LPS22HB::get_tempf()
{
	double tempC = this.get_temp();
	return (tempC * (9/5.0)) + 32;
}

double LPS22HB::get_pressureatm()
{
	double pressHPA = this.get_pressure();
	return pressHPA * 0.0009869233;
}

//Reference pressure is pressure in Pa at surface
double LPS22HB::get_relalt_ft(double reference_pressure)
{
	double p = this.get_pressure();
	double t = this.get_temp();

	//Hypsometric formula: https://keisan.casio.com/exec/system/1224585971
	double frac_p = (double)reference_pressure / p;
	double exponential = pow(frac_p, (double)1.0/5.257);
	double fraction_top = (exponential - 1) * (t + 273.15);
	double alt_m = fraction_top / 0.0065;
	return alt_m * 3.281; //Convert to ft and return
}

double LPS22HB::get_calibration_temperature(uint8_t num_samples, uint8_t sample_time_ms)
{
	char msg[] = "\r\n\nCalibrating LPS Temperature:";
	println(msg, strlen(msg), this.uart);

	double cum_val = 0;
	double avg_val = 0;
	uint8_t sample = 0;
	while(sample < num_samples) {
		double _temp = LPS_Get_Temp();
		print(".", 1, lpsConfig.uart);
		cum_val += _temp;
		HAL_Delay(sample_time_ms);
		sample ++;
	}
	avg_val = cum_val / (double)num_samples;
	char msg2[] = "\r\nAverage Temperature (C): ";
	print(msg2, strlen(msg2), lpsConfig.uart);
	printd(avg_val, this.uart);
	return avg_val;
}

double LPS22HB::get_calibration_pressure(uint8_t num_samples, uint8_t sample_time_ms)
{
	char msg[] = "\r\n\nCalibrating LPS Pressure:\n";
	println(msg, strlen(msg), this.uart);

	double cum_val = 0;
	double avg_val = 0;
	uint8_t sample = 0;
	while(sample < num_samples) {
		double _temp = this.get_pressure();
		print(".", 1, this.uart);
		cum_val += _temp;
		HAL_Delay(sample_time_ms);
		sample ++;
	}
	avg_val = cum_val / (double)num_samples;
	char msg2[] = "\r\nAverage Pressure (PA): ";
	print(msg2, strlen(msg2), this.uart);
	printd(avg_val, this.uart);
	return avg_val;
}

/*
void LPS_Configure_LPFP(enum LPS_LPFP_BANDWIDTH bandwidth)
{
	//Read the existing configuration from the CTRL_REG 1
	uint8_t existingConfig[1];
	LPS_Reg_Read(CTRL_REG1, 1, existingConfig);

	uint8_t newConfig[1];
	newConfig[0] = existingConfig[0] & 0xC;

	//Store the new ODR configuration
	newConfig[0] |= (bandwidth << 2);

	//Write new ODR to register
	HAL_I2C_Mem_Write(lpsConfig.i2c_config, (uint16_t)(lpsConfig.address<<1), CTRL_REG1, 1, newConfig, 1, 100);
}
*/
