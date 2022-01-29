#include "../src/trees/binTrees/bin_tree.h"
#include <criterion/criterion.h>
#include <stdlib.h>

Test(tree_new, new)
{
    int x = 42;
    struct bin_tree *t = bin_tree_new(&x, sizeof(int), NULL, NULL);

    cr_assert(t!=NULL);

    bin_tree_free(t, &free);
}

Test(tree_new, new_key)
{
    int x = 42;
    struct bin_tree *t = bin_tree_new(&x, sizeof(int), NULL, NULL);

    cr_assert(*(int *)t->key==x);

    bin_tree_free(t, &free);
}

Test(tree_new, new_left)
{
    int x = 42;
    struct bin_tree *tl = bin_tree_new(&x, sizeof(int), NULL, NULL);
    struct bin_tree *t = bin_tree_new(&x, sizeof(int), tl, NULL);

    cr_assert(t->left!=NULL);
    cr_assert(*(int *)t->left->key==x);

    bin_tree_free(t, &free);
}

Test(insert_left, NULL_left)
{
    int x = 42;
    struct bin_tree *t = bin_tree_new(&x, sizeof(int), NULL, NULL);
    bin_tree_insert_left(t, NULL, sizeof(int));

    cr_assert(t->left==NULL);

    bin_tree_free(t, &free);
}

Test(insert_left, 42_left)
{
    int x = 42;
    struct bin_tree *t = bin_tree_new(&x, sizeof(int), NULL, NULL);
    bin_tree_insert_left(t, &x, sizeof(int));

    cr_assert(t->left!=NULL);
    cr_assert(*(int *)t->left->key==x);

    bin_tree_free(t, &free);
}

Test(tree_height, height_NULL)
{
    cr_assert(bin_tree_height(NULL)==-1);
}

Test(tree_height, height_root)
{
    int x = 42;
    struct bin_tree *t = bin_tree_new(&x, sizeof(int), NULL, NULL);

    cr_assert(bin_tree_height(t)==0);

    bin_tree_free(t, &free);
}

Test(tree_height, height_1)
{
    int x = 42;
    struct bin_tree *t = bin_tree_new(&x, sizeof(int), NULL, NULL);
    bin_tree_insert_left(t, &x, sizeof(int));

    cr_assert(bin_tree_height(t)==1);

    bin_tree_free(t, &free);
}

Test(tree_size, size_NULL)
{
    cr_assert(bin_tree_size(NULL)==0);
}

Test(tree_size, size_root)
{
    int x = 42;
    struct bin_tree *t = bin_tree_new(&x, sizeof(int), NULL, NULL);

    cr_assert(bin_tree_size(t)==1);

    bin_tree_free(t, &free);
}

Test(tree_size, size_filled)
{
    int x = 42;
    struct bin_tree *t = bin_tree_new(&x, sizeof(int), NULL, NULL);
    bin_tree_insert_left(t, &x, sizeof(int));

    cr_assert(bin_tree_size(t)==2);

    bin_tree_insert_right(t, &x, sizeof(int));
    cr_assert(bin_tree_size(t)==3);

    bin_tree_free(t, &free);
}
