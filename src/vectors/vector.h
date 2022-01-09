#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

struct vector
{
    size_t capacity;
    size_t size;
    void **data;
};

#include "vector_manipulation.h"

// Create a new vector.
// The initial capacity is 1.
// The initial size is 0.
// If there is not enough memory, print
// "Not enough memory!" and exit with the error code 1.
struct vector *vector_new();

// Delete a vector.
// Free all the allocated memory.
// After this instruction, the vector can no longer be used.
void vector_free(struct vector *v, void (*free_function)(void*));

// Double the capacity of a vector.
// If there is not enough memory, prints
// "Not enough memory!" and exit with the error code 1.
void double_capacity(struct vector *v);

#endif /* ! VECTOR_H */
