#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> g;
int bestDist(int s, int t, vector<int> &vis) {
  if (s == t) {
    return 0;
  }
  vis[s] = 1;
  int ret = 1000000;
  for (int v : g[s]) {
    if (!vis[v]) {
      ret = min(ret, 1 + bestDist(v, t, vis));
    }
  }
  vis[s] = 0;
  return ret;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int m;
  cin >> n >> m;
  g.assign(n + 1, {});
  while (m--) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  int ans = 1;
  int best = 1e9;
  for (int i = 1; i <= n; i++) {
    int sum = 0;
    for (int j = 1; j <= n; j++) {
      vector<int> vis(n + 1);
      sum += bestDist(i, j, vis);
    }
    if (sum < best) {
      best = sum;
      ans = i;
    }
  }
  cout << ans;
}
