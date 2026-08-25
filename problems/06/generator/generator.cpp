#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void generate_random(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int max_allowed_m = min(maxM, n);
  if (minM > max_allowed_m) {
    cerr << "invalid generator bounds: minM is greater than min(maxM, N)\n";
    exit(1);
  }
  int m = rnd.next(minM, max_allowed_m);
  cout << n << ' ' << m << '\n';
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 8);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 8);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
