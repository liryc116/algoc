#include "int_matrix.h"
#include <stdlib.h>
#include <err.h>

struct int_matrix* int_matrix_new(size_t width, size_t height)
{
    struct int_matrix *matrix = malloc(sizeof(struct int_matrix));

    if(matrix==NULL)
        errx(1, "int_matrix_new: Not enough memory");

    matrix->width = width;
    matrix->height = height;
    matrix->data_size = sizeof(int);
    matrix->data = calloc(width*height, sizeof(int));

    if(matrix->data==NULL)
        errx(1, "int_matrix_new: Not enough memory");

    return matrix;
}

long int_matrix_col_sum(struct int_matrix *m, size_t n)
{
    if(n>=m->width)
        return 0;

    long res = 0;
    for(size_t i = 0; i<m->height; res+=m->data[i*m->width+n], i++);

    return res;
}

long int_matrix_row_sum(struct int_matrix *m, size_t n)
{
    if(n>=m->height)
        return 0;

    long res = 0;
    for(size_t i = 0; i<m->width; res+=m->data[n*m->width+i], i++);

    return res;
}

void int_matrix_scalar_mult(struct int_matrix *m, int scalar)
{
    for(size_t i = 0; i<m->width*m->height; m->data[i]*=scalar, i++);
}

struct int_matrix* int_matrix_mult
                        (struct int_matrix *m1, struct int_matrix *m2)
{
    if(m1->width!=m2->height)
        return NULL;

    struct int_matrix *res = int_matrix_new(m2->width, m1->height);

    for(size_t i = 0; i<m1->height; i++)
    {
        for(size_t j = 0; j<m2->width; j++)
        {
            for(size_t k = 0; k<m1->width; k++)
                res->data[i*m2->width+j]+=m1->data[i*m1->width+k]
                                            *m2->data[k*m2->width+j];
        }
    }

    return res;
}

struct int_matrix* int_matrix_sum(struct int_matrix *m1, struct int_matrix *m2)
{
    if(m1->width!=m2->width || m1->height!=m2->height)
        return NULL;

    struct int_matrix *res = int_matrix_new(m1->width, m1->height);

    for(size_t i = 0; i<m1->height; i++)
    {
        for(size_t j = 0; j<m2->width; j++)
        {
            res->data[i*m1->width+j]=m1->data[i*m1->width+j]
                                        +m2->data[i*m1->width+j];
        }
    }

    return res;

}
