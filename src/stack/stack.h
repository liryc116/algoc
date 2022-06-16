#ifndef STACK_H
#define STACK_H

#include <stddef.h>

struct stack{
    struct stack *next;
    void *value;
};

struct stack *stack_new();

int stack_is_empty(struct stack *stack);

void stack_push(struct stack *stack, void *data, size_t data_size);

void *stack_top(struct stack *stack);

void *stack_pop(struct stack *stack);

void stack_free(struct stack *stack, void(*free_function)(void *));

#endif /* ! STACK_H */
