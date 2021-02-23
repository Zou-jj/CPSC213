#ifndef _IMPLICIT_H_
#define _IMPLICIT_H_

#include <stdint.h>
#include <stdalign.h>

#define HEADER_SIZE (sizeof(int)) // same as footer size

/*
 * Struct used to represent the heap.
 */
struct heap {
    int size;                /* Size of the heap in bytes. */
    void *start;             /* Start address of the heap area. */
};

/*
 * Create a heap that is "size" bytes large.
 */
struct heap *heap_create(unsigned int size);

/*
 * Free a block on the heap h.
 */
void myfree(struct heap *h, void *payload);

/*
 * Our implementation of malloc.
 */
void *mymalloc(struct heap *h, unsigned int size);

#endif
