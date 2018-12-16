
#pragma once


typedef struct list_node_{
    int val;
    struct list_node_ *next;
}list_node;


list_node *new_list_node(int data);
list_node *new_list_node1(int data);
list_node *create_list(int num);
list_node *create_list1(int num_node);

int list_size(list_node *head);
list_node* get_list_from_arr(int arr[], int num_node);
int* get_arr_from_list(list_node* head, int* arr_len);
int compare_arr(int arr1[], int arr2[], int arr_len);
int compare_list(list_node* list1, list_node* list2);
int compare_list_arr(list_node* list1, int arr[], int num_node);


void del_list(list_node *head);
void del_list_recur(list_node *head);

void print_list(list_node *head,char *msg);
void print_list1(list_node *head);



list_node* reverse_list(list_node* head);
list_node* reverse_list_recur1(list_node* head);
list_node* reverse_list_recur2(list_node* head);

int nth_node(list_node *head,int n);
int nth_node_from_last(list_node *head,int n);
list_node* nth_node_remove(list_node* head, int n);
list_node *nth_node_from_last_remove(list_node *A,int B);

int insert_at_pos(list_node *head,int data,int pos);
int insert_at_end(list_node *head,int data);
int insert_at_beg(list_node *head,int data);
list_node* insert(list_node *head, int data, int pos);

list_node *find(list_node *head,int data);
list_node* sort_list(list_node *head);
void list_front_back_split(list_node *head, list_node** front, list_node **back);
list_node *merge_sorted(list_node *a,list_node *b);
list_node *merge_sort(list_node *head);

list_node* k_reverse(list_node *head,int k);
list_node* k_reverse1(list_node *head,int k);
list_node* k_reverse_rec1(list_node* head, int k);

list_node* k_sort(list_node *head,int k);
list_node* k_sort1(list_node* head, int k);
list_node* k_sort_rec1(list_node* head, int k);


list_node* copy_list(list_node *head);
list_node* copy_list_n(list_node *head,int n);
list_node* copy_sub_list_n(list_node *head,int beg,int end);
list_node* sub_list(list_node **head,int start,int end);
void split_list(list_node *head,list_node **first, list_node **secnd);

list_node* rotate_left(list_node* head, int n);
list_node* rotate_right(list_node* head, int n);
list_node* reverse_between(list_node *head,int beg,int end);

void test_list();

