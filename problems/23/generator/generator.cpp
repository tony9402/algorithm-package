#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> values(n), prefix(n + 1);
  for (int i = 0; i < n; ++i) {
    values[i] = rnd.next(1, 30000);
    prefix[i + 1] = prefix[i] + values[i];
  }

  int target;
  if (rnd.next(0, 1)) {
    target = rnd.next(1, 300000000);
  } else {
    int l = rnd.next(0, n - 1);
    int r = rnd.next(l, n - 1);
    target = prefix[r + 1] - prefix[l];
  }

  cout << n << ' ' << target << '\n';
  for (int i = 0; i < n; ++i)
    cout << values[i] << (i + 1 == n ? '\n' : ' ');
}

void generate_exact(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> values(n, 1);
  int target = rnd.next(1, n);

  cout << n << ' ' << target << '\n';
  for (int i = 0; i < n; ++i)
    cout << values[i] << (i + 1 == n ? '\n' : ' ');
}

void generate_no_solution(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> values(n, 1);
  int target = 300000000;

  cout << n << ' ' << target << '\n';
  for (int i = 0; i < n; ++i)
    cout << values[i] << (i + 1 == n ? '\n' : ' ');
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 10000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "exact")
    generate_exact(minN, maxN);
  else if (mode == "no_solution")
    generate_no_solution(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
