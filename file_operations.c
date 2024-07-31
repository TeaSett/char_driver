#include <linux/wait.h>
#include "my_device.h"

extern struct my_device_t my_device;

static DECLARE_WAIT_QUEUE_HEAD(wait_queue_readers);
static int has_input = 0

int open_d(struct inode *inode, struct file *filp) {
    printk(KERN_INFO DRIVER_NAME " OPENED!\n");
    return 0;
}


int release_d(struct inode *inode, struct file *filp) {
    printk(KERN_INFO DRIVER_NAME " CLOSED!\n");
    return 0;
}


ssize_t read_from_d(struct file *filp, char __user *ubuf, size_t len, loff_t *offset) {
    printk(KERN_INFO "READING from " DRIVER_NAME "\n");

    wait_event_interruptible(wait_queue_for_readers, has_input);
    has_input = 0;

    // int to_copy = my_device.buf.pos - my_device.buf.start;
    // copy_to_user(ubuf, my_device.buf.data, to_copy);
    // my_device.buf.pos = my_device.buf.start;
    // (*offset) += to_copy;

    return to_copy;
}


ssize_t write_to_d(struct file *filp, const char __user *ubuf, size_t len, loff_t *offset) {
    printk(KERN_INFO "WRITING to " DRIVER_NAME "\n");
    
    has_input = 1;
    wake_up_interruptible(&wait_queue_for_readers);

    // copy_from_user(my_device.buf.data, ubuf, len);
    // my_device.buf.pos += len;
    // (*offset) += len;

    return len;
}