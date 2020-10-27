#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<unistd.h> //close

#include "bulb.h"
#include "ini_config_parser.h"

//Include peripherals
#include "seven_seg_peripheral.h"
#include "infrared_fc_51_peripheral.h"

//Include devgpio ioctl commands
#include "../../dev_gpio/include/dev_gpio.h"

#define DEVICE_FILENAME "/dev/devgpio"
#pragma pack(1)

static const char * USAGE_BANNER = "Usage: bulb [OPTIONS]\n\n"
                      "A program that detects motion and "
                      "displays the number \n"
                      "of times that motion was detected "
                      "to a 7-segment display\n\n"
                      "Options:\n"
                      "\t\t%s filename\t\tLocation of bulb config file\n"
                      "\t\t%s\t\t\tPrint the version info\n";

/*
Peripherals
*/
static SEVEN_SEG_DISPLAY seven_display = {.seg_a = 0,.seg_b = 0,
                                          .seg_c = 0, .seg_d = 0,
                                          .seg_e = 0,.seg_f = 0, .seg_g = 0};

static INFRARED_SENSOR inf_fc51_sensor = {.out_pin = 0};

/*
Program options
*/
static const char * OPT_CONFIG  = "--config";
static const char * OPT_VERSION = "--version";


/*Write a 0 to the seven segment display
*/
int write_0(void){
  u_int32_t pin = 0;
  u_int32_t on = 1;
  int ret = 0;

  //Open device file for reading and writing
  int dev_fd = open(DEVICE_FILENAME, O_RDWR);

  if(dev_fd < 0){
      printf("Error opening file\n");
      ret = dev_fd;
      goto leave;
  }

  //Write to segment A
  pin = (seven_display.seg_a << 8);
  pin = pin | on;
  printf("Writing A");
  ret = ioctl(dev_fd, DEV_GPIO_IOC_WRITE, &pin);
  pin = 0;
  if (ret < 0){
    return ret;
  }

  //Write to segment B
  pin = (seven_display.seg_b << 8);
  pin = pin | on;
  ret = ioctl(dev_fd, DEV_GPIO_IOC_WRITE, &pin);
  pin = 0;
  if (ret < 0){
    return ret;
  }

  //Write to segment C
  pin = (seven_display.seg_c << 8);
  pin = pin | on;
  ret = ioctl(dev_fd, DEV_GPIO_IOC_WRITE, &pin);
  pin = 0;
  if (ret < 0){
    return ret;
  }

  //Write to segment D
  pin = (seven_display.seg_d << 8);
  pin = pin | on;
  ret = ioctl(dev_fd, DEV_GPIO_IOC_WRITE, &pin);
  pin = 0;
  if (ret < 0){
    return ret;
  }

  //Write to segment E
  pin = (seven_display.seg_e << 8);
  pin = pin | on;
  ret = ioctl(dev_fd, DEV_GPIO_IOC_WRITE, &pin);
  pin = 0;
  if (ret < 0){
    return ret;
  }

  //Write to segment F
  pin = (seven_display.seg_f << 8);
  pin = pin | on;
  ret = ioctl(dev_fd, DEV_GPIO_IOC_WRITE, &pin);
  pin = 0;
  if (ret < 0){
    return ret;
  }

  //Write to segment F
  pin = (seven_display.seg_g << 8);
  pin = pin | 0;
  ret = ioctl(dev_fd, DEV_GPIO_IOC_WRITE, &pin);
  pin = 0;
  if (ret < 0){
    return ret;
  }

  leave:
    close(dev_fd);
    return ret;

}

