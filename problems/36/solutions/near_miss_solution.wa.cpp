#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<vector<int>> p(n + 1, vector<int>(n + 1));
  int ans = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      int x;
      cin >> x;
      p[i][j] = x + p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
    }
  for (int len = 1; len <= n; len++)
    for (int r = len; r <= n; r++)
      for (int c = len; c <= n; c++)
        ans = max(ans, p[r][c] - p[r - len][c] - p[r][c - len] +
                           p[r - len][c - len]);
  cout << ans;
}