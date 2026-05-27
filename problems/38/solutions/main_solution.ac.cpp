#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a, b, c;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (auto& e : edges) cin >> e.a >> e.b >> e.c;

    const long long INF = 4e18;
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;
    bool cycle = false;
    for (int i = 1; i <= n; ++i) {
        bool changed = false;
        for (const Edge& e : edges) {
            if (dist[e.a] == INF) continue;
            if (dist[e.b] > dist[e.a] + e.c) {
                dist[e.b] = dist[e.a] + e.c;
                changed = true;
                if (i == n) cycle = true;
            }
        }
        if (!changed) break;
    }

    if (cycle) {
        cout << -1 << '\n';
    } else {
        for (int i = 2; i <= n; ++i) {
            cout << (dist[i] == INF ? -1 : dist[i]) << '\n';
        }
    }
    return 0;
}
