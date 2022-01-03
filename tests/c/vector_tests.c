#include "../../src/c/vectors/vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>

Test(initialize,init_01)
{
	struct vector *tmp = vector_new();
	cr_assert(tmp->capacity == 1);
    cr_assert(tmp->size == 0);
	vector_free(tmp, &free);
}

Test(initialize,init_02)
{
	struct vector *tmp = vector_new();
    cr_assert(tmp->size == 0);
	vector_free(tmp, &free);
}

Test (double_capacity,double_01)
{
	struct vector *tmp = vector_new();
	double_capacity(tmp);
    cr_assert(tmp->capacity == 2);
	vector_free(tmp, &free);
}

Test (double_capacity,double_02)
{
	struct vector *tmp = vector_new();
	double_capacity(tmp);
	double_capacity(tmp);
	double_capacity(tmp);
    cr_assert(tmp->capacity == 8);
	vector_free(tmp, &free);
}

Test(vector_push,push_01)
{
	struct vector *vect = vector_new();
	int **value = malloc(sizeof(int*));
	vector_push(vect, value);
    cr_assert(vect->data[0] == value);
	vector_free(vect, &free);
}

Test(vector_push,push_02)
{
	struct vector *vect = vector_new();
    int **l = calloc(4, sizeof(int*));
	vector_push(vect,l[0]);
	vector_push(vect,l[1]);
	vector_push(vect,l[2]);
	vector_push(vect,l[3]);
	cr_assert(vect->size == 4);
	cr_assert(vect->capacity == 4);
	vector_free(vect, &free);
    free(l);
}

Test(vector_pop,pop_01)
{
	struct vector *vect = vector_new();
    int **l = calloc(4, sizeof(int*));
	vector_push(vect,l[0]);
	vector_push(vect,l[1]);
	vector_push(vect,l[2]);
	vector_push(vect,l[3]);
	int *res = vector_pop(vect);
	cr_assert(res == l[3]);
	vector_free(vect, &free);
}

Test(vector_pop,pop_02)
{
	struct vector *tmp = vector_new();
    int *x = malloc(sizeof(int));
	vector_push(tmp,x);
	int *res = vector_pop(tmp);
	cr_assert(res == x);
	vector_free(tmp, &free);
    free(x);
}

Test(vector_pop,pop_03)
{
	struct vector *tmp = vector_new();
	int *res = vector_pop(tmp);
	cr_assert(res == NULL);
	vector_free(tmp, &free);
}
Test(vector_get,get_01)
{
	struct vector *vect = vector_new();
    int **l = calloc(4, sizeof(int*));
	vector_push(vect,l[0]);
	vector_push(vect,l[1]);
	vector_push(vect,l[2]);
	int *res = vector_get(vect,1);
	cr_assert(res == l[1]);
	res = vector_get(vect, 3);
	cr_assert(res == l[3]);
	vector_free(vect, &free);
    free(res);
}

Test(vector_get,get_02)
{
	struct vector *tmp = vector_new();
	int *res = vector_get(tmp,1);
	cr_assert(res == NULL);
	vector_free(tmp, &free);
}

Test(vector_insert,insert_01)
{
	struct vector *tmp = vector_new();
    int *x = malloc(sizeof(int));
	vector_insert(tmp, 0, x);
	cr_assert(tmp->data[0] == x);
	cr_assert(tmp->capacity == 1);
	cr_assert(tmp->size == 1);
	vector_free(tmp, &free);
}

Test(vector_insert,insert_02)
{
	struct vector *tmp = vector_new();
    int **l = calloc(4, sizeof(int*));
	vector_insert(tmp, 0, l[0]);
	cr_assert(tmp->data[0] == l[0]);
	vector_insert(tmp, 0, l[1]);
	cr_assert(tmp->data[0] == l[1]);
	vector_insert(tmp, 0, l[2]);
	cr_assert(tmp->data[0] == l[2]);
	vector_insert(tmp, 0, l[3]);
	cr_assert(tmp->data[0] == l[3]);
	cr_assert(tmp->data[3] == l[0]);
	cr_assert(tmp->capacity == 4);
	cr_assert(tmp->size == 4);
	vector_free(tmp, &free);
}

Test(vector_insert,insert_03)
{
	struct vector *tmp = vector_new();
    int **l = calloc(4, sizeof(int*));
	vector_insert(tmp, 0, l[0]);
	vector_insert(tmp, 0, l[1]);
	vector_insert(tmp, 0, l[2]);
	vector_insert(tmp, 2, l[3]);
	cr_assert(tmp->data[2] == l[3] );
	vector_insert(tmp, 2, l[2]);
	cr_assert(tmp->data[2] == l[2]);
	vector_free(tmp, &free);
}
Test(vector_remove,remove_01)
{
	struct vector *tmp = vector_new();
    int **l = calloc(4, sizeof(int*));
	vector_push(tmp, l[0]);
	vector_push(tmp, l[1]);
	vector_push(tmp, l[2]);
	vector_push(tmp, l[3]);

	int *res = vector_remove(tmp,1);
	cr_assert(*res == 2);
	res = vector_remove(tmp,2);
	cr_assert(*res == 4);
	vector_free(tmp, &free);
}

Test(vector_remove,remove_02)
{
	struct vector *tmp = vector_new();
    int **l = calloc(4, sizeof(int*));
	vector_push(tmp, l[0]);
	vector_push(tmp, l[1]);
	vector_push(tmp, l[2]);
	vector_push(tmp, l[3]);
	int *res = vector_remove(tmp,3);
	res = vector_remove(tmp,2);
	res = vector_remove(tmp,1);
	cr_assert(*res == 2);
	cr_assert(tmp->size == 1);
	cr_assert(tmp->capacity == 4);
	vector_free(tmp, &free);
}


Test(vector_remove,remove_03)
{
	struct vector *tmp = vector_new();
    int **l = calloc(4, sizeof(int*));
	vector_push(tmp, l[0]);
	vector_push(tmp, l[1]);
	vector_push(tmp, l[2]);
	vector_push(tmp, l[3]);
	int *res = vector_remove(tmp,10);
	cr_assert(res == NULL);
	vector_free(tmp, &free);
}
