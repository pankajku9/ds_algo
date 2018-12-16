/* gcc -g3 -D DEBUG linear_queue.c  */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#ifdef DEBUG
#define dprintf(frmt,...)  fprintf(stdout, frmt, ##__VA_ARGS__)
#else
#define dprintf(frmt, ...)
#endif

#define  MAX_QUEUE_SIZE  5
int qdata[MAX_QUEUE_SIZE];
int front_idx = -1, back_idx = -1;

int empty()
{
	if (front_idx == -1) {
		dprintf(" Queue empty \n");
		return 1;
	}
	return 0;
}

int full()
{
	if (back_idx == MAX_QUEUE_SIZE - 1) {
		dprintf(" Queue full \n");
		return 1;
	}
	return 0;
}

int push(int d)
{
	if (full())
		return EXIT_FAILURE;

	//first element
	if (back_idx == -1)
		front_idx++;

	qdata[++back_idx] = d;
	return EXIT_SUCCESS;
}

int pop()
{
	if (empty())
		return EXIT_FAILURE;

	int data = qdata[front_idx++];

	// last element
	if (front_idx > back_idx) {
		front_idx = back_idx = -1;
	}

	return data;
}

void printq()
{
	dprintf("%2d %2d :", front_idx, back_idx);
	if (front_idx == -1) {
		dprintf("\n");
		return;
	}

	for (int i = front_idx; i <= back_idx; i++)
		dprintf(" %d", qdata[i]);

	dprintf("\n");
}

void test_queue0()
{
	assert(empty());
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		assert(push(i) == EXIT_SUCCESS);

	}
	printq();
	assert(full());
	assert(push(0) == EXIT_FAILURE);

	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		assert(pop() == i);

	}
	assert(pop() == EXIT_FAILURE);
	assert(empty());
}

void test_queue1(int n)
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
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
		test_queue1(i);
}

#ifdef DEBUG
int main() {
	test_queue0();
	test_queue2();
}
#endif
