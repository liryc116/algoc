#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

struct heap
{
    size_t capacity;
    size_t size;
    void **data;
    int (*cmp_fun)(void *, void *); // for max heap:
                                    // <0 when 1st<2nd, ==0 when 1st==2nd,
                                    // >0 when 1st>2nd
};

struct heap *heap_new(int (*cmp_fun)(void *, void *));

void heap_free(struct heap *h, void (*free_function)(void*));

void heap_insert(struct heap *h, void *data, size_t data_size);

void *heap_peek(struct heap *h);

void *heap_pop(struct heap *h);

int heap_is_empty(struct heap *h);

#endif /* ! HEAP_H */
