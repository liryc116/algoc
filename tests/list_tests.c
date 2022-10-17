#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/lists/list.h"

int cmp(void *x, void *y)
{
    int *a = x;
    int *b = y;
    return *a == *b;
}

Test(list_new, exists)
{
    struct list *list = list_new();

    cr_assert(list != NULL);

    free(list);
}

Test(list_init, next_and_data)
{
    struct list *list = list_new();

    cr_assert(list->data == 0 && list->next == NULL);

    free(list);
}

Test(list_push_front, push_empty)
{
    struct list *list = list_new();

    list_push_front(list, NULL, sizeof(int));

    cr_assert(list->next == NULL);

    list_free(list, &free);
}

Test(list_push_front, push_42)
{
    struct list *list = list_new();

    int x = 42;
    list_push_front(list, &x, sizeof(int));

    cr_assert(list->next != NULL && list->next->data != NULL);

    list_free(list, &free);
}

Test(list_is_empty, empty_list)
{
    struct list *list = list_new();

    cr_assert(list_is_empty(list));

    free(list);
}

Test(list_is_empty, non_empty_list)
{
    struct list *list = list_new();

    int x = 42;

    list_push_front(list, &x, sizeof(int));

    cr_assert(!list_is_empty(list));

    list_free(list, &free);
}

Test(list_pop_front, pop_empty_list)
{
    struct list *list = list_new();

    void *elm = list_pop_front(list);

    cr_assert(elm == NULL);

    free(list);
}

Test(list_pop_front, non_empty_list)
{
    struct list *list = list_new();

    int x = 4;
    list_push_front(list, &x, sizeof(int));
    int *l = list_pop_front(list);

    cr_assert(*l == x);

    list_free(list, &free);
    free(l);
}

Test(list_find, find_not_in_list)
{
    struct list *list = list_new();

    int v[4] = { 7, 5, 8, 3 };
    list_push_front(list, &v[0], sizeof(int));
    list_push_front(list, &v[1], sizeof(int));
    list_push_front(list, &v[2], sizeof(int));

    struct list *l = list_find(list, &v[3], &cmp);

    cr_assert(l == NULL);

    list_free(list, &free);
}

Test(list_find, find_in_list)
{
    struct list *list = list_new();

    int v[3] = { 7, 5, 8 };
    list_push_front(list, &v[0], sizeof(int));
    list_push_front(list, &v[1], sizeof(int));
    list_push_front(list, &v[2], sizeof(int));

    struct list *l = list_find(list, &v[1], &cmp);

    cr_assert(l != NULL);

    list_free(list, &free);
}

Test(list_rev, rev_01)
{
    struct list *list = list_new();

    int v[4] = { 7, 3, 5, 8 };
    list_push_front(list, &v[0], sizeof(int));
    list_push_front(list, &v[1], sizeof(int));
    list_push_front(list, &v[2], sizeof(int));
    list_push_front(list, &v[3], sizeof(int));

    list_rev(list);
    struct list *l = list->next;
    size_t i = 0;
    while (i < 4 && l != NULL)
    {
        cr_assert(*(int *)l->data == v[i]);
        i += 1;
        l = l->next;
    }

    list_free(list, &free);
}

Test(list_rev, rev_02)
{
    struct list *list = list_new();

    int v[3] = { 7, 3, 5 };
    list_push_front(list, &v[0], sizeof(int));
    list_push_front(list, &v[1], sizeof(int));
    list_push_front(list, &v[2], sizeof(int));

    list_rev(list);
    struct list *l = list->next;
    size_t i = 0;
    while (i < 3 && l != NULL)
    {
        cr_assert(*(int *)l->data == v[i]);
        i += 1;
        l = l->next;
    }

    list_free(list, &free);
}

Test(list_rev, rev_03)
{
    struct list *list = list_new();

    int x = 3;
    list_push_front(list, &x, sizeof(int));

    list_rev(list);
    cr_assert(*(int *)list->next->data == x);

    list_free(list, &free);
}

Test(list_rev, rev_04)
{
    struct list *list = list_new();

    list_rev(list);
    int res = list_is_empty(list);
    cr_expect(res == 1);

    free(list);
}

Test(list_split, split_01)
{
    struct list *list = list_new();

    struct list *second = list_new();

    int v[4] = { 7, 5, 3, 9 };
    list_push_front(list, &v[3], sizeof(int));
    list_push_front(list, &v[2], sizeof(int));
    list_push_front(list, &v[1], sizeof(int));
    list_push_front(list, &v[0], sizeof(int));

    list_half_split(list, second);
    struct list *l = list->next;
    struct list *s = second->next;
    size_t i = 0;
    while (i < 2 && list != NULL)
    {
        cr_assert(*(int *)l->data == v[i] && *(int *)s->data == v[i + 2]);
        i += 1;
        l = l->next;
        s = s->next;
    }

    list_free(list, &free);
    list_free(second, &free);
}

Test(list_split, split_02)
{
    struct list *list = list_new();

    struct list *second = list_new();

    int v[3] = { 7, 3, 5 };
    list_push_front(list, &v[2], sizeof(int));
    list_push_front(list, &v[1], sizeof(int));
    list_push_front(list, &v[0], sizeof(int));

    list_half_split(list, second);
    struct list *l = list->next;
    struct list *s = second->next;
    size_t i = 0;
    while (list != NULL && i < 1)
    {
        cr_assert(v[i] == *(int *)l->data);
        i += 1;
        l = l->next;
    }
    i += 1;
    cr_assert(v[i] == *(int *)s->data);

    list_free(list, &free);
    list_free(second, &free);
}

Test(list_split, split_03)
{
    struct list *list = list_new();

    struct list *second = list_new();

    int x = 7;
    list_push_front(list, &x, sizeof(int));

    list_half_split(list, second);
    cr_assert(x == *(int *)list->next->data);
    cr_assert(second->next == NULL);

    list_free(list, &free);
    list_free(second, &free);
}

Test(list_split, split_04)
{
    struct list *list = list_new();

    struct list *second = list_new();

    list_half_split(list, second);
    cr_assert(list->next == NULL);
    cr_assert(second->next == NULL);

    list_free(list, &free);
    list_free(second, &free);
}
