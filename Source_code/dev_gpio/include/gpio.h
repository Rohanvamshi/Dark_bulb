#ifndef GPIO_H
#define GPIO_H
#include <linux/types.h>

//GPIO PIN count
#define GPIO_PIN_COUNT 54

// GPIO Physical base address
#define GPIO_BASE 0x3f200000

// GPIO offset for GPLEV (read state) registers
#define GPIO_GPLEV_OFFSET 0x34

// GPIO offset for GPSET (set to 1) registers
#define GPIO_GPSET_OFFSET 0x1c

// GPIO offset for GPCLR (set to 0) registers
#define GPIO_GPCLR_OFFSET 0x28

//GPIO register size
#define GPIO_REG_SIZE 0x4

//GPIO GPFSEL bit length
#define GPIO_GPSEL_FUNC_SIZE 3

//GPIO offset for GPFSEL0 pins 0 - 9
#define GPIO_GPFSEL0_OFFSET 0x00

//GPIO offset for GPFSEL1 pins  10 - 19
#define GPIO_GPFSEL1_OFFSET 0x04

//GPIO offset for GPFSEL2 pins  20 - 29
#define GPIO_GPFSEL2_OFFSET 0x08

//GPIO offset for GPFSEL3 pins  30 - 39
#define GPIO_GPFSEL3_OFFSET 0x0c

//GPIO offset for GPFSEL4 pins  40 - 49
#define GPIO_GPFSEL4_OFFSET 0x10

//GPIO offset for GPFSEL5 pins  50 - 53
#define GPIO_GPFSEL5_OFFSET 0x14

//Checks if GPFSEL0 applies to pin x
#define IN_RANGE_GPFSEL0(x) (x <= 9 && x >= 0)

//Checks if GPFSEL1 applies to pin x
#define IN_RANGE_GPFSEL1(x) (x <= 19 && x >= 10)

//Checks if GPFSEL2 applies to pin x
#define IN_RANGE_GPFSEL2(x) (x <= 29 && x >= 20)

//Checks if GPFSEL3 applies to pin x
#define IN_RANGE_GPFSEL3(x) (x <= 39 && x >= 30)

//Checks if GPFSEL4 applies to pin x
#define IN_RANGE_GPFSEL4(x) (x <= 49 && x >= 40)

//Checks if GPFSEL5 applies to pin x
#define IN_RANGE_GPFSEL5(x) (x <= (GPIO_PIN_COUNT-1) && x >= 50)

//GPIO value for selecting input mode
#define GPIO_GPFSEL_IN 0x00

//GPIO value for selecting output mode
#define GPIO_GPFSEL_OUT 0x01


/*
Internal implementations of device functions

pin_arg: The pin direction (0 for in, 1 for out) is in the first bit,
The pin number is represented as a value contained in bytes 8-15

Returns:
	Returns 0 for success or -1 for error
*/
int change_pin_dir(uint32_t pin_num, uint32_t pin_dir);

/*
Internal implementations of device functions

pin_num: The pin value to write to is in the first bit,
pin_val: The value to write to the pin (0 or 1)

Returns:
	Returns 0 for success or -1 for error
*/
int write_to_pin(uint32_t pin_num, uint32_t pin_val);

/*
Reads from the specified ioctl pin.
Assumes that the pin number is the physical pin number on the board
in the pinout diagram.

pin_num: The pin number to read from

Returns:
	0 or 1 as the value, or -1 if error
*/
int read_pin(uint32_t pin_num);

/*Determine bit start position of pin for GPSEL register
pin: The pin number

Returns:
Returns the ending index of the pins position
*/
inline int gpio_gpfsel_pos(unsigned int pin);

#endif //GPIO_H
