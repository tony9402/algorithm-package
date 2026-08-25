#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

void generate_dag(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  if (n == 1) {
    cout << "1 1\n1 1 0\n";
    return;
  }

  vector<tuple<int, int, int>> edges;
  set<pair<int, int>> used;
  auto add_unique = [&](int a, int b, int c) {
    if (a == b || !used.insert({a, b}).second) {
      return false;
    }
    edges.emplace_back(a, b, c);
    return true;
  };

  long long possible = 1LL * n * (n - 1) / 2;
  int target_max = min<long long>(maxM, possible);
  target_max = max(target_max, (int)edges.size());
  int target_min = min(minM, target_max);
  int target = max(rnd.next(target_min, target_max), (int)edges.size());

  int attempts = 0;
  while ((int)edges.size() < target && attempts < 200000) {
    ++attempts;
    int a = rnd.next(1, n);
    int b = rnd.next(1, n);
    if (a == b) {
      continue;
    }
    if (a > b) {
      swap(a, b);
    }
    add_unique(a, b, rnd.next(-10000, 10000));
  }

  cout << n << ' ' << edges.size() << '\n';
  for (auto [a, b, c] : edges)
    cout << a << ' ' << b << ' ' << c << '\n';
}

void generate_negative_cycle(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  if (n == 1) {
    cout << "1 1\n1 1 0\n";
    return;
  }

  vector<tuple<int, int, int>> edges;
  set<pair<int, int>> used;
  auto add_unique = [&](int a, int b, int c) {
    if (a == b || !used.insert({a, b}).second) {
      return false;
    }
    edges.emplace_back(a, b, c);
    return true;
  };

  add_unique(1, 2, -1);
  add_unique(2, 1, -1);

  long long possible = 1LL * n * (n - 1);
  int target_max = min<long long>(maxM, possible);
  target_max = max(target_max, (int)edges.size());
  int target_min = min(minM, target_max);
  int target = max(rnd.next(target_min, target_max), (int)edges.size());

  int attempts = 0;
  while ((int)edges.size() < target && attempts < 200000) {
    ++attempts;
    int a = rnd.next(1, n);
    int b = rnd.next(1, n);
    if (a != b) {
      add_unique(a, b, rnd.next(-10000, 10000));
    }
  }

  cout << n << ' ' << edges.size() << '\n';
  for (auto [a, b, c] : edges)
    cout << a << ' ' << b << ' ' << c << '\n';
}

void generate_unreachable(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  if (n == 1) {
    cout << "1 1\n1 1 0\n";
    return;
  }

  vector<tuple<int, int, int>> edges;
  set<pair<int, int>> used;
  auto add_unique = [&](int a, int b, int c) {
    if (a == b || !used.insert({a, b}).second) {
      return false;
    }
    edges.emplace_back(a, b, c);
    return true;
  };

  add_unique(2, 1, rnd.next(-10, 10));

  long long possible = 1LL * (n - 1) * (n - 1);
  int target_max = min<long long>(maxM, possible);
  target_max = max(target_max, (int)edges.size());
  int target_min = min(minM, target_max);
  int target = max(rnd.next(target_min, target_max), (int)edges.size());

  int attempts = 0;
  while ((int)edges.size() < target && attempts < 200000) {
    ++attempts;
    int a = rnd.next(2, n);
    int b = rnd.next(1, n);
    if (a != b) {
      add_unique(a, b, rnd.next(-10000, 10000));
    }
  }

  cout << n << ' ' << edges.size() << '\n';
  for (auto [a, b, c] : edges)
    cout << a << ' ' << b << ' ' << c << '\n';
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 500);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 6000);
  string mode = opt<string>("mode", "dag");

  if (mode == "dag")
    generate_dag(minN, maxN, minM, maxM);
  else if (mode == "negative_cycle")
    generate_negative_cycle(minN, maxN, minM, maxM);
  else if (mode == "unreachable")
    generate_unreachable(minN, maxN, minM, maxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
