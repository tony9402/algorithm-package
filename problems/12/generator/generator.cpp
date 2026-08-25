#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_values(const vector<int> &values) {
  cout << values.size() << '\n';
  for (int value : values)
    cout << value << '\n';
}

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> values(n);
  for (int &value : values)
    value = rnd.next(1, 10000);
  print_values(values);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 300);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
