#ifndef __BTN_H__
#define __BTN_H__

#define TFTWING_RESET_PIN = 8;

typedef enum
{
    BUTT_UP     = (1UL << 2),
    BUTT_DOWN   = (1UL << 4),
    BUTT_LEFT   = (1UL << 3),
    BUTT_RIGHT  = (1UL << 7),
    BUTT_SELECT = (1UL << 11),
    BUTT_A      = (1UL << 10),
    BUTT_B      = (1UL << 9),
} butt_bitmap_et;

typedef enum 
{
    BUTTON_UP = 0, 
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT, 
    BUTTON_SELECT,
    BUTTON_A, 
    BUTTON_B,
    BUTTON_NBR_OF
} btn_et;

void btn_initialize(void);

void btn_task(void);


#endif