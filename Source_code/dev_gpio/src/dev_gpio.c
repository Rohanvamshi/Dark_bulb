#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include "../include/dev_gpio.h"		// IOCTL and other definitions here
#include "../include/gpio.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bulbs");
MODULE_DESCRIPTION("dev gpio");
MODULE_VERSION("1.0");

#define DEVICE_NAME "devgpio"
#define CLASS_NAME "devgpio"
/*
Device class variables
*/
static struct class* dev_gpio_class = NULL;
static struct device* dev_gpio_device = NULL;

/*
TODO: Move function to debug.c file
*/
void int_to_bin(uint32_t num){
	uint32_t ctr;
  for (ctr = 1 << 31; ctr > 0; ctr = ctr / 2){
    (num & ctr)? printk(KERN_INFO "1"): printk(KERN_INFO "0");
  }
  printk("\n");
}

static int major_num = 0;
static int device_open_count = 0;

/*
Pointer to device functions
*/
static struct file_operations file_ops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.unlocked_ioctl = devgpio_ioctl
	};


/*
Internal implementations of device functions

pin_arg: The pin direction (0 for in, 1 for out) is in the first bit,
The pin number is represented as a value contained in bytes 8-15

Returns:
Returns 0 for success or -1 for error
*/
int _ioctl_change_pin_dir(unsigned int pin_arg){
	uint32_t first_bit = 1;
	uint32_t pin_num = (pin_arg >> 8);
	uint32_t pin_dir = pin_arg & first_bit; // The direction of the pin (0/1) (in/out)
	printk(KERN_INFO "Pin input for changing direction: %u", pin_arg);
	return change_pin_dir(pin_num, pin_dir);
}

/*
Internal implementations of device functions

pin_num: The pin value to write to is in the first bit,
The pin number is represented as a value contained in bytes 8-15

Returns:
Returns 0 for success or -1 for error
*/
int _ioctl_write_pin(uint32_t pin_arg){
	uint32_t mask_off = 0;
	uint32_t pin_val = (pin_arg & (mask_off+1));
	uint32_t pin_num = (pin_arg >> 8);
	printk(KERN_INFO "Pin input for writing:  %u", pin_arg);

	return write_to_pin(pin_num, pin_val);
}

/*
Reads from the specified ioctl pin.
Assumes that the pin number is the physical pin number on the board
in the pinout diagram.

pin_num: The pin number to read from

Returns:
	0 or 1 as the value, or -1 if error
*/
int _ioctl_read_pin(unsigned int pin_num){

	return read_pin(pin_num);
}

static ssize_t device_read(struct file *flip, char *buffer, size_t len, loff_t *offset){
	return 0;
}

static ssize_t device_write(struct file *flip, const char *buffer, size_t len, loff_t *offset){
	return 0;
}

static int device_open(struct inode *inode, struct file *file){
	//Check if device is already open
	if(device_open_count){
		printk(KERN_ALERT "device is open by %d devices \n", device_open_count);
	}
	else
	{
	printk(KERN_INFO "GPIO device open by you first \n");
	}
	device_open_count++;
	printk(KERN_INFO "device count = %d \n" , device_open_count);
	try_module_get(THIS_MODULE);
	return 0;

}

/*Called when device is closed*/
static int device_release(struct inode *inode, struct file *file){
	/*Update device reference counter*/
	device_open_count--;
	module_put(THIS_MODULE);
	printk(KERN_INFO"GPIO device released \n");
	printk(KERN_INFO "device count = %d \n" , device_open_count);
	return 0;
}

static int __init dev_gpio_init(void){
	printk(KERN_INFO "%s\n", DEVICE_NAME);

	/*Register character device*/
	major_num = register_chrdev(0, DEVICE_NAME, &file_ops);
	if (major_num < 0){
		//Failed to regiser device
		printk(KERN_ALERT "Failed to register device %s major number.\n", DEVICE_NAME);
		return major_num;
	}
	printk(KERN_INFO "%s device registered correctly with major \
		number %d\n",DEVICE_NAME, major_num );

	// Register device class with udev
	dev_gpio_class = class_create(THIS_MODULE, CLASS_NAME);

	// Error creating device class
	if(IS_ERR(dev_gpio_class)){
		unregister_chrdev(major_num, DEVICE_NAME);
		printk(KERN_ALERT "Failed to create device class %s\n", CLASS_NAME);
		return PTR_ERR(dev_gpio_class);
	}

	printk(KERN_INFO "%s device class registered correctly\n", CLASS_NAME);

	// Register device driver
	dev_gpio_device = device_create(dev_gpio_class, NULL, MKDEV(major_num, 0),
			NULL, DEVICE_NAME);

	//Error creating device and registering device driver
	if(IS_ERR(dev_gpio_device)){
		class_destroy(dev_gpio_class); //clean up created device class
		unregister_chrdev(major_num, DEVICE_NAME);
		printk(KERN_ALERT "Failed to create device %s\n", DEVICE_NAME);
		return PTR_ERR(dev_gpio_device);
	}
	printk(KERN_INFO "%s device created correctly\n", DEVICE_NAME);
	return 0;
}

static void __exit dev_gpio_exit(void){
	//Remove the device
	device_destroy(dev_gpio_class, MKDEV(major_num, 0));
	//Unregister device class
	class_unregister(dev_gpio_class);
	//Remove the device class
	class_destroy(dev_gpio_class);
 	printk(KERN_INFO "Goodbye %s\n", DEVICE_NAME);
	unregister_chrdev(major_num, DEVICE_NAME);
	printk(KERN_INFO "Goodbye, %s\n", DEVICE_NAME);
}
// IOCTL funciton implimentation

long devgpio_ioctl (struct file *filp,
                   unsigned int cmd, unsigned long arg)
{

	int return_val = 0;
	int err = 0;
	uint32_t val = 0;
	
	// Invalid command type
	if (_IOC_TYPE(cmd) != DEV_GPIO_IOC_MAGIC){
		return -ENOTTY;
	}
	//Checking if the user memory pointer specified can be written by the driver.
	if (_IOC_DIR(cmd) & _IOC_READ){
		err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));
	}else if (_IOC_DIR(cmd) & _IOC_WRITE){
		err =  !access_ok((void __user *)arg, _IOC_SIZE(cmd));
	}
	if (err){
		return -EFAULT;
	}


	//Implementation of supported dev_gpio commands
	switch(cmd) {
		case DEV_GPIO_IOC_RESET:
			break;

		case DEV_GPIO_IOC_READ:
			printk(KERN_INFO "Performing ioctl read");
			val = *((unsigned long *)arg);
			return_val = _ioctl_read_pin(val);
			break;

		case DEV_GPIO_IOC_WRITE:
			printk(KERN_INFO "Performing ioctl write");
			val = (uint32_t) *((unsigned long*) arg);
			return_val = _ioctl_write_pin(val);
			break;

		case DEV_GPIO_IOC_CHANGEDIR:
			printk(KERN_INFO "Performing ioctl change pin dir");
			val = (uint32_t) *((unsigned long*) arg);
			return_val = _ioctl_change_pin_dir(val);
			break;

		default:
		return -ENOTTY;
	}
	return return_val;
}
module_init(dev_gpio_init);
module_exit(dev_gpio_exit);
