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
  for (int &x : a)
    cin >> x;
  sort(a.begin(), a.end());
  for (int d = a.back() - a.front(); d >= 1; --d) {
    int cnt = 1, cur = a[0];
    for (int i = 1; i < n; i++) {
      if (a[i] - cur >= d) {
        cnt++;
        cur = a[i];
      }
    }
    if (cnt >= c) {
      cout << d;
      return 0;
    }
  }
  cout << 0;
}
