#include <criterion/criterion.h>
#include <stdlib.h>

#include "../src/trees/binTrees/bst.h"

Test(bst_new, new)
{
    struct bst_tree *t = bst_new(42);

    cr_assert(t != NULL);

    bst_free(t);
}

Test(bst_new, new_key)
{
    int x = 42;
    struct bst_tree *t = bst_new(x);
    cr_assert(t->key == x);
    bst_free(t);
}

Test(bst_insert, insert_1)
{
    int x = 42;
    struct bst_tree *t = bst_new(x);
    int y = 1;
    bst_insert(t, y);
    cr_assert(t->left != NULL);
    cr_assert(t->left->key == y);
    bst_free(t);
}

Test(bst_insert, insert_43)
{
    int x = 42;
    struct bst_tree *t = bst_new(x);
    int y = 43;
    bst_insert(t, y);
    cr_assert(t->right != NULL);
    cr_assert(t->right->key == y);
    bst_free(t);
}

Test(bst_insert, insert_42)
{
    int x = 42;
    struct bst_tree *t = bst_new(x);
    bst_insert(t, x);
    cr_assert(t->left != NULL);
    cr_assert(t->left->key == x);
    bst_free(t);
}

Test(bst_remove, rem_empty)
{
    struct bst_tree *t = NULL;
    cr_assert(bst_remove(t, 42) == NULL);
}

Test(bst_remove, rem_NULL)
{
    int x = 42;
    struct bst_tree *t = bst_new(x);
    cr_assert(bst_remove(t, 42) == NULL);
}

Test(bst_remove, rem_one)
{
    int x = 42;
    struct bst_tree *t = bst_new(x);
    int y = 43;
    bst_insert(t, y);
    cr_assert(t->right != NULL);
    t = bst_remove(t, x);
    cr_assert(t->right == NULL);
    cr_assert(t->key == y);
    bst_free(t);
}

Test(bst_remove, rem_two)
{
    int x = 42;
    struct bst_tree *t = bst_new(x);
    bst_insert(t, x);
    int y = 43;
    bst_insert(t, y);
    t = bst_remove(t, x);
    cr_assert(t->left == NULL);
    cr_assert(t->right != NULL);
    cr_assert(t->key == x);
    bst_free(t);
}

Test(bst_find, find_in)
{
    int x = 42;
    struct bst_tree *t = bst_new(x);
    bst_insert(t, 45);
    bst_insert(t, 46);
    bst_insert(t, 43);
    bst_insert(t, 18);
    bst_insert(t, 22);
    int y = 47;
    bst_insert(t, y);
    cr_assert(bst_find(t, y) != NULL);
    bst_free(t);
}

Test(bst_find, find_not_in)
{
    int x = 42;
    struct bst_tree *t = bst_new(x);
    bst_insert(t, 45);
    bst_insert(t, 46);
    bst_insert(t, 43);
    bst_insert(t, 18);
    bst_insert(t, 22);
    int y = 47;
    cr_assert(bst_find(t, y) == NULL);
    bst_free(t);
}
