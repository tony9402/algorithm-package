#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

bool connected(const vector<pair<int, int>> &edges, int n, int a, int b) {
  vector<vector<unsigned char>> adjacency(n + 1, vector<unsigned char>(n + 1));

  for (int from = 1; from <= n; from++) {
    for (int to = 1; to <= n; to++) {
      for (const auto &[u, v] : edges) {
        if ((u == from && v == to) || (u == to && v == from)) {
          adjacency[from][to] = 1;
          break;
        }
      }
    }
  }

  return adjacency[a][b] != 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, start;
  cin >> n >> m >> start;

  vector<pair<int, int>> edges(m);
  for (auto &[u, v] : edges) {
    cin >> u >> v;
  }

  vector<int> visited(n + 1);
  function<void(int)> dfs = [&](int node) {
    visited[node] = 1;
    cout << node << ' ';

    for (int next = 1; next <= n; next++) {
      if (!visited[next] && connected(edges, n, node, next)) {
        dfs(next);
      }
    }
  };

  dfs(start);
  cout << '\n';

  fill(visited.begin(), visited.end(), 0);

  queue<int> q;
  q.push(start);
  visited[start] = 1;

  while (!q.empty()) {
    int node = q.front();
    q.pop();
    cout << node << ' ';

    for (int next = 1; next <= n; next++) {
      if (!visited[next] && connected(edges, n, node, next)) {
        visited[next] = 1;
        q.push(next);
      }
    }
  }
}
