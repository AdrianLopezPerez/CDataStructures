#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

StackError stack_init(Stack * const stack, const size_t capacity, const size_t element_size) {
    if (!stack) {
        fprintf(stderr, "stack_init: invalid stack pointer.\n");
        return STACK_INVALID_PTR;
    }

    if (capacity == 0) {
        fprintf(stderr, "stack_init: capacity must be positive.\n");
        return STACK_INVALID_CAPACITY;
    }

    if (element_size == 0) {
        fprintf(stderr, "stack_init: element size must be positive.\n");
        return STACK_INVALID_ELEMENT_SIZE;
    }

    stack->elements = malloc(element_size * capacity);
    if (stack->elements == NULL) {
        fprintf(stderr, "stack_init: could not allocate memory.\n");
        return STACK_MEMORY_ALLOCATION_FAILURE;
    }

    stack->top = -1;
    stack->capacity = capacity;
    stack->element_size = element_size;
    return STACK_SUCCESS;
}

StackError stack_push(Stack * const stack, const void * const element) {
    if (!stack) {
        fprintf(stderr, "stack_push: invalid stack pointer.\n");
        return STACK_INVALID_PTR;
    }

    if (!element) {
        fprintf(stderr, "stack_push: invalid element pointer.\n");
        return STACK_INVALID_PTR;
    }

    if (stack->capacity <= stack->top + 1) {
        fprintf(stderr, "stack_push: not enough capacity.\n");
        return STACK_FULL;
    }

    stack->top++;
    void * target = (char *)stack->elements + stack->top * stack->element_size;
    memcpy(target, element, stack->element_size);
    return STACK_SUCCESS;
}

StackError stack_pop(Stack * const stack) {
    if (!stack) {
        fprintf(stderr, "stack_pop: invalid stack pointer.\n");
        return STACK_INVALID_PTR;
    }
    
    if (stack->top == -1) {
        fprintf(stderr, "stack_pop: stack is empty.\n");
        return STACK_EMPTY;
    }

    stack->top--;
    return STACK_SUCCESS;
}

StackError stack_resize(Stack * const stack, const size_t new_capacity) {
    if (!stack) {
        fprintf(stderr, "stack_resize: invalid stack pointer.\n");
        return STACK_INVALID_PTR;
    }

    if (new_capacity == 0 || new_capacity <= stack->top) {
        fprintf(stderr, "stack_resize: capacity must be positive.\n");
        return STACK_INVALID_CAPACITY;
    }

    void * new_elements = realloc(stack->elements, stack->element_size * new_capacity);
    if (new_elements == NULL) {
        fprintf(stderr, "stack_resize: could not allocate memory.");
        return STACK_MEMORY_ALLOCATION_FAILURE;
    }

    stack->elements = new_elements;
    stack->capacity = new_capacity;

    return STACK_SUCCESS;
}

StackError stack_copy(const Stack * const source_stack, Stack * const destination_stack) {
    if (!source_stack) {
        fprintf(stderr, "stack_copy: invalid source stack pointer.\n");
        return STACK_INVALID_PTR;
    }

    if (!destination_stack) {
        fprintf(stderr, "stack_copy: invalid destination stack pointer.\n");
        return STACK_INVALID_PTR;
    }

    destination_stack->element_size = source_stack->element_size;

    if (source_stack->capacity != destination_stack->capacity) {
        StackError resize_result = stack_resize(destination_stack, source_stack->capacity);
        if (resize_result != STACK_SUCCESS) {
            return resize_result;
        }
    }

    destination_stack->top = source_stack->top;
    memcpy(destination_stack->elements, source_stack->elements, source_stack->element_size * (source_stack->top + 1));

    return STACK_SUCCESS;
}

StackError stack_free(Stack * stack) {
    if (!stack) {
        fprintf(stderr, "stack_free: invalid stack pointer.\n");
        return STACK_INVALID_PTR;
    }

    free(stack->elements);
    stack->elements = NULL;
    stack->top = -1;
    stack->capacity = 0;
    stack->element_size = 0;
    return STACK_SUCCESS;
}