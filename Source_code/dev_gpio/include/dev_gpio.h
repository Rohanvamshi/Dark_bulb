#ifndef DEV_GPIO_H
#define DEV_GPIO_H

// define IOC commands
#define DEV_GPIO_IOC_MAGIC  'K'
#define DEV_GPIO_IOC_RESET    _IO(DEV_GPIO_IOC_MAGIC, 0)
#define DEV_GPIO_IOC_READ     _IOR(DEV_GPIO_IOC_MAGIC, 1, int)

#endif // End of DEV_GPIO_H
