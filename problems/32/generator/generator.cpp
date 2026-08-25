#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> order(n);
  iota(order.begin(), order.end(), 1);
  shuffle(order.begin(), order.end());

  vector<vector<int>> prereq(n + 1);
  for (int i = 0; i < n; ++i) {
    int building = order[i];
    int limit = min(i, 5);
    int cnt = i == 0 ? 0 : rnd.next(0, limit);
    set<int> used;
    while ((int)used.size() < cnt)
      used.insert(order[rnd.next(0, i - 1)]);
    prereq[building].assign(used.begin(), used.end());
  }

  cout << n << '\n';
  for (int i = 1; i <= n; ++i) {
    cout << rnd.next(1, 100000);
    for (int p : prereq[i])
      cout << ' ' << p;
    cout << " -1\n";
  }
}

void generate_chain(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> order(n);
  iota(order.begin(), order.end(), 1);

  vector<vector<int>> prereq(n + 1);
  for (int i = 0; i < n; ++i) {
    int building = order[i];
    if (i > 0)
      prereq[building].push_back(order[i - 1]);
  }

  cout << n << '\n';
  for (int i = 1; i <= n; ++i) {
    cout << rnd.next(1, 100000);
    for (int p : prereq[i])
      cout << ' ' << p;
    cout << " -1\n";
  }
}

void generate_dense(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> order(n);
  iota(order.begin(), order.end(), 1);
  shuffle(order.begin(), order.end());

  vector<vector<int>> prereq(n + 1);
  for (int i = 0; i < n; ++i) {
    int building = order[i];
    int cnt = i == 0 ? 0 : rnd.next(0, i);
    set<int> used;
    while ((int)used.size() < cnt)
      used.insert(order[rnd.next(0, i - 1)]);
    prereq[building].assign(used.begin(), used.end());
  }

  cout << n << '\n';
  for (int i = 1; i <= n; ++i) {
    cout << rnd.next(1, 100000);
    for (int p : prereq[i])
      cout << ' ' << p;
    cout << " -1\n";
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 500);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "chain")
    generate_chain(minN, maxN);
  else if (mode == "dense")
    generate_dense(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
