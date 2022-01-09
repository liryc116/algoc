#include "d_list_remove.h"
#include <stdlib.h>

void* d_list_pop_front(struct d_list *l)
{
    if(l->head==NULL)
        return NULL;

    void *data = l->head->data;
    struct list_elm *elm = l->head;
    l->head = elm->next;
    free(elm);

    return data;
}

void* d_list_pop_back(struct d_list *l)
{
    if(l->tail==NULL)
        return NULL;

    void *data = l->tail->data;
    struct list_elm *elm = l->tail;
    l->tail = elm->prev;
    free(elm);

    return data;
}

void* d_list_remove_at(struct d_list *l, size_t n)
{
    if(n==l->len)
        return d_list_pop_back(l);
    else if(n==0)
        return d_list_pop_front(l);
    else if(n<l->len)
    {
        struct list_elm *elm = l->head;
        if(n<=l->len/2)
            for(; n!=0; elm=elm->next, n--);
        else
            for(elm = l->tail; n<l->len-1; elm=elm->prev, n++);


        elm->prev->next = elm->next;
        elm->next->prev = elm->prev;

        void *data = elm->data;
        free(elm);
        return data;
    }
    return NULL;
}
