#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <err.h>

struct queue* queue_init(void)
{
    struct queue *queue = malloc(sizeof(struct queue));

    if(queue==NULL)
        errx(1, "Not enough memory");

    queue->newest = NULL;

    return queue;
}

int queue_is_empty(struct queue *queue)
{
    return queue!=NULL && queue->newest == NULL;
}


void queue_push(struct queue *queue, void* data, size_t data_size)
{
    struct queue_elm *elm = malloc(sizeof(struct queue_elm));
    if(elm==NULL)
        errx(1, "Not enough memory");

    elm->data = malloc(data_size);
    if(elm->data==NULL)
        errx(1, "Not enough memory");

    memcpy(elm->data, data, data_size);

    if(queue->newest == NULL)
    {
        elm->next = elm;
        queue->newest = elm;
    }
    else
    {
        elm->next = queue->newest->next;
        queue->newest->next = elm;
        queue->newest = elm;
    }
}

void* queue_pop(struct queue *queue)
{
    if(queue_is_empty(queue))
        return NULL;

    struct queue_elm *oldest = queue->newest->next;
    void *data = oldest->data;

    if(oldest==queue->newest)
        queue->newest = NULL;
    else
        queue->newest->next = oldest->next;

    free(oldest);
    return data;
}

void queue_free(struct queue *queue, void (*free_function)(void*))
{
    while(!queue_is_empty(queue))
        free_function(queue_pop(queue));
    free(queue);
}
