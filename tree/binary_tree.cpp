#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <cstdlib>
#include <string>
#include <stack>
#include <queue>
#include <mutex>
#include <cstdint>
#include <fstream>
#include <list>
#include <map>
#include <utility>
#include <cassert>
#include <array>
#include <cmath>

using namespace std;

#include "../../ds_algo1/tree/binary_tree.h"


#define BST_NUM_LEAF(height) (pow(2, height))
#define BST_MAX_NODES(height) (pow(2, height+1) -1)
#define BST_MAX_NODE_LEVEL(level) (power(2, level))

#define TEST_NUM_LEN 20
int path_arr[TEST_NUM_LEN] ={0};
int path_indx = -1;

#define log_to_path(x) 	path_arr[++path_indx] = x

tree_node* bin_tree_new_node(int key)
{
	tree_node *temp = (tree_node*) malloc(sizeof(tree_node));
	temp->left = NULL;
	temp->right = NULL;
	temp->key = key;
	return temp;
}

void bin_tree_insert_node(tree_node* root, int key)
{
	queue<tree_node*> myqueue;
	tree_node* curr_node;
	myqueue.push(root);

	while (!myqueue.empty()) {
		curr_node = myqueue.front();

		if (curr_node->left != NULL) {
			myqueue.push(curr_node->left);
		} else {
			curr_node->left = bin_tree_new_node(key);
			break;
		}

		if (curr_node->right != NULL) {
			myqueue.push(curr_node->right);
		} else {
			curr_node->right = bin_tree_new_node(key);
			break;
		}
		myqueue.pop();

	}
}

int bin_tree_height(tree_node * node)
{
	if (node == NULL)
		return 0;

	int height_left = bin_tree_height(node->left);
	int height_right = bin_tree_height(node->right);

	return (1 + (height_left > height_right ? height_left : height_right));
}
bool bin_tree_is_node_leaf(tree_node* node, int key)
{
	tree_node *next = NULL;

	if (node == NULL)
		return NULL;

	//next node
	if (key < node->key)
		next = node->left;
	if (key > node->key)
		next = node->right;

	// if  am the leaf node, no next node to traverse return parent
	if (next == NULL) {
		cout << node->key << "(1 am leaf node)" << endl;
		return 0;
	}
	return 1;
}

/*******************************************************************************************************/

void bin_tree_traversal_inorder(tree_node* curr_node, operation perform)
{
	if (curr_node == NULL)
		return;

	printf(" %d ", curr_node->key);
	bin_tree_traversal_inorder(curr_node->left, perform);
	if(perform) perform(curr_node);
	log_to_path(curr_node->key);
	bin_tree_traversal_inorder(curr_node->right, perform);

}
void bin_tree_traversal_postorder(tree_node* curr_node, operation perform)
{
	if (curr_node == NULL)
		return;

	printf(" %d ", curr_node->key);
	bin_tree_traversal_postorder(curr_node->left, perform);
	bin_tree_traversal_postorder(curr_node->right, perform);
	if(perform) perform(curr_node);
	log_to_path(curr_node->key);
}
/*******************************************************************************************************/
void bst_free_node(tree_node * curr_node)
{
	free(curr_node);
	curr_node = NULL;
}

void bin_tree_clear(tree_node* node)
{
	operation op2 = bst_free_node;
	bin_tree_traversal_postorder(node, op2);
}

static void prn_node(tree_node * curr_node)
{
	cout << curr_node->key << " ";
}

void bin_tree_print_inorder(tree_node* root)
{
	cout << "Sorted Keys:";
	operation op2 = prn_node;
	bin_tree_traversal_inorder(root, op2);
	cout << endl;
}
/*******************************************************************************************************/
int bin_tree_print(tree_node* root)
{
	queue<tree_node*> myqueue;
	queue<int> level;
	tree_node* curr_node;
	int curr_level;
	int previous_level = -1;

	int height = bin_tree_height(root);

	cout << "Doing Level order traversal: Height" << height << endl;
	myqueue.push(root);
	level.push(0);

	while (!myqueue.empty()) {
		curr_node = myqueue.front();
		curr_level = level.front();

		if (curr_level > previous_level) {
			cout << endl;
			previous_level = curr_level;
		}

		if (curr_node->left != NULL) {
			myqueue.push(curr_node->left);
			level.push(curr_level + 1);
		}

		if (curr_node->right != NULL) {
			myqueue.push(curr_node->right);
			level.push(curr_level + 1);
		}
		cout << curr_node->key << "(" << curr_level << ")" << " ";
		myqueue.pop();
		level.pop();
	}
	cout << endl;
	return 0;

}

int bin_tree_traversal_level_order(tree_node* root, operation1 perform)
{

	queue<tree_node*> myqueue;
	queue<int> level;
	tree_node* curr_node;
	int curr_level;
	int previous_level = -1;

	int height = bin_tree_height(root);

	cout << "Doing Level order traversal: Height" << height << endl;
	myqueue.push(root);
	level.push(0);

	while (!myqueue.empty()) {
		curr_node = myqueue.front();
		curr_level = level.front();

		if (curr_level > previous_level) {
			previous_level = curr_level;
		}

		if (curr_node->left != NULL) {
			myqueue.push(curr_node->left);
			level.push(curr_level + 1);
		}

		if (curr_node->right != NULL) {
			myqueue.push(curr_node->right);
			level.push(curr_level + 1);
		}
		//cout<<curr_node->key<<"("<<curr_level<<")"<<" ";
		perform(curr_node, curr_level);
		myqueue.pop();
		level.pop();
	}
	cout << endl;
	return 0;
}


