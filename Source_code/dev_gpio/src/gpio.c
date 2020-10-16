#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include "../include/gpio.h"

/*
Internal implementations of device functions

pin_arg: The pin direction (0 for in, 1 for out) is in the first bit,
The pin number is represented as a value contained in bytes 8-15

Returns:
Returns 0 for success or -1 for error
*/
int change_pin_dir(uint32_t pin_num, uint32_t pin_dir){
	uint32_t mask_off = 0;
	uint32_t zero = 0;
	uint32_t first_bit = 1;
	uint32_t pin_mode_pos = 0;
	uint32_t gpio_base = 0;
	uint32_t * gpio_virt_mem = NULL;
	uint32_t pin_reg_val = 0;
	uint32_t end_idx = 0; // The ending idx for the bits that represent that particular pin in the register

	//Make sure that pin number is valid
	if(pin_num >= GPIO_PIN_COUNT){
		printk(KERN_ALERT "Pin number %u given is invalid", pin_num);
		return -EINVAL;
	}
	printk(KERN_INFO "Attempting to set mode %u to pin %u", pin_dir, pin_num);

	
	//Set base to approprieate select offset for GPFSEL
	if (IN_RANGE_GPFSEL0(pin_num)){
		gpio_base = (uint32_t) (GPIO_BASE + GPIO_GPFSEL0_OFFSET);

	}else if(IN_RANGE_GPFSEL1(pin_num)){
		gpio_base = (uint32_t) (GPIO_BASE + GPIO_GPFSEL1_OFFSET);

	}else{
		//This should never happen
		printk(KERN_ALERT "Pin number %u is out of the range for GPFSEL", pin_num);
		return -EINVAL;
	}

	printk(KERN_INFO "Successfully requested memory region %x, pin num %u",
	(unsigned int) gpio_base, pin_num);

	// Even though it is deprecated, since this is an out-of-tree module,
	// We are using ioremap to request virtual map of physical address
	// We understand that we need to check if the memory area is being used first but we
	// are skipping disabling the existing gpio driver
	gpio_virt_mem = (uint32_t *) ioremap(gpio_base, GPIO_REG_SIZE);
	if(gpio_virt_mem == NULL){
		printk(KERN_ALERT "Failed to map physical memory to kernel address space");
		return -EINVAL;
	}

	printk(KERN_INFO "Successfully mapped physical memory "
	  		"at %x to kernel address space", gpio_base);

	// Read the contents of the GPFSEL register mapped to virtual memory
	pin_reg_val = (uint32_t) readw(gpio_virt_mem);

	// Get the correct ending bit position to change
	end_idx = gpio_gpfsel_pos(pin_num);
	printk(KERN_INFO "GPIOSEL ending index: %u\n", end_idx);

	//Change bits at applicable positions and write out register
	mask_off = 0;
	if(pin_dir == GPIO_GPFSEL_IN){//GPIO pin in direction
		pin_reg_val = pin_reg_val & ~(1 << end_idx); //change 3rd bit
		end_idx--;
		pin_reg_val = pin_reg_val & ~(1 << end_idx); //change 2nd bit
		end_idx--;
		pin_reg_val = pin_reg_val & ~(1 << end_idx); //change 1st bit

	}else{ //GPIO pin out direction
		pin_reg_val = pin_reg_val & ~(1 << end_idx); //change 3rd bit
		end_idx--;
		pin_reg_val = pin_reg_val & ~(1 << end_idx); //change 2nd bit
		end_idx--;
		pin_reg_val = pin_reg_val | (1 << end_idx); //change 1st bit
	}

	//Write the value back to the register with the desired bits set/cleared
	writew(pin_reg_val, gpio_virt_mem);

	return 0;
}



/*Determine bit start position of pin for GPSEL register
pin: The pin number

Returns:
Returns the ending index of the pins position
*/
inline int gpio_gpfsel_pos(unsigned int x){
	unsigned int result = 0;
	if (IN_RANGE_GPFSEL0(x)){
		result = 2 + 3 * x;
	}else if(IN_RANGE_GPFSEL1(x)){
		result = 2 + 3 * (x - 10);
	}else if(IN_RANGE_GPFSEL2(x)){
		result = 2 + 3 * (x - 20);
	}else if(IN_RANGE_GPFSEL3(x)){
		result = 2 + 3 * (x - 30);
	}else if(IN_RANGE_GPFSEL4(x)){
		result = 2 + 3 * (x - 40);
	}else if(IN_RANGE_GPFSEL5(x)){
		result = 2 + 3 * (x - 50);
	}

	return result;
}