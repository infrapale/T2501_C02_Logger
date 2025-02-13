#include "main.h"
#include "io.h"


typedef struct
{
    uint8_t  pin;
    uint16_t tick_cntr;
} led_ctrl_st;


led_ctrl_st led_ctrl = { PIN_LED_ONBOARD, 0};

void io_initialize(void)
{
    pinMode(PIN_LED_ONBOARD, OUTPUT);
    digitalWrite(PIN_LED_ONBOARD, LOW);

    io_led_flash(10);


}

void io_led_flash( uint16_t nbr_ticks )
{
    // duration = nbr_ticks * 100ms
    digitalWrite(led_ctrl.pin, HIGH);
    led_ctrl.tick_cntr = nbr_ticks;
}

void io_run_100ms(void)
{
    if (led_ctrl.tick_cntr > 0)
    {
      led_ctrl.tick_cntr--;
      if (led_ctrl.tick_cntr == 0)
      {
        digitalWrite(led_ctrl.pin, LOW);
      }
    }
}

void io_toggle_clear_wd(void)
{
  // static uint8_t state = HIGH;

  // if (state == HIGH ) state = LOW;
  // else state = HIGH;
  // digitalWrite(PIN_CLEAR_WD, state);  
}
