#ifndef _CUSTOM_H
#define _CUSTOM_H

#define ONE_SECOND 			ONE_MILLI_SECOND*1000
#define ONE_MILLI_SECOND 	1000
#define RPI_SYSTIMER_BASE	0x20003000
#define CHAR_SPACE       	' '
#define TEMP_USER_MAX      	1000

#define BTN_MODE_WAITING	0
#define BTN_MODE_INCREASING	1

#define BTN_STATE_PRESSED	1
#define BTN_STATE_RELEASED	0

#define PERIOD_DEADLINE		ONE_MILLI_SECOND * 100 // 100000 us

typedef struct{
	int temp_current;
	int temp_user;
	int relay;
	int btn_mode;
	int btn_state;
	int btn_state_t;
} States;

typedef struct {
    volatile unsigned int control_status;
    volatile unsigned int counter_lo;
    volatile unsigned int counter_hi;
    volatile unsigned int compare0;
    volatile unsigned int compare1;
    volatile unsigned int compare2;
    volatile unsigned int compare3;
} rpi_sys_timer_t;

int current_time_micros(void);

int transform_to_char_array(char *int_as_char, int i);

int shift(char* int_as_char, int length);

void uart_send_string(char *string);

void send_int_to_uart(int value);

void sleep(int microseconds);

#endif