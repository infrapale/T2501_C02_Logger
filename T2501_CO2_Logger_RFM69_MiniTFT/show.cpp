#include "main.h"
#include "io.h"
#include "show.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include "Adafruit_miniTFTWing.h"
#include "sensor.h"
#include "atask.h"

Adafruit_miniTFTWing ss;
#define TFT_RST    -1    // we use the seesaw for resetting to save a pin

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

typedef struct
{
    uint8_t task_indx;
} show_st;

extern   sensor_st sensor[]; 

void show_task(void);

show_st show;
atask_st show_handle         = {"Show           ", 1000, 0, 0, 255, 0, 1, &show_task};


void show_initialize(void)
{
   if (!ss.begin()) {
    Serial.println("seesaw init error!");
    while(1);
  }
  else Serial.println("seesaw started");

 
  ss.tftReset();
  ss.setBacklight(0x0); //set the backlight fully on

  // Use this initializer (uncomment) if you're using a 0.96" 180x60 TFT
  tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display

  tft.setRotation(3);
    
  Serial.println("Initialized");
 // large block of text

  show.task_indx = atask_add_new(&show_handle);

  tft.fillScreen(ST77XX_BLACK);
  // show_text(0,0,2,ST77XX_GREEN, "CO2");
  // show_text(0,30,2,ST77XX_YELLOW, "C");
  // show_text(0,60,2,ST77XX_MAGENTA, "Hum");
}

void show_fill_screen(uint16_t color)
{
  tft.fillScreen(color);
}

void show_text(int16_t x, int16_t y, uint8_t t_size,  uint16_t color, char *text) {
  tft.setCursor(x, y);
  tft.setTextSize(t_size);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

int16_t  row_pos[3] = {0,30,60};
uint16_t row_color[3] = {ST77XX_GREEN, ST77XX_YELLOW, ST77XX_MAGENTA};

void show_task(void)
{
  char buff[40];
  show_fill_screen(ST77XX_BLACK);
  for (uint8_t i=0;i<3;i++)
  {
    sprintf(buff, "%s %.1f",sensor[0].values[i].label,sensor[0].values[i].value);
    show_text(0,row_pos[i],2,row_color[i], buff);
  } 
}
