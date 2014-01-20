#include "custom.h"
#include "bcm2835.h"

static rpi_sys_timer_t* rpi_sys_timer = (rpi_sys_timer_t*)RPI_SYSTIMER_BASE;

int shift(char* int_as_char, int length){
    int i;
    for(i = 0;i < length;i++){
		int_as_char[i] = int_as_char[i] + 48;
	}
	return 0;
}

int transform_to_char_array(char *int_as_char, int i){    
	int mod_result = -1;
	int counter = 0;
	do {
		mod_result = i%10;
		int_as_char[counter] = mod_result;
		i = i / 10;
		counter++;
	}while(i!=0);

	shift(int_as_char, counter);
	return counter;
}

void uart_send_string(char *string){
	int i = 0;
	while (string[i]!=0){
		bcm2835_uart_send(string[i]);
		i++;
	}
}

int current_time_micros(void){
	return rpi_sys_timer->counter_lo;
}

void send_int_to_uart(int value){
	char value_char[10];
	int length = transform_to_char_array(value_char, value);
	int index;
	for (index = length - 1; index >= 0; index--)
	{
		bcm2835_uart_send(value_char[index]);
	}
}

void sleep(int microseconds){
	bcm2835_delayMicroseconds(microseconds);

}


