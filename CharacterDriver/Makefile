KERNEL_VERSION = $(shell uname -r)

obj-m += my_cdev.o

build: kernel_modules
kernel_modules:
	make -C /lib/modules/$(KERNEL_VERSION)/build M=$(CURDIR) modules
clean:
	make -C /lib/modules/$(KERNEL_VERSION)/build M=$(CURDIR) clean
