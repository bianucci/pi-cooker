#ifndef _RELAY_H
#define _RELAY_H

#include "custom.h"

#define RELAY_ON 1
#define RELAY_OFF 0
#define RELAY_PIN RPI_V2_GPIO_P1_07

extern void task_relays(States*);
extern void init_relays(void);

#endif