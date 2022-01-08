#include "matrix.h"
#include <err.h>
#include <stdlib.h>
#include <string.h>

struct matrix* matrix_new(size_t height, size_t width)
{

    struct matrix *matrix = malloc(sizeof(struct matrix));

    if(matrix==NULL)
        errx(1, "matrix_new: Not enough memory");

    matrix->width = width;
    matrix->height = height;
    matrix->data_size = sizeof(void *);
    matrix->data = calloc(width*height, sizeof(void *));

    if(matrix->data==NULL)
        errx(1, "matrix_new: Not enough memory");

    return matrix;
}

void matrix_add_rows(struct matrix *matrix, size_t n)
{
    if(n!=0)
    {
        matrix->height += n;
        matrix->data = reallocarray(matrix->data,
                matrix->width*matrix->height,
                matrix->data_size);

        if(matrix->data==NULL)
            errx(1, "Not enough memory");

        for(size_t i = 0; i<matrix->width; i++)
        {
            for(size_t k = matrix->height-n; k<matrix->height; k++)
                matrix->data[k*matrix->width+i] = NULL;
        }
    }
}

void matrix_add_cols(struct matrix *matrix, size_t n)
{
    if(n!=0)
    {
        size_t old_w = matrix->width;
        matrix->width += n;
        matrix->data = reallocarray(matrix->data,
                matrix->width*matrix->height,
                matrix->data_size);


        //size_t to_shift = matrix->height*old_w;
        // NULL ptr on new onews
        //for(void *i = matrix->data+old_w; to_shift>0;
        //        to_shift-=old_w, i+=matrix->width)
        //    memmove(i+n, i, to_shift);
        for(size_t i = 0; i<matrix->height; i++)
        {
            size_t k = matrix->width;
            for(; k>old_w; k--)
                matrix->data[i*matrix->width+k-1] = NULL;
            for(; k>0; k--)
                matrix->data[i*matrix->width+k-1] = matrix->data[i*old_w+k-1];
        }
    }
}

void matrix_free(struct matrix *matrix, void (*free_function)(void*))
{
    size_t width = matrix->width;
    size_t height = matrix->height;

    for(size_t i = 0; i<height; i++)
    {
        for(size_t k = 0; k<width; k++)
            if(matrix->data[i*width+k]!=NULL)
                free_function(matrix->data[i*width+k]);
    }

    free(matrix->data);
    free(matrix);
}
