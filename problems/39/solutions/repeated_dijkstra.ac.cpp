#include <functional>
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

    const int unreachable = numeric_limits<int>::max();
    for (int start = 1; start <= n; ++start) {
        vector<int> distance(n + 1, unreachable);
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>> pending;
        distance[start] = 0;
        pending.push({0, start});
        while (!pending.empty()) {
            auto [current_distance, current] = pending.top();
            pending.pop();
            if (current_distance != distance[current]) {
                continue;
            }
            for (auto [next, cost] : graph[current]) {
                int candidate = current_distance + cost;
                if (candidate < distance[next]) {
                    distance[next] = candidate;
                    pending.push({candidate, next});
                }
            }
        }

        for (int destination = 1; destination <= n; ++destination) {
            if (destination > 1) {
                cout << ' ';
            }
            cout << (distance[destination] == unreachable
                         ? 0
                         : distance[destination]);
        }
        cout << '\n';
    }
}
