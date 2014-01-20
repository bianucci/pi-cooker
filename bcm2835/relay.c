#include "relay.h"
#include "bcm2835.h"
#include "custom.h"


void task_relays(States *states){
	
	if (states->temp_current >= states->temp_user && states->relay == RELAY_ON){
		// Relay off
		bcm2835_gpio_set(RELAY_PIN);
		states->relay = RELAY_OFF;
	}else if (states->temp_current < states->temp_user && states->relay == RELAY_OFF){
		// Relay on
		bcm2835_gpio_clr(RELAY_PIN);
		states->relay = RELAY_ON;
	}

}

void init_relays(){
    bcm2835_gpio_fsel(RPI_V2_GPIO_P1_07, BCM2835_GPIO_FSEL_OUTP);
}