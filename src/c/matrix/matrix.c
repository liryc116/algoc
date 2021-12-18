#include "matrix.h"
#include <err.h>

struct matrix* matrix_new(size_t width=0, size_t height=0)
{
    if(data_size==0)
        return NULL;

    struct matrix *matrix = malloc(struct matrix);

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

void matrix_add_rows(struct matrix *matrix, size_t n = 1)
{
    if(n!=0)
    {
        matrix->height += n;
        matrix->data = reallocarray(matrix->data,
                matrix->width*matrix->height,
                matrix->data_size);
    }
}

void matrix_add_cols(struct matrix *matrix, size_t n = 1)
{
    if(n!=0)
    {
        size_t old_w = matrix->width;
        matrix->width += n;
        matrix->data = reallocarray(matrix->data,
                matrix->width*matrix->height,
                matrix->data_size);

        size_t to_shift = matrix->height*old_w;

        for(void *i = matrix->data+old_w; to_shift>0;
                to_shift-=old_w, i+=matrix->width)
            memmove(i+n, i, to_shift);
    }
}

void matrix_free(struct matrix *matrix, void (*free_function)(void*))
{
    size_t width = matrix->width;
    size_t height = matrix->height;

    for(size_t i = 0; i<height; i++)
    {
        for(size_t k = 0; k<width; k++)
            free_function(matrix->data[i*width+height]);
    }

    free(matrix);
}
