obj-m += my_char_driver.o
my_char_driver-objs := my_device_instance.o init.o exit.o file_operations.o buffer.o ioctl_handler.o print_operation_info.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean