KERNEL_DRIVER=dev_gpio
USER_PROG=bulb

.PHONY: clean driver prog clean

all: driver prog

driver:
	make -C $(KERNEL_DRIVER)

prog:
	make -C $(USER_PROG)

clean:
	make -C $(KERNEL_DRIVER) clean
	make -C $(USER_PROG) clean
