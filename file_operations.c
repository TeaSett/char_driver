#include <linux/wait.h>
#include "my_device.h"

extern struct my_device_t my_device;
extern struct buffer buffer;

static DECLARE_WAIT_QUEUE_HEAD(wait_queue_for_readers);
static DECLARE_WAIT_QUEUE_HEAD(wait_queue_for_writers);

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

    if(my_device.read_blocking) {
        wait_event_interruptible(wait_queue_for_readers, ((buffer.wend != buffer.start)||((buffer.wend == buffer.rstart)&&(buffer.wend != buffer.start))));
    }
    
    int to_copy = buffer.wend - buffer.rstart;
    if(to_copy == 0) buffer.wend = buffer.rstart = buffer.start;
    copy_to_user(ubuf, buffer.data, to_copy);
    buffer.rstart += to_copy;
    (*offset) += to_copy;
    wake_up_interruptible(&wait_queue_for_writers);

    return to_copy;
}


ssize_t write_to_d(struct file *filp, const char __user *ubuf, size_t len, loff_t *offset) {
    printk(KERN_INFO "WRITING to " DRIVER_NAME " %d\n", len);
    
    // if(my_device.write_blocking) {
    //     has_input = 1;
    //     wake_up_interruptible(&wait_queue_for_readers);
    //     wait_event_interruptible(wait_queue_for_writers, has_output_waiter != 0);
    //     has_output_waiter = 0;
    // }

    wait_event_interruptible(wait_queue_for_writers, (buffer.wend != buffer.end)||(buffer.rstart != buffer.start));
    if(buffer.rstart != buffer.start) buffer.wend = buffer.rstart = buffer.start;

    int to_copy = min(size, len);
    copy_from_user(buffer.data, ubuf, to_copy);
    buffer.wend += to_copy;
    (*offset) += to_copy;

    if(my_device.read_blocking) {
        wake_up_interruptible(&wait_queue_for_readers);
    }

    return to_copy;
}