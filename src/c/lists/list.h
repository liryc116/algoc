#ifndef LIST_H
#define LIST_H

#include <stddef.h>

struct list
{
  struct list *next;
  void* data;
};

// Initialize the sentinel of an empty list.
struct list* list_new(void);

// Return true if the list is empty.
// Otherwise, return false.
// Do not forget that there is always a sentinel.
// So the list is empty if the sentinel does not point to a next element.
int list_is_empty(struct list *list);

// Return the length of the list (sentinel excluded).
size_t list_len(struct list *list);

// Insert 'elm' in front of the list, that is just after the sentinel.
// Note that 'elm' is already an existing element.
// You just have to insert it.
void list_push_front(struct list *list, void *data, size_t elm_size);

// Extract the first element (not the sentinel) of the list.
// This operation removes the element from the list and returns it
// (the caller is responsible for freeing it).
// If the list is empty, the function returns NULL.
void *list_pop_front(struct list *list);

// Search for the first element that contains 'value' and return it
// (without removing it from the list).
// The function returns NULL if the value is not in the list.
struct list *list_find(struct list *list, void *value,
        int (*is_equal)(void *, void *));

// Insert 'elm' in the list at the i index.
void list_insert_at(struct list *list, void *data, size_t elm_size, size_t i);

// Reverse the elements of the list (except for the sentinel).
void list_rev(struct list *list);

// Split the list in half and put the second half in 'second'.
// 'second' is an empty list (just a sentinel).
void list_half_split(struct list *list, struct list *second);

// Free the list and all its data (using the function in parameter).
void list_free(struct list *list, void (*free_function)(void*));

#endif /* ! LIST_H */
