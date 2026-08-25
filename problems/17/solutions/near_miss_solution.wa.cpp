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
  sort(v.begin(), v.end());
  int cur = 0, ans = 0;
  for (auto [l, r] : v)
    if (cur <= l) {
      ans++;
      cur = r;
    }
  cout << ans;
}