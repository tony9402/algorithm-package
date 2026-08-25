#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void generate_random(int minN, int maxN, int minM, int maxM, bool hasMinM,
                     bool hasMaxM) {
  int n = rnd.next(minN, maxN);
  int max_possible = (int)min(100000LL, 1LL * n * (n - 1) / 2);
  int default_max_m = min(100000, max(1, n * 3));
  int min_m = hasMinM ? minM : 1;
  int max_m = hasMaxM ? maxM : default_max_m;
  min_m = min(min_m, max_possible);
  max_m = min(max_m, max_possible);
  if (min_m > max_m)
    min_m = max_m;
  int m = rnd.next(min_m, max_m);

  vector<int> order(n);
  iota(order.begin(), order.end(), 1);
  shuffle(order.begin(), order.end());

  set<pair<int, int>> edges;
  while ((int)edges.size() < m) {
    int a = rnd.next(0, n - 2);
    int b = rnd.next(a + 1, n - 1);
    edges.emplace(order[a], order[b]);
  }

  cout << n << ' ' << edges.size() << '\n';
  for (auto [a, b] : edges)
    cout << a << ' ' << b << '\n';
}

void generate_chain(int minN, int maxN, int minM, int maxM, bool hasMinM,
                    bool hasMaxM) {
  int n = rnd.next(minN, maxN);
  int max_possible = (int)min(100000LL, 1LL * n * (n - 1) / 2);
  int min_m = hasMinM ? minM : n - 1;
  int max_m = hasMaxM ? maxM : n - 1;
  min_m = min(min_m, max_possible);
  max_m = min(max_m, max_possible);
  if (min_m > max_m)
    min_m = max_m;
  int m = rnd.next(min_m, max_m);

  vector<int> order(n);
  iota(order.begin(), order.end(), 1);
  shuffle(order.begin(), order.end());

  set<pair<int, int>> edges;
  for (int i = 0; i + 1 < n && (int)edges.size() < m; ++i) {
    edges.emplace(order[i], order[i + 1]);
  }
  while ((int)edges.size() < m) {
    int a = rnd.next(0, n - 2);
    int b = rnd.next(a + 1, n - 1);
    edges.emplace(order[a], order[b]);
  }

  cout << n << ' ' << edges.size() << '\n';
  for (auto [a, b] : edges)
    cout << a << ' ' << b << '\n';
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 2);
  int maxN = opt<int>("maxN", 32000);
  string mode = opt<string>("mode", "random");
  bool hasMinM = has_opt("minM");
  bool hasMaxM = has_opt("maxM");
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 100000);

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM, hasMinM, hasMaxM);
  else if (mode == "chain")
    generate_chain(minN, maxN, minM, maxM, hasMinM, hasMaxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
