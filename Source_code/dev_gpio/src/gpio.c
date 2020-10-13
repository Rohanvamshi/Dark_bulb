#include "../include/gpio.h"

inline int gpio_gpfsel_pos(unsigned int x){
	unsigned int result = 0;
	if (IN_RANGE_GPFSEL0(x)){
		result = (2 + x) + 3 * x;
	}else if(IN_RANGE_GPFSEL1(x)){
		result = (2 + (x - 10)) + 3 * (x - 10);
	}

	return result;
}