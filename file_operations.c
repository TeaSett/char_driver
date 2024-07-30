#include "my_device.h"

int open_d(struct inode *inode, struct file *filp) {
    return 0;
}


int release_d(struct inode *inode, struct file *filp) {
    return 0;
}


ssize_t read_from_d(struct file *filp, char __user *ubuf, size_t len, loff_t *offset) {
    return 0;
}


ssize_t write_to_d(struct file *filp, const char __user *ubuf, size_t len, loff_t *offset) {
    return 0;
}