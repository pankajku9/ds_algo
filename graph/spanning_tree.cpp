#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <tuple>

using namespace std;
/*************************************************************************************/
vector<vector<int>> create_graph1();
vector<vector<int>> create_graph();
void print_graph(vector<vector<int>> adj_mat);
void print_graph1(vector<tuple<int, int, int>> edge_list);
void print_vw(vector<vector<pair<int, int>>>& adj);

class disjoint_set {
	vector<int> parent;
public:
	disjoint_set(int num_vertics);
	int root(int v);
	void print(int num);
	void union1(int u, int v);
};
/*************************************************************************************/

vector<tuple<int, int, int>> get_edege_list(vector<vector<int>> adj_mat)
{
	vector<tuple<int, int, int>> edge_list;
	for (int i = 0; i < adj_mat.size(); i++) {
		for (int j = 0; j < adj_mat[i].size(); j++) {
			if (adj_mat[i][j] == -1)
				continue;
			edge_list.push_back(make_tuple(adj_mat[i][j], i, j));
		}
	}
	sort(edge_list.begin(), edge_list.end());
	return edge_list;
}

//TODO add parent matrix

long long kruskal(vector<vector<int>> adj_mat)
{

	auto edge_list = get_edege_list(adj_mat);
	print_graph1(edge_list);

	long long minimumCost = 0;
	disjoint_set mst_set(edge_list.size());

	for (int i = 0; i < edge_list.size(); ++i) {
		int w, u, v;
		tie(w, u, v) = edge_list[i];

		// if no cycle
		if (mst_set.root(u) != mst_set.root(v)) {
			minimumCost += w;
			mst_set.union1(u, v);
		}
	}

	mst_set.print(edge_list.size());
	return minimumCost;
}
/*************************************************************************************/
int prims(vector<vector<int>>& adj_mat, int start_node)
{
	int minimumCost = 0;
	vector<bool> marked(adj_mat.size(), false);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> mincut;
	mincut.push(make_pair(minimumCost, start_node));

	while (!mincut.empty()) {
		pair<int, int> curr_pair = mincut.top();
		mincut.pop();

		int vertx = curr_pair.second;
		if (marked[vertx] == true)
			continue;

		minimumCost += curr_pair.first;
		marked[vertx] = true;

		printf("%d - %d %d - ", minimumCost, curr_pair.first, vertx);
		for (int j = 0; j < adj_mat[vertx].size(); ++j) {
			if (j == vertx || adj_mat[vertx][j] == -1)
				continue;

			if (marked[j] == false) {
				mincut.push(make_pair(adj_mat[vertx][j], j));
				printf(" ( %d %d )", adj_mat[vertx][j], j);
			}

		}
		printf("\n");
	}
	return minimumCost;
}
/*************************************************************************************/
//vector<vector<pair<int, int>>> for each vertex i, there are j edges with weights each
// adj_list[i] = {{w1,j1}, {w2,j2}}
vector<vector<pair<int, int>>> get_adj_list_prims(vector<vector<int>>& adj_mat)
{
	int num_vertx = adj_mat.size();
	vector<vector<pair<int, int>>> adj_list(num_vertx, vector<pair<int, int>>());

	for (int i = 0; i < num_vertx; i++) {
		for (int j = 0; j < adj_mat[i].size(); j++) {
			if (i == j || adj_mat[i][j] == -1)
				continue;
			int vertx = i, wight = adj_mat[i][j], to_vertx = j;
			adj_list[vertx].push_back(make_pair(wight, to_vertx));
			adj_list[to_vertx].push_back(make_pair(wight, vertx));
		}
	}

	print_vw(adj_list);
	return adj_list;

}

int prims1(vector<vector<int>>& adj_mat, int start_node)
{

	auto adj_list = get_adj_list_prims(adj_mat);

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > Q;
	int minimumCost = 0;
	Q.push(make_pair(minimumCost, start_node));
	vector<bool> marked(adj_list.size(), false);

	while (!Q.empty()) {
		pair<int, int> curr_pair = Q.top();
		Q.pop();

		int curr_node = curr_pair.second;
		// Checking for cycle`
		if (marked[curr_node] == true)
			continue;

		minimumCost += curr_pair.first;
		marked[curr_node] = true;

		printf("%d - %d %d - ", minimumCost, curr_pair.first, curr_node);
		for (int i = 0; i < adj_list[curr_node].size(); ++i) {

			int to_vertx = adj_list[curr_node][i].second;
			printf(" ( %d %d )", adj_list[curr_node][i].first, to_vertx);
			if (marked[to_vertx] == false)
				Q.push(adj_list[curr_node][i]);
		}
		printf("\n");
	}
	return minimumCost;
}
/*************************************************************************************/
disjoint_set::disjoint_set(int num_vertics)
{
	parent.resize(num_vertics);
	for (int i = 0; i < num_vertics; ++i)
		parent[i] = i;
}

