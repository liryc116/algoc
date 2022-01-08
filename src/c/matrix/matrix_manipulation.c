#include "matrix_manipulation.h"
#include "matrix.h"
#include <err.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void* matrix_get(struct matrix *matrix, size_t i, size_t j)
{
    if(i>=matrix->height || j>=matrix->width)
        return NULL;
    return matrix->data[matrix->width*i+j];
}

void matrix_put(struct matrix *matrix, size_t i, size_t j,
                                    void* data, size_t elm_size)
{
    if(i<matrix->height && j<matrix->width)
    {
        matrix->data[matrix->width*i+j] = malloc(elm_size);
        memcpy(matrix->data[matrix->width*i+j], data, elm_size);
    }
}

void matrix_transpose(struct matrix *matrix)
{
    void **tp_data = calloc(matrix->width*matrix->height, matrix->data_size);

    if(tp_data == NULL)
        errx(1, "Not enough memory");

    for(size_t i = 0; i<matrix->width; i++)
    {
        for(size_t j = 0; j<matrix->height; j++)
        {
            tp_data[matrix->height*i+j] = matrix->data[matrix->width*j+i];
            //if(matrix->data[matrix->width*j+i]!=NULL)
              //  memcpy(tp_data[matrix->height*i+j],
                //        matrix->data[matrix->width*j+i], matrix->data_size);
        }
    }

    size_t tmp = matrix->width;
    matrix->width = matrix->height;
    matrix->height = tmp;

    free(matrix->data);
    matrix->data = tp_data;
}
