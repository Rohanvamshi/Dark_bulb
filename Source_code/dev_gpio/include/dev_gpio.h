#ifndef DEV_GPIO_H
#define DEV_GPIO_H

// Define error
#define GENERIC_ERROR -1

// Define IOC commands
#define DEV_GPIO_IOC_MAGIC  'Z'
#define DEV_GPIO_IOC_RESET  _IO(DEV_GPIO_IOC_MAGIC, 0)
#define DEV_GPIO_IOC_READ   _IOR(DEV_GPIO_IOC_MAGIC, 1, unsigned long *)
#define DEV_GPIO_IOC_WRITE   _IOR(DEV_GPIO_IOC_MAGIC, 2, unsigned long *)

/*
Internal implementations of device functions

pin_num: The pin number to read from

Returns:
Returns 0 for pin off, 1 for pin on, or -1 for error
*/
int _ioctl_read_pin(unsigned int pin_num);

/*
Internal implementations of device functions

pin_num: The pin value to write to is in the first bit,
The pin number is represented as a value contained in bytes 8-15

Returns:
Returns 0 for success or -1 for error
*/
int _ioctl_write_pin(unsigned int pin_arg);

long devgpio_ioctl (struct file *,unsigned int, unsigned long);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#endif //DEV_GPIO_H
