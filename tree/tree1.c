#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node{
    int val;
    struct tree_node* left;
    struct tree_node* right;
}tree_node;

typedef tree_node treenode;

void print_t(tree_node* root){
    if(root == NULL) return;
    printf(" %d", root->val);
    print_t(root->left);
    print_t(root->right);
}

tree_node* create_tree1(int* in_ord, int ibeg, int iend, int * pre_ord, int* pidx){
    
    //printf(" IB:%d IE:%d PI:%d \n", ibeg, iend, *pidx);
    if(ibeg > iend)
        return NULL;
    
    int root_val = pre_ord[*pidx];
    *pidx = *pidx + 1;
     
    int idx = ibeg;
    for(; idx <= iend; idx++){
        if(in_ord[idx] == root_val)
            break;
    }
    
    tree_node* root = malloc(sizeof(tree_node));
    root->val = root_val;
    root->left = create_tree1(in_ord, ibeg, idx-1, pre_ord, pidx);
    root->right = create_tree1(in_ord, idx+1, iend, pre_ord, pidx);
    
    return root;
}
int tree_size(treenode* A){
    if(!A)
        return 0;
   return tree_size(A->left) + tree_size(A->right) + 1;
}

tree_node* create_tree(int* in_ord, int ibeg, int iend, int *pre_ord, int* pidx){
    
    printf(" IB:%d IE:%d PI:%d ", ibeg, iend, *pidx);    
    int root_val = pre_ord[*pidx];
    *pidx = *pidx + 1;
    
    tree_node* root = malloc(sizeof(tree_node));
    root->val = root_val;
    
    if(ibeg == iend){
        root->left = NULL;
        root->right = NULL;
        printf("\n");
        return root;
        
    }
     
    int idx = ibeg;
    for(; idx <= iend; idx++){
        if(in_ord[idx] == root_val)
            break;
    }
    printf(" IDX:%d \n", idx);
    
    root->left = create_tree(in_ord, ibeg, idx-1, pre_ord, pidx);
    root->right = create_tree(in_ord, idx+1, iend, pre_ord, pidx);
    return root;
}

unsigned size_tree(tree_node* root){
    if(root == NULL) return 0;
    return size_tree(root->left) + size_tree(root->right) + 1;
}

void printt_preorder(tree_node* root){
    int N = size_tree(root);
    tree_node** stack = calloc(N, sizeof(tree_node*));
    int top = -1;
    stack[++top] = root;
    
    while(top > -1){
        tree_node* curr = stack[top--];
        if(curr->right)
            stack[++top] = curr->right;
        if(curr->left)
            stack[++top] = curr->left;
        printf(" %d" , curr->val);  
    }
    free(stack);
}
void printt_preorder1(tree_node *root, int N){
    tree_node** stack = malloc(sizeof(tree_node*)*N);
    tree_node* curr = root;
    int top = -1; 
    while(1){
        while(curr){
            if(curr->right)
                stack[++top] = curr->right;
            printf(" %d", curr->val);
            curr = curr->left;
        }
        if(top <= -1)
            break;
        curr = stack[top--];
    }
    free(stack);
}

void printt_postorder(tree_node* root){
    int N = size_tree(root);
    tree_node** stack = calloc(N, sizeof(tree_node*));
    tree_node** stack1 = calloc(N, sizeof(tree_node*));
    int top = -1, top1 = -1;
    stack[++top] = root;
    
    while(top > -1){
        tree_node* curr = stack[top--];
        if(curr->right)
            stack[++top] = curr->right;
        if(curr->left)
            stack[++top] = curr->left;
        stack1[++top1] = curr;
    }
    
     while(top1 > -1){
          printf(" %d" , stack1[top1--]->val); 
     }
    free(stack1);    
    free(stack);
}

void printt_postorder1(tree_node* root){
    int N = size_tree(root);
    tree_node** stack = calloc(N, sizeof(tree_node*));
    int top = -1;
    tree_node* curr = root;
    while(1){
        
        while(curr){
            if(curr->right)
                stack[++top] = curr->right;
            stack[++top] = curr;
            curr = curr->left;
        }
        if(top <= -1)
            break;
        
        curr = stack[top--];
        if(curr->right == stack[top]){
            top--;
            stack[++top] = curr;
            curr = curr->right;
        }
        else{
            printf(" %d" , curr->val);
            curr = NULL;
        }
    }
    free(stack);
}

void printt_inorder(tree_node* root){
    int N = size_tree(root);
    tree_node** stack = calloc(N, sizeof(tree_node*));
    int top = -1;
    tree_node* curr = root;
    while(1){
        
        while(curr){
            stack[++top] = curr;
            curr = curr->left;
        }
        
        if(top <= -1)
            break;
        
        curr = stack[top--];
        printf(" %d" , curr->val);
        curr = curr->right;
    }
    free(stack);
}

void printt_levelorder(tree_node* root){
    int N = size_tree(root);
    tree_node** queue = calloc(N, sizeof(tree_node*));
    int front = 0, back = -1;
    queue[++back] = root;
    
    while(front <= back){
        tree_node* curr = queue[front++];
        if(curr->left)
            queue[++back] = curr->left;
        if(curr->right)
            queue[++back] = curr->right;
        printf(" %d" , curr->val);  
    }
    free(queue);
}

treenode* flatten1(treenode* A) {
     treenode dummy_head = {0, NULL};
     treenode* ptr = &dummy_head;
     int n = tree_size(A);
     treenode** stack = malloc(sizeof(tree_node*)*n);
     int top = -1;
     
     treenode* curr = A;
     
     while(1){
         while(curr){
             if(curr->right)
                 stack[++top] = curr->right;
             ptr->right = curr;
             curr = curr->left;
             ptr->left = NULL;
             ptr = ptr->right;
         }
         if(top <= -1){
             break;
         }
         curr = stack[top--];
     }
     ptr = dummy_head.left;
     free(stack);
     return ptr;
}


int sumNumbers(treenode* A) {
    int n = size_tree(A);
    treenode** queue = malloc(n*sizeof(treenode*));
    int* queue_val = malloc(n*sizeof(int));
    int front = 0, back = -1, front1 = 0, back1 = -1;
    queue[++back] = A;
    queue_val[++back1] = A->val;
    int sum = 0;
    
    while(front <= back){
        treenode* curr = queue[front++];
        int curr_val = queue_val[front1++];
        if(curr->left){
            queue_val[++back1] = curr_val * 10 + curr->left->val;
            queue[++back] = curr->left;
        }
        if(curr->right){
            queue_val[++back1] = curr_val * 10 + curr->right->val;
            queue[++back] = curr->right;
        }
        
        if(!curr->left && !curr->right){
            sum = ((sum + curr_val)%1003);
        }
    }
    free(queue);
    free(queue_val);
    return sum;
    
}


int test_create(){
    int in[] = {4,2,5,1,6,3,7};
    int pre[] = {1,2,4,5,3,6,7};
    int pidx = 0;
    tree_node* root = create_tree(in, 0, 6, pre, &pidx);
    printf("\n lEVEL ORDER: ");
    printt_levelorder(root);
    printf("\n PRE ORDER  : ");
    printt_preorder(root);
    printf("\n POST ORDER : ");
    printt_postorder(root);
    printf("\n POST ORDER : ");
    printt_postorder1(root);
    printf("\n IN ORDER   : ");
    printt_inorder(root);
    
    printf("\n PRE ORDER  : ");
    int N = size_tree(root);
    printt_preorder1(root, N);
}

int main(){
    test_create();
}


