#include "../src/queues/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

Test(queue_init, init01)
{
    struct queue *q = queue_init();

    cr_assert(q!=NULL);

    queue_free(q, &free);
}

Test(queue_init, init02)
{
    struct queue *q = queue_init();

    cr_assert(q!=NULL && q->newest==NULL);

    queue_free(q, &free);
}

Test(queue_is_empty, empty_q)
{
    struct queue *q = queue_init();

    cr_assert(queue_is_empty(q));

    queue_free(q, &free);
}

Test(queue_is_empty, not_empty_q)
{
    struct queue *q = queue_init();

    int x = 42;
    queue_push(q, &x, sizeof(int));

    cr_assert(!queue_is_empty(q));

    queue_free(q, &free);
}

Test(queue_push, push_1)
{
    struct queue *q = queue_init();

    int x = 42;
    queue_push(q, &x, sizeof(int));

    cr_assert(*(int *)q->newest->data == x);

    queue_free(q, &free);
}

Test(queue_push, push_2)
{
    struct queue *q = queue_init();

    int x = 42;
    queue_push(q, &x, sizeof(int));
    int y = 3;
    queue_push(q, &y, sizeof(int));

    cr_assert(*(int *)q->newest->data == y);
    cr_assert(*(int *)q->newest->next->data == x);

    queue_free(q, &free);
}

Test(queue_pop, pop_empty)
{
    struct queue *q = queue_init();

    cr_assert(queue_pop(q)==NULL);

    queue_free(q, &free);
}

Test(queue_pop, pop_1)
{
    struct queue *q = queue_init();

    int x = 42;
    queue_push(q, &x, sizeof(int));

    int *ptr = queue_pop(q);

    cr_assert(*ptr == x);
    cr_assert(queue_is_empty(q));

    queue_free(q, &free);
    free(ptr);
}

Test(queue_pop, pop_2)
{
    struct queue *q = queue_init();

    int x = 42;
    queue_push(q, &x, sizeof(int));
    int y = 3;
    queue_push(q, &y, sizeof(int));

    int *ptr = queue_pop(q);

    cr_assert(*ptr == x);
    cr_assert(!queue_is_empty(q));

    free(ptr);
    ptr = queue_pop(q);

    cr_assert(*ptr == y);
    cr_assert(queue_is_empty(q));

    queue_free(q, &free);
    free(ptr);
}

Test(queue_pop, pop_3)
{
    struct queue *q = queue_init();

    int v[5] = {42, 5, 7, 9, 3};
    for(size_t i = 0; i<5; i++)
        queue_push(q, &v[i], sizeof(int));

    int *ptr;

    cr_assert(!queue_is_empty(q));

    for(size_t i = 0; i<5; i++)
    {
        ptr = queue_pop(q);
        cr_assert(*ptr == v[i]);
        free(ptr);
    }

    cr_assert(queue_is_empty(q));

    queue_free(q, &free);
}
