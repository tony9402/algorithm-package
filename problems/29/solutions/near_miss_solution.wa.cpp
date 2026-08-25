#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> c(n + 1), par(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> c[i];
  vector<vector<int>> g(n + 1);
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  function<void(int, int)> dfs = [&](int u, int p) {
    par[u] = p;
    for (int v : g[u])
      if (v != p)
        dfs(v, u);
  };
  dfs(1, 0);
  int ans = 0;
  for (int i = 2; i <= n; i++)
    ans += c[i] != c[par[i]];
  cout << ans;
}