#include "../../src/c/lists/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

Test(list_new, exists)
{
    struct list *list = list_new();

    cr_assert(list!=NULL);

    free(list);
}

Test(list_init, next_and_data)
{
    struct list *list = list_new();

    cr_assert(list->data==0 && list->next==NULL);

    free(list);
}


Test(list_push_front, push_empty)
{
    struct list *list = list_new();

    int *x = NULL;
    list_push_front(list, x);

    cr_assert(list->next!=NULL && list->next->data==NULL);

    list_free(list, &free);
}

Test(list_push_front, push_42)
{
    struct list *list = list_new();

    int *x = malloc(sizeof(int));
    list_push_front(list, x);

    cr_assert(list->next!=NULL && list->next->data==x);

    list_free(list, &free);
}


Test(list_is_empty, empty_list)
{
    struct list *list = list_new();

    cr_assert(list_is_empty(list));

    free(list);
}

Test(list_is_empty, non_empty_null_list)
{
    struct list *list = list_new();

    int *x = malloc(sizeof(int));
    list_push_front(list, x);

    cr_assert(!list_is_empty(list));

    list_free(list, &free);
}

Test(list_is_empty, non_empty_list)
{
    struct list *list = list_new();

    int *x = malloc(sizeof(int));
    list_push_front(list, x);

    cr_assert(!list_is_empty(list));

    list_free(list, &free);
}


Test(list_pop_front, pop_empty_list)
{
    struct list *list = list_new();

    int *elm = list_pop_front(list);

    cr_assert(elm==NULL);

    free(list);
}

Test(list_pop_front, non_empty_list)
{
    struct list *list = list_new();

    int *x = malloc(sizeof(int));
    list_push_front(list, x);
    int *l = list_pop_front(list);

    cr_assert(l==x);

    list_free(list, &free);
}


Test(list_find, find_not_in_list)
{
    struct list *list = list_new();

    int **v = calloc(4, sizeof(int *));
    list_push_front(list, v[0]);
    list_push_front(list, v[1]);
    list_push_front(list, v[2]);

    struct list *l = list_find(list, v[3]);

    cr_assert(l==NULL);

    list_free(list, &free);
}

Test(list_find, find_in_list)
{
    struct list *list = list_new();

    int **v = calloc(3, sizeof(int *));
    list_push_front(list, v[0]);
    list_push_front(list, v[1]);
    list_push_front(list, v[2]);

    struct list *l = list_find(list, v[2]);

    cr_assert(l!=NULL);

    list_free(list, &free);
}

Test(list_rev,rev_01)
{
    struct list *list = list_new();

    int **v = calloc(4, sizeof(int *));
    list_push_front(list, v[0]);
    list_push_front(list, v[1]);
    list_push_front(list, v[2]);
    list_push_front(list, v[3]);

	list_rev(list);
	struct list *l = list->next;
	size_t i = 0;
	while (i < 4 && l != NULL)
	{
		cr_assert(l->data == v[i]);
		i += 1;
		l = l->next;
	}

    list_free(list, &free);
}

Test(list_rev,rev_02)
{
    struct list *list = list_new();

    int x = 1;
    list_push_front(list, &x);
    int y = 8;
    list_push_front(list, &y);
    int z = 2;
    list_push_front(list, &z);

	list_rev(list);
	struct list *l = list->next;
	int *s[3] = {&z,&y,&x};
	size_t i = 0;
	while (i < 3 && l != NULL)
	{
		cr_assert(l->data == s[i]);
		i += 1;
		l = l->next;
	}

    list_free(list, &free);
}

Test(list_rev,rev_03)
{
    struct list *list = list_new();

    int x = 1;
    list_push_front(list, &x);

	list_rev(list);
	struct list *l = list->next;
	int *s[1] = {&x};
	size_t i = 0;
	while (i < 1 && l != NULL)
	{
		cr_assert(l->data == s[i]);
		i += 1;
		l = l->next;
	}

    list_free(list, &free);
}


Test(list_rev,rev_04)
{
    struct list *list = list_new();

	list_rev(list);
	int res = list_is_empty(list);
	cr_expect(res == 1);

	free(list);
}

Test(list_split,split_01)
{
    struct list *list = list_new();

    struct list *second = list_new();

    int x = 5;
    list_push_front(list, &x);
    int y = 2;
    list_push_front(list, &y);
    int z = 8;
    list_push_front(list, &z);
    int a = 1;
    list_push_front(list, &a);

	list_half_split(list,second);
	list = list->next;
	second  = second->next;
	int *s[4] = {&x,&y,&z,&a};
	size_t i = 0;
	while (i < 2 && list != NULL)
	{
		cr_assert(list->data == s[i] && second->data == s[i+2]);
		i += 1;
		list = list->next;
		second = second->next;
	}

    list_free(list, &free);
    list_free(second, &free);
}

Test(list_split,split_02)
{
    struct list *list = list_new();

    struct list *second = list_new();

    int x = 1;
    list_push_front(list, &x);
    int y = 8;
    list_push_front(list, &y);
    int z = 2;
    list_push_front(list, &z);

	list_half_split(list,second);
	list = list->next;
	second  = second->next;
	int *s[3] = {&x,&y,&z};
	size_t i = 0;
	while (list != NULL && i < 1)
	{
		cr_assert(s[i] == list->data);
		i += 1;
		list = list->next;
	}
	i += 1;
	cr_assert(s[i] == second->data);

    list_free(list, &free);
    list_free(second, &free);
}

Test(list_split,split_03)
{
    struct list *list = list_new();

    struct list *second = list_new();

    int x = 1;
    list_push_front(list, &x);

	list_half_split(list,second);
	struct list *elm = list->next;
	second  = second->next;
	int *s[1] = {&x};
	size_t i = 0;
	while (elm != NULL)
	{
		cr_assert(s[i] == list->data);
		i += 1;
		elm = elm->next;
	}
	cr_assert(second == NULL);

    list_free(list, &free);
    list_free(second, &free);
}

Test(list_split,split_04)
{
    struct list *list = list_new();

    struct list *second = list_new();

	list_half_split(list,second);
	list = list->next;
	second  = second->next;
	cr_assert(list == NULL);
	cr_assert(second == NULL);

    list_free(list, &free);
    list_free(second, &free);
}
