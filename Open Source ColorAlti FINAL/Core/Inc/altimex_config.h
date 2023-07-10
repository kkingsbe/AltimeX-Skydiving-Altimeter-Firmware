#ifndef INC_ALTIMEX_CONFIG_H_
#define INC_ALTIMEX_CONFIG_H_

struct AltimexConfig {
		uint16_t ascentThreshold;             //The altitude you must pass for it to transition into the ascent state
		uint16_t ascentThresholdTime;         //ms, that altitude must be above the ascentThreshold before transitioning between states
		uint16_t deployTestThresholdTime;     //ms, threshold time that vertical speed has to be under 50mph
		uint32_t gearCheckNotificationLength; //ms, the length of the gearcheck notification
		uint32_t freefallThresholdTime;       //ms, the amount of time that the vertical speed must be above the freefall threshold speed to transition into freefall state
		uint16_t exit;                        //Exit altitude
		uint16_t breakoff;                    //Breakoff altitude
		uint16_t deploy;                      //Deployment altitude
		uint32_t standbyFlashOnLength;        //How long the light is on for when in standby mode
		uint32_t standbyFlashOffLength;       //Period between each flash in standby mode
		uint8_t numLeds;                      //The number of leds being used
		uint16_t gearCheckAlt;                //The altitude that the gear check notification is given
		uint8_t brightness;                   //LED brightness
		uint8_t standbyBrightness;            //Brightness of LEDS while in standby mode
};

#endif
