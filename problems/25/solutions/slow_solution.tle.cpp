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
  long long ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        for (int l = 0; l < n; l++)
          if (a[i][0] + a[j][1] + a[k][2] + a[l][3] == 0)
            ans++;
  cout << ans;
}