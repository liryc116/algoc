#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

struct matrix
{
    size_t data_size;
    size_t width;
    size_t height;
    void **data;
};

#include "matrix_manipulation.h"

struct matrix* matrix_new(size_t width, size_t height);

// Add n rows at the bottom of the matrix
void matrix_add_rows(struct matrix *matrix, size_t n);

// Add n rows to the right of the matrix
void matrix_add_cols(struct matrix *matrix, size_t n);

void matrix_free(struct matrix *matrix, void (*free_function)(void*));

#endif /* ! MATRIX_H */
