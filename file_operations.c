#include <linux/wait.h>
#include "my_device.h"

extern struct my_device_t my_device;
extern struct buffer buffer;
extern size_t size;
extern void print_operation_info(const char *op);


int open_d(struct inode *inode, struct file *filp) {
    print_operation_info("OPENED");
    return 0;
}


int release_d(struct inode *inode, struct file *filp) {
    print_operation_info("CLOSED");
    return 0;
}


static DECLARE_WAIT_QUEUE_HEAD(wait_queue_for_readers);
static DECLARE_WAIT_QUEUE_HEAD(wait_queue_for_writers);
static bool someone_waits_for_output = false;

//TODO: check 'len' value
ssize_t read_from_d(struct file *filp, char __user *ubuf, size_t len, loff_t *offset) {
    print_operation_info("START READING");

    if (my_device.write_blocking) {
        someone_waits_for_output = true;
        wake_up_interruptible(&wait_queue_for_writers);
    }

    if (my_device.read_blocking) {
        wait_event_interruptible(wait_queue_for_readers, ((buffer.wend != buffer.start)||((buffer.wend == buffer.rstart)&&(buffer.wend != buffer.start))));
    }
    
    int to_copy = buffer.wend - buffer.rstart;
    if (to_copy == 0) {
        buffer.wend = buffer.rstart = buffer.start;
    }

    if (copy_to_user(ubuf, buffer.data, to_copy) != 0) {
        return -EFAULT;
    }

    buffer.rstart += to_copy;
    (*offset) += to_copy;
    wake_up_interruptible(&wait_queue_for_writers);

    if (my_device.write_blocking) {
        someone_waits_for_output = false;
    }

    print_operation_info("STOP READING");

    return to_copy;
}


ssize_t write_to_d(struct file *filp, const char __user *ubuf, size_t len, loff_t *offset) {
    print_operation_info("START WRITING");

    wait_event_interruptible(wait_queue_for_writers, (buffer.wend != buffer.end)||(buffer.rstart != buffer.start));

    if (buffer.rstart != buffer.start) {
        buffer.wend = buffer.rstart = buffer.start;
    }

    if (my_device.write_blocking) {
        wait_event_interruptible(wait_queue_for_writers, someone_waits_for_output);
    }

    int to_copy = min(size, len);

    if (copy_from_user(buffer.data, ubuf, to_copy) != 0) {
        return -EFAULT;
    }

    buffer.wend += to_copy;
    (*offset) += to_copy;

    if(my_device.read_blocking) {
        wake_up_interruptible(&wait_queue_for_readers);
    }

    print_operation_info("STOP WRITING");

    return to_copy;
}