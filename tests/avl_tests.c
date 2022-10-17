#include <criterion/criterion.h>
#include <stdlib.h>

#include "../src/trees/binTrees/avl.h"

Test(avl_new, new)
{
    int x = 42;
    struct avl_tree *t = avl_new(x);

    cr_assert(t != NULL);

    avl_free(t);
}

Test(avl_new, new_key)
{
    int x = 42;
    struct avl_tree *t = avl_new(x);

    cr_assert(t->key == x);

    avl_free(t);
}
