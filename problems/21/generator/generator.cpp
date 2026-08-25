#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int choose_n(int minN, int maxN, int minV, int maxV) {
  int capacity = (int)min<long long>(maxV - 1LL * minV + 1, maxN);
  minN = min(minN, capacity);
  return rnd.next(minN, capacity);
}

int choose_c(int minC, int n) {
  int lower = min(minC, n);
  return rnd.next(lower, n);
}

void print_case(int c, const vector<int> &values) {
  cout << values.size() << ' ' << c << '\n';
  for (int value : values)
    cout << value << '\n';
}

void generate_random(int minN, int maxN, int minC, int minV, int maxV) {
  int n = choose_n(minN, maxN, minV, maxV);
  int c = choose_c(minC, n);

  set<int> positions;
  while ((int)positions.size() < n)
    positions.insert(rnd.next(minV, maxV));
  vector<int> values(positions.begin(), positions.end());
  shuffle(values.begin(), values.end());

  print_case(c, values);
}

void generate_even(int minN, int maxN, int minC, int minV, int maxV) {
  int n = choose_n(minN, maxN, minV, maxV);
  int c = choose_c(minC, n);
  vector<int> values(n);
  long long step = max(1LL, (maxV - 1LL * minV) / max(1, n - 1));
  for (int i = 0; i < n; ++i)
    values[i] = (int)(minV + step * i);
  shuffle(values.begin(), values.end());
  print_case(c, values);
}

void generate_clustered(int minN, int maxN, int minC, int minV, int maxV) {
  int n = choose_n(minN, maxN, minV, maxV);
  int c = choose_c(minC, n);
  int start = rnd.next(minV, maxV - n + 1);
  vector<int> values(n);
  for (int i = 0; i < n; ++i)
    values[i] = start + i;
  shuffle(values.begin(), values.end());
  print_case(c, values);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 2);
  int maxN = opt<int>("maxN", 200000);
  int minC = opt<int>("minC", 2);
  int minV = opt<int>("minV", 0);
  int maxV = opt<int>("maxV", 1000000000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minC, minV, maxV);
  else if (mode == "even")
    generate_even(minN, maxN, minC, minV, maxV);
  else if (mode == "clustered")
    generate_clustered(minN, maxN, minC, minV, maxV);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
