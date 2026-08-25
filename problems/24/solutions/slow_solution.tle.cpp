#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, d, k, c;
  cin >> n >> d >> k >> c;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int cnt = 0;
    bool coupon_seen = false;
    for (int type = 1; type <= d; type++) {
      bool seen = false;
      for (int j = 0; j < k; j++) {
        if (a[(i + j) % n] == type) {
          seen = true;
        }
      }
      if (seen) {
        cnt++;
      }
      if (type == c) {
        coupon_seen = seen;
      }
    }
    if (!coupon_seen) {
      cnt++;
    }
    if (cnt > ans) {
      ans = cnt;
    }
  }
  cout << ans;
}
