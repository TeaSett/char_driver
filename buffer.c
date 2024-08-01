#include "buffer.h"

struct buffer buffer;

void init_buffer(void) {
    buffer.start = buffer.wend = buffer.rstart = buffer.data;
    buffer.end = buffer.data+size;
    // buffer.pos = buffer.data;
}