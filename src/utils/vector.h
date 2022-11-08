#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

struct vector
{
    size_t capacity;
    size_t size;
    void **data;
};

// Create a new vector.
// The initial capacity is 1.
// The initial size is 0.
// If there is not enough memory, print
// "Not enough memory!" and exit with the error code 1.
struct vector *vector_new();

// Delete a vector.
// Free all the allocated memory.
// After this instruction, the vector can no longer be used.
void vector_free(struct vector *v, void (*free_function)(void *));

// Append x at the end of a vector.
// According to the size of the vector,
// May multiply its capacity by two.
void vector_push(struct vector *v, void *x, size_t elm_size);

// Remove and return the last element of a vector.
// Return NULL if vector is empty
void *vector_pop(struct vector *v);

// Get the value at the i index.
// - If the i index is not out of bound,
//   returns it.
// - Otherwise the function returns NULL.
void *vector_get(struct vector *v, size_t i);

// Insert x in the vector at the i-index position.
// The i index must be between 0 and v->size (included).
// According to the size of the vector,
// Mmay multiply its capacity by two.
// If the i index is out of bound, do nothing.
void vector_insert(struct vector *v, void *x, size_t elm_size, size_t i);

// Remove and return the i-index element of a vector.
// - If the i index is not out of bound,
//   the i-index element is removed and returned.
// - Otherwise the function return NULL.
void *vector_remove(struct vector *v, size_t i);

#endif /* ! VECTOR_H */
