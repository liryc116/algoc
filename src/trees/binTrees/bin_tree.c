#include "bin_tree.h"
#include "../../queues/queue.h"
#include <stdlib.h>
#include <string.h>

struct bin_tree* bin_tree_new(void *data, size_t data_size,
                                            void *left, void *right)
{
    if(data==NULL || data_size==0)
        return NULL;

    struct bin_tree *new = malloc(sizeof(struct bin_tree));

    new->key = malloc(data_size);
    memcpy(new->key, data, data_size);
    new->left = left;
    new->right = right;

    return new;
}

void bin_tree_insert_left(struct bin_tree *tree, void *insert,
                                                            size_t data_size)
{
    if(tree->left==NULL && insert!=NULL && data_size!=0)
        tree->left = bin_tree_new(insert, data_size, NULL, NULL);
}

void bin_tree_insert_right(struct bin_tree *tree, void *insert,
                                                            size_t data_size)
{
    if(tree->right==NULL && insert!=NULL && data_size!=0)
        tree->right = bin_tree_new(insert, data_size, NULL, NULL);
}

int bin_tree_height(struct bin_tree *tree)
{
    if(tree==NULL)
        return -1;

    int right_height = bin_tree_height(tree->right);
    int left_height = bin_tree_height(tree->left);

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
    // Prefix visit

    bin_tree_depth(tree->left);

    // Infix visit

    bin_tree_depth(tree->right);

    // Sufffix visit
}

void bin_tree_breadth(struct bin_tree *tree)
{
    struct queue *q = queue_init();
    if(tree!=NULL)
        queue_push(q, tree, sizeof(void *));

    while(!queue_is_empty(q))
    {
        struct bin_tree *t = queue_pop(q);

        // Treatment on t

        if(t->left!=NULL)
            queue_push(q, t->left, sizeof(struct bin_tree));
        if(t->right!=NULL)
            queue_push(q, t->right, sizeof(struct bin_tree));
    }

    queue_free(q, &free);
}

void bin_tree_free(struct bin_tree *tree, void (*free_function)(void *))
{
    if(tree!=NULL)
    {
        bin_tree_free(tree->left, free_function);
        bin_tree_free(tree->right, free_function);
        free_function(tree->key);
        free(tree);
    }

}
