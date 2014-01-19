#ifndef _TEMP_LCD_H
#define _TEMP_LCD_H

extern int current_rotation;
extern void lcd_update_temps(int, int);
extern void lcd_update_temp(int, unsigned char);
extern void lcd_init_temps(void);
extern void lcd_rotate(void);

#endif