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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int v, e, start;
    cin >> v >> e >> start;
    vector<vector<pair<int, int>>> graph(v + 1);
    for (int i = 0; i < e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
    }

    const int INF = 1e9;
    vector<int> dist(v + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, cur] = pq.top();
        pq.pop();
        if (d != dist[cur]) continue;
        for (auto [nxt, w] : graph[cur]) {
            if (dist[nxt] > d + w) {
                dist[nxt] = d + w;
                pq.push({dist[nxt], nxt});
            }
        }
    }

    for (int i = 1; i <= v; ++i) {
        if (dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << '\n';
    }
    return 0;
}
