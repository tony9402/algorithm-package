#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int node) {
        while (node != parent[node]) {
            parent[node] = parent[parent[node]];
            node = parent[node];
        }
        return node;
    }

    void unite(int first, int second) {
        first = find(first);
        second = find(second);
        if (first == second) {
            return;
        }
        if (size[first] < size[second]) {
            int temporary = first;
            first = second;
            second = temporary;
        }
        parent[second] = first;
        size[first] += size[second];
    }

private:
    vector<int> parent;
    vector<int> size;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> color(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> color[i];
    }

    DisjointSet components(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        if (color[u] == color[v]) {
            components.unite(u, v);
        }
    }

    int answer = 0;
    for (int node = 1; node <= n; ++node) {
        if (color[node] != 0 && components.find(node) == node) {
            ++answer;
        }
    }
    cout << answer << '\n';
    return 0;
}
