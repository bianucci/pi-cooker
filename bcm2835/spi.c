#include "bcm2835.h"

int notmain(void)
{
	uint32_t data = 0;
	uint32_t space = '-';

	char message[10];
	int length;

	bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_clr(16);

	lcd_init();

	int penis;
	for(penis = 0; penis <=9;penis++){
		lcd_clear_screen();	
		lcd_send_char(penis + 48);
		bcm2835_delayMicroseconds(1000000);

	}
	
	bcm2835_uart_begin();
    
    
    int temp = 0;
    
    uint8_t pin;
    
	pin = RPI_V2_GPIO_P1_07;
    
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    
	while(1){

		
		data = read_temp();
		length = transform_to_char_array(message, data);
        
        if( (data<=(temp-50)) || ((temp+50)<=data) ){
            temp = data;

            int i;
            for(i=length-1;i>=0;i--){
                bcm2835_uart_send(message[i]);
            }
            bcm2835_uart_send(space);
        }
        
	}
	return 0;
}