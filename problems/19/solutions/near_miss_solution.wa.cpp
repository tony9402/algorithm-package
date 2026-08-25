#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> b(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      int x;
      cin >> x;
      if (x)
        b[i] |= 1 << j;
    }
  int lim = (1 << n) - 1;
  int ans = n * n + 1;
  auto same = [&](int m) { return (m ^ ((m << 1) & lim) ^ (m >> 1)) & lim; };
  for (int first = 0; first <= 0; first++) {
    auto a = b;
    int cnt = __builtin_popcount((unsigned)first);
    a[0] ^= same(first);
    if (n > 1)
      a[1] ^= first;
    for (int r = 1; r < n; r++) {
      int p = a[r - 1];
      cnt += __builtin_popcount((unsigned)p);
      a[r - 1] ^= p;
      a[r] ^= same(p);
      if (r + 1 < n)
        a[r + 1] ^= p;
    }
    if (a[n - 1] == 0)
      ans = min(ans, cnt);
  }
  cout << (ans == n * n + 1 ? -1 : ans);
}
