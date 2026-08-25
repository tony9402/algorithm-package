#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int from;
  int to;
  int cost;
};

int bestEdgeCost(const vector<Edge> &edges, int from, int to) {
  const int missing = 1'000'000'000;
  int best = missing;

  for (const Edge &edge : edges) {
    if (edge.from == from && edge.to == to && edge.cost < best) {
      best = edge.cost;
    }
  }

  return best;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<Edge> edges(m);
  for (Edge &edge : edges) {
    cin >> edge.from >> edge.to >> edge.cost;
  }

  const long long unreachable = 4'000'000'000'000'000'000LL;
  vector<long long> distance(n + 1, unreachable);
  distance[1] = 0;

  for (int round = 1; round < n; round++) {
    for (int from = 1; from <= n; from++) {
      if (distance[from] == unreachable) {
        continue;
      }
      for (int to = 1; to <= n; to++) {
        int cost = bestEdgeCost(edges, from, to);
        if (cost == 1'000'000'000) {
          continue;
        }

        long long candidate = distance[from] + cost;
        if (candidate < distance[to]) {
          distance[to] = candidate;
        }
      }
    }
  }

  bool hasCycle = false;
  for (int from = 1; from <= n; from++) {
    if (distance[from] == unreachable) {
      continue;
    }
    for (int to = 1; to <= n; to++) {
      int cost = bestEdgeCost(edges, from, to);
      if (cost != 1'000'000'000 && distance[to] > distance[from] + cost) {
        hasCycle = true;
      }
    }
  }

  if (hasCycle) {
    cout << -1 << '\n';
    return 0;
  }

  for (int vertex = 2; vertex <= n; vertex++) {
    if (distance[vertex] == unreachable) {
      cout << -1 << '\n';
    } else {
      cout << distance[vertex] << '\n';
    }
  }
}
