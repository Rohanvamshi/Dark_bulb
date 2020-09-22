#ifndef SEVEN_SEG_PERIPHERAL_H
#define SEVEN_SEG_PERIPHERAL_H
#include <stdint.h>
#include "peripheral.h"
#define SEV_SEG_HEADER "7_SEG_DISPLAY"
#define SEV_SEG_A 'A'
#define SEV_SEG_B 'B'
#define SEV_SEG_C 'C'
#define SEV_SEG_D 'D'
#define SEV_SEG_E 'E'
#define SEV_SEG_F 'F'
#define SEV_SEG_G 'G'
#define SEV_SEG_MAX_VAL 255
#define NUM_SEV_DISPLAY_SEGS 7

/*
Defines a seven segment cathode display
*/
typedef struct seven_seg_display {
  PERIPHERAL base;
  uint8_t seg_a;
  uint8_t seg_b;
  uint8_t seg_c;
  uint8_t seg_d;
  uint8_t seg_e;
  uint8_t seg_f;
  uint8_t seg_g;
} SEVEN_SEG_DISPLAY;

/*
Prints out the contents of a seven seg display
*/
void print_seven_segment(SEVEN_SEG_DISPLAY sev_display);

/*
Sets the correct section of the seven segment display

sev_display: The seven segment display
seg: The char segment selected
value: The value to set the segment to

Returns:
Returns 0 on success, a negative value on failure
*/
int set_seven_segment(SEVEN_SEG_DISPLAY * sev_display, char seg, unsigned int value);
#endif /*SEVEN_SEG_PERIPHERAL_H*/