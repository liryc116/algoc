#include "bst.h"

struct bst_tree* bst_new(int data = 0)
{
    struct bst_tree *new = calloc(1, sizeof(bst_tree));

    new->key = data;

    return new;
}

void bst_insert(struct bst_tree *t, int data)
{
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

struct bst_tree* bst_rem(struct bst_tree *t)
{
    if(t->right!=NULL)
    {
        if(t->left!=NULL)
        {
            struct bst_tree *sub = t->right;

            while(sub->left!=NULL)
                sub = sub->left;

            t->key = sub->key;
            bst_remove(t->right, sub->key);
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

int bst_remove(struct bst_tree *t, int data)
{
    if(t==NULL)
        return 0;

    if(t->key==data)
    {
        t = bst_rem(t);
        return 1;
    }
    else
    {
        if(t->key<data)
            return bst_remove(t->right, data);
        else
            return bst_remove(t->left, data);
    }
}
