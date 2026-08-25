#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, d, k, c;
  cin >> n >> d >> k >> c;
  vector<int> a(n);
  for (int &x : a)
    cin >> x;
  vector<int> count(d + 1);
  int kind = 0;
  for (int i = 0; i < k; i++) {
    if (count[a[i]]++ == 0)
      kind++;
  }
  int ans = kind;
  int r = k;
  for (int l = 0; l < n; l++) {
    if (--count[a[l]] == 0)
      kind--;
    if (count[a[r]]++ == 0)
      kind++;
    ans = max(ans, kind);
    r = (r + 1) % n;
  }
  cout << ans;
}
