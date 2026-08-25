#include "testlib.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void print_meetings(const vector<pair<int, int>> &meetings) {
  cout << meetings.size() << '\n';
  for (auto [l, r] : meetings)
    cout << l << ' ' << r << '\n';
}

void generate_random(int minN, int maxN, int maxTime) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> meetings;
  meetings.reserve(n);
  for (int i = 0; i < n; ++i) {
    int l = rnd.next(0, maxTime);
    int r = rnd.next(l, maxTime);
    meetings.emplace_back(l, r);
  }
  print_meetings(meetings);
}

void generate_touching(int minN, int maxN, int maxTime) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> meetings;
  meetings.reserve(n);
  for (int i = 0; i < n; ++i) {
    int l = maxTime == 0 ? 0 : i % maxTime;
    int r = l == maxTime ? maxTime : l + 1;
    meetings.emplace_back(l, r);
  }
  print_meetings(meetings);
}

void generate_same_end(int minN, int maxN, int maxTime) {
  int n = rnd.next(minN, maxN);
  int endTime = rnd.next(0, maxTime);
  vector<pair<int, int>> meetings;
  meetings.reserve(n);
  for (int i = 0; i < n; ++i)
    meetings.emplace_back(rnd.next(0, endTime), endTime);
  print_meetings(meetings);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 100000);
  int maxTime = opt<int>("max_time", 2147483647);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, maxTime);
  else if (mode == "touching")
    generate_touching(minN, maxN, maxTime);
  else if (mode == "same_end")
    generate_same_end(minN, maxN, maxTime);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
