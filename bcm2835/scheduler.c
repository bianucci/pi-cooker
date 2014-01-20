#include "scheduler.h"
#include "temp_lcd.h"
#include "custom.h"
#include "button_control.h"

int notmain(){

	// Temperatures
	States states = initStates();

	init();

	int period = 1;

	while (1){

		int start = current_time_micros();

		task_button_control(&states);

		if (period % 2 == 0){
			task_lcd_print_temperatures(states);			
		}

		if (period % 20 == 0){
			task_relays(&states);			
		}

		if (period % 5 == 0){
			task_lcd_rotate(states);
			task_measure_temperature(&states);
		}

		int end = current_time_micros();
		int duration = (end - start);
		int sleep_t = PERIOD_DEADLINE - duration;

		bcm2835_uart_send('*');	
		send_int_to_uart(duration);				
		bcm2835_uart_send('#');

		sleep(sleep_t);

		period++;

	} 


}

void init(){
	lcd_init_temps();
	init_relays();
	button_init();
}

States initStates(){
	States states;	
	states.temp_current = 0;
	states.temp_user = 650;
	states.relay = 0;
	states.btn_mode = BTN_MODE_WAITING;
	states.btn_state = BTN_STATE_RELEASED;
	states.btn_state_t = 0;

	return states;
}