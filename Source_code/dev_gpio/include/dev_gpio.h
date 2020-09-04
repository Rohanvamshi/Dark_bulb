#ifndef DEV_GPIO_H
#define DEV_GPIO_H

// Define error
#define GENERIC_ERROR -1

// Define IOC commands
#define DEV_GPIO_IOC_MAGIC  'K'
#define DEV_GPIO_IOC_RESET  _IO(DEV_GPIO_IOC_MAGIC, 0)
#define DEV_GPIO_IOC_READ   _IOR(DEV_GPIO_IOC_MAGIC, 1, unsigned int)

#endif //DEV_GPIO_H
