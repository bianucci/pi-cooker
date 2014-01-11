#include "lib.h"

static rpi_sys_timer_t* rpiSystemTimer = (rpi_sys_timer_t*)RPI_SYSTIMER_BASE;

void sleepMicros( unsigned int us )
{
    volatile unsigned int ts = rpiSystemTimer->counter_lo;

    while( ( rpiSystemTimer->counter_lo - ts ) < us )
    {
        // Nothing to do   
    }
}

void sleepMillis( unsigned int us )
{
    sleepMicros(us*1000);
}

void sleepSeconds( unsigned int us )
{
    sleepMillis(us*1000);
}