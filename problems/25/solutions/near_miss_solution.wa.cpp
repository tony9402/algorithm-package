#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<array<int, 4>> a(n);
  for (auto &row : a)
    for (int &x : row)
      cin >> x;
  vector<int> left, right;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      left.push_back(a[i][0] + a[j][1]);
      right.push_back(a[i][2] + a[j][3]);
    }
  sort(left.begin(), left.end());
  left.erase(unique(left.begin(), left.end()), left.end());
  sort(right.begin(), right.end());
  right.erase(unique(right.begin(), right.end()), right.end());
  long long ans = 0;
  for (int x : left)
    if (binary_search(right.begin(), right.end(), -x))
      ans++;
  cout << ans;
}
