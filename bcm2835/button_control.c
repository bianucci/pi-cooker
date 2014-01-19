#include "bcm2835.h"
#include "rpi_hd44780.h"
#include "custom.h"

#define	TEMPERATURE_USER	0
#define	TEMPERATURE_CURR	1

void lcd_print_temperature(int, int);
void raw_temp_convert(char*, char*);

int temp_as_int;
//uint8_t pin_button_1;
//uint8_t pin_button_1;

int notmain(void){

	temp_as_int = 0;
	lcd_init();
	bcm2835_uart_begin();

	//pin_button_1 = RPI_V2_GPIO_P1_07;
	//pin_button_2 = RPI_V2_GPIO_P1_07; ////////////////////////////	
	
	//bcm2835_gpio_fsel(pin_button_1, BCM2835_GPIO_FSEL_INPT);
	//bcm2835_gpio_fsel(pin_button_2, BCM2835_GPIO_FSEL_INPT);

	//  with a pullup
	//bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);

	//but = bcm2835_gpio_lev(pin);

	
	int i;

	for(i=0;i<=1234;i++){
		lcd_print_temperature(i, TEMPERATURE_USER);
		lcd_print_temperature(i, TEMPERATURE_CURR);
		bcm2835_delayMicroseconds(150000);
	}

	return 0;
}

void lcd_print_temperature(int temp_as_int, int type){
	char temp_raw_string[4] = "0000";
	char temp_with_floating_point[5];
	
	transform_to_char_array(temp_raw_string, temp_as_int);
	raw_temp_convert(temp_with_floating_point, temp_raw_string);

	switch(type){
		case TEMPERATURE_USER: lcd_set_cursor(LINE2_START); 	break;
		case TEMPERATURE_CURR: lcd_set_cursor(LINE2_START+11);	break;
	}

	lcd_send_string(temp_with_floating_point);

	//bcm2835_uart_send(temp_as_int);
	//uart_send_string(temp_raw_string);
	//uart_send_string(temp_with_floating_point);
}

void raw_temp_convert(char* temp_with_floating_point, char* temp_raw_string){
	temp_with_floating_point[0] = temp_raw_string[3];
	temp_with_floating_point[1] = temp_raw_string[2];
	temp_with_floating_point[2] = temp_raw_string[1];
	temp_with_floating_point[3] = '.';
	temp_with_floating_point[4] = temp_raw_string[0];
}
