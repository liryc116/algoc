#include <stdlib.h>
#include "list.h"

struct list* list_init(void)
{
    struct list *list = malloc(sizeof(struct list));

    list->data=0;
    list->next=NULL;

    return list;
}

int list_is_empty(struct list *list)
{
    return list->next==NULL;
}

size_t list_len(struct list *list)
{
    struct list *l = list;
    size_t i;
    for(i=0; l->next!=NULL; l = l->next, i++);

    return i;
}

void list_push_front(struct list *list, void *data)
{
    struct list *new = list_init();
    new->data = data;
    new->next=list->next;
    list->next=new;
}

void* list_pop_front(struct list *list)
{
    struct list *l = list->next;
    void *data = NULL;
    if (l!=NULL)
    {
        list->next=l->next;
        data = l->data;
        free(l);
    }
    return data;
}

struct list* list_find(struct list *list, void *value)
{
    struct list *l = list;
    for(; l!=NULL && l->data!=value; l=l->next);

    return l;
}

int list_is_sorted(struct list *list)
{
    struct list *l = list->next;
    if(l==NULL)
        return 1;

    for(; !(list_is_empty(l)) && l->data<(l->next)->data; l=l->next);

    return list_is_empty(l);
}

void list_insert_at(struct list *list, size_t i, void *data)
{
    struct list *l = list;

    for(; !list_is_empty(l) && i!=0; l=l->next);
    struct list *elm = list_init();
    elm->data=data;

    list_push_front(l, elm);
}

void list_rev(struct list *list)
{
    if(!list_is_empty(list))
    {
        struct list *l = list->next;
        struct list *next = l->next;

        for(; next!=NULL; )
        {
            struct list *prev = l;
            l = next;
            next = next->next;
            l->next=prev;
        }

        list->next=l;
    }
}

void list_half_split(struct list *list, struct list *second)
{
    struct list *l=list->next;
    struct list *half = l;
    for(int i = 0; l!=NULL; l=l->next, i++)
    {
        if(i%2==0)
            half = half->next;
    }
    second->next = half;
}
