#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include "../include/dev_gpio.h"												// IOCTL and other definitions here


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bulbs");
MODULE_DESCRIPTION("dev gpio");
MODULE_VERSION("1.0");

#define DEVICE_NAME "dev_gpio"
#define CLASS_NAME "dev_gpio"
/*
Device class variables
*/
static struct class* dev_gpio_class = NULL;
static struct device* dev_gpio_device = NULL;


/*
Device functions
*/
long devgpio_ioctl (struct file *,unsigned int, unsigned long);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static int major_num = 0;
static int device_open_count = 0;

/*
Pointer to device functions
*/
static struct file_operations file_ops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
	};

static ssize_t device_read(struct file *flip, char *buffer, size_t len, loff_t *offset){
	return 0;
}

static ssize_t device_write(struct file *flip, const char *buffer, size_t len, loff_t *offset){
	return 0;
}

static int device_open(struct inode *inode, struct file *file){
	//Check if device is already open
	if(device_open_count){
		
		printk(KERN_ALERT"device is open by %d devices \n", device_open_count);
	
	}
	else
	{
	printk(KERN_INFO"GPIO device open by you first \n");
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

	int err = 0;
	if (_IOC_TYPE(cmd) != DEV_GPIO_IOC_MAGIC) return -ENOTTY;
	
	// checking if the memory pointer specified can be written by the driver.
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err)
		return -EFAULT;
		
		
	switch(cmd) {
		
		default:
		return -ENOTTY;
	}
	
	
}	
module_init(dev_gpio_init);
module_exit(dev_gpio_exit);
