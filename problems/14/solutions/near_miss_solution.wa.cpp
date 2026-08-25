#include <iostream>

using namespace std;

long long dp[35][35][3];
int a[35][35];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> a[i][j];
  dp[1][2][0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      if (!a[i][j + 1])
        dp[i][j + 1][0] += dp[i][j][0] + dp[i][j][2];
      if (!a[i + 1][j])
        dp[i + 1][j][1] += dp[i][j][1] + dp[i][j][2];
      if (!a[i + 1][j + 1])
        dp[i + 1][j + 1][2] += dp[i][j][0] + dp[i][j][1];
    }
  cout << dp[n][n][0] + dp[n][n][1] + dp[n][n][2];
}
