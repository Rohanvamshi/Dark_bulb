#include<stdlib.h>
#include "ini_config_parser.h"

/*
Prints a map object

a_map: An array of maps
len: The length of the map array

Returns:
N/A
*/
void print_map(MAP * a_map, size_t len){
  size_t ctr = 0;
  for(ctr = 0; ctr < len; ctr++){

    //Stop at the first entry that has an empty key
    if(a_map[ctr].key == NULL){
      return;
    }
    // Print headers
    printf("=====%s=====\n", a_map[ctr].key);

    if(a_map[ctr].value != NULL){
      // Print Values
      printf("%s\n", a_map[ctr].value);
    }
  }
}


/*
Parses the config file

filep: The pointer to the file
content: The array to store key value pairs from the config
content_len: The length of the content array

Returns:
Returns an int of value 0 for success and -errno for failure
*/
int parse_ini_config(FILE * filep, MAP content[] , size_t content_len){

  size_t num_map_items = 0;
  char * label = NULL;
  char * label_value = NULL;
  int ret_val = 0;
  char line_buffer[MAX_LABEL_LEN];

  //Go through each line of file
  //The program will limit the number of lines read
  while((feof(filep) == 0)
          && (num_map_items <= content_len)){
    //Initialize storage for labels from config file
    label = (char*)calloc(MAX_LABEL_LEN, sizeof(char));
    label_value = (char*)calloc(MAX_LABEL_LEN, sizeof(char));

    //Read line
    if(fgets(line_buffer, MAX_LABEL_LEN, filep) != NULL){
      sscanf(line_buffer, ENTRY_FMT, label, label_value);

      //Check to make sure something is in the label_value
      if(*label_value != '\0'){
        content[num_map_items].key = label;
        content[num_map_items].value = label_value;
        label = NULL;
        label_value = NULL;
      }else if(*label != '\0'){
        content[num_map_items].key = label;
        content[num_map_items].value = NULL;
        label = NULL;
      }
      num_map_items++;
    }
  }
  //Check if cleanup needed
  if(label != NULL){
      free(label);
  }

  if(label_value != NULL){
    free(label_value);
  }
  return ret_val;
}
