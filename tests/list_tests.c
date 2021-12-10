#include "list.h"
#include <stdio.h>
#include <criterion/criterion.h>

Test(list_int, exists)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);
    free(list);
}

Test(list_int, next_and_data)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    cr_assert(list->data==0 && list->next==NULL);

    free(list);
}


Test(list_push_front, push_empty)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);
    struct list *elm = malloc(sizeof(struct list));
    list_push_front(list, elm);

    cr_assert(list->next!=NULL && list->next->data==0);

    free(elm);
    free(list);
}

Test(list_push_front, push_42)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);
    struct list *elm = malloc(sizeof(struct list));
    elm->data=42;
    list_push_front(list, elm);

    cr_assert(list->next!=NULL && list->next->data==42);

    free(elm);
    free(list);
}


Test(list_is_empty, empty_list)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    cr_assert(list_is_empty(list));

    free(list);
}

Test(list_is_empty, non_empty_null_list)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
    list_push_front(list, elm);

    cr_assert(!list_is_empty(list));

    free(elm);
    free(list);
}

Test(list_is_empty, non_empty_list)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
    elm->data = 42;
    list_push_front(list, elm);

    cr_assert(!list_is_empty(list));

    free(elm);
    free(list);
}


Test(list_pop_front, pop_empty_list)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = list_pop_front(list);

    cr_assert(elm==NULL);

    free(list);
}

Test(list_pop_front, non_empty_list)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
    elm->data = 42;
    list_push_front(list, elm);
    struct list *l = list_pop_front(list);

    cr_assert(l==elm);

    free(elm);
    free(list);
}


Test(list_find, find_not_in_list)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
    elm->data = 1;
    list_push_front(list, elm);
    struct list *elm2 = malloc(sizeof(struct list));
    elm2->data = 2;
    list_push_front(list, elm2);
    struct list *elm3 = malloc(sizeof(struct list));
    elm3->data = 42;
    list_push_front(list, elm3);

	/*struct list* tmp = list->next;
	for (;tmp; tmp = tmp->next)
		printf("%i\n",tmp->data);*/

    struct list *l = list_find(list, 3);

    cr_assert(l==NULL);

    free(elm);
    free(elm2);
    free(elm3);
    free(list);
}

Test(list_find, find_in_list)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);


    struct list *elm = malloc(sizeof(struct list));
    elm->data = 1;
    list_push_front(list, elm);
    struct list *elm2 = malloc(sizeof(struct list));
    elm2->data = 2;
    list_push_front(list, elm2);
    struct list *elm3 = malloc(sizeof(struct list));
    elm3->data = 42;
    list_push_front(list, elm3);
    struct list *l = list_find(list, 42);

    cr_assert(l!=NULL);

    free(elm);
    free(elm2);
    free(elm3);
    free(list);
}
Test(list_is_sorted,sorted_01)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
	elm->data = 42;
	list_push_front(list,elm);

    struct list *elm1 = malloc(sizeof(struct list));
	elm1->data = 2;
	list_push_front(list,elm1);

    struct list *elm2 = malloc(sizeof(struct list));
	elm2->data = 1;
	list_push_front(list,elm2);

	int res = list_is_sorted(list);
	cr_assert(res == 1);

    free(elm);
    free(elm2);
    free(elm1);
    free(list);

}

Test(list_is_sorted,sorted_02)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
	elm->data = 1;
	list_push_front(list,elm);

	int res = list_is_sorted(list);
	cr_expect(res == 1);

	free(list);
	free(elm);

}

Test(list_is_sorted,sorted_03)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
	elm->data = 1;
	list_push_front(list,elm);

    struct list *elm1 = malloc(sizeof(struct list));
	elm1->data = 8;
	list_push_front(list,elm1);

    struct list *elm2 = malloc(sizeof(struct list));
	elm2->data = 2;
	list_push_front(list,elm2);

    struct list *elm3 = malloc(sizeof(struct list));
	elm3->data = 5;
	list_push_front(list,elm3);

	int res = list_is_sorted(list);
	cr_expect(res == 0);

	free(list);
	free(elm);
	free(elm1);
	free(elm2);
	free(elm3);
}


Test(list_is_sorted,sorted_04)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

	int res = list_is_sorted(list);
	cr_expect(res == 1);

    free(list);
}

