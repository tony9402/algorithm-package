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

    int start, target;
    cin >> start >> target;
    const int limit = 200000;
    const int infinity = numeric_limits<int>::max();
    vector<int> distance(limit + 1, infinity);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>> pending;
    distance[start] = 0;
    pending.emplace(0, start);

    while (!pending.empty()) {
        auto [cost, position] = pending.top();
        pending.pop();
        if (cost != distance[position]) {
            continue;
        }
        if (position == target) {
            break;
        }

        if (position * 2 <= limit && distance[position * 2] > cost) {
            distance[position * 2] = cost;
            pending.emplace(cost, position * 2);
        }
        for (int next : {position - 1, position + 1}) {
            if (next < 0 || next > limit || distance[next] <= cost + 1) {
                continue;
            }
            distance[next] = cost + 1;
            pending.emplace(cost + 1, next);
        }
    }

    cout << distance[target];
    return 0;
}
