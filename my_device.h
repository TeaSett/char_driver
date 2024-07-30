#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/cdev.h>

#pragma once

#define DRIVER_NAME "my_char_driver"

struct my_device_t {
    struct file_operations fops;
    struct cdev dev;
    dev_t num;
    struct class *class;
};