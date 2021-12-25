#include "avl.h"
#include <err.h>

struct avl_tree* avl_new(int key=0)
{
    struct avl_tree *t = calloc(1, sizeof(struct avl_tree));

    if(t==NULL)
        errx(1, "Not enough memory");

    t->key = key;

    return t;
}

struct avl_tree* avl_r_rot(struct avl_tree *t)
{
    struct avl_tree *new_root = t->left;
    t->left = new_root->right;
    new_root->right = t;
    t->balance+=1;
    t->balance = -new_root->balance;
    return new_root;
}

struct avl_tree* avl_l_rot(struct avl_tree *t)
{
    struct avl_tree *new_root = t->right;
    t->right = new_root->left;
    new_root->left = t;
    t->balance-=1;
    t->balance = -new_root->balance;
    return new_root;
}

struct avl_tree* avl_lr_rot(struct avl_tree *t)
{
    struct avl_tree *aux = t->left->right;
    t->left->right = aux->left;
    aux->left = t->left;
    t->left = aux->right;
    aux->right = t;

    aux->left->balance = 0;
    aux->right->balance = 0;

    if(aux->balance==-1)
        aux->right->balance = 1;
    else if(aux->balance==1)
        aux->left->balance = -1;

    aux->balance = 0;

    return aux;
}

struct avl_tree* avl_rl_rot(struct avl_tree *t)
{
    struct avl_tree *aux = t->right->left;
    t->right->left = aux->right;
    aux->right = t->right;
    t->right = aux->left;
    aux->left = t;

    aux->right->balance = 0;
    aux->left->balance = 0;

    if(aux->balance==-1)
        aux->right->balance = 1;
    else if(aux->balance==1)
        aux->left->balance = -1;

    aux->balance = 0;

    return aux;
}

// dh = 0 if there is no difference in height else dh!=0
struct avl_tree* avl_ins(struct avl_tree *t, int key, int *dh)
{
    *dh = 1;
    if(t==NULL)
        return avl_new(key);
    else if(t->key==key)
    {
        *dh = 0;
        return t;
    }
    else if(t->key>key)
    {
        t->left = avl_ins(t->left, key, dh);
        if(*dh!=0)
        {
            t->balance-=1;
            *dh = t->balance==-1;
            if(t->balance==-2)
            {
                if(t->left->balance==-1)
                    t=avl_r_rot(t);
                else
                    t=avl_lr_rot(t);
            }
        }
        return t;
    }
    else // if t->key<key
    {
        t->right = avl_ins(t->right, key, dh);
        if(*dh!=0)
        {
            t->balance+=1;
            *dh = t->balance==1;
            if(t->balance==2)
            {
                if(t->right->balance==1)
                    t=avl_l_rot(t);
                else
                    t=avl_rl_rot(t);
            }
        }
        return t;
    }
}

struct avl_tree* avl_insert(struct avl_tree *t, int key)
{
    int *x;
    *x = 0;
    t = avl_ins(t, key, x);
    return t;
}

struct avl_tree* avl_rem_max(struct avl_tree *t, int *max, int *dh)
{
    *dh = 0;
    if(t==NULL)
        return NULL;
    if(t->right!=NULL)
    {
        t->right = avl_rem_max(t->right, max, dh);
        if(*dh!=0)
        {
            t->balance-=1;
            *dh = t->balance!=0;
            if(t->balance==-2)
            {
                *dh = t->left->balance==0;
                if(t->left->balance==1)
                    t = avl_lr_rot(t);
                else
                    t = avl_r_rot(t);
            }
        }
        return t;
    }
    else
    {
        *dh = 1;
        *max = t->key;
        struct avl_tree *new = t->left;
        free(t);
        return new;
    }
}

struct avl_tree* avl_rem(struct avl_tree *t, int key, int *dh)
{
    *dh = 0;
    if(t==NULL)
        return NULL;
    else if(t->key>=key)
    {
        if(t->key>key)
            t->left = avl_rem(t->left, key, dh);
        else
        {
            *dh = 1;
            if(t->right == NULL)
                return t->left;
            else if (t->left==NULL)
                return t->right;
            int *max;
            t->left = avl_rem_max(t->left, max, dh);
            t->key = max;
        }

        if(*dh!=0)
        {
            t->balance+=1;
            *dh = t->balance==1;
            if(t->balance==2)
            {
                if(t->left->balance==1)
                    t=avl_l_rot(t);
                else
                    t=avl_rl_rot(t);
            }
        }
        return t;
    }
    else // if t->key<key
    {
        t->right = avl_rem(t->right, key, dh);
        if(*dh!=0)
        {
            t->balance-=1;
            *dh = t->balance==-1;
            if(t->balance==-2)
            {
                if(t->right->balance==-1)
                    t=avl_r_rot(t);
                else
                    t=avl_lr_rot(t);
            }
        }
        return t;
    }
}

struct avl_tree* avl_remove(struct avl_tree *t, int key)
{
    int *x;
    *x = 0;
    t = avl_rem(t, key, x);
    return t;
}

int avl_is_in(struct avl_tree *t, int searched)
{
    if(t==NULL)
        return 0;
    else if(t->key==searched)
        return 1;

    if(t->key<searched)
        return avl_is_in(t->right, searched);
    else
        return avl_is_in(t->left, searched);
}

void avl_free(struct avl_tree *t)
{
    if(t!=NULL)
    {
        avl_free(t->left);
        avl_free(t->right);
        free(t);
    }
}
