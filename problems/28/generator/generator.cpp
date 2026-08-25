#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

void add_edge(vector<vector<int>> &g, int a, int b) {
  if (a == b || g[a][b])
    return;
  g[a][b] = g[b][a] = 1;
}

void print_case(int n, const vector<int> &pop, const vector<vector<int>> &g) {
  cout << n << '\n';
  for (int i = 1; i <= n; ++i)
    cout << pop[i] << (i == n ? '\n' : ' ');
  for (int i = 1; i <= n; ++i) {
    vector<int> adj;
    for (int j = 1; j <= n; ++j) {
      if (g[i][j])
        adj.push_back(j);
    }
    cout << adj.size();
    for (int v : adj)
      cout << ' ' << v;
    cout << '\n';
  }
}

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> pop(n + 1);
  for (int i = 1; i <= n; ++i)
    pop[i] = rnd.next(1, 100);

  vector<vector<int>> g(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (rnd.next(0, 99) < 35)
        add_edge(g, i, j);
    }
  }
  print_case(n, pop, g);
}

void generate_connected(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> pop(n + 1);
  for (int i = 1; i <= n; ++i)
    pop[i] = rnd.next(1, 100);

  vector<vector<int>> g(n + 1, vector<int>(n + 1));
  vector<int> nodes(n);
  iota(nodes.begin(), nodes.end(), 1);
  shuffle(nodes.begin(), nodes.end());
  for (int i = 1; i < (int)nodes.size(); ++i)
    add_edge(g, nodes[i], nodes[rnd.next(0, i - 1)]);
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (rnd.next(0, 99) < 25)
        add_edge(g, i, j);
    }
  }
  print_case(n, pop, g);
}

void generate_disconnected(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> pop(n + 1);
  for (int i = 1; i <= n; ++i)
    pop[i] = rnd.next(1, 100);

  vector<vector<int>> g(n + 1, vector<int>(n + 1));
  int cut = rnd.next(1, n - 1);
  vector<int> left, right;
  for (int i = 1; i <= n; ++i)
    (i <= cut ? left : right).push_back(i);
  for (int i = 1; i < (int)left.size(); ++i)
    add_edge(g, left[i], left[rnd.next(0, i - 1)]);
  for (int i = 1; i < (int)right.size(); ++i)
    add_edge(g, right[i], right[rnd.next(0, i - 1)]);
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if ((i <= cut) == (j <= cut) && rnd.next(0, 99) < 30)
        add_edge(g, i, j);
    }
  }
  print_case(n, pop, g);
}

void generate_isolated(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> pop(n + 1);
  for (int i = 1; i <= n; ++i)
    pop[i] = rnd.next(1, 100);

  vector<vector<int>> g(n + 1, vector<int>(n + 1));
  print_case(n, pop, g);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 2);
  int maxN = opt<int>("maxN", 10);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "connected")
    generate_connected(minN, maxN);
  else if (mode == "disconnected")
    generate_disconnected(minN, maxN);
  else if (mode == "isolated")
    generate_isolated(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
