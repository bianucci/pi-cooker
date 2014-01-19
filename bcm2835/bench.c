#include "custom.h"
#include "bcm2835.h"
#include "temp_lcd.h"

int notmain(){

	int start;
	int duration;

	bcm2835_uart_send('#');

	bcm2835_uart_send('F');
	bcm2835_uart_send(CHAR_SPACE);

	start = current_time_micros();
	lcd_init();
	duration = current_time_micros() - start;
	send_int_to_uart(duration);

	bcm2835_uart_send('#');

	start = current_time_micros();
	lcd_init_temps();
	duration = current_time_micros() - start;
	send_int_to_uart(duration); 

	bcm2835_uart_send('#');

	start = current_time_micros();
	lcd_update_temps(33, 59);
	duration = current_time_micros() - start;
	send_int_to_uart(duration);
	
	bcm2835_uart_send('#');
	
	start = current_time_micros();
	lcd_rotate();
	duration = current_time_micros() - start;
	send_int_to_uart(duration);

	bcm2835_uart_send('#');

	start = current_time_micros();
	mcp3202_read_data();
	duration = current_time_micros() - start;
	send_int_to_uart(duration);

}

