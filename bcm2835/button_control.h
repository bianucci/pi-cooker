#ifndef _BUTTON_CONTROL_H
#define _BUTTON_CONTROL_H

#define BUTTON_PIN					RPI_GPIO_P1_13 // breakout board gpio 21
#define BUTTON_INCREASE_PER_RUN		10 // breakout board gpio 21
#define BUTTON_DELAY_US		1000000 // breakout board gpio 21

void button_init(void);
int button_state(void);
void task_button_control(States*);

#endif