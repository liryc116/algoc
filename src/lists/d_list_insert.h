#ifndef D_LIST_INSERT_H
#define D_LIST_INSERT_H

#include <stddef.h>
#include "double_list.h"

void d_list_push_front(struct d_list *l, void *data, size_t elm_size);

void d_list_push_back(struct d_list *l, void *data, size_t elm_size);

void d_list_insert_at(struct d_list *l, void *data, size_t elm_size, size_t n);

#endif /* ! D_LIST_INSERT_H*/
