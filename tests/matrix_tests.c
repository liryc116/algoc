#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/matrix/matrix.h"

Test(matrix_new, new_01)
{
    struct matrix *mat = matrix_new(4, 3);

    cr_assert(mat != NULL);

    matrix_free(mat, &free);
}

Test(matrix_new, new_02)
{
    struct matrix *mat = matrix_new(3, 4);

    cr_assert(mat->width == 4);
    cr_assert(mat->height == 3);

    matrix_free(mat, &free);
}

Test(matrix_add_row, row_1)
{
    struct matrix *mat = matrix_new(3, 3);

    matrix_add_rows(mat, 1);

    cr_assert(mat->width == 3);
    cr_assert(mat->height == 4);

    matrix_free(mat, &free);
}

Test(matrix_add_row, row_3)
{
    struct matrix *mat = matrix_new(3, 3);

    matrix_add_rows(mat, 3);

    cr_assert(mat->width == 3);
    cr_assert(mat->height == 6);

    matrix_free(mat, &free);
}

Test(matrix_add_col, col_1)
{
    struct matrix *mat = matrix_new(3, 3);

    matrix_add_cols(mat, 1);

    cr_assert(mat->width == 4);
    cr_assert(mat->height == 3);

    matrix_free(mat, &free);
}

Test(matrix_add_col, col_3)
{
    struct matrix *mat = matrix_new(3, 3);

    int *x = malloc(sizeof(int));
    *x = 42;
    mat->data[8] = x;
    matrix_add_cols(mat, 3);

    cr_assert(mat->width == 6);
    cr_assert(mat->height == 3);
    // cr_assert(*(int *)mat->data[14] == *x);

    matrix_free(mat, &free);
}

Test(matrix_put, put_01)
{
    struct matrix *mat = matrix_new(3, 3);

    int x = 42;
    matrix_put(mat, 1, 2, &x, sizeof(int));

    cr_assert(*(int *)mat->data[5] == x);

    matrix_free(mat, &free);
}

Test(matrix_put, put_02)
{
    struct matrix *mat = matrix_new(3, 4);

    int x = 42;
    matrix_put(mat, 2, 1, &x, sizeof(int));

    cr_assert(*(int *)mat->data[9] == x);

    matrix_free(mat, &free);
}

Test(matrix_put, put_oob)
{
    struct matrix *mat = matrix_new(3, 4);

    int x = 42;
    matrix_put(mat, 2, 4, &x, sizeof(int));

    matrix_free(mat, &free);
}

Test(matrix_get, get_01)
{
    struct matrix *mat = matrix_new(3, 3);

    int x = 42;
    matrix_put(mat, 1, 2, &x, sizeof(int));

    cr_assert(*(int *)matrix_get(mat, 1, 2) == x);

    matrix_free(mat, &free);
}

Test(matrix_get, get_02)
{
    struct matrix *mat = matrix_new(3, 4);

    int x = 42;
    matrix_put(mat, 2, 1, &x, sizeof(int));

    cr_assert(*(int *)matrix_get(mat, 2, 1) == x);

    matrix_free(mat, &free);
}

Test(matrix_get, get_oob)
{
    struct matrix *mat = matrix_new(3, 3);

    int x = 42;
    matrix_put(mat, 2, 1, &x, sizeof(int));

    cr_assert(matrix_get(mat, 3, 1) == NULL);

    matrix_free(mat, &free);
}

Test(matrix_transpose, same1)
{
    struct matrix *mat = matrix_new(3, 3);

    int x = 42;
    matrix_put(mat, 2, 2, &x, sizeof(int));
    matrix_transpose(mat);

    cr_assert(*(int *)matrix_get(mat, 2, 2) == x);

    matrix_free(mat, &free);
}

Test(matrix_transpose, same2)
{
    struct matrix *mat = matrix_new(3, 4);

    int x = 42;
    matrix_put(mat, 1, 1, &x, sizeof(int));
    matrix_transpose(mat);

    cr_assert(*(int *)matrix_get(mat, 1, 1) == x);

    matrix_free(mat, &free);
}

Test(matrix_transpose, diff1)
{
    struct matrix *mat = matrix_new(7, 4);

    int x = 42;
    matrix_put(mat, 5, 1, &x, sizeof(int));
    matrix_transpose(mat);

    cr_assert(*(int *)matrix_get(mat, 1, 5) == x);

    matrix_free(mat, &free);
}

Test(matrix_transpose, diff2)
{
    struct matrix *mat = matrix_new(3, 4);

    int x = 42;
    matrix_put(mat, 0, 3, &x, sizeof(int));
    matrix_transpose(mat);

    cr_assert(*(int *)matrix_get(mat, 3, 0) == x);

    matrix_free(mat, &free);
}

Test(matrix_transpose, diff3)
{
    struct matrix *mat = matrix_new(3, 4);

    int x = 42;
    matrix_put(mat, 1, 2, &x, sizeof(int));
    matrix_transpose(mat);

    cr_assert(*(int *)matrix_get(mat, 2, 1) == x);

    matrix_free(mat, &free);
}