/*******************************************************************************************************/
void bin_tree_traversal_postorder_iter(tree_node* root, operation perform)
{
	stack<tree_node*> mystack;
	stack<int> is_right;
	int is_curr_right = 0;
	tree_node* curr_node = root;
	if (curr_node == NULL)
		return;
	int done = 0;

	while (!done) {
		if (curr_node != NULL) {

			mystack.push(curr_node);
			is_right.push(0);

			if (curr_node->right != NULL) {
				mystack.push(curr_node->right);
				is_right.push(1);
			}
			curr_node = curr_node->left;

		} else {
			if (!mystack.empty()) {
				curr_node = mystack.top();
				mystack.pop();
				is_curr_right = is_right.top();
				is_right.pop();

				if (is_curr_right == 0) {
					if(perform) perform(curr_node);
					log_to_path(curr_node->key);
					curr_node = NULL;
				}
			} else
				done = 1;
		}
	}
}

void bin_tree_traversal_inorder_iter(tree_node* root, operation perform)
{
	stack<tree_node*> mystack;
	tree_node* curr_node = root;
	bool done = false;
	if (curr_node == NULL)
		return;

	while (!done) {
		if (curr_node != NULL) {
			mystack.push(curr_node);
			curr_node = curr_node->left;
		} else {
			if (!mystack.empty()) {
				curr_node = mystack.top();
				mystack.pop();
				if(perform) perform(curr_node);
				log_to_path(curr_node->key);
				curr_node = curr_node->right;
			} else {
				done = true;
			}
		}
	}
}

void bin_tree_traversal_preorder_itr(tree_node* root, operation perform)
{
	stack<tree_node*> mystack;
	mystack.push(root);
	tree_node* curr_node = root;

	while (!mystack.empty()) {

		curr_node = mystack.top();
		mystack.pop();

		if(perform)perform(curr_node);
		log_to_path(curr_node->key);

		if (curr_node->right != NULL)
			mystack.push(curr_node->right);

		if (curr_node->left != NULL)
			mystack.push(curr_node->left);
	};

}
/*******************************************************************************************************/
int* create_arr(int size)
{
	int* arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		int key = (rand() / 1000) % 100;
		arr[i] = key;
	}
	return arr;
}

tree_node * create_bin_tree(int* arr, int size)
{
	tree_node * root = bin_tree_new_node(arr[0]);
	for (int i = 1; i < size; i++)
		bin_tree_insert_node(root, arr[i]);
	return root;
}

int compare_arr(int* arr1, int* arr2, int len){

	int i = 0;
	while(i < len){
		if(arr1[i] != arr2[i])
			return EXIT_FAILURE;
		i++;
	}
	return EXIT_SUCCESS;
}

void print_arr(int* arr, int arr_len)
{
	printf("( Len: %d Arr: ", arr_len);
	for (int i = 0; i < arr_len; i++) {
		printf("%d ", arr[i]);
	}

	printf(")");
}
/**
			1
		/		 \
	2				3
 /	  \			  /	  \
4		5		6		7
 */

typedef void (*traversal_func_t)(tree_node* root, operation perform);
void test_inorder()
{
	traversal_func_t funcs[2];
	funcs[0] = bin_tree_traversal_inorder;
	funcs[1] = bin_tree_traversal_inorder_iter;

	int arr[] = {1,2,3,4,5,6,7};
	int arr2[] = {4,2,5,1,6,3,7};
	int size = 7;
	path_indx = -1;


	for (int i = 0; i < 2; i++) {
		tree_node * root = create_bin_tree(arr, size);
		bin_tree_print(root);
		funcs[i](root, prn_node);
		print_arr(path_arr, size);
		assert(compare_arr(arr2, path_arr, size) == EXIT_SUCCESS);
		bin_tree_clear(root);
	}
}
void test_postorder()
{
	traversal_func_t funcs[2];
	funcs[0] = bin_tree_traversal_postorder;
	funcs[1] = bin_tree_traversal_postorder_iter;

	int arr[] = {1,2,3,4,5,6,7};
	int arr1[] = {4,5,2,6,7,3,1};
	int size = 7;
	path_indx = -1;


	for (int i = 0; i < 2; i++) {
		tree_node * root = create_bin_tree(arr, size);
		bin_tree_print(root);
		funcs[i](root, prn_node);
		print_arr(path_arr, size);
		assert(compare_arr(arr1, path_arr, size) == EXIT_SUCCESS);
		bin_tree_clear(root);
	}
}
void test_preorder(){

	int arr[] = {1,2,3,4,5,6,7};
	int arr3[] = {1,2,4,5,3,6,7};
	int size = 7;
	path_indx = -1;

	tree_node * root = create_bin_tree(arr, size);
	bin_tree_print(root);
	bin_tree_traversal_preorder_itr(root, prn_node);
	print_arr(path_arr, size);
	assert(compare_arr(arr3, path_arr, size) == EXIT_SUCCESS);
	bin_tree_clear(root);

}

void test_bin_tree(){
	test_postorder();
	test_inorder();
	test_preorder();
}

int binary_tree_test()
{

	int size = 16;
	int* arr = create_arr(size);
	tree_node * root= create_bin_tree(arr, size);
	bin_tree_print(root);
	bin_tree_clear(root);

	root = root= create_bin_tree(arr, size);
	bin_tree_print(root);

	cout << "Height:" << bin_tree_height(root) << endl;

	bin_tree_print_inorder(root);

	cout << endl << "pre Order Travesal: ";
	bin_tree_traversal_preorder_itr(root, prn_node);

	cout << endl << "In order Travesal: ";
	bin_tree_traversal_inorder_iter(root, prn_node);

	cout << endl << "PostOrder Travesal: ";
	bin_tree_traversal_postorder_iter(root, prn_node);

	return 0;

}

int main(){
	//binary_tree_test();
	test_bin_tree();
}
