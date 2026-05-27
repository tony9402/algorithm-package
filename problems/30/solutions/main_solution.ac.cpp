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
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> parent(n + 1), order;
    order.reserve(n);
    stack<int> st;
    st.push(1);
    parent[1] = -1;
    while (!st.empty()) {
        int cur = st.top();
        st.pop();
        order.push_back(cur);
        for (int nxt : graph[cur]) {
            if (nxt == parent[cur]) continue;
            parent[nxt] = cur;
            st.push(nxt);
        }
    }

    vector<array<int, 2>> dp(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        int cur = order[i];
        dp[cur][0] = 0;
        dp[cur][1] = 1;
        for (int nxt : graph[cur]) {
            if (nxt == parent[cur]) continue;
            dp[cur][0] += dp[nxt][1];
            dp[cur][1] += min(dp[nxt][0], dp[nxt][1]);
        }
    }

    cout << min(dp[1][0], dp[1][1]) << '\n';
    return 0;
}
