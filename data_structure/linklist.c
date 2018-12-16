/* http://cslibrary.stanford.edu/105/LinkedListProblems.pdf */

#include "../../ds_algo1/data_structure/linklist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#ifdef DEBUG
#define dprintf(frmt,...)  fprintf(stdout, frmt, ##__VA_ARGS__)
#else
#define dprintf(frmt, ...)
#endif



#define RET_ERR_IF_NULL(i) do { if(i == NULL) return EXIT_FAILURE; } while(0)
#define RET_NULL_IF_NULL(i) do { if(i == NULL) return NULL; } while(0)

list_node* new_list_node(int data)
{
	list_node* temp = malloc(sizeof(list_node));
	if(temp == NULL)
		return NULL;
	temp->val = data;
	temp->next = NULL;
	return temp;
}

list_node* new_list_node1(int i)
{
	list_node* temp = calloc(1, sizeof(list_node));
	if(temp == NULL)
			return NULL;
	temp->val = i;
	temp->next = NULL;
	return temp;
}

int list_size(list_node *head)
{
	if(head == NULL)
		return 0;

	int len = 0;
	for(; head; len++, head = head->next);
	return len;
}
/*********************************************************************************************************/
list_node* create_list(int num_node)
{
	list_node* head = new_list_node1(0);
	RET_NULL_IF_NULL(head);

	list_node* ptr = head;
	for (int i = 1; i < num_node; i++) {
		ptr->next = new_list_node1(i);
		ptr = ptr->next;
	}
	return head;
}

list_node* create_list1(int num_node)
{
	list_node* head = calloc(num_node, sizeof(list_node));
	RET_NULL_IF_NULL(head);

	for (int i = 0; i < num_node; i++){
		head[i].next = head+i+1;
		head[i].val = i;
	}

	return head;
}
list_node* get_list_from_arr(int arr[], int num_node)
{
	RET_NULL_IF_NULL(arr);

	if (num_node == 0)
		return NULL;

	list_node* head = new_list_node1(arr[0]);
	list_node* ptr = head;
	for (int i = 1; i < num_node && ptr; i++) {
		ptr->next = new_list_node1(arr[i]);
		ptr = ptr->next;
	}
	return head;
}

int* get_arr_from_list(list_node* head, int* arr_len)
{
	int i = 0;
	int num_node = list_size(head);;
	int* arr = (int*) calloc(num_node, sizeof(int));

	for(i=0; i< num_node && head ; i++, head = head->next){
		arr[i] = head->val;
	}

	assert(i == num_node);
	*arr_len = i;

	return arr;

}

