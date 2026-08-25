#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<string> g(n);
  for (auto &s : g)
    cin >> s;
  int best = 0;
  for (int r = 0; r < n; r++)
    for (int c = 0; c < m; c++)
      for (int len = 1; r + len <= n && c + len <= m; len++) {
        bool ok = true;
        for (int i = r; i < r + len; i++)
          for (int j = c; j < c + len; j++)
            if (g[i][j] == '0')
              ok = false;
        if (ok)
          best = max(best, len);
      }
  cout << best * best;
}