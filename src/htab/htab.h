#ifndef _HTAB_H_
#define _HTAB_H_

#include <stdint.h>
#include <stdlib.h>

struct pair
{
	uint32_t hkey;
	char* key;
	void* value;
	struct pair* next;
};

struct htab
{
	size_t capacity;
	size_t size;
	struct pair* data;
};

// Return the hash value of the 'key' string.
// Use the Jenkins's one_at_a_time hash.
uint32_t hash(char* key);

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
void htab_remove(struct htab* ht, char* key);

#endif
