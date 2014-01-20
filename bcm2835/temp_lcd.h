#ifndef _TEMP_LCD_H
#define _TEMP_LCD_H

#include "custom.h"

extern int current_rotation;
extern void lcd_update_temps(int, int);
extern void lcd_update_temp(int, unsigned char);
extern void lcd_init_temps(void);
extern void lcd_rotate(States);
extern void task_lcd_print_temperatures(States);
extern void task_lcd_rotate(States);

#endif