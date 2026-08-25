#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  cout << n << '\n';
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      if (c)
        cout << ' ';
      cout << rnd.next(0, 1);
    }
    cout << '\n';
  }
}

void generate_sparse(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  cout << n << '\n';
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      if (c)
        cout << ' ';
      cout << (rnd.next(0, 9) == 0);
    }
    cout << '\n';
  }
}

void generate_checkerboard(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  cout << n << '\n';
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      if (c)
        cout << ' ';
      cout << ((r + c) & 1);
    }
    cout << '\n';
  }
}

void generate_all_on(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  cout << n << '\n';
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      if (c)
        cout << ' ';
      cout << 1;
    }
    cout << '\n';
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 2);
  int maxN = opt<int>("maxN", 18);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "sparse")
    generate_sparse(minN, maxN);
  else if (mode == "checkerboard")
    generate_checkerboard(minN, maxN);
  else if (mode == "all_on")
    generate_all_on(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
