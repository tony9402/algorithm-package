#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>

using namespace std;

void generate_random(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int default_m = min(100000, max(1, n * 4));
  int upper_m = min(maxM, default_m);
  if (upper_m < minM)
    upper_m = minM;
  int m = rnd.next(minM, upper_m);

  cout << n << '\n' << m << '\n';
  set<pair<int, int>> used;
  for (int i = 0; i < m; ++i) {
    int a, b;
    do {
      a = rnd.next(1, n);
      b = rnd.next(1, n);
    } while (a == b ||
             (!used.insert({a, b}).second && (int)used.size() < n * (n - 1)));
    cout << a << ' ' << b << ' ' << rnd.next(1, 100000) << '\n';
  }
}

void generate_dense(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int default_m = min(100000, n * (n - 1) * 3);
  int upper_m = min(maxM, default_m);
  if (upper_m < minM)
    upper_m = minM;
  int m = rnd.next(minM, upper_m);

  cout << n << '\n' << m << '\n';
  set<pair<int, int>> used;
  for (int i = 0; i < m; ++i) {
    int a, b;
    do {
      a = rnd.next(1, n);
      b = rnd.next(1, n);
    } while (a == b ||
             (!used.insert({a, b}).second && (int)used.size() < n * (n - 1)));
    cout << a << ' ' << b << ' ' << rnd.next(1, 100000) << '\n';
  }
}

void generate_duplicates(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int default_m = min(100000, max(1, n * 4));
  int upper_m = min(maxM, default_m);
  if (upper_m < minM)
    upper_m = minM;
  int m = rnd.next(minM, upper_m);

  cout << n << '\n' << m << '\n';
  for (int i = 0; i < m; ++i) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n);
    while (a == b)
      b = rnd.next(1, n);
    cout << a << ' ' << b << ' ' << rnd.next(1, 100000) << '\n';
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 2);
  int maxN = opt<int>("maxN", 100);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 100000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM);
  else if (mode == "dense")
    generate_dense(minN, maxN, minM, maxM);
  else if (mode == "duplicates")
    generate_duplicates(minN, maxN, minM, maxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
