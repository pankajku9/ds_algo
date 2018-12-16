

#ifndef __BINARY_TREE_H_
#define __BINARY_TREE_H_


struct tree_node {
	tree_node* left;
	tree_node* right;
	tree_node* parent;
	int key;
};

typedef void (*operation) (tree_node *);
typedef void (*operation1) (tree_node * , int arg);

bool bin_tree_is_node_leaf(tree_node* node, int key);
int bin_tree_height(tree_node * node);

tree_node* bin_tree_new_node( int key);
void bin_tree_insert_node(tree_node* root, int key);
void bin_tree_clear(tree_node* node);

int bin_tree_print(tree_node* root); // level order
void bin_tree_print_inorder(tree_node* root);

int bin_tree_traversal_level_order(tree_node* root, operation1 perform);

void bin_tree_traversal_postorder_iter(tree_node* root, operation perform);
void bin_tree_traversal_inorder_iter(tree_node* root, operation perform);
void bin_tree_traversal_preorder_itr(tree_node* root, operation perform);

void bin_tree_traversal_postorder(tree_node* curr_node, operation perform);
void bin_tree_traversal_inorder(tree_node* curr_node, operation perform);


int binary_tree_test();

#endif /* LIB_BST_H_ */
