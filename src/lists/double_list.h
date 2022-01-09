#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <stddef.h>

// Doubly linked lists
struct d_list{
    size_t len;
    struct list_elm *head, *tail;
};

struct list_elm{
    void *data;
    struct list_elm *next,*prev;
};

#include "d_list_insert.h"
#include "d_list_remove.h"

struct d_list* d_list_new(void);

size_t d_list_len(struct d_list *l);

int d_list_is_empty(struct d_list *l);

void d_list_free(struct d_list *l, void(*free_function)(void*));

#endif /* ! DOUBLE_LIST_H */
