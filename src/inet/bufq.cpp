#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inet/buf.h"

//
// A bufq is a First-In-First-Out (FIFO) queue of buf_t pointers. The
// data structure works with buf_t pointers, it does not touch the data
// in the buffers
//

bufq::bufq(int entries, int bufsize) {
#if 0
    int size = entries * sizeof(void *);
#endif
    this->q = NULL;
#if 0
    this->q = (buf_t *) malloc(size);
    memset(this->q, 0, size);
#endif
    this->len = NULL;
#if 0
    size = entries * sizeof(int);
    this->len = (int *) malloc(size);
    memset(this->len, 0, size);
#endif
    this->entries = entries;
    this->bufsize = bufsize;
    this->h = 0;
    this->t = 0;
    this->full = false;
}

//
// Determine number of buffers in the queue
//
int
bufq::get_nbufs() {
    int h, n;

    if (this->full) {
        int entries = this->entries;
        return entries;
    }
    for (n = 0, h = this->h; h != this->t; n++, h = (h + 1) % this->entries)
        ;

    return n;
}

int
bufq::get_bufsize() {
    int bufsize = this->bufsize;
    return bufsize;
}

//
// Determine the sum of the lengths of the buffers in the queue
//
int
bufq::get_length() {
    int h, len;

    if (this->full) {
        int entries = this->entries;
        return entries;
    }

    for (len = 0, h = this->h; h != this->t;
         len += this->len[h], h = (h + 1) % this->entries)
        ;

    return len;
}

//
// Append a buf_t pointer to the tail of the queue
//
int
bufq::append(buf_t buf, int len) {
    if (buf == NULL || this->full)
        return (-1);

    this->q[t] = buf;
    this->len[t] = len;
    this->t = (this->t + 1) % this->entries;
    if (this->t == this->h)
        this->full = true;

    return 0;
}

//
// Remove a buf_t pointer from the head of the queue
//
buf_t
bufq::remove(int *len) {
    if (!(this->full) && this->h == this->t) {
        *len = 0;
        return NULL;
    }
    buf_t buf = this->q[this->h];
    *len = this->len[this->h];
    this->h = (this->h + 1) % this->entries;
    if (this->full)
        this->full = false;

    return buf;
}

void
bufq::dump() {
    if (!(this->full) && this->h == this->t) {
        return;
    }
    printf("<");
    for (int i = this->h;;) {
        printf("%d", this->len[i]);

        i = (i + 1) % this->entries;
        if (i == this->t)
            break;

        printf(",");
    }
    printf(">");
}

void
bufq::dump_contents() {
    if (!(this->full) && this->h == this->t)
        return;

    for (int i = this->h;;) {
        printf("[");

        for (int j = 0; j < this->len[i]; j++) {
            char ch = *(this->q[i] + j);
            if (isprint(ch)) {
                printf("%c", ch);
            } else {
                printf(".");
            }
        }
        printf("]\r\n");

        i = (i + 1) % this->entries;
        if (i == this->t)
            break;
    }
}
