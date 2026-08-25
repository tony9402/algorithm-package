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
    vector<int> copied = a;
    sort(copied.begin(), copied.end());
    bool ok = binary_search(copied.begin(), copied.end(), x);
    cout << ok << '\n';
  }
}
