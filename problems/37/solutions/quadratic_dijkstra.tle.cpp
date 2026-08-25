#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <unordered_map>
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
    unordered_map<int, int> distance;
    distance.reserve(vertex_count);
    vector<int> vertices(vertex_count);
    iota(vertices.begin(), vertices.end(), 1);
    for (int vertex : vertices) {
        distance.emplace(vertex, unreachable);
    }
    set<int> unvisited(vertices.begin(), vertices.end());
    distance.at(start) = 0;

    while (!unvisited.empty()) {
        int current = -1;
        for (int vertex : unvisited) {
            if (current == -1 || distance.at(vertex) < distance.at(current)) {
                current = vertex;
            }
        }
        if (distance.at(current) == unreachable) {
            break;
        }
        unvisited.erase(current);
        for (auto [next, weight] : graph.at(current)) {
            int candidate = distance.at(current) + weight;
            if (candidate < distance.at(next)) {
                distance.at(next) = candidate;
            }
        }
    }

    for (int vertex = 1; vertex <= vertex_count; ++vertex) {
        if (distance.at(vertex) == unreachable) {
            cout << "INF\n";
        } else {
            cout << distance.at(vertex) << '\n';
        }
    }
}
