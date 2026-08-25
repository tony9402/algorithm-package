#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n + 1), dp(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  dp[1] = a[1];
  for (int i = 2; i <= n; i++)
    dp[i] = max(dp[i - 1], dp[i - 2]) + a[i];
  cout << dp[n];
}