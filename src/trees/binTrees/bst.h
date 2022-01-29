#ifndef BST_H
#define BST_H

// Put the key type by the suited number type
struct bst_tree {
    int key;
    struct bst_tree *left, *right;
};

struct bst_tree* bst_new(int data);

void bst_insert(struct bst_tree *t, int data);

/**
** Removes the first occurence of data in the tree
** If data is not in the tree do nothing
*/
struct bst_tree *bst_remove(struct bst_tree *t, int data);

struct bst_tree *bst_find(struct bst_tree *t, int data);

void bst_free(struct bst_tree *t);

#endif /* ! BST_H  */
