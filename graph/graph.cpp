/*
 * graph.cpp
 *
 *  Created on: Nov 30, 2018
 *      Author: pankajku
 */

#include <vector>
#include <cstdio>
#include <queue>
#include <stack>
#include <unordered_map>
#include <cassert>

using namespace std;

//#define DEBUG 1
#ifdef DEBUG
#define dprintf(frmt, ...)  fprintf(stdout, frmt, ##__VA_ARGS__)
#else
#define dprintf(frmt, ...)

#endif
#define test_com_mark()   fprintf(stdout, "%s passed\n", __PRETTY_FUNCTION__)

vector<vector<int>> bfs(vector<vector<int>>& adj_mat, int source)
{
	int num_vertx = adj_mat.size();
	vector<vector<int>> ans;
	queue<int> trav;
	vector<int> visited(num_vertx, 0);
	if (source > num_vertx)
		return ans;

	trav.push(source);
	visited[source] = 1;

	while (!trav.empty()) {
		int count = trav.size();
		vector<int> nodes_at_curr_lvl;
		while (count--) {
			int curr_node = trav.front();
			trav.pop();
			dprintf("%d ", curr_node);
			nodes_at_curr_lvl.push_back(curr_node);

			for (int i = 0; i < num_vertx; i++) {
				if (adj_mat[curr_node][i] == -1)
					continue;
				if (i != curr_node && visited[i] == 0) {
					trav.push(i);
					visited[i] = 1;
				}
			}
		}
		ans.push_back(nodes_at_curr_lvl);
		dprintf("\n");
	}
	return ans;

}

vector<int> dfs(vector<vector<int>>& adj_mat, int s)
{
	int V = adj_mat.size();
	vector<int> ans;
	stack<int> trav;
	vector<int> visited(V, 0);
	if (s > V)
		return ans;

	trav.push(s);
	visited[s] = 1;

	while (!trav.empty()) {
		int curr_node = trav.top();
		trav.pop();
		dprintf("%d ", curr_node);
		ans.push_back(curr_node);

		for (int i = 0; i < V; i++) {
			if (adj_mat[curr_node][i] == -1)
				continue;
			if (i != curr_node && visited[i] == 0) {
				trav.push(i);
				visited[i] = 1;
			}
		}
	}

	return ans;
}

void dfs_recur__(vector<vector<int>>& adj_mat, int s, vector<int>& visited, vector<int>& path)
{
	int V = adj_mat.size();
	visited[s] = 1;
	dprintf(" %d", s);
	path.push_back(s);

	for (int i = 0; i < V; i++) {
		if (adj_mat[s][i] == -1)
			continue;

		if (i != s && visited[i] == 0) {
			dfs_recur__(adj_mat, i, visited, path);
		}
	}
}

vector<int> dfs_recur(vector<vector<int>>& adj_mat, int s)
{
	int V = adj_mat.size();
	vector<int> path;
	vector<int> visited(V, 0);
	if (s > V)
		return path;

	dfs_recur__(adj_mat, s, visited, path);

	return path;
}

int num_connected_com(vector<vector<int>>& adj_mat)
{
	int V = adj_mat.size();
	vector<int> visited(V, 0);
	vector<int> path;
	int cc_count = 0;
	for (int i = 0; i < V; i++) {
		if (visited[i] == 0) {
			dfs_recur__(adj_mat, i, visited, path);
			cc_count++;
		}
	}
	return cc_count;
}

unordered_map<int, vector<int>> get_adj_list(vector<vector<int>>& adj_mat)
{
	unordered_map<int, vector<int>> graph_edge;
	for (int i = 0; i < adj_mat.size(); i++) {
		dprintf(" %d : { ", i);
		std::vector<int> edges;
		for (int j = 0; j < adj_mat[i].size(); j++) {
			if (adj_mat[i][j] == 1) {
				edges.push_back(j);
				dprintf("%d ", j);
			}
		}
		graph_edge[i] = edges;
		edges.clear();
		dprintf("} \n");
	}
	return graph_edge;
}

vector<vector<int>> get_adj_mat(unordered_map<int, vector<int>>& edge_list)
{
	int V = edge_list.size();
	vector<vector<int>> adj_mat(V, vector<int>(V, -1));
	for (auto& a : edge_list) {
		for (auto b : a.second) {
			adj_mat[a.first][b] = 1;
		}
	}
	return adj_mat;
}

