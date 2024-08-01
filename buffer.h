struct buffer {
    char *data;
    char *start, *end;
    char *rstart, *wend;
};

void init_buffer(char *allocated);