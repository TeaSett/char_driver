#include <linux/slab.h>
#include "my_device.h"

#define DRIVER_CLASS "my_driver_class"
enum {DEFAULT_SIZE = 1024};

extern struct my_device_t my_device;
extern size_t size;
extern void print_operation_info(const char *op);

int init_module() {
    int ret = 0;
	print_operation_info("initialization");

	/* Allocate a device nr */
	if(alloc_chrdev_region(&my_device.num, 0, 1, DRIVER_NAME) < 0) {
		printk(KERN_ERR "Device could not be allocated!\n");
		return -1;
	}
	printk(KERN_INFO DRIVER_NAME " - Major: %d, Minor: %d was registered!\n", MAJOR(my_device.num), MINOR(my_device.num));

	/* Create device class */
	if((my_device.class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk(KERN_ERR DRIVER_NAME ": device class can not be created!\n");
        ret = -1;
		goto exit;
	}

	/* Create device file */
	if(device_create(my_device.class, NULL, my_device.num, NULL, DRIVER_NAME) == NULL) {
		printk(KERN_ERR DRIVER_NAME ": can not create device file!\n");
        ret = -2;
		goto exit;
	}

	/* Initialize device file */
	cdev_init(&(my_device.dev), &(my_device.fops));
	if(cdev_add(&(my_device.dev), my_device.num, 1) == -1) {
		printk(KERN_ERR DRIVER_NAME ": registering of device to kernel failed!\n");
        ret = -3;
		goto exit;
	}

	if(size == 0) size = DEFAULT_SIZE;
	char *allocated;
	if(!(allocated = (char*)kmalloc(size, GFP_KERNEL))) {
		printk(KERN_ERR DRIVER_NAME ": buffer alocation is failed!\n");
		ret = -3;
		goto exit;
	}
	init_buffer(allocated);

    print_operation_info("initialization SUCCESS");

exit:
    switch(ret) {
    case -3: device_destroy(my_device.class, my_device.num);
    case -2: class_destroy(my_device.class);
    case -1: unregister_chrdev_region(my_device.num, 1);
    default:
        break;
    }

	return ret;
}