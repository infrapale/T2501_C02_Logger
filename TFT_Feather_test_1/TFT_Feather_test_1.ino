/******************************************************************************
Test sketch for the BM32_Btn library and the Adafruit Mini TFT 
with Joystick Featherwing
*******************************************************************************
Hardware:
TFT Featherwing olf SAM09 version used
https://learn.adafruit.com/adafruit-mini-tft-featherwing/pinouts
*******************************************************************************
Own libraries required:
https://github.com/infrapale/T2409_atask
*****************************************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include "Adafruit_miniTFTWing.h"
#include "atask.h"
//#include "BM32_Btn.h"
#include "btn.h"

#define TFT_RST    -1    // we use the seesaw for resetting to save a pin
#define TFT_CS   5
#define TFT_DC   6

Adafruit_ST7789 tft_7789 = Adafruit_ST7789(TFT_CS,  TFT_DC, TFT_RST);
Adafruit_ST7735 tft_7735 = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void debug_print_task(void);
void btn_task(void);
void btn_read_all(void);

atask_st debug_print_handle        = {"Debug Print    ", 5000,0, 0, 255, 0, 1, debug_print_task};

// we'll assign it later
Adafruit_ST77xx *tft = NULL;



void initialize_tasks(void)
{
  atask_initialize();
  atask_add_new(&debug_print_handle);
  btn_initialize();
}

void setup()   {
  Serial.begin(115200);
  delay(3000);
  while (!Serial)  delay(10);  // Wait until serial console is opened

  
  tft_7735.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display
  tft = &tft_7735;
  tft->setRotation(1);
  Serial.println("TFT initialized");

  tft->fillScreen(ST77XX_RED);
  delay(100);
  tft->fillScreen(ST77XX_GREEN);
  delay(100);
  tft->fillScreen(ST77XX_BLUE);
  delay(100);
  tft->fillScreen(ST77XX_BLACK);

  initialize_tasks();
}

void loop() {
  //delay(10);
  atask_run();
  // btn_read_all();
  //Serial.print("#");
  /*
  uint32_t buttons = ss.readButtons();
  //Serial.println(buttons, BIN);
  
  uint16_t color;

  color = ST77XX_BLACK;
  if (! (buttons & TFTWING_BUTTON_LEFT)) {
    Serial.println("LEFT");
    color = ST77XX_WHITE;
  }
  tft->fillTriangle(150, 30, 150, 50, 160, 40, color);

  color = ST77XX_BLACK;
  if (! (buttons & TFTWING_BUTTON_RIGHT)) {
    Serial.println("RIGHT");
    color = ST77XX_WHITE;
  }
  tft->fillTriangle(120, 30, 120, 50, 110, 40, color);

  color = ST77XX_BLACK;
  if (! (buttons & TFTWING_BUTTON_DOWN)) {
    Serial.println("DOWN");
    color = ST77XX_WHITE;
  }
  tft->fillTriangle(125, 26, 145, 26, 135, 16, color);
  
  color = ST77XX_BLACK;
  if (! (buttons & TFTWING_BUTTON_UP)) {
    Serial.println("UP");
    color = ST77XX_WHITE;
  }
    tft->fillTriangle(125, 53, 145, 53, 135, 63, color);
  
  color = ST77XX_BLACK;
  if (! (buttons & TFTWING_BUTTON_A)) {
    Serial.println("A");
    color = ST7735_GREEN;
  }
  tft->fillCircle(30, 57, 10, color);
  
  color = ST77XX_BLACK;
  if (! (buttons & TFTWING_BUTTON_B)) {
    Serial.println("B");
    color = ST77XX_YELLOW;
  }
  tft->fillCircle(30, 18, 10, color);
  
  color = ST77XX_BLACK;
  if (! (buttons & TFTWING_BUTTON_SELECT)) {
    Serial.println("SELECT");
    color = ST77XX_RED;
  }
    tft->fillCircle(80, 40, 7, color);
  */  
}

void debug_print_task(void)
{
  atask_print_status(true);
  btn_read_all();
  
}
