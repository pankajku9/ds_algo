#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define RET_ERR_IF_NULL(i) do { if(i == NULL) return EXIT_FAILURE; } while(0)
#define RET_NULL_IF_NULL(i) do { if(i == NULL) return NULL; } while(0)
#define MIN_NODES 10
/********************************************************************************************************/

typedef struct tree_node_{
	struct tree_node_* left;
	struct tree_node_* right;
	int val;
}tree_node;

void print_arr(int* arr, int arr_len);
void print_tree(tree_node* root);

/*********************************************************************************************************/
tree_node* new_tree_node(int i)
{
	tree_node* new = malloc(sizeof(tree_node));
	if(!new)
		exit(0);
	new->val = i;
	new->left = new->right = NULL;
	return new;
}

tree_node* insert_node(tree_node* root, int val)
{
	if(!root)
		return new_tree_node(val);

	tree_node** queue = calloc(MIN_NODES, sizeof(tree_node*));
	RET_NULL_IF_NULL(queue);
	int back = -1, front = 0, size = MIN_NODES;
	queue[++back] = root;

	while(front <= back && queue[front]) {
		tree_node* curr = queue[front++];
		if(!curr->left){
			curr->left = new_tree_node(val);
			break;
		}else
			queue[++back] = curr->left;

		if(!curr->right){
			curr->right = new_tree_node(val);
			break;
		}else
			queue[++back] = curr->right;

		if (back == size-2) {
			int new_size = 2 * size * (sizeof(tree_node*));
			tree_node**  temp = (tree_node**)realloc(queue, new_size);
			RET_NULL_IF_NULL(temp);
			queue = temp;
			size = 2 * size;
		}
	}
	free(queue);
	return root;
}

tree_node* create_tree(int* arr, int n)
{
	tree_node* root = NULL;
	for(int i = 0; i < n ; i++)
		root = insert_node(root, arr[i]);
	return root;
}

void delete_tree(tree_node* root)
{
	if(root == NULL)
		return;
	delete_tree(root->left);
	delete_tree(root->right);
	free(root);
}

int count_nodes(tree_node* root)
{
	tree_node** stack = calloc(MIN_NODES, sizeof(tree_node*));
	int size = MIN_NODES;
	int top =-1;
	int count = 0;
	stack[++top] = root;

	while(top > -1 && stack[top]){
		tree_node* curr = stack[top--];
		count++;

		if(curr->left)
			stack[++top] = curr->left;

		if(curr->right)
			stack[++top] = curr->right;

		if(top == size-2){
			stack = realloc(stack, 2*size*sizeof(tree_node*));
			size = 2*size;
		}
	}
	free(stack);
	return count;
}

int travrs_nodes_level_order(tree_node* root, int* nodes, int* count_ret)
{
	int front = 0, back = -1, size = MIN_NODES , count = 0;
	tree_node** queue = calloc(MIN_NODES, sizeof(tree_node*));
	queue[++back] = root;

	while (front <= back && queue[front])
	{
		tree_node* curr = queue[front++];
		nodes[count++] = curr->val;

		if (curr->left){
			queue[++back] = curr->left;
		}

		if (curr->right){
			queue[++back] = curr->right;
		}

		if (back == size-2) {
			int new_size = 2 * size* (sizeof(tree_node*));
			queue = realloc(queue, new_size);
			size = 2 * size;
			RET_ERR_IF_NULL(queue);
		}
	}

	free(queue);
	*count_ret = count;
	return EXIT_SUCCESS;
}

int travrs_nodes_pre_order(tree_node* root, int* nodes, int* count)
{
	int count_idx = 0, top = -1, size = MIN_NODES;
	tree_node** stack = calloc(size, sizeof(tree_node*));
	RET_ERR_IF_NULL(stack);
	stack[++top] = root;

	while(top > -1 && stack[top]){

		tree_node* curr = stack[top--];
		nodes[count_idx++] = curr->val;

		if(curr->right)
			stack[++top] = curr->right;

		if(curr->left)
			stack[++top] = curr->left;

		if(top == size-2){
			stack = realloc(stack, 2* size* sizeof(tree_node*));
			size = size *2;
		}
	}

	*count = count_idx;
	free(stack);
	return EXIT_SUCCESS;
}

