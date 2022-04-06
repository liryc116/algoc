#include "btree.h"

#include "../../utils/xmalloc.h"

#include <stdlib.h>
#include <string.h>

struct btree *btree_new(size_t degree, int (*cmp_fun)(void *, void *))
{
    struct btree *t = xcalloc(1, sizeof(struct btree));

    t->degree = degree;
    t->cmp_fun = cmp_fun;

    return t;
}

static void insert_key(struct btree *t, void *key, size_t n)
{
    if(n>t->nbkeys)
        return;
    t->keys = xreallocarray(t->keys, t->nbkeys+1, sizeof(struct btree *));
    t->nbkeys += 1;
    for(size_t i = t->nbkeys; i>n ; i--)
        t->keys[i] = t->keys[i-1];
    t->keys[n] = key;
}

static void insert_child(struct btree *t, struct btree *child, size_t n)
{
    if(n>t->nbchildren)
        return;
    t->children = xreallocarray(t->children, t->nbchildren+1,
                                    sizeof(struct btree *));
    t->nbchildren += 1;
    for(size_t i = t->nbchildren; i>n ; i--)
        t->children[i] = t->children[i-1];
    t->children[n] = child;
}

static size_t bin_search(int (*cmp_fun)(void *, void *), void **keys,
        size_t len, void *value)
{
    size_t a = 0;
    size_t b = len;

    while(a<b)
    {
        size_t mid = a + (b-a)/2;
        if(cmp_fun(keys[mid], value)==0)
            return mid;
        else if(cmp_fun(keys[mid], value)>0)
            b = mid;
        else
            a = mid + 1;
    }

    return b;
}

static void split(struct btree *t, size_t i)
{
   size_t mid = t->degree - 1;
   struct btree *L = t->children[i];
   struct btree *R = btree_new(t->degree, t->cmp_fun);

   void *x = L->keys[mid];
   R->nbkeys = L->nbkeys-mid+1;
   R->keys = xcalloc(R->nbkeys, sizeof(void *));
   memcpy(R->keys, L->keys+mid+1, R->nbkeys);

   L->keys = xreallocarray(L->keys, mid, sizeof(void *));
   L->nbkeys = mid;
    //(L.keys, x, R.keys) = (L.keys[:mid], L.keys[mid], L.keys[mid+1:])
    //# children
    if(L->nbchildren!=0)
    {
       // (L.children, R.children) = (L.children[:mid+1], L.children[mid+1:])
       R->nbchildren = L->nbchildren-mid+1;
       R->children = xcalloc(R->nbchildren, sizeof(void *));
       memcpy(R->children, L->children+mid+1, R->nbchildren);

       L->keys = xreallocarray(L->keys, mid, sizeof(void *));
       L->nbkeys = mid;
    }
    //# root
    insert_key(t, x, i);
    insert_child(t, R, i+1);
}

void btree_insert_key(struct btree **tree, void *key, size_t data_size)
{
    struct btree *t = *tree;
    if(t==NULL)
        return;
    else
    {
        if(t->nbkeys == 2*t->degree - 1)
        {
            struct btree *tmp = btree_new(t->degree, t->cmp_fun);

            tmp->nbkeys = 1;
            t->keys = xcalloc(1, sizeof(void *));
            t->keys[0] = xmalloc(data_size);
            memcpy(t->keys[0], key, data_size);

            split();
        }
        __insert();
    }
}

void btree_insert_children(struct btree *t, struct btree *child)
{

}

void btree_free(struct btree *t, void(*free_fun)(void *))
{
    for(size_t i = 0; i<t->nbchildren; i++)
        btree_free(t->children[i], free_fun);

    for(size_t i = 0; i<t->nbkeys; i++)
        free_fun(t->keys[i]);

    free(t->keys);
    free(t->children);
    free(t);
}
