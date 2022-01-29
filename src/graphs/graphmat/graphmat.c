#include "graphmat.h"
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

struct graphmat *graphmat_new(size_t order, int directed, char *labels[])
{
    struct graphmat *g = malloc(sizeof(struct graphmat));

    if(g==NULL)
        errx(1, "graphmat_new: Not enough memory");

    g->order = order;
    g->directed = directed;
    g->labels = NULL;
    g->adj = calloc(order*order, sizeof(int));

    if(g->adj==NULL)
        errx(1, "graphmat_new: Not enough memory");

    if(labels!=NULL)
    {
        g->labels = malloc(order * sizeof(char *));
        if(g->labels==NULL)
            errx(1, "graphmat_new: Not enough memory");

        for(size_t i = 0; i<order; i++)
        {
            g->labels[i] = malloc(strlen(labels[i]) + 1);
            strcpy(g->labels[i], labels[i]);
            if(g->labels[i]==NULL)
                errx(1, "graphmat_new: Not enough memory");
        }
    }

    return g;
}

void graphmat_add_vertex(struct graphmat *g, size_t n, char *labels[])
{
    if(n!=0)
    {
        size_t old_order = g->order;
        g->order+=n;
        g->labels = reallocarray(g->labels, g->order, sizeof(char *));

        for(size_t i = old_order; i<g->order; i++)
        {
            g->labels[i] = malloc(strlen(labels[i]) + 1);
            strcpy(g->labels[i], labels[i]);
        }

        g->adj = reallocarray(g->adj, g->order*g->order, sizeof(int));
        for(size_t i = 0; i<g->order; i++)
        {
            size_t k = g->order-1;
            for(; k>old_order; k--)
                g->adj[i*g->order+k-1] = 0;
            for(; k>0; k--)
            {
                g->adj[i*g->order+k-1] = g->adj[i*old_order+k-1];
                g->adj[i*old_order+k-1] = 0;
            }
        }

    }
}

void graphmat_add_edge(struct graphmat *g, size_t i, size_t j)
{
    if(i<g->order && j<g->order)
    {
        g->adj[g->order*i+j] += 1;
        if(!g->directed)
            g->adj[g->order*j+i] += 1;
    }
}

void graphmat_free(struct graphmat *g)
{
    free(g->adj);

    if(g->labels!=NULL)
    {
        for(size_t i = 0; i<g->order; i++)
            free(g->labels[i]);
        free(g->labels);
    }

    free(g);
}
