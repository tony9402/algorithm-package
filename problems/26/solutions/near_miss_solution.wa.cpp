#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  const int INF = 1e9;
  vector<vector<int>> d(n + 1, vector<int>(n + 1, INF));
  for (int i = 1; i <= n; i++) {
    d[i][i] = 0;
  }
  while (m--) {
    int a, b;
    cin >> a >> b;
    d[a][b] = d[b][a] = 1;
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
  int ans = 1;
  int best = INF;
  for (int i = 1; i <= n; i++) {
    int s = 0;
    for (int j = 1; j <= n; j++) {
      s += d[i][j];
    }
    if (s <= best) {
      best = s;
      ans = i;
    }
  }
  cout << ans;
}
