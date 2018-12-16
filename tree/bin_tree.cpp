#include <cstdio>
#include <cstdlib>
#include <queue>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <stack>

using namespace std;


#define RET_ERR_IF_NULL(i) do { if(i == NULL) return EXIT_FAILURE; } while(0)
#define RET_NULL_IF_NULL(i) do { if(i == NULL) return NULL; } while(0)

struct tree_node{
    tree_node* left;
    tree_node* right;
    int val;
};
typedef tree_node TreeNode;

tree_node* new_tree_node(int i){
    tree_node* temp = new tree_node;
    temp->val = i;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

tree_node* insert_node(tree_node* root, int i)
{
    if(root == NULL)
        return new_tree_node(i);

    std::queue<tree_node*> trav_q;
    tree_node* curr;
    trav_q.push(root);

    while (1) {
        curr = trav_q.front();
        trav_q.pop();

        if (!curr->left) {
            curr->left = new_tree_node(i);
            break;
        }
        else
            trav_q.push(curr->left);

        if (!curr->right) {
            curr->right = new_tree_node(i);
            break;
        }
        else
            trav_q.push(curr->right);
    }
    return root;
}

tree_node* create_tree(int* arr, int arr_len){

    tree_node* root = NULL;
    for(int i = 1; i <= arr_len ; i++){
        root = insert_node(root, i);
    }
    return root;
}

static int tree_depth__(tree_node* root, int depth)
{
	if (root == NULL)
		return depth;

	int left_d = tree_depth__(root->left, depth);
	int right_d = tree_depth__(root->right, depth);

	return std::max(left_d, right_d) + 1;
}

int tree_depth(tree_node* root){
    return tree_depth__(root, 0);
}

void print_tree_level(tree_node* root, const char* msg)
{
	if (root == NULL)
		return;

	printf("%s\n", msg);

	std::queue<tree_node*> trav_q;
	tree_node* curr;
	trav_q.push(root);

	while (!trav_q.empty()) {

		int node_count = trav_q.size();

		while (node_count > 0) {
			curr = trav_q.front();
			trav_q.pop();
			printf(" %d ", curr->val);
			if (curr->left)
				trav_q.push(curr->left);

			if (curr->right)
				trav_q.push(curr->right);

			node_count--;
		}
		printf("\n");
	}
}

void print_tree_preorder(tree_node* root, const char* msg){

    if(root == NULL)
        return;

    printf("%s : ", msg);

    std::stack<tree_node*> trav_q;
    tree_node* curr;
    trav_q.push(root);

    while (!trav_q.empty()) {
            curr = trav_q.top();
            trav_q.pop();
            printf(" %d ", curr->val);

            if (curr->right)
               trav_q.push(curr->right);

            if (curr->left)
                trav_q.push(curr->left);
    }
    printf("\n");
}
/********************************************************************************************************/

vector<int> trav_tree_inorder(tree_node* root)
{
	if (root == NULL)
		return vector<int>();

	std::stack<tree_node*> stk;
	tree_node* curr = root;
	vector<int> ans;

	while (1) {
		while (curr) {
			stk.push(curr);
			curr = curr->left;
		}

		if (stk.empty())
			break;

		curr = stk.top();
		stk.pop();
		ans.push_back(curr->val);
		curr = curr->right;
	}

	return ans;
}

vector<int> trav_tree_preorder(tree_node* root)
{
	vector<int> ans;
	if (root == NULL)
		return ans;

	std::stack<tree_node*> trav_q;
	trav_q.push(root);

	while (!trav_q.empty()) {
		tree_node* curr = trav_q.top();
		trav_q.pop();
		ans.push_back(curr->val);

		if (curr->right)
			trav_q.push(curr->right);

		if (curr->left)
			trav_q.push(curr->left);
	}
	return ans;
}

vector<int> trav_tree_postorder(TreeNode* root)
{
    if (root == NULL)
    	return vector<int>();

    stack<TreeNode*> s1, s2;
    s1.push(root);
    vector<int> ans;

    while (!s1.empty()) {
    	TreeNode* node = s1.top();
    	s1.pop();
        s2.push(node);

        if (node->left)
            s1.push(node->left);
        if (node->right)
            s1.push(node->right);
    }

    while (s2.empty()) {
    	TreeNode* node = s2.top();
    	s2.pop();
        ans.push_back(node->val);
    }

    return ans;
}



vector<int> trav_tree_postorder1(tree_node* root)
{
	if (root == NULL)
			return vector<int>();

	std::stack<tree_node*> stk;
	vector<int> ans;
	tree_node* curr = root;

	while (1) {
		while (curr) {
			if (curr->right)
				stk.push(curr->right);
			stk.push(curr);
			curr = curr->left;
		}

		if (stk.empty())
			break;

		curr = stk.top();
		stk.pop();

		if (!stk.empty() && curr->right == stk.top()) {
			stk.pop();
			stk.push(curr);
			curr = curr->right;
		} else {
			ans.push_back(curr->val);
			curr = NULL;
		}
	}

	return ans;
}



void trav_recurcive(tree_node* root, int mode){
    if(root == NULL)
        return;

    if(mode == 1){
        trav_recurcive(root->left,mode);
        trav_recurcive(root->right,mode);
        printf("%d ", root->val,mode);

    }
    else if(mode == 2){
        trav_recurcive(root->left,mode);
        printf("%d ", root->val,mode);
        trav_recurcive(root->right,mode);

    }
    else{
       printf("%d ", root->val,mode);
       trav_recurcive(root->left,mode);
       trav_recurcive(root->right,mode);
    }

}

vector<vector<int> > verticalOrderTraversal(TreeNode* A) {

   if(A == NULL) return vector<vector<int> >();

    unordered_map<int, int> dist;
    queue<TreeNode*> trav;
    trav.push(A);
    dist[A->val] = 0;
    int min = 0, max= 0;

    while(!trav.empty()){
        TreeNode* curr = trav.front();
        trav.pop();

        int dis = dist[curr->val];

        if(curr->left){
            dist[curr->left->val] = dis-1;
            trav.push(curr->left);
            if(min > dis-1)
                min = dis-1;
        }

        if(curr->right){
            dist[curr->right->val] = dis+1;
            trav.push(curr->right);
            if(max < dis+1)
                max= dis+1;
        }
    }
    //printf("%d %d %d \n", max, min, dist.size());
    vector<vector<int>> ans(max-min+1, std::vector<int>(0));
    for(auto& p : dist){
        int pos = p.second - min;
        ans[pos].push_back(p.first);
    }

    return ans;

}

vector<vector<int> > zigzagLevelOrder(TreeNode* A) {
    vector<vector<int> > ans;
    if(A == NULL) return ans;

    stack<TreeNode*> curr_lvl, nxt_lvl;
    curr_lvl.push(A);

    bool right_to_left  = true;
    while(!curr_lvl.empty()){
        std::vector<int> val_at_lvl;
        while(!curr_lvl.empty()){
            TreeNode* curr = curr_lvl.top();
            curr_lvl.pop();
            val_at_lvl.push_back(curr->val);
            if(right_to_left){
                if(curr->left){
                    nxt_lvl.push(curr->left);
                }

                if(curr->right){
                    nxt_lvl.push(curr->right);
                }
            }
            else{
                if(curr->right){
                    nxt_lvl.push(curr->right);
                }
                if(curr->left){
                    nxt_lvl.push(curr->left);
                }
            }
        }
        right_to_left = !right_to_left;
        ans.push_back(val_at_lvl);
        nxt_lvl.swap(curr_lvl);
    }
    return ans;
}


vector<int> print_path(unordered_map<TreeNode*, TreeNode*>& par, TreeNode* leaf){
	stack<TreeNode*> path;
	while(leaf){
		path.push(leaf);
		leaf = par[leaf];
	}

	vector<int> ans;
	while(!path.empty()){
		ans.push_back(path.top()->val);
		path.pop();
	}
	return ans;
}

void print_all_path(TreeNode* root){

	std::queue<tree_node*> trav_q;
	tree_node* curr;
	trav_q.push(root);
	unordered_map<TreeNode*, TreeNode*> parents;
	parents[root] = NULL;

	while (!trav_q.empty()) {
			curr = trav_q.front();
			trav_q.pop();

			if (curr->left){
				trav_q.push(curr->left);
				parents[curr->left] = curr;

			}

			if (curr->right){
				trav_q.push(curr->right);
				parents[curr->right] = curr;
			}

			if(!curr->left && !curr->right){
				auto path = print_path(parents, curr);
				for(auto a: path)
					printf(" %d", a);
				printf("\n");
			}

	}
}
//TODO  Add test case to data
int main(int argc, char** argv)
{
	if (argc < 2){
		printf(" usages: a.exe num_node ");
		return 0;
	}

	int n = std::stoi(argv[1]);
	int * arr = (int*) malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
		arr[i] = i;

	auto root1 = create_tree(arr, n);
	printf("Depth: %d \n", tree_depth(root1));

	print_tree_level(root1, " Level Order");
	print_tree_preorder(root1, "preorder");
	//print_tree_inorder(root1, "inorder");

	printf("\n");
	trav_recurcive(root1, 1);
	printf("\n");
	trav_recurcive(root1, 2);
	printf("\n");
	trav_recurcive(root1, 3);

	print_all_path(root1);
}
