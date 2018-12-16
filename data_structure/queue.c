
#include "../../ds_algo1/data_structure/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#ifdef DEBUG
#define dprintf(frmt,...)  fprintf(stdout, frmt, ##__VA_ARGS__)
#else
#define dprintf(frmt, ...)
#endif

#define QUEUE_MARKER_MAGIC (0xFF12FF12)
#define QUEUE_IS_VALID(q)   do { if( q == NULL || q->magic != QUEUE_MARKER_MAGIC) { \
									dprintf("Invalid Queue \n"); \
									return EXIT_FAILURE; \
								} } while(0)

typedef struct _queue {
	int front, back;
	unsigned capacity;
	unsigned magic;
	int* array;
} queue;

queue* queue_create(unsigned capacity)
{
	queue* newQ = (queue*) malloc(sizeof(queue));
	if (newQ == NULL)
		return NULL;

	newQ->array = (int*) malloc(capacity * sizeof(int));
	if (newQ->array == NULL) {
		free(newQ);
		return NULL;
	}

	newQ->front = -1;
	newQ->back = -1;
	newQ->magic = QUEUE_MARKER_MAGIC;
	newQ->capacity = capacity;

	return newQ;
}
int queue_free(queue **q_ref){

	queue *q = *q_ref;
	free(q->array);
	q->array = NULL;
	free(q);
	*q_ref = NULL;
	return EXIT_SUCCESS;
}

int queue_is_empty(queue *q)
{
	QUEUE_IS_VALID(q);
	return q->front == -1 ? EXIT_SUCCESS : EXIT_FAILURE;
}

int queue_is_full(queue *q)
{
	QUEUE_IS_VALID(q);
	return q->front == (q->back + 1) % q->capacity ? EXIT_SUCCESS : EXIT_FAILURE;
}

int queue_push(queue *q, int data)
{
	QUEUE_IS_VALID(q);
	if (queue_is_full(q) == 0) {
		dprintf("\n:Overflow: FRONT: %d BACK:%d %d", q->front, q->back, q->capacity);
		//TODO add resize
		return EXIT_FAILURE;
	}

	if(q->back == -1)
		q->front = 0;

	q->back = (q->back + 1) % q->capacity;
	q->array[q->back] = data;

	dprintf("\n:Added: FRONT:%d Rear:%d DATA %d", q->front,q->back,q->array[q->back] );
	return EXIT_SUCCESS;
}

int queue_pop(queue *q)
{
	int data;
	QUEUE_IS_VALID(q);
	if (queue_is_empty(q) == 0) {
		dprintf("\n:underflow: FRONT: %d Rear:%d SIZE:%d ", q->front,q->back,q->capacity);
		return EXIT_FAILURE;
	}
	dprintf("\n:Removing: FRONT: %d Rear:%d SIZE:%d ", q->front, q->back, q->capacity);

	data = q->array[q->front];
	q->array[q->front] = -1;
	if(q->front == q->back)
		q->front = q->back = -1;
	else
	q->front = (q->front + 1) % q->capacity;

	return data;
}


int queue_print(queue *Q)
{
	int i;

	QUEUE_IS_VALID(Q);
	dprintf("\n Printing Queue:");
	for (i = 0; i < Q->capacity; i++) {
		dprintf("%d ", Q->array[i]);
	}
	dprintf("\n");
	return EXIT_SUCCESS;
}

void test_queue_fill_empty(queue *q, int size){
	int i;
	assert(queue_pop(q) == EXIT_FAILURE);
	assert(queue_is_empty(q) == EXIT_SUCCESS);
	for (i = 0; i < size; i++) {
		assert(queue_push(q, i) == EXIT_SUCCESS);
	}
	queue_print(q);

	assert(queue_is_full(q) == EXIT_SUCCESS);
	assert(queue_push(q, i) == EXIT_FAILURE);

	for (i = 0; i < size; i++) {
		assert(queue_pop(q) == i);
	}
	assert(queue_is_empty(q) == EXIT_SUCCESS);
	assert(queue_pop(q) == EXIT_FAILURE);
}

void test_queue()
{
	int i, x;
	int size = 5;

	queue *q = queue_create(size);
	assert(q != NULL);

	test_queue_fill_empty(q, size);
	test_queue_fill_empty(q, size);

	assert(queue_free(&q) ==EXIT_SUCCESS);

}



#ifdef DEBUG
int main(){
	test_queue();
}

#endif

#undef QUEUE_MARKER_MAGIC
#undef QUEUE_IS_VALID
#undef dprintf
