#include <stdlib.h>
#include "list.h"

void list_init(struct list *list)
{
    list->data=0;
    list->next=NULL;
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

void list_push_front(struct list *list, struct list *elm)
{
    elm->next=list->next;
    list->next=elm;
}

struct list *list_pop_front(struct list *list)
{
    struct list *l = list->next;
    if (l!=NULL)
    {
        list->next=l->next;
        l->next = NULL;
    }
    return l;
}

struct list *list_find(struct list *list, int value)
{
    struct list *l = list;
    for(; l!=NULL && l->data!=value; l=l->next);

    return l;
}

struct list *list_lower_bound(struct list *list, int value)
{
   struct list *l = list;

   for(; !(list_is_empty(l)) && (l->next)->data<value; l=l->next);

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

void list_insert(struct list *list, struct list *elm)
{
    struct list *l = list;

    for(; !list_is_empty(l) && (l->next)->data<elm->data ; l=l->next);
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
