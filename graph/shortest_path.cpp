/*
 * minDistanceTree.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: pankajku
 */

#include <vector>
#include <climits>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

/**

 BELLMAN-FORD(G,w,s)
1.  INITIALIZE-SINGLE-SOURCE(G,s)
2.  for i = 1 to |G.V|-1
3.     for each edge (u,v) ∈ G.E
4.        RELAX(u,v,w)
5.  for each edge (u,v) ∈ G.E
6.     if v.d > u.d + w(u,v)
7.        return FALSE
8.  return TRUE

INITIALIZE-SINGLE-SOURCE(G,s)
1.  for each vertex v ∈ G.V
2.     v.d = ∞
3.     v.pi = NIL
4.  s.d = 0

RELAX(u,v,w)
1.  if v.d > u.d + w(u,v)
2.     v.d = u.d + w(u,v)
3.     v.pi = u

 */
vector<tuple<int, int, int>>  get_edege_list(vector<vector<int>> adj_mat ){
    vector<tuple<int, int, int>> edge_list;
    for(int i = 0 ; i< adj_mat.size();i++){
        for(int j = 0; j < adj_mat[i].size(); j++){
            if(adj_mat[i][j] == -1)
                continue;

            edge_list.push_back(make_tuple(i, j, adj_mat[i][j]));
        }
    }
    return edge_list;
}


void relax(int* dis, int*par, int u, int v, int w){
    if(dis[v] > dis[u] + w){
        dis[v] = dis[u] + w;
        par[v] = u;
    }
}

void bellman_ford(vector<vector<int>>& adj_mat){

    int num_vrtx = adj_mat.size();
    vector<int> dis(num_vrtx, INT_MAX);
    vector<int> parent(num_vrtx, INT_MAX);
    dis[0] = 0;

    auto edge_list = get_edege_list(adj_mat);

    for(int v = 1; v < num_vrtx-1; ++v){
    	for(int e = 0; e < edge_list.size(); e++){

    		int u = edge_list[e][0];
    		int v = edge_list[e][1];
    		int w = edge_list[e][2];

    		relax(dis.data(), parent.data(), u, v, w);
        }
    }
    //TODO negative cycle
    bool neg_cycle = false;
    for(int e = 0; e < edge_list.size(); e++){
    }
}
/*
DIJKSTRA(G,w, s)
1 INITIALIZE-SINGLE-SOURCE(G, s)
2 S = {$};
3 Q = G:V
4 while Q not empty() ;
5 	u = EXTRACT-MIN(Q)
6   S =  S U {u}
7 	for each vertex v in  G:Adj
8 		RELAX(u, v, w)

 */
int get_min_weight_unvisited_node(vector<int>& dis, vector<bool>& visited){
	int min = INT_MAX, idx = -1;
	for(int i= 0; i < dis.size(); i++){
		if(!visited[i] && min > dis[i]){
			min = dis[i];
			idx = i;
		}
	}
	return idx;
}


void dijkastras(vector<vector<int>>& adj_mat, int s){
	int num_vrtx = adj_mat.size();
	vector<int> dis(num_vrtx, INT_MAX);
	vector<int> parent(num_vrtx, INT_MAX);
	vector<bool> visited(num_vrtx, false);
	dis[0] = 0;

	while(1){
		int vrtx = get_min_weight_unvisited_node(dis, visited);

		if(vrtx == -1)
			break;

		visited[vrtx] = true;

		for(int j = 0; j < adj_mat[vrtx].size(); j++){
			if( j == vrtx || adj_mat[vrtx][j] == -1)
				continue;
			relax(dis.data(), parent.data(), vrtx, j, adj_mat[vrtx][j]);

		}
	}
}
/* Input Graph is for each vertices there is vector pair of node and weight */
void dijkastras1(vector<vector<pair<int, int>>>& adj_list, int s){
	int num_vrtx = adj_list.size();
	vector<int> dis(num_vrtx, INT_MAX);
	vector<int> parent(num_vrtx, INT_MAX);
	vector<bool> visited(num_vrtx, false);
	dis[0] = 0;

	while(1){
		int vrtx = get_min_weight_unvisited_node(dis, visited);

		if(vrtx == -1)
			break;

		visited[vrtx] = true;

		for(int j = 0; j < adj_list[vrtx].size(); j++){
			relax(dis.data(), parent.data(), vrtx, adj_list[vrtx][j].first, adj_list[vrtx][j].second);
		}
	}


}
