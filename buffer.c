#include "buffer.h"

extern struct buffer buffer;
extern unsigned long long size;

void init_buffer(char *allocated) {
    buffer.data = allocated;
    buffer.start = buffer.wend = buffer.rstart = buffer.data;
    buffer.end = buffer.data+size;
}