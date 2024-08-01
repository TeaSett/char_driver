#include <linux/cred.h>
#include <linux/timekeeping.h>
#include "my_device.h"

void print_operation_info(const char *op) {
    struct 	timespec64 last_op_time;
    ktime_get_ts64(&last_op_time);
    const struct cred *cred = current_cred();

    printk(KERN_INFO DRIVER_NAME ": %s\nUID: %d; PID: %d; last_time: %d", op, cred->uid.val, current->pid, last_op_time);
}