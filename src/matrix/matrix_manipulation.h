#ifndef MATRIX_MANIPULATION_H
#define MATRIX_MANIPULATION_H

#include "matrix.h"
#include <stddef.h>

/**
** Return the element at index [i][j] (in classic matrix)
** Return NULL if i or j is OOB
*/
void* matrix_get(struct matrix *matrix, size_t i, size_t j);

void matrix_put(struct matrix *matrix, size_t i, size_t j,
                                                void* data, size_t elm_size);

void matrix_transpose(struct matrix *matrix);


#endif /* ! MATRIX_MANIPULATION_H */
