#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<string> names;
  map<string, int> cnt;
  while (n--) {
    string s;
    cin >> s;
    string alias = s;
    for (size_t len = 1; len <= s.size(); len++) {
      string p = s.substr(0, len);
      bool exists = false;
      for (string &old : names)
        if (old.rfind(p, 0) == 0)
          exists = true;
      if (!exists) {
        alias = p;
        break;
      }
    }
    if (cnt[s])
      cout << s << cnt[s] + 1 << '\n';
    else
      cout << alias << '\n';
    cnt[s]++;
    names.push_back(s);
  }
}