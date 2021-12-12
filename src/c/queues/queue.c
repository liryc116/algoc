#include "queue.h"

struct queue* queue_init(void)
{
    struct queue *queue = malloc(sizeof(struct queue));

    queue->newest = NULL;

    return queue;
}

int queue_is_empty(struct queue *queue);
{
    return queue!=NULL && queue->newest == NULL;
}


void queue_push(struct queue *queue, void* data)
{
    struct queue_elm *elm = malloc(sizeof(struct queue_elm));
    elm->data = data;

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
    if(queue->newest==NULL)
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
