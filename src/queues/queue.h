#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

struct queue
{
    struct queue_elm *newest;
};

struct queue_elm
{
    void *data;
    struct queue_elm *next;
};

// Initialize (and allocate) the queue structure.
struct queue* queue_init(void);

// Return true if the queue is empty.
// Otherwise, return false.
int queue_is_empty(struct queue *queue);

// Puts data at the end of the queue
void queue_push(struct queue *queue, void* data, size_t data_size);

// Removes the element at the beginning of the queue
// Return the data of the element
void* queue_pop(struct queue *queue);

// Free the queue and all its data (using the passed in function).
void queue_free(struct queue *queue, void (*free_function)(void*));

#endif /* ! QUEUE_H */
