#include "bcm2835.h"

int notmain(void){

	int i;

	uint32_t data;

	bcm2835_uart_begin();

	data = 'a';

	for(i = 0; i<26; i++){
	
		bcm2835_uart_send(data);
		data++;

	}

	return 0;
}
