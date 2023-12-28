#ifndef __BUF_H
#define __BUF_H

#include <stdint.h>

//
// Buffer pointer
//
typedef uint8_t *buf_t;

//
// Buffer pool
//
class bufpool {
private:
    buf_t pool;
    int nbufs;
    int bufsize;
    buf_t stack;

public:
    bufpool(int nbufs, int bufsize);
    int get_nbufs();
    int get_bufsize();
    buf_t pop();
    void push(buf_t buf);
    void dump();
};

typedef class bufpool *bufpool_t;

//
// Buffer queue
//
class bufq {
private:
    buf_t *q;     // Array of buffer ptrs
    int *len;     // Array of the current lengths of the buffers
    int entries;  // Number of entries in the buffer ptr array
    int bufsize;  // Size of each buffers allocated memory
    int h, t;     // Queue head and tail indices in buffer ptr array
    bool full;    // Full flag

public:
    bufq(int entries, int bufsize);
    int get_nbufs();
    int get_bufsize();
    int get_length();
    int append(buf_t buf, int len);
    buf_t remove(int *len);
    void dump();
    void dump_contents();
};

typedef class bufq *bufq_t;

#endif
