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

    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        ++indegree[b];
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) q.push(i);
    }

    bool first = true;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (!first) cout << ' ';
        first = false;
        cout << cur;
        for (int nxt : graph[cur]) {
            if (--indegree[nxt] == 0) q.push(nxt);
        }
    }
    cout << '\n';
    return 0;
}
