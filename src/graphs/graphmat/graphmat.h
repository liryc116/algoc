#ifndef GRAPHMAT_H
#define GRAPHMAT_H

#include <stddef.h>

struct graphmat
{
    int *adj;
    char **labels; // list of string
    size_t order;
    int directed; // 0 if the graph is not directed else !0
};

// labels an array (of size order) of strings
struct graphmat *graphmat_new(size_t order, int directed, char *labels[]);

void graphmat_addedge(struct graphmat *g, size_t src, size_t dst);

void graphmat_addvertex(struct graphmat *g, size_t n, char *labels[]);

void graphmat_free(struct graphmat *g);

#include "graphmat_manipulation.h"

#endif /* ! GRAPHMAT_H */
