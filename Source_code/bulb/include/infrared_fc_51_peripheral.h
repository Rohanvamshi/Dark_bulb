#ifndef INFRARED_FC_51_PERIPHERAL_H
#define INFRARED_FC_51_PERIPHERAL_H

#include <stdint.h>
#include "peripheral.h"

#define INF_SENSOR_HEADER "INFRARED_SENSOR"
#define INF_SENSOR_OUT 'O'
#define INF_FC51_MAX_VAL 255
#define NUM_INF_SENSOR_SEGS 1
/*
Defines a Infrared sensor
*/
typedef struct infrared_sensor {
  PERIPHERAL base;
  uint8_t out_pin;
} INFRARED_SENSOR;

/*
Prints out an infrared sensor

inf_sensor: An infrared sensor structur

Returns:
	N/A
*/
void print_infrared_sensor(INFRARED_SENSOR inf_sensor);

/*
Sets the correct pin of the infrared sensor

sev_display: The infrared sensor fc 51
seg: The char segment selected
value: The value to set the pin to

Returns:
	Returns 0 on success, a negative value on failure
*/
int set_inf_fc51_segment(INFRARED_SENSOR * inf_sensor, char seg, unsigned int value);
#endif /*INFRARED_FC_51_PERIPHERAL_H*/