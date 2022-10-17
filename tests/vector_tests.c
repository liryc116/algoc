#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/vectors/vector.h"

Test(initialize, init_01)
{
    struct vector *tmp = vector_new();
    cr_assert(tmp->capacity == 1);
    cr_assert(tmp->size == 0);
    vector_free(tmp, &free);
}

Test(initialize, init_02)
{
    struct vector *tmp = vector_new();
    cr_assert(tmp->size == 0);
    vector_free(tmp, &free);
}

Test(double_capacity, double_01)
{
    struct vector *tmp = vector_new();
    double_capacity(tmp);
    cr_assert(tmp->capacity == 2);
    vector_free(tmp, &free);
}

Test(double_capacity, double_02)
{
    struct vector *tmp = vector_new();
    double_capacity(tmp);
    double_capacity(tmp);
    double_capacity(tmp);
    cr_assert(tmp->capacity == 8);
    vector_free(tmp, &free);
}

Test(vector_free, free_01)
{
    struct vector *tmp = vector_new();
    double_capacity(tmp);
    vector_free(tmp, &free);
}

Test(vector_free, free_02)
{
    struct vector *tmp = vector_new();
    int *x = malloc(sizeof(int));
    tmp->data[0] = x;
    tmp->size += 1;
    vector_free(tmp, &free);
}

Test(vector_push, push_01)
{
    struct vector *vect = vector_new();
    int value = 42;
    vector_push(vect, &value, sizeof(int));
    cr_assert(*(int *)vect->data[0] == value);
    vector_free(vect, &free);
}

Test(vector_push, push_02)
{
    struct vector *vect = vector_new();
    int l[4] = { 42, 15, 2, 6 };
    vector_push(vect, &l[0], sizeof(int));
    vector_push(vect, &l[1], sizeof(int));
    vector_push(vect, &l[2], sizeof(int));
    vector_push(vect, &l[3], sizeof(int));
    cr_assert(vect->size == 4);
    cr_assert(vect->capacity == 4);
    vector_free(vect, &free);
}

Test(vector_pop, pop_01)
{
    struct vector *vect = vector_new();
    int l[4] = { 42, 15, 2, 6 };
    vector_push(vect, &l[0], sizeof(int));
    vector_push(vect, &l[1], sizeof(int));
    vector_push(vect, &l[2], sizeof(int));
    vector_push(vect, &l[3], sizeof(int));
    int *res = vector_pop(vect);
    cr_assert(*(int *)res == l[3]);
    vector_free(vect, &free);
    free(res);
}

Test(vector_pop, pop_02)
{
    struct vector *tmp = vector_new();
    int x = 3;
    vector_push(tmp, &x, sizeof(int));
    int *res = vector_pop(tmp);
    cr_assert(*(int *)res == x);
    vector_free(tmp, &free);
    free(res);
}

Test(vector_pop, pop_03)
{
    struct vector *tmp = vector_new();
    int *res = vector_pop(tmp);
    cr_assert(res == NULL);
    vector_free(tmp, &free);
}

Test(vector_get, get_01)
{
    struct vector *vect = vector_new();
    int l[4] = { 42, 15, 2, 6 };
    vector_push(vect, &l[0], sizeof(int));
    vector_push(vect, &l[1], sizeof(int));
    vector_push(vect, &l[2], sizeof(int));
    vector_push(vect, &l[3], sizeof(int));
    int *res = vector_get(vect, 1);
    cr_assert(*(int *)res == l[1]);
    res = vector_get(vect, 3);
    cr_assert(*(int *)res == l[3]);
    vector_free(vect, &free);
}

Test(vector_get, get_02)
{
    struct vector *vect = vector_new();
    int *res = vector_get(vect, 1);
    cr_assert(res == NULL);
    vector_free(vect, &free);
}

Test(vector_insert, insert_01)
{
    struct vector *vect = vector_new();
    int x = 42;
    vector_insert(vect, &x, sizeof(int), 0);
    cr_assert(*(int *)vect->data[0] == x);
    cr_assert(vect->capacity == 1);
    cr_assert(vect->size == 1);
    vector_free(vect, &free);
}

Test(vector_insert, insert_02)
{
    struct vector *vect = vector_new();
    int l[4] = { 42, 15, 2, 6 };
    vector_insert(vect, &l[0], sizeof(int), 0);
    cr_assert(*(int *)vect->data[0] == l[0]);
    vector_insert(vect, &l[1], sizeof(int), 0);
    cr_assert(*(int *)vect->data[0] == l[1]);
    vector_insert(vect, &l[2], sizeof(int), 0);
    cr_assert(*(int *)vect->data[0] == l[2]);
    vector_insert(vect, &l[3], sizeof(int), 0);
    cr_assert(*(int *)vect->data[0] == l[3]);
    cr_assert(*(int *)vect->data[3] == l[0]);
    cr_assert(vect->capacity == 4);
    cr_assert(vect->size == 4);
    vector_free(vect, &free);
}

Test(vector_insert, insert_03)
{
    struct vector *vect = vector_new();
    int l[4] = { 42, 15, 2, 6 };
    vector_insert(vect, &l[0], sizeof(int), 0);
    vector_insert(vect, &l[1], sizeof(int), 0);
    vector_insert(vect, &l[2], sizeof(int), 0);
    vector_insert(vect, &l[3], sizeof(int), 2);
    cr_assert(*(int *)vect->data[2] == l[3]);
    vector_insert(vect, &l[2], sizeof(int), 2);
    cr_assert(*(int *)vect->data[2] == l[2]);
    vector_free(vect, &free);
}

Test(vector_remove, remove_01)
{
    struct vector *vect = vector_new();
    int l[4] = { 42, 15, 2, 6 };
    vector_push(vect, &l[0], sizeof(int));
    vector_push(vect, &l[1], sizeof(int));
    vector_push(vect, &l[2], sizeof(int));
    vector_push(vect, &l[3], sizeof(int));

    int *res = vector_remove(vect, 1);
    cr_assert(*res == l[1]);
    free(res);
    res = vector_remove(vect, 2);
    cr_assert(*res == l[3]);
    vector_free(vect, &free);
    free(res);
}

Test(vector_remove, remove_02)
{
    struct vector *vect = vector_new();
    int l[4] = { 42, 15, 2, 6 };
    vector_push(vect, &l[0], sizeof(int));
    vector_push(vect, &l[1], sizeof(int));
    vector_push(vect, &l[2], sizeof(int));
    vector_push(vect, &l[3], sizeof(int));
    int *res = vector_remove(vect, 3);
    free(res);
    res = vector_remove(vect, 2);
    free(res);
    res = vector_remove(vect, 1);
    cr_assert(*res == l[1]);
    free(res);
    cr_assert(vect->size == 1);
    cr_assert(vect->capacity == 4);
    res = vector_remove(vect, 0);
    vector_free(vect, &free);
    free(res);
}

Test(vector_remove, remove_03)
{
    struct vector *vect = vector_new();
    int l[4] = { 42, 15, 2, 6 };
    vector_push(vect, &l[0], sizeof(int));
    vector_push(vect, &l[1], sizeof(int));
    vector_push(vect, &l[2], sizeof(int));
    vector_push(vect, &l[3], sizeof(int));
    int *res = vector_remove(vect, 10);
    cr_assert(res == NULL);
    vector_free(vect, &free);
}
