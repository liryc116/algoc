#include "int_matrix.h"

struct matrix* matrix_new_int(size_t width, size_t height)
{
    if(data_size==0)
        return NULL;

    struct matrix *matrix = malloc(struct matrix);

    if(matrix==NULL)
        errx(1, "matrix_new: Not enough memory");

    matrix->width = width;
    matrix->height = height;
    matrix->data_size = sizeof(int);
    matrix->data = calloc(width*height, sizeof(int));

    if(matrix->data==NULL)
        errx(1, "matrix_new: Not enough memory");

    return matrix;
}

long matrix_col_sum(struct matrix *m, size_t n)
{
    if(n>=m->width)
        return 0;

    long res = 0;
    for(size_t i = 0; i<m->height; res+=m->data[i*m->width+n], i++);

    return res;
}

long matrix_row_sum(struct matrix *m, size_t n)
{
    if(n>=m->height)
        return 0;

    long res = 0;
    for(size_t i = 0; i<m->width; res+=m->data[n*m->width+i], i++);

    return res;
}

void matrix_scalar_mult(struct matrix *m, int scalar)
{
    for(size_t i = 0; i<m->width*m->height; m->data[i]=m->data[i]*scalar, i++);
}

struct matrix* matrix_mult(struct matrix *m1, struct matrix *m2)
{
    if(m1->width!=m2->height)
        return NULL;

    struct matrix *res = matrix_new_int(m2->width, m1->height);

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

struct matrix* matrix_sum(struct matrix *m1, struct matrix *m2)
{
    if(m1->width!=m2->width || m1->height!=m2->height)
        return NULL;

    struct matrix *res = matrix_new_int(m1->width, m1->height);

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
