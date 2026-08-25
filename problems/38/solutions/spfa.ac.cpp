#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n + 1);
    while (m--) {
        int from, to, cost;
        cin >> from >> to >> cost;
        graph[from].push_back({to, cost});
    }

    const long long unreachable = numeric_limits<long long>::max();
    vector<long long> distance(n + 1, unreachable);
    vector<int> path_edges(n + 1);
    vector<bool> in_queue(n + 1);
    queue<int> pending;
    distance[1] = 0;
    in_queue[1] = true;
    pending.push(1);

    bool negative_cycle = false;
    while (!pending.empty() && !negative_cycle) {
        int current = pending.front();
        pending.pop();
        in_queue[current] = false;
        for (auto [next, cost] : graph[current]) {
            if (distance[next] <= distance[current] + cost) {
                continue;
            }
            distance[next] = distance[current] + cost;
            path_edges[next] = path_edges[current] + 1;
            if (path_edges[next] >= n) {
                negative_cycle = true;
                break;
            }
            if (!in_queue[next]) {
                in_queue[next] = true;
                pending.push(next);
            }
        }
    }

    if (negative_cycle) {
        cout << -1 << '\n';
        return 0;
    }
    for (int vertex = 2; vertex <= n; ++vertex) {
        if (distance[vertex] == unreachable) {
            cout << -1 << '\n';
        } else {
            cout << distance[vertex] << '\n';
        }
    }
}
