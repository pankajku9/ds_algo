#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void heapify(int* heap, int size, int i)
{
	//printf(" %s %d \n", __FUNCTION__, i);
	int max = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < size && heap[max] < heap[left]) {
		max = left;
	}

	if (right < size && heap[max] < heap[right]) {
		max = right;
	}

	if (max != i) {
		int temp = heap[i];
		heap[i] = heap[max];
		heap[max] = temp;
		heapify(heap, size, max);
	}
}

void make_heap(int* heap, int size)
{
	for (int i = (size - 1) / 2; i >= 0; i--) {
		heapify(heap, size, i);
	}
}

int pop_heap(int* heap, int size)
{
	int max = heap[0];
	heap[0] = heap[size - 1];
	heapify(heap, size - 1, 0);
	return max;
}

void push_heap(int* heap, int size, int data)
{
	heap[size] = data;
	heapify(heap, size, size);
}

void print_arr(int* arr, int arr_len)
{
	printf("( Len: %d Arr: ", arr_len);
	for (int i = 0; i < arr_len; i++) {
		printf("%d ", arr[i]);
	}

	printf(")");
}

void test_heap()
{
	int arr[] = { 1, 2, 8, 9, 13, 16 };
	make_heap(arr, 6);
	print_arr(arr, 6);
	assert(pop_heap(arr, 6) == 16);
	assert(pop_heap(arr, 5) == 13);
	push_heap(arr, 4, 6);
	assert(pop_heap(arr, 5) == 9);
	assert(pop_heap(arr, 4) == 8);
}

int main()
{
	test_heap();
}
