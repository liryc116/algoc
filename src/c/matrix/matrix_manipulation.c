#include "matrix_manipulation.h"
#include "matrix.h"
#include <err.h>
#include <stddef.h>

void* matrix_get(struct matrix *matrix, size_t i, size_t j)
{
    if(i>=matrix->height || j>=matrix->width)
        return NULL;
    return matrix->data[matrix->width*i+j];
}

void matrix_put(struct matrix *matrix, size_t i, size_t j, void* data);
{
    if(i<matrix->height && j<matrix->width)
        matrix->data[matrix->width*i+j] = data;
}

void matrix_transpose(struct matrix *matrix)
{
    void *tp_data = malloc(matrix->width*matrix->height*matrix->data_size);

    if(tp_data == NULL)
        errx(1, "Not enough memory");

    for(size_t i = 0; i<matrix->width; i++)
    {
        for(size_t k = 0; k<matrix->height; k++)
            tp_matrix[matrix->width*i+k]=matrix->data[matrix->width*k+i];
    }

    size_t tmp = matrix->width;
    matrix->width = matrix->height;
    matrix->haight = tmp;

    free(matrix->data);
    matrix->data = tp_data;
}
