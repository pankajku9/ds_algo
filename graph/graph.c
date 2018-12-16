

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>


#define RET_ERR_IF_NULL(i) do { if(i == NULL) return EXIT_FAILURE; } while(0)
#define RET_NULL_IF_NULL(i) do { if(i == NULL) return NULL; } while(0)

void write_to_path(int* path, int path_idx, int vrtx);
void write_level_end_marker(int* path, int path_idx);
int validate_input(int** adj_mat, int num_vertx, int source, int* path);
#define check_valid_edge(adj_mat, curr, i, visited) if(i == curr || adj_mat[curr][i] != 1 || visited[i]) continue
/******************************************************************/
struct gnode{
   struct gnode* next;
   int val;
};
typedef int error_t;

error_t bfs(int** adj_mat, int num_vertx, int s, int* path)
{
	int front = 0, back = 0, path_idx = 0;
	int* queue = (int*) calloc(num_vertx, sizeof(int));
	int* visited = (int*) calloc(num_vertx, sizeof(int));

	assert(validate_input(adj_mat, num_vertx, s, path) == EXIT_SUCCESS);
	queue[back++] = s;
	visited[s] = 1;

	while (front < back) {
		int num = back - front;
		while (num--) {
			int curr = queue[front++];
			write_to_path(path, path_idx++, curr);
			for (int i = 0; i < num_vertx; i++) {
				if (i == curr || adj_mat[curr][i] != 1 || visited[i])
					continue;

				queue[back++] = i;
				visited[i] = 1;
			}
		}//write_level_end_marker(path, path_idx++);
	}

	free(queue);
	free(visited);
	return EXIT_SUCCESS;
}
static void bfs2_core(int** adj_mat, int num_vertx, int source, int* path, int* queue, int* visited)
{
	int front = 0, back = 0, path_idx = 0;
	queue[back++] = source;
	visited[source] = 1;

	while (front < back) {
		int num_node_curr = back - front ;
		while (num_node_curr--) {
			int curr = queue[front++];
			write_to_path(path, path_idx++, curr);

			for (int i = 0; i < num_vertx; i++)	{
				check_valid_edge(adj_mat, curr, i, visited);
				queue[back++] = i;
				visited[i] = 1;
			}
		} //write_level_end_marker(path, path_idx++);
	}
}
error_t bfs2(int** adj_mat, int num_vertx, int source, int* path)
{
	int* queue = (int*) calloc(num_vertx, sizeof(int));
	int* visited = (int*) calloc(num_vertx, sizeof(int));

	assert(validate_input(adj_mat, num_vertx, source, path) == EXIT_SUCCESS);
	bfs2_core(adj_mat, num_vertx, source, path, queue, visited);

	free(queue);
	free(visited);

	return 0;
}
void dfs(int** adj_mat, int num_vertx, int source, int* path)
{
	int top = -1, path_idx = 0;
	int* stack = (int*) calloc(3 * num_vertx, sizeof(int));
	int* visited = (int*) calloc(num_vertx, sizeof(int));

	assert(validate_input(adj_mat, num_vertx, source, path) == EXIT_SUCCESS);
	stack[++top] = source;
	visited[source] = 1;

	while (top > -1) {
		int curr = stack[top--];
		write_to_path(path, path_idx++, curr);
		for (int i = 0; i < num_vertx; i++) {
			if (i == curr || adj_mat[curr][i] != 1 || visited[i])
				continue;

			stack[++top] = i;
			visited[i] = 1;
		}
	}

	free(stack);
	free(visited);
}
#undef check_valid_edge
/************************************************************************************************************/
void write_to_path(int* path, int path_idx, int vrtx){
	if (path)
		path[path_idx] = vrtx;
	else
		printf("%d ", vrtx);
}

void write_level_end_marker(int* path, int path_idx){
	if (path)
		path[path_idx] = -1; //level end_marker
	else
		printf("\n");
}

