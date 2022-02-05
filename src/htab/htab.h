#ifndef HTAB_H
#define HTAB_H

#include <stdint.h>
#include <stdlib.h>

struct pair
{
	uint32_t hkey;
	char *key;
	void *value;
	struct pair *next;
};

struct htab
{
	size_t capacity;
	size_t size;
	struct pair *data;
};

// Create a new empty hash table.
// The initial capacity is 4.
// The initial size is 0.
// If there is not enough memory, the program prints
// "Not enough memory!" and exits with the error code 1.
// (Use the errx() function of the standard library.)
// Be careful, you have to allocate two memory spaces.
// - The memory space that holds the 'struct htab' variable.
// - The memory space that holds the data.
//   All cells of the 'data' array must be initialized to zero
//   (they contain the sentinels of the linked lists.)
struct htab* htab_new(void);

// Delete all the pairs of a hash table.
// Free the memory allocated by the pairs.
// The 'data' array is not freed.
// The table's capacity does not change.
// The table's size is set to zero.
// After this function, the hash table can still be used.
void htab_clear(struct htab* ht);

// Delete a hash table.
// Free all the allocated memory.
// After this function, the hash table can no longer be used.
void htab_free(struct htab* ht);

#include "htab_manipulation.h"

#endif /* ! HTAB_H */
