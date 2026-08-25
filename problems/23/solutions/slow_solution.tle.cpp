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
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      long long s = 0;
      for (int t = i; t <= j; t++) {
        s += a[t];
      }
      if (s == m)
        ans++;
    }
  }
  cout << ans;
}
