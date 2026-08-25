#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

void generate_random(int minN, int maxN, int minM, int maxM, int startV) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  int v = startV == -1 ? rnd.next(1, n) : startV;

  cout << n << ' ' << m << ' ' << v << '\n';
  for (int i = 0; i < m; ++i) {
    cout << rnd.next(1, n) << ' ' << rnd.next(1, n) << '\n';
  }
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 1000);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 10000);
  int startV = opt<int>("startV", -1);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM, startV);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
