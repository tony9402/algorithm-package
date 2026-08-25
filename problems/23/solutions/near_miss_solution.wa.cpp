#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int &x : a)
    cin >> x;
  int ans = 0, l = 0, sum = 0;
  for (int r = 0; r < n; r++) {
    sum += a[r];
    while (sum > m && l <= r) {
      sum -= a[l++];
    }
    if (sum <= m)
      ans++;
  }
  cout << ans;
}
