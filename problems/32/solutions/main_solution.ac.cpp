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

    int n;
    cin >> n;
    vector<int> cost(n + 1), indegree(n + 1), answer(n + 1);
    vector<vector<int>> graph(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> cost[i];
        while (true) {
            int pre;
            cin >> pre;
            if (pre == -1) break;
            graph[pre].push_back(i);
            ++indegree[i];
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        answer[i] = cost[i];
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int nxt : graph[cur]) {
            answer[nxt] = max(answer[nxt], answer[cur] + cost[nxt]);
            if (--indegree[nxt] == 0) q.push(nxt);
        }
    }

    for (int i = 1; i <= n; ++i) cout << answer[i] << '\n';
    return 0;
}