int travrs_nodes_pre_order1(tree_node* root, int* nodes, int* count)
{
	if(root == NULL) return EXIT_FAILURE;

	int count_idx = *count;
	nodes[count_idx] = root->val;
	*count = count_idx +1;

	travrs_nodes_pre_order1(root->left, nodes, count);
	travrs_nodes_pre_order1(root->right, nodes, count);

	return EXIT_SUCCESS;
}
int travrs_nodes_post_order2(tree_node* root, int* nodes, int* count)
{
	if(root == NULL)
		return EXIT_FAILURE;

	travrs_nodes_post_order2(root->left, nodes, count);
	travrs_nodes_post_order2(root->right, nodes, count);

	int count_idx = *count;
	nodes[count_idx] = root->val;
	*count = count_idx +1;

	return EXIT_SUCCESS;
}
int travrs_nodes_post_order1(tree_node* root, int* nodes, int* count)
{
	int count_idx = -1, top = -1, size = MIN_NODES;
	tree_node** stack = calloc(size, sizeof(tree_node*));
	RET_ERR_IF_NULL(stack);
	int done = 0;
	tree_node* curr = root;

	while(!done){

		while(curr){
			if(curr->right)
				stack[++top] = curr->right;
			stack[++top] = curr;
			curr = curr->left;
		}

		if(top == -1){
			done = 1;
			break;
		}

		curr = stack[top--];
		if(top > -1 && curr->right == stack[top]){
			tree_node* right = stack[top--];
			stack[++top] = curr;
			curr = right;
		}
		else{
			nodes[++count_idx] = curr->val;
			curr = NULL;
		}

		if(top == size-2){
			stack = realloc(stack, 2* size* sizeof(tree_node*));
			size = size *2;
		}

	}
	*count = count_idx +1;
	free(stack);
	return EXIT_SUCCESS;
}

int travrs_nodes_post_order(tree_node* root, int* nodes, int* count)
{
	int top = -1, top1 = -1, size = MIN_NODES, size1 = MIN_NODES;
	tree_node** stack = calloc(size, sizeof(tree_node*));
	tree_node** stack1 = calloc(size, sizeof(tree_node*));
	RET_ERR_IF_NULL(stack);
	stack[++top] = root;

	while(top > -1 && stack[top]){
		tree_node* curr = stack[top--];
		stack1[++top1] = curr;

		if(curr->left)
			stack[++top] = curr->left;

		if(curr->right)
			stack[++top] = curr->right;

		if(top == size-2){
			stack = realloc(stack, 2* size* sizeof(tree_node*));
			size = size *2;
		}

		if(top1 == size1-2){
			stack1 = realloc(stack1, 2* size1* sizeof(tree_node*));
			size1 = size1 *2;
		}
	}

	int count_idx = 0;
	while(top1 > -1)
		nodes[count_idx++] = stack1[top1--]->val;

	*count = count_idx;

	free(stack);
	free(stack1);
	return EXIT_SUCCESS;
}

int travrs_nodes_in_order1(tree_node* root, int* nodes, int* count)
{
	if(root == NULL) return EXIT_FAILURE;


	travrs_nodes_in_order1(root->left, nodes, count);

	int count_idx = *count;
	nodes[count_idx] = root->val;
	*count = count_idx +1;

	travrs_nodes_in_order1(root->right, nodes, count);

	return EXIT_SUCCESS;
}

int travrs_nodes_in_order(tree_node* root, int* nodes, int* count)
{
	int count_idx = 0, top = -1, size = MIN_NODES;
	tree_node** stack = calloc(size, sizeof(tree_node*));
	RET_ERR_IF_NULL(stack);
	int done = 0;

	tree_node* curr = root;

	while(!done){
		while(curr){
			stack[++top] = curr;
			curr = curr->left;
		}

		if(top == -1){
			done = 1;
			break;
		}

		curr = stack[top--];
		nodes[count_idx++] = curr->val;
		curr = curr->right;

		if(top == size-2){
			stack = realloc(stack, 2* size* sizeof(tree_node*));
			size = size *2;
		}
	}

	*count = count_idx;
	free(stack);
	return EXIT_SUCCESS;
}

/*********************************************************************************************************/
int compare_arr(int* arr1, int* arr2, int len){

	int i = 0;
	while(i < len){
		if(arr1[i] != arr2[i])
			return EXIT_FAILURE;
		i++;
	}
	return EXIT_SUCCESS;
}

void print_tree(tree_node* root){
	if(root == NULL)
		return;
	print_tree(root->left);
	print_tree(root->right);
	printf(" %d", root->val);
}

void print_arr(int* arr, int arr_len)
{
	printf("( Len: %d Arr: ", arr_len);
	if( arr_len < 10){
		for (int i = 0; i < arr_len; i++) {
			printf("%d ", arr[i]);
		}
	}
	else{
		for (int i = 0; i < 6; i++) {
			printf("%d ", arr[i]);
		}
		printf(" ... %d %d", arr[arr_len-2], arr[arr_len-1]);
	}

	printf(")");
}

/************************************************************************************************/

#define log_test_case(arr, arr_len)   do{\
                printf(" %s ", __FUNCTION__); \
                print_arr(arr, arr_len); \
                printf(" passed\n"); \
            } while(0) \


