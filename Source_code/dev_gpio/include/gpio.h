#ifndef GPIO_H
#define GPIO_H

// GPIO Physical base address
#define GPIO_BASE 0x3f200000

// GPIO offset for GPLEV (read state) registers
#define GPIO_GPLEV_OFFSET 0x34

//GPIO register size
#define GPIO_REG_SIZE 0x4

//GPIO PIN count
#define GPIO_PIN_COUNT 54

#endif //GPIO_H
