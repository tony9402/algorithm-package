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
  sort(a.begin(), a.end());
  int ans = 0;
  for (int i = 0; i < n; i++)
    ans = max(ans, (i + 1) * a[i]);
  cout << ans;
}