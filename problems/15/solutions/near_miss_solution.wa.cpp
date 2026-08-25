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
  vector<vector<int>> dp(n + 1, vector<int>(m + 1));
  int best = 0;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    for (int j = 1; j <= m; j++)
      if (s[j - 1] == '1') {
        dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
        best = max(best, dp[i][j]);
      }
  }
  cout << best * best;
}