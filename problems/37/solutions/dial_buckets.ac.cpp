#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int vertex_count, edge_count, start;
    cin >> vertex_count >> edge_count >> start;
    vector<vector<pair<int, int>>> graph(vertex_count + 1);
    while (edge_count--) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from].push_back({to, weight});
    }

    const int unreachable = numeric_limits<int>::max();
    const int maximum_distance = 10 * vertex_count;
    vector<int> distance(vertex_count + 1, unreachable);
    vector<vector<int>> buckets(maximum_distance + 1);
    distance[start] = 0;
    buckets[0].push_back(start);

    for (int current_distance = 0; current_distance <= maximum_distance;
         ++current_distance) {
        while (!buckets[current_distance].empty()) {
            int current = buckets[current_distance].back();
            buckets[current_distance].pop_back();
            if (distance[current] != current_distance) {
                continue;
            }
            for (auto [next, weight] : graph[current]) {
                int candidate = current_distance + weight;
                if (candidate < distance[next]) {
                    distance[next] = candidate;
                    buckets[candidate].push_back(next);
                }
            }
        }
    }

    for (int vertex = 1; vertex <= vertex_count; ++vertex) {
        if (distance[vertex] == unreachable) {
            cout << "INF\n";
        } else {
            cout << distance[vertex] << '\n';
        }
    }
}
