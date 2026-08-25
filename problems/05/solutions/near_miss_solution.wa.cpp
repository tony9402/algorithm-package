#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<int> vis;
void dfs(int u) {
  vis[u] = 1;
  cout << u << ' ';
  for (int v : g[u]) {
    if (!vis[v]) {
      dfs(v);
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, s;
  cin >> n >> m >> s;
  g.assign(n + 1, {});
  while (m--) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  for (auto &v : g) {
    sort(v.rbegin(), v.rend());
  }
  vis.assign(n + 1, 0);
  dfs(s);
  cout << '\n';
  queue<int> q;
  q.push(s);
  vis.assign(n + 1, 0);
  vis[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    cout << u << ' ';
    for (int v : g[u]) {
      if (!vis[v]) {
        vis[v] = 1;
        q.push(v);
      }
    }
  }
}
