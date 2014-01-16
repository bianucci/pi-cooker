#include "bcm2835.h"

int notmain(void){
	uint8_t pin;

	pin = RPI_V2_GPIO_P1_07;

    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    
    
	while(1){
        bcm2835_gpio_set(pin);
        bcm2835_delayMicroseconds(1000000);
        bcm2835_gpio_clr(pin);
        bcm2835_delayMicroseconds(1000000);
	}
	
	return 0;
}
