#ifndef BICOLOR_H
#define BICOLOR_H

struct bicolor_tree{
    int isRed; // !=0 if isRed else ==0
    int key; // can be replaced by other numeric types
    struct redblack_tree *left, *right;
};

struct bicolor_tree* bicolor_new(int key);

struct bicolor_tree* bicolor_insert(struct bicolor_tree *t, int key);

struct bicolor_tree* bicolor_remove(struct bicolor_tree *t, int key);

int bicolor bicolor_is_in(struct bicolor_tree *t, int key);

void bicolor_free(struct bicolor_tree *t);

#endif /* ! BICOLOR_H */
