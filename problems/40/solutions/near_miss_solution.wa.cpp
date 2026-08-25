#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  set<string> s;
  while (n--) {
    string x;
    cin >> x;
    s.insert(x);
  }
  int ans = 0;
  while (m--) {
    string q;
    cin >> q;
    if (s.count(q))
      ans++;
  }
  cout << ans;
}