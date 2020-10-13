TARGET=dev_gpio
GPIO=gpio
SRC=./src
obj-m+=$(SRC)/$(TARGET).o 
dev_gpio-objs+=$(SRC)/$(GPIO).o

ifndef CURR_KERNEL_DIR
	CURR_KERNEL_DIR=$(PWD)
endif

.PHONY: clean

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(CURR_KERNEL_DIR) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(CURR_KERNEL_DIR) clean
