#ifndef D_LIST_REMOVE_H
#define D_LIST_REMOVE_H

#include "double_list.h"
#include <stddef.h>

void* d_list_pop_front(struct d_list *l);

void* d_list_pop_back(struct d_list *l);

void* d_list_remove_at(struct d_list *l, size_t n);

#endif /* ! D_LIST_REMOVE_H */
