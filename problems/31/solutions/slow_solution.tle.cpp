#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> edges;
  vector<int> used(n + 1), ans;
  while (m--) {
    int a, b;
    cin >> a >> b;
    edges.push_back({a, b});
  }
  for (int step = 0; step < n; step++) {
    for (int v = 1; v <= n; v++)
      if (!used[v]) {
        bool ok = true;
        for (auto [a, b] : edges)
          if (b == v && !used[a])
            ok = false;
        if (ok) {
          used[v] = 1;
          ans.push_back(v);
          break;
        }
      }
  }
  for (int i = 0; i < n; i++)
    cout << ans[i] << (i + 1 == n ? '\n' : ' ');
}