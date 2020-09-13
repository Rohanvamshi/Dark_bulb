#ifndef PERIPHERAL_H
#define PERIPHERAL_H

/*
Defines a peripheral
*/
typedef struct peripheral {
  char * name;
} PERIPHERAL;

/*
Defines a seven segment cathode display
*/
typedef struct seven_seg_display {
  PERIPHERAL base;
  unsigned int seg_a :1;
  unsigned int seg_b :1;
  unsigned int seg_c :1;
  unsigned int seg_d :1;
  unsigned int seg_e :1;
  unsigned int seg_f :1;
  unsigned int seg_g :1;
} SEVEN_SEG_DISPLAY;


/*
Defines a Infrared sensor
*/
typedef struct infrared_sensor {
  PERIPHERAL base;
  unsigned int seg_out :1;
} INFRARED_SENSOR;
#endif /*PERIPHERAL_H*/
