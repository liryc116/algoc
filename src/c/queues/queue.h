#ifndef QUEUE_H
#define QUEUE_H

#include "../list/list.h"

struct queue
{
    struct list* newest;
}

// Initialize (and allocate) the queue structure.
struct queue* queue_init(void);

// Return true if the queue is empty.
// Otherwise, return false.
int queue_is_empty(struct queue *queue);

// Puts data at the end of the queue
void queue_push(struct queue *queue, void* data);

// Removes the element at the beginning of the queue
// Return the data of the element
void* queue_pop(struct queue *queue);

// Free the queue and all its data (using the passed in function).
void queue_free(struct queue *queue, void (*free_function)(void*));

#endif
