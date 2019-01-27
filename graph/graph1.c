#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void bfs(int** adj_mat, int V, int source, int* parent){
    
    int* queue = calloc(V, sizeof(int));
    int front = 0, back = -1;
    
    for(int i = 0; i< V; i++)
        parent[i] = -1;
    
    queue[++back] = source;
    parent[source] = source;
    
    while(front <= back){
        int curr = queue[front++];
        for(int i = 0; i< V; i++){
            if(i == curr || adj_mat[curr][i] == 0 ) 
                continue;
            if(parent[i] == -1){
                parent[i] = curr;
                queue[++back] = i;
            }
        }
        printf("%d ", curr);
    }
}

void dfs_util(int** adj_mat, int V, int source, int* parent){
    printf("%d ", source);    
    for(int i = 0; i< V; i++){
        if(i == source || adj_mat[source][i] == 0) // || parent[i] != -1)
            continue;
        if(parent[i] == -1){
            parent[i] = source;
            dfs_util(adj_mat, V, i, parent);
        }
    }
}

void dfs(int** adj_mat, int V, int source, int* parent)
{
    for(int i = 0; i< V; i++)
        parent[i] = -1;
    parent[source] = source;
    dfs_util(adj_mat, V, source, parent);
}

void dfs1(int** adj_mat, int V, int source, int* parent) {
    int* stack = malloc(sizeof(int)*V);
    int top = -1;
    
    for(int i = 0; i< V; i++)
        parent[i] = -1;
    
    stack[++top] = source;
    parent[source] = source;
    
    while(top > -1){
        int curr = stack[top--];
        for(int i = 0; i< V; i++){
            if(i == source || adj_mat[source][i] == 0 ) //|| parent[i] != -1)
                continue;
            if(parent[i] == -1){
                parent[i] = source;
                stack[++top] = i;
            }
        }
    }        
    free(stack);
}

void relax(int *dis, int* par, int u, int w, int v){
    if(dis[u]+w < dis[v]){
        dis[v]= dis[u]+w;
        par[v] = u;
    }
}

void init_single_source(int source, int V, int* parent, int* dis)
{
    for(int i = 0; i< V; i++){
        parent[i] = -1;
        dis[i] = INT_MAX;
    }
    parent[source] = source;
    dis[source] = 0;
}

int extract_min(int* queue, int front, int back, int* dis){    
    int min = INT_MAX, min_v = 0;
    for(int idx = front; idx <= back; idx++){
       if(dis[queue[idx]] < min){
            min = dis[idx];
            min_v = idx;
        }
    }
    int temp = queue[min_v];
    queue[min_v] = queue[front];
    return temp;
}

void dijkastra(int** adj_mat, int V, int source, int* parent, int* dis)
{
    int front = 0, back = -1;
    int* queue = calloc(V, sizeof(int));
    queue[++back] = source;
    
    init_single_source(source, V, parent, dis);   
    while(front <= back){
        int curr = extract_min(queue, front, back, dis);
        front = front+1;
        for(int i = 0; i< V; i++){
            // if(i == curr || adj_mat[curr][i] == 0 ) 
                // continue;
            if(parent[i] == -1)
                queue[++back] = i;
            relax(dis, parent, curr, adj_mat[curr][i], i);
            
        }
    }
}
/**
 
INITIALIZE-SINGLE-SOURCE(G,s)
1.  for each vertex v ? G.V
2.     v.d = 8
3.     v.pi = NIL
4.  s.d = 0
RELAX(u,v,w)
1.  if v.d > u.d + w(u,v)
2.     v.d = u.d + w(u,v)
3.     v.pi = u
BELLMAN-FORD(G,w,s)
1.  INITIALIZE-SINGLE-SOURCE(G,s)
2.  for i = 1 to |G.V|0
3.     for each edge (u,v) ? G.E
4.        RELAX(u,v,w)
5.  for each edge (u,v) ? G.E
6.     if v.d > u.d + w(u,v)
7.        return FALSE
8.  return TRUE
 */



 void print_a(int* arr, int n)
 {
     for(int i = 0; i < n; i++){
         printf(" %d", arr[i]);
     }
     printf("\n");
 }
 void bellman_ford(int** adj_mat, int num_vertx, int source, int* parent, int* dis)
 {  
    init_single_source(source, num_vertx, parent, dis);   
    for(int i = 0; i< num_vertx; i++){
         printf(" I: %d",i);
         print_a(dis, num_vertx);
         for(int u = 0; u< num_vertx; u++)
         {
             for(int v = 0; v< num_vertx; v++)
             {
               if(u == v || adj_mat[u][v] == 0 ) 
                continue;
            
               relax(dis, parent, u, adj_mat[u][v], v);  
            }
            //printf("   u: %d",i);
            //print_a(dis, num_vertx);
         }
     }
 }
