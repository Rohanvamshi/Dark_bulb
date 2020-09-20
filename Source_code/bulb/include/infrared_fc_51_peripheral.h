#ifndef INFRARED_FC_51_PERIPHERAL_H
#define INFRARED_FC_51_PERIPHERAL_H

#include "peripheral.h"

#define INF_SENSOR_HEADER "INFRARED_SENSOR"
#define INF_SENSOR_OUT 'O'

/*
Defines a Infrared sensor
*/
typedef struct infrared_sensor {
  PERIPHERAL base;
  unsigned int seg_out :1;
} INFRARED_SENSOR;

#endif /*INFRARED_FC_51_PERIPHERAL_H*/