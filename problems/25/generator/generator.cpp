#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

const int MAX_VALUE = 1 << 28;

void print_case(const vector<int> &a, const vector<int> &b,
                const vector<int> &c, const vector<int> &d) {
  int n = (int)a.size();
  ensure((int)b.size() == n && (int)c.size() == n && (int)d.size() == n);
  cout << n << '\n';
  for (int i = 0; i < n; ++i)
    cout << a[i] << ' ' << b[i] << ' ' << c[i] << ' ' << d[i] << '\n';
}

tuple<int, int, int, int> generate_quad(bool sum_zero) {
  if (!sum_zero) {
    return make_tuple(
        rnd.next(-MAX_VALUE, MAX_VALUE), rnd.next(-MAX_VALUE, MAX_VALUE),
        rnd.next(-MAX_VALUE, MAX_VALUE), rnd.next(-MAX_VALUE, MAX_VALUE));
  }
  int a = rnd.next(-MAX_VALUE / 3, MAX_VALUE / 3);
  int b = rnd.next(-MAX_VALUE / 3, MAX_VALUE / 3);
  int c = rnd.next(-MAX_VALUE / 3, MAX_VALUE / 3);
  int d = -(a + b + c);
  ensure(-MAX_VALUE <= d && d <= MAX_VALUE);
  return make_tuple(a, b, c, d);
}

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> a(n), b(n), c(n), d(n);
  for (int i = 0; i < n; ++i)
    tie(a[i], b[i], c[i], d[i]) = generate_quad(false);
  print_case(a, b, c, d);
}

void generate_random_exist_zero(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<int> a(n), b(n), c(n), d(n);
  int guaranteed = rnd.next(1, n);
  for (int i = 0; i < guaranteed; ++i)
    tie(a[i], b[i], c[i], d[i]) = generate_quad(true);
  for (int i = guaranteed; i < n; ++i)
    tie(a[i], b[i], c[i], d[i]) = generate_quad(false);
  shuffle(a.begin(), a.end());
  shuffle(b.begin(), b.end());
  shuffle(c.begin(), c.end());
  shuffle(d.begin(), d.end());
  print_case(a, b, c, d);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 4000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "random_exist_zero")
    generate_random_exist_zero(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
