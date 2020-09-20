#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>

#include "bulb.h"
#include "ini_config_parser.h"

//Include peripherals
#include "seven_seg_peripheral.h"
#include "infrared_fc_51_peripheral.h"
#pragma pack(1)

char * USAGE_BANNER = "Usage: bulb [OPTIONS]\n\n"
                      "A program that detects motion and "
                      "displays the number \n"
                      "of times that motion was detected "
                      "to a 7-segment display\n\n"
                      "Options:\n"
                      "\t\t%s filename\t\tLocation of bulb config file\n"
                      "\t\t%s\t\t\tPrint the version info\n";

/*
Program options
*/
char * OPT_CONFIG  = "--config";
char * OPT_VERSION = "--version";

/*
Initializes a given seven seg display structure based on the given ini map

seven_display: The seven segment peripheral structure
ini_content: The ini map object containin the config data

Returns:
Returns 0 on success, else returns -1 on failure
*/
int init_seven_seg_peripheral(SEVEN_SEG_DISPLAY * seven_display, MAP ini_content[], size_t len){

  //Check map contains correct number of segs + header
  if(len < NUM_SEGS+1){
    printf("Nnumber of segs listed in ini map is not enough\n");
    return -1;
  }

  int ctr = 0;
  int is_seven_seg_header = 0;
  MAP entry;
  for(ctr = len; ctr < len; ctr ++){
    entry = ini_content[ctr];

    //Check if we have reached the seven segment display section
    if(is_header(entry) && strstr(entry.key, SEV_SEG_HEADER) != NULL){
      is_seven_seg_header = 1;
      printf("%s header found\n", SEV_SEG_HEADER);

    //If we have reached a header that is not seven segment
    } else if(is_header(entry) && strstr(entry.key, SEV_SEG_HEADER) == NULL){
      break;
    }

    //When inside of the seven_seg_section, set segment in display
    if(is_header(entry) != 1 && entry.value != NULL && is_seven_seg_header){
      set_seven_segment(seven_display, entry.key[0], (unsigned int)atoi(entry.value));
    }
  }
  return 0;
}


/*
Main program
*/
int main(int argc, char **argv){
  char * option = argv[OPT_ARG_IDX];
  char * filename  = NULL;
  FILE * filep = NULL;
  MAP ini_content[MAX_FILE_LINES+1];

  if(argc == NO_ARGS){
    printf(USAGE_BANNER, OPT_CONFIG, OPT_VERSION);
    goto leave;
  }

  // Run version option if matching
  if(strcmp(option, OPT_VERSION) == 0){
    printf("%s\n", BULB_VERSION);
    goto leave;

  // Run config option if matching
  }else if(strcmp(option, OPT_CONFIG) == 0){
    if(argc == VALID_CMD_LEN){
      filename = argv[OPT_ARG_IDX+1];
    }else{
      printf("Usage: bulb %s filename\n", OPT_CONFIG);
      goto leave;
    }
  }else{
    //Option not supported
    printf("%s is not supported\n", option);
    goto leave;
  }

  //Load config file
  if( (filep = fopen(filename, "r")) == 0){
    printf("Error opening file %s\n", filename);
    goto leave;
  }

  printf("Reading from config file %s\n", filename);
  memset(ini_content, 0, sizeof(MAP)*MAX_FILE_LINES);

  //Parse file contents into map object
  parse_ini_config(filep, ini_content, MAX_FILE_LINES);
  print_map(ini_content, MAX_FILE_LINES);
  SEVEN_SEG_DISPLAY seven_display = {.seg_a = 0,.seg_b = 0,
                                          .seg_c = 0, .seg_d = 0,
                                          .seg_e = 0,.seg_f = 0, .seg_g = 0};

  //Initialize seven segment display
  if(init_seven_seg_peripheral(&seven_display, ini_content,
      (size_t) MAX_FILE_LINES) < 0){
    printf("Error initializing seven segment display peripheral configuration");
    goto leave;
  }
  print_seven_segment(seven_display);

  leave:
    //Close file if open
    if(filep > 0)
      fclose(filep);

    return 0;
}
