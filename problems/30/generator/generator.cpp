#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void print_edges(int n, const vector<pair<int, int>> &edges) {
  cout << n << '\n';
  for (auto [a, b] : edges)
    cout << a << ' ' << b << '\n';
}

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> edges;
  edges.reserve(n - 1);

  for (int i = 2; i <= n; ++i)
    edges.emplace_back(rnd.next(1, i - 1), i);
  shuffle(edges.begin(), edges.end());
  print_edges(n, edges);
}

void generate_chain(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> edges;
  edges.reserve(n - 1);
  for (int i = 1; i < n; ++i)
    edges.emplace_back(i, i + 1);
  print_edges(n, edges);
}

void generate_star(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> edges;
  edges.reserve(n - 1);
  for (int i = 2; i <= n; ++i)
    edges.emplace_back(1, i);
  print_edges(n, edges);
}

void generate_binary(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> edges;
  edges.reserve(n - 1);
  for (int i = 2; i <= n; ++i)
    edges.emplace_back(i / 2, i);
  print_edges(n, edges);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 2);
  int maxN = opt<int>("maxN", 1000000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "chain")
    generate_chain(minN, maxN);
  else if (mode == "star")
    generate_star(minN, maxN);
  else if (mode == "binary")
    generate_binary(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
