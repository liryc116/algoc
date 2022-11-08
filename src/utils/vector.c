#include "vector.h"

#include <err.h>
#include <stdlib.h>
#include <string.h>

struct vector *vector_new()
{
    struct vector *vect = calloc(1, sizeof(struct vector));
    if (vect != NULL)
        vect->data = calloc(4, sizeof(void *));

    if (vect == NULL || vect->data == NULL)
        errx(1, "Not enough memory!");

    vect->capacity = 4;
    return vect;
}

void vector_free(struct vector *v, void (*free_function)(void *))
{
    for (size_t i = 0; i < v->size; i++)
        free_function(v->data[i]);
    free(v->data);
    free(v);
}

// Double the capacity of a vector.
// If there is not enough memory, prints
// "Not enough memory!" and exit with the error code 1.
static void double_capacity(struct vector *v)
{
    v->data = realloc(v->data, v->capacity * 2 * sizeof(void *));
    if (v->data == NULL)
        errx(1, "Not enough memory!");
    v->capacity *= 2;
}

void vector_push(struct vector *v, void *x, size_t elm_size)
{
    if (v->capacity == v->size)
        double_capacity(v);
    v->data[v->size] = malloc(elm_size);
    memcpy(v->data[v->size], x, elm_size);
    v->size += 1;
}

void *vector_pop(struct vector *v)
{
    if (v->size == 0)
        return NULL;

    v->size -= 1;
    void *x = v->data[v->size];
    v->data[v->size] = NULL;

    return x;
}

void *vector_get(struct vector *v, size_t i)
{
    if (i < v->size)
        return v->data[i];

    return NULL;
}

void vector_insert(struct vector *v, void *x, size_t elm_size, size_t i)
{
    if (i > v->size)
        return;

    if (v->capacity <= v->size)
        double_capacity(v);

    for (size_t n = v->size; n >= i && n != 0; n--)
        v->data[n] = v->data[n - 1];

    v->data[i] = malloc(elm_size);
    memcpy(v->data[i], x, elm_size);
    v->size += 1;
}

void *vector_remove(struct vector *v, size_t i)
{
    if (i >= v->size)
        return NULL;

    void *x = v->data[i];
    for (size_t n = i + 1; n < v->size; n++)
        v->data[n - 1] = v->data[n];
    v->size -= 1;
    return x;
}
