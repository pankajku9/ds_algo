#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cassert>

using namespace std;

#include "../../ds_algo1/tree/bst.h"

struct cartesian_tree{
    tree_node *node;
    int x;
    int y;
};

void print_path( vector<tree_node*> path){

    for(int i=0; i < path.size(); i++){
        cout<<path[i]->key<<" ";
    }
    cout<<endl;
}

void print_tree_paths(tree_node * root){

    if(root == NULL) return;

    vector<tree_node *> path;
    stack<tree_node *> backtrack_stk;

    backtrack_stk.push(root);
    bool done = false;

    while(!done){

        if(!backtrack_stk.empty())
        {
            tree_node *curr_node = backtrack_stk.top();
            backtrack_stk.pop();

            cout<<curr_node->key<<" ";

            if(curr_node->right != NULL){
                backtrack_stk.push(curr_node->right);
            }

            if(curr_node->left != NULL){
                backtrack_stk.push(curr_node->left);
            }
        }
        else{
            done = true;
        }

    }
}

int main(int argc, char **argv)
{
    cout << "creating  BST nodes and add 99 nodes and print"<< endl;
    tree_node *root = new_bst_node(50);

    std::vector<cartesian_tree *> tree;
    std::stack<tree_node*> mystack;
    bool done = false;
    tree_node  *curr_node;
    cartesian_tree *temp;

    for(int i = 1; i < 10; i++)
    {
        int key = (rand()/1000) % 100;
        bst_insert_node(root, key);
    }

    bst_print1(root);

    print_tree_paths(root);
   /* while(!done){
        if(curr_node != NULL){
            mystack.push(curr_node);
            curr_node = curr_node->left;
        }
        else{
            if(!mystack.empty())
            {
                curr_node = mystack.top();
                mystack.pop();
                temp = new cartesian_tree;
                temp->node = curr_node;
                if(curr_node == root)
                {
                    temp.x = 0;
                    temp.y = 0;
                }
                else{
                    if(curr_node->parent->left != NULL){
                        if(curr_node == curr_node->parent->left){
                    }
                }


                curr_node = curr_node->right;
            }
            else
            {
                done = true;
            }
        }
   }
    */
    return 0;
}
