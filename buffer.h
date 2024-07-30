struct buffer {
    static const int size = 1024;
    char data[size];
    char *const start = data, *const end = data+size;
    char *pos = data;
};