#include "../../ds_algo1/tree/bst.h"

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

#define RET_ERR_IF_NULL(i) do { if(i == NULL) return EXIT_FAILURE; } while(0)
#define RET_NULL_IF_NULL(i) do { if(i == NULL) return NULL; } while(0)

static tree_node* get_next(tree_node* curr, int key)
{
	if (key > curr->key)
		curr = curr->right;
	else
		curr = curr->left;
	return curr;
}

tree_node* bst_get_node(tree_node* root, int key, tree_node** parent_ref)
{
	RET_NULL_IF_NULL(root);

	if (root->key == key)
		return root;

	if (parent_ref)
		*parent_ref = root;

	root = get_next(root, key);
	return bst_get_node(root, key, parent_ref);
}

tree_node* bst_get_node1(tree_node* root, int key, tree_node** parent_ref)
{
	RET_NULL_IF_NULL(root);

	tree_node* parent;
	while (root && root->key != key) {
		parent = root;
		root = get_next(root, key);
	}
	if (parent_ref)
		*parent_ref = parent;
	return root;
}

void bst_get_path(tree_node* root, int key, vector<int>& path)
{
	while (root && root->key != key) {
		path.push_back(root->key);
		root = get_next(root, key);
	}

	if (root) {
		path.push_back(root->key);
	}
}

vector<int> bst_get_nodes_inorder(tree_node* root)
{
	stack<tree_node*> trav;
	tree_node* curr = root;
	vector<int> path;

	while (1) {
		while (curr) {
			trav.push(curr);
			curr = curr->left;
		}

		if (trav.empty())
			break;

		curr = trav.top();
		trav.pop();
		path.push_back(curr->key);

		curr = curr->right;
	}

	return path;
}

bool bst_is_valid(tree_node* root)
{
	auto nodes = bst_get_nodes_inorder(root);
	return is_sorted(nodes.begin(), nodes.end());
}
/***********************************************************************************************************/
int bst_find_node(tree_node* root, int key)
{
	while (root && root->key != key)
		root = get_next(root, key);

	if (root && root->key == key)
		return EXIT_SUCCESS;

	return EXIT_FAILURE;
}

tree_node* new_bst_node(int data)
{
	tree_node* temp = new tree_node;
	temp->key = data;
	temp->left = temp->right = nullptr;
	return temp;
}

tree_node* bst_insert_node(tree_node* bst_root, int key)
{
	if (!bst_root)
		return new_bst_node(key);

	tree_node* parent;
	tree_node* node = bst_get_node1(bst_root, key, &parent);
	if (node && node->key == key)
		return bst_root;

	if (key > parent->key)
		parent->right = new_bst_node(key);
	else
		parent->left = new_bst_node(key);

	return bst_root;
}
/***********************************************************************************************************/
static void add_child_to_node_parent(tree_node* curr, tree_node* parent, tree_node* child)
{
	if (parent->left == curr)
		parent->left = child;
	else
		parent->right = child;
}

static tree_node* get_child(tree_node* curr)
{
	tree_node* child;
	if (curr->left)
		child = curr->left;
	else if (curr->right)
		child = curr->right;
	else
		child = nullptr;
	return child;
}

static tree_node* extract_next_minimum_node(tree_node* curr)
{
	tree_node *pred_par = curr, *pred = curr->right;
	while (pred->left) {
		pred_par = pred;
		pred = pred->left;
	}
	tree_node* child = get_child(pred);
	add_child_to_node_parent(pred, pred_par, child);
	return pred;
}

static int at_most_one_child(tree_node* curr)
{
	return !(curr->left && curr->right);
}

tree_node* bst_delete_node(tree_node* root, int key)
{
	RET_NULL_IF_NULL(root);

	tree_node *parent = nullptr, *curr = root;
	while (curr && curr->key != key) {
		parent = curr;
		curr = get_next(curr, key);
	}

	if (!curr)
		return root;

	if (at_most_one_child(curr)) {
		tree_node* child = get_child(curr);
		if (!parent) {
			delete curr;
			return child;
		}
		add_child_to_node_parent(curr, parent, child);
		delete curr;
		return root;
	} else {
		auto pred = extract_next_minimum_node(curr);
		pred->left = curr->left;
		pred->right = curr->right;
		if (!parent) {
			delete curr;
			return pred;
		}
		add_child_to_node_parent(curr, parent, pred);
		delete curr;
		return root;
	}
}

tree_node* construct_from_preorder(int* preorder_arr, int beg, int end){

	int i = beg;
	for(; i < end; i++)
		if(preorder_arr[i] > preorder_arr[beg])
			break;

	//printf(" %d %d %d\n", beg, i, end);

	if(beg > end)
		return nullptr;

	if(beg == end)
		return new_bst_node(preorder_arr[beg]);

	tree_node* root = new_bst_node(preorder_arr[beg]);
	root->left = construct_from_preorder(preorder_arr, beg+1, i-1);
	root->right = construct_from_preorder(preorder_arr,i, end);
	return root;

}
/***********************************************************************************************************/
#define log_test_case(vector)   do{\
                printf(" %s ", __FUNCTION__); \
                print_vector(vector); \
                printf(" passed\n"); \
            } while(0) \

