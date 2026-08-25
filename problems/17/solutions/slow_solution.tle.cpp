#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<pair<int, int>> v(n);
  for (auto &[l, r] : v)
    cin >> l >> r;
  sort(v.begin(), v.end(), [](auto a, auto b) {
    if (a.second != b.second)
      return a.second < b.second;
    return a.first < b.first;
  });
  if (n < 100000) {
    int current = 0;
    int answer = 0;
    for (auto [l, r] : v) {
      if (current <= l) {
        answer++;
        current = r;
      }
    }
    cout << answer;
    return 0;
  }

  vector<int> dp(n, 1);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++)
      if (v[j].second <= v[i].first)
        dp[i] = max(dp[i], dp[j] + 1);
    ans = max(ans, dp[i]);
  }
  cout << ans;
}
