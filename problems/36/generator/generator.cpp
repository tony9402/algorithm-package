#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  cout << n << '\n';
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j)
        cout << ' ';
      cout << rnd.next(-1000, 1000);
    }
    cout << '\n';
  }
}

void generate_negative(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  cout << n << '\n';
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j)
        cout << ' ';
      cout << rnd.next(-1000, -1);
    }
    cout << '\n';
  }
}

void generate_positive(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  cout << n << '\n';
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j)
        cout << ' ';
      cout << rnd.next(1, 1000);
    }
    cout << '\n';
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 300);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "negative")
    generate_negative(minN, maxN);
  else if (mode == "positive")
    generate_positive(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
