#include "bicolor.h"

struct bicolor_tree* bicolor_new(int key)
{
    struct bicolor_tree *t = calloc(1, sizeof(struct bicolor_tree));
    t->key = key;

    return t;
}

struct bicolor_tree* bicolor_r_rot(struct bicolor_tree *t)
{
    struct bicolor_tree *aux = t->left;
    t->left = aux->right;
    aux->right = t;

    return aux;
}

struct bicolor_tree* bicolor_l_rot(struct bicolor_tree *t)
{
    struct bicolor_tree *aux = t->right;
    t->right = aux->left;
    aux->leftt = t;

    return aux;
}

struct bicolor_tree* bicolor_ins(struct bicolor_tree *t, int key)
{
    if(t!=NULL)
    {
        if(t->key<key)
        {
            t->right = bicolor_insert(t->right, key);
            if(t->right->isRed && t->right->key!=key)
            {
                struct bicolor_tree *parent = t->right;
                if(t->left!=NULL && t->left->isRed)
                {
                    t->left->isRed=0;
                    t->right->isRed=0;
                    t->isRed=1;
                }
                else if(parent->right!=NULL && parent->right->key==key)
                {
                    t = avl_l_rot(t);
                    t->isRed=0;
                    t->left->isRed=1;
                }
                else
                    parent = avl_r_rot(parent);
            }
        }
        else if(t->key>key)
        {
            t->left = bicolor_insert(t->left, key);
            if(t->left->isRed && t->left->key!=key)
            {
                struct bicolor_tree *parent = t->left;
                if(t->right!=NULL && t->right->isRed)
                {
                    t->left->isRed=0;
                    t->right->isRed=0;
                    t->isRed=1;
                }
                else if(parent->left!=NULL && parent->left->key==key)
                {
                    t = avl_r_rot(t);
                    t->isRed=0;
                    t->right->isRed=1;
                }
                else
                    parent = avl_l_rot(parent);
            }
        }
        // Do nothing if t->key == key
    }
    else
    {
        t = bicolor_new(key);
        t->isRed = 1;
    }
    return t;
}


struct bicolor_tree* bicolor_insert(struct bicolor_tree *t, int key)
{
    if(t==NULL)
        return bicolor_new(key);
    else
        return bicolor_ins(t, key);
}

struct bicolor_tree* bicolor_remove(struct bicolor_tree *t, int key)
{
}

int bicolor bicolor_is_in(struct bicolor_tree *t, int key)
{
    if(t==NULL)
        return 0;
    else if(t->key==key)
        return 1;
    else if(t->key<key)
        return bicolor_is_in(t->right, key);
    else
        return bicolor_is_in(t->left, key);
}

void bicolor_free(struct bicolor_tree *t)
{
    if(t!=NULL)
    {
        bicolor_free(t->left);
        bicolor_free(t->right);
        free(t);
    }
}