int validate_input(int** adj_mat, int num_vertx, int source, int* path)
{
	RET_ERR_IF_NULL(adj_mat);
	RET_ERR_IF_NULL(adj_mat+(num_vertx*num_vertx));
	//RET_ERR_IF_NULL(path);
	//RET_ERR_IF_NULL(path+num_vertx);
	if (source >= num_vertx)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
/************************************************************************************************************/
void bfs1(struct gnode** adj_list, int size, int source, int* path)
{
    int front = 0, back = 0, path_idx = 0;
    int* queue = (int*)calloc(3*size, sizeof(int));
    int* visited = (int*)calloc(size, sizeof(int));

    queue[back++] = source;
    visited[source] = 1;

    while(front < back ){
        int num = back-front;
        while(num--){
            int curr = queue[front++];
            write_to_path(path, path_idx++, curr);
            struct gnode* head = adj_list[curr];
            while(head){
                int i = head->val;
                head = head->next;
                if(i == curr || visited[i])
                    continue;

                queue[back++] = i;
                visited[i] = 1;
            }
        }
    }

    free(queue);
    free(visited);
}

void dfs1(struct gnode** adj_list, int size, int s, int* path){

    int top = -1, path_idx = 0;
    int* stack = (int*)calloc(size, sizeof(int));
    int* visited = (int*)calloc(size, sizeof(int));

    stack[++top] = s;
    visited[s] = 1;

    while(top > -1 ){
            int curr = stack[top--];
            write_to_path(path, path_idx++, curr);
            struct gnode* head = adj_list[curr];
            while(head){
                int i = head->val;
                head = head->next;
                if(i == curr  || visited[i])
                    continue;

                stack[++top] = i;
                visited[i] = 1;
            }
    }

    free(stack);
    free(visited);
}
/********************************************************************************************/

struct adj_mat{
    int size;
    int** mat;
};


struct adj_list{
    int size;
    struct gnode** data;
};

bool is_graph_edge(int val){
    return val == 1;
}

struct adj_list* alloc_adj_list(int size){
    struct adj_list* g1 = (struct adj_list*)calloc(1, sizeof(struct adj_list));
    g1->size = size;
    g1->data = (struct gnode**) calloc(size, sizeof(struct gnode*));
    for(int i = 0; i < size; i++)
        g1->data[i] = NULL;
    return g1;
}
struct adj_mat* alloc_adj_mat(int size){
    struct adj_mat* g1 = (struct adj_mat*)calloc(1, sizeof(struct adj_mat));
    g1->size = size;
    g1->mat = (int**) calloc(size, sizeof(int*));
    for(int i = 0; i < size; i++){
        g1->mat[i] = (int*)calloc(size, sizeof(int));
        memset(g1->mat[i], -1, sizeof(int)*size);
    }
    return g1;
}
static void del_list(struct gnode* list){
    struct gnode* temp;
    while(list){
        temp = list->next;
        free(list);
        list = temp;
    }
}
void free_adj_list(struct adj_list ** g1){
    struct adj_list * g = *g1;
    for(int i = 0; i < g->size; i++){
       del_list(g->data[i]);
       g->data[i] = NULL;
    }
    free(g->data);
    free(g);
    *g1 = NULL;
}
void free_adj_mat(struct adj_mat** g1){
    struct adj_mat* g = *g1;
    for(int i = 0; i < g->size; i++){
       free(g->mat[i]);
       g->mat[i] = NULL;
    }
    free(g->mat);
    free(g);
    *g1 = NULL;
}

void print_adj_list(struct adj_list* g1, const char* msg){
    printf(" %s \n", msg);
        for(int i = 0; i < g1->size; i++){
            printf("%d {", i);
            struct gnode* head = g1->data[i];
            while(head){
                printf("%d ", head->val);
                head = head->next;
            }
            printf("}\n");
        }
}

void print_adj_mat(struct adj_mat* mat, const char* msg){
    printf(" %s \n", msg);
    for(int i = 0; i < mat->size; i++){
        for(int j = 0; j < mat->size; j++){
            printf("%2d ", mat->mat[i][j]);
        }
        printf("\n");
    }
}



struct adj_mat* convert_list_to_mat(struct adj_list* g1){
    struct adj_mat* g2 = alloc_adj_mat(g1->size);
    for(int i = 0; i < g1->size; i++){
        struct gnode* head = g1->data[i];
        while(head){
            g2->mat[i][head->val] = 1;
            head = head->next;
        }
    }
    return g2;
}

struct gnode* new_gnode(int j){
    struct gnode* temp = (struct gnode*)malloc(sizeof(struct gnode));
    temp->val = j;
    temp->next = NULL;
    return temp;
}

struct adj_list*  convert_mat_to_list(struct adj_mat* g1){
    struct gnode* temp;
    struct adj_list* g2 = alloc_adj_list(g1->size);
    for(int i = 0; i < g1->size; i++){
        for(int j = 0; j < g1->size; j++){
            if(j == i || !is_graph_edge(g1->mat[i][j]))
                continue;
            if(g2->data[i] == NULL){
                g2->data[i] = new_gnode(j);
            }
            else{
                temp = g2->data[i];
                while(temp->next){
                    temp = temp->next;
                }
                temp->next = new_gnode(j);
            }
        }
    }
    return g2;
}
int compare_arr(int* arr1, int* arr2, int len){

	int i = 0;
	while(i < len){
		if(arr1[i] != arr2[i])
			return EXIT_FAILURE;
		i++;
	}
	return EXIT_SUCCESS;
}
void print_arr(int* arr, int arr_len)
{
	printf("V:%d G: ", arr_len);
	for (int i = 0; i < arr_len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/*    0-----2
 *    | \   |\
 *    |  \  | \
 *    |   \ |  \
 *    1-----3	\
 *     \		 \
 *      \	      \
 *       \---------4    */

int bfs_output0[] = {0,1,2,3,4};
int dfs_output0[] = {0,3,2,4,1};

int bfs_output3[] = {3,0,1,2,4};
int dfs_output3[] = {3,2,4,1,0};

int bfs_output4[] = {4,1,2,0,3};
int dfs_output4[] = {4,2,3,0,1};


int source[] = {0,3,4};
int* bfs_output[] = {bfs_output0, bfs_output3, bfs_output4};
int* dfs_output[] = {dfs_output0, dfs_output3, dfs_output4};

struct adj_mat* create_graph(int num_vertx)
{
    struct adj_mat*  g1 = alloc_adj_mat(num_vertx);
    g1->size = num_vertx;

    g1->mat[0][1] = 1;
    g1->mat[0][2] = 1;
    g1->mat[0][3] = 1;

    g1->mat[1][0] = 1;
    g1->mat[1][3] = 1;
    g1->mat[1][4] = 1;

    g1->mat[2][0] = 1;
    g1->mat[2][3] = 1;
    g1->mat[2][4] = 1;

    g1->mat[3][0] = 1;
    g1->mat[3][1] = 1;
    g1->mat[3][2] = 1;

    g1->mat[4][1] = 1;
    g1->mat[4][2] = 1;

    return g1;
}
void test_adj_mat()
{
	int num_vertex = 5;
	struct adj_mat* g1 = create_graph(num_vertex);
	//print_adj_mat(g1, " adj_mat");

	for (int i = 0; i < 3; i++) {
		int* path = malloc(sizeof(int) * 2 * num_vertex);
		bfs2(g1->mat, g1->size, source[i], path);
		assert(compare_arr(path, bfs_output[i], num_vertex) == EXIT_SUCCESS);

		memset(path, -1, num_vertex);
		bfs(g1->mat, g1->size, source[i], path);
		assert(compare_arr(path, bfs_output[i], num_vertex) == EXIT_SUCCESS);

		memset(path, -1, num_vertex);
		dfs(g1->mat, g1->size, source[i], path);
		//print_arr(dfs_output[i], num_vertex);
		assert(compare_arr(path, dfs_output[i], num_vertex) == EXIT_SUCCESS);

		free(path);
	}

	free_adj_mat(&g1);
}

void test_adj_list()
{
	int num_vertex = 5;
	struct adj_mat* g1 = create_graph(num_vertex);
	struct adj_list *g2 = convert_mat_to_list(g1);
	//print_adj_list(g2, " adj_list");

	for (int i = 0; i < 3; i++) {
		int* path = malloc(sizeof(int) * 2 * num_vertex);

		memset(path, -1, num_vertex);
		bfs1(g2->data, g2->size, source[i], path);
		assert(compare_arr(path, bfs_output[i], num_vertex) == EXIT_SUCCESS);

		memset(path, -1, num_vertex);
		dfs1(g2->data, g2->size, source[i], path);
		assert(compare_arr(path, dfs_output[i], num_vertex) == EXIT_SUCCESS);

		free(path);
	}
	free_adj_list(&g2);
	free_adj_mat(&g1);
}

void test_list(){
	test_adj_mat();
	test_adj_list();
}

int main(int argc, char** argv){
	test_list();
}