/*Initializes the board with the configurations stated for the sensors.

inf-sensor: The infrared sensor
seven_display: The 7 segment cathode display

Returns:
Returns the file descriptor of the open device file
*/
int init_program_board(INFRARED_SENSOR * inf_sensor, SEVEN_SEG_DISPLAY * seven_display){
  u_int32_t pin = 0;
  int ret = 0;

  //Open device file for reading and writing
  int dev_fd = open(DEVICE_FILENAME, O_RDWR);

  if(dev_fd < 0){
      printf("Error opening file\n");
      ret = dev_fd;
      goto leave;
  }

  //Initialize infrared sensor on board
  pin = (inf_sensor->out_pin << 8);
  pin = pin | GPIO_IN; //Set pin direction to in
  printf("Set pin %u to out direction via ioctl changedir\n", inf_sensor->out_pin);
  ret = ioctl(dev_fd, DEV_GPIO_IOC_CHANGEDIR, &pin);
  if(ret < 0){
    goto leave;
  }
  
  //Initialize seven segment display

  //Setting segment A
  pin = 0;
  pin = (seven_display->seg_a << 8);
  pin = pin | GPIO_OUT; //Set pin direction to out
  printf("Set pin %u to in direction via ioctl changedir\n", seven_display->seg_a);
  ret = ioctl(dev_fd, DEV_GPIO_IOC_CHANGEDIR, &pin);
  if(ret < 0){
    goto leave;
  }

  //Setting segment B
  pin = 0;
  pin = (seven_display->seg_b << 8);
  pin = pin | GPIO_OUT; //Set pin direction to out
  printf("Set pin %u to in direction via ioctl changedir\n", seven_display->seg_b);
  ret = ioctl(dev_fd, DEV_GPIO_IOC_CHANGEDIR, &pin);
  if(ret < 0){
    goto leave;
  }

  //Setting segment C
  pin = 0;
  pin = (seven_display->seg_c << 8);
  pin = pin | GPIO_OUT; //Set pin direction to out
  printf("Set pin %u to in direction via ioctl changedir\n", seven_display->seg_c);
  ret = ioctl(dev_fd, DEV_GPIO_IOC_CHANGEDIR, &pin);
  if(ret < 0){
    goto leave;
  }

    //Setting segment D
  pin = 0;
  pin = (seven_display->seg_d << 8);
  pin = pin | GPIO_OUT; //Set pin direction to out
  printf("Set pin %u to in direction via ioctl changedir\n", seven_display->seg_d);
  ret = ioctl(dev_fd, DEV_GPIO_IOC_CHANGEDIR, &pin);
  if(ret < 0){
    goto leave;
  }

    //Setting segment E
  pin = 0;
  pin = (seven_display->seg_e << 8);
  pin = pin | GPIO_OUT; //Set pin direction to out
  printf("Set pin %u to in direction via ioctl changedir\n", seven_display->seg_e);
  ret = ioctl(dev_fd, DEV_GPIO_IOC_CHANGEDIR, &pin);
  if(ret < 0){
    goto leave;
  }

    //Setting segment F
  pin = 0;
  pin = (seven_display->seg_f << 8);
  pin = pin | GPIO_OUT; //Set pin direction to out
  printf("Set pin %u to in direction via ioctl changedir\n", seven_display->seg_f);
  ret = ioctl(dev_fd, DEV_GPIO_IOC_CHANGEDIR, &pin);
  if(ret < 0){
    goto leave;
  }

    //Setting segment G
  pin = 0;
  pin = (seven_display->seg_g << 8);
  pin = pin | GPIO_OUT; //Set pin direction to out
  printf("Set pin %u to in direction via ioctl changedir\n", seven_display->seg_g);
  ret = ioctl(dev_fd, DEV_GPIO_IOC_CHANGEDIR, &pin);
  if(ret < 0){
    goto leave;
  }

  leave:
    close(dev_fd);
    return ret;

}

