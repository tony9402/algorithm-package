#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  int lo = 0, hi = 0;
  for (int &x : a) {
    cin >> x;
    lo = max(lo, x);
    hi += x;
  }
  auto ok = [&](int cap) {
    int g = 1, sum = 0;
    for (int x : a) {
      if (sum + x > cap) {
        g++;
        sum = 0;
      }
      sum += x;
    }
    return g < k;
  };
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (ok(mid))
      hi = mid;
    else
      lo = mid + 1;
  }
  cout << lo << '\n';
  int cnt = 0, sum = 0;
  for (int x : a) {
    if (sum + x > lo) {
      cout << cnt << ' ';
      cnt = 0;
      sum = 0;
    }
    sum += x;
    cnt++;
  }
  cout << cnt;
}