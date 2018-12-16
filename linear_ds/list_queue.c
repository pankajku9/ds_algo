/*  gcc -D DEBUG data_structure\list_queue.c */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


#ifdef DEBUG
#define dprintf(frmt,...)  fprintf(stdout, frmt, ##__VA_ARGS__)
#else
#define dprintf(frmt, ...)
#endif


struct qnode{
    int data;
    struct qnode* next;
};

struct qnode* new_qnode(int i)
{
	struct qnode * tail = malloc(sizeof(struct qnode));
	if (tail == NULL){
		dprintf("alloc failed for new node \n");
		return NULL;
	}

	tail->data = i;
	tail->next = tail;
	return tail;
}

struct qnode* push(struct qnode* tail, int i){
    if (tail == NULL)
    	return new_qnode(i);

    struct qnode* temp =  new_qnode(i);
    if(temp == NULL)
		return tail;

    temp->next = tail->next;;
    tail->next = temp;
    return temp;
}

int front(struct qnode* tail){
    if(tail == NULL)
        return -1;

    return tail->next->data;
}

int back(struct qnode* tail){
    if(tail == NULL)
        return -1;
    return tail->data;
}

void pop(struct qnode* tail){
    if(tail == NULL)
        return;

    struct qnode* front = tail->next;
    tail->next = front->next;
    free(front);
}


void clear(struct qnode** tail){

    struct qnode* head = (*tail)->next;
    (*tail)->next = NULL;

    while(head){
        struct qnode* temp = head->next;
        free(head);
        head = temp;
    }
    *tail = NULL;

}

void print(struct qnode* tail){
    if(tail == NULL)
            return;

    struct qnode* ptr = tail->next;
    do{
        dprintf(" %d ", ptr->data);
        ptr = ptr->next;
    }while(ptr != tail->next);
    dprintf("\n");
}

void test_queue0() {

    struct qnode* que1 = NULL;
    que1 = push(que1, 1);
    print(que1);
    que1 = push(que1, 2);
    que1 = push(que1, 3);
    print(que1);
    que1 = push(que1, 4);
    que1 = push(que1, 5);
    print(que1);
    pop(que1);
    print(que1);

    pop(que1);
    print(que1);

    pop(que1);
    print(que1);

    pop(que1);
    print(que1);
}

void test_queue(){

    struct qnode* que1 = NULL;
    que1 = push(que1, 1);
    assert(front(que1) == 1);
    assert(back(que1) == 1);

    que1 = push(que1, 2);
    que1 = push(que1, 3);

    assert(front(que1) == 1);
    assert(back(que1) == 3);

    que1 = push(que1, 4);
    que1 = push(que1, 5);

    assert(front(que1) == 1);
    assert(back(que1) == 5);

    pop(que1);
    assert(front(que1) == 2);

    pop(que1);
    assert(front(que1) == 3);

    clear(&que1);

}

void test_queue1(){
	struct qnode* q1;
	for(int i = 0; i < 10; i++)
		q1 = push(q1, i);

	for(int i = 0; i < 10; i++){
		assert(i == front(q1));
			pop(q1);
	}
}

#ifdef DEBUG
int main(){
    test_queue0();
    test_queue();
    test_queue1();
}
#endif
