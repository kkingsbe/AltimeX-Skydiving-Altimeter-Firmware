/*
 * altimex_usb.h
 *
 *  Created on: Sep 24, 2023
 *      Author: kking
 */

#ifndef INC_ALTIMEX_USB_H_
#define INC_ALTIMEX_USB_H_
#define ALTIMEX_COMMAND_TABLE_SIZE 16

#include "usb.h"
#include "altimex_eeprom.h"

struct AltimexCommand {
	char* name;
	char* identifier;
	void (*handler_function)();
};

class AltimexUsb {
private:
	static const char end_flag = ';';
	static AltimexCommand command_table[];
	static AltimexEeprom* data_eeprom;
public:
	static void init(AltimexEeprom* eeprom);
	static void handle_received_command();
	static void handle_download_data_pretty();
	static void handle_download_data_raw();
	//TODO: Add handlers for configuring settings
};


#endif /* INC_ALTIMEX_USB_H_ */
