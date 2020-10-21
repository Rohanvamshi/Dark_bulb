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
	uint32_t first_bit = 1;
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

	}else if(IN_RANGE_GPFSEL2(pin_num)){
		gpio_base = (uint32_t) (GPIO_BASE + GPIO_GPFSEL2_OFFSET);

	}else if(IN_RANGE_GPFSEL3(pin_num)){
		gpio_base = (uint32_t) (GPIO_BASE + GPIO_GPFSEL3_OFFSET);

	}else if(IN_RANGE_GPFSEL4(pin_num)){
		gpio_base = (uint32_t) (GPIO_BASE + GPIO_GPFSEL4_OFFSET);

	}else if(IN_RANGE_GPFSEL5(pin_num)){
		gpio_base = (uint32_t) (GPIO_BASE + GPIO_GPFSEL5_OFFSET);
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
	if(pin_dir == GPIO_GPFSEL_IN){//GPIO pin in direction
		pin_reg_val = pin_reg_val & ~(first_bit << end_idx); //change 3rd bit
		end_idx--;
		pin_reg_val = pin_reg_val & ~(first_bit << end_idx); //change 2nd bit
		end_idx--;
		pin_reg_val = pin_reg_val & ~(first_bit << end_idx); //change 1st bit

	}else{ //GPIO pin out direction
		pin_reg_val = pin_reg_val & ~(first_bit << end_idx); //change 3rd bit
		end_idx--;
		pin_reg_val = pin_reg_val & ~(first_bit << end_idx); //change 2nd bit
		end_idx--;
		pin_reg_val = pin_reg_val | (first_bit << end_idx); //change 1st bit
	}

	//Write the value back to the register with the desired bits set/cleared
	writew(pin_reg_val, gpio_virt_mem);

	//Unmap Memory
	iounmap(gpio_virt_mem);

	return 0;
}


/*
Internal implementations of device functions

pin_num: The pin value to write to is in the first bit,
pin_val: The value to write to the pin (0 or 1)

Returns:
Returns 0 for success or -1 for error
*/
int write_to_pin(uint32_t pin_num, uint32_t pin_val){
	uint32_t zero = 0;
	uint32_t first_bit = 1;
	uint32_t pin_write = 0;
	uint32_t gpio_base = 0;
	uint32_t * gpio_virt_mem = NULL;
	uint32_t pin_reg_val = 0;
	uint32_t pin_curr_val = 0;

	//Make sure that pin number is valid
	if(pin_num >= GPIO_PIN_COUNT){
		printk(KERN_ALERT "Pin number %u given is invalid", pin_num);
		return -EINVAL;
	}
	printk(KERN_INFO "Attempting to write value %u to pin %u", pin_val, pin_num);

	
	//Check if GPCLR is to be chosen
	if (pin_val == 0){
		gpio_base = (uint32_t) (GPIO_BASE + GPIO_GPCLR_OFFSET);
		pin_val = 1;

	//Check if GPSET is to be chosen
	}else if (pin_val == 1){
		gpio_base = (uint32_t) (GPIO_BASE + GPIO_GPSET_OFFSET);
	}

	//Check if pin is part of first or second set of pin level registers
	if(pin_num >= 32){
		// Use the second register for the pin count
		gpio_base += (uint32_t) GPIO_REG_SIZE;
		//Adjust pin number to match bit position
		pin_num = pin_num % 32;
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

    //Read word containing pin state
	pin_reg_val = (uint32_t) readw(gpio_virt_mem);

	//Calculate current state of pin, need to shift if pin number is not 0
	if(pin_num != 0){
		pin_curr_val = (pin_reg_val >> (pin_num - 1)) ^ zero;
	}

	printk(KERN_INFO "Current state of pin %u is %u", pin_num, pin_curr_val);

	//Set position to write to
	pin_write = (first_bit << pin_num);

	//Set bit in read value
	pin_write = pin_reg_val | pin_write;

	//Write the value back to the register with the desired bit set/cleared
	writew(pin_write, gpio_virt_mem);

	printk(KERN_INFO "Wrote the value %u to pin %u\n", pin_val, pin_num);

	//Unmap Memory
	iounmap(gpio_virt_mem);

	return 0;
}

/*
Reads from the specified ioctl pin.
Assumes that the pin number is the physical pin number on the board
in the pinout diagram.

pin_num: The pin number to read from

Returns:
	0 or 1 as the value, or -1 if error
*/
int read_pin(uint32_t pin_num){
	uint32_t gpio_gplev_base = (uint32_t) (GPIO_BASE + GPIO_GPLEV_OFFSET);
	uint32_t * gpio_virt_mem = NULL;
	int pin_state = 0;
	uint32_t pin_reg_val = 0;

	//Make sure that pin number is valid
	if(pin_num >= GPIO_PIN_COUNT){
		printk(KERN_ALERT "Pin number %u given is invalid", pin_num);
		return -EINVAL;
	}

	//Check if pin is part of first or second set of pin level registers
	if(pin_num >= 32){
		// Use the second register for the pin count
		gpio_gplev_base += (uint32_t) GPIO_REG_SIZE;
		//Adjust pin number to match bit position
		pin_num = pin_num % 32;
	}

	//For now, to avoid having to disable buit-in gpio, do not request mem region
	//I know this is bad practice
	//Request memory region using request_mem_region
	/*if(request_mem_region(gpio_gplev_base, GPIO_REG_SIZE, DEVICE_NAME) == NULL){
		printk(KERN_ALERT "Memory region %x is already requested by another process",
			(unsigned int) gpio_gplev_base);
		return -EBUSY;
	}*/


	printk(KERN_INFO "Successfully requested memory region %x, pin num %u",
		(unsigned int) gpio_gplev_base, pin_num);

	//Even though it is deprecated, since this is an out-of-tree module,
	// We are using ioremap to request virtual map of physical address
	gpio_virt_mem = (uint32_t *) ioremap(gpio_gplev_base, GPIO_REG_SIZE);
	if(gpio_virt_mem == NULL){
		printk(KERN_ALERT "Failed to map physical memory to kernel address space");
		return -EINVAL;
	}

	printk(KERN_INFO "Successfully mapped physical memory "
	  		"at %x to kernel address space", gpio_gplev_base);

  //Read byte containing pin state
    pin_reg_val = (uint32_t) readw(gpio_virt_mem);

	//Get correct bit position value
	pin_state = (pin_reg_val & (1 << pin_num));

	//Covert value at bit position to 0 or 1
	pin_state = (pin_state >> pin_num);

	printk(KERN_INFO "Pin state read is %d", pin_state);

	//Release memory region using release_mem_region
	/*release_mem_region(gpio_gplev_base, GPIO_REG_SIZE);
	printk(KERN_INFO "Successfully released memory region %x",
		(unsigned int) gpio_gplev_base);
*/

	//Unmap Memory
	iounmap(gpio_virt_mem);

	//return result
	return pin_state;
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