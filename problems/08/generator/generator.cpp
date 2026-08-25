#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

void generate_random(int minN, int maxN, int minK, int maxK) {
  cout << rnd.next(minN, maxN) << ' ' << rnd.next(minK, maxK) << '\n';
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 0);
  int maxN = opt<int>("maxN", 100000);
  int minK = opt<int>("minK", 0);
  int maxK = opt<int>("maxK", 100000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minK, maxK);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
