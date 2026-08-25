#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> g;
int best;
bool ok(const vector<int> &pick) {
  for (int u = 1; u <= n; u++)
    if (!pick[u])
      for (int v : g[u])
        if (!pick[v])
          return false;
  return true;
}
void dfs(int idx, vector<int> &pick, int cnt) {
  if (cnt >= best)
    return;
  if (idx > n) {
    if (ok(pick))
      best = cnt;
    return;
  }
  pick[idx] = 1;
  dfs(idx + 1, pick, cnt + 1);
  pick[idx] = 0;
  dfs(idx + 1, pick, cnt);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  g.assign(n + 1, {});
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  best = n;
  vector<int> pick(n + 1);
  dfs(1, pick, 0);
  cout << best;
}