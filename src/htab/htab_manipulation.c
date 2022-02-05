#include "htab_manipulation.h"
#include "htab.h"
#include <stdint.h>
#include <string.h>

// Return the hash value of the 'key' string.
// Use the Jenkins's one_at_a_time hash.
static uint32_t hash(char *key)
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

static void htab_double_capacity(struct htab *ht)
{
    size_t old_cap = ht->capacity;
    ht->capacity *= 2;
    ht->data = reallocarray(ht->data, ht->capacity, sizeof(struct htab));

    for(size_t i = 0; i<old_cap; i++)
    {
        struct pair *p = &ht->data[i];
        while(p->next!=NULL)
        {
            size_t new_index = p->hkey%ht->capacity;
            if(p->hkey%old_cap != new_index)
            {
                struct pair *tmp = p->next;
                p->next = tmp->next;
                tmp->next = ht->data[new_index].next;
                ht->data[new_index].next = tmp;
            }
            else
                p = p->next;
        }
    }
}

struct pair *htab_get(struct htab *ht, char *key)
{
    uint32_t searched = hash(key);

    struct pair* tmp = ht->data[searched%ht->capacity].next;
    while (tmp != NULL && tmp->hkey != searched && strcmp(key, tmp->key) != 0)
        tmp = tmp->next;

    return NULL;
}


int htab_insert(struct htab *ht, char *key, void *value)
{
    if(htab_get(ht, key)!=NULL)
        return 0;


    struct pair *i = malloc(sizeof(struct pair));
    i->key = key;
    i->value = value;
    i->hkey = hash(key);

    i->next = ht->data[i->hkey%ht->capacity].next;
    ht->data[i->hkey%ht->capacity].next=i;

    if(i->next==NULL)
        ht->size+=1;

    if((ht->size+1)*100/ht->capacity>75)
        htab_double_capacity(ht);

    return ht->capacity;
}

struct pair *htab_remove(struct htab *ht, char *key)
{
    uint32_t search = hash(key);

    struct pair *i = &ht->data[search%ht->capacity];
    while(i->next!=NULL)
    {
        if(i->next->hkey==search && i->next->key==key)
        {
            struct pair *tmp = i->next;
            i->next = tmp->next;
            return tmp;
        }
        i = i->next;
    }

    return NULL;
}
