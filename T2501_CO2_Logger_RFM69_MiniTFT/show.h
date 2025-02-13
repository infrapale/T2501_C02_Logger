#ifndef __SHOW_H__
#define __SHOW_H__


void show_initialize(void);
void show_text(int16_t x, int16_t y, uint8_t t_size,  uint16_t color, char *text);
void show_fill_screen(uint16_t color);
#endif