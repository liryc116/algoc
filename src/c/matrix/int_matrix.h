#ifndef INT_MATRIX_H
#define INT_MATRIX_H

#include <stddef.h>

struct int_matrix
{
    size_t data_size;
    size_t width;
    size_t height;
    int *data;
};

/**
** Create a matrix of int
*/
struct int_matrix* int_matrix_new(size_t width, size_t height);

/**
** Sum the value of the n-th column
*/
long int_matrix_col_sum(struct int_matrix *m, size_t n);

/**
** Sum the value of the n-th row
*/
long int_matrix_row_sum(struct int_matrix *m, size_t n);

/**
** Multiply the matrix by scalar
*/
void int_matrix_scalar_mult(struct int_matrix *m, int scalar);

/**
** Return a matrix of m1*m2 (in that order)
** Return NULL if m1->width != m2->height
*/
struct int_matrix* int_matrix_mult
                    (struct int_matrix *m1, struct int_matrix *m2);

/**
** Return a matrix of m1+m2
*/
struct int_matrix* int_matrix_sum
                        (struct int_matrix *m1, struct int_matrix *m2);

#endif /* ! INT_MATRIX_H */
