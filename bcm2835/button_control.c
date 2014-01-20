#include "bcm2835.h"
#include "rpi_hd44780.h"
#include "custom.h"
#include "button_control.h"

void button_init(){
	bcm2835_gpio_fsel(BUTTON_PIN, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(BUTTON_PIN, BCM2835_GPIO_PUD_DOWN);	
}

int button_state(){
	int button_1_value;
	button_1_value = bcm2835_gpio_lev(BUTTON_PIN);
	return button_1_value;
}

void task_button_control(States *states){
	if(button_state() == BTN_STATE_PRESSED){
		// PRESSED
		if (states->btn_state == BTN_STATE_RELEASED){
			states->btn_state_t = current_time_micros();
			states->btn_state = BTN_STATE_PRESSED;
		}

		if (states->btn_mode == BTN_MODE_INCREASING){
			// PRESSED / INCREASING
			states->temp_user = states->temp_user + BUTTON_INCREASE_PER_RUN;
			if (states->temp_user > TEMP_USER_MAX){
				states->temp_user = states->temp_user - TEMP_USER_MAX;
			}
		} else{
			// PRESSED / WAITING
			int delay = current_time_micros() - states->btn_state_t;
			if (delay > BUTTON_DELAY_US){
				states->btn_mode = BTN_MODE_INCREASING;
			}
		}
	}else{
		// RELEASED
		if (states->btn_state == BTN_STATE_PRESSED){
			states->btn_state_t = current_time_micros();
			states->btn_state = BTN_STATE_RELEASED;
		}

		if (states->btn_mode == BTN_MODE_INCREASING){
			int delay = current_time_micros() - states->btn_state_t;
			if (delay > BUTTON_DELAY_US){
				states->btn_mode = BTN_MODE_WAITING;
			}
		}

	}	

}

