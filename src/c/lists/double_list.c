#include "double_list.h"
#include <stddef.h>
#include <err.h>

struct d_list* d_list_new(void)
{
    struct d_list *l = calloc(1, sizeof(struct d_list));

    if(l==NULL)
        errx(1, "Not enough memory");

    return l;
}

size_t d_list_len(struct d_list *l)
{
    return l->len;
}

void d_list_push_front(struct d_list *l, void *data)
{
    struct list_elm *new = malloc(sizeof(struct list_elm));

    if(new==NULL)
        errx(1, "Not enough memory");

    new->next = l->head;
    new->prev = NULL;
    new->data = data;

    l->len+=1;
    if(l->head!=NULL)
        l->head->prev = new;
    l->head = new;
}

void d_list_push_back(struct d_list *l, void *data)
{
    struct list_elm *new = malloc(sizeof(struct list_elm));

    if(new==NULL)
        errx(1, "Not enough memory");

    new->next = NULL;
    new->prev = l->tail;
    new->data = data;

    l->len+=1;
    if(l->tail!=NULL)
        l->tail->next = new;
    l->tail = new;
}

void d_list_insert_at(struct d_list *l, void *data, size_t n)
{

}

void* d_list_pop_front(struct d_list *l);

void* d_list_pop_back(struct d_list *l);

void* d_list_remove_at(struct d_list *l, size_t n);
