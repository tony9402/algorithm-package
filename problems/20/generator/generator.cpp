#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MIN_VALUE = -2147483648;
const int MAX_VALUE = 2147483647;

void print_case(const vector<int> &a, const vector<int> &b) {
  cout << a.size() << '\n';
  for (int i = 0; i < (int)a.size(); ++i)
    cout << a[i] << (i + 1 == (int)a.size() ? '\n' : ' ');
  cout << b.size() << '\n';
  for (int i = 0; i < (int)b.size(); ++i)
    cout << b[i] << (i + 1 == (int)b.size() ? '\n' : ' ');
}

void generate_random(int minN, int maxN, int minM, int maxM, int minV,
                     int maxV) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  vector<int> a(n), b(m);
  for (int &value : a)
    value = rnd.next(minV, maxV);
  for (int &value : b)
    value = rnd.next(minV, maxV);
  print_case(a, b);
}

void generate_all_hits(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  vector<int> a(n), b(m);
  for (int i = 0; i < n; ++i)
    a[i] = i + 1;
  for (int i = 0; i < m; ++i)
    b[i] = a[rnd.next(0, n - 1)];
  print_case(a, b);
}

void generate_all_misses(int minN, int maxN, int minM, int maxM) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  vector<int> a(n), b(m);
  for (int i = 0; i < n; ++i)
    a[i] = i + 1;
  for (int i = 0; i < m; ++i)
    b[i] = n + i + 1;
  print_case(a, b);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 100000);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 100000);
  int minV = opt<int>("minV", MIN_VALUE);
  int maxV = opt<int>("maxV", MAX_VALUE);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM, minV, maxV);
  else if (mode == "all_hits")
    generate_all_hits(minN, maxN, minM, maxM);
  else if (mode == "all_misses")
    generate_all_misses(minN, maxN, minM, maxM);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