void print_vector(vector<int> vec)
{
	cout << "( Len: " << vec.size() << " vec: ";
	if (vec.size() < 10) {
		for (int i = 0; i < vec.size(); i++) {
			cout << " " << vec[i];
		}
	} else {
		for (int i = 0; i < 6; i++) {
			cout << " " << vec[i];
		}
		cout << " ... " << vec[vec.size() - 2] << vec[vec.size() - 1];
		;
	}

	printf(")");
}

void bst_print(tree_node * root)
{
	if (!root)
		return;
	bst_print(root->left);
	std::cout << root->key << " ";
	bst_print(root->right);
}

void bst_print1(tree_node* root)
{
	queue<tree_node*> trav;
	trav.push(root);
	cout << " Tree:" << endl;
	while (!trav.empty()) {
		int count = trav.size();
		while (count) {
			auto curr = trav.front();
			trav.pop();
			cout << " " << curr->key;
			if (curr->left)
				trav.push(curr->left);
			if (curr->right)
				trav.push(curr->right);
			count--;
		}
		cout << endl;
	}
}

void test_bst_delete_root()
{
	tree_node * root = new_bst_node(1);
	assert(bst_delete_node(root, 1) == nullptr);

	root = new_bst_node(5);
	tree_node * node1 = new_bst_node(3);
	root->left = node1;
	assert(bst_delete_node(root, 5) == node1);

	root = new_bst_node(5);
	root->left = new_bst_node(3);;
	node1 = new_bst_node(7);
	root->right = node1;

	root = bst_delete_node(root, 5);
	assert(root == node1);
}
void test_bst_delete_node()
{
	tree_node * root = new_bst_node(5);
	root->left = new_bst_node(3);
	assert(bst_delete_node(root, 3) == root);

	root->left = new_bst_node(3);
	root->left->left = new_bst_node(1);
	assert(bst_delete_node(root, 3) == root);

	root->left = new_bst_node(3);
	root->left->right = new_bst_node(4);
	assert(bst_delete_node(root, 3) == root);
}

tree_node * get_custom_tree()
{
	tree_node * root = new_bst_node(10);
	root->left = new_bst_node(5);
	root->right = new_bst_node(15);

	root->left->left = new_bst_node(2);
	root->left->right = new_bst_node(7);

	root->right->left = new_bst_node(12);
	root->right->right = new_bst_node(17);

	root->right->left->right = new_bst_node(13);

	root->left->right->right = new_bst_node(8);
	bst_print1(root);
	return root;
}

void test_bst_delete_node1()
{
	tree_node * root = get_custom_tree();
	assert(bst_delete_node(root, 5) == root);
	bst_print1(root);

}

void manual_test_bst_delete()
{
	test_bst_delete_root();
	test_bst_delete_node();
	test_bst_delete_node1();
}

tree_node* get_random_bst(int size, vector<int>& input)
{
	tree_node *root = nullptr;
	for (int i = 0; i < size; i++) {
		int key = (rand() / 1000) % 100;
		root = bst_insert_node(root, key);
		input.push_back(key);
	}
	return root;
}

void bst_test1(int size)
{
	vector<int> inputs, input1;
	auto root1 = get_random_bst(size, inputs);
	assert(bst_is_valid(root1));

	//sort, remove duplicate from input
	input1.resize(inputs.size());
	copy(inputs.begin(), inputs.end(), input1.begin());
	sort(input1.begin(), input1.end());
	auto it = unique(input1.begin(), input1.end());
	input1.resize(distance(input1.begin(), it));

	auto nodes = bst_get_nodes_inorder(root1);
	assert(nodes == input1);

	log_test_case(inputs);
}

void bst_test2(int size)
{
	vector<int> inputs;
	auto root1 = get_random_bst(size, inputs);
	assert(bst_is_valid(root1));

	for (auto x : inputs) {
		assert(bst_find_node(root1, x) == EXIT_SUCCESS);
		assert(bst_get_node(root1, x) != nullptr);
		assert(bst_get_node1(root1, x) != nullptr);
		assert(bst_get_node(root1, x)->key == x);
		assert(bst_get_node1(root1, x)->key == x);
	}

	for (int i = 0; i < size; i++) {
		int key = rand();
		auto status1 = find(inputs.begin(), inputs.end(), key) == inputs.end() ? EXIT_FAILURE : EXIT_SUCCESS;
		auto status2 = bst_find_node(root1, key);
		assert(status1 == status2);
	}
	log_test_case(inputs);
}

void bst_test3(int size)
{
	vector<int> inputs;
	auto root1 = get_random_bst(size, inputs);
	assert(bst_is_valid(root1));

	sort(inputs.begin(), inputs.end());
	auto it = unique(inputs.begin(), inputs.end());
	inputs.resize(distance(inputs.begin(), it));

	for (auto a : inputs) {
		root1 = bst_delete_node(root1, a);
		//assert(root1 != nullptr);
		assert(bst_find_node(root1, a) == EXIT_FAILURE);
	}
	log_test_case(inputs);
}

void test_basic(int max_size)
{

	for (int i = 1; i <= max_size; i = i * 2) {
		bst_test1(i - 1);
		bst_test2(i - 1);
		bst_test3(i - 1);
	}
}

void test_bst_construct(){
	int arr[] = {10,5,1,7,40,50};
	tree_node* root = construct_from_preorder(arr, 0,5);
	bst_print1(root);

}

int bst_test()
{
	manual_test_bst_delete();
	test_basic(4096);
	return 0;
}

int main()
{
	//bst_test();
	test_bst_construct();
}
