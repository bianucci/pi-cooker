#ifndef TEMP_LCD_H_INCLUDED
#define TEMP_LCD_H_INCLUDED

extern int current_rotation;

extern void lcd_update_temps(int, int);
extern void lcd_update_temp(int, unsigned char);
extern void lcd_init_temps(void);
extern void lcd_rotate(void);

#endif