int compare_arr(int arr1[], int arr2[], int arr_len)
{
	RET_ERR_IF_NULL(arr1);
	RET_ERR_IF_NULL(arr2);

	for(int i = 0; i < arr_len; i++){
		if (arr1[i] != arr2[i])
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int compare_list(list_node* list1, list_node* list2)
{
	while (list1 && list2) {
		if (list1->val != list2->val)
			return EXIT_FAILURE;
		list1 = list1->next;
		list2 = list2->next;
	}

	if (list1 || list2){
		dprintf(" length mismatch");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int compare_list_arr(list_node* list1, int arr[], int num_node)
{
	list_node* list2 = get_list_from_arr(arr, num_node);
	return compare_list(list1, list2);
}


void print_arr(int* arr, int arr_len)
{
	dprintf("( Len: %d Arr: ", arr_len);
	if (arr_len < 10) {
		for (int i = 0; i < arr_len; i++) {
			dprintf("%d ", arr[i]);
		}
	} else {
		dprintf("%d %d ... %d", arr[0], arr[1], arr[arr_len - 1]);
	}
	dprintf(")");
}

void print_list(list_node* head, char* msg)
{
	dprintf("%s ", msg);
	for (; head; head = head->next)
		dprintf(" %d", head->val);
	dprintf("\n");
}

void print_list1(list_node *head)
{
	while (head) {
		dprintf(" %d", head->val);
		head = head->next;
	}
	dprintf("\n");
}

void del_list(list_node* head)
{
	while (head) {
		list_node *temp = head->next;
		head->next = NULL;
		free(head);
		head = temp;
	}
}

void del_list_recur(list_node* head)
{
	if (head == NULL)
		return;
	del_list(head->next);
	free(head);
}

void del_list1(list_node** head_ref)
{
	del_list_recur(*head_ref);
	*head_ref = NULL;
}


list_node* reverse_list(list_node* head)
{
	list_node* rev_head = NULL, *temp;
	while (head) {
		temp = head->next;
		head->next = rev_head;
		rev_head = head;
		head = temp;
	}
	return rev_head;
}
//TODO improve this
static void reverse_list_recur1_(list_node* head, list_node** rev_head){
	if(head == NULL)
		return;

	list_node* temp = head->next;
	head->next = *rev_head;
	*rev_head = head;
	head = temp;

	reverse_list_recur1_(head, rev_head);
}
list_node* reverse_list_recur1(list_node* head){
	RET_NULL_IF_NULL(head);

	list_node* new_head = NULL;
	reverse_list_recur1_(head, &new_head);
	return new_head;
}

static list_node* reverse_list_recur2_(list_node* head, list_node** head_ref)
{
	if (head->next == NULL) {
		*head_ref = head;
		return head;
	} else{
		list_node* tail = reverse_list_recur2_(head->next, head_ref);
		tail ->next = head;
		return tail->next;
	}
}

list_node* reverse_list_recur2(list_node* head)
{
	RET_NULL_IF_NULL(head);

	list_node* new_head = NULL;
	list_node* tail = reverse_list_recur2_(head, &new_head);
	tail->next = NULL;
	return new_head;
}

list_node* reverse_list_recur(list_node *list)
{
    if (list == NULL || list->next == NULL)
        return list;
    list_node * revHead = recursiveReverseLL(list->next);
    list->next->next = list;
    list->next = NULL;
    return revHead;
}

list_node* reverse_list_stack(list_node* head){
	int len = list_size();
	list_node* stack = malloc(sizeof(list_node*)*len);
	int top  = -1;

	while(head){
		stack[++top] = head;
		head = head->next;
	}

	list_node* new_head = stack[top--];
	head = new_head;
	while(top > -1){
		new_head->next = stack[top--];
		new_head = new_head->next;
	}
	new_head->next =NULL;
	free(stack);
	return head;
}
//TODO improve reverse recursion

/********************************************************************************************/
int nth_node(list_node* head, int n)
{
	for(int i = 0; i < n && head; i++, head = head->next);

	if (!head)
		return EXIT_FAILURE;

	return head->val;

}

int nth_node_from_last(list_node *head, int n)
{
	RET_ERR_IF_NULL(head);
	int len = list_size(head);
	return nth_node(head, len-1 - n);
}

list_node* nth_node_remove(list_node* head, int n)
{
	RET_NULL_IF_NULL(head);

	list_node *prev = NULL, *head1 = head;
	for (int i = 0; i < n && head1; i++, head1 = head1->next) {
		prev = head1;
	}

	if (prev == NULL)
		return head->next;

	prev->next = prev->next->next;
	return head;
}

list_node* nth_node_from_last_remove(list_node* head, int n)
{
	RET_NULL_IF_NULL(head);

	int len = list_size(head);
	int node_to_del = len-1-n;

	if (n > len)
		return NULL;

	dprintf("%s: %d %d %d \n", __FUNCTION__, node_to_del, len, n);

	return nth_node_remove(head, node_to_del);

}

/************************************************************************************************/
int insert_at_beg(list_node* head, int data)
{
	RET_ERR_IF_NULL(head);

	list_node* temp = new_list_node(head->val);
	RET_ERR_IF_NULL(temp);

	temp->next = head->next;

	head->val = data;
	head->next = temp;

	return EXIT_SUCCESS;
}

int insert_at_end(list_node *head, int data)
{
	RET_ERR_IF_NULL(head);

	list_node* temp = new_list_node(data);
	RET_ERR_IF_NULL(temp);

	while (head->next) {
		head = head->next;
	}

	head->next = temp;

	return EXIT_SUCCESS;
}

int insert_at_pos(list_node* head, int data, int pos)
{
	RET_ERR_IF_NULL(head);

	list_node* prev = NULL, *head1 = head;
	for(int i = 0; i < pos && head1; i++, head1 = head1->next){
		//dprintf(" %d %d ", i , head1->val);
		prev = head1;
	}

	if(prev == NULL){
		return insert_at_beg(head, data);
	}

	list_node* temp = new_list_node(data);
	RET_ERR_IF_NULL(temp);

	temp->next = head1;
	prev->next = temp;

	return EXIT_SUCCESS;
}



list_node* insert(list_node *head, int data, int pos)
{

	list_node* temp = new_list_node(data);
	RET_NULL_IF_NULL(temp);

	list_node* prev = NULL, *head1 = head;
	for(int i = 0; i < pos && head1; i++, head1 = head1->next){
		prev = head1;
	}

	if(prev == NULL){
		temp->next = head;
		return temp;
	}

	temp->next = head1;
	prev->next = temp;

	return head;

}
/************************************************************************************************/


list_node* find(list_node* head, int data)
{
	while (head) {
		if (head->val == data)
			break;
		head = head->next;
	}

	return head;
}

list_node* sort_list(list_node *head)
{
	for(list_node *i = head; i; i = i->next){
		for(list_node *j = head; j && j->next; j = j->next){
			if(j->val > j->next->val){
				int temp = j->next->val;
				j->next->val = j->val;
				j->val = temp;
			}
		}
	}
	/*list_node *i = head;
	while (i) {
		list_node *j = head;
		while (j && j->next) {
			if (j->val > j->next->val) {
				int temp = j->next->val;
				j->next->val = j->val;
				j->val = temp;
			}
			j = j->next;
		}
		i = i->next;
	}*/
	return head;
}

void list_front_back_split(list_node *head, list_node** front, list_node **back)
{

	list_node *slow = head;
	list_node *fast = head->next;

	while (fast) {
		fast = fast->next;
		if (fast) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*front = head;
	*back = slow->next;
	slow->next = NULL;
}

list_node* merge_sorted(list_node *a, list_node *b)
{
	list_node dummy_head , *cptr = &dummy_head;

	while (a && b) {
		if (a->val < b->val) {
			cptr->next = a;
			a = a->next;
		} else {
			cptr->next = b;
			b = b->next;
		}

		cptr = cptr->next;
	}

	if (a) {
		while (a) {
			cptr->next = a;
			a = a->next;
			cptr = cptr->next;
		}
	}

	if (b) {
		while (b) {
			cptr->next = b;
			b = b->next;
			cptr = cptr->next;
		}
	}
	//print_list1(dummy_head->next);
	return dummy_head.next;
}

list_node* merge_sort(list_node *head)
{

	if (head == NULL)
		return NULL;
	if (head->next == NULL)
		return head;

	list_node *front, *back;
	list_front_back_split(head, &front, &back);
	front = merge_sort(front);
	back = merge_sort(back);
	return merge_sorted(front, back);
}


/************************************************************************************************/
list_node* k_reverse(list_node* head, int k)
{
	list_node dummy_head = {0, head};
	list_node *list_tail = &dummy_head;
	while(head){
		list_node* rev_head = NULL, *rev_tail = head, *temp;
		for(int i = 0; i < k && head; i++){
			temp = head->next;
			head->next = rev_head;
			rev_head = head;
			head = temp;
		}
		list_tail->next = rev_head;
		list_tail = rev_tail;
	}
	return dummy_head.next;
}

static void k_reverse_rec(list_node* head, int k, list_node* new_tail)
{
	if(head == NULL)
			return;
	list_node *tail = head,* rev_head = NULL,  *temp;
	for(int i = 0; i < k && head; i++){
		temp = head->next;
		head->next = rev_head;
		rev_head = head;
		head = temp;
	}
	new_tail->next = rev_head;
	k_reverse_rec(head, k, tail);
}

list_node* k_reverse1(list_node* head, int k)
{
	list_node dummy_head = {0, head};
	list_node *list_tail = &dummy_head;
	k_reverse_rec(head, k, list_tail);
	return dummy_head.next;
}

list_node* k_reverse_rec1(list_node* head, int k)
{
	if(head == NULL)
		return NULL;

	list_node* prev = NULL, *curr_head = head;
	for(int i = 0; i < k && head; i++, head = head->next)
		prev = head;
	prev->next = NULL;

	list_node* new_head = reverse_list(curr_head);

	curr_head->next = k_reverse_rec1(head, k);

	return new_head;


}

list_node* k_sort(list_node* head, int k)
{
	list_node dummy_head = {0, head};
	list_node *list_tail = &dummy_head;

	while (head) {
		int i = 0;
		list_node *prev = NULL, *curr_head = head;
		for(int i = 0; i < k && head; i++, head = head->next)
			prev = head;
		prev->next = NULL;

		list_tail->next = merge_sort(curr_head);

		while (list_tail->next)
			list_tail = list_tail->next;

	}

	return dummy_head.next;
}

static void k_sort_rec(list_node* head, int k, list_node* new_tail){
	int i = 0;

	if(head == NULL)
			return;

	list_node *prev = NULL, *curr_head = head;
	for(int i = 0; i < k && head; i++, head = head->next)
		prev = head;
	prev->next = NULL;

	new_tail->next = merge_sort(curr_head);

	while (new_tail->next)
		new_tail = new_tail->next;

	k_sort_rec(head, k, new_tail);

}
list_node* k_sort1(list_node* head, int k)
{
	list_node dummy_head = {0, head};
	list_node *list_tail = &dummy_head;
	k_sort_rec(head, k, list_tail);
	return dummy_head.next;
}

list_node* k_sort_rec1(list_node* head, int k){
	RET_NULL_IF_NULL(head);

	list_node *prev = NULL, *curr_head = head;
	for(int i = 0; i < k && head; i++, head = head->next)
		prev = head;
	prev->next = NULL;

	curr_head = merge_sort(curr_head);

	list_node *curr_tail = curr_head;
	while (curr_tail->next)
		curr_tail = curr_tail->next;
	curr_tail->next = k_sort_rec1(head, k);

	return curr_head;

}
/************************************************************************************************/
list_node* copy_list(list_node* head)
{
	list_node dummy = { 0, NULL };
	list_node* tail = &dummy;
	while (head) {
		tail->next = new_list_node1(head->val);
		head = head->next;
		tail = tail->next;
	}
	tail->next = head;
	print_list(dummy.next, " hello");
	return dummy.next;
}

list_node* copy_list_n(list_node* head, int n)
{
	list_node dummy = { 0, NULL };
	list_node* tail = &dummy;
	int i = 0;
	while (head && i < n) {
		tail->next = new_list_node1(head->val);
		head = head->next;
		tail = tail->next;
		i++;
	}
	return dummy.next;
}

list_node* copy_sub_list_n(list_node* head, int beg, int end)
{
	list_node dummy = { 0, NULL };
	list_node* tail = &dummy;
	int i = 0;
	while (head && i < end) {
		if (i >= beg && i < end) {
			tail->next = new_list_node1(head->val);
			tail = tail->next;
		}
		i++;
		head = head->next;
	}
	return dummy.next;
}
list_node* sub_list(list_node** head_ref, int start, int end)
{
	int i = 0;
	list_node* head = *head_ref, *temp , *prev = NULL;
	for (; head && i < start; i++, head = head->next){
		prev = head;
	}
	for (; head && i < end; i++, head = head->next);

	if(prev == NULL){
		temp = *head_ref;
		*head_ref = head->next;
		if(head->next)
			head->next = NULL;
		return temp;
	}

	temp = prev->next;
	prev->next = head->next;
	if(head->next)
		head->next = NULL;

	return temp;
}


void split_list(list_node* head, list_node** first, list_node** secnd)
{
	list_node fst = { 0, NULL }, *ptr1 = &fst;
	list_node scnd = { 0, NULL }, *ptr2 = &scnd;
	list_node *temp;

	while (head) {
		temp = head->next;
		if (head->val % 2 == 0) {
			ptr1->next = head;
			ptr1 = ptr1->next;
			if (!head->next)
				ptr2->next = NULL;
		} else {
			ptr2->next = head;
			ptr2 = ptr2->next;
			if (!head->next)
				ptr1->next = NULL;
		}
		head = temp;
	}
	*first = fst.next;
	*secnd = scnd.next;
}

/************************************************************************************************/

list_node* rotate_left(list_node* head, int n){
	RET_NULL_IF_NULL(head);

	list_node *head1 = head, *prev = NULL;
	for(int i = 0; i < n && head1; i++, head1 = head1->next)
		prev = head1;

	if(prev == NULL)
		return head;

	assert(head != NULL);

	while(head1->next)
		head1 = head1->next;

	head1->next = head;
	head = prev->next;
	prev->next = NULL;

	return head;

}

list_node* rotate_right(list_node* head, int n)
{
	int len = list_size(head);
	n = n % len;
	return rotate_left(head, len-n);
}

list_node* reverse_between(list_node* head, int B, int C)
{

	int i = 0;
	list_node* prev = NULL, *head1 = head;
	for(; i < B && head1; i++, head1 = head1->next){
		prev = head1;
	}

	list_node* rev_head = NULL, *rev_tail = head1, *temp;
	while(i <= C && head1){
		temp = head1->next;
		head1->next = rev_head;
		rev_head = head1;
		head1 = temp;
		i++;
	}
	rev_tail->next = head1;

	if(prev == NULL)
		return rev_head;

	prev->next = rev_head;
	return head;

}


list_node* reverse_between1(list_node* head, int beg, int end)
{
	RET_NULL_IF_NULL(head);

	int i = 0;
	list_node* prev = NULL, *head1 = head;
	for(;head1 && i< beg; i++, head1 = head1->next)
		prev = head1;

	dprintf(" i =  %d ptr = %d", i, prev->val);

	list_node* rev_tail = head1;
	list_node* rev_head = NULL, *temp;
	while (head1 && i < end - 1) {
		temp = head1->next;
		head1->next = rev_head;
		rev_head = head1;
		head1 = temp;
		i++;
	}

	rev_tail->next = head1;

	if(prev == NULL)
		return rev_head;

	prev->next = rev_head;
	return head;

}

/*********************************************************************************************************/
//TODO improve the test cases
#define print_test_input_log(arr, arr_len)   do{\
                printf(" %s ", __FUNCTION__); \
                print_arr(arr, arr_len); \
                printf(" passed\n"); \
            } while(0) \


typedef void (*test_function)(int* arr1, int arr1_len);

void execute_test(test_function test_fn)
{

	int arr1[] = { 1, 2, 3, 4, 5, 6, 7 };
	int arr1_len = 7;
	int i = 0;

	test_fn(arr1, arr1_len);

	int arr2[] = { 1 };
	int arr2_len = 1;

	test_fn(arr2, arr2_len);

	int arr3[] = { };
	int arr3_len = 0;

	test_fn(arr3, arr3_len);

	int arr4[] = { 1, 2, 3, 4, 5, 6, 7 };
	int arr4_len = 5;
	test_fn(arr4, arr4_len);

	int arr5[] = { 1, 2, 3, 4, 5, 6, 7 };
	int arr5_len = 10;
	test_fn(arr5, arr5_len);

	int arr6_len = 10000;
	int* arr6;

	arr6 = (int*) calloc(arr6_len, sizeof(int));
	for (i = 0; i < arr6_len; i++) {
		arr6[i] = i;
	}
	test_fn(arr6, arr6_len);
}

void test_basic_ops(int arr1[], int arr1_len)
{

	int* arr2;
	int arr2_len;

	list_node * list1 = get_list_from_arr(arr1, arr1_len);
	int list_len1 = list_size(list1);
	assert(arr1_len == list_len1);

	arr2 = get_arr_from_list(list1, &arr2_len);
	assert(arr2_len == list_len1);

	list_node * list2 = get_list_from_arr(arr2, arr2_len);
	int list_len2 = list_size(list1);
	assert(arr2_len == list_len2);

	assert(compare_list(list1, list2) == EXIT_SUCCESS);
	assert(compare_arr(arr1, arr2, arr2_len) == EXIT_SUCCESS);

	print_test_input_log(arr1, arr1_len);

}

typedef list_node* (*reverse_func_t)(list_node*);


void test_reverse(int* arr, int arr_len)
{
	reverse_func_t func_list[3];
	func_list[0] = reverse_list_recur2;
	func_list[1] = reverse_list_recur1;
	func_list[2] =  reverse_list;
	func_list[3] =  reverse_list_recur;
	func_list[4] =  reverse_list_stack;

	for(int i = 0; i <5; i++){
		list_node* list2 = get_list_from_arr(arr, arr_len);
		list_node* list3 = func_list[i](list2);
		list_node* list4 = func_list[i](list3); //double reverse
		assert(compare_list(list2, list4) == 0);
		dprintf(" %d", i);
		print_test_input_log(arr, arr_len);
	}

}
void test_nth_node(){

	int arr[] = {1,2,3,4,5};
	int arr_len = 5;

	list_node *list1 = get_list_from_arr(arr,arr_len);

	assert(nth_node(list1, 0) == 1);
	assert(nth_node(list1, 4) == 5);

	assert(nth_node_from_last(list1, 0) == 5);
	assert(nth_node_from_last(list1, 4) == 1);

	assert(nth_node_remove(list1, 0) == list1->next);
	assert(nth_node_remove(list1, 4) == list1);
	print_list1(list1);
	//assert(nth_node(list1, 2) == 4);

	assert(nth_node_from_last_remove(list1, 0) == list1);
	//assert(nth_node(list1, 3) == 4);
	//TODO fail assert(nth_node_from_last_remove(list1, 4) == list1->next);
	//print_list1(list1);
	//assert(nth_node(list1, 0) == 2);
	print_test_input_log(arr, arr_len);

}

int test_insert()
{

	int arr[] = {1,2,3,4,5,6};
	int arr_len = 6;
	assert(insert_at_beg(NULL, 2) == EXIT_FAILURE);

	list_node *head = new_list_node(2);
	assert(head != NULL);

	//assert(insert_at_beg(head, 2) == EXIT_SUCCESS);
	assert(insert_at_beg(head, 1) == EXIT_SUCCESS);
	assert(compare_list_arr(head, arr, 2) == EXIT_SUCCESS);

	assert(insert_at_pos(head, 3, 2) == EXIT_SUCCESS);
	assert(insert_at_pos(head, 4, 3) == EXIT_SUCCESS);
	print_list1(head);
	assert(compare_list_arr(head, arr, 4) == EXIT_SUCCESS);

	assert(insert_at_end(head, 5) == EXIT_SUCCESS);
	assert(insert_at_end(head, 6) == EXIT_SUCCESS);
	print_list1(head);

	assert(compare_list_arr(head, arr, arr_len) == EXIT_SUCCESS);
	del_list1(&head);

	head = insert(head, 2,0);
	head = insert(head, 1,0);

	head = insert(head, 5, 2);
	head = insert(head, 6, 3);

	head = insert(head, 3, 2);
	head = insert(head, 4, 3);
	print_list1(head);
	assert(compare_list_arr(head, arr, arr_len) == EXIT_SUCCESS);
	print_test_input_log(arr, arr_len);
	return 0;
}

int compare(const void* a, const void* b){
	return (*((int*)a)) < (*((int*)b));
}

void sort_arr(int arr[], int arr_len){
	qsort(arr, arr_len, sizeof(int), compare);
}

typedef list_node* (*sort_func_t)(list_node*);

void test_list_sort(int* arr , int arr_len)
{
	sort_func_t sort_funcs[2];
	sort_funcs[0] = sort_list;
	sort_funcs[1] = merge_sort;

	if(arr_len >= 10) // skip negative call
		return;

	int *arr2 = malloc(sizeof(int)*arr_len);
	for(int i = 0; i < arr_len; i++ )
		arr2[i] = arr[i];
	sort_arr(arr2, arr_len);
	print_arr(arr2, arr_len);


	for(int i =0; i < 2; i++){
		list_node *head = get_list_from_arr(arr, arr_len);

		sort_funcs[0](head);
		print_list1(head);

		assert(compare_list_arr(head, arr, arr_len) == EXIT_SUCCESS);
		dprintf(" %d",i);
		print_test_input_log(arr, arr_len);
		del_list1(&head);

	}
}

typedef list_node* (*k_opr_fun_t)(list_node* head, int k);
void test_k_reverse(){

	int arr[] = {1,2,3,4,5,6,7,8,9};
	int arr2[] = {3,2,1,6,5,4,9,8,7};
	int arr_len = 9;
	int k= 3;

	k_opr_fun_t sort_funcs[4];
	sort_funcs[0] = k_reverse;
	sort_funcs[1] = k_reverse1;
	sort_funcs[2] = k_reverse_rec1;

	for(int i = 0; i< 3; i++){
		list_node* list1 = get_list_from_arr(arr, arr_len);
		list_node* list2 = sort_funcs[i](list1, k);
		print_list1(list1);
		print_list1(list2);
		assert(compare_list_arr(list2, arr2, arr_len) == EXIT_SUCCESS);
		dprintf(" %d",i);
		print_test_input_log(arr, arr_len);
		del_list1(&list1);
	}


}

void test_k_sort(){

	int arr[] = {3,2,1,6,5,4,9,8,7};
	int arr2[] = {1,2,3,4,5,6,7,8,9};
	int arr_len = 9;
	int k= 3;

	k_opr_fun_t sort_funcs[4];

	sort_funcs[0] = k_sort;
	sort_funcs[1] = k_sort1;
	sort_funcs[2] = k_sort_rec1;

	for(int i = 0; i< 3; i++){
		list_node* list1 = get_list_from_arr(arr, arr_len);
		list_node* list2 = sort_funcs[i](list1, k);
		print_list1(list1);
		print_list1(list2);
		assert(compare_list_arr(list2, arr2, arr_len) == EXIT_SUCCESS);
		dprintf(" %d",i);
		print_test_input_log(arr, arr_len);
		del_list1(&list1);
	}

}

void test_copy_list(){
	int arr[] = {1,2,3,4,5,6,7,8,9};
	int arr2[] = {3,4,5,6,7,8};
	int arr_len = 9;

	list_node* list1 = get_list_from_arr(arr, arr_len);
	print_list1(list1);
	list_node* list2 = copy_list(list1);
	print_list1(list2);
	list_node* list3 = copy_list_n(list1, 4);
	list_node* list4 = copy_sub_list_n(list1, 2, 6);

	assert(compare_list(list2,list1) == EXIT_SUCCESS);
	assert(compare_list_arr(list3, arr, 4) == EXIT_SUCCESS);
	assert(compare_list_arr(list4, arr2, 4) == EXIT_SUCCESS);
	list_node* list5 = sub_list(&list1, 2, 6);
	print_list1(list5);
	assert(compare_list_arr(list5, arr2, 5) == EXIT_SUCCESS);


	del_list_recur(list1);
	del_list_recur(list2);
	del_list_recur(list3);
	del_list_recur(list4);
	del_list_recur(list5);

	print_test_input_log(arr, arr_len);
}


void test_rotate()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int arr2[] = { 4, 5, 6, 7, 8, 9, 1, 2, 3 };
	int arr3[] = { 6, 7, 8, 9, 1, 2, 3, 4, 5 };
	int arr_len = 9;

	list_node* list1 = get_list_from_arr(arr, arr_len);
	list_node* list2 = rotate_left(list1, 3);
	print_list(list2, (char*)__FUNCTION__);
	assert(compare_list_arr(list2, arr2, 9) == EXIT_SUCCESS);
	del_list_recur(list2);

	list1 = get_list_from_arr(arr, arr_len);
	list2 = rotate_right(list1, 4);
	print_list1(list2);
	assert(compare_list_arr(list2, arr3, 9) == EXIT_SUCCESS);

	del_list_recur(list2);
	print_test_input_log(arr, arr_len);

}



void test_reverse_between()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int arr2[] = { 1, 2, 5,4,3, 6, 7, 8, 9 };
	int arr_len = 9;

	list_node* list1 = get_list_from_arr(arr, arr_len);
	list_node* list2 = reverse_between(list1, 2,4);
	print_list(list2, (char*)__FUNCTION__);
	assert(compare_list_arr(list2, arr2, arr_len) == EXIT_SUCCESS);

	print_test_input_log(arr, arr_len);
}

void test_list(){
	execute_test(test_basic_ops);
	execute_test(test_reverse);
	test_nth_node();
	test_insert();
	execute_test(test_list_sort);
	test_k_reverse();
	test_k_sort();
	test_copy_list();
	test_rotate();
	test_reverse_between();

}
/************************************************************************************************/
int main()
{
	test_list();

}