/***************************************************************************************/
vector<vector<int>> create_graph()
{
	int vertices = 5;
	vector<vector<int>> adj_mat(vertices, std::vector<int>(vertices, -1));

	adj_mat[0][1] = 1;
	adj_mat[0][2] = 1;
	//adj_mat[0][3] = 1;

	adj_mat[1][0] = 1;
	adj_mat[1][3] = 1;
	adj_mat[1][4] = 1;

	adj_mat[2][0] = 1;
	adj_mat[2][3] = 1;
	adj_mat[2][4] = 1;

	adj_mat[3][0] = 1; //TODO correct
	adj_mat[3][1] = 1;
	adj_mat[3][2] = 1;

	adj_mat[4][1] = 1;
	adj_mat[4][2] = 1;

	return adj_mat;
}

void print_graph(vector<vector<int>> adj_mat)
{
	for (int i = 0; i < adj_mat.size(); i++)
		for (int j = 0; j < adj_mat[i].size(); j++)
			dprintf(" %2d" , adj_mat[i][j]); dprintf("\n");
	dprintf("\n");
}

void test_bfs()
{
	auto adj_mat = create_graph();
	print_graph(adj_mat);

	vector<vector<int>> ans1 = { { 0 }, { 1, 2 }, { 3, 4 } };
	auto ans2 = bfs(adj_mat, 0);
	assert(ans1 == ans2);

	vector<vector<int>> ans3 = { { 4 }, { 1, 2 }, { 0, 3 } };
	auto ans4 = bfs(adj_mat, 4);
	assert(ans3 == ans4);
	test_com_mark();
}

void test_dfs()
{
	auto adj_mat = create_graph();
	print_graph(adj_mat);

	vector<int> ans1 = { 0, 2, 4, 3, 1 };
	auto ans2 = dfs(adj_mat, 0);
	assert(ans1 == ans2);

	dprintf("\n");
	vector<int> ans3 = { 4, 2, 3, 0, 1 };
	auto ans4 = dfs(adj_mat, 4);
	assert(ans3 == ans4); dprintf("\n");
	test_com_mark();
}

void test_dfs_recur()
{
	auto adj_mat = create_graph();
	print_graph(adj_mat);

	vector<int> ans1 = { 0, 1, 3, 2, 4 };
	auto ans2 = dfs_recur(adj_mat, 0);
	assert(ans1 == ans2);

	dprintf("\n");
	vector<int> ans3 = { 4, 1, 0, 2, 3 };
	auto ans4 = dfs_recur(adj_mat, 4);
	assert(ans3 == ans4); dprintf("\n");
	test_com_mark();
}

vector<vector<int>> create_graph1()
{
	int vertices = 5;
	vector<vector<int>> adj_mat(vertices, std::vector<int>(vertices, -1));
	adj_mat[0][1] = 1;
	adj_mat[0][2] = 1;

	adj_mat[1][0] = 1;
	adj_mat[1][2] = 1;

	adj_mat[2][0] = 1;
	adj_mat[2][1] = 1;

	adj_mat[3][4] = 1;

	adj_mat[4][3] = 1;

	return adj_mat;
}

void test_count_cc()
{
	auto g1 = create_graph1();
	auto cc = num_connected_com(g1);
	dprintf("\nCC =  %d", cc);
	assert(cc == 2);
	test_com_mark();
}

void test_graph_edge()
{
	unordered_map<int, vector<int>> graph_edge1 = { { 0, { 1, 2 } }, { 1, { 0, 3, 4 } }, { 2, { 0, 3, 4 } }, { 3, { 0,
			1, 2 } }, { 4, { 1, 2 } } };
	auto adj_mat = create_graph();
	print_graph(adj_mat);
	auto graph_edge2 = get_adj_list(adj_mat);
	assert(graph_edge1 == graph_edge2);
	test_com_mark();

}

void test_adj_mat()
{
	unordered_map<int, vector<int>> edge_list1 = { { 0, { 1, 2 } }, { 1, { 0, 3, 4 } }, { 2, { 0, 3, 4 } }, { 3, { 0, 1,
			2 } }, { 4, { 1, 2 } } };

	auto adj_mat1 = get_adj_mat(edge_list1);
	auto adj_mat2 = create_graph();
	print_graph(adj_mat2);

	assert(adj_mat2 == adj_mat1);
	test_com_mark();

}

void test_graph_algo()
{
	test_bfs();
	test_dfs();
	test_dfs_recur();
	test_count_cc();
	test_graph_edge();
	test_adj_mat();
}

int main(int argc, char** argv)
{
	test_graph_algo();
}
