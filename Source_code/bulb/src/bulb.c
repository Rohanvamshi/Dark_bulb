#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>

#include "bulb.h"
#include "peripherals.h"
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
Main program
*/
int main(int argc, char **argv){
  char * option = argv[OPT_ARG_IDX];
  char * filename  = NULL;
  FILE * filep = NULL;
  char line_buffer[MAX_LINE_LEN];

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



  leave:
    //Close file if open
    if(filep > 0)
      fclose(filep);

    return 0;
}
