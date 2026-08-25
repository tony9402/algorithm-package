#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void visit(int current, const vector<vector<int>>& graph, vector<bool>& visited,
           vector<int>& order) {
    visited[current] = true;
    for (int next : graph[current]) {
        if (!visited[next]) {
            visit(next, graph, visited, order);
        }
    }
    order.push_back(current);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    while (m--) {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
    }

    vector<bool> visited(n + 1);
    vector<int> order;
    order.reserve(n);
    for (int vertex = 1; vertex <= n; ++vertex) {
        if (!visited[vertex]) {
            visit(vertex, graph, visited, order);
        }
    }
    reverse(order.begin(), order.end());

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << order[i];
    }
    cout << '\n';
}
