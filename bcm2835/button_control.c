#include "bcm2835.h"
#include "pi_hd44780.h"
#include "custom.h"

void current_temp_up(int);
void current_temp_down(int);
void lcd_update_current_temp(int);
void fancy_temp(char*, char*);

int temp_as_int;


int main(void){
	temp_as_int = 0;
	lcd_init();
	

	return 0;
}

void current_temp_up(int current_temp){
	current_temp++;
	lcd_update_current_temp(temp_as_int);
}

void current_temp_down(int current_temp){
	if(current_temp > 0){
		current_temp--;
	}
	lcd_update_current_temp(current_temp);
}	

void lcd_update_current_temp(int temp_as_int){
	char[4] temp_raw_string;
	char[5] temp_with_floating_point;
	
	transform_to_char_array(temp_raw_string, temp_as_int);
	fancy_temp(temp_with_floating_point, temp_raw_string);

	lcd_set_cursor(LINE2_START);
	lcd_send_string(temp_with_floating_point);
}
