#include "custom.h"
#include "bcm2835.h"
#include "temp_lcd.h"

int notmain(void){

	int i;

	uint32_t data;

	bcm2835_uart_begin();

	data = 'a';

	for(i = 0; i<26; i++){
	
		bcm2835_uart_send(data);
		data++;
		bcm2835_delayMicroseconds(ONE_SECOND);


	}

	return 0;
}
