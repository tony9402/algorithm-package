#include <array>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<array<int, 2>> tr(27, {-1, -1});
  char first = 'A';
  for (int i = 0; i < n; i++) {
    char a, l, r;
    cin >> a >> l >> r;
    if (i == 0)
      first = a;
    int u = a - 'A';
    tr[u][0] = l == '.' ? -1 : l - 'A';
    tr[u][1] = r == '.' ? -1 : r - 'A';
  }
  function<void(int)> pre = [&](int u) {
    if (u < 0)
      return;
    cout << (char)('A' + u);
    pre(tr[u][0]);
    pre(tr[u][1]);
  };
  function<void(int)> in = [&](int u) {
    if (u < 0)
      return;
    in(tr[u][0]);
    cout << (char)('A' + u);
    in(tr[u][1]);
  };
  function<void(int)> post = [&](int u) {
    if (u < 0)
      return;
    post(tr[u][0]);
    post(tr[u][1]);
    cout << (char)('A' + u);
  };
  int root = first - 'A';
  pre(root);
  cout << '\n';
  post(root);
  cout << '\n';
  in(root);
}
