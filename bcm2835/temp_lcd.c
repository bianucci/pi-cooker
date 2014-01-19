#include "temp_lcd.h"
#include "rpi_hd44780.h"
#include "custom.h"

int current_rotation = 0;

void lcd_update_temps(int temp_current, int temp_user){
	lcd_update_temp(temp_current,LINE2_START);
	lcd_update_temp(temp_user,LINE2_START+12);
}

void lcd_update_temp(int temp, unsigned char cursor){
	char temp_raw_string[4];
	transform_to_char_array(temp_raw_string, temp);
	lcd_set_cursor(cursor);
	lcd_send_string(temp_raw_string);	
}

void lcd_init_temps(){
	// Init display and clear screen
	lcd_init();
	lcd_clear_screen();
	// Assign variables for header and values
	char header[16] = "HAVE   ##   WANT";
	char values[16] = "000.0  ##  000.0";
	// Send header and values to display using cursor
	lcd_set_cursor(LINE1_START);		
	lcd_send_string(header);
	lcd_set_cursor(LINE2_START);
	lcd_send_string(values);
}

void lcd_rotate(){
	char draw[4] = "####";
    draw[current_rotation] = ' ';

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

int notmain(void){
	lcd_init_temps();
	bcm2835_delayMicroseconds(ONE_SECOND);
	lcd_update_temps(34, 80);
	bcm2835_delayMicroseconds(ONE_SECOND);	
	while (1){
		lcd_rotate();
		bcm2835_delayMicroseconds(ONE_SECOND);	
	}
	return 0;
}