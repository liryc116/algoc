#ifndef BTREE_H
#define BTREE_H

#include <stddef.h>

struct btree{
    void **keys;
    size_t nbkeys;
    struct btree **children;
    size_t nbchildren;
    size_t degree;
    int (*cmp_fun)(void *, void *);
};

struct btree *btree_new(size_t order, int (*cmp_fun)(void *, void *));

// tree = &btree_new()
void btree_insert_key(struct btree **tree, void *key, size_t data_size);

void btree_insert_children(struct btree *t, struct btree *child);

void btree_free(struct btree *t, void(*free_fun)(void *));

#endif /* ! BTREE_H */
