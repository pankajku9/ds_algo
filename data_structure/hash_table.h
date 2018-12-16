#pragma  once

typedef struct hash_table_  hash_table;

hash_table* new_hash_table(unsigned size);
void del_hash_table(hash_table* ht);
void* htable_get(hash_table* ht, int key);
int htable_put(hash_table* ht, int key, void* data);

