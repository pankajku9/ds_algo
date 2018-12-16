#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ALPHABET_SIZE (5)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define INDEX_TO_CHAR(i) ((char)('a'+i))
#define my_sizeof(type) (char *)(&type+1)-(char*)(&type)
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

#define MAX_NODE 256

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}


typedef struct trie_node {
	struct trie_node * child[ALPHABET_SIZE];
} trie_node;

trie_node* new_trie_node()
{
	int i;
	trie_node *node = (trie_node*) malloc(sizeof(trie_node));
	for (i = 0; i < ALPHABET_SIZE; i++) {
		node->child[i] = NULL;
	}
	return node;
}

void add_word(trie_node * triePtr, char * word)
{
	int len = strlen(word);
	for (int i = 0; i < len; i++) {
		int indx = CHAR_TO_INDEX(word[i]);
		if (!(triePtr->child[indx]))
			triePtr->child[indx] = new_trie_node();
		triePtr = triePtr->child[indx];
	}
}

int valid_word(char* word){
	if (!strcmp(word, "") || word[0] == '\0') {
		printf("Word Added");
		return 0;
	}
	return 1;
}
void add_word1(trie_node * node, char * word)
{
	if(!valid_word(word))
		return;

	int indx = CHAR_TO_INDEX(*word);
	if (!(node->child[indx]))
		node->child[indx] = new_trie_node();
	word++;
	add_word1(node->child[indx], word);

}

void add_word2(trie_node * root, char* word)
{
	while((*word) && root){
		int indx = CHAR_TO_INDEX(*word);
		if(!(root->child[indx]))
			root->child[indx] = new_trie_node();
		word++;
		root = root->child[indx];
	}
}


int count_nodes(trie_node *root)
{
	trie_node **tq = calloc(MAX_NODE, sizeof(trie_node*));
	int count = 0, front = 0, back = -1;
	tq[++back] = root;

	while(front <= back){
		trie_node* curr = tq[front++];
		for(int i = 0; i< ALPHABET_SIZE; i++){
			if(curr->child[i]){
				tq[++back] = curr->child[i];
				count++;
			}
		}
	}
	return count;
}

void free_trie(trie_node *root)
{
	trie_node **tq = calloc(MAX_NODE, sizeof(trie_node*));
	int count = 0, front = 0, back = -1;
	tq[++back] = root;

	while(front <= back){
		trie_node* curr = tq[front++];
		for(int i = 0; i< ALPHABET_SIZE; i++){
			if(curr->child[i]){
				tq[++back] = curr->child[i];
			}
		}
		free(curr);
		curr = NULL;
	}
}

void get_all_nodes_level_order(trie_node* root, char* path)
{
	trie_node **tq = calloc(MAX_NODE, sizeof(trie_node*));
	int count = 0, front = 0, back = -1;
	tq[++back] = root;

	while(front <= back){
		trie_node* curr = tq[front++];
		for(int i = 0; i< ALPHABET_SIZE; i++){
			if(curr->child[i]){
				tq[++back] = curr->child[i];
				path[count++] = INDEX_TO_CHAR(i);
			}
		}
	}
}

void print_trie(trie_node *root)
{
	trie_node **tq = calloc(MAX_NODE, sizeof(trie_node*));
	int front = 0, back = -1;
	printf("\n");
	tq[++back] = root;

	while (front <= back) {
		int count = back - front + 1;
		while (count--) {
			trie_node * triePtr = tq[front++];
			for (int i = 0; i < ALPHABET_SIZE; i++) {
				int indx = CHAR_TO_INDEX(INDEX_TO_CHAR(i));
				if (triePtr->child[indx] != NULL) {
					tq[++back] = triePtr->child[indx];
					printf(" %c", INDEX_TO_CHAR(i));
				}
			}
		}
		printf("\n");
	}
}

typedef void (*add_word_t)(trie_node * root, char * word);

void test_trie0(){
	char* str1 = "ab";
	char* str2 = "ac";
	char* res = "abc";

	add_word_t funcs[3];
	funcs[0] = add_word1;
	funcs[1] = add_word2;
	funcs[2] = add_word;

	for(int i = 0; i < 3; i++){
		trie_node  *t1 = new_trie_node();
		funcs[i](t1, str1);
		funcs[i](t1, str2);
		print_trie(t1);

		int count = count_nodes(t1);
		char* ans = calloc(count+1,sizeof(char));
		get_all_nodes_level_order(t1, ans);
		assert(strcmp(res, ans) == 0);
		free(ans);
		free_trie(t1);
	}
}

void test_trie1(){

	char* res = "aabccddd";

	add_word_t funcs[3];
	funcs[0] = add_word1;
	funcs[1] = add_word2;
	funcs[2] = add_word;

	for(int i = 0; i < 3; i++){
		trie_node  *t1 = new_trie_node();
		funcs[i](t1, "aa");
		funcs[i](t1, "ab");
		funcs[i](t1, "abc");
		funcs[i](t1, "abcd");
		funcs[i](t1, "acd");
		funcs[i](t1, "abd");
		print_trie(t1);

		int count = count_nodes(t1);
		char* ans = calloc(count+1,sizeof(char));
		get_all_nodes_level_order(t1, ans);
		//printf(" %s %s ", res, ans);
		assert(strcmp(res, ans) == 0);
		free(ans);
		free_trie(t1);
	}

}


int main()
{
	test_trie0();
	test_trie1();
	return 0;
}

