TARGET=devgpio
MAIN=dev_gpio
GPIO=gpio
SRC=./src
obj-m += $(TARGET).o
$(TARGET)-objs := $(SRC)/$(GPIO).o $(SRC)/$(MAIN).o

ifndef CURR_KERNEL_DIR
	CURR_KERNEL_DIR=$(PWD)
endif

.PHONY: clean

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(CURR_KERNEL_DIR) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(CURR_KERNEL_DIR) clean
