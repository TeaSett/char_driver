#include "my_device.h"

MODULE_DESCRIPTION("Linux character driver with ring-buffer");
MODULE_LICENSE("GPL v2");

extern int open_d(struct inode *inode, struct file *filp);
extern int release_d(struct inode *inode, struct file *filp);
extern ssize_t read_from_d(struct file *filp, char __user *ubuf, size_t len, loff_t *offset);
extern ssize_t write_to_d(struct file *filp, const char __user *ubuf, size_t len, loff_t *offset);

extern long ioctl_handler(struct file *file, unsigned int cmd, unsigned long arg);

struct buffer buffer;
MODULE_PARM_DESC(size, "Parameter used to set char driver buffer size");
module_param(bufsize, ulong, S_IRUGO);
size_t size;

struct my_device_t my_device = {
    .fops = {
        .owner = THIS_MODULE,
        .open = open_d,
        .release = release_d,
        .read = read_from_d,
        .write = write_to_d,
        .unlocked_ioctl = ioctl_handler
    },

    .write_blocking = true,
    .read_blocking = true
};