#ifndef GPIO_H
#define GPIO_H

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

//GPIO offset for GPFSEL0 pins 0 - 9
#define GPIO_GPFSEL0_OFFSET 0x00

//GPIO offset for GPFSEL1 pins  10 - 19
#define GPIO_GPFSEL1_OFFSET 0x04

//Checks if GPFSEL0 applies to x
#define IN_RANGE_GPFSEL0(x) (x <= 9 && x >= 0)

//Checks if GPFSEL1 applies to x
#define IN_RANGE_GPFSEL1(x) (x <= 19 && x >= 10)

//Determine bit start position of pin for GPFSEL register
#define GPIO_GPFSEL_POS(x, pos)  
	if (IN_RANGE_GPFSEL0(x)) 
		pos = (2 + x) + 3 * x;
	else if(IN_RANGE_GPFSEL1(x)) 
		pos = (2 + (x - 10)) + 3 * (x - 10)

//GPIO value for selecting input mode
#define GPIO_GPFSEL_IN 0x00

//GPIO value for selecting output mode
#define GPIO_GPFSEL_OUT 0x01

//GPIO PIN count
#define GPIO_PIN_COUNT 54

#endif //GPIO_H
