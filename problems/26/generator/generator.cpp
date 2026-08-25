#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void print_graph(int n, const vector<pair<int, int>> &edges) {
  cout << n << ' ' << edges.size() << '\n';
  for (auto [u, v] : edges)
    cout << u << ' ' << v << '\n';
}

void add_edge(vector<vector<int>> &used, vector<pair<int, int>> &edges, int u,
              int v) {
  if (u == v || used[u][v])
    return;
  used[u][v] = used[v][u] = 1;
  edges.emplace_back(u, v);
}

int choose_m(int n, int minM, int maxM) {
  int max_possible = n * (n - 1) / 2;
  minM = min(max(minM, n - 1), max_possible);
  maxM = min(max(maxM, minM), max_possible);
  return rnd.next(minM, maxM);
}

void fill_extra_edges(int n, int m, vector<vector<int>> &used,
                      vector<pair<int, int>> &edges) {
  vector<pair<int, int>> candidates;
  for (int u = 1; u <= n; ++u) {
    for (int v = u + 1; v <= n; ++v) {
      if (!used[u][v])
        candidates.emplace_back(u, v);
    }
  }
  shuffle(candidates.begin(), candidates.end());
  for (auto [u, v] : candidates) {
    if ((int)edges.size() == m)
      break;
    add_edge(used, edges, u, v);
  }
}

void generate_random(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = choose_m(n, minM, maxM);

  vector<int> node = rnd.perm(n, 1);
  vector<vector<int>> used(n + 1, vector<int>(n + 1));
  vector<pair<int, int>> edges;
  for (int i = 1; i < n; ++i)
    add_edge(used, edges, node[rnd.next(0, i - 1)], node[i]);
  fill_extra_edges(n, m, used, edges);
  print_graph(n, edges);
}

void generate_line(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = choose_m(n, minM, maxM);
  vector<vector<int>> used(n + 1, vector<int>(n + 1));
  vector<pair<int, int>> edges;
  for (int i = 1; i < n; ++i)
    add_edge(used, edges, i, i + 1);
  fill_extra_edges(n, m, used, edges);
  print_graph(n, edges);
}

void generate_star(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = choose_m(n, minM, maxM);
  vector<vector<int>> used(n + 1, vector<int>(n + 1));
  vector<pair<int, int>> edges;
  for (int i = 2; i <= n; ++i)
    add_edge(used, edges, 1, i);
  fill_extra_edges(n, m, used, edges);
  print_graph(n, edges);
}

void generate_dense(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int max_possible = n * (n - 1) / 2;
  int m = min(max(maxM, n - 1), max_possible);
  vector<vector<int>> used(n + 1, vector<int>(n + 1));
  vector<pair<int, int>> edges;
  for (int u = 1; u <= n; ++u) {
    for (int v = u + 1; v <= n; ++v) {
      if ((int)edges.size() == m)
        break;
      add_edge(used, edges, u, v);
    }
    if ((int)edges.size() == m)
      break;
  }
  print_graph(n, edges);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 2);
  int maxN = opt<int>("maxN", 100);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 5000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM);
  else if (mode == "line")
    generate_line(minN, maxN, minM, maxM);
  else if (mode == "star")
    generate_star(minN, maxN, minM, maxM);
  else if (mode == "dense")
    generate_dense(minN, maxN, minM, maxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
