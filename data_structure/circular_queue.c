/* gcc -D DEBUG circular_queue.c  */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG 1
#ifdef DEBUG
#define dprintf(frmt,...)  fprintf(stdout, frmt, ##__VA_ARGS__)
#else
#define dprintf(frmt, ...)
#endif

#define  MAX_QUEUE_SIZE  5

static int qdata[MAX_QUEUE_SIZE] = { 0 };
static int front_idx = -1, back_idx = -1;

int empty()
{
	dprintf(" %s F:%d B%d \n", __FUNCTION__, front_idx, back_idx);
	if (front_idx == -1 && back_idx == -1) {
		dprintf(" Queue Empty \n");
		return 1;
	}
	return 0;
}

int full()
{
	dprintf(" %s F:%d B%d \n", __FUNCTION__, front_idx, back_idx);
	int check1 = (front_idx == 0) && (back_idx == MAX_QUEUE_SIZE - 1);
	int check2 = front_idx == (back_idx + 1);
	if (check1 || check2) {
		dprintf(" Queue Full \n");
		return 1;
	}
	return 0;
}

int push(int data)
{
	if (full())
		return EXIT_FAILURE;

	qdata[(++back_idx) % MAX_QUEUE_SIZE] = data;
	back_idx = back_idx % MAX_QUEUE_SIZE;

	if (front_idx == -1)
		front_idx = 0;

	return EXIT_SUCCESS;
}

int pop()
{
	if (empty())
		return EXIT_FAILURE;

	int data = qdata[front_idx];

	if (front_idx == back_idx) {
		front_idx = -1;
		back_idx = -1;
	}
	else
		front_idx = (front_idx+1) % MAX_QUEUE_SIZE;


	return data;
}

void printq()
{
	if (empty())
		return;

	dprintf("%d %d :", front_idx, back_idx);
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
		dprintf(" %d", qdata[i]);
	dprintf("\n");
}

void cycle_the_queue()
{
	int qsize = MAX_QUEUE_SIZE;
	// push n element
	assert(empty());
	for (int i = 0; i < qsize; i++)
		assert(push(i) == EXIT_SUCCESS);
	assert(full());
	assert(push(0) == EXIT_FAILURE);

	// pop and push n/2 elements
	for (int i = 0; i < qsize / 2; i++)
		pop(i);
	assert(!full());
	for (int i = 0; i < qsize / 2; i++)
		assert(push(i) == EXIT_SUCCESS);

	// pop and push n-1 element
	assert(full());
	for (int i = 0; i < qsize-1; i++)
			pop(i);
	assert(!full());
	for (int i = 0; i < qsize-1; i++)
		assert(push(i) == EXIT_SUCCESS);

	// pop n element
	for (int i = 0; i < qsize; i++)
		pop(i);
	assert(empty());
}

void test_cycle_the_queue()
{
	int qsize = MAX_QUEUE_SIZE;
	for (int i = 0; i < qsize; i++) {
		cycle_the_queue();
	}
}
void k_push_pop(int n)
{
	assert(empty());
	for (int i = 0; i < n; i++)
		assert(push(i) == EXIT_SUCCESS);

	for (int i = 0; i < n; i++)
		assert(pop() == i);
	assert(empty());
}
void test_queue2()
{
	for (int i = 1; i <= MAX_QUEUE_SIZE; i++)
		k_push_pop(i);
}
#ifdef DEBUG
int main()
{
	test_queue2();
	test_cycle_the_queue();

}
#endif
/* Resize have cache hit and copy overhead */
