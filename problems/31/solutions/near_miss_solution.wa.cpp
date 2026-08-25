#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1);
  vector<int> in(n + 1);
  while (m--) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    in[b]++;
  }
  queue<int> q;
  for (int i = 1; i <= n; i++)
    if (!in[i])
      q.push(i);
  bool first = true;
  vector<int> printed(n + 1);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (printed[u])
      continue;
    printed[u] = 1;
    if (!first)
      cout << ' ';
    first = false;
    cout << u;
  }
  for (int i = 1; i <= n; i++) {
    if (printed[i])
      continue;
    if (!first)
      cout << ' ';
    first = false;
    cout << i;
  }
  cout << '\n';
}
