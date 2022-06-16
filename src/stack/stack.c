#include "stack.h"

#include "../utils/xmalloc.h"

#include <string.h>
#include <stdlib.h>

struct stack *stack_new()
{
    struct stack *stack = xcalloc(1, sizeof(struct stack));

    return stack;
}

int stack_is_empty(struct stack *stack)
{
    return stack->next == NULL;
}

void stack_push(struct stack *stack, void *data, size_t data_size)
{
    struct stack *new_elem = xmalloc(sizeof(struct stack));
    new_elem->next = stack->next;
    new_elem->value = xmalloc(data_size);
    memcpy(new_elem->value, data, data_size);

    stack->next = new_elem;
}

void *stack_top(struct stack *stack)
{
    if(stack->next == NULL)
        return NULL;
    return stack->next->value;
}

void *stack_pop(struct stack *stack)
{
    if(stack_is_empty(stack))
        return NULL;

    struct stack *tmp = stack->next;
    stack->next = tmp->next;

    void *data = tmp->value;
    free(tmp);

    return data;
}

void stack_free(struct stack *stack, void(*free_function)(void *))
{
    while(!stack_is_empty(stack))
        free_function(stack_pop(stack));

    free(stack);
}
