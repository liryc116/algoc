#include <err.h>
#include "vector.h"

struct vector *vector_new()
{
    struct vector* vect = calloc(1, sizeof(struct vector));
    if (vect != NULL)
        vect->data = calloc(1, sizeof(int));

    if (vect == NULL || vect->data==NULL)
        errx(1, "Not enough memory!");

    vect->capacity = 1;
	vect->size = 0;
    return vect;
}

void vector_free(struct vector *v)
{
    free(v->data);
    free(v);
}

void double_capacity(struct vector *v)
{
    v->data=realloc(v->data, v->capacity * 2);
	if (v->data == NULL)
        errx(1, "Not enough memory!");
    v->capacity *= 2;
}

void vector_push(struct vector *v, int x)
{
    if (v->capacity == v->size)
        double_capacity(v);
    v->data[v->size] = x;
    v->size+=1;
}

int vector_pop(struct vector *v, int *x)
{
    if(v->size>0)
    {
        *x = v->data[v->size-1];
        v->data[v->size] = 0;
        v->size -= 1;
        return 1;
    }

    return 0;
}

int vector_get(struct vector *v, size_t i, int *x)
{
    if (i < v->size)
    {
        *x = v->data[i];
        return 1;
    }

	return 0;
}

void vector_insert(struct vector *v, size_t i, int x)
{
    if (i<=v->size)
    {
		if (v->capacity <= v->size)
			double_capacity(v);

        for(size_t n = v->size; n>=i && n!=0; n--)
            v->data[n] = v->data[n-1];

        v->data[i] = x;
        v->size+=1;
    }
}

int vector_remove(struct vector *v, size_t i, int *x)
{
	if (i < v->size)
	{
		*x = v->data[i];
        for(size_t n = i+1; n<v->size; n++)
            v->data[n-1] = v->data[n];
        v->data[v->size] = 0;
		v->size -= 1;
		return 1;
	}

	return 0;
}
