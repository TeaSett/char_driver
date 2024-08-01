#include "my_device.h"
#include "my_char_driver_ioctl_calls.h"

extern struct my_device_t my_device;
extern size_t size;


long ioctl_handler(struct file *file, unsigned int cmd, unsigned long arg) 
{
    if (_IOC_TYPE(cmd) != MCD_IOCTL_NUM) return -EINVAL;
    printk(KERN_INFO DRIVER_NAME " ioctl called. cmd = %d\n", cmd);


    switch(cmd) {
        case MCD_INPUT_AND_OUTPUT_BLOCK: {
            my_device.write_blocking = true;
            my_device.read_blocking = true;
            break;
        }
        case MCD_INPUT_AND_OUTPUT_NONBLOCK: {
            my_device.write_blocking = false;
            my_device.read_blocking = false;
            break;
        }
        case MCD_INPUT_BLOCK: {
            my_device.write_blocking = true;
            break;
        }
        case MCD_INPUT_NONBLOCK: {
            my_device.write_blocking = false;
            break;
        }
        case MCD_OUTPUT_BLOCK: {
            my_device.read_blocking = true;
            break;
        }
        case MCD_OUTPUT_NONBLOCK: {
            my_device.read_blocking = false;
            break;
        }
        case MCD_GET_BUF_SIZE: {
            return size;
        }
        // case MCD_GET_LAST_FILE_OPERATION_INFO: {
        //     ;
        // }

        default:
            return -ENOTTY;
    }


    return 0;
}