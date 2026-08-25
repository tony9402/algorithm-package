#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

const int MAX_VALUE = 300000;

void generate_random(int minR, int maxR, int minC, int maxC) {
  int r = rnd.next(minR, maxR);
  int c = rnd.next(minC, maxC);
  vector<int> values(MAX_VALUE + 1);
  iota(values.begin(), values.end(), 0);
  shuffle(values.begin(), values.end());

  cout << r << ' ' << c << '\n';
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (j)
        cout << ' ';
      cout << values[i * c + j];
    }
    cout << '\n';
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minR = opt<int>("minR", 1);
  int maxR = opt<int>("maxR", 500);
  int minC = opt<int>("minC", 1);
  int maxC = opt<int>("maxC", 500);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minR, maxR, minC, maxC);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
