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

    int *x = malloc(sizeof(int));
    d_list_push_front(list, x);

    cr_assert(list->head->data == x);

    d_list_free(list, &free);
}

Test(push_front, push_7)
{
    struct d_list *list = d_list_new();

    int **v = calloc(7, sizeof(int *));
    d_list_push_front(list, v[0]);
    d_list_push_front(list, v[1]);
    d_list_push_front(list, v[2]);
    d_list_push_front(list, v[3]);
    d_list_push_front(list, v[4]);
    d_list_push_front(list, v[5]);
    d_list_push_front(list, v[6]);

    cr_assert(list->head->data == v[6] && list->tail->data==v[0]);

    d_list_free(list, &free);
}

Test(push_back, push_1)
{
    struct d_list *list = d_list_new();

    int *x = malloc(sizeof(int*));
    d_list_push_back(list, x);

    cr_assert(list->tail->data == x);

    d_list_free(list, &free);
}

Test(push_back, push_4)
{
    struct d_list *list = d_list_new();

    int **v = calloc(4, sizeof(int *));
    d_list_push_front(list, v[0]);
    d_list_push_front(list, v[1]);
    d_list_push_front(list, v[2]);
    d_list_push_front(list, v[3]);

    cr_assert(list->tail->data == v[3] && list->head->data == v[0]);

    d_list_free(list, &free);
}

Test(insert_at, insert_1)
{
    struct d_list *list = d_list_new();

    int *x = malloc(sizeof(int));
    d_list_insert_at(list, x, 0);

    cr_assert(list->tail->data == x);

    d_list_free(list, &free);
}

Test(insert_at, insert_4)
{
    struct d_list *list = d_list_new();

    int **v = calloc(4, sizeof(int *));
    d_list_insert_at(list, v[0], 0);
    d_list_insert_at(list, v[1], 0);
    d_list_insert_at(list, v[2], 2);
    d_list_insert_at(list, v[3], 2);

    cr_assert(list->tail->data==v[2] && list->head->data==v[0]);

    d_list_free(list, &free);
}
