#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void generate_random(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);

  cout << n << '\n';
  for (int i = 1; i <= n; ++i)
    cout << rnd.next(1, 1000) << (i == n ? '\n' : ' ');
  cout << m << '\n';
  for (int i = 0; i < m; ++i) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n);
    if (a > b)
      swap(a, b);
    cout << a << ' ' << b << '\n';
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 100000);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 100000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
