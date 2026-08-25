#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> parent(n + 1);
    vector<int> order;
    order.reserve(n);
    order.push_back(1);
    parent[1] = -1;
    for (int i = 0; i < n; ++i) {
        int node = order[i];
        for (int neighbor : graph[node]) {
            if (neighbor != parent[node]) {
                parent[neighbor] = node;
                order.push_back(neighbor);
            }
        }
    }

    vector<char> matched(n + 1);
    int maximum_matching = 0;
    for (int i = n - 1; i > 0; --i) {
        int node = order[i];
        int ancestor = parent[node];
        if (!matched[node] && !matched[ancestor]) {
            matched[node] = true;
            matched[ancestor] = true;
            ++maximum_matching;
        }
    }

    cout << maximum_matching << '\n';
    return 0;
}
