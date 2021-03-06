#include "bst.h"
#include <stdlib.h>

struct bst_tree* bst_new(int data)
{
    struct bst_tree *new = calloc(1, sizeof(struct bst_tree));

    new->key = data;

    return new;
}

void bst_insert(struct bst_tree *t, int data)
{
    if(t==NULL)
        return;

    if(data<=t->key)
    {
        if(t->left==NULL)
            t->left = bst_new(data);
        else
            bst_insert(t->left, data);
    }
    else
    {
        if(t->right==NULL)
            t->right = bst_new(data);
        else
            bst_insert(t->right, data);
    }
}

// *max the max value of the tree
struct bst_tree* bst_rem_max(struct bst_tree *t, int *max)
{
    if(t->right!=NULL)
    {
        t->right = bst_rem_max(t->right, max);
        return t;
    }
    else
    {
        *max = t->key;
        struct bst_tree *new = t->left;
        free(t);
        return new;
    }
}

struct bst_tree* bst_rem(struct bst_tree *t)
{
    if(t->right!=NULL)
    {
        if(t->left!=NULL)
        {
            int max;

            t->left = bst_rem_max(t->left, &max);

            t->key = max;
            return t;
        }
        else
        {
            struct bst_tree *new = t->right;
            free(t);
            return new;
        }
    }
    else
    {
        struct bst_tree *new = t->left;
        free(t);
        return new;
    }
}

struct bst_tree *bst_remove(struct bst_tree *t, int data)
{
    if(t==NULL)
        return NULL;

    if(t->key==data)
    {
        t = bst_rem(t);
        return t;
    }
    else
    {
        if(t->key<data)
            return bst_remove(t->right, data);
        else
            return bst_remove(t->left, data);
    }
}

struct bst_tree *bst_find(struct bst_tree *t, int data)
{
    if(t==NULL)
        return NULL;
    else if(t->key==data)
        return t;
    else if(t->key<data)
        return bst_find(t->right, data);
    else
        return bst_find(t->left, data);
}

void bst_free(struct bst_tree *t)
{
    if(t!=NULL)
    {
        bst_free(t->left);
        bst_free(t->right);
        free(t);
    }
}
