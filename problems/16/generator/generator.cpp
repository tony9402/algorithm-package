#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_ropes(const vector<int> &ropes) {
  cout << ropes.size() << '\n';
  for (int rope : ropes)
    cout << rope << '\n';
}

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> ropes(n);
  for (int &rope : ropes)
    rope = rnd.next(1, 10000);
  print_ropes(ropes);
}

void generate_equal(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  int value = rnd.next(1, 10000);
  vector<int> ropes(n, value);
  print_ropes(ropes);
}

void generate_extremes(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> ropes(n);
  for (int i = 0; i < n; ++i)
    ropes[i] = rnd.next(0, 3) == 0 ? 10000 : 1;
  print_ropes(ropes);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 100000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "equal")
    generate_equal(minN, maxN);
  else if (mode == "extremes")
    generate_extremes(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
