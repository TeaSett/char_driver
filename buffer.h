enum {size = 1024};
struct buffer {
    char data[size];
    char *start, *end;
    char *pos;
};

void init_buffer(struct buffer *buf);