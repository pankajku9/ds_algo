#include "../../ds_algo1/data_structure/hash_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


#define HMAGIC 0xFFFFF123

typedef struct ht_bucket_ {
    void* data;
    unsigned long key;
    struct ht_bucket_* next;
} ht_bucket;


typedef struct hash_table_ {
    ht_bucket** ht_entries;
    unsigned size;
    unsigned long magic;
} hash_table;


hash_table* new_hash_table(unsigned size)
{
	hash_table *ht = malloc(sizeof(hash_table));
	ht->ht_entries = malloc(sizeof(ht_bucket*) * size);
	ht->size = size;
	for (int i = 0; i < size; i++)
		ht->ht_entries[i] = NULL;
	ht->magic = HMAGIC;
	return ht;
}

void del_list(ht_bucket* head)
{
	while (head) {
		ht_bucket* node_to_del = head;
		head = head->next;
		free(node_to_del);
	}
}

void del_hash_table(hash_table* ht)
{
	for (int i = 0; i < ht->size; i++)
		del_list(ht->ht_entries[i]);

	free(ht->ht_entries);
	free(ht);
}

int is_ht_valid(hash_table* ht)
{
	if (ht == NULL)
		return -1;
	if (ht->magic != HMAGIC)
		return -2;

	if (ht->ht_entries == NULL)
		return -3;

	return 0;
}

//TODO make hash function as user input
int hash_function(hash_table* ht, unsigned long key)
{
	return key % ht->size;
}

void* htable_get(hash_table* ht, int key)
{
	int ret = is_ht_valid(ht);
	if (ret != 0)
		return NULL;

	int index = hash_function(ht, key);
	ht_bucket *curr = ht->ht_entries[index];
	while (curr != NULL) {
		if (curr->key == key) {
			return curr->data;
		}
		curr = curr->next;
	}
	return NULL;
}

int htable_put(hash_table* ht, int key, void* data)
{

	int ret = is_ht_valid(ht);
	if (ret != 0)
		return -1;

	int index = hash_function(ht, key);
	ht_bucket *curr = ht->ht_entries[index];

	ht_bucket *in = malloc(sizeof(ht_bucket));
	in->key = key;
	in->data = data;
	in->next = NULL;

	if (curr == NULL) {
		ht->ht_entries[index] = in;
		return 0;
	}

	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = in;

	return 0;
}

void test_insert()
{
	hash_table *ht = new_hash_table(5);

	int ret = is_ht_valid(ht);
	assert(0 == ret);

	assert(NULL == htable_get(ht, 1));
	assert(NULL == htable_get(ht, 100));

	char *data = "pankaj";

	ret = htable_put(ht, 3, data);
	assert(0 == ret);
	ret = strcmp(data, (char*) htable_get(ht, 3));
	assert(ret == 0);

	int x = 45;
	htable_put(ht, 4, &x);
	assert(45 == *(int* )htable_get(ht, 4));

	del_hash_table(ht);

}

void test2()
{
	hash_table ht;

	assert(-1 == htable_put(&ht, 3, "pankaj"));
	assert(NULL == htable_get(&ht, 3));

}

void test3() {
	hash_table *ht = new_hash_table(2);

	char *data = "pankaj";

	int ret = htable_put(ht, 3, "pankaj3");
	assert(0 == ret);

	ret = htable_put(ht, 4, "pankaj4");
	assert(0 == ret);

	ret = htable_put(ht, 5, "pankaj5");
	assert(0 == ret);

	ret = htable_put(ht, 6, "pankaj6");
	assert(0 == ret);

	ret = strcmp("pankaj3", (char*) htable_get(ht, 3));
	assert(ret == 0);

	ret = strcmp("pankaj4", (char*) htable_get(ht, 4));
	assert(ret == 0);

	ret = strcmp("pankaj5", (char*) htable_get(ht, 5));
	assert(ret == 0);

	ret = strcmp("pankaj6", (char*) htable_get(ht, 6));
	assert(ret == 0);

	del_hash_table(ht);

}

int hash_table_test() {

	test_insert();
	test2();
	test3();
	printf("All Test passed for Hash Table");

	return 0;

}

