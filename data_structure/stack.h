#ifndef ___stack
#define ___stack

typedef struct _stack stack;

stack* stack_create(unsigned size);
int stack_free(stack *s);

int stack_push(stack *s, int data);
int stack_pop(stack *s);
int stack_top(stack *s);

int stack_is_full(stack *s);
int stack_is_empty(stack*s);

int stack_resize(stack * newstack);

#endif
