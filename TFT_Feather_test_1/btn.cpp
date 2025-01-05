#include "Arduino.h"
#include "BM32_Btn.h"
#include "btn.h"
#include "Adafruit_miniTFTWing.h"
#include "atask.h"



typedef struct 
{
  uint8_t indx;
  uint32_t bitmap;
  bool      pospol;
} btn_st;

btn_st btn[BUTTON_NBR_OF] =
{
    [BUTTON_UP]     = {0, BUTT_UP, false},
    [BUTTON_DOWN]   = {0, BUTT_DOWN, false},
    [BUTTON_LEFT]   = {0, BUTT_LEFT, false},
    [BUTTON_RIGHT]  = {0, BUTT_RIGHT, false}, 
    [BUTTON_SELECT] = {0,BUTT_SELECT, false},
    [BUTTON_A]      = {0, BUTT_A, false}, 
    [BUTTON_B]      = {0, BUTT_B, false},
};

Adafruit_miniTFTWing ss;

atask_st btn_handle                = {"Button Task    ", 50,0, 0, 255, 0, 1, btn_task};
uint32_t version;

// const uint32_t btn_mask[] = 
// {
//     TFTWING_BUTTON_UP, TFTWING_BUTTON_DOWN, TFTWING_BUTTON_LEFT,
//     TFTWING_BUTTON_RIGHT, TFTWING_BUTTON_A, TFTWING_BUTTON_B,
//     TFTWING_BUTTON_SELECT
// };

Bm32Btn btn32;

void btn_initialize(void)
{

  if (!ss.begin(0x5F)) {
    Serial.println("seesaw couldn't be found!");
    while(1) Serial.print("%");
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

  btn32.Init(4,20,4);

  for (uint8_t i= 0; i < BUTTON_NBR_OF; i++)
  {
      btn[i].indx = btn32.AddBm(btn[i].bitmap, btn[i].pospol);
      Serial.print(btn[i].indx); Serial.print(" : ");
		  Serial.println(btn[i].bitmap,HEX);
  }
  atask_add_new(&btn_handle);
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
          // Serial.println(butt_bit_map,HEX);
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
        Serial.print("Button: "); Serial.print(i); Serial.print("="); Serial.println(butt);
      }
  }
}