#ifndef BIN_TREE_H
#define BIN_TREE_H

struct bin_tree {
    struct bin_tree *left, *right;
    void *key;
}

struct bin_tree* bin_tree_new(void *data=NULL, void *left=NULL, void *right=NULL);

void bin_tree_insert_left(struct bint_tree *tree, void *insert);

void bin_tree_insert_right(struct bint_tree *tree, void *insert);

int bin_tree_height(struct bin_tree *tree);

size_t bin_tree_size(struct bin_tree *tree);

void bin_tree_depth(struct bin_tree *tree);

void bin_tree_breadth(struct bin_tree *tree);

#endif /* ! BIN_TREE_H */
