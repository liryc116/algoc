#include "../../src/c/lists/double_list.h"
#include <criterion/criterion.h>
#include <stdlib.h>

Test(list_new, init)
{
    struct d_list *list = d_list_new();

    free(list);
}

Test(push_front, push_1)
{
    struct d_list *list = d_list_new();

    int x = 1;
    d_list_push_front(list, &x, sizeof(int));

    cr_assert(*(int *)list->head->data == x);

    d_list_free(list, &free);
}

Test(push_front, push_7)
{
    struct d_list *list = d_list_new();

    int v[7] = {17, 5, 9, 20, 16, 2, 4};
    d_list_push_front(list, &v[0], sizeof(int));
    d_list_push_front(list, &v[1], sizeof(int));
    d_list_push_front(list, &v[2], sizeof(int));
    d_list_push_front(list, &v[3], sizeof(int));
    d_list_push_front(list, &v[4], sizeof(int));
    d_list_push_front(list, &v[5], sizeof(int));
    d_list_push_front(list, &v[6], sizeof(int));

    cr_assert(*(int *)list->head->data == v[6] && *(int *)list->tail->data==v[0]);

    d_list_free(list, &free);
}

Test(push_back, push_1)
{
    struct d_list *list = d_list_new();

    int x = 42;
    d_list_push_back(list, &x, sizeof(int));

    cr_assert(*(int *)list->tail->data == x);

    d_list_free(list, &free);
}

Test(push_back, push_4)
{
    struct d_list *list = d_list_new();

    int v[4] = {17, 5, 9, 20};
    d_list_push_back(list, &v[0], sizeof(int));
    d_list_push_back(list, &v[1], sizeof(int));
    d_list_push_back(list, &v[2], sizeof(int));
    d_list_push_back(list, &v[3], sizeof(int));

    cr_assert(*(int *)list->tail->data == v[3] && *(int *)list->head->data == v[0]);

    d_list_free(list, &free);
}

Test(insert_at, insert_1)
{
    struct d_list *list = d_list_new();

    int x = 42;
    d_list_insert_at(list, &x, sizeof(int), 0);

    cr_assert(*(int *)list->tail->data == x);

    d_list_free(list, &free);
}

Test(insert_at, insert_4)
{
    struct d_list *list = d_list_new();

    int v[4] = {17, 5, 9, 20};
    d_list_insert_at(list, &v[0], sizeof(int), 0);
    d_list_insert_at(list, &v[1], sizeof(int), 0);
    d_list_insert_at(list, &v[2], sizeof(int), 2);
    d_list_insert_at(list, &v[3], sizeof(int), 2);

    cr_assert(*(int *)list->tail->data==v[2]);
    cr_assert(*(int *)list->head->data==v[1]);
    cr_assert(*(int *)list->head->next->data==v[0]);
    cr_assert(*(int *)list->tail->prev->data==v[3]);

    d_list_free(list, &free);
}
