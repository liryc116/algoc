#include "vector_manipulation.h"
#include "vector.h"
#include <stdlib.h>
#include <string.h>

void vector_push(struct vector *v, void *x, size_t elm_size)
{
    if (v->capacity == v->size)
        double_capacity(v);
    v->data[v->size] = malloc(elm_size);
    memcpy(v->data[v->size], x, elm_size);
    v->size+=1;
}

void* vector_pop(struct vector *v)
{
    if(v->size>0)
    {
        v->size -= 1;
        void* x = v->data[v->size];
        v->data[v->size] = NULL;

        return x;
    }

    return NULL;
}

void* vector_get(struct vector *v, size_t i)
{
    if (i < v->size)
        return v->data[i];

    return NULL;
}

void vector_insert(struct vector *v, void *x, size_t elm_size, size_t i)
{
    if (i<=v->size)
    {
		if (v->capacity <= v->size)
			double_capacity(v);

        for(size_t n = v->size; n>=i && n!=0; n--)
            v->data[n] = v->data[n-1];

        v->data[i] = malloc(elm_size);
        memcpy(v->data[i], x, elm_size);
        v->size+=1;
    }
}

void* vector_remove(struct vector *v, size_t i)
{
	if (i < v->size)
	{
		void *x = v->data[i];
        for(size_t n = i+1; n<v->size; n++)
            v->data[n-1] = v->data[n];
		v->size -= 1;
		return x;
	}

	return NULL;
}
