#include <err.h>
#include <string.h>

#include "htab.h"

uint32_t hash(char* key)
{
	size_t i = 0;
	uint32_t hkey = 0;

	while (key[i++]!='\0')
	{
		hkey += key[i];
		hkey += hkey << 10;
		hkey ^= hkey >> 6;
	}

	hkey += hkey << 3;
	hkey ^= hkey >> 11;
	hkey += hkey << 15;

	return hkey;
}

struct htab* htab_new(void)
{
	struct htab* hash_table = malloc(sizeof(struct htab*));
	if (hash_table == NULL || (data = malloc(sizeof(struct pair*))) == NULL)
		errx(1, "Not enough memory!");

	hash_table->capacity=4;
	hash_table->size=0;

	hash_table->data->hkey = 0;
	hash_table->data->key = 0;
	hash_table->data->value = 0;
	hash_table->data->next = 0;
}

void htab_clear(struct htab* ht)
{
	for (size_t i=0; i<= ht->size;i++)
		free(ht->data[i]);

	ht->size = 0;
}

void htab_free(struct htab* ht)
{
	htab_clear(ht);
	free(ht);
}

struct pair* htab_get(struct htab* ht, char* key)
{
	struct pair* result = ht->data[0];
	while (result != NULL && result->key != key)
		result = result->next,
		return result;
}

int htab_insert(struct htab* ht, char* key, void* value)
{
	// TODO
}

void htab_remove(struct htab* ht, char* key)
{
	// TODO
}
