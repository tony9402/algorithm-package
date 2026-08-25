#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

string random_word(int max_len, int alphabet) {
  int len = rnd.next(1, max_len);
  string s;
  s.reserve(len);
  for (int i = 0; i < len; ++i)
    s.push_back(char('a' + rnd.next(0, alphabet - 1)));
  return s;
}

void generate_random(int minN, int maxN, int minM, int maxM, int maxLen) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  int cappedLen = min(maxLen, 500);

  set<string> used;
  vector<string> words;
  while ((int)words.size() < n) {
    string s = random_word(cappedLen, 26);
    if (used.insert(s).second)
      words.push_back(s);
  }

  cout << n << ' ' << m << '\n';
  for (const string &s : words)
    cout << s << '\n';
  for (int i = 0; i < m; ++i) {
    if (rnd.next(0, 99) < 60) {
      const string &base = words[rnd.next(0, n - 1)];
      cout << base.substr(0, rnd.next(1, (int)base.size())) << '\n';
    } else {
      cout << random_word(cappedLen, 26) << '\n';
    }
  }
}

void generate_prefix_heavy(int minN, int maxN, int minM, int maxM, int maxLen) {
  int n = rnd.next(minN, maxN);
  int m = rnd.next(minM, maxM);
  int cappedLen = min(maxLen, 500);

  set<string> used;
  vector<string> words;
  while ((int)words.size() < n) {
    string s =
        string(rnd.next(1, min(cappedLen, 30)), char('a' + rnd.next(0, 2)));
    if (rnd.next(0, 1))
      s += random_word(max(1, cappedLen / 2), 3);
    if ((int)s.size() > 500)
      s.resize(500);
    if (used.insert(s).second)
      words.push_back(s);
  }

  cout << n << ' ' << m << '\n';
  for (const string &s : words)
    cout << s << '\n';
  for (int i = 0; i < m; ++i) {
    if (rnd.next(0, 99) < 60) {
      const string &base = words[rnd.next(0, n - 1)];
      cout << base.substr(0, rnd.next(1, (int)base.size())) << '\n';
    } else {
      cout << random_word(cappedLen, 3) << '\n';
    }
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 10000);
  int minM = opt<int>("minM", 1);
  int maxM = opt<int>("maxM", 10000);
  int maxLen = opt<int>("maxLen", 20);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN, minM, maxM, maxLen);
  else if (mode == "prefix_heavy")
    generate_prefix_heavy(minN, maxN, minM, maxM, maxLen);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
