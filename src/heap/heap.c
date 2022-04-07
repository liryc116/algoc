#include "heap.h"

#include "../utils/xmalloc.h"

#include <stdlib.h>
#include <string.h>

struct heap *heap_new(int (*cmp_fun)(void *, void *))
{
    struct heap *h = malloc(sizeof(struct heap));

    h->size = 0;
    h->capacity = 2;
    h->data = xcalloc(2, sizeof(void *));
    h->cmp_fun = cmp_fun;

    return h;
}

void heap_free(struct heap *h, void (*free_function)(void*))
{
    for(size_t i = 0; i<h->size; i++)
        free_function(h->data[i]);

    free(h->data);
    free(h);
}

static void heap_double_capacity(struct heap *h)
{
    h->capacity *= 2;
    h->data=xreallocarray(h->data, h->capacity, sizeof(void *));
}
static void swap(void **data, size_t a, size_t b)
{
    void *tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}

static void sift_up(struct heap *h, size_t n)
{
    void *val = h->data[n];

    if(h->cmp_fun(val, h->data[n/2])>0)
    {
        swap(h->data, n, n/2);
        sift_up(h, n/2);
    }
}

static void sift_down(struct heap *h, size_t n)
{
    void *val = h->data[n];

    if(h->cmp_fun(val, h->data[2*n+1])<0 &&
            h->cmp_fun(h->data[2*n+1], h->data[2*n+2])>=0)
    {
        swap(h->data, n, 2*n+1);
        sift_down(h, 2*n+1);
    }
    else if(h->cmp_fun(val, h->data[2*n+2])<0)
    {
        swap(h->data, n, 2*n+2);
        sift_down(h, 2*n+2);
    }
}

void heap_insert(struct heap *h, void *data, size_t data_size)
{
    if(h->size==h->capacity)
        heap_double_capacity(h);

    h->data[h->size] = xmalloc(data_size);
    memcpy(h->data[h->size], data, data_size);
    sift_up(h, h->size);

    h->size += 1;
}

void *heap_peek(struct heap *h)
{
    if(h->size==0)
        return NULL;
    return h->data[0];
}

void *heap_pop(struct heap *h)
{
    if(h->size==0)
        return NULL;

    void *tmp = h->data[0];
    if(h->size>1)
    {
        h->data[0] = h->data[h->size-1];
        sift_down(h, 0);
    }

    h->size-=1;
    return tmp;
}

int heap_is_empty(struct heap *h)
{
    return h->size==0;
}
