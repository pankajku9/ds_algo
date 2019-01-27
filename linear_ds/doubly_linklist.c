
#include <stdio.h>
#include <stdlib.h>

typedef struct dlist_node{
    int val;
    struct dlist_node * next;
    struct dlist_node * prev;
} dlist_node;

dlist_node* make_node(int val){
    dlist_node* temp = malloc(sizeof(dlist_node));
    if(!temp)
        return NULL;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

dlist_node* push_front(dlist_node* head, int val){

    dlist_node* temp = make_node(val);
    if(head){
        head->prev = temp;
        temp->next = head;
    }
    return temp;
}

dlist_node* push_back(dlist_node* tail, int val){
    dlist_node* temp = make_node(val);
    if(!temp)
            return NULL;
    if(tail){
        tail->next = temp;
        temp->prev = tail;
    }
    return temp;
}

dlist_node* pop_front(dlist_node* head){
    dlist_node* new_head = head->next;
    if(new_head){
        new_head->prev = NULL;
    }
    free(head);
    return new_head;
}

dlist_node* pop_back(dlist_node* tail){
    dlist_node* new_tail = tail->prev;
    if(new_tail){
        new_tail->next = NULL;
    }
    free(tail);
    return new_tail;
}

dlist_node* add_at(dlist_node* head, int pos, int val){

    dlist_node* head1 = head;
    int i = 0;
    for(; i < pos && head1; i++)
        head1 = head1->next;

    if(i != pos)
        return NULL;

    dlist_node* temp = make_node(val);
    if(!temp)
        return NULL;

    if(i == 0){
        temp->next = head;
        head->prev = temp;
        return temp;
    }

    temp->next = head1->next;
    if(head1->next)
        head1->next->prev = temp;
    head1->next = temp;
    temp->prev = head1;

    return head;
}
#ifndef DISABLE_TEST_AND_LOCAL_MAIN
int main(){
}
#endif
