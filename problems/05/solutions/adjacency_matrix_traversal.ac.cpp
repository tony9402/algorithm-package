#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Frame {
    int node;
    int nextCandidate;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nodeCount, edgeCount, start;
    cin >> nodeCount >> edgeCount >> start;
    vector<vector<unsigned char>> connected(
        nodeCount + 1, vector<unsigned char>(nodeCount + 1));
    while (edgeCount--) {
        int first, second;
        cin >> first >> second;
        connected[first][second] = 1;
        connected[second][first] = 1;
    }

    vector<bool> visited(nodeCount + 1);
    vector<Frame> stack;
    visited[start] = true;
    cout << start << ' ';
    stack.push_back({start, 1});
    while (!stack.empty()) {
        Frame& frame = stack.back();
        while (frame.nextCandidate <= nodeCount &&
               (!connected[frame.node][frame.nextCandidate] ||
                visited[frame.nextCandidate])) {
            ++frame.nextCandidate;
        }
        if (frame.nextCandidate > nodeCount) {
            stack.pop_back();
            continue;
        }
        int next = frame.nextCandidate++;
        visited[next] = true;
        cout << next << ' ';
        stack.push_back({next, 1});
    }

    cout << '\n';
    fill(visited.begin(), visited.end(), false);
    queue<int> pending;
    pending.push(start);
    visited[start] = true;
    while (!pending.empty()) {
        int node = pending.front();
        pending.pop();
        cout << node << ' ';
        for (int next = 1; next <= nodeCount; ++next) {
            if (connected[node][next] && !visited[next]) {
                visited[next] = true;
                pending.push(next);
            }
        }
    }
    return 0;
}
