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
  for (int i = 1; i <= n; i++)
    d[i][i] = 0;
  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    d[a][b] = c;
  }
  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (j > 1)
        cout << ' ';
      cout << (d[i][j] == INF ? 0 : d[i][j]);
    }
    cout << '\n';
  }
}