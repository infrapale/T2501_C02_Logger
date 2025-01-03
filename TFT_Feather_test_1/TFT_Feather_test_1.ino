#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include "Adafruit_miniTFTWing.h"
#include "atask.h"
#include "BM32_Btn.h"

Adafruit_miniTFTWing ss;
#define TFT_RST    -1    // we use the seesaw for resetting to save a pin
#define TFT_CS   5
#define TFT_DC   6

Adafruit_ST7789 tft_7789 = Adafruit_ST7789(TFT_CS,  TFT_DC, TFT_RST);
Adafruit_ST7735 tft_7735 = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void debug_print_task(void);
void btn_task(void);
void btn_read_all(void);

atask_st debug_print_handle        = {"Debug Print    ", 5000,0, 0, 255, 0, 1, debug_print_task};
atask_st btn_handle                = {"Button Task    ", 10,0, 0, 255, 0, 1, btn_task};

// we'll assign it later
Adafruit_ST77xx *tft = NULL;
uint32_t version;


void initialize_tasks(void)
{
  atask_initialize();
  atask_add_new(&debug_print_handle);
  atask_add_new(&btn_handle);
}

void setup()   {
  Serial.begin(115200);
  
  while (!Serial)  delay(10);  // Wait until serial console is opened

  if (!ss.begin(0x5F)) {
    Serial.println("seesaw couldn't be found!");
    while(1);
  }

  version = ((ss.getVersion() >> 16) & 0xFFFF);
  Serial.print("Version: "); Serial.println(version);
  if (version == 3322) {
    Serial.println("Houston, we have a problem");
  } else {
    Serial.println("Version 1 TFT FeatherWing found");
  }
  
  ss.tftReset();   // reset the display
  ss.setBacklight(TFTWING_BACKLIGHT_ON);  // turn off the backlight

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
  btn_read_all();
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
}

typedef enum 
{
    BUTTON_UP = 0, 
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT, 
    BUTTON_A, 
    BUTTON_B,
    BUTTON_SELECT,
    BUTTON_NBR_OF
} btn_et;

typedef struct 
{
  uint8_t indx;
  uint32_t bitmap;
} btn_st;

btn_st btn[BUTTON_NBR_OF] =
{
    [BUTTON_UP]     = {0,TFTWING_BUTTON_UP},
    [BUTTON_DOWN]   = {0,TFTWING_BUTTON_DOWN},
    [BUTTON_LEFT]   = {0,TFTWING_BUTTON_LEFT},
    [BUTTON_RIGHT]  = {0,TFTWING_BUTTON_RIGHT}, 
    [BUTTON_A]      = {0,TFTWING_BUTTON_A}, 
    [BUTTON_B]      = {0,TFTWING_BUTTON_B},
    [BUTTON_SELECT] = {0,TFTWING_BUTTON_SELECT}
};


// const uint32_t btn_mask[] = 
// {
//     TFTWING_BUTTON_UP, TFTWING_BUTTON_DOWN, TFTWING_BUTTON_LEFT,
//     TFTWING_BUTTON_RIGHT, TFTWING_BUTTON_A, TFTWING_BUTTON_B,
//     TFTWING_BUTTON_SELECT
// };

Bm32Btn btn32;

void btn_initialize(void)
{
  btn32.Init();

  for (uint8_t i= 0; i < BUTTON_NBR_OF; i++)
  {
      btn[i].indx = btn32.AddBm(btn[i].bitmap);
  }
}

void btn_task(void)
{
    switch(btn_handle.state)
    {
        case 0:
            btn_initialize();
            btn_handle.state = 10;
            break;
        case 10:  
          uint32_t butt_bit_map = ss.readButtons();
          btn32.Process(butt_bit_map);
          break;  
    }
}

void btn_read_all(void)
{
  for (uint8_t i= 0; i < BUTTON_NBR_OF; i++)
  {
      btn_status_et butt = btn32.Read(i);
      if (butt != PRESSED_UNDEFINED )
      {
        Serial.print("Button: "); Serial.println(butt);
      }
  }
}