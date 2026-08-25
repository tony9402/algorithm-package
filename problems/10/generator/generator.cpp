#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

void generate_random(int n) {
  int value = n;
  cout << value << '\n';
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int n = opt<int>("N", 1);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(n);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
