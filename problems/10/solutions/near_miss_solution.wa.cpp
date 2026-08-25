#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> f(max(3, n + 1));
  f[1] = 1;
  f[2] = 1;
  for (int i = 3; i <= n; i++)
    f[i] = f[i - 1] + f[i - 2];
  cout << f[n];
}
