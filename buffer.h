enum {size = 5};
struct buffer {
    char data[size];
    char *start, *end;
    char *rstart, *wend;
    // char *pos;
};

void init_buffer(void);