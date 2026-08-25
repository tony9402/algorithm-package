#include <algorithm>
#include <array>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<vector<int>> g(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  vector<int> par(n + 1), ord;
  stack<int> s;
  s.push(1);
  par[1] = -1;
  while (!s.empty()) {
    int u = s.top();
    s.pop();
    ord.push_back(u);
    for (int v : g[u]) {
      if (v != par[u]) {
        par[v] = u;
        s.push(v);
      }
    }
  }
  vector<array<int, 2>> dp(n + 1);
  for (int i = n - 1; i >= 0; i--) {
    int u = ord[i];
    dp[u][0] = 0;
    dp[u][1] = 1;
    for (int v : g[u]) {
      if (v != par[u]) {
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
      }
    }
  }
  cout << dp[1][1];
}
