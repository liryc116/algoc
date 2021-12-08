#ifndef _LIST_H_
#define _LIST_H_


#include <stddef.h>

struct list
{
  struct list *next;
  int data;
};

// Initialize the sentinel of an empty list.
void list_init(struct list *list);

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
void list_push_front(struct list *list, struct list *elm);

// Extract the first element (not the sentinel) of the list.
// This operation removes the element from the list and returns it
// (the caller is responsible for freeing it).
// If the list is empty, the function returns NULL.
struct list *list_pop_front(struct list *list);

// Search for the first element that contains 'value' and return it
// (without removing it from the list).
// The function returns NULL if the value is not in the list.
struct list *list_find(struct list *list, int value);

// Search for the first element that is greater than 'value'
// and return the element that comes just before.
// If the first element is greater than 'value', return the sentinel.
// If no element is greater than 'value', return the last element.
struct list *list_lower_bound(struct list *list, int value);

// Return true if the list is sorted in increasing order.
// Otherwise, return false.
int list_is_sorted(struct list *list);

// Insert 'elm' in the sorted list (keeping the list sorted).
// Note that 'elm' is already an existing element.
// You just have to insert it.
void list_insert(struct list *list, struct list *elm);

// Reverse the elements of the list (except for the sentinel).
void list_rev(struct list *list);

// Split the list in half and put the second half in 'second'.
// 'second' is an empty list (just a sentinel).
void list_half_split(struct list *list, struct list *second);

#endif
