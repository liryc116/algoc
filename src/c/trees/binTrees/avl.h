#ifndef AVL_H
#define AVL_H

// Change key to the numeric type you want
struct avl_tree {
    int key;
    char balance; // balance = height(right)-height(left)
    struct avl_tree *left, *right;
};

struct avl_tree* avl_new(int key=0);

/**
** Inserts key in the tree t
** If key is already in t do nothing
*/
void avl_insert(struct avl_tree *t, int key);

void avl_remove(struct avl_tree *t, int key);

int avl_is_in(struct avl_tree *t, int searched);

void avl_free(struct avl_tree *t);

#endif /* ! AVL_H */
