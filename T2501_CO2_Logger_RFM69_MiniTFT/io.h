#ifndef __IO_H__
#define __IO_H__

#define LOGGER_M0_RFM69_WING_MINI_TFT_ADALOGGER
#ifdef  LOGGER_M0_RFM69_WING_MINI_TFT_ADALOGGER

// RFM69 Feather Wing
// SPI: MOSI, MISO, SCK
#define RFM69_CS      9
#define RFM69_INT     5
// #define RFM69_IRQN    0  // Pin 2 is IRQ 0!
#define RFM69_RST     18

// Mini Color TFT + Joystick
// SPI: MOSI, SCK
// I2C: SCL,SDA Addr = 
#define TFT_CS        11
#define TFT_DC        12

// ADALOGGER
// TFT SPI: MOSI, MISO, SCK
// RTC I2C: SCL,SDA Addr = 
#define LOGGER_SD_CS  6 

#endif

// LED Definitions
#define PIN_LED_ONBOARD 13  // onboard blinky

typedef enum
{
    LED_INDX_ONBOARD = 0,
    LED_INDX_RED,
    LED_INDX_GREEN,
    LED_INDX_BLUE,
    LED_INDX_NBR_OF
} led_index_et;

void io_initialize(void);

void io_led_flash(uint16_t nbr_ticks );

void io_run_100ms(void);

void io_toggle_clear_wd(void);

#endif