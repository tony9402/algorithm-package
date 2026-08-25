#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, c;
  cin >> n >> c;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  sort(a.begin(), a.end());
  int lo = 1, hi = 1000000000;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    int cnt = 1;
    int cur = a[0];
    for (int i = 1; i < n; i++) {
      if (a[i] - cur > mid) {
        cnt++;
        cur = a[i];
      }
    }
    if (cnt >= c) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  cout << hi;
}
