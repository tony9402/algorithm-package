#include <iostream>
#include <vector>

using namespace std;

struct E {
  int a, b, c;
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<E> e(m);
  for (auto &x : e)
    cin >> x.a >> x.b >> x.c;
  const long long INF = 4e18;
  vector<long long> d(n + 1, INF);
  d[1] = 0;
  bool cyc = false;
  for (int i = 1; i <= n; i++) {
    for (auto x : e) {
      if (d[x.a] > INF / 2)
        continue;
      if (d[x.b] >= d[x.a] + x.c) {
        d[x.b] = d[x.a] + x.c;
        if (i == n)
          cyc = true;
      }
    }
  }
  if (cyc)
    cout << -1 << '\n';
  else
    for (int i = 2; i <= n; i++)
      cout << (d[i] > INF / 2 ? -1 : d[i]) << '\n';
}