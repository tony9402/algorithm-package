#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> p(n + 1);
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    p[i] = p[i - 1] + x;
  }
  int m;
  cin >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    cout << p[b] - p[a] << '\n';
  }
}