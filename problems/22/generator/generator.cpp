#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void generate_random(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  minM = min(minM, n);
  maxM = min(maxM, n);
  int m = rnd.next(minM, maxM);

  cout << n << ' ' << m << '\n';
  for (int i = 0; i < n; ++i) {
    cout << rnd.next(1, 100) << (i + 1 == n ? '\n' : ' ');
  }
}

void generate_uniform(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  minM = min(minM, n);
  maxM = min(maxM, n);
  int m = rnd.next(minM, maxM);
  int value = rnd.next(1, 100);

  cout << n << ' ' << m << '\n';
  for (int i = 0; i < n; ++i) {
    cout << value << (i + 1 == n ? '\n' : ' ');
  }
}

void generate_high_values(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  minM = min(minM, n);
  maxM = min(maxM, n);
  int m = rnd.next(minM, maxM);

  cout << n << ' ' << m << '\n';
  for (int i = 0; i < n; ++i) {
    cout << (i % 2 ? 100 : 99) << (i + 1 == n ? '\n' : ' ');
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 300);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", maxN);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM);
  else if (mode == "uniform")
    generate_uniform(minN, maxN, minM, maxM);
  else if (mode == "high_values")
    generate_high_values(minN, maxN, minM, maxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
