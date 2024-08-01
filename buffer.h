enum {size = 1024};
struct buffer {
    char data[size];
    char *start, *end;
    char *rstart, *wend;
    // char *pos;
};

void init_buffer(void);