/*
Initializes a given infrared structure based on the given ini map

inf_sensor: The infrared peripheral structure
ini_content: The ini map object containin the config data
len: The length of the ini_content

Returns:
  Returns 0 on success, else returns -1 on failure
*/
int init_inffc51_peripheral(INFRARED_SENSOR * inf_sensor, MAP ini_content[], size_t len){

  int ret = 0;
    //Check map contains correct number of segs + header
  if(len < NUM_INF_SENSOR_SEGS+1){
    printf("Number of segs listed in ini map is not enough\n");
    ret = -1;
    return ret;
  }

  int ctr = 0;
  int is_inf_header = 0;
  MAP entry;
  for(ctr = 0; ctr < len; ctr++){  
    entry = ini_content[ctr];

    //Check if we have reached the seven segment display section
    if(is_header(entry) && strstr(entry.key, INF_SENSOR_HEADER) != NULL){
      is_inf_header = 1;
      printf("%s header found\n", INF_SENSOR_HEADER);

    //If we have reached a header that is not seven segment
    } else if(is_header(entry) && strstr(entry.key, INF_SENSOR_HEADER) == NULL){
      is_inf_header = 0;
      continue;
    }

    //When inside of the infrared_section, set out pin value
    if(is_header(entry) != 1 && entry.value != NULL && is_inf_header){
      printf("Setting segment %c of infrared sensor to %s\n", entry.key[0], entry.value);
      if(set_inf_fc51_segment(inf_sensor, entry.key[0], (unsigned int)atoi(entry.value))){
        printf("Error setting infrared sensor %s. \n", entry.key);
        ret = -1;
      }
    }
  }
  return ret;
}


/*
Initializes a given seven seg display structure based on the given ini map

seven_display: The seven segment peripheral structure
ini_content: The ini map object containin the config data
len: The length of the ini_content

Returns:
  Returns 0 on success, else returns -1 on failure
*/
int init_seven_seg_peripheral(SEVEN_SEG_DISPLAY * seven_display, MAP ini_content[], size_t len){

  int ret = 0;
  //Check map contains correct number of segs + header
  if(len < NUM_SEV_DISPLAY_SEGS+1){
    printf("Number of segs listed in ini map is not enough\n");
    ret = -1;
    return ret;
  }

  int ctr = 0;
  int is_seven_seg_header = 0;
  MAP entry;
  for(ctr = 0; ctr < len; ctr++){  
    entry = ini_content[ctr];

    //Check if we have reached the seven segment display section
    if(is_header(entry) && strstr(entry.key, SEV_SEG_HEADER) != NULL){
      is_seven_seg_header = 1;
      printf("%s header found\n", SEV_SEG_HEADER);

    //If we have reached a header that is not seven segment
    } else if(is_header(entry) && strstr(entry.key, SEV_SEG_HEADER) == NULL){
      is_seven_seg_header = 0;
      continue;
    }

    //When inside of the seven_seg_section, set segment in display
    if(is_header(entry) != 1 && entry.value != NULL && is_seven_seg_header){
      printf("Setting segment %c of seven segment display to %s\n", entry.key[0], entry.value);
      if(set_seven_segment(seven_display, entry.key[0], (unsigned int)atoi(entry.value))){
        printf("Error setting %s of seven segment display\n", entry.key);
        ret = -1;
      }
    }
  }
  return ret;
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
  if(parse_ini_config(filep, ini_content, MAX_FILE_LINES) < 0){
    printf("Error parsing ini config file");
    goto cleanup;
  }

  //Initialize seven segment display if specified in the file
  if(init_seven_seg_peripheral(&seven_display, ini_content,
      (size_t) MAX_FILE_LINES) < 0){
    printf("Error initializing seven segment display peripheral configuration");
    goto cleanup;
  }
  print_seven_segment(seven_display);

  //Initialize infrared sensor if specified in the file
  if(init_inffc51_peripheral(&inf_fc51_sensor, ini_content,
      (size_t) MAX_FILE_LINES) < 0){
    printf("Error initializing infrared sensor peripheral configuration");
    goto cleanup;
  }
  print_infrared_sensor(inf_fc51_sensor);

  //Initialize board
  printf("Initializing board....");
  if(init_program_board(&inf_fc51_sensor, &seven_display) < 0){
    printf("Failed to initialize board with given configuration");
    goto cleanup;
  }

  //Test
  printf("Writing a 0");
  if(write_0() < 0){
    printf("Failed to initialize board with given configuration");
  }

  cleanup:
    //Cleanup ini parser content
    free_map_list(ini_content, (size_t) MAX_FILE_LINES);

  leave:
    //Close file if open
    if(filep > 0)
      fclose(filep);

    return 0;
}
