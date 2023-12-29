#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inet/buf.h"

bufpool::bufpool(int nbufs, int bufsize) {
    buf_t pool = (buf_t) malloc(nbufs * bufsize);
    memset(pool, 0, nbufs * bufsize);

    this->pool = pool;
    this->nbufs = nbufs;
    this->bufsize = bufsize;
    this->stack = NULL;

    // Setup the stack
    for (int i = 0; i < nbufs; i++)
        this->push((buf_t) (pool + (i * bufsize)));
}

int
bufpool::get_nbufs() {
    return this->nbufs;
}

int
bufpool::get_bufsize() {
    return this->bufsize;
}

buf_t
bufpool::pop() {
    if (this->stack == NULL)
        return NULL;

    buf_t buf = this->stack;
    this->stack = *((buf_t *) this->stack);
    return buf;
}

void
bufpool::push(buf_t buf) {
    if (buf == NULL)
        return;

    *((buf_t *) buf) = this->stack;
    this->stack = buf;
}

void
bufpool::dump() {
    for (buf_t buf = this->stack; buf != NULL;) {
        printf("%p\r\n", buf);
        buf = *((buf_t *) buf);
    }
}
