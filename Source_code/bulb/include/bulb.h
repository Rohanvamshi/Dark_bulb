#ifndef BULB_H
#define BULB_H
#include "ini_config_parser.h"
#include "infrared_fc_51_peripheral.h"
#include "seven_seg_peripheral.h"
#define NO_ARGS 1         //Length of command line args when no args given
#define OPT_ARG_IDX 1     //Index of option command in command line args
#define VALID_CMD_LEN 3   //Length of command line args to have a valid config
                          //command
#define MAX_LINE_LEN 100  //Max line length when reading a line from file

//Check if bulb version has been defined
#ifndef BULB_VERSION
  #define BULB_VERSION "1"
#endif

/*
Initializes a given infrared structure based on the given ini map

inf_sensor: The infrared peripheral structure
ini_content: The ini map object containin the config data

Returns:
	Returns 0 on success, else returns -1 on failure
*/
int init_inffc51_peripheral(INFRARED_SENSOR * inf_sensor, MAP ini_content[], size_t len);

/*
Initializes a given seven seg display structure based on the given ini map

seven_display: The seven segment peripheral structure
ini_content: The ini map object containin the config data
len: the length of the ini_content array

Returns:
	Returns 0 on success, else returns -1 on failure
*/
int init_seven_seg_peripheral(SEVEN_SEG_DISPLAY * seven_display, MAP ini_content[], size_t len);

/*Initializes the board with the configurations stated for the sensors.

inf-sensor: The infrared sensor
seven_display: The 7 segment cathode display

Returns:
Returns the file descriptor of the open device file
*/
int init_program_board(INFRARED_SENSOR * inf_sensor, SEVEN_SEG_DISPLAY * seven_display);
//parse_config
#endif /*BULB_H*/
