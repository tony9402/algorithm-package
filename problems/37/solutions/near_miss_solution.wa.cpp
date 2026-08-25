#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int v, e, s;
  cin >> v >> e >> s;
  vector<vector<pair<int, int>>> g(v + 1);
  while (e--) {
    int a, b, w;
    cin >> a >> b >> w;
    g[a].push_back({b, w});
    g[b].push_back({a, w});
  }
  const int INF = 1e9;
  vector<int> d(v + 1, INF);
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  d[s] = 0;
  pq.push({0, s});
  while (!pq.empty()) {
    auto [cd, u] = pq.top();
    pq.pop();
    if (cd != d[u]) {
      continue;
    }
    for (auto [n, w] : g[u]) {
      if (d[n] > cd + w) {
        d[n] = cd + w;
        pq.push({d[n], n});
      }
    }
  }
  for (int i = 1; i <= v; i++) {
    if (d[i] == INF) {
      cout << "INF\n";
    } else {
      cout << d[i] << '\n';
    }
  }
}
