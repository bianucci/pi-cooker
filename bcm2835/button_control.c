#include "bcm2835.h"
#include "rpi_hd44780.h"
#include "custom.h"

#define	TEMPERATURE_USER	0
#define	TEMPERATURE_CURR	1
#define BUTTON_PRESSED		1
#define BUTTON_RELEASED		0
#define BUTTON_PIN		RPI_GPIO_P1_13 // breakout board gpio 21

void lcd_print_temperature(int, int);
void raw_temp_convert(char*, char*);
void button_init(void);
int button_state(void);

int notmain(void){
	lcd_init();
	button_init();

	int temp = 0;
	bcm2835_uart_begin();
	char lock_message[6] = "locked";

	while(1){
		//int i=0;
		//i = button_state();
		//bcm2835_uart_send(i+48);
		
		if(button_state() == BUTTON_PRESSED){
			temp++;	
			lcd_print_temperature(temp, TEMPERATURE_USER);
			bcm2835_uart_send(BUTTON_PRESSED+48);

			int counter = 0;
			while(counter<30){
				if(button_state() == BUTTON_PRESSED){
					counter=0;
					temp++;
					lcd_print_temperature(temp, TEMPERATURE_USER);
					bcm2835_uart_send(BUTTON_PRESSED+48);
				}else{
					counter++;
				}
			}
				
		}
		uart_send_string(lock_message);
		
		//some complex stuff
		bcm2835_delayMicroseconds(5000000);

		
	}
	return 0;
}

void button_init(){
	bcm2835_gpio_fsel(BUTTON_PIN, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(BUTTON_PIN, BCM2835_GPIO_PUD_DOWN);	
}

int button_state(){
	int button_1_value;
	button_1_value = bcm2835_gpio_lev(BUTTON_PIN);
	bcm2835_delayMicroseconds(100000);
	return button_1_value;
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
