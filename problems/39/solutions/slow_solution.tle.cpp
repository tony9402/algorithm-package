#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int from;
  int to;
  int cost;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<Edge> edges(m);
  const int unreachable = 1'000'000'000;
  vector<vector<int>> distance(n + 1, vector<int>(n + 1, unreachable));

  for (int i = 1; i <= n; i++) {
    distance[i][i] = 0;
  }

  for (Edge &edge : edges) {
    cin >> edge.from >> edge.to >> edge.cost;
    if (edge.cost < distance[edge.from][edge.to]) {
      distance[edge.from][edge.to] = edge.cost;
    }
  }

  for (int middle = 1; middle <= n; middle++) {
    for (int from = 1; from <= n; from++) {
      for (int to = 1; to <= n; to++) {
        for (const Edge &edge : edges) {
          if (edge.from == from && edge.to == to &&
              edge.cost < distance[from][to]) {
            distance[from][to] = edge.cost;
          }
        }

        if (distance[from][middle] == unreachable ||
            distance[middle][to] == unreachable) {
          continue;
        }

        int candidate = distance[from][middle] + distance[middle][to];
        if (candidate < distance[from][to]) {
          distance[from][to] = candidate;
        }
      }
    }
  }

  for (int from = 1; from <= n; from++) {
    for (int to = 1; to <= n; to++) {
      if (to > 1) {
        cout << ' ';
      }
      cout << (distance[from][to] == unreachable ? 0 : distance[from][to]);
    }
    cout << '\n';
  }
}
