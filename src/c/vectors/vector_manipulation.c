#include "matrix_manipulation.h"
#include "matrix.h"

void vector_push(struct vector *v, void *x)
{
    if (v->capacity == v->size)
        double_capacity(v);
    v->data[v->size] = x;
    v->size+=1;
}

void* vector_pop(struct vector *v)
{
    if(v->size>0)
    {
        void* x = v->data[v->size-1];
        v->size -= 1;
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

void vector_insert(struct vector *v, size_t i, void *x)
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

void* vector_remove(struct vector *v, size_t i)
{
	if (i < v->size)
	{
		void *x = v->data[i];
        for(size_t n = i+1; n<v->size; n++)
            v->data[n-1] = v->data[n];
        v->data[v->size] = NULL;
		v->size -= 1;
		return x;
	}

	return NULL;
}
