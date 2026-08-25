#include "testlib.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void print_lectures(const vector<pair<int, int>> &lectures) {
  cout << lectures.size() << '\n';
  for (auto [pay, day] : lectures)
    cout << pay << ' ' << day << '\n';
}

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> lectures;
  for (int i = 0; i < n; ++i)
    lectures.emplace_back(rnd.next(1, 10000), rnd.next(1, 10000));
  print_lectures(lectures);
}

void generate_same_deadline(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> lectures;
  lectures.reserve(n);
  int day = rnd.next(1, 10);
  for (int i = 0; i < n; ++i)
    lectures.emplace_back(rnd.next(1, 10000), day);
  print_lectures(lectures);
}

void generate_tight_deadlines(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> lectures;
  lectures.reserve(n);
  for (int i = 0; i < n; ++i)
    lectures.emplace_back(rnd.next(1, 10000), rnd.next(1, 20));
  print_lectures(lectures);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 0);
  int maxN = opt<int>("maxN", 10000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "same_deadline")
    generate_same_deadline(minN, maxN);
  else if (mode == "tight_deadlines")
    generate_tight_deadlines(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