void test_bfs(){
    int v1[] = {0,1,0};
    int v2[] = {1,0,1};
    int v3[] = {0,1,0};
    int* adj_mat[] = {v1, v2, v3};
    int parent[3] = {0};
    
    bfs(adj_mat, 3, 0, parent);
    printf("\n");
    dfs(adj_mat, 3, 0, parent);
    printf("\n");
}
void test_bfs1(){
    int v1[] = {0, 1, 1,0,0};
    int v2[] = { 1,0,0, 1,0};
    int v3[] = { 1,0,0,0, 1};
    int v4[] = {0, 1,0,0, 1};
    int v5[] = {0,0, 1, 1,0};
    int* adj_mat[] = {v1, v2, v3, v4, v5};
    int parent[5];
    int dis[5];
    
    bfs(adj_mat, 5, 0, parent);
    printf("\n");
    dfs(adj_mat, 5, 0, parent);
    printf("\n");
    dfs1(adj_mat, 5, 0, parent);
    printf("\n");
    dijkastra(adj_mat, 5, 0, parent, dis);
    print_a(dis,5);
    bellman_ford(adj_mat, 5, 0, parent, dis);
    print_a(dis,5);
   
}

void test_bfs3(){
    int v1[] = {0,5, 5,0,0};
    int v2[] = { 5,0,0,10,0};
    int v3[] = { 5,0,0,0, 10};
    int v4[] = {0, 10,0,0, 10};
    int v5[] = {0,0, 10, 10,0};
    int* adj_mat[] = {v1, v2, v3, v4, v5};
    int parent[5];
    int dis[5];
    
    dijkastra(adj_mat, 5, 0, parent, dis);
    print_a(dis,5);
     
    bellman_ford(adj_mat, 5, 0, parent, dis);
    print_a(dis,5);
   
}

/*
During execution of the algorithm, all vertices that are not in the tree reside in a min-priority queue Q based on a key attribute.
For each vertex, the attribute v.key is the minimum weight of any edge connecting to a vertex in the tree; 
by convention,v.k = infinity if there is no such edge. 

The attribute parent [v] names the parent of v in the tree.
*/
int spanning_tree_prims(int** adj_mat, int V, int source, int* parents)
{
    int front = 0, back = -1;
    int* queue = malloc(V*sizeof(int));
    int* weights = malloc(sizeof(int)*V);
    
    queue[++back] = source;
    init_single_source(source, V, parents, weights);
    while(front <= back){
        int curr = extract_min(queue, front, back, weights);
        front = front+1;
        printf(" cur: %d ", curr);
        for(int i = front; i< back; i++){
            printf("(%d %d) ", queue[i], weights[queue[i]]);
        }
        for(int i = 0; i< V; i++){
             if(i == curr || adj_mat[curr][i] == 0 ) 
                 continue;
            if(parents[i] == -1){
                queue[++back] = i;
                parents[i] = curr;
            }
            if( adj_mat[curr][i] < weights[i] ){
                weights[i] = adj_mat[curr][i];
                parents[i] = curr;
            }
            
        }
        //TODO handle black node
    }
    print_a(parents,5);
    
    int sum = 0;
    for(int i = 0; i< V; i++)
    {   
        if(i == source && parents[i] < V)
            continue;
        printf("(%d %d - %d ) ",parents[i],i, adj_mat[parents[i]][i]);
        sum += adj_mat[parents[i]][i];
    }
    return sum;
    
}


void test_bfs4(){
    int v1[] = {0,5, 5,0,0};
    int v2[] = { 5,0,0,10,0};
    int v3[] = { 5,0,0,0, 10};
    int v4[] = {0, 10,0,0, 10};
    int v5[] = {0,0, 10, 10,0};
    int* adj_mat[] = {v1, v2, v3, v4, v5};
    int parent[5];
    spanning_tree_prims(adj_mat, 5, 0, parent);
    print_a(parent,5);
    
   
}

int main(){
    //test_bfs();
    //test_bfs1();
    //test_bfs3();
    
    test_bfs4();
}