Test(list_rev,rev_01)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
	elm->data = 1;
	list_push_front(list,elm);

    struct list *elm1 = malloc(sizeof(struct list));
	elm1->data = 8;
	list_push_front(list,elm1);

    struct list *elm2 = malloc(sizeof(struct list));
	elm2->data = 2;
	list_push_front(list,elm2);

    struct list *elm3 = malloc(sizeof(struct list));
	elm3->data = 5;
	list_push_front(list,elm3);

	list_rev(list);
	struct list *l = list->next;
	int s[4] = {1,8,2,5};
	size_t i = 0;
	while (i < 4 && l != NULL)
	{
		cr_assert(l->data == s[i]);
		i += 1;
		l = l->next;
	}

	free(list);
	free(elm);
	free(elm1);
	free(elm2);
	free(elm3);
}


Test(list_rev,rev_02)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
	elm->data = 1;
	list_push_front(list,elm);

    struct list *elm1 = malloc(sizeof(struct list));
	elm1->data = 8;
	list_push_front(list,elm1);

    struct list *elm2 = malloc(sizeof(struct list));
	elm2->data = 2;
	list_push_front(list,elm2);

	list_rev(list);
	struct list *l = list->next;
	int s[3] = {1,8,2};
	size_t i = 0;
	while (i < 3 && l != NULL)
	{
		cr_assert(l->data == s[i]);
		i += 1;
		l = l->next;
	}

	free(list);
	free(elm);
	free(elm1);
	free(elm2);
}

Test(list_rev,rev_03)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
	elm->data = 1;
	list_push_front(list,elm);

	list_rev(list);
	struct list *l = list->next;
	int s[1] = {1};
	size_t i = 0;
	while (i < 1 && l != NULL)
	{
		cr_assert(l->data == s[i]);
		i += 1;
		l = l->next;
	}

	free(list);
	free(elm);
}


Test(list_rev,rev_04)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

	list_rev(list);
	int res = list_is_empty(list);
	cr_expect(res == 1);

	free(list);
}

Test(list_split,split_01)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *second = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
	elm->data = 1;
	list_push_front(list,elm);

    struct list *elm1 = malloc(sizeof(struct list));
	elm1->data = 8;
	list_push_front(list,elm1);

    struct list *elm2 = malloc(sizeof(struct list));
	elm2->data = 2;
	list_push_front(list,elm2);

    struct list *elm3 = malloc(sizeof(struct list));
	elm3->data = 5;
	list_push_front(list,elm3);

	list_half_split(list,second);
	list = list->next;
	second  = second->next;
	int s[4] = {5,2,8,1};
	size_t i = 0;
	while (i < 2 && list != NULL)
	{
		cr_assert(list->data == s[i] && second->data == s[i+2]);
		i += 1;
		list = list->next;
		second = second->next;
	}
	free(elm);
	free(elm1);
	free(elm2);
	free(elm3);
}

Test(list_split,split_02)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *second = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
	elm->data = 1;
	list_push_front(list,elm);

    struct list *elm1 = malloc(sizeof(struct list));
	elm1->data = 8;
	list_push_front(list,elm1);

    struct list *elm2 = malloc(sizeof(struct list));
	elm2->data = 2;
	list_push_front(list,elm2);

	list_half_split(list,second);
	list = list->next;
	second  = second->next;
	int s[3] = {2,8,1};
	size_t i = 0;
	while (list != NULL && i < 1)
	{
		cr_assert(s[i] == list->data);
		i += 1;
		list = list->next;
	}
	i += 1;
	cr_assert(s[i] == second->data);
	free(elm);
	free(elm1);
	free(elm2);

}

Test(list_split,split_03)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *second = malloc(sizeof(struct list));
    list_init(list);

    struct list *elm = malloc(sizeof(struct list));
	elm->data = 1;
	list_push_front(list,elm);

	list_half_split(list,second);
	list = list->next;
	second  = second->next;
	int s[1] = {1};
	size_t i = 0;
	while (list != NULL)
	{
		cr_assert(s[i] == list->data);
		i += 1;
		list = list->next;
	}
	cr_assert(second == NULL);
	free(elm);
}

Test(list_split,split_04)
{
    struct list *list = malloc(sizeof(struct list));
    list_init(list);

    struct list *second = malloc(sizeof(struct list));
    list_init(list);

	list_half_split(list,second);
	list = list->next;
	second  = second->next;
	cr_assert(list == NULL);
	cr_assert(second == NULL);

	free(list);
	free(second);

}
