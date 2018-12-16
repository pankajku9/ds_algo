
#pragma once

typedef struct tree_node_{
	struct tree_node_ *left;
	struct tree_node_ *right;
	int key;
}tree_node;

tree_node* new_bst_node(int data);

bool bst_is_valid(tree_node* root);
int bst_find_node(tree_node* root, int key);

tree_node* bst_delete_node( tree_node* bst_root, int key);
tree_node* bst_insert_node( tree_node* bst_root, int key);
tree_node* bst_get_node(tree_node* root, int key, tree_node** parent_ref = nullptr);
tree_node* bst_get_node1(tree_node* root, int key, tree_node** parent_ref = nullptr);
void bst_print1(tree_node* root);
int bst_test();


