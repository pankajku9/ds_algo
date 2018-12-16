/*
 * spanning_tree.c
 *
 *  Created on: Dec 3, 2018
 *      Author: pankajku
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_EDGE 20

void ds_init(int** par, int V);
int ds_root(int* parents, int x);
void ds_union(int* parent, int x, int y);
void ds_print(int* parent, int V);

struct edge{
    int w, u, v;
};

struct edge_list{
    int num;
    struct edge * edges;
};

/*****************************************************************************************************/
struct edge_list* get_sorted_edges(int** adj_mat, int V);

int mst_kruskal(int** adj_mat, int V){
    struct edge_list* edges = get_sorted_edges(adj_mat, V);
    int* ds_vrtx;
    ds_init(&ds_vrtx, V);
    int mst_eght = 0;

    for(int i = 0; i < edges->num; i++){

    	printf(" %d %d %d ", i, edges->edges[i].u, edges->edges[i].v);
    	ds_print(ds_vrtx, V);

        if(ds_root(ds_vrtx, edges->edges[i].u) == ds_root(ds_vrtx, edges->edges[i].v))
            continue;

        mst_eght += edges->edges[i].w;
        ds_union(ds_vrtx, edges->edges[i].u, edges->edges[i].v);

    }

    return mst_eght;
}

int compare(const void* e1, const void* e2){
    return ((struct edge*)e1)->w <  ((struct edge*)e1)->w;
}

struct edge_list* get_sorted_edges(int** adj_mat, int V){

    struct edge_list *list1 = calloc(1, sizeof(struct edge_list));
    list1->edges = calloc(MAX_EDGE, sizeof(struct edge));

    int num = 0;
    for(int i = 0; i < V; i++){
        for(int j = 0; j< V; j++){
            if(i == j || adj_mat[i][j] == -1)
                continue;

            list1->edges[num].w = adj_mat[i][j];
            list1->edges[num].u = i;
            list1->edges[num].v = j;
            num++;
        }
    }

    qsort(list1->edges, num, sizeof(struct edge), compare);

    return list1;

}
/**********************************************************************************************************/

void ds_init(int** par, int V){
    int* parent = calloc(V, sizeof(int));
    for(int i = 0; i < V; i++)
        parent[i] = i;
    *par = parent;
}

int ds_root(int* parents, int x){
    while(x != parents[x]){
        parents[x] = parents[parents[x]];
        x = parents[x];
    }
    return x;
}

void ds_union(int* parent, int x, int y){
    int px = ds_root(parent, x);
    int py = ds_root(parent, y);

    if(px != py)
        parent[px] = py;

}
void ds_print(int* parent, int V){
	for(int i = 0; i < V; i++)
		printf("%d ", parent[i]);
	printf("\n");

}

/**********************************************************************************************************/

struct adj_mat{
    int size;
    int** mat;
};

void print_adj_mat(struct adj_mat* mat, const char* msg){
    printf(" %s \n", msg);
    for(int i = 0; i < mat->size; i++){
        for(int j = 0; j < mat->size; j++){
            printf("%2d ", mat->mat[i][j]);
        }
        printf("\n");
    }
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

struct adj_mat* create_graph(){

    int vertices = 5;
    struct adj_mat*  g1 = alloc_adj_mat(vertices);

    g1->size = vertices;
    g1->mat[0][1] = 1;
    g1->mat[0][2] = 1;
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
//TODO test disjoint and add more test case
void test_spanning_tree(){

	struct adj_mat* mat1 = create_graph();
	print_adj_mat(mat1, " first");

	int w = mst_kruskal(mat1->mat, mat1->size);
	printf(" Minimum Weight : %d", w);

}

int main(){
	test_spanning_tree();
}
