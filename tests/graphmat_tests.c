#include <criterion/criterion.h>
#include <stdlib.h>

#include "../src/graphs/graphmat/graphmat.h"

Test(graphmat_new, new_0)
{
    struct graphmat *g = graphmat_new(3, 0, NULL);

    cr_assert(g != NULL);

    graphmat_free(g);
}

Test(graphmat_new, new_3)
{
    size_t i = 3;
    struct graphmat *g = graphmat_new(i, 0, NULL);

    cr_assert(g->order == i);
    cr_assert(g->directed == 0);
    cr_assert(g->labels == NULL);

    graphmat_free(g);
}
