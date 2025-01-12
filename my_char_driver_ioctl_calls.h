#include <linux/ioctl.h>


#define MCD_IOCTL_NUM 0x12

#define MCD_INPUT_BLOCK 				_IO(MCD_IOCTL_NUM, 1)
#define MCD_INPUT_NONBLOCK              _IO(MCD_IOCTL_NUM, 2)
#define MCD_OUTPUT_BLOCK                _IO(MCD_IOCTL_NUM, 3)
#define MCD_OUTPUT_NONBLOCK             _IO(MCD_IOCTL_NUM, 4)
#define MCD_INPUT_AND_OUTPUT_BLOCK      _IO(MCD_IOCTL_NUM, 5)
#define MCD_INPUT_AND_OUTPUT_NONBLOCK   _IO(MCD_IOCTL_NUM, 6)
#define MCD_GET_BUF_SIZE 	            _IOR(MCD_IOCTL_NUM, 7, unsigned long long)