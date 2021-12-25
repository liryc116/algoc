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
int bst_remove(struct bst_tree *t, int data);

#endif /* ! BST_H  */
