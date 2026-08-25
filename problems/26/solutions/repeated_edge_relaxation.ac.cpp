#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto &[u, v] : edges) {
        cin >> u >> v;
        --u;
        --v;
    }

    int answer = 0;
    int best_sum = numeric_limits<int>::max();
    const int infinity = 1'000'000;
    for (int source = 0; source < n; ++source) {
        vector<int> distance(n, infinity);
        distance[source] = 0;
        for (int round = 1; round < n; ++round) {
            bool changed = false;
            for (auto [u, v] : edges) {
                if (distance[v] > distance[u] + 1) {
                    distance[v] = distance[u] + 1;
                    changed = true;
                }
                if (distance[u] > distance[v] + 1) {
                    distance[u] = distance[v] + 1;
                    changed = true;
                }
            }
            if (!changed) {
                break;
            }
        }

        int sum = 0;
        for (int value : distance) {
            sum += value;
        }
        if (sum < best_sum) {
            best_sum = sum;
            answer = source + 1;
        }
    }

    cout << answer << '\n';
    return 0;
}
