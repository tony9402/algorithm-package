#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string random_name(int max_len, int alphabet) {
  int len = rnd.next(1, max_len);
  string s;
  s.reserve(len);
  for (int i = 0; i < len; ++i)
    s.push_back(char('a' + rnd.next(0, alphabet - 1)));
  return s;
}

void print_names(const vector<string> &names) {
  cout << names.size() << '\n';
  for (const string &name : names)
    cout << name << '\n';
}

void generate_random(int n) {
  vector<string> names;
  names.reserve(n);
  for (int i = 0; i < n; ++i)
    names.push_back(random_name(10, 26));
  print_names(names);
}

void generate_duplicates(int n) {
  int candidate_count = max(n * 8 / 10, 1);
  vector<string> candidates(candidate_count);
  for (string &name : candidates)
    name = random_name(10, 26);

  vector<string> names;
  names.reserve(n);
  for (int i = 0; i < n; ++i)
    names.push_back(candidates[rnd.next(0, candidate_count - 1)]);
  print_names(names);
}

void generate_prefixes(int n) {
  vector<string> names;
  names.reserve(n);
  string current = random_name(1, 3);
  for (int i = 0; i < n; ++i) {
    if ((int)current.size() < 10 && rnd.next(0, 2) != 0) {
      current.push_back(char('a' + rnd.next(0, 2)));
    } else if (rnd.next(0, 1)) {
      current = current.substr(0, rnd.next(1, (int)current.size()));
    } else {
      current = random_name(10, 3);
    }
    names.push_back(current);
  }
  print_names(names);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 100000);
  string mode = opt<string>("mode", "random");
  int n = rnd.next(minN, maxN);

  if (mode == "random")
    generate_random(n);
  else if (mode == "duplicates")
    generate_duplicates(n);
  else if (mode == "prefixes")
    generate_prefixes(n);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
