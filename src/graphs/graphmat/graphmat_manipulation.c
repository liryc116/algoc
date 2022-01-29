#include "graphmat_manipulation.h"
#include "graphmat.h"
#include <stdlib.h>
#include <err.h>

int graphmat_has_predecessor(struct graphmat *g, size_t n)
{
    if(n>=g->order)
        return 0;

    int res = 0;
    for(size_t i = 0; i<g->order && res==0; res+=g->adj[i*g->order+n], i++);

    return res!=0;
}

int graphmat_has_successor(struct graphmat *g, size_t n)
{
    if(n>=g->order)
        return 0;

    int res = 0;
    for(size_t i = 0; i<g->order && res==0; res+=g->adj[n*g->order+i], i++);

    return res!=0;
}

int graphmat_has_link(struct graphmat *g, size_t i, size_t j)
{
    if(i>=g->order || j>=g->order)
        return -1;
    return g->adj[g->order*i+j];
}
