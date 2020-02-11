/*gcc -DDEBUG .\queue.c -lpthread*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#include "queue.h"

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
	pthread_mutex_t lock;
} queue;

unsigned int queue_num_avail(queue *q)
{
	if (q->front == -1)
		return q->capacity;

	if (q->front == (q->back + 1) % q->capacity)
		return 0;

	if (q->back > q->front)
		return q->capacity - (q->back + 1) + q->front ;

	if (q->back < q->front)
		return q->front - (q->back +1);

	return q->capacity -1;
}

unsigned int queue_num_filled(queue *q)
{
	if (q->front == -1)
		return 0;

	if (q->front == (q->back + 1) % q->capacity)
		return q->capacity;

	if (q->back > q->front)
		return q->back - q->front + 1;

	if (q->back < q->front)
		return q->capacity - q->front +  q->back;

	return 1;

}

queue* queue_create(unsigned capacity)
{
	queue* newQ = (queue*)calloc(1, sizeof(queue));
	if (newQ == NULL)
		return NULL;

	newQ->array = (int*)calloc(capacity, sizeof(int));
	if (newQ->array == NULL) {
		free(newQ);
		return NULL;
	}

	newQ->front = -1;
	newQ->back = -1;
	newQ->magic = QUEUE_MARKER_MAGIC;
	newQ->capacity = capacity;
	pthread_mutex_init(&newQ->lock, NULL);
	return newQ;
}
int queue_free(queue **q_ref){

	queue *q = *q_ref;
	pthread_mutex_destroy(&q->lock);
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
		return EXIT_FAILURE;
	}

	pthread_mutex_lock(&q->lock);

	if(q->back == -1)
		q->front = 0;
	q->back = (q->back + 1) % q->capacity;
	q->array[q->back] = data;

	pthread_mutex_unlock(&q->lock);

	dprintf("\n:Added: FRONT:%d Rear:%d DATA %d", q->front,q->back,q->array[q->back] );
	return EXIT_SUCCESS;
}

int queue_push_batch(queue *q, int* data, int len)
{
	int avail;
	QUEUE_IS_VALID(q);

	avail = queue_num_avail(q);

	if(avail < len)
		return EXIT_FAILURE;

	pthread_mutex_lock(&q->lock);

	if(q->back == -1)
		q->front = 0;

	for (int i = 0; i < len; i++) {
		q->back = (q->back + 1) % q->capacity;
		q->array[q->back] = data[i];
	}

	pthread_mutex_unlock(&q->lock);

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

	pthread_mutex_lock(&q->lock);

	data = q->array[q->front];
	q->array[q->front] = -1;
	if(q->front == q->back)
		q->front = q->back = -1;
	else
		q->front = (q->front + 1) % q->capacity;

	pthread_mutex_unlock(&q->lock);

	return data;
}

int queue_pop_batch(queue *q, int* data, int len)
{
	int fill;

	QUEUE_IS_VALID(q);

	fill = queue_num_filled(q);

	if (fill < len)
		return EXIT_FAILURE;

	dprintf("\n:Removing: FRONT: %d Rear:%d SIZE:%d ", q->front, q->back, q->capacity);

	pthread_mutex_lock(&q->lock);

	for (int i = 0; i < len; i++) {
		data[i] = q->array[q->front];
		q->array[q->front] = -1;
		if(q->front == q->back)
			q->front = q->back = -1;
		else
			q->front = (q->front + 1) % q->capacity;
	}
	pthread_mutex_unlock(&q->lock);

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
