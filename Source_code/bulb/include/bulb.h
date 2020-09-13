#ifndef BULB_H
#define BULB_H
#include "peripherals.h"

#define NO_ARGS 1         //Length of command line args when no args given
#define OPT_ARG_IDX 1     //Index of option command in command line args
#define VALID_CMD_LEN 3   //Length of command line args to have a valid config
                          //command
#define MAX_LINE_LEN 100  //Max line length when reading a line from file

//Check if bulb version has been defined
#ifndef BULB_VERSION
  #define BULB_VERSION "1"
#endif

//parse_config
#endif /*BULB_H*/
