#ifndef GRAPHMAT_MANIPULATION_H
#define GRAPHMAT_MANIPULATION_H

#include <stddef.h>
#include "graphmat.h"

int graphmat_has_predecessor(struct graphmat *g, size_t n);

int graphmat_has_successor(struct graphmat *g, size_t n);

int graphmat_has_link(struct graphmat *g, size_t i, size_t j);

#endif /* ! GRAPHMAT_MANIPULATION_H */
