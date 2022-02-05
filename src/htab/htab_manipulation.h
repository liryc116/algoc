#ifndef HTAB_MANIPULATION_H
#define HTAB_MANIPULATION_H

#include "htab.h"

// Return a pair of the hash table from its key.
// (The pair is not removed from the hash table.)
// If the pair is not in the table, return NULL.
struct pair* htab_get(struct htab* ht, char* key);

// Insert a pair into the hash table.
// If the pair is already in the table, return 0.
// Otherwise:
// - Insert the pair in the hash table.
// - Increment the size if the pair has been placed into an empty cell.
// - If the ratio (size / capacity) is larger than 75%,
//   double the capacity of the hash table.
int htab_insert(struct htab* ht, char* key, void* value);

// Remove a pair from the table.
// The pair is also freed.
// After this function, the pair can no longer be used.
// The size is updated.
struct pair *htab_remove(struct htab* ht, char* key);

#endif /* ! HTAB_MANIPULATION_H */
