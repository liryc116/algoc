#include "bin_tree.h"
#include "../../queues/queues.h"
#include <stdio.h>

struct bin_tree* bin_tree_new(void *data=NULL, void *left=NULL, void *right=NULL)
{
    struct bin_tree *new = malloc(sizeof(struct bin_tree));

    new->key = data;
    new->left = left;
    new->right = right;

    return new;
}

void bin_tree_insert_left(struct bint_tree *tree, void *insert)
{
    struct bin_tree *new = new_bin_tree(insert);

    tree->left = new;
}

void bin_tree_insert_right(struct bint_tree *tree, void *insert)
{
    struct bin_tree *new = new_bin_tree(insert);

    tree->right = new;
}

int bin_tree_height(struct bin_tree *tree)
{
    if(tree==NULL)
        return -1;

    size_t right_height = bin_tree_height(tree->right);
    size_t left_height = bin_tree_height(tree->left);

    if(right_height>left_height)
        return 1 + right_height;

    return 1 + left_height;
}

size_t bin_tree_size(struct bin_tree *tree)
{
    if(tree==NULL)
        return 0;

    return 1 + bin_tree_size(tree->left) + bin_tree_size(tree->right);
}

void bin_tree_depth(struct bin_tree *tree)
{
    // Replace the print by the behavior you want
    if(tree!=NULL)
        printf("prefix node visit\n");

    bin_tree_depth(tree->left);

    if(tree!=NULL)
        printf("infix node visit\n");

    bin_tree_depth(tree->left);

    if(tree!=NULL)
        printf("suffix node visit\n");
}

void bin_tree_breadth(struct bin_tree *tree)
{
    struct queue *q = queue_init();
    queue_push(tree);

    while(!queue_is_empty(q))
    {
        struct tree *t = queue_pop(q);

        // Treatment on t

        if(t->left!=NULL)
            queue_push(q, t->left);
        if(t->right!=NULL)
            queue_push(q, t->right);
    }
}
