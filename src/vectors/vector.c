#include "vector.h"
#include <stdlib.h>
#include <err.h>
#include <string.h>

struct vector *vector_new()
{
    struct vector* vect = calloc(1, sizeof(struct vector));
    if (vect != NULL)
        vect->data = calloc(1, sizeof(void*));

    if (vect==NULL || vect->data==NULL)
        errx(1, "Not enough memory!");

    vect->capacity = 1;
    return vect;
}

void vector_free(struct vector *v, void(*free_function)(void*))
{
    for(size_t i = 0; i<v->size; i++)
        free_function(v->data[i]);
    free(v->data);
    free(v);
}

void double_capacity(struct vector *v)
{
    v->data=realloc(v->data, v->capacity * 2 * sizeof(void *));
	if (v->data == NULL)
        errx(1, "Not enough memory!");
    v->capacity *= 2;
}
