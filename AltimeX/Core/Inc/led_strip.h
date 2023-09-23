/*
 * led_strip.h
 *
 * Created on: Apr 15, 2023
 * Author: kking
 */

#include <ws2813b_controller.h>

#ifndef INC_LED_STRIP_H_
#define INC_LED_STRIP_H_

class LedStrip {
private:
    TIM_HandleTypeDef* timer;
    WS2813BController* controller;
public:
    LedStrip(TIM_HandleTypeDef* _timer);
    void progress_bar_single_color(uint8_t num_filled, enum COLOR color);
    void set_brightness(int brightness);  // 0-45
    void clear();
    void send();
};

#endif /* INC_LED_STRIP_H_ */
