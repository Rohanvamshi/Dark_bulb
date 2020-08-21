TARGET=dev_gpio
SRC=./src

obj-m +=$(SRC)/$(TARGET).o

.PHONY: clean

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