static void test_basic_ops_(int size)
{
	int* arr = calloc(size+1, sizeof(int));
	int* arr1 = calloc(size+1, sizeof(int));
	int num_nodes;

	for(int i = 0; i < size ; i++)
		arr[i] = i+1;

	tree_node* root = create_tree(arr, size);
	if(size > 0)
		assert( root != NULL);

	int count = count_nodes(root);
	assert(count == size);
	assert(travrs_nodes_level_order(root, arr1, &num_nodes) == EXIT_SUCCESS);
	assert(num_nodes == count);

	assert(compare_arr(arr, arr1, size) == EXIT_SUCCESS);

	log_test_case(arr, size);
	free(arr);
	free(arr1);
	delete_tree(root);
}

void test_basic_ops(int max_node){
	for(int i = 1; i <= max_node; i = 2*i){
		test_basic_ops_(i-1);;
	}
}

/**
			1
		/		 \
	2				3
 /	  \			  /	  \
4		5		6		7
 */

typedef int (*traversal_func_t)(tree_node* root, int* nodes, int* count);

void test_inorder_(int* arr, int* arr2, int size)
{
	traversal_func_t funcs[2];
	funcs[0] = travrs_nodes_in_order;
	funcs[1] = travrs_nodes_in_order1;

	int count, *nodes;
	for (int i = 0; i < 2; i++) {
		tree_node * root = create_tree(arr, size);
		print_tree(root);

		int num_nodes = count_nodes(root);
		assert(size == num_nodes);
		nodes = malloc(sizeof(int)*num_nodes);

		count = 0;
		funcs[i](root, nodes,&count);
		print_arr(nodes, count);
		assert(count == num_nodes);
		assert(compare_arr(arr2, nodes, num_nodes) == EXIT_SUCCESS);

		delete_tree(root);
		free(nodes);
		printf("\n");
	}
	log_test_case(arr, size);
}
void test_inorder()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	int arr1[] = { 4, 2, 5, 1, 6, 3, 7 };
	int size = 7;
	test_inorder_(arr, arr1, size);

	int arr2[] = {  };
	int arr3[] = { };
	size = 0;
	test_inorder_(arr2, arr3, size);

	int arr4[] = { 1 };
	int arr5[] = {1 };
	size = 1;
	test_inorder_(arr4, arr5, size);
}

void test_post_order_(int* arr, int* arr2, int size)
{
	traversal_func_t funcs[3];
	funcs[0] = travrs_nodes_post_order;
	funcs[1] = travrs_nodes_post_order1;
	funcs[2] = travrs_nodes_post_order2;



	int count, *nodes;

	for (int i = 0; i < 3; i++) {
		tree_node * root = create_tree(arr, size);
		print_tree(root);
		int num_nodes = count_nodes(root);
		assert(size == num_nodes);
		nodes = malloc(sizeof(int)*num_nodes);

		count = 0;
		funcs[i](root, nodes, &count);
		print_arr(nodes, count);
		assert(count == num_nodes);
		assert(compare_arr(arr2, nodes, num_nodes) == EXIT_SUCCESS);
		delete_tree(root);
		free(nodes);
		printf("\n");
	}
	log_test_case(arr, size);
}

void test_post_order(){
	int arr[] = {1,2,3,4,5,6,7};
	int arr1[] = {4,5,2,6,7,3,1};
	int size = 7;
	test_post_order_(arr, arr1, size);

	int arr2[] = {  };
	int arr3[] = { };
	size = 0;
	test_post_order_(arr2, arr3, size);

	int arr4[] = { 1 };
	int arr5[] = {1 };
	size = 1;
	test_post_order_(arr4, arr5, size);
}


void test_pre_order_(int* arr, int* arr2, int size)
{
	traversal_func_t funcs[2];
	funcs[0] = travrs_nodes_pre_order;
	funcs[1] = travrs_nodes_pre_order1;

	int count = 0, *nodes;

	for (int i = 0; i < 2; i++) {
		tree_node * root = create_tree(arr, size);

		print_tree(root);
		int num_nodes = count_nodes(root);
		assert(size == num_nodes);
		nodes = malloc(sizeof(int)*num_nodes);

		count = 0;
		funcs[i](root, nodes, &count);
		print_arr(nodes, count);
		assert(count == num_nodes);
		assert(compare_arr(arr2, nodes, num_nodes) == EXIT_SUCCESS);
		printf("\n");

		delete_tree(root);
		free(nodes);
	}
	log_test_case(arr, size);
}

void test_pre_order(){
	int arr[] = {1,2,3,4,5,6,7};
	int arr1[] = {1,2,4,5,3,6,7};
	int size = 7;
	test_pre_order_(arr, arr1, size);

	int arr2[] = {  };
	int arr3[] = { };
	size = 0;
	test_pre_order_(arr2, arr3, size);

	int arr4[] = { 1 };
	int arr5[] = {1 };
	size = 1;
	test_pre_order_(arr4, arr5, size);
}


void test_tree(){
	test_basic_ops(4096	);
	test_pre_order();
	test_post_order();
	test_inorder();
}
int main(){
	test_tree();
}
