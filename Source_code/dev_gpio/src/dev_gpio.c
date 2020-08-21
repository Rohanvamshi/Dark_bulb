#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bulbs");
MODULE_DESCRIPTION("gpio");
MODULE_VERSION("1.0");

#define DEVICE_NAME "gpio"
#define CLASS_NAME "gpio"
/*
Device class variables
*/
static struct class* gpio_class = NULL;
static struct device* gpio_device = NULL;


/*
Device functions
*/
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
		return -EBUSY;
	}

	device_open_count++;
	try_module_get(THIS_MODULE);
	return 0;
}

/*Called when device is closed*/
static int device_release(struct inode *inode, struct file *file){
	/*Update device reference counter*/
	device_open_count--;
	module_put(THIS_MODULE);
	return 0;
}

static int __init dev_gpio_init(void){
	printk(KERN_INFO "gpio\n");

	/*Register character device*/
	major_num = register_chrdev(0, DEVICE_NAME, &file_ops);
	if (major_num < 0){
		//Failed to regiser device
		printk(KERN_ALERT "Failed to register device %s major number.\n", DEVICE_NAME);
		return major_num;
	}
	printk(KERN_ALERT "%s device registered correctly with major \
		number %d\n",DEVICE_NAME, major_num );

	// Register device class with udev
	gpio_class = class_create(THIS_MODULE, CLASS_NAME);

	// Error creating device class
	if(IS_ERR(gpio_class)){
		unregister_chrdev(major_num, DEVICE_NAME);
		printk(KERN_ALERT "Failed to create device class %s\n", CLASS_NAME);
		return PTR_ERR(gpio_class);
	}

	printk(KERN_INFO "%s device class registered correctly\n", CLASS_NAME);

	// Register device driver
	gpio_device = device_create(gpio_class, NULL, MKDEV(major_num, 0),
			NULL, DEVICE_NAME);

	//Error creating device and registering device driver
	if(IS_ERR(gpio_device)){
		class_destroy(gpio_class); //clean up created device class
		unregister_chrdev(major_num, DEVICE_NAME);
		printk(KERN_ALERT "Failed to create device %s\n", DEVICE_NAME);
		return PTR_ERR(gpio_device);
	}
	printk(KERN_INFO "%s device created correctly\n", DEVICE_NAME);
	return 0;
}

static void __exit dev_gpio_exit(void){
	//Remove the device
	device_destroy(gpio_class, MKDEV(major_num, 0));
	//Unregister device class
	class_unregister(gpio_class);
	//Remove the device class
	class_destroy(gpio_class);
 	printk(KERN_INFO "Goodbye %s\n", DEVICE_NAME);
	unregister_chrdev(major_num, DEVICE_NAME);
	printk(KERN_INFO "Goodbye, %s\n", DEVICE_NAME);
}

module_init(dev_gpio_init);
module_exit(dev_gpio_exit);
