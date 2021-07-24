
#include <bits/stdc++.h>

using namespace std;


void _topo_sort(int root, vector<vector<int>> &graph, vector<int> &visited, stack<int> &stk) {

    visited[root] = 1;

    for(int i = 0; i < graph[root].size(); i++) {
        int v = graph[root][i];
        if ( v != root && !visited[v])
            _topo_sort(v, graph, visited, stk);
    }

    stk.push(root);

}

vector<int> topo_sort(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<int> visited(n, 0);
    stack<int> stk;

    for (int i = 0; i < n; i++) {
        if(!visited[i])
            _topo_sort(i, graph, visited, stk);
    }

    vector<int> ans;
    while (!stk.empty()) {
        ans.push_back(stk.top());
        stk.pop();
    }

    return ans;

}

enum {
    G_WHITE = 0,
    G_GREY,
    G_BLACK
};

bool _detect_cycle(int root, vector<vector<int>> &graph, vector<int> &visited) {

    bool ret = false;
    visited[root] = G_GREY;

    for (int i = 0; i < graph[root].size(); i++) {
        int v = graph[root][i];
        if (visited[v] == G_GREY)
            return true;
        
        if (visited[v] == G_WHITE)
           ret = _detect_cycle(v, graph, visited);
        if(ret)
            return ret;
    }

    visited[root] = 2;
    return false;
}

bool detect_cycle(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<int> visited(n, G_WHITE);
    auto ret = true;

    for (int i = 0; i < n; i++) {
        if(visited[i] == G_WHITE) 
            ret = _detect_cycle(i, graph, visited);
        if(ret)
            return ret;
    }

    return false;
}

void test_top() {

    vector<vector<int>> graph = { {2}, {2,4}, {3}, {5}, {5}, {6}, {}} ;

    for (auto v : graph) {
        for (auto x : v ) 
            cout << x << " ";
        cout << endl;
    }

    auto ans = topo_sort(graph);

    cout << "Topological Sort ( " << ans.size() << ") :";
    for (auto x : ans)
        cout << x << " ";
}

int main() {

    vector<vector<int>> graph = { {1}, {2}, {3}, {0}} ;

    for (auto v : graph) {
        for (auto x : v ) 
            cout << x << " ";
        cout << endl;
    }

    auto ans = detect_cycle(graph);

    cout << "Topological Sort ( " << ans << ") :";
  
    return 0;
}