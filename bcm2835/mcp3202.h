#ifndef _MCP3202_H
#define _MCP3202_H

#include "custom.h"

extern int mcp3202_read_data(void);
extern void task_measure_temperature(States*);

#endif