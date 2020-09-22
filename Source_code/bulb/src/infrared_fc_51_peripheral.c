#include <stdio.h>
#include "infrared_fc_51_peripheral.h"

/*
Prints out an infrared sensor

inf_sensor: An infrared sensor structur

Returns:
N/A
*/
void print_infrared_sensor(INFRARED_SENSOR inf_sensor){

	printf("%s\n", INF_SENSOR_HEADER);
	printf("OUT PIN: %u\n", inf_sensor.out_pin);
	return;
}

/*
Sets the correct pin of the infrared sensor

sev_display: The infrared sensor fc 51
seg: The char segment selected
value: The value to set the pin to

Returns:
	Returns 0 on success, a negative value on failure
*/
int set_inf_fc51_segment(INFRARED_SENSOR * inf_sensor, char seg, unsigned int value){

	if(value > INF_FC51_MAX_VAL){
		return -1;
	}

	//Select a segment
	switch(seg){
		case INF_SENSOR_OUT:
			inf_sensor->out_pin = value;
			break;

		// Invalid segment
		default:
			return -1;
	}
	return 0;
}