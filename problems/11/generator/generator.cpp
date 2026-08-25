#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

void generate_random(int minN, int maxN) {
  cout << rnd.next(minN, maxN) << '\n';
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 1000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
