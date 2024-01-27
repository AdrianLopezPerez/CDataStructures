#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct {
    void *elements;
    size_t top;
    size_t capacity;
    size_t element_size;
} Stack;

typedef enum {
    STACK_SUCCESS = 0,
    STACK_INVALID_PTR = -1,
    STACK_INVALID_CAPACITY = -2,
    STACK_INVALID_ELEMENT_SIZE = -3,
    STACK_MEMORY_ALLOCATION_FAILURE = -4,
    STACK_FULL = -5,
    STACK_EMPTY = -6
} StackError;

StackError stack_init(Stack * const stack, const size_t capacity, const size_t element_size);

StackError stack_push(Stack * const stack, const void * const element);

StackError stack_pop(Stack * const stack);

StackError stack_resize(Stack * const stack, const size_t new_capacity);

StackError stack_copy(const Stack * const source_stack, Stack * const destination_stack);

StackError stack_free(Stack * const stack);

#endif
