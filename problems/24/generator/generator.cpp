#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void generate_random(int minN, int maxN, int minD, int maxD, int minK,
                     int maxK) {
  int n = rnd.next(minN, maxN);
  int d = rnd.next(minD, maxD);
  int max_allowed_k = min(maxK, n);
  int min_allowed_k = min(minK, max_allowed_k);
  int k = rnd.next(min_allowed_k, max_allowed_k);

  vector<int> sushi(n);
  for (int &item : sushi)
    item = rnd.next(1, d);
  int coupon = rnd.next(0, 1) ? sushi[rnd.next(0, n - 1)] : rnd.next(1, d);

  cout << n << ' ' << d << ' ' << k << ' ' << coupon << '\n';
  for (int item : sushi)
    cout << item << '\n';
}

void generate_coupon_absent(int minN, int maxN, int minD, int maxD, int minK,
                            int maxK) {
  int n = rnd.next(minN, maxN);
  int d = rnd.next(max(2, minD), maxD);
  int max_allowed_k = min(maxK, n);
  int min_allowed_k = min(minK, max_allowed_k);
  int k = rnd.next(min_allowed_k, max_allowed_k);
  int coupon = d;

  cout << n << ' ' << d << ' ' << k << ' ' << coupon << '\n';
  for (int i = 0; i < n; ++i)
    cout << rnd.next(1, d - 1) << '\n';
}

void generate_all_same(int minN, int maxN, int minD, int maxD, int minK,
                       int maxK) {
  int n = rnd.next(minN, maxN);
  int d = rnd.next(max(2, minD), maxD);
  int max_allowed_k = min(maxK, n);
  int min_allowed_k = min(minK, max_allowed_k);
  int k = rnd.next(min_allowed_k, max_allowed_k);
  int item = rnd.next(1, d);
  int coupon = item == d ? 1 : d;

  cout << n << ' ' << d << ' ' << k << ' ' << coupon << '\n';
  for (int i = 0; i < n; ++i)
    cout << item << '\n';
}

void generate_cycle(int minN, int maxN, int minD, int maxD, int minK,
                    int maxK) {
  int n = rnd.next(minN, maxN);
  int d = rnd.next(minD, maxD);
  int max_allowed_k = min(maxK, n);
  int min_allowed_k = min(minK, max_allowed_k);
  int k = rnd.next(min_allowed_k, max_allowed_k);
  int coupon = rnd.next(1, d);

  cout << n << ' ' << d << ' ' << k << ' ' << coupon << '\n';
  for (int i = 0; i < n; ++i)
    cout << i % d + 1 << '\n';
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 2);
  int maxN = opt<int>("maxN", 3000000);
  int minD = opt<int>("minD", 2);
  int maxD = opt<int>("maxD", 3000);
  int minK = opt<int>("minK", 2);
  int maxK = opt<int>("maxK", 3000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minD, maxD, minK, maxK);
  else if (mode == "coupon_absent")
    generate_coupon_absent(minN, maxN, minD, maxD, minK, maxK);
  else if (mode == "all_same")
    generate_all_same(minN, maxN, minD, maxD, minK, maxK);
  else if (mode == "cycle")
    generate_cycle(minN, maxN, minD, maxD, minK, maxK);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
