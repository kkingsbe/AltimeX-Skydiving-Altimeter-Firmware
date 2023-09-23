/*
 * bmp581.h
 *
 *  Created on: Apr 16, 2023
 *      Author: kking
 */

#include "stm32f1xx_hal.h"
#include "math.h"
#include <string.h>
#include <usb.h>

#ifndef INC_LPS22HB_H_
#define INC_LPS22HB_H_

//Register map for the sensor
enum LPS_REG_MAP {
	CTRL_REG1 = 0x10,
	CTRL_REG2 = 0x11,
	CTRL_REG3 = 0x12,
	FIFO_CTRL = 0x14,
	REF_P_XL = 0x15,
	REF_P_L = 0x16,
	REF_P_H = 0x17,
	STATUS_REG = 0x27,
	PRESS_OUT_XL = 0x28,
	PRESS_OUT_L = 0x29,
	PRESS_OUT_H = 0x2A,
	TEMP_OUT_L = 0x2B,
	TEMP_OUT_H = 0x2C,
	LPFP_RES = 0x33
};

//ODR Options
enum LPS_ODR {
	ODR_off  = 0,
	ODR_1hz  = 0x1,
	ODR_10hz = 0x2,
	ODR_25hz = 0x3,
	ODR_50hz = 0x4,
	ODR_75hz = 0x5
};

//FIFO Options
enum LPS_FIFO {
	BYPASS = 0x0
};

enum LPS_LPFP_BANDWIDTH {
	ODR_2 = 0x0, //ODR/2
	ODR_9 = 0x2, //ODR/9
	ODR_20 = 0x3 //ODR/20
};

#define LPS_DEFAULT_ADDRESS 0x5C

class LPS22HB {
private:
    I2C_HandleTypeDef* i2c_config;
    uint16_t address;
    uint16_t reference_pressure;
    uint16_t reference_temperature;

    double get_calibration_temperature(uint8_t num_samples, uint8_t sample_time_ms);
    double get_calibration_pressure(uint8_t num_samples, uint8_t sample_time_ms);
public:
    LPS22HB(I2C_HandleTypeDef* i2c_config, uint16_t address);
    uint8_t init();
    void reg_read(uint16_t reg_addr, uint16_t reg_size, uint8_t* data_output);
    void set_odr(enum LPS_ODR new_odr);
    enum LPS_ODR get_odr();
    void configure_fifo(enum LPS_FIFO desiredFifo);
    void configure_lpfp(enum LPS_LPFP_BANDWIDTH bandwidth);
    double get_pressure();
    double get_temp();
    double get_tempf();
    double get_pressureatm();
    double get_relalt_ft();

    void calibrate(uint8_t num_samples, uint8_t sample_time_ms);
};

#endif /* INC_LPS22HB_H_ */
