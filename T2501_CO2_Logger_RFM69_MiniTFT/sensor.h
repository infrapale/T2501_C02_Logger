#ifndef __SENSOR_H__
#define __SENSOR_H__

#define  SENSOR_SENSOR_LEN    10
#define  SENSOR_NAME_LEN      10
#define  ZONE_NAME_LEN        10
#define  SENSOR_MAX_VALUES    4

//#define ZONE_UNDEFINED 
//#define ZONE_VA_TUPA
//#define ZONE_TEST
//#define ZONE_VA_VARASTO
#define ZONE_CO2_LOGGER

//#define SENSOR_VA_MH1
//#define SENSOR_VA_MH2
//#define SENSOR_VA_PARVI
//#define SENSOR_VA_KHH
//#define SENSOR_VA_OD
//#define SENSOR_LA_H
//#define SENSOR_LA_STUDIO
//#define SENSOR_DOCK

typedef enum
{
  SENSOR_VALUE_UNDEFINED = 0,
  SENSOR_VALUE_TEMPERATURE,
  SENSOR_VALUE_CO2,
  SENSOR_VALUE_HUMIDITY,
  SENSOR_VALUE_PRESSURE,
  SENSOR_VALUE_GAS,
  SENSOR_VALUE_LDR,
  SENSOR_VALUE_LUX,
  SENSOR_VALUE_ALS,
  SENSOR_VALUE_WHITE,
} sensor_value_type_et;

typedef enum
{
  SENSOR_UNDEFINED = 0,
  SENSOR_BME680,
  SENSOR_SCD30,
  SENSOR_LDR,
  SENSOR_VEML7700,
  SENSOR_MCP9808,
  SENSOR_BME680_HUM,
  SENSOR_BME680_PRESSURE,
  SENSOR_CO2,
  SENSOR_PCT2075,
  SENSOR_NBR_OF
} sensor_et;


typedef struct
{
  char                  label[SENSOR_NAME_LEN];
  sensor_value_type_et  type;
  uint8_t               addr;
  float                 value;
  bool                  updated;
  uint32_t              next_ms;
  uint32_t              interval_ms;          
 } value_st;

typedef struct
{
  char        zone[ZONE_NAME_LEN];
  sensor_et   sensor_type;
  value_st   values[SENSOR_MAX_VALUES];
} sensor_st;

void sensor_initialize(void);
void sensor_read_task(void);
void sensor_send_task(void);


#endif




