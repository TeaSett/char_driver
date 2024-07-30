#include "buffer.h"

void init_buffer(struct buffer *buf) {
    buf->start = buf->data;
    buf->end = buf->data;
    buf->pos = buf->data;
}