#ifndef INT_MATRIX_H
#define INT_MATRIX_H

#include "matrix.h"

/**
** Create a matrix of int
*/
struct matrix* matrix_new_int(size_t width, size_t height);

/**
** Sum the value of the n-th column
*/
long matrix_col_sum(struct matrix *m, size_t n);

/**
** Sum the value of the n-th row
*/
long matrix_row_sum(struct matrix *m, size_t n);

/**
** Multiply the matrix by scalar
*/
void matrix_scalar_mult(struct matrix *m, int scalar);

/**
** Return a matrix of m1*m2 (in that order)
** Return NULL if m1->height != m2->width
*/
struct matrix* matrix_mult(struct matrix *m1, struct matrix *m2);

/**
** Return a matrix of m1+m2
*/
struct matrix* matrix_sum(struct matrix *m1, struct matrix *m2);

#endif /* ! INT_MATRIX_H */
