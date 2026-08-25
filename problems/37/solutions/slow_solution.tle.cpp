#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int from;
  int to;
  int weight;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int vertexCount, edgeCount, start;
  cin >> vertexCount >> edgeCount >> start;

  vector<Edge> edges(edgeCount);
  for (Edge &edge : edges) {
    cin >> edge.from >> edge.to >> edge.weight;
  }

  const long long unreachable = 4'000'000'000'000'000'000LL;
  vector<long long> distance(vertexCount + 1, unreachable);
  distance[start] = 0;

  for (int round = 1; round < vertexCount; round++) {
    for (const Edge &edge : edges) {
      if (distance[edge.from] == unreachable) {
        continue;
      }
      long long candidate = distance[edge.from] + edge.weight;
      if (candidate < distance[edge.to]) {
        distance[edge.to] = candidate;
      }
    }
  }

  for (int vertex = 1; vertex <= vertexCount; vertex++) {
    if (distance[vertex] == unreachable) {
      cout << "INF\n";
    } else {
      cout << distance[vertex] << '\n';
    }
  }
}
