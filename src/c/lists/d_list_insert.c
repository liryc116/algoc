#include "d_list_insert.h"
#include <stdlib.h>
#include <string.h>
#include <err.h>

void d_list_push_front(struct d_list *l, void *data, size_t elm_size)
{
    struct list_elm *new = malloc(sizeof(struct list_elm));

    if(new==NULL)
        errx(1, "Not enough memory");

    new->next = l->head;
    new->prev = NULL;
    new->data = malloc(elm_size);
    memcpy(new->data, data, elm_size);

    l->len+=1;
    if(l->head!=NULL)
        l->head->prev = new;
    l->head = new;
    if(l->tail==NULL)
        l->tail = new;
}

void d_list_push_back(struct d_list *l, void *data, size_t elm_size)
{
    struct list_elm *new = malloc(sizeof(struct list_elm));

    if(new==NULL)
        errx(1, "Not enough memory");

    new->next = NULL;
    new->prev = l->tail;
    new->data = malloc(elm_size);
    memcpy(new->data, data, elm_size);

    l->len+=1;
    if(l->tail!=NULL)
        l->tail->next = new;
    l->tail = new;
    if(l->head==NULL)
        l->head = new;
}

void d_list_insert_at(struct d_list *l, void *data, size_t elm_size, size_t n)
{
    if(l->len==n)
    {
        d_list_push_back(l, data, elm_size);
        if(n==0)
            l->head = l->tail;
    }
    else if(n==0)
    {
        d_list_push_front(l, data, elm_size);
    }
    else if(n<l->len)
    {
        struct list_elm *new = malloc(sizeof(struct list_elm));
        if(new==NULL)
            errx(1, "Not enough memory");

        struct list_elm *elm = l->head;
        if(n<=l->len/2)
            for(; n!=0; elm=elm->next, n--);
        else
            for(elm = l->tail; n<l->len-1; elm=elm->prev, n++);

        new->next = elm;
        new->prev = elm->prev;
        new->data = malloc(elm_size);
        memcpy(new->data, data, elm_size);

        new->prev->next = new;
        new->next->prev = new;

        l->len++;

        if(n==0)
            l->head = new;
    }
}
