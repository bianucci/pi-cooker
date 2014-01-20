#include "temp_lcd.h"
#include "rpi_hd44780.h"
#include "custom.h"
#include "relay.h"

int current_rotation = 0;

void lcd_update_temps(int temp_current, int temp_user){
	lcd_update_temp(temp_current,LINE2_START);
	lcd_update_temp(temp_user,LINE2_START+11);
}

void lcd_update_temp(int temp, unsigned char cursor){
	char temp_raw_string[4] = "0000";
	char temp_with_floating_point[5];
	transform_to_char_array(temp_raw_string, temp);
	temp_with_floating_point[0] = temp_raw_string[3];
	temp_with_floating_point[1] = temp_raw_string[2];
	temp_with_floating_point[2] = temp_raw_string[1];
	temp_with_floating_point[3] = '.';
	temp_with_floating_point[4] = temp_raw_string[0];
	lcd_set_cursor(cursor);
	sleep(1000);
	lcd_send_string(temp_with_floating_point);	
	sleep(1000);
}

void lcd_init_temps(){
	// Init display and clear screen
	lcd_init();
	lcd_clear_screen();
	// Assign variables for header and values
	char header[16] = "CURR   ##   USER";
	char values[16] = "000.0  ##  000.0";
	// Send header and values to display using cursor
	lcd_set_cursor(LINE1_START);		
	sleep(1000);
	lcd_send_string(header);
	lcd_set_cursor(LINE2_START);
	sleep(1000);
	lcd_send_string(values);
	sleep(1000);
}

void lcd_rotate(States states){
	char draw[4] = "####";
	bcm2835_uart_send(states.relay);
	if (states.relay == RELAY_ON){
    	draw[current_rotation] = ' ';		
	}

    lcd_set_cursor(LINE1_START+7);
    lcd_send_char(draw[0]);
    lcd_set_cursor(LINE1_START+8);
    lcd_send_char(draw[1]);
    lcd_set_cursor(LINE2_START+8);
    lcd_send_char(draw[2]);
    lcd_set_cursor(LINE2_START+7);
    lcd_send_char(draw[3]);

    current_rotation++;

    if (current_rotation > 3){
    	current_rotation = 0;
    }
}

void task_lcd_print_temperatures(States states){
	lcd_update_temps(states.temp_current, states.temp_user);
}

void task_lcd_rotate(States states){
	lcd_rotate(states);
}

