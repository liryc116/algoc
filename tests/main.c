#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>

Test(Initialise,init_01)
{
	struct vector *tmp = vector_new();
	cr_assert(tmp->capacity == 1);
    cr_assert(tmp->size == 0);
	vector_free(tmp);
}

Test (Initialise,init_02)
{
	struct vector *tmp = vector_new();
    cr_assert(tmp->size == 0);
	vector_free(tmp);
}

Test (double_capacity,double_01)
{

	struct vector *tmp = vector_new();
	double_capacity(tmp);
    cr_assert(tmp->capacity == 2);
	vector_free(tmp);
}

Test (double_capacity,double_02)
{

	struct vector *tmp = vector_new();
	double_capacity(tmp);
	double_capacity(tmp);
	double_capacity(tmp);
    cr_assert(tmp->capacity == 8);
	vector_free(tmp);
}
Test(vector_push,push_01)
{
	struct vector *vect = vector_new();
	int *tmp = vect->data;
	int value = 2;
	vector_push(vect,value);
	while (*(tmp + 1) != '\0')
		tmp += 1;
    cr_assert(*tmp == value);
	vector_free(vect);
}

Test(vector_push,push_02)
{
	struct vector *vect = vector_new();
	int *tmp = vect->data;
	vector_push(vect,1);
	vector_push(vect,2);
	vector_push(vect,3);
	vector_push(vect,4);
	while (*(tmp + 1) != '\0')
		tmp += 1;
    cr_assert(*tmp == 4);
	cr_assert(vect->size = 4);
	cr_assert(vect->capacity == 4);
	vector_free(vect);
}

Test(vector_pop,pop_01)
{
	struct vector *tmp = vector_new();
	int *res = malloc(sizeof(int));
	vector_push(tmp,1);
	vector_push(tmp,2);
	vector_push(tmp,3);
	vector_push(tmp,4);
	int err = vector_pop(tmp,res);
	cr_assert(*res == 4);
	cr_assert(err == 1);
	vector_free(tmp);
}

Test(vector_pop,pop_02)
{
	struct vector *tmp = vector_new();
	int *res = malloc(sizeof(int));
	vector_push(tmp,1);
	int err = vector_pop(tmp,res);
	cr_assert(*res == 1);
	cr_assert(err == 1);
	vector_free(tmp);
}

Test(vector_pop,pop_03)
{
	struct vector *tmp = vector_new();
	int *res = malloc(sizeof(int));
	int err = vector_pop(tmp,res);
	cr_assert(err == 0);
	vector_free(tmp);
}
Test(vector_get,get_01)
{
	struct vector *tmp = vector_new();
	int *res = malloc(sizeof(int));
	vector_push(tmp,1);
	vector_push(tmp,2);
	vector_push(tmp,3);
	vector_push(tmp,4);
	int err = vector_get(tmp,1,res);
	cr_assert(*res == 2);
	cr_assert(err == 1);
	err = vector_get(tmp,3,res);
	cr_assert(*res == 4);
	cr_assert(err == 1);
	vector_free(tmp);
}

Test(vector_get,get_02)
{
	struct vector *tmp = vector_new();
	int *res = malloc(sizeof(int));
	int err = vector_get(tmp,1,res);
	cr_assert(err == 0);
	vector_free(tmp);
}

Test(vector_insert,insert_01)
{
	struct vector *tmp = vector_new();
	vector_insert(tmp,0,42);
	cr_assert(*(tmp->data) == 42);
	cr_assert(tmp->capacity == 1);
	cr_assert(tmp->size == 1);
	vector_free(tmp);
}

Test(vector_insert,insert_02)
{
	struct vector *tmp = vector_new();
	int *data = tmp->data;
	vector_insert(tmp,0,10);
	cr_assert(*data == 10);
	vector_insert(tmp,0,20);
	cr_assert(*data == 20);
	vector_insert(tmp,0,33);
	cr_assert(*data == 33);
	vector_insert(tmp,0,41);
	cr_assert(*data == 41);
	while (*(data +1 ) != '\0')
		data += 1;
	cr_assert(*data == 10);
	cr_assert(tmp->capacity == 4);
	cr_assert(tmp->size == 4);
	vector_free(tmp);
}

Test(vector_insert,insert_03)
{
	struct vector *tmp = vector_new();
	int *data = tmp->data;
	vector_insert(tmp,0,10);
	vector_insert(tmp,0,20);
	vector_insert(tmp,0,30);
	vector_insert(tmp,2,100);
	cr_assert(data[2] == 100 );
	vector_insert(tmp,2,10);
	cr_assert(data[2] == 10);
	vector_free(tmp);
}
Test(vector_remove,remove_01)
{
	struct vector *tmp = vector_new();
	int *res = malloc(sizeof(int));
	vector_push(tmp,1);
	vector_push(tmp,2);
	vector_push(tmp,3);
	vector_push(tmp,4);

	int err = vector_remove(tmp,1,res);
	cr_assert(*res == 2);
	cr_assert(err = 1);
	err = vector_remove(tmp,2,res);
	cr_assert(*res == 4);
	cr_assert(err == 1);
	vector_free(tmp);

}

Test(vector_remove,remove_02)
{
	struct vector *tmp = vector_new();
	int *res = malloc(sizeof(int));
	vector_push(tmp,1);
	vector_push(tmp,2);
	vector_push(tmp,3);
	vector_push(tmp,4);
	vector_remove(tmp,3,res);
	vector_remove(tmp,2,res);
	int err = vector_remove(tmp,1,res);
	cr_assert(*res == 2);
	cr_assert(err = 1);
	cr_assert(tmp->size == 1);
	cr_assert(tmp->capacity == 4);
	vector_free(tmp);
}


Test(vector_remove,remove_03)
{
	struct vector *tmp = vector_new();
	int *res = malloc(sizeof(int));
	vector_push(tmp,1);
	vector_push(tmp,2);
	vector_push(tmp,3);
	vector_push(tmp,4);
	int err = vector_remove(tmp,10,res);
	cr_assert(err == 0);
	vector_free(tmp);
}
