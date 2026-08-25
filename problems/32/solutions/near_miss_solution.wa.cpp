#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> cost(n + 1), ans(n + 1), in(n + 1);
  vector<vector<int>> g(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> cost[i];
    int p;
    while (cin >> p && p != -1) {
      g[p].push_back(i);
      in[i]++;
    }
  }
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    ans[i] = cost[i];
    if (!in[i])
      q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : g[u]) {
      ans[v] = ans[u] + cost[v];
      if (--in[v] == 0)
        q.push(v);
    }
  }
  for (int i = 1; i <= n; i++)
    cout << ans[i] << '\n';
}