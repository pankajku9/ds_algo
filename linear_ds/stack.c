/* gcc -g3 -D DEBUG stack.c  */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef DEBUG
#define dprintf(frmt,...)  fprintf(stdout, frmt, ##__VA_ARGS__)
#else
#define dprintf(frmt, ...)
#endif

#define stack_magic_marker (0xFF11FF11)
#define STACK_IS_VALID(s)   do { if( s == NULL || s->magic != stack_magic_marker) { \
									dprintf("Invalid Stack \n"); \
									return EXIT_FAILURE; \
								} } while(0)

typedef struct _stack {
	unsigned magic;
	int top;
	int capacity;
	int * array;
} stack;



stack* stack_create(unsigned size)
 {
	stack *s = (stack*) malloc(sizeof(size));
	if(s == NULL)
		return NULL;

	s->array = (int *) malloc(size * sizeof(int));
	if(s->array == NULL){
		free(s);
		return NULL;
	}

	s->capacity = size;
	s->top = -1;
	s->magic = stack_magic_marker;
	return s;

}

int stack_is_empty(stack *s)
{
	STACK_IS_VALID(s);
	return (s->top == -1) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int stack_top(stack *s)
{
	STACK_IS_VALID(s);
	if (stack_is_empty(s) == 0)
		return -1;
	return  s->array[s->top];
}

int stack_is_full(stack *s)
{
	STACK_IS_VALID(s);
	return (s->top == s->capacity-1) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int stack_pop(stack *s)
{
	STACK_IS_VALID(s);
	if (stack_is_empty(s) == EXIT_SUCCESS) {
		dprintf("\n:underflow while POP: Top: %d ", s->top);
		return EXIT_FAILURE;
	}
	dprintf("\n:Done POP: Top: %d  DATA %d", s->top, s->array[s->top]);

	return s->array[(s->top)--];
}

int stack_resize(stack * newstack)
{
	int* temp = NULL;
	int size = newstack->capacity * 2;
	STACK_IS_VALID(newstack);

	temp = (int*) realloc(newstack->array, size * sizeof(int));
	if(temp == NULL)
		return EXIT_FAILURE;

	newstack->array = temp;
	newstack->capacity = size;
	return EXIT_SUCCESS;
}

int stack_push(stack *s, int data)
{
	int ret, input = -1;
	STACK_IS_VALID(s);
	if (stack_is_full(s) == EXIT_SUCCESS) {
		ret = stack_resize(s);
		if(ret < 0){
			dprintf("\n: Overflow ! resize failed SH: Top: %d  DATA %d", s->top, s->array[s->top]);
			return EXIT_FAILURE;
		}
	}

	s->array[++(s->top)] = data;

	dprintf("\n:Done PUSH: Top: %d  DATA %d", s->top, s->array[s->top]);
	return EXIT_SUCCESS;
}

int stack_free(stack **s_ref)
{
	stack *s = *s_ref;
	STACK_IS_VALID(s);
    free(s->array);
    s->array = NULL;
    free(s);
    *s_ref = NULL;
    return EXIT_SUCCESS;
}

void stack_test0(){
	stack s1, *s2 = NULL;
	assert(stack_push(&s1, 1) == EXIT_FAILURE);
	assert(stack_top(&s1) == EXIT_FAILURE);
	assert(stack_pop(&s1) == EXIT_FAILURE);
	assert(stack_is_empty(&s1) == EXIT_FAILURE);
	assert(stack_is_full(&s1) == EXIT_FAILURE);

	assert(stack_push(s2, 1) == EXIT_FAILURE);
	assert(stack_top(s2) == EXIT_FAILURE);
	assert(stack_pop(s2) == EXIT_FAILURE);
	assert(stack_is_empty(s2) == EXIT_FAILURE);
	assert(stack_is_full(s2) == EXIT_FAILURE);
}

void stack_test1(){

	int i,  size = 5;

	stack *s = stack_create(size);
	assert(s != NULL);

	assert(stack_is_empty(s) == 0); // stack empty
	assert(s->top == -1);
	assert(stack_pop(s) == EXIT_FAILURE);
	assert(s->capacity == size);

	for(i =0; i < size; i++){
		assert(stack_push(s, i) == EXIT_SUCCESS);
		assert(stack_top(s) == i);
	}

	assert(stack_is_full(s) == 0);
	assert(stack_push(s, i) == 0);
	assert(stack_top(s) == i);
	assert(s->capacity == 2*size);

	assert(stack_pop(s) == i);


	for(i =size-1; i >= 0; i--){
		assert(stack_top(s) == i);
		assert(stack_pop(s) == i);
	}
	assert(stack_is_empty(s) == EXIT_SUCCESS);
	assert(stack_pop(s) == EXIT_FAILURE);

}

#ifdef DEBUG
int main(){
	stack_test0();
	stack_test1();
	return 0;
}
#endif
