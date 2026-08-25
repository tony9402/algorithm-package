#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

void generate_random(int minV, int maxV, int minE, int maxE, bool hasMinE,
                     bool hasMaxE) {
  int v = rnd.next(minV, maxV);
  long long possible_edges = 1LL * v * (v - 1);
  int max_possible = (int)min(300000LL, possible_edges);
  int default_max_e = min(max_possible, max(1, v * 3));
  int min_e = hasMinE ? minE : 1;
  int max_e = hasMaxE ? maxE : default_max_e;
  min_e = min(min_e, max_possible);
  max_e = min(max_e, max_possible);
  if (min_e > max_e)
    min_e = max_e;
  int e = rnd.next(min_e, max_e);
  int start = rnd.next(1, v);

  set<pair<int, int>> used;
  vector<tuple<int, int, int>> edges;
  auto add = [&](int a, int b) {
    if (a == b || !used.insert({a, b}).second) {
      return false;
    }
    edges.emplace_back(a, b, rnd.next(1, 10));
    return true;
  };

  while ((int)edges.size() < e) {
    int a = rnd.next(1, v);
    int b = rnd.next(1, v);
    if (a != b) {
      add(a, b);
    }
  }

  cout << v << ' ' << edges.size() << '\n' << start << '\n';
  for (auto [a, b, w] : edges)
    cout << a << ' ' << b << ' ' << w << '\n';
}

void generate_chain(int minV, int maxV, int minE, int maxE, bool hasMinE,
                    bool hasMaxE) {
  int v = rnd.next(minV, maxV);
  long long possible_edges = max(1, v - 1);
  int max_possible = (int)min(300000LL, possible_edges);
  int min_e = hasMinE ? minE : max(1, v - 1);
  int max_e = hasMaxE ? maxE : max(1, v - 1);
  min_e = min(min_e, max_possible);
  max_e = min(max_e, max_possible);
  if (min_e > max_e)
    min_e = max_e;
  int e = rnd.next(min_e, max_e);
  int start = rnd.next(1, v);

  set<pair<int, int>> used;
  vector<tuple<int, int, int>> edges;
  auto add = [&](int a, int b) {
    if (a == b || !used.insert({a, b}).second) {
      return false;
    }
    edges.emplace_back(a, b, rnd.next(1, 10));
    return true;
  };

  for (int i = 1; i < v && (int)edges.size() < e; ++i) {
    add(i, i + 1);
  }

  cout << v << ' ' << edges.size() << '\n' << start << '\n';
  for (auto [a, b, w] : edges)
    cout << a << ' ' << b << ' ' << w << '\n';
}

void generate_unreachable(int minV, int maxV, int minE, int maxE, bool hasMinE,
                          bool hasMaxE) {
  int v = rnd.next(minV, maxV);
  int cut = max(1, v / 2);
  long long possible_edges = 1LL * v * (v - 1) - 1LL * cut * (v - cut);
  int max_possible = (int)min(300000LL, possible_edges);
  int default_max_e = min(max_possible, max(1, v * 3));
  int min_e = hasMinE ? minE : 1;
  int max_e = hasMaxE ? maxE : default_max_e;
  min_e = min(min_e, max_possible);
  max_e = min(max_e, max_possible);
  if (min_e > max_e)
    min_e = max_e;
  int e = rnd.next(min_e, max_e);
  int start = 1;

  set<pair<int, int>> used;
  vector<tuple<int, int, int>> edges;
  auto add = [&](int a, int b) {
    if (a == b || !used.insert({a, b}).second) {
      return false;
    }
    edges.emplace_back(a, b, rnd.next(1, 10));
    return true;
  };

  for (int i = 1; i < cut && (int)edges.size() < e; ++i) {
    add(i, i + 1);
  }
  while ((int)edges.size() < e) {
    int a = rnd.next(1, v);
    int b = rnd.next(1, v);
    if (a == b || (a <= cut && b > cut)) {
      continue;
    }
    add(a, b);
  }

  cout << v << ' ' << edges.size() << '\n' << start << '\n';
  for (auto [a, b, w] : edges)
    cout << a << ' ' << b << ' ' << w << '\n';
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minV = opt<int>("minV", 2);
  int maxV = opt<int>("maxV", 20000);
  minV = max(minV, 2);
  maxV = max(maxV, minV);
  bool hasMinE = has_opt("minE");
  bool hasMaxE = has_opt("maxE");
  int minE = opt<int>("minE", 1);
  int maxE = opt<int>("maxE", 300000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minV, maxV, minE, maxE, hasMinE, hasMaxE);
  else if (mode == "chain")
    generate_chain(minV, maxV, minE, maxE, hasMinE, hasMaxE);
  else if (mode == "unreachable")
    generate_unreachable(minV, maxV, minE, maxE, hasMinE, hasMaxE);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
