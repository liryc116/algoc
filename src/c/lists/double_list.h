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

struct d_list* d_list_new(void);

size_t d_list_len(struct d_list *l);

void d_list_push_front(struct d_list *l, void *data);

void d_list_push_back(struct d_list *l, void *data);

void d_list_insert_at(struct d_list *l, void *data, size_t n);

void* d_list_pop_front(struct d_list *l);

void* d_list_pop_back(struct d_list *l);

void* d_list_remove_at(struct d_list *l, size_t n);


#endif /* ! DOUBLE_LIST_H */
