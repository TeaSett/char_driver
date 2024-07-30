#include "my_device.h"

extern struct my_device_t my_device;

void cleanup_module() {
    cdev_del(&(my_device.dev));
	device_destroy(my_device.class, my_device.num);
	class_destroy(my_device.class);
	unregister_chrdev_region(my_device.num, 1);
	printk(DRIVER_NAME "REMOVED\n");
}