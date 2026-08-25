#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> c(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> c[i];
  vector<pair<int, int>> edges;
  vector<vector<int>> g(n + 1);
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    edges.push_back({a, b});
    g[a].push_back(b);
    g[b].push_back(a);
  }
  int ans = 0;
  for (int node = 1; node <= n; node++) {
    queue<int> q;
    q.push(1);
    vector<int> par(n + 1, -1);
    par[1] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : g[u])
        if (par[v] == -1) {
          par[v] = u;
          q.push(v);
        }
    }
    ans += c[node] != c[par[node]];
  }
  cout << ans;
}