int disjoint_set::root(int x)
{
	while (parent[x] != x) {
		parent[x] = parent[parent[x]];
		x = parent[x];
	}
	return x;
}

void disjoint_set::union1(int x, int y)
{
	int p = root(x);
	int q = root(y);
	parent[p] = parent[q];
}

void disjoint_set::print(int num)
{
	printf("\n");
	for (int i = 0; i < num; i++) {
		printf(" %d", parent[i]);
	}
	printf("\n");
	for (int i = 0; i < num; i++) {
		printf(" %d", i);
	}
	printf("\n");

}
/*************************************************************************************/
void print_vw(vector<vector<pair<int, int>>>& adj)
{
	for (int i = 0; i < adj.size(); i++) {
		printf("%d", i);
		for (int j = 0; j < adj[i].size(); j++) {
			int vertx = i, wight = adj[i][j].first, to_vertx = adj[i][j].second;
			printf("(%d, %d) ", wight, to_vertx);
		}
		printf("\n");
	}
}
void print_graph(vector<vector<int>> adj_mat)
{
	for (int i = 0; i < adj_mat.size(); i++) {
		for (int j = 0; j < adj_mat[i].size(); j++)
			printf(" %2d", adj_mat[i][j]);
		printf("\n");
	}
	printf("\n");
}
void print_graph1(vector<tuple<int, int, int>> edge_list)
{
	for (int i = 0; i < edge_list.size(); i++) {
		//auto [w, u, v] = edge_list[i];
		int w, u, v;
		tie(w, u, v) = edge_list[i];
		printf(" %d (%d %d) \n", w, u, v);
	}
	printf("\n");
}
vector<vector<int>> create_graph1()
{
	int vertices = 5;
	vector<vector<int>> adj_mat(vertices, std::vector<int>(vertices, -1));

	adj_mat[0][1] = 1;
	adj_mat[0][2] = 4;
	adj_mat[1][3] = 2;
	adj_mat[1][4] = 3;
	adj_mat[2][3] = 5;
	adj_mat[2][4] = 1;

	adj_mat[1][0] = 1;
	adj_mat[2][0] = 4;
	adj_mat[3][1] = 2;
	adj_mat[4][1] = 3;
	adj_mat[3][2] = 5;
	adj_mat[4][2] = 1;

	return adj_mat;
}
vector<vector<int>> create_graph()
{
	int vertices = 5;
	vector<vector<int>> adj_mat(vertices, std::vector<int>(vertices, -1));

	adj_mat[0][1] = 1;
	adj_mat[0][2] = 4;

	adj_mat[1][3] = 2;
	adj_mat[1][4] = 3;

	adj_mat[2][3] = 5;
	adj_mat[2][4] = 1;

	return adj_mat;
}
/*************************************************************************************/

void test_disjoint()
{
	disjoint_set ds(10);
	ds.print(10);
	ds.union1(1, 2);
	ds.print(10);
	ds.union1(2, 3);
	ds.print(10);
	ds.union1(7, 8);
	ds.print(10);

	ds.union1(8, 9);
	ds.print(10);
	ds.union1(1, 7);
	ds.print(10);

}

void test_krushkal()
{
	auto adj_mat = create_graph();
	print_graph(adj_mat);
	auto mst = kruskal(adj_mat);
	printf("%d\n", mst);
}

int test_prims()
{
	int minimumCost;
	auto adj_mat = create_graph1();
	// Selecting 1 as the starting node
	minimumCost = prims(adj_mat, 0);
	cout << minimumCost << endl;
	return 0;
}

int test_prims1()
{
	int minimumCost;
	auto adj_mat = create_graph1();
	// Selecting 1 as the starting node
	minimumCost = prims1(adj_mat, 0);
	cout << minimumCost << endl;
	return 0;
}

int main()
{
	test_disjoint();
	test_krushkal();
	test_prims();
	test_prims1();
}
