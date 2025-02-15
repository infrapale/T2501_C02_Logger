/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library. Pin numbers reflect the default
  SPI pins for Uno and Nano models

  The circuit:
   analog sensors on analog pins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** SDO - pin 11
 ** SDI - pin 12
 ** CLK - pin 13
 ** CS - depends on your SD card shield or module.
 		Pin 10 used here for consistency with other Arduino examples
    (for MKR Zero SD: SDCARD_SS_PIN)

  created  24 Nov 2010
  modified  24 July 2020
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>
#include "main.h"
#include "atask.h"
#include "logger.h"
#include "rtc_time.h"
#include "io.h"
#include "sensor.h"

const int chipSelect = LOGGER_SD_CS;
logger_st  logger;
extern   sensor_st sensor[]; 

void logger_task();

atask_st logger_handle                 = {"Data Logger    ", 5000,0, 0, 255, 0, 1, logger_task};


void logger_initialize(void) 
{
  Serial.print(F("Initializing SD card..."));

  if (!SD.begin(chipSelect)) {
    Serial.println(F("initialization failed. Things to check:"));
    Serial.println(F("1. is a card inserted?"));
    Serial.println(F("2. is your wiring correct?"));
    Serial.println(F("3. did you change the chipSelect pin to match your shield or module?"));
    Serial.println(F("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!"));
    logger.sd_ok = false;
    logger_handle.state = 0;
    delay(1000);
  }
  else
  {
      logger.sd_ok = true;
      logger.do_log = false;
      logger.task_indx = atask_add_new(&logger_handle);
      Serial.println(F("initialization done."));
      logger_handle.state = 10;
  }
}

void logger_do_log(void)
{
    logger.do_log = true;
}

void logger_task() {
  // make a string for assembling the data to log:
  // String dataString = "";
  char line_buff[80];
  

  if (logger.do_log)
  {
      logger.do_log = false;
 
      // strncpy(logger.file_name,"log-",4);
      rtc_time_get_date_str(&logger.file_name[0]);
      strcat(logger.file_name,".txt");
      //strncpy(logger.file_name,"L_250210.txt",12);
      File dataFile = SD.open(logger.file_name, FILE_WRITE);

      // if the file is available, write to it:
      if (dataFile) 
      {
        rtc_time_get_stamp(line_buff);
        dataFile.print(line_buff);
        dataFile.print(";");
        for (uint8_t i=0;i<3;i++)
        {
          sprintf(line_buff, "%s=%.1f;",sensor[0].values[i].label,sensor[0].values[i].value);
          dataFile.print(line_buff);
        } 
        dataFile.println();
        dataFile.close();
        // print to the serial port too:
        Serial.println(line_buff);
      }
      // if the file isn't open, pop up an error:
      else {
        Serial.print("error opening: ");
        Serial.println(logger.file_name);
      }
  }
}


