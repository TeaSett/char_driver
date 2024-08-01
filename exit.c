#include <linux/slab.h>
#include "my_device.h"

extern struct my_device_t my_device;
extern struct buffer buffer;

void cleanup_module() {
	kfree(buffer.data);
    cdev_del(&(my_device.dev));
	device_destroy(my_device.class, my_device.num);
	class_destroy(my_device.class);
	unregister_chrdev_region(my_device.num, 1);
	printk(KERN_INFO DRIVER_NAME " REMOVED\n");
}