#include "temp_lcd.h"
#include "rpi_hd44780.h"
#include "bcm2835.h"
#include "custom.h"

void rotate(int blank);


int notmain(void){
	lcd_init();
	bcm2835_uart_begin();

	char header[16] = "HAVE   ##   WANT";
	char values[16] = "081.1  ##  102.3";

	lcd_clear_screen();
		
	lcd_set_cursor(LINE1_START);		
	lcd_send_string(header);

	lcd_set_cursor(LINE2_START);
	lcd_send_string(values);

    int i = 0;
    while(1){
		rotate(i);
        bcm2835_delayMicroseconds(200000);
        
        i++;
        if (i>3) {
            i=0;
        }
	}
	return 0;
}

void rotate(int blank){

    char draw[4] = "####";
    draw[blank] = ' ';
    
    lcd_set_cursor(LINE1_START+7);
    lcd_send_char(draw[0]);
    lcd_set_cursor(LINE1_START+8);
    lcd_send_char(draw[1]);
    lcd_set_cursor(LINE2_START+8);
    lcd_send_char(draw[2]);
    lcd_set_cursor(LINE2_START+7);
    lcd_send_char(draw[3]);
}

