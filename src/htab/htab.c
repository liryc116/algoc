#include <err.h>

#include "htab.h"

struct htab* htab_new(void)
{
	struct htab* table = malloc(sizeof(struct htab*));
	if (table == NULL)
		errx(1, "Not enough memory!");

    table->data = calloc(4, sizeof(struct pair));

    if(table->data == NULL)
		errx(1, "Not enough memory!");

	table->size=0;
	table->capacity=4;

    for(size_t i = 0; i < table->capacity; i++)
    {
        table->data[0] = (struct pair)
        {
            .hkey = 0,
            .key = '\0',
            .value = NULL,
            .next = NULL
        };
    }
    return table;
}

void htab_clear(struct htab* ht)
{
	for (size_t i=0; i< ht->size;i++)
    {
        struct pair *p = ht->data[i].next;
        struct pair *tmp;
        for(; p!=NULL; tmp = p->next, free(p), p=tmp);
    }

	ht->size = 0;
}

void htab_free(struct htab* ht)
{
	htab_clear(ht);
    free(ht->data);
	free(ht);
}
