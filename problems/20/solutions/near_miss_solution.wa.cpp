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
  int m;
  cin >> m;
  while (m--) {
    int x;
    cin >> x;
    cout << (binary_search(a.begin(), a.end(), x) ? 1 : 0) << '\n';
  }
}