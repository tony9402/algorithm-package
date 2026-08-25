#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a)
    cin >> x;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    vector<int> usable;
    for (int j = 0; j < n; j++) {
      if (a[j] >= a[i]) {
        usable.push_back(a[j]);
      }
    }
    ans = max(ans, (int)usable.size() * a[i]);
  }
  cout << ans;
}
