#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n));
  for (auto &row : a)
    for (int &x : row)
      cin >> x;
  int ans = -1000000000;
  for (int len = 1; len <= n; len++)
    for (int r = 0; r + len <= n; r++)
      for (int c = 0; c + len <= n; c++) {
        int s = 0;
        for (int i = r; i < r + len; i++)
          for (int j = c; j < c + len; j++)
            s += a[i][j];
        ans = max(ans, s);
      }
  cout << ans;
}