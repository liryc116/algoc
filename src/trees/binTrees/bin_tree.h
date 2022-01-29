#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <stddef.h>

struct bin_tree {
    struct bin_tree *left, *right;
    void *key;
};

struct bin_tree* bin_tree_new(void *data, size_t data_size,
                                        void *left, void *right);

void bin_tree_insert_left(struct bin_tree *tree, void *insert,
                                                            size_t data_size);

void bin_tree_insert_right(struct bin_tree *tree, void *insert,
                                                            size_t data_size);

int bin_tree_height(struct bin_tree *tree);

size_t bin_tree_size(struct bin_tree *tree);

void bin_tree_depth(struct bin_tree *tree);

void bin_tree_breadth(struct bin_tree *tree);

void bin_tree_free(struct bin_tree *tree, void (*free_function)(void *));

#endif /* ! BIN_TREE_H */
