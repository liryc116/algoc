#include "double_list.h"
#include "d_list_remove.h"
#include <stdlib.h>
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

int d_list_is_empty(struct d_list *l)
{
    return l->head == NULL;
}

void d_list_free(struct d_list *l, void(*free_function)(void*))
{
    while(!d_list_is_empty(l))
        free_function(d_list_pop_front(l));

    free(l);
}
