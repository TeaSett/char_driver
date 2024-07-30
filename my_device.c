#include "my_device.h"

MODULE_DESCRIPTION("Character driver with ring-buffer");
MODULE_LICENSE("GPL v2");

extern int open_d(struct inode *inode, struct file *filp);
extern int release_d(struct inode *inode, struct file *filp);
extern int read_from_d(struct file *filp, char __user *ubuf, size_t len, loff_t *offset);
extern int write_to_d(struct file *filp, const char __user *ubuf, size_t len, loff_t *offset);

struct my_device_t my_device = {
    .fops = {
        .owner = THIS_MODULE,
        .open = open_d,
        .release = release_d,
        .read = read_from_d,
        .write = write_to_d
    }
};