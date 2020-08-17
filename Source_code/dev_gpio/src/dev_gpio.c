#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Example");
MODULE_DESCRIPTION("gpio");
MODULE_VERSION("0.01");

#define DEVICE_NAME "gpio"

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
		printk(KERN_ALERT "Failed to register device %d.\n", major_num);
	} else {
		return 0;
	}
	return 0;
}

static void __exit dev_gpio_exit(void){
	printk(KERN_INFO "Goodbye My kernel\n");
	unregister_chrdev(major_num, DEVICE_NAME);
	printk(KERN_INFO "Goodbye, World!\n");
}

module_init(dev_gpio_init);
module_exit(dev_gpio_exit);
