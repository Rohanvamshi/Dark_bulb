TARGET=dev_gpio
SRC=./src
obj-m +=$(SRC)/$(TARGET).o

ifndef CURR_KERNEL_DIR
	CURR_KERNEL_DIR=$(PWD)
endif

.PHONY: clean

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(CURR_KERNEL_DIR) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(CURR_KERNEL_DIR) clean
