#ifndef __queue
#define __queue

typedef struct _queue queue;

queue* queue_create(unsigned capacity);
int queue_free(queue**);

int queue_is_empty(queue *q);
int queue_is_full(queue *q);

int queue_push(queue *q, int data);
int queue_pop(queue *q);

int queue_print(queue *Q);

#endif
