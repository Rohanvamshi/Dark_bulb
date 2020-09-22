#ifndef INI_CONFIG_PARSER_H
#define INI_CONFIG_PARSER_H

#include <stdio.h>
#define MAX_LINE_LEN 100
#define MAX_FILE_LINES 50
#define MAX_LABEL_LEN 50

// Define line formatting
#define SECTION_HEADER_FMT "\\[%s\\]"
#define ENTRY_FMT "%[^=]=%[^=]"

/*
Defines a key value pair
*/
typedef struct map{
  char * key;
  char * value;
}MAP;

/*
Prints a map object

a_map: An array of maps
len: The length of the map array

Returns:
N/A
*/
void print_map(MAP *a_map, size_t len);


/*
Checks to see if the given map object is a header or not

a_map: The given MAP object

Returns:
1 if the map object is a header, else 0;
*/
int is_header(MAP a_map);

/*
Parses the config file

filep: The pointer to the file
content: The array to store key value pairs from the config
content_len: The length of the content array

Returns:
Returns an int of value 0 for success and -errno for failure
*/
int parse_ini_config(FILE * filep, MAP  content[], size_t content_len);

#endif /*INI_CONFIG_PARSER_H*/
